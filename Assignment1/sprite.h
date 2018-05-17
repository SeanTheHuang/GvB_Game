#pragma once

#include "userinterface.h"
#include "texture.h"


class CSprite : public CUi
{
public:
	CSprite(std::string _file, glm::vec2 _position, glm::vec2 _dimensions);
	CSprite(std::string _file, glm::vec2 _position, glm::vec2 _dimensions, glm::vec3 _color);

	~CSprite();

	virtual void Render();
	virtual bool Initialise();
private:
	void CreateAndLoadTexture(Texture*& texture);
	void CreateIndexBuffer();
	void CreateVertexBuffer();
	void CreateVAOwithVBOs();
	void CompileShaders();
	void getAddressofUniformLocation();

private:
	std::string m_filename;
	Texture *m_texture;
	glm::vec3 m_color;

	GLuint m_EBO;

	glm::vec2 m_dimensions;

	GLuint gOrthoLocation, gSampler, gViewLocation, colorLocation;

};