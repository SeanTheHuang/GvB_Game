#include "Square.h"

CSquare::CSquare(std::vector<VertexFormat> _vecVertices, std::vector<GLuint> _vecIndices, GLuint _shaders, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, std::string _strClickedTex, std::string _strUnclickedTex) :
	shaders(_shaders),
	m_iIndices(0),
	m_shaders(_shaders),
	m_pActiveTexture(nullptr)
{
	m_position = _position;
	m_rotation = _rotation;
	m_scale = _scale;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	CreateVBOAttributes(_vecVertices);
	CreateEBO(_vecIndices);
	m_iIndices = _vecIndices.size();

	// Store 2 textures as button has 2 states
	CreateAndBindTexture(_strClickedTex , _strUnclickedTex);

	getUniformLocation();
}

CSquare::~CSquare()
{
	if (m_pUnclicked != nullptr)
	{
		delete m_pUnclicked;
		m_pUnclicked = 0;
	}

	if (m_pClicked != nullptr)
	{
		delete m_pClicked;
		m_pClicked = 0;
	}

	
}

void CSquare::DrawModel()
{
	glDisable(GL_DEPTH_TEST);

	glUseProgram(m_shaders);
	glEnable(GL_BLEND);

	// Transparency elimination
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindVertexArray(VAO);

	glm::mat4 Scale = glm::scale(glm::mat4(1.0f), m_scale);
	glm::mat4 Rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f,1.0f,1.0f));
	glm::mat4 Translate = glm::translate(glm::mat4(1.0f), m_position);
	currentTime = Time::Instance().TotalTime();
	currentTime = currentTime / 1000.0f;

	glUniformMatrix4fv(gScaleLocation, 1, GL_FALSE, glm::value_ptr(Scale));
	glUniformMatrix4fv(gRotateLocation, 1, GL_FALSE, glm::value_ptr(Rotate));
	glUniformMatrix4fv(gTranslateLocation, 1, GL_FALSE, glm::value_ptr(Translate));
	glUniform1f(currentTimeLocation, currentTime);

	glUniform1i(gSampler, 0);
	m_pActiveTexture->bind(GL_TEXTURE0);
	
	glDrawElements(GL_TRIANGLES, m_iIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glDisable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);

}

CSquare* CSquare::CreateSquare(GLuint _shaders, glm::vec3 _position, glm::vec3 _scale, std::string _strClickedTex, std::string _strUnclickedTex)
{
	std::vector<VertexFormat> _vecVertices;
	std::vector<GLuint> vecIndices;
	glm::vec3 rotation;

	_vecVertices = CreateVertices();
	vecIndices = CreateIndices();
	rotation = glm::vec3(0.0f, 0.0f, 1.0f);

	CSquare* square = new CSquare(_vecVertices, vecIndices, _shaders, _position, rotation, _scale, _strClickedTex, _strUnclickedTex);
	return square;
}

void CSquare::getUniformLocation()
{
	gScaleLocation = glGetUniformLocation(m_shaders, "gScale");
	assert(gScaleLocation != 0xFFFFFFFF);

	gRotateLocation = glGetUniformLocation(m_shaders, "gRotate");
	assert(gRotateLocation != 0xFFFFFFFF);

	gTranslateLocation = glGetUniformLocation(m_shaders, "gTranslate");
	assert(gTranslateLocation != 0xFFFFFFFF);

	gSampler = glGetUniformLocation(m_shaders, "gSampler");
	assert(gSampler != 0xFFFFFFFF);

	currentTimeLocation = glGetUniformLocation(m_shaders, "currentTime");
	//assert(currentTimeLocation != 0xFFFFFFFF);
}

void CSquare::CreateAndBindTexture(std::string _strClickedTex, std::string _strUnclickedTex)
{
	aTextureLocation = GL_TEXTURE_2D;
	m_pClicked = new Texture(aTextureLocation, _strClickedTex);
	if (!m_pClicked->load())
	{
		//CLog::Write("Error Loading Texture");
	}

	m_pUnclicked = new Texture(aTextureLocation, _strUnclickedTex);
	if (!m_pUnclicked->load())
	{
		//CLog::Write("Error Loading Texture");
	}

	// Set default active texture to unclicked
	m_pActiveTexture = m_pUnclicked;
	glUniform1i(glGetUniformLocation(m_shaders, "Texture"), 0);
}

void CSquare::SwapButtonTexture(bool _bClicked)
{
	// Set active to appropriate texture
	m_pActiveTexture = (_bClicked) ? m_pClicked : m_pUnclicked;
}

void CSquare::CreateVBOAttributes(std::vector<VertexFormat> _vecVertices)
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * _vecVertices.size(), _vecVertices.data(), GL_STATIC_DRAW);

	aPositionLocation = glGetAttribLocation(shaders, "a_position");
	glVertexAttribPointer(aPositionLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(aPositionLocation);

	aColorLocation = glGetAttribLocation(shaders, "a_Color");
	glVertexAttribPointer(aColorLocation, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), BUFFER_OFFSET(3));
	glEnableVertexAttribArray(aColorLocation);

	aTextureLocation = glGetAttribLocation(shaders, "a_texCord");
	glVertexAttribPointer(aTextureLocation, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), BUFFER_OFFSET(6));
	glEnableVertexAttribArray(aTextureLocation);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CSquare::CreateEBO(std::vector<GLuint> _vecIndices)
{
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _vecIndices.size(), _vecIndices.data(), GL_STATIC_DRAW);
}

std::vector<VertexFormat> CSquare::CreateVertices()
{
	VertexFormat verTopLeft{ { -1.0f,  1.0f, 0.0f },{ 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } };
	VertexFormat verTopRight{ { 1.0f,  1.0f, 0.0f },{ 1.0f, 1.0f, 1.0f },{ 1.0f, 0.0f } };
	VertexFormat verBottomLeft{ { -1.0f, -1.0f, 0.0f },{ 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } };
	VertexFormat verBottomRight{ { 1.0f, -1.0f, 0.0f },{ 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f } };

	std::vector<VertexFormat> vecVertices{
		verTopLeft,
		verTopRight,
		verBottomLeft,
		verBottomRight };

	return vecVertices;
}

std::vector<GLuint> CSquare::CreateIndices()
{
	std::vector<GLuint> vecIndices{
		0,2,1,
		1,2,3 };
	return vecIndices;
}

void CSquare::SetHidden(bool _newState) { m_bHidden = _newState; }
bool CSquare::IfHidden() { return m_bHidden; }
