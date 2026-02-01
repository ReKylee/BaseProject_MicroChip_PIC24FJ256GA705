#include "I2C.h"
#include "../System/delay.h"
#include <stdlib.h>

static i2c_config_t config;

typedef enum {
    I2C1_MESSAGE_FAIL,
    I2C1_MESSAGE_PENDING,
    I2C1_MESSAGE_COMPLETE,
    I2C1_STUCK_START,
    I2C1_MESSAGE_ADDRESS_NO_ACK,
    I2C1_DATA_NO_ACK,
    I2C1_LOST_STATE
} I2C1_MESSAGE_STATUS;

typedef struct {
    uint16_t address;
    uint8_t length;
    uint8_t *pbuffer;
} I2C1_TRANSACTION_REQUEST_BLOCK;

typedef union {
    struct {
        uint8_t full:1;
        uint8_t empty:1;
        uint8_t reserved:6;
    } s;
    uint8_t status;
} I2C_TR_QUEUE_STATUS;

typedef struct {
    uint8_t count;
    I2C1_TRANSACTION_REQUEST_BLOCK *ptrb_list;
    I2C1_MESSAGE_STATUS *pTrFlag;
} I2C_TR_QUEUE_ENTRY;

typedef struct {
    I2C_TR_QUEUE_ENTRY *pTrTail;
    I2C_TR_QUEUE_ENTRY *pTrHead;
    I2C_TR_QUEUE_STATUS trStatus;
#if I2C1_ENABLE_ERROR_COUNT
    uint8_t i2cErrors;
#endif
} I2C_OBJECT;

typedef enum {
    S_MASTER_IDLE,
    S_MASTER_RESTART,
    S_MASTER_SEND_ADDR,
    S_MASTER_SEND_DATA,
    S_MASTER_SEND_STOP,
    S_MASTER_ACK_ADDR,
    S_MASTER_RCV_DATA,
    S_MASTER_RCV_STOP,
    S_MASTER_ACK_RCV_DATA,
    S_MASTER_NOACK_STOP,
#if I2C1_ENABLE_10BIT
    S_MASTER_SEND_ADDR_10BIT_LSB,
    S_MASTER_10BIT_RESTART
#endif
} I2C_MASTER_STATES;

#define I2C1_TRANSMIT_REG                       I2C1TRN
#define I2C1_RECEIVE_REG                        I2C1RCV
#define I2C1_WRITE_COLLISION_STATUS_BIT         I2C1STATbits.IWCOL
#define I2C1_ACKNOWLEDGE_STATUS_BIT             I2C1STATbits.ACKSTAT
#define I2C1_START_CONDITION_ENABLE_BIT         I2C1CONLbits.SEN
#define I2C1_REPEAT_START_CONDITION_ENABLE_BIT  I2C1CONLbits.RSEN
#define I2C1_RECEIVE_ENABLE_BIT                 I2C1CONLbits.RCEN
#define I2C1_STOP_CONDITION_ENABLE_BIT          I2C1CONLbits.PEN
#define I2C1_ACKNOWLEDGE_ENABLE_BIT             I2C1CONLbits.ACKEN
#define I2C1_ACKNOWLEDGE_DATA_BIT               I2C1CONLbits.ACKDT

static volatile I2C_TR_QUEUE_ENTRY i2c1_tr_queue[I2C1_CONFIG_TR_QUEUE_LENGTH];
static I2C_OBJECT i2c1_object;
static volatile I2C_MASTER_STATES i2c1_state = S_MASTER_IDLE;
static uint8_t i2c1_trb_count;

static I2C1_TRANSACTION_REQUEST_BLOCK *p_i2c1_trb_current;
static I2C_TR_QUEUE_ENTRY *p_i2c1_current = NULL;

static void i2c1_function_complete(void);
static void i2c1_stop(I2C1_MESSAGE_STATUS completion_code);
static void i2c1_master_read_trb_build(I2C1_TRANSACTION_REQUEST_BLOCK *ptrb,
                                       uint8_t *pdata,
                                       uint8_t length,
                                       uint16_t address);
static void i2c1_master_write_trb_build(I2C1_TRANSACTION_REQUEST_BLOCK *ptrb,
                                        uint8_t *pdata,
                                        uint8_t length,
                                        uint16_t address);
static void i2c1_master_trb_insert(uint8_t count,
                                   I2C1_TRANSACTION_REQUEST_BLOCK *ptrb_list,
                                   I2C1_MESSAGE_STATUS *pflag);
static i2c_status_t i2c_wait_status(volatile I2C1_MESSAGE_STATUS *status);

void i2c_init(const i2c_config_t *cfg) {
    if (cfg) config = *cfg;
    else {
        config.bus_hz = 100000;
        config.timeout_ms = 50;
    }

    i2c1_object.pTrHead = (I2C_TR_QUEUE_ENTRY *)i2c1_tr_queue;
    i2c1_object.pTrTail = (I2C_TR_QUEUE_ENTRY *)i2c1_tr_queue;
    i2c1_object.trStatus.s.empty = true;
    i2c1_object.trStatus.s.full = false;
#if I2C1_ENABLE_ERROR_COUNT
    i2c1_object.i2cErrors = 0;
#endif

    I2C1CONLbits.I2CEN = 0;
    I2C1STAT = 0x0000;
    I2C1CONL = 0x0000;
    I2C1CONH = 0x0000;

    if (config.bus_hz > 400000) {
        I2C1CONLbits.DISSLW = 1;
        I2C1BRG = ((FCY / config.bus_hz) - 1);
    } else {
        I2C1CONLbits.DISSLW = 0;
        I2C1BRG = ((FCY / config.bus_hz - FCY / 10000000) - 1);
    }

    I2C1CONLbits.I2CEN = 1;
    IFS1bits.MI2C1IF = 0;
    IEC1bits.MI2C1IE = 1;

}

void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void) {
    static uint8_t *pi2c_buf_ptr;
    static uint16_t i2c_address;
    static uint8_t i2c_bytes_left;
#if I2C1_ENABLE_10BIT
    static uint8_t i2c_10bit_address_restart = 0;
#endif

    IFS1bits.MI2C1IF = 0;

    if (I2C1STATbits.BCL) {
        I2C1STATbits.BCL = 0;
        i2c1_state = S_MASTER_IDLE;
        if (p_i2c1_current && p_i2c1_current->pTrFlag) {
            *(p_i2c1_current->pTrFlag) = I2C1_MESSAGE_FAIL;
        }
        p_i2c1_current = NULL;
        return;
    }

    if (I2C1_WRITE_COLLISION_STATUS_BIT) {
        I2C1_WRITE_COLLISION_STATUS_BIT = 0;
        i2c1_state = S_MASTER_IDLE;
        if (p_i2c1_current && p_i2c1_current->pTrFlag) {
            *(p_i2c1_current->pTrFlag) = I2C1_MESSAGE_FAIL;
        }
        p_i2c1_current = NULL;
        return;
    }

    switch (i2c1_state) {
        case S_MASTER_IDLE:
            if (i2c1_object.trStatus.s.empty != true) {
#if I2C1_ENABLE_QUEUE
                p_i2c1_current     = i2c1_object.pTrHead;
                i2c1_trb_count     = i2c1_object.pTrHead->count;
                p_i2c1_trb_current = i2c1_object.pTrHead->ptrb_list;

                i2c1_object.pTrHead++;
                if (i2c1_object.pTrHead == (i2c1_tr_queue + I2C1_CONFIG_TR_QUEUE_LENGTH)) {
                    i2c1_object.pTrHead = i2c1_tr_queue;
                }

                i2c1_object.trStatus.s.full = false;
                if (i2c1_object.pTrHead == i2c1_object.pTrTail) {
                    i2c1_object.trStatus.s.empty = true;
                }
#else
                p_i2c1_current     = i2c1_object.pTrHead;
                i2c1_trb_count     = p_i2c1_current->count;
                p_i2c1_trb_current = p_i2c1_current->ptrb_list;
                i2c1_object.trStatus.s.empty = true;
#endif

                I2C1_START_CONDITION_ENABLE_BIT = 1;
                i2c1_state = S_MASTER_SEND_ADDR;
            }
            break;

        case S_MASTER_RESTART:
            I2C1_REPEAT_START_CONDITION_ENABLE_BIT = 1;
            i2c1_state = S_MASTER_SEND_ADDR;
            break;

#if I2C1_ENABLE_10BIT
        case S_MASTER_SEND_ADDR_10BIT_LSB:
            if (I2C1_ACKNOWLEDGE_STATUS_BIT) {
#if I2C1_ENABLE_ERROR_COUNT
                i2c1_object.i2cErrors++;
#endif
                i2c1_stop(I2C1_MESSAGE_ADDRESS_NO_ACK);
            } else {
                I2C1_TRANSMIT_REG = (i2c_address >> 1) & 0x00FF;
                if (i2c_address & 0x01) {
                    i2c1_state = S_MASTER_10BIT_RESTART;
                } else {
                    i2c1_state = S_MASTER_SEND_DATA;
                }
            }
            break;

        case S_MASTER_10BIT_RESTART:
            if (I2C1_ACKNOWLEDGE_STATUS_BIT) {
#if I2C1_ENABLE_ERROR_COUNT
                i2c1_object.i2cErrors++;
#endif
                i2c1_stop(I2C1_MESSAGE_ADDRESS_NO_ACK);
            } else {
                I2C1_REPEAT_START_CONDITION_ENABLE_BIT = 1;
                i2c_address = 0x00F0 | ((i2c_address >> 8) & 0x0006);
                i2c_address |= 0x0001;
                i2c_10bit_address_restart = 1;
                i2c1_state = S_MASTER_SEND_ADDR;
            }
            break;
#endif

        case S_MASTER_SEND_ADDR:
#if I2C1_ENABLE_10BIT
            if (i2c_10bit_address_restart != 1) {
                i2c_address    = p_i2c1_trb_current->address;
                pi2c_buf_ptr   = p_i2c1_trb_current->pbuffer;
                i2c_bytes_left = p_i2c1_trb_current->length;
            } else {
                i2c_10bit_address_restart = 0;
            }

            if (i2c_address > 0x00FF) {
                I2C1_TRANSMIT_REG = 0xF0 | ((i2c_address >> 8) & 0x0006);
                i2c1_state = S_MASTER_SEND_ADDR_10BIT_LSB;
            } else {
                I2C1_TRANSMIT_REG = i2c_address;
                if (i2c_address & 0x01) {
                    i2c1_state = S_MASTER_ACK_ADDR;
                } else {
                    i2c1_state = S_MASTER_SEND_DATA;
                }
            }
#else
            i2c_address    = p_i2c1_trb_current->address;
            pi2c_buf_ptr   = p_i2c1_trb_current->pbuffer;
            i2c_bytes_left = p_i2c1_trb_current->length;

            I2C1_TRANSMIT_REG = i2c_address;
            if (i2c_address & 0x01) {
                i2c1_state = S_MASTER_ACK_ADDR;
            } else {
                i2c1_state = S_MASTER_SEND_DATA;
            }
#endif
            break;

        case S_MASTER_SEND_DATA:
            if (I2C1_ACKNOWLEDGE_STATUS_BIT) {
#if I2C1_ENABLE_ERROR_COUNT
                i2c1_object.i2cErrors++;
#endif
                I2C1_ACKNOWLEDGE_STATUS_BIT = 0;
                i2c1_stop(I2C1_DATA_NO_ACK);
            } else {
                if (i2c_bytes_left-- == 0U) {
                    p_i2c1_trb_current++;
                    if (--i2c1_trb_count == 0) {
                        i2c1_stop(I2C1_MESSAGE_COMPLETE);
                    } else {
                        I2C1_REPEAT_START_CONDITION_ENABLE_BIT = 1;
                        i2c1_state = S_MASTER_SEND_ADDR;
                    }
                } else {
                    I2C1_TRANSMIT_REG = *pi2c_buf_ptr++;
                }
            }
            break;

        case S_MASTER_ACK_ADDR:
            if (I2C1_ACKNOWLEDGE_STATUS_BIT) {
#if I2C1_ENABLE_ERROR_COUNT
                i2c1_object.i2cErrors++;
#endif
                i2c1_stop(I2C1_MESSAGE_ADDRESS_NO_ACK);
                I2C1_ACKNOWLEDGE_STATUS_BIT = 0;
            } else {
                I2C1_RECEIVE_ENABLE_BIT = 1;
                i2c1_state = S_MASTER_ACK_RCV_DATA;
            }
            break;

        case S_MASTER_RCV_DATA:
            i2c1_state = S_MASTER_ACK_RCV_DATA;
            I2C1_RECEIVE_ENABLE_BIT = 1;
            break;

        case S_MASTER_ACK_RCV_DATA:
            *pi2c_buf_ptr++ = I2C1_RECEIVE_REG;
            if (--i2c_bytes_left) {
                I2C1_ACKNOWLEDGE_DATA_BIT = 0;
                i2c1_state = S_MASTER_RCV_DATA;
            } else {
                I2C1_ACKNOWLEDGE_DATA_BIT = 1;
                i2c1_function_complete();
            }
            I2C1_ACKNOWLEDGE_ENABLE_BIT = 1;
            break;

        case S_MASTER_RCV_STOP:
        case S_MASTER_SEND_STOP:
            i2c1_stop(I2C1_MESSAGE_COMPLETE);
            break;

        default:
#if I2C1_ENABLE_ERROR_COUNT
            i2c1_object.i2cErrors++;
#endif
            i2c1_stop(I2C1_LOST_STATE);
            break;
    }
}

static void i2c1_function_complete(void) {
    p_i2c1_trb_current++;
    if (--i2c1_trb_count == 0) {
        i2c1_state = S_MASTER_SEND_STOP;
    } else {
        i2c1_state = S_MASTER_RESTART;
    }
}

static void i2c1_stop(I2C1_MESSAGE_STATUS completion_code) {
    I2C1_STOP_CONDITION_ENABLE_BIT = 1;
    if (p_i2c1_current && p_i2c1_current->pTrFlag) {
        *(p_i2c1_current->pTrFlag) = completion_code;
    }
    i2c1_state = S_MASTER_IDLE;
}

static void i2c1_master_trb_insert(uint8_t count,
                                   I2C1_TRANSACTION_REQUEST_BLOCK *ptrb_list,
                                   I2C1_MESSAGE_STATUS *pflag) {
#if I2C1_ENABLE_QUEUE
    if (i2c1_object.trStatus.s.full != true) {
        *pflag = I2C1_MESSAGE_PENDING;

        i2c1_object.pTrTail->ptrb_list = ptrb_list;
        i2c1_object.pTrTail->count     = count;
        i2c1_object.pTrTail->pTrFlag   = pflag;
        i2c1_object.pTrTail++;

        if (i2c1_object.pTrTail == (i2c1_tr_queue + I2C1_CONFIG_TR_QUEUE_LENGTH)) {
            i2c1_object.pTrTail = i2c1_tr_queue;
        }

        i2c1_object.trStatus.s.empty = false;
        if (i2c1_object.pTrHead == i2c1_object.pTrTail) {
            i2c1_object.trStatus.s.full = true;
        }

        if (i2c1_state == S_MASTER_IDLE) {
            IFS1bits.MI2C1IF = 1;
        }
    } else {
        *pflag = I2C1_MESSAGE_FAIL;
    }
#else
    if (i2c1_object.trStatus.s.empty != true) {
        *pflag = I2C1_MESSAGE_FAIL;
        return;
    }

    *pflag = I2C1_MESSAGE_PENDING;
    i2c1_object.pTrHead->ptrb_list = ptrb_list;
    i2c1_object.pTrHead->count     = count;
    i2c1_object.pTrHead->pTrFlag   = pflag;
    i2c1_object.trStatus.s.empty = false;

    if (i2c1_state == S_MASTER_IDLE) {
        IFS1bits.MI2C1IF = 1;
    }
#endif
}

static void i2c1_master_read_trb_build(I2C1_TRANSACTION_REQUEST_BLOCK *ptrb,
                                       uint8_t *pdata,
                                       uint8_t length,
                                       uint16_t address) {
    ptrb->address = address << 1;
    ptrb->address |= 0x01;
    ptrb->length = length;
    ptrb->pbuffer = pdata;
}

static void i2c1_master_write_trb_build(I2C1_TRANSACTION_REQUEST_BLOCK *ptrb,
                                        uint8_t *pdata,
                                        uint8_t length,
                                        uint16_t address) {
    ptrb->address = address << 1;
    ptrb->length = length;
    ptrb->pbuffer = pdata;
}

static i2c_status_t i2c_wait_status(volatile I2C1_MESSAGE_STATUS *status) {
    uint32_t timeout = config.timeout_ms;
    while (*status == I2C1_MESSAGE_PENDING) {
        if (I2C1STATbits.BCL) {
            I2C1STATbits.BCL = 0;
            return I2C_COLLISION;
        }
        if (timeout == 0) return I2C_TIMEOUT;
        DELAY_milliseconds(1);
        timeout--;
    }

    switch (*status) {
        case I2C1_MESSAGE_COMPLETE:
            return I2C_OK;
        case I2C1_MESSAGE_ADDRESS_NO_ACK:
        case I2C1_DATA_NO_ACK:
            return I2C_NACK;
        case I2C1_STUCK_START:
        case I2C1_LOST_STATE:
            return I2C_COLLISION;
        case I2C1_MESSAGE_FAIL:
        default:
            return I2C_COLLISION;
    }
}

i2c_status_t i2c_writeReg(uint8_t addr, uint8_t reg, uint8_t val) {
    uint8_t payload[2] = { reg, val };
    I2C1_TRANSACTION_REQUEST_BLOCK trb;
    volatile I2C1_MESSAGE_STATUS status;

    i2c1_master_write_trb_build(&trb, payload, 2, addr);
    i2c1_master_trb_insert(1, &trb, (I2C1_MESSAGE_STATUS *)&status);
    return i2c_wait_status(&status);
}

i2c_status_t i2c_readRegs(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t len) {
    uint8_t reg_addr = reg;
    I2C1_TRANSACTION_REQUEST_BLOCK trb[2];
    volatile I2C1_MESSAGE_STATUS status;

    i2c1_master_write_trb_build(&trb[0], &reg_addr, 1, addr);
    i2c1_master_read_trb_build(&trb[1], data, len, addr);
    i2c1_master_trb_insert(2, trb, (I2C1_MESSAGE_STATUS *)&status);
    return i2c_wait_status(&status);
}

i2c_status_t i2c_readReg(uint8_t addr, uint8_t reg, uint8_t *val) {
    return i2c_readRegs(addr, reg, val, 1);
}
