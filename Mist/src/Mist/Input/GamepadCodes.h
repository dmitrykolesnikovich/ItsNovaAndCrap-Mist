#pragma once

#ifdef MST_ENABLE_GAMEPAD
#ifdef MST_USE_GLFW_KEYCODES
// From glfw3.h
#define MST_JOYSTICK_1             0
#define MST_JOYSTICK_2             1
#define MST_JOYSTICK_3             2
#define MST_JOYSTICK_4             3
#define MST_JOYSTICK_5             4
#define MST_JOYSTICK_6             5
#define MST_JOYSTICK_7             6
#define MST_JOYSTICK_8             7
#define MST_JOYSTICK_9             8
#define MST_JOYSTICK_10            9
#define MST_JOYSTICK_11            10
#define MST_JOYSTICK_12            11
#define MST_JOYSTICK_13            12
#define MST_JOYSTICK_14            13
#define MST_JOYSTICK_15            14
#define MST_JOYSTICK_16            15
#define MST_JOYSTICK_LAST          MST_JOYSTICK_16

#define MST_GAMEPAD_BUTTON_A               0
#define MST_GAMEPAD_BUTTON_B               1
#define MST_GAMEPAD_BUTTON_X               2
#define MST_GAMEPAD_BUTTON_Y               3
#define MST_GAMEPAD_BUTTON_LEFT_BUMPER     4
#define MST_GAMEPAD_BUTTON_RIGHT_BUMPER    5
#define MST_GAMEPAD_BUTTON_BACK            6
#define MST_GAMEPAD_BUTTON_START           7
#define MST_GAMEPAD_BUTTON_GUIDE           8
#define MST_GAMEPAD_BUTTON_LEFT_THUMB      9
#define MST_GAMEPAD_BUTTON_RIGHT_THUMB     10
#define MST_GAMEPAD_BUTTON_DPAD_UP         11
#define MST_GAMEPAD_BUTTON_DPAD_RIGHT      12
#define MST_GAMEPAD_BUTTON_DPAD_DOWN       13
#define MST_GAMEPAD_BUTTON_DPAD_LEFT       14
#define MST_GAMEPAD_BUTTON_LAST            MST_GAMEPAD_BUTTON_DPAD_LEFT

#define MST_GAMEPAD_BUTTON_CROSS       MST_GAMEPAD_BUTTON_A
#define MST_GAMEPAD_BUTTON_CIRCLE      MST_GAMEPAD_BUTTON_B
#define MST_GAMEPAD_BUTTON_SQUARE      MST_GAMEPAD_BUTTON_X
#define MST_GAMEPAD_BUTTON_TRIANGLE    MST_GAMEPAD_BUTTON_Y

#define MST_GAMEPAD_AXIS_LEFT_X        0
#define MST_GAMEPAD_AXIS_LEFT_Y        1
#define MST_GAMEPAD_AXIS_RIGHT_X       2
#define MST_GAMEPAD_AXIS_RIGHT_Y       3
#define MST_GAMEPAD_AXIS_LEFT_TRIGGER  4
#define MST_GAMEPAD_AXIS_RIGHT_TRIGGER 5
#define MST_GAMEPAD_AXIS_LAST          MST_GAMEPAD_AXIS_RIGHT_TRIGGER
#endif
#endif