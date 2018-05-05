#ifndef __ARROW_H__
#define __ARROW_H__

#include "Object.h"
#include "Model.h"
#include "level.h"

class CArrow :
	public CObject
{
public:
	CArrow(GLuint _shaders, glm::vec3 _position, Level& level);
	~CArrow();

	void DrawObject() override;

	// Creates a model based on the input
	// Takes what shaders the object shuld use and its position in world space
	// Returns the created model
	static CArrow* CreateArrow(GLuint _shaders, glm::vec3 _position, Level& level);
	void SetPosition(glm::vec3 _newPos);
	void SetRotation(float _newRotation);
	void SetScale(float _newScale);
private:
	// Gets the location of some variables for the shader for later edditiong
	void getUniformLocation();

	GLuint gScaleLocation, gRotateLocation, gTranslateLocation;
	GLuint m_shaders;
	Texture* pTexture;
	Model m_model;

	int m_iIndices;
	float m_fRotation;
	float m_fScale;
};

#endif // __ARROW_H__