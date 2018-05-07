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

class CArrow;

class Level;
class CPlayer :
	public CObject
{
public:
	CPlayer(GLuint _shaders, glm::vec3 _position, Level& level, int _index, glm::vec3 _color);
	~CPlayer();

	void SetPhysics();

	void DrawObject() override;
	void Update() override;
	void PlayerInput();
	bool GetIsAlive();

	// Creates a model based on the input
	// Takes what shaders the object shuld use and its position in world space
	// Returns the created model
	static CPlayer* CreatePlayer(GLuint _shaders, glm::vec3 _position, Level& level, int _index, glm::vec3 _color);
	void Collide(b2Body& otherPlayerBody);
	void SetPosition(glm::vec3 newPos);
	void SetArrow(CArrow* _arrow);
private:
	// Gets the location of some variables for the shader for later edditiong
	void getUniformLocation();
	void ReduceHealth();

	GLuint gScaleLocation, gRotateLocation, gTranslateLocation, currentTimeLocation, colorLocation;
	GLuint m_shaders;
	Texture* pTexture;
	Model m_model;
	GLfloat currentTime;
	float m_angle;
	float m_chargeAmount = (glm::pi<float>() * 3.0f) / 2.0f;

	bool m_chargeLeft;
	bool m_chargeRight;
	bool m_isAlive;

	float m_power;

	int m_iIndices;
	int m_iPlayerIndex;
	int m_iHealth;
	float m_fRadius;
	glm::mat4 Scale;
	CArrow* arrow;
	glm::vec3 color;
};

#endif // __PLAYER_H__