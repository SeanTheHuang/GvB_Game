//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: Utills.h
// Description	: some useful defines and structs
// Author		: Sebastian Tengdahl
// Mail			: sebastian.ten7230@mediadesign.school.nz
//

#ifndef __UTILLS_H__
#define __UTILLS_H__

#include <glm/gtc/type_ptr.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define BUFFER_OFFSET(i) ((GLvoid*)(i*sizeof(float)))
#define BUTTON_UP 0
#define BUTTON_DOWN 1
#define MOUSE_LEFT 0
#define MOUSE_MIDDLE 1
#define MOUSE_RIGHT 2

// The data in glm::vec3 and 2 is packed next to each other so it can be sent to the shaders
struct VertexFormat
{
	glm::vec3 Position;
	glm::vec3 Color;
	glm::vec2 TexCord;
};

enum ModelType
{
	SQUARE,
	SKYBOX,
	FLOOR,
	CUBOID
};

#endif //__UTILLS_H__