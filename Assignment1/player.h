//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: Pyramid.h
// Description	: this is the pyramid object with all relevant functions
// Author		: Sebastian Tengdahl
// Mail			: sebastian.ten7230@mediadesign.school.nz
//

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Object.h"
#include "Model.h"

class Level;
class CPlayer :
	public CObject
{
public:
	CPlayer(GLuint _shaders, glm::vec3 _position, Level& level);
	~CPlayer();

	void SetPhysics();

	void DrawObject() override;

	// Creates a model based on the input
	// Takes what shaders the object shuld use and its position in world space
	// Returns the created model
	static CPlayer* CreatePlayer(GLuint _shaders, glm::vec3 _position, Level& level);
private:
	// Gets the location of some variables for the shader for later edditiong
	void getUniformLocation();

	GLuint gScaleLocation, gRotateLocation, gTranslateLocation, currentTimeLocation;
	GLuint m_shaders;
	Texture* pTexture;
	Model m_model;
	GLfloat currentTime;

	int m_iIndices;
};

#endif // __PLAYER_H__