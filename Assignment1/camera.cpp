//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: Camera.cpp
// Description	: this is the camera object containing related functions
// Author		: Sebastian Tengdahl
// Mail			: sebastian.ten7230@mediadesign.school.nz
//

#include "Camera.h"
#include "gamemaster.h"

CCamera::CCamera()
{
	m_cameraPos = glm::vec3(0.0f, 0.0f, 40.0f);
	m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}


CCamera::~CCamera()
{
}

void CCamera::GetUniformLocation(GLuint _shaders, bool _bIsOrthographic)
{
	if (_bIsOrthographic)
	{
		CShader shaderFunctions(_shaders, ORTHOGRAPHIC);
		vecShaderFunctions.push_back(shaderFunctions);
	}
	else
	{
		CShader shaderFunctions(_shaders, PERSPECTIVE);
		vecShaderFunctions.push_back(shaderFunctions);
	}
}

void CCamera::SendDataToShaders()
{
	int width, height;
	glfwGetWindowSize(GameMaster::Instance().Window(), &width, &height);
	float aspectRatio = static_cast<float>(width) / height;
	glm::mat4 View = glm::lookAtRH(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
	glm::mat4 Ortho = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, 0.1f, 100.0f);
	glm::mat4 Perspective = glm::perspectiveRH(glm::radians(60.0f), aspectRatio, 1.0f, 100.0f);

	for (size_t i = 0; i < vecShaderFunctions.size(); ++i)
	{
		vecShaderFunctions.at(i).SendDataToShaders(View, Ortho, Perspective);
	}
}

void CCamera::MoveForward(float _fSpeed)
{
	m_cameraPos += m_cameraFront * _fSpeed;
}

void CCamera::MoveLeft(float _fSpeed)
{
	m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * _fSpeed;
}

void CCamera::SetCameraFront(glm::vec3 _front)
{
	m_cameraFront = _front;
}

void CCamera::SetPosition(glm::vec3 _position)
{
	m_cameraPos = _position;
}

glm::vec3 CCamera::GetPosition()
{
	return m_cameraPos;
}

glm::vec3 CCamera::GetFront()
{
	return m_cameraFront;
}
