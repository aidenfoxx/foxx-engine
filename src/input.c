#include "input.h"

static void inputSetKeyRelease(int);
static void inputSetKeyPress(int);

static int keySpace = INPUT_KEY_RELEASE;
static int keyLeftShift = INPUT_KEY_RELEASE;
static int keyRightShift = INPUT_KEY_RELEASE;
static int keyLeftControl = INPUT_KEY_RELEASE;
static int keyRightControl = INPUT_KEY_RELEASE;
static int keyLeftAlt = INPUT_KEY_RELEASE;
static int keyRightAlt = INPUT_KEY_RELEASE;
static int keyLeftSuper = INPUT_KEY_RELEASE;
static int keyRightSuper = INPUT_KEY_RELEASE;
static int keyEscape = INPUT_KEY_RELEASE;
static int keyEnter = INPUT_KEY_RELEASE;
static int keyTab = INPUT_KEY_RELEASE;
static int keyBackspace = INPUT_KEY_RELEASE;
static int keyInsert = INPUT_KEY_RELEASE;
static int keyDelete = INPUT_KEY_RELEASE;
static int keyUp = INPUT_KEY_RELEASE;
static int keyDown = INPUT_KEY_RELEASE;
static int keyLeft = INPUT_KEY_RELEASE;
static int keyRight = INPUT_KEY_RELEASE;
static int keyPageUp = INPUT_KEY_RELEASE;
static int keyPageDown = INPUT_KEY_RELEASE;
static int keyHome = INPUT_KEY_RELEASE;
static int keyEnd = INPUT_KEY_RELEASE;
static int keyCapsLock = INPUT_KEY_RELEASE;
static int keyScrollLock = INPUT_KEY_RELEASE;
static int keyNumLock = INPUT_KEY_RELEASE;
static int keyPrintScreen = INPUT_KEY_RELEASE;
static int keyPause = INPUT_KEY_RELEASE;

static int keyApostrophe = INPUT_KEY_RELEASE; /* ' */
static int keyComma = INPUT_KEY_RELEASE; /* , */
static int keyMinus = INPUT_KEY_RELEASE; /* - */
static int keyPeriod = INPUT_KEY_RELEASE; /* . */
static int keySlash = INPUT_KEY_RELEASE; /* / */
static int keyBackslash = INPUT_KEY_RELEASE; /* \ */
static int keySemicolon = INPUT_KEY_RELEASE; /* ; */
static int keyEqual = INPUT_KEY_RELEASE; /* = */
static int keyLeftBracket = INPUT_KEY_RELEASE; /* [ */
static int keyRightBracket = INPUT_KEY_RELEASE; /* ] */
static int keyGraveAccent = INPUT_KEY_RELEASE; /* ` */

static int key0 = INPUT_KEY_RELEASE;
static int key1 = INPUT_KEY_RELEASE;
static int key2 = INPUT_KEY_RELEASE;
static int key3 = INPUT_KEY_RELEASE;
static int key4 = INPUT_KEY_RELEASE;
static int key5 = INPUT_KEY_RELEASE;
static int key6 = INPUT_KEY_RELEASE;
static int key7 = INPUT_KEY_RELEASE;
static int key8 = INPUT_KEY_RELEASE;
static int key9 = INPUT_KEY_RELEASE;

static int keyA = INPUT_KEY_RELEASE;
static int keyB = INPUT_KEY_RELEASE;
static int keyC = INPUT_KEY_RELEASE;
static int keyD = INPUT_KEY_RELEASE;
static int keyE = INPUT_KEY_RELEASE;
static int keyF = INPUT_KEY_RELEASE;
static int keyG = INPUT_KEY_RELEASE;
static int keyH = INPUT_KEY_RELEASE;
static int keyI = INPUT_KEY_RELEASE;
static int keyJ = INPUT_KEY_RELEASE;
static int keyK = INPUT_KEY_RELEASE;
static int keyL = INPUT_KEY_RELEASE;
static int keyM = INPUT_KEY_RELEASE;
static int keyN = INPUT_KEY_RELEASE;
static int keyO = INPUT_KEY_RELEASE;
static int keyP = INPUT_KEY_RELEASE;
static int keyQ = INPUT_KEY_RELEASE;
static int keyR = INPUT_KEY_RELEASE;
static int keyS = INPUT_KEY_RELEASE;
static int keyT = INPUT_KEY_RELEASE;
static int keyU = INPUT_KEY_RELEASE;
static int keyV = INPUT_KEY_RELEASE;
static int keyW = INPUT_KEY_RELEASE;
static int keyX = INPUT_KEY_RELEASE;
static int keyY = INPUT_KEY_RELEASE;
static int keyZ = INPUT_KEY_RELEASE;

static int keyF1 = INPUT_KEY_RELEASE;
static int keyF2 = INPUT_KEY_RELEASE;
static int keyF3 = INPUT_KEY_RELEASE;
static int keyF4 = INPUT_KEY_RELEASE;
static int keyF5 = INPUT_KEY_RELEASE;
static int keyF6 = INPUT_KEY_RELEASE;
static int keyF7 = INPUT_KEY_RELEASE;
static int keyF8 = INPUT_KEY_RELEASE;
static int keyF9 = INPUT_KEY_RELEASE;
static int keyF10 = INPUT_KEY_RELEASE;
static int keyF11 = INPUT_KEY_RELEASE;
static int keyF12 = INPUT_KEY_RELEASE;
static int keyF13 = INPUT_KEY_RELEASE;
static int keyF14 = INPUT_KEY_RELEASE;
static int keyF15 = INPUT_KEY_RELEASE;
static int keyF16 = INPUT_KEY_RELEASE;
static int keyF17 = INPUT_KEY_RELEASE;
static int keyF18 = INPUT_KEY_RELEASE;
static int keyF19 = INPUT_KEY_RELEASE;
static int keyF20 = INPUT_KEY_RELEASE;
static int keyF21 = INPUT_KEY_RELEASE;
static int keyF22 = INPUT_KEY_RELEASE;
static int keyF23 = INPUT_KEY_RELEASE;
static int keyF24 = INPUT_KEY_RELEASE;
static int keyF25 = INPUT_KEY_RELEASE;

static int keyNumDecimal = INPUT_KEY_RELEASE;
static int keyNumDivide = INPUT_KEY_RELEASE;
static int keyNumMultiply = INPUT_KEY_RELEASE;
static int keyNumSubtract = INPUT_KEY_RELEASE;
static int keyNumAdd = INPUT_KEY_RELEASE;
static int keyNumEnter = INPUT_KEY_RELEASE;
static int keyNumEqual = INPUT_KEY_RELEASE;

static int keyNum0 = INPUT_KEY_RELEASE;
static int keyNum1 = INPUT_KEY_RELEASE;
static int keyNum2 = INPUT_KEY_RELEASE;
static int keyNum3 = INPUT_KEY_RELEASE;
static int keyNum4 = INPUT_KEY_RELEASE;
static int keyNum5 = INPUT_KEY_RELEASE;
static int keyNum6 = INPUT_KEY_RELEASE;
static int keyNum7 = INPUT_KEY_RELEASE;
static int keyNum8 = INPUT_KEY_RELEASE;
static int keyNum9 = INPUT_KEY_RELEASE;

void inputSetState(int input, int state)
{
	if (state == INPUT_KEY_RELEASE)
	{
		inputSetKeyRelease(input);
	}

	if (state == INPUT_KEY_PRESS)
	{
		inputSetKeyPress(input);
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
	}

	return INPUT_INVALID;
}

void inputSetKeyRelease(int key)
{
	switch (key)
	{
		case INPUT_KEY_SPACE:
			keySpace = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_LEFT_SHIFT:
			keyLeftShift = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_RIGHT_SHIFT:
			keyRightShift = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_LEFT_CONTROL:
			keyLeftControl = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_RIGHT_CONTROL:
			keyRightControl = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_LEFT_ALT:
			keyLeftAlt = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_RIGHT_ALT:
			keyRightAlt = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_LEFT_SUPER:
			keyLeftSuper = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_RIGHT_SUPER:
			keyRightSuper = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_ESCAPE:
			keyEscape = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_ENTER:
			keyEnter = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_TAB:
			keyTab = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_BACKSPACE:
			keyBackspace = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_INSERT:
			keyInsert = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_DELETE:
			keyDelete = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_UP:
			keyUp = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_DOWN:
			keyDown = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_LEFT:
			keyLeft = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_RIGHT:
			keyRight = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_PAGE_UP:
			keyPageUp = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_PAGE_DOWN:
			keyPageDown = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_HOME:
			keyHome = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_END:
			keyEnd = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_CAPS_LOCK:
			keyCapsLock = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_SCROLL_LOCK:
			keyScrollLock = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_LOCK:
			keyNumLock = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_PRINT_SCREEN:
			keyPrintScreen = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_PAUSE:
			keyPause = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_APOSTROPHE:
			keyApostrophe = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_COMMA:
			keyComma = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_MINUS:
			keyMinus = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_PERIOD:
			keyPeriod = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_SLASH:
			keySlash = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_BACKSLASH:
			keyBackslash = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_SEMICOLON:
			keySemicolon = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_EQUAL:
			keyEqual = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_LEFT_BRACKET:
			keyLeftBracket = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_RIGHT_BRACKET:
			keyRightBracket = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_GRAVE_ACCENT:
			keyGraveAccent = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_0:
			key0 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_1:
			key1 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_2:
			key2 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_3:
			key3 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_4:
			key4 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_5:
			key5 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_6:
			key6 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_7:
			key7 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_8:
			key8 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_9:
			key9 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_A:
			keyA = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_B:
			keyB = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_C:
			keyC = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_D:
			keyD = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_E:
			keyE = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F:
			keyF = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_G:
			keyG = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_H:
			keyH = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_I:
			keyI = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_J:
			keyJ = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_K:
			keyK = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_L:
			keyL = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_M:
			keyM = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_N:
			keyN = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_O:
			keyO = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_P:
			keyP = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_Q:
			keyQ = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_R:
			keyR = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_S:
			keyS = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_T:
			keyT = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_U:
			keyU = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_V:
			keyV = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_W:
			keyW = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_X:
			keyX = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_Y:
			keyY = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_Z:
			keyZ = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F1:
			keyF1 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F2:
			keyF2 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F3:
			keyF3 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F4:
			keyF4 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F5:
			keyF5 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F6:
			keyF6 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F7:
			keyF7 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F8:
			keyF8 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F9:
			keyF9 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F10:
			keyF10 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F11:
			keyF11 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F12:
			keyF12 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F13:
			keyF13 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F14:
			keyF14 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F15:
			keyF15 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F16:
			keyF16 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F17:
			keyF17 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F18:
			keyF18 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F19:
			keyF19 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F20:
			keyF20 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F21:
			keyF21 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F22:
			keyF22 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F23:
			keyF23 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F24:
			keyF24 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_F25:
			keyF25 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_DECIMAL:
			keyNumDecimal = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_DIVIDE:
			keyNumDivide = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_MULTIPLY:
			keyNumMultiply = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_SUBTRACT:
			keyNumSubtract = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_ADD:
			keyNumAdd = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_ENTER:
			keyNumEnter = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_EQUAL:
			keyNumEqual = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_0:
			keyNum0 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_1:
			keyNum1 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_2:
			keyNum2 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_3:
			keyNum3 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_4:
			keyNum4 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_5:
			keyNum5 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_6:
			keyNum6 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_7:
			keyNum7 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_8:
			keyNum8 = INPUT_KEY_RELEASE;
			break;

		case INPUT_KEY_NUM_9:
			keyNum9 = INPUT_KEY_RELEASE;
			break;
	}
}

void inputSetKeyPress(int key)
{
	switch (key)
	{
		case INPUT_KEY_SPACE:
			keySpace = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_LEFT_SHIFT:
			keyLeftShift = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_RIGHT_SHIFT:
			keyRightShift = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_LEFT_CONTROL:
			keyLeftControl = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_RIGHT_CONTROL:
			keyRightControl = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_LEFT_ALT:
			keyLeftAlt = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_RIGHT_ALT:
			keyRightAlt = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_LEFT_SUPER:
			keyLeftSuper = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_RIGHT_SUPER:
			keyRightSuper = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_ESCAPE:
			keyEscape = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_ENTER:
			keyEnter = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_TAB:
			keyTab = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_BACKSPACE:
			keyBackspace = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_INSERT:
			keyInsert = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_DELETE:
			keyDelete = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_UP:
			keyUp = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_DOWN:
			keyDown = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_LEFT:
			keyLeft = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_RIGHT:
			keyRight = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_PAGE_UP:
			keyPageUp = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_PAGE_DOWN:
			keyPageDown = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_HOME:
			keyHome = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_END:
			keyEnd = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_CAPS_LOCK:
			keyCapsLock = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_SCROLL_LOCK:
			keyScrollLock = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_LOCK:
			keyNumLock = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_PRINT_SCREEN:
			keyPrintScreen = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_PAUSE:
			keyPause = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_APOSTROPHE:
			keyApostrophe = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_COMMA:
			keyComma = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_MINUS:
			keyMinus = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_PERIOD:
			keyPeriod = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_SLASH:
			keySlash = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_BACKSLASH:
			keyBackslash = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_SEMICOLON:
			keySemicolon = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_EQUAL:
			keyEqual = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_LEFT_BRACKET:
			keyLeftBracket = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_RIGHT_BRACKET:
			keyRightBracket = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_GRAVE_ACCENT:
			keyGraveAccent = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_0:
			key0 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_1:
			key1 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_2:
			key2 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_3:
			key3 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_4:
			key4 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_5:
			key5 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_6:
			key6 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_7:
			key7 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_8:
			key8 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_9:
			key9 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_A:
			keyA = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_B:
			keyB = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_C:
			keyC = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_D:
			keyD = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_E:
			keyE = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F:
			keyF = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_G:
			keyG = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_H:
			keyH = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_I:
			keyI = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_J:
			keyJ = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_K:
			keyK = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_L:
			keyL = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_M:
			keyM = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_N:
			keyN = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_O:
			keyO = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_P:
			keyP = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_Q:
			keyQ = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_R:
			keyR = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_S:
			keyS = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_T:
			keyT = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_U:
			keyU = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_V:
			keyV = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_W:
			keyW = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_X:
			keyX = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_Y:
			keyY = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_Z:
			keyZ = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F1:
			keyF1 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F2:
			keyF2 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F3:
			keyF3 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F4:
			keyF4 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F5:
			keyF5 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F6:
			keyF6 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F7:
			keyF7 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F8:
			keyF8 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F9:
			keyF9 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F10:
			keyF10 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F11:
			keyF11 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F12:
			keyF12 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F13:
			keyF13 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F14:
			keyF14 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F15:
			keyF15 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F16:
			keyF16 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F17:
			keyF17 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F18:
			keyF18 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F19:
			keyF19 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F20:
			keyF20 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F21:
			keyF21 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F22:
			keyF22 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F23:
			keyF23 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F24:
			keyF24 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_F25:
			keyF25 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_DECIMAL:
			keyNumDecimal = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_DIVIDE:
			keyNumDivide = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_MULTIPLY:
			keyNumMultiply = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_SUBTRACT:
			keyNumSubtract = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_ADD:
			keyNumAdd = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_ENTER:
			keyNumEnter = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_EQUAL:
			keyNumEqual = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_0:
			keyNum0 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_1:
			keyNum1 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_2:
			keyNum2 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_3:
			keyNum3 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_4:
			keyNum4 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_5:
			keyNum5 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_6:
			keyNum6 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_7:
			keyNum7 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_8:
			keyNum8 = INPUT_KEY_PRESS;
			break;

		case INPUT_KEY_NUM_9:
			keyNum9 = INPUT_KEY_PRESS;
			break;
	}
}