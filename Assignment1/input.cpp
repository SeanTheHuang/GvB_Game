#include "input.h"

#include "gamemaster.h"
#include <algorithm>

Input* Input::s_instance = nullptr;

Input& Input::Instance()
{
	if (!s_instance)
		s_instance = new Input();

	return (*s_instance);
}

void Input::Destroy()
{
	//Nothing to destroy
	if (!s_instance)
		return;

	delete s_instance;

	s_instance = nullptr;
}

bool Input::GetKeyDown(int _key)
{
	return std::find(m_vecKeyDown.begin(), m_vecKeyDown.end(), _key) != m_vecKeyDown.end();
}

bool Input::GetKeyUp(int _key)
{
	return std::find(m_vecKeyUp.begin(), m_vecKeyUp.end(), _key) != m_vecKeyUp.end();
}

bool Input::GetKey(int _key)
{
	return glfwGetKey(GameMaster::Instance().Window(), _key) == GLFW_PRESS;
}

bool Input::GetPlayerLeft(int _playerIndex)
{
	return GetKey(m_inputMappings[_playerIndex].m_left) || GetControllerInputDown(_playerIndex-1, JOYSTICK_X);
}

bool Input::GetPlayerRight(int _playerIndex)
{
	return GetKey(m_inputMappings[_playerIndex].m_right) || GetControllerInputDown(_playerIndex-1, JOYSTICK_B);
}

bool Input::GetMouseButton(int _whichButton, int _state)
{
	if (_whichButton == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (m_leftHeld)
			return false;

		return m_iLeftMouseState == _state;
	}
	else if (_whichButton == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (m_rightHeld)
			return false;

		return m_iRightMouseState == _state;
	}

	//int state = glfwGetMouseButton(GameMaster::Instance().Window(), _whichButton);
	//return state == _state;
}

bool Input::GetControllerInputDown(int _joyStickID, JOYSTICK_INPUT _button)
{
	int count;
	const unsigned char* axes = glfwGetJoystickButtons(_joyStickID, &count);
	if (!axes)
		return false;
	return (axes[(int)_button] != '\0');
}

float Input::GetControllerAxes(int _joyStickID, int _button)
{
	int count;
	const float* axes = glfwGetJoystickAxes(_joyStickID, &count);

	if (!axes)
		return false;
	return axes[_button];
}

bool Input::GetControllerInputUp(int _joyStickID, JOYSTICK_INPUT _button)
{
	int count;
	const unsigned char* axes = glfwGetJoystickButtons(_joyStickID, &count);

	if (!axes)
		return false;
	char a = axes[(int)_button];

	return false;
}

void Input::Clear()
{
	m_vecKeyDown.clear();
	m_vecKeyUp.clear();
}

glm::vec2 Input::MousePosition()
{
	double xPos, yPos;
	glfwGetCursorPos(GameMaster::Instance().Window(), &xPos, &yPos);
	return glm::vec2(xPos, yPos);
}

void Input::Update()
{
	m_oldLeftMouse = m_iLeftMouseState;
	m_oldRightMouse = m_iRightMouseState;

	m_iLeftMouseState = glfwGetMouseButton(GameMaster::Instance().Window(), GLFW_MOUSE_BUTTON_LEFT);
	if (m_iLeftMouseState == m_oldLeftMouse)
		m_leftHeld = true;
	else
		m_leftHeld = false;
	
	m_iRightMouseState = glfwGetMouseButton(GameMaster::Instance().Window(), GLFW_MOUSE_BUTTON_RIGHT);
	if (m_iRightMouseState == m_oldRightMouse)
		m_rightHeld = true;
	else
		m_rightHeld = false;
}

void Input::Initialize()
{
	m_inputMappings[1] = { GLFW_KEY_A, GLFW_KEY_S };
	m_inputMappings[2] = { GLFW_KEY_O, GLFW_KEY_P };
	m_inputMappings[3] = { GLFW_KEY_LEFT, GLFW_KEY_RIGHT };
	m_inputMappings[4] = { GLFW_KEY_KP_8, GLFW_KEY_KP_9 };

}

void Input::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	// Record key presses
	if (action == GLFW_PRESS)
	{
		Input::Instance().m_vecKeyDown.push_back(key);
	}
	else if (action == GLFW_RELEASE)
	{
		Input::Instance().m_vecKeyUp.push_back(key);
	}
}



Input::Input()
{
	m_iLeftMouseState = m_oldLeftMouse = GLFW_RELEASE;
	m_iRightMouseState = m_oldRightMouse = GLFW_RELEASE;
	glfwSetKeyCallback(GameMaster::Instance().Window(), KeyCallback);
}
