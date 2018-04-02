#include "input.h"

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

bool Input::GetKeyDown(char _key)
{
	return false;
}

bool Input::GetKeyUp(char _key)
{
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
}

Input::Input()
{
	//Do nothing?
}
