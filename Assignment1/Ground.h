#ifndef __GROUND_H__
#define __GROUND_H__

#include "Object.h"
#include "Model.h"
#include "level.h"

class CGround :
	public CObject
{
public:
	CGround(GLuint _shaders, glm::vec3 _position, Level& level);
	~CGround();

	void SetPhysics();

	void DrawObject() override;

	// Creates a model based on the input
	// Takes what shaders the object shuld use and its position in world space
	// Returns the created model
	static CGround* CreateGround(GLuint _shaders, glm::vec3 _position, Level& level);
private:
	// Gets the location of some variables for the shader for later edditiong
	void getUniformLocation();

	GLuint gScaleLocation, gRotateLocation, gTranslateLocation;
	GLuint m_shaders;
	Texture* pTexture;
	Model m_model;

	int m_iIndices;
};

#endif // __GROUND_H__