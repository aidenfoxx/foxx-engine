#include "input.h"

static void inputSetButtonState(int, int);
static void inputSetPosition(int, int);

static int keySpace = INPUT_RELEASE;
static int keyLeftShift = INPUT_RELEASE;
static int keyRightShift = INPUT_RELEASE;
static int keyLeftControl = INPUT_RELEASE;
static int keyRightControl = INPUT_RELEASE;
static int keyLeftAlt = INPUT_RELEASE;
static int keyRightAlt = INPUT_RELEASE;
static int keyLeftSuper = INPUT_RELEASE;
static int keyRightSuper = INPUT_RELEASE;
static int keyEscape = INPUT_RELEASE;
static int keyEnter = INPUT_RELEASE;
static int keyTab = INPUT_RELEASE;
static int keyBackspace = INPUT_RELEASE;
static int keyInsert = INPUT_RELEASE;
static int keyDelete = INPUT_RELEASE;
static int keyUp = INPUT_RELEASE;
static int keyDown = INPUT_RELEASE;
static int keyLeft = INPUT_RELEASE;
static int keyRight = INPUT_RELEASE;
static int keyPageUp = INPUT_RELEASE;
static int keyPageDown = INPUT_RELEASE;
static int keyHome = INPUT_RELEASE;
static int keyEnd = INPUT_RELEASE;
static int keyCapsLock = INPUT_RELEASE;
static int keyScrollLock = INPUT_RELEASE;
static int keyNumLock = INPUT_RELEASE;
static int keyPrintScreen = INPUT_RELEASE;
static int keyPause = INPUT_RELEASE;

static int keyApostrophe = INPUT_RELEASE; /* ' */
static int keyComma = INPUT_RELEASE; /* , */
static int keyMinus = INPUT_RELEASE; /* - */
static int keyPeriod = INPUT_RELEASE; /* . */
static int keySlash = INPUT_RELEASE; /* / */
static int keyBackslash = INPUT_RELEASE; /* \ */
static int keySemicolon = INPUT_RELEASE; /* ; */
static int keyEqual = INPUT_RELEASE; /* = */
static int keyLeftBracket = INPUT_RELEASE; /* [ */
static int keyRightBracket = INPUT_RELEASE; /* ] */
static int keyGraveAccent = INPUT_RELEASE; /* ` */

static int key0 = INPUT_RELEASE;
static int key1 = INPUT_RELEASE;
static int key2 = INPUT_RELEASE;
static int key3 = INPUT_RELEASE;
static int key4 = INPUT_RELEASE;
static int key5 = INPUT_RELEASE;
static int key6 = INPUT_RELEASE;
static int key7 = INPUT_RELEASE;
static int key8 = INPUT_RELEASE;
static int key9 = INPUT_RELEASE;

static int keyA = INPUT_RELEASE;
static int keyB = INPUT_RELEASE;
static int keyC = INPUT_RELEASE;
static int keyD = INPUT_RELEASE;
static int keyE = INPUT_RELEASE;
static int keyF = INPUT_RELEASE;
static int keyG = INPUT_RELEASE;
static int keyH = INPUT_RELEASE;
static int keyI = INPUT_RELEASE;
static int keyJ = INPUT_RELEASE;
static int keyK = INPUT_RELEASE;
static int keyL = INPUT_RELEASE;
static int keyM = INPUT_RELEASE;
static int keyN = INPUT_RELEASE;
static int keyO = INPUT_RELEASE;
static int keyP = INPUT_RELEASE;
static int keyQ = INPUT_RELEASE;
static int keyR = INPUT_RELEASE;
static int keyS = INPUT_RELEASE;
static int keyT = INPUT_RELEASE;
static int keyU = INPUT_RELEASE;
static int keyV = INPUT_RELEASE;
static int keyW = INPUT_RELEASE;
static int keyX = INPUT_RELEASE;
static int keyY = INPUT_RELEASE;
static int keyZ = INPUT_RELEASE;

static int keyF1 = INPUT_RELEASE;
static int keyF2 = INPUT_RELEASE;
static int keyF3 = INPUT_RELEASE;
static int keyF4 = INPUT_RELEASE;
static int keyF5 = INPUT_RELEASE;
static int keyF6 = INPUT_RELEASE;
static int keyF7 = INPUT_RELEASE;
static int keyF8 = INPUT_RELEASE;
static int keyF9 = INPUT_RELEASE;
static int keyF10 = INPUT_RELEASE;
static int keyF11 = INPUT_RELEASE;
static int keyF12 = INPUT_RELEASE;
static int keyF13 = INPUT_RELEASE;
static int keyF14 = INPUT_RELEASE;
static int keyF15 = INPUT_RELEASE;
static int keyF16 = INPUT_RELEASE;
static int keyF17 = INPUT_RELEASE;
static int keyF18 = INPUT_RELEASE;
static int keyF19 = INPUT_RELEASE;
static int keyF20 = INPUT_RELEASE;
static int keyF21 = INPUT_RELEASE;
static int keyF22 = INPUT_RELEASE;
static int keyF23 = INPUT_RELEASE;
static int keyF24 = INPUT_RELEASE;
static int keyF25 = INPUT_RELEASE;

static int keyNumDecimal = INPUT_RELEASE;
static int keyNumDivide = INPUT_RELEASE;
static int keyNumMultiply = INPUT_RELEASE;
static int keyNumSubtract = INPUT_RELEASE;
static int keyNumAdd = INPUT_RELEASE;
static int keyNumEnter = INPUT_RELEASE;
static int keyNumEqual = INPUT_RELEASE;

static int keyNum0 = INPUT_RELEASE;
static int keyNum1 = INPUT_RELEASE;
static int keyNum2 = INPUT_RELEASE;
static int keyNum3 = INPUT_RELEASE;
static int keyNum4 = INPUT_RELEASE;
static int keyNum5 = INPUT_RELEASE;
static int keyNum6 = INPUT_RELEASE;
static int keyNum7 = INPUT_RELEASE;
static int keyNum8 = INPUT_RELEASE;
static int keyNum9 = INPUT_RELEASE;

static int mouseLeft = INPUT_RELEASE;
static int mouseMiddle = INPUT_RELEASE;
static int mouseRight = INPUT_RELEASE;

static int mouseX = 0;
static int mouseY = 0;

void inputSetState(int input, int state, int value)
{
	switch (state)
	{
		case INPUT_RELEASE:
		case INPUT_PRESS:
			inputSetButtonState(input, state);

		case INPUT_MOVE:
			inputSetPosition(input, value);
	}
}

int inputGetState(int input)
{
	switch (input)
	{
		case INPUT_KEY_SPACE:
			return keySpace;
			break;

		case INPUT_KEY_LEFT_SHIFT:
			return keyLeftShift;
			break;

		case INPUT_KEY_RIGHT_SHIFT:
			return keyRightShift;
			break;

		case INPUT_KEY_LEFT_CONTROL:
			return keyLeftControl;
			break;

		case INPUT_KEY_RIGHT_CONTROL:
			return keyRightControl;
			break;

		case INPUT_KEY_LEFT_ALT:
			return keyLeftAlt;
			break;

		case INPUT_KEY_RIGHT_ALT:
			return keyRightAlt;
			break;

		case INPUT_KEY_LEFT_SUPER:
			return keyLeftSuper;
			break;

		case INPUT_KEY_RIGHT_SUPER:
			return keyRightSuper;
			break;

		case INPUT_KEY_ESCAPE:
			return keyEscape;
			break;

		case INPUT_KEY_ENTER:
			return keyEnter;
			break;

		case INPUT_KEY_TAB:
			return keyTab;
			break;

		case INPUT_KEY_BACKSPACE:
			return keyBackspace;
			break;

		case INPUT_KEY_INSERT:
			return keyInsert;
			break;

		case INPUT_KEY_DELETE:
			return keyDelete;
			break;

		case INPUT_KEY_UP:
			return keyUp;
			break;

		case INPUT_KEY_DOWN:
			return keyDown;
			break;

		case INPUT_KEY_LEFT:
			return keyLeft;
			break;

		case INPUT_KEY_RIGHT:
			return keyRight;
			break;

		case INPUT_KEY_PAGE_UP:
			return keyPageUp;
			break;

		case INPUT_KEY_PAGE_DOWN:
			return keyPageDown;
			break;

		case INPUT_KEY_HOME:
			return keyHome;
			break;

		case INPUT_KEY_END:
			return keyEnd;
			break;

		case INPUT_KEY_CAPS_LOCK:
			return keyCapsLock;
			break;

		case INPUT_KEY_SCROLL_LOCK:
			return keyScrollLock;
			break;

		case INPUT_KEY_NUM_LOCK:
			return keyNumLock;
			break;

		case INPUT_KEY_PRINT_SCREEN:
			return keyPrintScreen;
			break;

		case INPUT_KEY_PAUSE:
			return keyPause;
			break;

		case INPUT_KEY_APOSTROPHE:
			return keyApostrophe;
			break;

		case INPUT_KEY_COMMA:
			return keyComma;
			break;

		case INPUT_KEY_MINUS:
			return keyMinus;
			break;

		case INPUT_KEY_PERIOD:
			return keyPeriod;
			break;

		case INPUT_KEY_SLASH:
			return keySlash;
			break;

		case INPUT_KEY_BACKSLASH:
			return keyBackslash;
			break;

		case INPUT_KEY_SEMICOLON:
			return keySemicolon;
			break;

		case INPUT_KEY_EQUAL:
			return keyEqual;
			break;

		case INPUT_KEY_LEFT_BRACKET:
			return keyLeftBracket;
			break;

		case INPUT_KEY_RIGHT_BRACKET:
			return keyRightBracket;
			break;

		case INPUT_KEY_GRAVE_ACCENT:
			return keyGraveAccent;
			break;

		case INPUT_KEY_0:
			return key0;
			break;

		case INPUT_KEY_1:
			return key1;
			break;

		case INPUT_KEY_2:
			return key2;
			break;

		case INPUT_KEY_3:
			return key3;
			break;

		case INPUT_KEY_4:
			return key4;
			break;

		case INPUT_KEY_5:
			return key5;
			break;

		case INPUT_KEY_6:
			return key6;
			break;

		case INPUT_KEY_7:
			return key7;
			break;

		case INPUT_KEY_8:
			return key8;
			break;

		case INPUT_KEY_9:
			return key9;
			break;

		case INPUT_KEY_A:
			return keyA;
			break;

		case INPUT_KEY_B:
			return keyB;
			break;

		case INPUT_KEY_C:
			return keyC;
			break;

		case INPUT_KEY_D:
			return keyD;
			break;

		case INPUT_KEY_E:
			return keyE;
			break;

		case INPUT_KEY_F:
			return keyF;
			break;

		case INPUT_KEY_G:
			return keyG;
			break;

		case INPUT_KEY_H:
			return keyH;
			break;

		case INPUT_KEY_I:
			return keyI;
			break;

		case INPUT_KEY_J:
			return keyJ;
			break;

		case INPUT_KEY_K:
			return keyK;
			break;

		case INPUT_KEY_L:
			return keyL;
			break;

		case INPUT_KEY_M:
			return keyM;
			break;

		case INPUT_KEY_N:
			return keyN;
			break;

		case INPUT_KEY_O:
			return keyO;
			break;

		case INPUT_KEY_P:
			return keyP;
			break;

		case INPUT_KEY_Q:
			return keyQ;
			break;

		case INPUT_KEY_R:
			return keyR;
			break;

		case INPUT_KEY_S:
			return keyS;
			break;

		case INPUT_KEY_T:
			return keyT;
			break;

		case INPUT_KEY_U:
			return keyU;
			break;

		case INPUT_KEY_V:
			return keyV;
			break;

		case INPUT_KEY_W:
			return keyW;
			break;

		case INPUT_KEY_X:
			return keyX;
			break;

		case INPUT_KEY_Y:
			return keyY;
			break;

		case INPUT_KEY_Z:
			return keyZ;
			break;

		case INPUT_KEY_F1:
			return keyF1;
			break;

		case INPUT_KEY_F2:
			return keyF2;
			break;

		case INPUT_KEY_F3:
			return keyF3;
			break;

		case INPUT_KEY_F4:
			return keyF4;
			break;

		case INPUT_KEY_F5:
			return keyF5;
			break;

		case INPUT_KEY_F6:
			return keyF6;
			break;

		case INPUT_KEY_F7:
			return keyF7;
			break;

		case INPUT_KEY_F8:
			return keyF8;
			break;

		case INPUT_KEY_F9:
			return keyF9;
			break;

		case INPUT_KEY_F10:
			return keyF10;
			break;

		case INPUT_KEY_F11:
			return keyF11;
			break;

		case INPUT_KEY_F12:
			return keyF12;
			break;

		case INPUT_KEY_F13:
			return keyF13;
			break;

		case INPUT_KEY_F14:
			return keyF14;
			break;

		case INPUT_KEY_F15:
			return keyF15;
			break;

		case INPUT_KEY_F16:
			return keyF16;
			break;

		case INPUT_KEY_F17:
			return keyF17;
			break;

		case INPUT_KEY_F18:
			return keyF18;
			break;

		case INPUT_KEY_F19:
			return keyF19;
			break;

		case INPUT_KEY_F20:
			return keyF20;
			break;

		case INPUT_KEY_F21:
			return keyF21;
			break;

		case INPUT_KEY_F22:
			return keyF22;
			break;

		case INPUT_KEY_F23:
			return keyF23;
			break;

		case INPUT_KEY_F24:
			return keyF24;
			break;

		case INPUT_KEY_F25:
			return keyF25;
			break;

		case INPUT_KEY_NUM_DECIMAL:
			return keyNumDecimal;
			break;

		case INPUT_KEY_NUM_DIVIDE:
			return keyNumDivide;
			break;

		case INPUT_KEY_NUM_MULTIPLY:
			return keyNumMultiply;
			break;

		case INPUT_KEY_NUM_SUBTRACT:
			return keyNumSubtract;
			break;

		case INPUT_KEY_NUM_ADD:
			return keyNumAdd;
			break;

		case INPUT_KEY_NUM_ENTER:
			return keyNumEnter;
			break;

		case INPUT_KEY_NUM_EQUAL:
			return keyNumEqual;
			break;

		case INPUT_KEY_NUM_0:
			return keyNum0;
			break;

		case INPUT_KEY_NUM_1:
			return keyNum1;
			break;

		case INPUT_KEY_NUM_2:
			return keyNum2;
			break;

		case INPUT_KEY_NUM_3:
			return keyNum3;
			break;

		case INPUT_KEY_NUM_4:
			return keyNum4;
			break;

		case INPUT_KEY_NUM_5:
			return keyNum5;
			break;

		case INPUT_KEY_NUM_6:
			return keyNum6;
			break;

		case INPUT_KEY_NUM_7:
			return keyNum7;
			break;

		case INPUT_KEY_NUM_8:
			return keyNum8;
			break;

		case INPUT_KEY_NUM_9:
			return keyNum9;
			break;

		case INPUT_MOUSE_LEFT:
			return mouseLeft;
			break;

		case INPUT_MOUSE_MIDDLE:
			return mouseMiddle;
			break;

		case INPUT_MOUSE_RIGHT:
			return mouseRight;
			break;

		case INPUT_MOUSE_X:
			return mouseX;
			break;

		case INPUT_MOUSE_Y:
			return mouseY;
			break;
	}

	return INPUT_INVALID;
}

void inputSetButtonState(int button, int state)
{
	switch (button)
	{
		case INPUT_KEY_SPACE:
			keySpace = state;
			break;

		case INPUT_KEY_LEFT_SHIFT:
			keyLeftShift = state;
			break;

		case INPUT_KEY_RIGHT_SHIFT:
			keyRightShift = state;
			break;

		case INPUT_KEY_LEFT_CONTROL:
			keyLeftControl = state;
			break;

		case INPUT_KEY_RIGHT_CONTROL:
			keyRightControl = state;
			break;

		case INPUT_KEY_LEFT_ALT:
			keyLeftAlt = state;
			break;

		case INPUT_KEY_RIGHT_ALT:
			keyRightAlt = state;
			break;

		case INPUT_KEY_LEFT_SUPER:
			keyLeftSuper = state;
			break;

		case INPUT_KEY_RIGHT_SUPER:
			keyRightSuper = state;
			break;

		case INPUT_KEY_ESCAPE:
			keyEscape = state;
			break;

		case INPUT_KEY_ENTER:
			keyEnter = state;
			break;

		case INPUT_KEY_TAB:
			keyTab = state;
			break;

		case INPUT_KEY_BACKSPACE:
			keyBackspace = state;
			break;

		case INPUT_KEY_INSERT:
			keyInsert = state;
			break;

		case INPUT_KEY_DELETE:
			keyDelete = state;
			break;

		case INPUT_KEY_UP:
			keyUp = state;
			break;

		case INPUT_KEY_DOWN:
			keyDown = state;
			break;

		case INPUT_KEY_LEFT:
			keyLeft = state;
			break;

		case INPUT_KEY_RIGHT:
			keyRight = state;
			break;

		case INPUT_KEY_PAGE_UP:
			keyPageUp = state;
			break;

		case INPUT_KEY_PAGE_DOWN:
			keyPageDown = state;
			break;

		case INPUT_KEY_HOME:
			keyHome = state;
			break;

		case INPUT_KEY_END:
			keyEnd = state;
			break;

		case INPUT_KEY_CAPS_LOCK:
			keyCapsLock = state;
			break;

		case INPUT_KEY_SCROLL_LOCK:
			keyScrollLock = state;
			break;

		case INPUT_KEY_NUM_LOCK:
			keyNumLock = state;
			break;

		case INPUT_KEY_PRINT_SCREEN:
			keyPrintScreen = state;
			break;

		case INPUT_KEY_PAUSE:
			keyPause = state;
			break;

		case INPUT_KEY_APOSTROPHE:
			keyApostrophe = state;
			break;

		case INPUT_KEY_COMMA:
			keyComma = state;
			break;

		case INPUT_KEY_MINUS:
			keyMinus = state;
			break;

		case INPUT_KEY_PERIOD:
			keyPeriod = state;
			break;

		case INPUT_KEY_SLASH:
			keySlash = state;
			break;

		case INPUT_KEY_BACKSLASH:
			keyBackslash = state;
			break;

		case INPUT_KEY_SEMICOLON:
			keySemicolon = state;
			break;

		case INPUT_KEY_EQUAL:
			keyEqual = state;
			break;

		case INPUT_KEY_LEFT_BRACKET:
			keyLeftBracket = state;
			break;

		case INPUT_KEY_RIGHT_BRACKET:
			keyRightBracket = state;
			break;

		case INPUT_KEY_GRAVE_ACCENT:
			keyGraveAccent = state;
			break;

		case INPUT_KEY_0:
			key0 = state;
			break;

		case INPUT_KEY_1:
			key1 = state;
			break;

		case INPUT_KEY_2:
			key2 = state;
			break;

		case INPUT_KEY_3:
			key3 = state;
			break;

		case INPUT_KEY_4:
			key4 = state;
			break;

		case INPUT_KEY_5:
			key5 = state;
			break;

		case INPUT_KEY_6:
			key6 = state;
			break;

		case INPUT_KEY_7:
			key7 = state;
			break;

		case INPUT_KEY_8:
			key8 = state;
			break;

		case INPUT_KEY_9:
			key9 = state;
			break;

		case INPUT_KEY_A:
			keyA = state;
			break;

		case INPUT_KEY_B:
			keyB = state;
			break;

		case INPUT_KEY_C:
			keyC = state;
			break;

		case INPUT_KEY_D:
			keyD = state;
			break;

		case INPUT_KEY_E:
			keyE = state;
			break;

		case INPUT_KEY_F:
			keyF = state;
			break;

		case INPUT_KEY_G:
			keyG = state;
			break;

		case INPUT_KEY_H:
			keyH = state;
			break;

		case INPUT_KEY_I:
			keyI = state;
			break;

		case INPUT_KEY_J:
			keyJ = state;
			break;

		case INPUT_KEY_K:
			keyK = state;
			break;

		case INPUT_KEY_L:
			keyL = state;
			break;

		case INPUT_KEY_M:
			keyM = state;
			break;

		case INPUT_KEY_N:
			keyN = state;
			break;

		case INPUT_KEY_O:
			keyO = state;
			break;

		case INPUT_KEY_P:
			keyP = state;
			break;

		case INPUT_KEY_Q:
			keyQ = state;
			break;

		case INPUT_KEY_R:
			keyR = state;
			break;

		case INPUT_KEY_S:
			keyS = state;
			break;

		case INPUT_KEY_T:
			keyT = state;
			break;

		case INPUT_KEY_U:
			keyU = state;
			break;

		case INPUT_KEY_V:
			keyV = state;
			break;

		case INPUT_KEY_W:
			keyW = state;
			break;

		case INPUT_KEY_X:
			keyX = state;
			break;

		case INPUT_KEY_Y:
			keyY = state;
			break;

		case INPUT_KEY_Z:
			keyZ = state;
			break;

		case INPUT_KEY_F1:
			keyF1 = state;
			break;

		case INPUT_KEY_F2:
			keyF2 = state;
			break;

		case INPUT_KEY_F3:
			keyF3 = state;
			break;

		case INPUT_KEY_F4:
			keyF4 = state;
			break;

		case INPUT_KEY_F5:
			keyF5 = state;
			break;

		case INPUT_KEY_F6:
			keyF6 = state;
			break;

		case INPUT_KEY_F7:
			keyF7 = state;
			break;

		case INPUT_KEY_F8:
			keyF8 = state;
			break;

		case INPUT_KEY_F9:
			keyF9 = state;
			break;

		case INPUT_KEY_F10:
			keyF10 = state;
			break;

		case INPUT_KEY_F11:
			keyF11 = state;
			break;

		case INPUT_KEY_F12:
			keyF12 = state;
			break;

		case INPUT_KEY_F13:
			keyF13 = state;
			break;

		case INPUT_KEY_F14:
			keyF14 = state;
			break;

		case INPUT_KEY_F15:
			keyF15 = state;
			break;

		case INPUT_KEY_F16:
			keyF16 = state;
			break;

		case INPUT_KEY_F17:
			keyF17 = state;
			break;

		case INPUT_KEY_F18:
			keyF18 = state;
			break;

		case INPUT_KEY_F19:
			keyF19 = state;
			break;

		case INPUT_KEY_F20:
			keyF20 = state;
			break;

		case INPUT_KEY_F21:
			keyF21 = state;
			break;

		case INPUT_KEY_F22:
			keyF22 = state;
			break;

		case INPUT_KEY_F23:
			keyF23 = state;
			break;

		case INPUT_KEY_F24:
			keyF24 = state;
			break;

		case INPUT_KEY_F25:
			keyF25 = state;
			break;

		case INPUT_KEY_NUM_DECIMAL:
			keyNumDecimal = state;
			break;

		case INPUT_KEY_NUM_DIVIDE:
			keyNumDivide = state;
			break;

		case INPUT_KEY_NUM_MULTIPLY:
			keyNumMultiply = state;
			break;

		case INPUT_KEY_NUM_SUBTRACT:
			keyNumSubtract = state;
			break;

		case INPUT_KEY_NUM_ADD:
			keyNumAdd = state;
			break;

		case INPUT_KEY_NUM_ENTER:
			keyNumEnter = state;
			break;

		case INPUT_KEY_NUM_EQUAL:
			keyNumEqual = state;
			break;

		case INPUT_KEY_NUM_0:
			keyNum0 = state;
			break;

		case INPUT_KEY_NUM_1:
			keyNum1 = state;
			break;

		case INPUT_KEY_NUM_2:
			keyNum2 = state;
			break;

		case INPUT_KEY_NUM_3:
			keyNum3 = state;
			break;

		case INPUT_KEY_NUM_4:
			keyNum4 = state;
			break;

		case INPUT_KEY_NUM_5:
			keyNum5 = state;
			break;

		case INPUT_KEY_NUM_6:
			keyNum6 = state;
			break;

		case INPUT_KEY_NUM_7:
			keyNum7 = state;
			break;

		case INPUT_KEY_NUM_8:
			keyNum8 = state;
			break;

		case INPUT_KEY_NUM_9:
			keyNum9 = state;
			break;

		case INPUT_MOUSE_LEFT:
			mouseLeft = state;
			break;

		case INPUT_MOUSE_MIDDLE:
			mouseMiddle = state;
			break;

		case INPUT_MOUSE_RIGHT:
			mouseRight = state;
			break;
	}
}

static void inputSetPosition(int input, int value)
{
	switch (input)
	{
		case INPUT_MOUSE_X:
			mouseX = value;
			break;

		case INPUT_MOUSE_Y:
			mouseY = value;
	}
}