# Watch Project - Integration Guide

## 📦 What You Have

A complete, modular watch application for your PIC24FJ256GA705 Curiosity Board with:

### ✅ Features Implemented
- ✓ Digital watch face (large numbers, 12/24hr)
- ✓ Analog watch face (clock hands with hour markers)
- ✓ **Binary counter watch face** (aesthetically pleasing BCD display)
- ✓ **Pomodoro timer** (25/5/15 min intervals with visual feedback)
- ✓ Complete menu system with potentiometer scrolling
- ✓ Alarm with screen flashing (20s auto-dismiss)
- ✓ Accelerometer integration (flip/shake to exit menus)
- ✓ Date tracking (28-day February)
- ✓ 1-second ISR-based timing (Timer2 with compare)
- ✓ LED feedback on button presses
- ✓ Jitter-free potentiometer with hysteresis
- ✓ Modular, clean architecture
- ✓ Professional color palette
- ✓ **Hebrew user manual** (required for submission!)

---

## 📁 File Structure

```
watch_project/
├── shared/                  # Shared types and state
│   ├── watch_types.h
│   ├── watch_state.h
│   └── watch_state.c
│
├── watchCore/              # Core timing and alarm
│   ├── watch_timer.h
│   ├── watch_timer.c
│   ├── timekeeper.h
│   ├── timekeeper.c
│   ├── alarm.h
│   └── alarm.c
│
├── watchFaces/             # All watch displays
│   ├── digital_face.h
│   ├── digital_face.c
│   ├── analog_face.h
│   ├── analog_face.c
│   ├── binary_face.h       # Your custom binary face
│   └── binary_face.c
│
├── watchMenu/              # Menu system
│   ├── menu.h
│   └── menu.c
│
├── watchInput/             # Input handling
│   ├── buttons.h
│   ├── buttons.c
│   ├── potentiometer.h
│   ├── potentiometer.c
│   ├── accel_input.h
│   └── accel_input.c
│
├── pomodoroTimer/          # Your Pomodoro timer
│   ├── pomodoro.h
│   └── pomodoro.c
│
├── watch_main.c            # Main application
├── USER_MANUAL_HE.md       # Hebrew user manual (REQUIRED!)
└── README.md               # Technical documentation
```

---

## 🚀 Integration Steps

### Step 1: Add Files to MPLAB X Project

1. **Open your CuriosityOledBase.X project** in MPLAB X
2. **Right-click on "Source Files"** → Add Existing Items from Folders
3. **Navigate to `watch_project/`** and add all `.c` files:
   ```
   watch_main.c
   shared/watch_state.c
   watchCore/watch_timer.c
   watchCore/timekeeper.c
   watchCore/alarm.c
   watchFaces/digital_face.c
   watchFaces/analog_face.c
   watchFaces/binary_face.c
   watchMenu/menu.c
   watchInput/buttons.c
   watchInput/potentiometer.c
   watchInput/accel_input.c
   pomodoroTimer/pomodoro.c
   ```

4. **Right-click on "Header Files"** → Add Existing Items from Folders
5. **Add all `.h` files** from the same directories

### Step 2: Update Include Paths

1. Right-click project → Properties
2. XC16 (Global Options) → xc16-gcc → Preprocessing and messages
3. Add to Include directories:
   ```
   ${ProjectDir}/watch_project
   ${ProjectDir}/watch_project/shared
   ${ProjectDir}/watch_project/watchCore
   ${ProjectDir}/watch_project/watchFaces
   ${ProjectDir}/watch_project/watchMenu
   ${ProjectDir}/watch_project/watchInput
   ${ProjectDir}/watch_project/pomodoroTimer
   ```

### Step 3: Replace Main Files

**Option A: Clean Integration (Recommended)**
1. Rename your current `main.c` to `main_old.c`
2. Rename your current `app.c` to `app_old.c`
3. Set `watch_main.c` as the active main file

**Option B: Integrate with Existing Code**
1. Keep your initialization code from `app_setup()`
2. Replace the main loop with the watch application loop
3. Use the existing `systemExtensions.c` or replace with `watch_timer.c`

### Step 4: Build and Test

1. **Clean Build**: Project → Clean and Build
2. **Check for errors** - should compile cleanly
3. **Program device**: Run → Program Device
4. **Test functionality**:
   - Watch displays should show time
   - S2 should cycle through faces
   - Long press S1 should enter menu
   - Flip board to exit menu

---

## 🎨 Color Palette (Already Defined)

```c
#define COLOR_BG        0x0000  // Black background
#define COLOR_PRIMARY   0x07FF  // Cyan (main content)
#define COLOR_SECONDARY 0xFD20  // Orange (interactive)
#define COLOR_ACCENT    0xF81F  // Magenta (highlights)
#define COLOR_WARNING   0xF800  // Red (alarms)
#define COLOR_SUCCESS   0x07E0  // Green (confirm)
#define COLOR_DIM       0x8410  // Gray (secondary)
```

---

## 🎯 Quick Start Guide

### Basic Usage

**Watch Mode:**
- Press S2 → Cycle through watch faces (Digital → Analog → Binary)
- Long press S1 (>2s) → Enter menu

**Menu Mode:**
- Press S1 → Navigate down (cyclic)
- Press S2 → Select/Enter
- Turn potentiometer → Adjust values
- Flip board OR shake 3× → Exit menu

**Setting Time:**
1. Long press S1
2. Select "Set Time"
3. S1 to change field, Pot to adjust
4. S2 to confirm

**Setting Alarm:**
1. Long press S1
2. Select "Set Alarm"
3. Configure time
4. Auto-enables on save

**Pomodoro:**
1. Long press S1
2. Select "Pomodoro"
3. S2 to start/pause
4. S1 to reset
5. Long press S1 to exit

---

## 🐛 Troubleshooting

### Compilation Errors

**Problem**: Cannot find header files
- **Fix**: Check include paths in project properties
- Verify all files are in correct directories

**Problem**: Undefined references
- **Fix**: Ensure all `.c` files are added to project
- Check that function prototypes match implementations

**Problem**: Multiple definition of 'main'
- **Fix**: Remove or rename old `main.c` and `app.c`

### Runtime Issues

**Problem**: Timer not working
- **Fix**: Verify Timer2 initialization in `watch_timer.c`
- Check that ISR vector is correct: `_T2Interrupt`

**Problem**: OLED not updating
- **Fix**: Ensure `oledC_setup()` is called in initialization
- Verify SPI pins are configured correctly

**Problem**: Buttons not responding
- **Fix**: Check LED feedback - if LEDs work, code is running
- Verify TRISA register configuration for S1/S2

**Problem**: Potentiometer jumping
- **Fix**: Increase `HYSTERESIS_THRESHOLD` in `potentiometer.c`
- Default is 30, try 40-50 for more stability

---

## 📋 Before Submission Checklist

### Required Items:
- [ ] **Compiled project** - must compile successfully!
- [ ] **ZIP/RAR archive** containing entire MPLAB X project
- [ ] **Hebrew user manual** (`USER_MANUAL_HE.md`) - CRITICAL!
- [ ] **All source files** included
- [ ] **Project builds without errors**
- [ ] **Basic functionality tested** on hardware

### Code Quality:
- [ ] Meaningful variable and function names ✓
- [ ] Clean indentation and formatting ✓
- [ ] Modular file organization ✓
- [ ] No code duplication ✓
- [ ] Comments explaining complex logic ✓

### Functionality:
- [ ] Multiple watch faces working
- [ ] Menu system functional
- [ ] Time can be set and advances correctly
- [ ] Alarm rings and auto-dismisses
- [ ] Accelerometer exits menu
- [ ] Pomodoro timer works
- [ ] LED feedback on button presses

---

## 🎓 Submission Package

Create a ZIP file containing:
```
YourName_Watch_Project.zip
├── CuriosityOledBase.X/          # Your MPLAB X project
│   ├── watch_project/            # All watch modules
│   ├── oledDriver/               # Existing drivers
│   ├── System/                   # System files
│   └── ... (all other files)
│
└── USER_MANUAL_HE.md             # Hebrew manual (copy to root!)
```

---

## 💡 Tips for Success

1. **Test incrementally**: Add one module at a time
2. **Use the simulator**: Test logic before hardware
3. **Check LED feedback**: Quick way to verify button inputs
4. **Start simple**: Get basic digital display working first
5. **Read the manual**: The Hebrew manual explains all features
6. **Ask for help**: If compilation fails, check error messages carefully

---

## 🌟 Bonus Features Implemented

1. **Binary Watch Face** (+10 points potential)
   - Aesthetically pleasing BCD display
   - Color-coded for clarity
   - Unique visual design

2. **Pomodoro Timer** (Extra feature)
   - Full productivity timer
   - Auto-transitions
   - Visual progress bar

3. **Advanced Input Handling**
   - Jitter-free potentiometer
   - Accelerometer integration
   - Debounced buttons

4. **Professional Architecture**
   - Modular design
   - Clean separation of concerns
   - Minimal memory usage

---

## 📞 Support

If you encounter issues:
1. Check README.md for detailed technical documentation
2. Review USER_MANUAL_HE.md for usage instructions
3. Verify all files are included in project
4. Ensure hardware connections are correct
5. Contact your course instructor/TA

---

## ✅ Success Criteria

Your project should:
- ✓ **Compile successfully** (zero grade if not!)
- ✓ **Include user manual** (zero grade if missing!)
- ✓ Show multiple watch faces
- ✓ Have functional menu system
- ✓ Keep accurate time
- ✓ Ring alarm at set time
- ✓ Exit menu via accelerometer
- ✓ Display date and alarm status

---

## 🎉 You're Ready!

You now have a complete, professional-grade watch application that:
- Meets ALL assignment requirements
- Includes bonus features (binary face, Pomodoro)
- Has clean, modular architecture
- Includes required Hebrew documentation
- Follows best embedded systems practices

**Good luck with your final project! 🚀**

---

*If you have any questions about the implementation, refer to the extensive comments in the code and the technical README.md*
