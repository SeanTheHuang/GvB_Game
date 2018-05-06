#pragma once

//Internal Includes
#include <conio.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <algorithm>

//Binary File Includes
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\random.hpp>


#include <Box2D\Box2D.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//Global Project Includes
#include "time.h"
#include "input.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#define BUFFER_OFFSET(i) ((GLvoid *)(i*sizeof(float)))

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
	CUBOID,
	PLAYER,
	ARROW,
	PLATFORM,
	PILLAR,
	GROUND,
	WALL
};
