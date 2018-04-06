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
	return GetKeyDown(m_inputMappings[_playerIndex].m_left);
}

bool Input::GetPlayerRight(int _playerIndex)
{
	return GetKeyDown(m_inputMappings[_playerIndex].m_right);
}

bool Input::GetControllerInputDown(int _joyStickID, JOYSTICK_INPUT _button)
{
	int count;
	const unsigned char* axes = glfwGetJoystickButtons(_joyStickID, &count);
	return (axes[(int)_button] != '\0');
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
	return glm::vec2();
}

void Input::Initialize()
{
	m_inputMappings[1] = { GLFW_KEY_A, GLFW_KEY_D };
	m_inputMappings[2] = { GLFW_KEY_LEFT, GLFW_KEY_RIGHT };
}

Input::Input()
{
	//Do nothing?
}
