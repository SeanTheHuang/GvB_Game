//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2017 Media Design School
//
// File Name	: Square.h
// Description	: this is the square object with all relevant functions
// Author		: Madeleine Day, Sebastian Tengdahl
// Mail			: sebastian.ten7230@mediadesign.school.nz
//

#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "include.h"
#include "texture.h"

class CSquare
{
public:
	CSquare(std::vector<VertexFormat> _vecVertices, std::vector<GLuint> _vecIndices, GLuint _shaders, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, std::string _strClickedTex, std::string _strUnclickedTex);
	~CSquare();


	void DrawModel();

	// Creates a model based on the input
	// Takes what shaders the object shuld use and its position in world space
	// Returns the created model
	static CSquare* CreateSquare(GLuint _shaders, glm::vec3 _position, glm::vec3 _scale, std::string _strClickedTex, std::string _strUnclickedTex);

	// Creates the texture and sends it to the shader
	void CreateAndBindTexture(std::string _strClickedTex, std::string _strUnclickedTex);

	// Swap whether the button is clicked or not
	void SwapButtonTexture(bool _bClicked);

private:
	// Gets the location of some variables for the shader for later edditiong
	void getUniformLocation();
	

	// Sends the vertex data to the shader
	// Takes the vertex data
	void CreateVBOAttributes(std::vector<VertexFormat> _vecVertices);
	// Sends what order the vertices shuld be used
	// Takes the indices which contains the order of the vertices
	void CreateEBO(std::vector<GLuint> _vecIndices);

	static std::vector<VertexFormat> CreateVertices();
	static std::vector<GLuint> CreateIndices();

	GLuint VBO, VAO, EBO, aPositionLocation, aColorLocation, shaders, aTextureLocation, currentTimeLocation;
	GLuint gScaleLocation, gRotateLocation, gTranslateLocation, gSampler;
	GLuint m_shaders;
	GLfloat currentTime;
	
	// Switch active texture between clicked and unclicked
	Texture* m_pActiveTexture;
	Texture* m_pUnclicked;
	Texture* m_pClicked;

	int m_iIndices;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};

#endif //__SQUARE_H__

