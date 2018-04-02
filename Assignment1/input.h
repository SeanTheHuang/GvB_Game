#pragma once

#include "include.h"


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
	bool GetKeyDown(char _key);
	//Returns if key was released this frame
	bool GetKeyUp(char _key);

	//Returns current mouse position in pixels
	glm::vec2 MousePosition();

	//Clears key down/up data for a frame
	void Clear();

	//Initializes call backs
	void Initialize();



private:
	Input(); //Singleton stuff
	Input(const Input&) = delete;
	void operator=(Input const&) = delete;

	//=== Members
private:
	static Input* s_instance;
};