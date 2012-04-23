#include "Input.h"

//
// Global declaration of the CInput class. Gives callback handlers access to the instantiated CInput object
//
CInput g_Input;

// 
//
// Input callback handlers
//
//
//
// HandleMultiTouchButtonCB - For multitouch devices the system will call this callback when the user touches the screen. This callback is called once for each screen touch
// 
void HandleMultiTouchButtonCB(s3ePointerTouchEvent* event)
{
	// Check to see if the touch already exists
	CTouch* touch = g_Input.findTouch(event->m_TouchID);
    if (touch != NULL)
    {
		// Yes it does, so update the touch information
        touch->active = event->m_Pressed != 0; 
        touch->x = event->m_x;
        touch->y = event->m_y;
    }
}
//
// HandleMultiTouchMotionCB - For multitouch devices the system will call this callback when the user moves their finger on the screen. This callback is called once for each screen touch
// 
void HandleMultiTouchMotionCB(s3ePointerTouchMotionEvent* event)
{
	// Check to see if the touch already exists
	CTouch* touch = g_Input.findTouch(event->m_TouchID);
    if (touch != NULL)
    {
		// Updates the touches positional information
        touch->x = event->m_x;
        touch->y = event->m_y;
    }
}
//
// HandleSingleTouchButtonCB - The system will call this callback when the user touches the screen
// 
void HandleSingleTouchButtonCB(s3ePointerEvent* event)
{
	CTouch* touch = g_Input.getTouch(0);
    touch->active = event->m_Pressed != 0;
    touch->x = event->m_x;
    touch->y = event->m_y;
}
//
// HandleSingleTouchMotionCB - The system will call this callback when the user moves their finger on the screen
// 
void HandleSingleTouchMotionCB(s3ePointerMotionEvent* event)
{
	CTouch* touch = g_Input.getTouch(0);
    touch->x = event->m_x;
    touch->y = event->m_y;
}

//
//
// CInput implementation
//
//
CTouch*	CInput::findTouch(int id)
{
	if (!PointerAvailable)
		return NULL;

    // Attempt to find the touch by its ID and then return it
	// If the touch does not exist then it is recorded in the touches list
	for (int t = 0; t < MAX_TOUCHES; t++)
	{
		if (Touches[t].id == id)
			return &Touches[t];
		if (!Touches[t].active)
		{
            Touches[t].id = id;
			return &Touches[t];
		}
	}

	return NULL;
}

CTouch*	CInput::getTouchByID(int id)
{
	if (!PointerAvailable)
		return NULL;

	// Find touch by its ID and return it
	for (int t = 0; t < MAX_TOUCHES; t++)
	{
		if (Touches[t].active && Touches[t].id == id)
			return &Touches[t];
	}

	return NULL;
}

int CInput::getTouchCount() const
{
	if (!PointerAvailable)
		return 0;

	// Return the total number of active touches
	int count = 0;
	for (int t = 0; t < MAX_TOUCHES; t++)
	{
		if (Touches[t].active)
            count++;
	}

	return count;
}

bool CInput::Init()
{
	// Check to see if the device that we are running on supports the pointer
    PointerAvailable = s3ePointerGetInt(S3E_POINTER_AVAILABLE) ? true : false;
	if (!PointerAvailable)
		return false;	// No pointer support

	if (PointerAvailable)
	{
		// Clear out the touches array
		for (int t = 0; t < MAX_TOUCHES; t++)
		{
			Touches[t].active = false;
			Touches[t].id = 0;
		}

		// Determine if the device supports multi-touch
		IsMultiTouch = s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) ? true : false;

		// For multi-touch devices we handle touch and motion events using different callbacks
		if (IsMultiTouch)
		{
			s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)HandleMultiTouchButtonCB, NULL);
			s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)HandleMultiTouchMotionCB, NULL);
		}
		else
		{
			s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)HandleSingleTouchButtonCB, NULL);
			s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)HandleSingleTouchMotionCB, NULL);
		}
	}

	// Check to see if the device that we are running on supports the keyboard
    KeysAvailable = (s3eKeyboardGetInt(S3E_KEYBOARD_HAS_KEYPAD) || s3eKeyboardGetInt(S3E_KEYBOARD_HAS_ALPHA));

	// Check to see if the device that we are running on supports the on screen keyboard
	OSKeyboardAvailable = s3eOSReadStringAvailable() == S3E_TRUE; 

	return true; // Pointer support
}

void CInput::Release()
{
	if (PointerAvailable)
	{
		// Unregister the pointer system callbacks
		if (IsMultiTouch)
		{
			s3ePointerUnRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)HandleMultiTouchButtonCB);
			s3ePointerUnRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)HandleMultiTouchMotionCB);
		}
		else
		{
			s3ePointerUnRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)HandleSingleTouchButtonCB);
			s3ePointerUnRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)HandleSingleTouchMotionCB);
		}
	}
}

void CInput::Update()
{
	// Update the pointer if it is available
	if (PointerAvailable)
		s3ePointerUpdate();

	// Update key system if it is available
	if (KeysAvailable)
		s3eKeyboardUpdate();
}

bool CInput::isKeyDown(s3eKey key) const
{
	if (!KeysAvailable)
		return false;

	// Return down state of queried key
	return (s3eKeyboardGetState(key) & S3E_KEY_STATE_DOWN) == S3E_KEY_STATE_DOWN;
}

bool CInput::isKeyUp(s3eKey key) const
{
	if (!KeysAvailable)
		return false;

	// Return up state of queried key
	return (s3eKeyboardGetState(key) & S3E_KEY_STATE_UP) == S3E_KEY_STATE_UP;
}

bool CInput::wasKeyPressed(s3eKey key) const
{
	if (!KeysAvailable)
		return false;

	// Return pressed state of queried key
	return (s3eKeyboardGetState(key) & S3E_KEY_STATE_PRESSED) == S3E_KEY_STATE_PRESSED;
}

bool CInput::wasKeyReleased(s3eKey key) const
{
	if (!KeysAvailable)
		return false;

	// Return released state of queried key
	return (s3eKeyboardGetState(key) & S3E_KEY_STATE_RELEASED) == S3E_KEY_STATE_RELEASED;
}

const char* CInput::showOnScreenKeyboard(const char* prompt, int flags, const char* default_text)
{
	if (!OSKeyboardAvailable)
		return NULL;

	// Show on screen keyboard and return the input string
	if (default_text != NULL)
		return s3eOSReadStringUTF8WithDefault(prompt, default_text, flags);
	else
		return s3eOSReadStringUTF8(prompt, flags);
}
