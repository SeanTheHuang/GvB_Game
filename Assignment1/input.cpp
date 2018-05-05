#include "input.h"

#include "gamemaster.h"

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
	return glfwGetKey(GameMaster::Instance().Window(), _key) == GLFW_PRESS;
}

bool Input::GetKeyUp(int _key)
{
	return glfwGetKey(GameMaster::Instance().Window(), _key) == GLFW_RELEASE;
}

bool Input::GetPlayerLeft(int _playerIndex)
{
	return GetKeyDown(m_inputMappings[_playerIndex].m_left) || GetControllerInputDown(_playerIndex-1, JOYSTICK_X);
}

bool Input::GetPlayerRight(int _playerIndex)
{
	return GetKeyDown(m_inputMappings[_playerIndex].m_right) || GetControllerInputDown(_playerIndex-1, JOYSTICK_B);
}

bool Input::GetMouseButton(int _whichButton, int _state)
{
	int state = glfwGetMouseButton(GameMaster::Instance().Window(), _whichButton);
	return state == _state;
}

bool Input::GetControllerInputDown(int _joyStickID, JOYSTICK_INPUT _button)
{
	int count;
	const unsigned char* axes = glfwGetJoystickButtons(_joyStickID, &count);
	if (!axes)
		return false;
	return (axes[(int)_button] != '\0');
}

float Input::GetControllerAxes(int _joyStickID, int _button, int _direction)
{
	int count;
	const float* axes = glfwGetJoystickAxes(_button, &count);

	return axes[_direction];
	
}

bool Input::GetControllerInputUp(int _joyStickID, JOYSTICK_INPUT _button)
{
	int count;
	const unsigned char* axes = glfwGetJoystickButtons(_joyStickID, &count);

	char a = axes[(int)_button];

	return false;
}

void Input::Clear()
{

}

glm::vec2 Input::MousePosition()
{
	double xPos, yPos;
	glfwGetCursorPos(GameMaster::Instance().Window(), &xPos, &yPos);
	return glm::vec2(xPos, yPos);
}

void Input::Initialize()
{
	m_inputMappings[1] = { GLFW_KEY_A, GLFW_KEY_S };
	m_inputMappings[2] = { GLFW_KEY_O, GLFW_KEY_P };
	m_inputMappings[3] = { GLFW_KEY_LEFT, GLFW_KEY_RIGHT };
	m_inputMappings[4] = { GLFW_KEY_KP_8, GLFW_KEY_KP_9 };

}

Input::Input()
{
	//Do nothing?
}
