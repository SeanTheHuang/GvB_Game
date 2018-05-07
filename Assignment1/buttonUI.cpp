#include "buttonUI.h"

#include "shaderhelper.h"
#include "buttonUI.h"
#include "gamemaster.h"
#include "lobbylevel.h"

CButtonUI::CButtonUI(std::string _buttonUpImage, std::string _buttonDownImage,
	glm::vec2 _position, glm::vec2 _dimensions, BUTTON_ACTION _action, int _controlledByPlayer)
	:
	m_playerUsedBy(_controlledByPlayer)
{
	m_buttonUpPath = _buttonUpImage;
	m_buttonDownPath = _buttonDownImage;

	m_position.x = _position.x;
	m_position.y = _position.y;

	m_dimensions = _dimensions;

	m_eAction = _action;
	m_isInteractive = true;

	m_color = glm::vec3(1, 1, 1);

	this->Initialise();
}

CButtonUI::~CButtonUI()
{
	if (m_textureUp)
		delete m_textureUp;

	if (m_textureDown)
		delete m_textureDown;
}

void CButtonUI::Render()
{
	glUseProgram(m_program);

	float aspectRatio = WINDOW_WIDTH / WINDOW_HEIGHT;
	glm::mat4 View = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	glm::mat4 Ortho = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, 0.1f, 100.0f);
	glUniformMatrix4fv(gViewLocation, 1, GL_FALSE, glm::value_ptr(View));
	glUniformMatrix4fv(gOrthoLocation, 1, GL_FALSE, glm::value_ptr(Ortho));
	glUniform1i(gSampler, 0);
	glUniform3f(colorLocation, m_color.x, m_color.y, m_color.z);

	//Find if mouse is hovering over button or not
	if (MouseIsOverButton() || m_highlighted)
	{
		m_textureDown->bind(GL_TEXTURE0);
	}
	else
	{
		m_textureUp->bind(GL_TEXTURE0);
	}

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

bool CButtonUI::Initialise()
{
	CompileShaders();
	CreateVAOwithVBOs();

	glUseProgram(m_program);

	CreateAndLoadTexture();

	getAddressofUniformLocation();
	return true;
}

void CButtonUI::ProcessInteract()
{
	if ((Input::Instance().GetMouseButton(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS) && MouseIsOverButton()) || (Input::Instance().GetControllerInputDown(0, JOYSTICK_A) && m_highlighted))
	{
		switch (m_eAction)
		{
		case TO_LOBBY_BTN:
		{
			GameMaster::Instance().ChangeLevel("Lobby");
			break;
		}
		case TO_HOWTOPLAY_BTN:
		{
			GameMaster::Instance().ChangeLevel("HowToPlay");
			break;
		}
		case STARTGAME_BTN:
		{
			// TEMP!!!, only goes to our test play scene
			GameMaster::Instance().StorePlayerInfo(dynamic_cast<LobbyLevel*>(GameMaster::Instance().GetCurrentLevel())->GetPlayerData());
			GameMaster::Instance().ChangeLevel("Level1");
			break;
		}
		case QUIT_BTN:
		{
			glfwSetWindowShouldClose(GameMaster::Instance().Window(), GLFW_TRUE);
			break;
		}
		case TO_MENU_BTN:
		{
			GameMaster::Instance().ChangeLevel("MainMenu");
			break;
		}
		case ADD_PLAYER_BTN:
		{
			LobbyLevel* lobby = dynamic_cast<LobbyLevel*>(GameMaster::Instance().GetCurrentLevel());
			lobby->AddPlayer(m_playerUsedBy);
			break;
		}
		case PLAYER_PORTRAIT_BTN:
		{
			m_color = glm::vec3(GenerateRandomFloat(0.0f, 1.0f), GenerateRandomFloat(0.0f, 1.0f), GenerateRandomFloat(0.0f, 1.0f));
			LobbyLevel* lobby = dynamic_cast<LobbyLevel*>(GameMaster::Instance().GetCurrentLevel());
			lobby->ChangePlayerColor(m_playerUsedBy, m_color);
			break;
		}
		case READY_PLAYER_BTN:
		{
			LobbyLevel* lobby = dynamic_cast<LobbyLevel*>(GameMaster::Instance().GetCurrentLevel());
			lobby->ReadyPlayer(m_playerUsedBy);
			break;
		}
		default:
			break;
		}
	}


	if ((Input::Instance().GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS) && MouseIsOverButton()))
	{
		switch (m_eAction)
		{
		case PLAYER_PORTRAIT_BTN:
		{
			LobbyLevel* lobby = dynamic_cast<LobbyLevel*>(GameMaster::Instance().GetCurrentLevel());
			lobby->RemovePlayer(m_playerUsedBy);

			break;
		}
		}

	}
}

void CButtonUI::UpdateHighlight(bool _highlighted)
{
	m_highlighted = _highlighted;
}

int CButtonUI::GetPlayerUsedBy()
{
	return m_playerUsedBy;
}

void CButtonUI::CreateAndLoadTexture()
{
	m_textureUp = new Texture(GL_TEXTURE_2D, m_buttonUpPath);

	if (!m_textureUp->load())
	{
		std::cout << "error loading texture from: " << m_buttonUpPath << std::endl;
	}

	m_textureDown = new Texture(GL_TEXTURE_2D, m_buttonDownPath);

	if (!m_textureDown->load())
	{
		std::cout << "error loading texture from: " << m_buttonDownPath << std::endl;
	}
}

void CButtonUI::CreateIndexBuffer()
{
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	GLint indices[6] = { 0,1,2,3,4,5 };
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void CButtonUI::CreateVertexBuffer()
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
		right, down, 0.0f, 1.0f, 0.0f,	//Bottom Right front 2
		right, up, 0.0f, 1.0f, 1.0f,  	// Top Right front  1
		left, up, 0.0f,	0.0f, 1.0f,	// Top Left front  0
		left, down, 0.0f, 0.0f, 0.0f,	//Bottom Left front  3
		right, down, 0.0f, 1.0f, 0.0f	//Bottom Right front 2
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), BUFFER_OFFSET(3));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CButtonUI::CreateVAOwithVBOs()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	CreateVertexBuffer();
	CreateIndexBuffer();
	glBindVertexArray(0);
}

void CButtonUI::CompileShaders()
{
	glUseProgram(m_program);
	ShaderHelper::CompileAndLinkShaders("sprite_vs.glsl", "sprite_fs.glsl", m_program);
}

void CButtonUI::getAddressofUniformLocation()
{
	glUseProgram(m_program);

	gViewLocation = glGetUniformLocation(m_program, "gView");
	assert(gViewLocation != 0xFFFFFFFF);

	gSampler = glGetUniformLocation(m_program, "gSampler");
	assert(gSampler != 0xFFFFFFFF);

	gOrthoLocation = glGetUniformLocation(m_program, "gOrtho");
	assert(gOrthoLocation != 0xFFFFFFFF);

	colorLocation = glGetUniformLocation(m_program, "gColor");
	assert(colorLocation != 0xFFFFFFFF);
}

bool CButtonUI::MouseIsOverButton()
{
	//Get mouse position
	glm::vec2 mousePos = Input::Instance().MousePosition();

	//Invert y axis as button draws from bottom left
	mousePos.y = WINDOW_HEIGHT - mousePos.y;

	if (mousePos.x >= m_position.x
		&& mousePos.y >= m_position.y
		&& mousePos.x <= m_position.x + m_dimensions.x
		&& mousePos.y <= m_position.y + m_dimensions.y)
	{
		return true;
	}

	return false; //Reach here: No mouse hover
}


