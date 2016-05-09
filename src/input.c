#include "input.h"
#include "context.h"

static int mouse1;
static int mouse2;
static int mouse3;
static int mouse4;
static int mouse5;
static int mouse6;
static int mouse7;
static int mouse8;

static int keySpace;
static int keyApostrophe;
static int keyComma;
static int keyMinus;
static int keyPeriod;
static int keySlash;
static int key0;
static int key1;
static int key2;
static int key3;
static int key4;
static int key5;
static int key6;
static int key7;
static int key8;
static int key9;
static int keySemicolon;
static int keyEqual;
static int keyA;
static int keyB;
static int keyC;
static int keyD;
static int keyE;
static int keyF;
static int keyG;
static int keyH;
static int keyI;
static int keyJ;
static int keyK;
static int keyL;
static int keyM;
static int keyN;
static int keyO;
static int keyP;
static int keyQ;
static int keyR;
static int keyS;
static int keyT;
static int keyU;
static int keyV;
static int keyW;
static int keyX;
static int keyY;
static int keyZ;
static int keyLeftBracket;
static int keyBackslash;
static int keyRightBracket;
static int keyGraveAccent;
static int keyEscape;
static int keyEnter;
static int keyTab;
static int keyBackspace;
static int keyInsert;
static int keyDelete;
static int keyRight;
static int keyLeft;
static int keyDown;
static int keyUp;
static int keyPageUp;
static int keyPageDown;
static int keyHome;
static int keyEnd;
static int keyCapsLock;
static int keyScrollLock;
static int keyNumLock;
static int keyPrintScreen;
static int keyF1;
static int keyF2;
static int keyF3;
static int keyF4;
static int keyF5;
static int keyF6;
static int keyF7;
static int keyF8;
static int keyF9;
static int keyF10;
static int keyF11;
static int keyF12;
static int keyF13;
static int keyF14;
static int keyF15;
static int keyF16;
static int keyF17;
static int keyF18;
static int keyF19;
static int keyF20;
static int keyF21;
static int keyF22;
static int keyF23;
static int keyF24;
static int keyF25;
static int keyKP0;
static int keyKP1;
static int keyKP2;
static int keyKP3;
static int keyKP4;
static int keyKP5;
static int keyKP6;
static int keyKP7;
static int keyKP8;
static int keyKP9;
static int keyKPDecimal;
static int keyKPDivide;
static int keyKPMultiply;
static int keyKPSubtract;
static int keyKPAdd;
static int keyKPEnter;
static int keyKPEqual;
static int keyLeftShift;
static int keyLeftControl;
static int keyLeftAlt;
static int keyLeftSuper;
static int keyRightShift;
static int keyRightControl;
static int keyRightAlt;
static int keyRightSuper;
static int keyMenu;
static int keyUnknown;

static int joystick1;
static int joystick2;
static int joystick3;
static int joystick4;
static int joystick5;
static int joystick6;
static int joystick7;
static int joystick8;
static int joystick9;
static int joystick10;
static int joystick11;
static int joystick12;
static int joystick13;
static int joystick14;
static int joystick15;
static int joystick16;

static void inputKeyCallback(GLFWwindow*, int, int, int, int);
static void inputMouseCallback(GLFWwindow*, int, int, int);

void inputInit()
{
	glfwSetKeyCallback(contextWindow, inputKeyCallback);
	glfwSetMouseButtonCallback(contextWindow, inputMouseCallback);
}

int inputStatusMouse(int mouse)
{
	switch (mouse)
	{
		case MOUSE_1:
			return mouse1;

		case MOUSE_2:
			return mouse2;

		case MOUSE_3:
			return mouse3;

		case MOUSE_4:
			return mouse4;

		case MOUSE_5:
			return mouse5;

		case MOUSE_6:
			return mouse6;

		case MOUSE_7:
			return mouse7;
	}
	return -1;
}

int inputStatusKey(int key)
{
	switch (key)
	{
		case KEY_SPACE:
			return keySpace;
			 
		case KEY_APOSTROPHE:
			return keyApostrophe;
			 
		case KEY_COMMA:
			return keyComma;
			 
		case KEY_MINUS:
			return keyMinus;
			 
		case KEY_PERIOD:
			return keyPeriod;
			 
		case KEY_SLASH:
			return keySlash;
			 
		case KEY_0:
			return key0;
			 
		case KEY_1:
			return key1;
			 
		case KEY_2:
			return key2;
			 
		case KEY_3:
			return key3;
			 
		case KEY_4:
			return key4;
			 
		case KEY_5:
			return key5;
			 
		case KEY_6:
			return key6;
			 
		case KEY_7:
			return key7;
			 
		case KEY_8:
			return key8;
			 
		case KEY_9:
			return key9;
			 
		case KEY_SEMICOLON:
			return keySemicolon;
			 
		case KEY_EQUAL:
			return keyEqual;
			 
		case KEY_A:
			return keyA;
			 
		case KEY_B:
			return keyB;
			 
		case KEY_C:
			return keyC;
			 
		case KEY_D:
			return keyD;
			 
		case KEY_E:
			return keyE;
			 
		case KEY_F:
			return keyF;
			 
		case KEY_G:
			return keyG;
			 
		case KEY_H:
			return keyH;
			 
		case KEY_I:
			return keyI;
			 
		case KEY_J:
			return keyJ;
			 
		case KEY_K:
			return keyK;
			 
		case KEY_L:
			return keyL;
			 
		case KEY_M:
			return keyM;
			 
		case KEY_N:
			return keyN;
			 
		case KEY_O:
			return keyO;
			 
		case KEY_P:
			return keyP;
			 
		case KEY_Q:
			return keyQ;
			 
		case KEY_R:
			return keyR;
			 
		case KEY_S:
			return keyS;
			 
		case KEY_T:
			return keyT;
			 
		case KEY_U:
			return keyU;
			 
		case KEY_V:
			return keyV;
			 
		case KEY_W:
			return keyW;
			 
		case KEY_X:
			return keyX;
			 
		case KEY_Y:
			return keyY;
			 
		case KEY_Z:
			return keyZ;
			 
		case KEY_LEFT_BRACKET:
			return keyLeftBracket;
			 
		case KEY_BACKSLASH:
			return keyBackslash;
			 
		case KEY_RIGHT_BRACKET:
			return keyRightBracket;
			 
		case KEY_GRAVE_ACCENT :
			return keyGraveAccent;
			 
		case KEY_ESCAPE:
			return keyEscape;
			 
		case KEY_ENTER:
			return keyEnter;
			 
		case KEY_TAB:
			return keyTab;
			 
		case KEY_BACKSPACE:
			return keyBackspace;
			 
		case KEY_INSERT:
			return keyInsert;
			 
		case KEY_DELETE:
			return keyDelete;
			 
		case KEY_RIGHT:
			return keyRight;
			 
		case KEY_LEFT:
			return keyLeft;
			 
		case KEY_DOWN:
			return keyDown;
			 
		case KEY_UP:
			return keyUp;
			 
		case KEY_PAGE_UP:
			return keyPageUp;
			 
		case KEY_PAGE_DOWN:
			return keyPageDown;
			 
		case KEY_HOME:
			return keyHome;
			 
		case KEY_END:
			return keyEnd;
			 
		case KEY_CAPS_LOCK:
			return keyCapsLock;
			 
		case KEY_SCROLL_LOCK:
			return keyScrollLock;
			 
		case KEY_NUM_LOCK:
			return keyNumLock;
			 
		case KEY_PRINT_SCREEN:
			return keyPrintScreen;
			 
		case KEY_F1:
			return keyF1;
			 
		case KEY_F2:
			return keyF2;
			 
		case KEY_F3:
			return keyF3;
			 
		case KEY_F4:
			return keyF4;
			 
		case KEY_F5:
			return keyF5;
			 
		case KEY_F6:
			return keyF6;
			 
		case KEY_F7:
			return keyF7;
			 
		case KEY_F8:
			return keyF8;
			 
		case KEY_F9:
			return keyF9;
			 
		case KEY_F10:
			return keyF10;
			 
		case KEY_F11:
			return keyF11;
			 
		case KEY_F12:
			return keyF12;
			 
		case KEY_F13:
			return keyF13;
			 
		case KEY_F14:
			return keyF14;
			 
		case KEY_F15:
			return keyF15;
			 
		case KEY_F16:
			return keyF16;
			 
		case KEY_F17:
			return keyF17;
			 
		case KEY_F18:
			return keyF18;
			 
		case KEY_F19:
			return keyF19;
			 
		case KEY_F20:
			return keyF20;
			 
		case KEY_F21:
			return keyF21;
			 
		case KEY_F22:
			return keyF22;
			 
		case KEY_F23:
			return keyF23;
			 
		case KEY_F24:
			return keyF24;
			 
		case KEY_F25:
			return keyF25;
			 
		case KEY_KP_0:
			return keyKP0;
			 
		case KEY_KP_1:
			return keyKP1;
			 
		case KEY_KP_2:
			return keyKP2;
			 
		case KEY_KP_3:
			return keyKP3;
			 
		case KEY_KP_4:
			return keyKP4;
			 
		case KEY_KP_5:
			return keyKP5;
			 
		case KEY_KP_6:
			return keyKP6;
			 
		case KEY_KP_7:
			return keyKP7;
			 
		case KEY_KP_8:
			return keyKP8;
			 
		case KEY_KP_9:
			return keyKP9;
			 
		case KEY_KP_DECIMAL:
			return keyKPDecimal;
			 
		case KEY_KP_DIVIDE:
			return keyKPDivide;
			 
		case KEY_KP_MULTIPLY:
			return keyKPMultiply;
			 
		case KEY_KP_SUBTRACT:
			return keyKPSubtract;
			 
		case KEY_KP_ADD:
			return keyKPAdd;
			 
		case KEY_KP_ENTER:
			return keyKPEnter;
			 
		case KEY_KP_EQUAL:
			return keyKPEqual;
			 
		case KEY_LEFT_SHIFT:
			return keyLeftShift;
			 
		case KEY_LEFT_CONTROL:
			return keyLeftControl;
			 
		case KEY_LEFT_ALT:
			return keyLeftAlt;
			 
		case KEY_LEFT_SUPER:
			return keyLeftSuper;
			 
		case KEY_RIGHT_SHIFT:
			return keyRightShift;
			 
		case KEY_RIGHT_CONTROL:
			return keyRightControl;
			 
		case KEY_RIGHT_ALT:
			return keyRightAlt;
			 
		case KEY_RIGHT_SUPER:
			return keyRightSuper;
			 
		case KEY_MENU:
			return keyMenu;
			 
		case KEY_UNKNOWN:
			return keyUnknown;
	}
	return -1;
}

int inputStatusJoystick(int joystick)
{
	switch (joystick)
	{
		case JOYSTICK_1:
			return joystick1;

		case JOYSTICK_2:
			return joystick2;

		case JOYSTICK_3:
			return joystick3;

		case JOYSTICK_4:
			return joystick4;

		case JOYSTICK_5:
			return joystick5;

		case JOYSTICK_6:
			return joystick6;

		case JOYSTICK_7:
			return joystick7;

		case JOYSTICK_8:
			return joystick8;

		case JOYSTICK_9:
			return joystick9;

		case JOYSTICK_10:
			return joystick10;

		case JOYSTICK_11:
			return joystick11;

		case JOYSTICK_12:
			return joystick12;

		case JOYSTICK_13:
			return joystick13;

		case JOYSTICK_14:
			return joystick14;

		case JOYSTICK_15:
			return joystick15;

		case JOYSTICK_16:
			return joystick16;
	}
	return -1;
}

void inputMouseCallback(GLFWwindow* window, int mouse, int action, int mods)
{
	switch (mouse)
	{
		case MOUSE_1:
			mouse1 = action;
			break;

		case MOUSE_2:
			mouse2 = action;
			break;

		case MOUSE_3:
			mouse3 = action;
			break;

		case MOUSE_4:
			mouse4 = action;
			break;

		case MOUSE_5:
			mouse5 = action;
			break;

		case MOUSE_6:
			mouse6 = action;
			break;

		case MOUSE_7:
			mouse7 = action;
			break;

		case MOUSE_8:
			mouse8 = action;
			break;
	}
}

void inputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key)
	{
		case KEY_SPACE:
			keySpace = action;
			break;

		case KEY_APOSTROPHE:
			keyApostrophe = action;
			break;

		case KEY_COMMA:
			keyComma = action;
			break;

		case KEY_MINUS:
			keyMinus = action;
			break;

		case KEY_PERIOD:
			keyPeriod = action;
			break;

		case KEY_SLASH:
			keySlash = action;
			break;

		case KEY_0:
			key0 = action;
			break;

		case KEY_1:
			key1 = action;
			break;

		case KEY_2:
			key2 = action;
			break;

		case KEY_3:
			key3 = action;
			break;

		case KEY_4:
			key4 = action;
			break;

		case KEY_5:
			key5 = action;
			break;

		case KEY_6:
			key6 = action;
			break;

		case KEY_7:
			key7 = action;
			break;

		case KEY_8:
			key8 = action;
			break;

		case KEY_9:
			key9 = action;
			break;

		case KEY_SEMICOLON:
			keySemicolon = action;
			break;

		case KEY_EQUAL:
			keyEqual = action;
			break;

		case KEY_A:
			keyA = action;
			break;

		case KEY_B:
			keyB = action;
			break;

		case KEY_C:
			keyC = action;
			break;

		case KEY_D:
			keyD = action;
			break;

		case KEY_E:
			keyE = action;
			break;

		case KEY_F:
			keyF = action;
			break;

		case KEY_G:
			keyG = action;
			break;

		case KEY_H:
			keyH = action;
			break;

		case KEY_I:
			keyI = action;
			break;

		case KEY_J:
			keyJ = action;
			break;

		case KEY_K:
			keyK = action;
			break;

		case KEY_L:
			keyL = action;
			break;

		case KEY_M:
			keyM = action;
			break;

		case KEY_N:
			keyN = action;
			break;

		case KEY_O:
			keyO = action;
			break;

		case KEY_P:
			keyP = action;
			break;

		case KEY_Q:
			keyQ = action;
			break;

		case KEY_R:
			keyR = action;
			break;

		case KEY_S:
			keyS = action;
			break;

		case KEY_T:
			keyT = action;
			break;

		case KEY_U:
			keyU = action;
			break;

		case KEY_V:
			keyV = action;
			break;

		case KEY_W:
			keyW = action;
			break;

		case KEY_X:
			keyX = action;
			break;

		case KEY_Y:
			keyY = action;
			break;

		case KEY_Z:
			keyZ = action;
			break;

		case KEY_LEFT_BRACKET:
			keyLeftBracket = action;
			break;

		case KEY_BACKSLASH:
			keyBackslash = action;
			break;

		case KEY_RIGHT_BRACKET:
			keyRightBracket = action;
			break;

		case KEY_GRAVE_ACCENT :
			keyGraveAccent = action;
			break;

		case KEY_ESCAPE:
			keyEscape = action;
			break;

		case KEY_ENTER:
			keyEnter = action;
			break;

		case KEY_TAB:
			keyTab = action;
			break;

		case KEY_BACKSPACE:
			keyBackspace = action;
			break;

		case KEY_INSERT:
			keyInsert = action;
			break;

		case KEY_DELETE:
			keyDelete = action;
			break;

		case KEY_RIGHT:
			keyRight = action;
			break;

		case KEY_LEFT:
			keyLeft = action;
			break;

		case KEY_DOWN:
			keyDown = action;
			break;

		case KEY_UP:
			keyUp = action;
			break;

		case KEY_PAGE_UP:
			keyPageUp = action;
			break;

		case KEY_PAGE_DOWN:
			keyPageDown = action;
			break;

		case KEY_HOME:
			keyHome = action;
			break;

		case KEY_END:
			keyEnd = action;
			break;

		case KEY_CAPS_LOCK:
			keyCapsLock = action;
			break;

		case KEY_SCROLL_LOCK:
			keyScrollLock = action;
			break;

		case KEY_NUM_LOCK:
			keyNumLock = action;
			break;

		case KEY_PRINT_SCREEN:
			keyPrintScreen = action;
			break;

		case KEY_F1:
			keyF1 = action;
			break;

		case KEY_F2:
			keyF2 = action;
			break;

		case KEY_F3:
			keyF3 = action;
			break;

		case KEY_F4:
			keyF4 = action;
			break;

		case KEY_F5:
			keyF5 = action;
			break;

		case KEY_F6:
			keyF6 = action;
			break;

		case KEY_F7:
			keyF7 = action;
			break;

		case KEY_F8:
			keyF8 = action;
			break;

		case KEY_F9:
			keyF9 = action;
			break;

		case KEY_F10:
			keyF10 = action;
			break;

		case KEY_F11:
			keyF11 = action;
			break;

		case KEY_F12:
			keyF12 = action;
			break;

		case KEY_F13:
			keyF13 = action;
			break;

		case KEY_F14:
			keyF14 = action;
			break;

		case KEY_F15:
			keyF15 = action;
			break;

		case KEY_F16:
			keyF16 = action;
			break;

		case KEY_F17:
			keyF17 = action;
			break;

		case KEY_F18:
			keyF18 = action;
			break;

		case KEY_F19:
			keyF19 = action;
			break;

		case KEY_F20:
			keyF20 = action;
			break;

		case KEY_F21:
			keyF21 = action;
			break;

		case KEY_F22:
			keyF22 = action;
			break;

		case KEY_F23:
			keyF23 = action;
			break;

		case KEY_F24:
			keyF24 = action;
			break;

		case KEY_F25:
			keyF25 = action;
			break;

		case KEY_KP_0:
			keyKP0 = action;
			break;

		case KEY_KP_1:
			keyKP1 = action;
			break;

		case KEY_KP_2:
			keyKP2 = action;
			break;

		case KEY_KP_3:
			keyKP3 = action;
			break;

		case KEY_KP_4:
			keyKP4 = action;
			break;

		case KEY_KP_5:
			keyKP5 = action;
			break;

		case KEY_KP_6:
			keyKP6 = action;
			break;

		case KEY_KP_7:
			keyKP7 = action;
			break;

		case KEY_KP_8:
			keyKP8 = action;
			break;

		case KEY_KP_9:
			keyKP9 = action;
			break;

		case KEY_KP_DECIMAL:
			keyKPDecimal = action;
			break;

		case KEY_KP_DIVIDE:
			keyKPDivide = action;
			break;

		case KEY_KP_MULTIPLY:
			keyKPMultiply = action;
			break;

		case KEY_KP_SUBTRACT:
			keyKPSubtract = action;
			break;

		case KEY_KP_ADD:
			keyKPAdd = action;
			break;

		case KEY_KP_ENTER:
			keyKPEnter = action;
			break;

		case KEY_KP_EQUAL:
			keyKPEqual = action;
			break;

		case KEY_LEFT_SHIFT:
			keyLeftShift = action;
			break;

		case KEY_LEFT_CONTROL:
			keyLeftControl = action;
			break;

		case KEY_LEFT_ALT:
			keyLeftAlt = action;
			break;

		case KEY_LEFT_SUPER:
			keyLeftSuper = action;
			break;

		case KEY_RIGHT_SHIFT:
			keyRightShift = action;
			break;

		case KEY_RIGHT_CONTROL:
			keyRightControl = action;
			break;

		case KEY_RIGHT_ALT:
			keyRightAlt = action;
			break;

		case KEY_RIGHT_SUPER:
			keyRightSuper = action;
			break;

		case KEY_MENU:
			keyMenu = action;
			break;

		case KEY_UNKNOWN:
			keyUnknown = action;
			break;
	}
}