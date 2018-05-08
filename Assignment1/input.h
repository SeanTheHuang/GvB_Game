#pragma once

#include <map>
#include "include.h"

// Currently only doing the right, coloured buttons
enum JOYSTICK_INPUT
{
	JOYSTICK_A, 
	JOYSTICK_B, 
	JOYSTICK_X, 
	JOYSTICK_Y
};

struct InputMap
{
	int m_left;
	int m_right;
};

//Gets input through OpenGL systems
//Input is a [Singleton class]
class Input
{
	//=== Methods
public:
	static Input& Instance(); //Singleton stuff
							  //Clear memory
	static void Destroy();

	//Returns if key was pressed this frame
	bool GetKeyDown(int _key);
	//Returns if key was released this frame
	bool GetKeyUp(int _key);

	//Returns if key was released this frame
	bool GetKey(int _key);

	bool GetPlayerLeft(int _playerIndex);
	bool GetPlayerRight(int _playerIndex);
	bool GetMouseButton(int _whichButton, int _state);

	// Returns if button was pressed that frame
	bool GetControllerInputDown(int _joyStickID, JOYSTICK_INPUT _button);
	bool GetControllerInputA(int _joyStickID);
	float GetControllerAxes(int _joyStickID, int _button);
	// Returns if button was released that frame
	bool GetControllerInputUp(int _joyStickID, JOYSTICK_INPUT _button);

	//Returns current mouse position in pixels
	glm::vec2 MousePosition();

	// Update mouse buttons
	void Update();

	//Clears key down/up data for a frame
	void Clear();

	//Initializes call backs
	void Initialize();

	// GLFW callbacks
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	// ?????

private:
	Input(); //Singleton stuff
	Input(const Input&) = delete;
	void operator=(Input const&) = delete;

	//=== Members
private:
	static Input* s_instance;
	std::map<int, InputMap> m_inputMappings;

	std::vector<int> m_vecKeyDown;
	std::vector<int> m_vecKeyUp;

	bool m_leftHeld, m_rightHeld;
	int m_oldLeftMouse, m_oldRightMouse;
	int m_iLeftMouseState, m_iRightMouseState;

	bool m_bAHeld[4];
	int m_oldAButton[4];
	int m_AButtonState[4];
};