#include "sprite.h"
#include "shaderhelper.h"

CSprite::CSprite(std::string _file, glm::vec2 _position, glm::vec2 _dimensions)
{
	m_filename = _file;

	m_position.x = _position.x;
	m_position.y = _position.y;

	m_dimensions = _dimensions;

	m_isInteractive = false;

	this->Initialise();
}

CSprite::~CSprite()
{
	if (m_texture != nullptr)
	{
		delete m_texture;
		m_texture = nullptr;
	}
}

bool CSprite::Initialise()
{
	CompileShaders();
	CreateVAOwithVBOs();

	glUseProgram(m_program);

	CreateAndLoadTexture(m_texture);

	getAddressofUniformLocation();
	return true;
}

void CSprite::CreateVAOwithVBOs()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	CreateVertexBuffer();
	CreateIndexBuffer();
	glBindVertexArray(0);
}

void CSprite::CreateIndexBuffer()
{
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	GLint indices[6] = { 0,1,2,3,4,5 };
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void CSprite::CreateVertexBuffer()
{
	glm::vec2 temp;
	temp.x = m_position.x;
	temp.y = m_position.y;
	glm::vec2 screenPosition = CUi::PixelToScreenPosition(temp);

	glm::vec2 screenDimension;
	screenDimension.x = (m_dimensions.x / WINDOW_WIDTH) * 2;
	screenDimension.y = (m_dimensions.y / WINDOW_HEIGHT) * 2;

	float left = screenPosition.x;
	float right = screenPosition.x + screenDimension.x;
	float up = screenPosition.y;
	float down = screenPosition.y + screenDimension.y;

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	GLfloat vertices[30]
	{
		left, up, 0.0f,	0.0f, 1.0f,	// Top Left front  0
		right, up, 0.0f, 1.0f, 1.0f,	// Top Right front  1
		left, down, 0.0f, 0.0f, 0.0f,	//Bottom Left front  3
		left, down, 0.0f, 0.0f, 0.0f,	//Bottom Left front  3
		right, up, 0.0f, 1.0f, 1.0f,	// Top Right front  1
		right, down, 0.0f, 1.0f, 0.0f	//Bottom Right front 2
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), BUFFER_OFFSET(3));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CSprite::CreateAndLoadTexture(Texture*& texture)
{
	m_texture = new Texture(GL_TEXTURE_2D, m_filename);

	if (!m_texture->load())
	{
		std::cout << "error loading texture" << std::endl;
	}
}

void CSprite::Render()
{
	glUseProgram(m_program);
	glDepthMask(GL_FALSE);
	float aspectRatio = WINDOW_WIDTH / WINDOW_HEIGHT;
	glm::mat4 View = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	glm::mat4 Ortho = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(gViewLocation, 1, GL_FALSE, glm::value_ptr(View));
	glUniformMatrix4fv(gOrthoLocation, 1, GL_FALSE, glm::value_ptr(Ortho));


	glUniform1i(gSampler, 0);

	m_texture->bind(GL_TEXTURE0);

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
}

void CSprite::getAddressofUniformLocation()
{
	glUseProgram(m_program);

	gViewLocation = glGetUniformLocation(m_program, "gView");
	assert(gViewLocation != 0xFFFFFFFF);

	gSampler = glGetUniformLocation(m_program, "gSampler");
	assert(gSampler != 0xFFFFFFFF);

	gOrthoLocation = glGetUniformLocation(m_program, "gOrtho");
	assert(gOrthoLocation != 0xFFFFFFFF);
}

void CSprite::CompileShaders()
{
	glUseProgram(m_program);
	ShaderHelper::CompileAndLinkShaders("sprite_vs.glsl", "sprite_fs.glsl", m_program);
}