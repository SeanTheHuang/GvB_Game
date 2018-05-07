#include "GameLevel4.h"
#include "modelloader.h"
#include "Arrow.h"

void GameLevel4::Initialize(std::vector<Player> _players)
{
	GLuint cubeShaders;
	ShaderHelper::CompileAndLinkShaders("cube_vertex_shader.glsl", "cube_fragment_shader.glsl", cubeShaders);
	GLuint basicShader;
	ShaderHelper::CompileAndLinkShaders("vertex_shader.glsl", "fragment_shader.glsl", basicShader);
	GLuint perlinShader;
	ShaderHelper::CompileAndLinkShaders("perlin_vertex_shader.glsl", "perlin_fragment_shader.glsl", perlinShader);
	GLuint levelShader;
	ShaderHelper::CompileAndLinkShaders("level_vertex_shader.glsl", "level_fragment_shader.glsl", levelShader);

	m_Camera.GetUniformLocation(cubeShaders, false);
	m_vecShaders.push_back(cubeShaders);
	m_Camera.GetUniformLocation(basicShader, false);
	m_vecShaders.push_back(basicShader);
	m_Camera.GetUniformLocation(perlinShader, false);
	m_vecShaders.push_back(perlinShader);
	m_Camera.GetUniformLocation(levelShader, false);
	m_vecShaders.push_back(levelShader);

	m_vecObjects.push_back(CObject::CreateObject(SKYBOX, m_vecShaders.at(0), m_Camera.GetPosition(), *this));

	// Box2D world creation
	b2Vec2 gravity(0.0f, s_kGravity);
	m_world = std::unique_ptr<b2World>(new b2World(gravity));

	float platformWidth = 7.0f;
	float platformHeight = 2.0f;
	float pillarWidth = 2.0f;
	float pillarHeight = 4.0f;
	float levelCentre = (platformHeight + pillarHeight * 7.0f) / 2.0f;
	int connectedPlayers = _players.size();

	// =================Border=====================
	// Floor
	m_vecObjects.push_back(CObject::CreateObject(GROUND, m_vecShaders.at(3), glm::vec3(0.0f, 0.0f, -5.0f), *this));
	// Right wall
	m_vecObjects.push_back(CObject::CreateObject(WALL, m_vecShaders.at(3), glm::vec3(4.0f * platformWidth + platformWidth / 2.0f + pillarWidth / 2.0f, (platformHeight / 2.0f) + pillarHeight * 3.5f, -5.0f), *this));
	// Roof
	m_vecObjects.push_back(CObject::CreateObject(GROUND, m_vecShaders.at(3), glm::vec3(0.0f, platformHeight + pillarHeight * 7.0f, -5.0f), *this));
	// Left wall
	m_vecObjects.push_back(CObject::CreateObject(WALL, m_vecShaders.at(3), glm::vec3(-4.0f * platformWidth - platformWidth / 2.0f - pillarWidth / 2.0f, (platformHeight / 2.0f) + pillarHeight * 3.5f, -5.0f), *this));

	// =================Platforms and pillars=====================
	m_vecObjects.push_back(CObject::CreateObject(PLATFORM, m_vecShaders.at(3), glm::vec3(-4.0f * platformWidth, levelCentre / 2.0f, -5.0f), *this));
	m_vecObjects.push_back(CObject::CreateObject(PLATFORM, m_vecShaders.at(3), glm::vec3(-3.0f * platformWidth, levelCentre / 2.0f, -5.0f), *this));
	m_vecObjects.push_back(CObject::CreateObject(PLATFORM, m_vecShaders.at(3), glm::vec3(-4.0f * platformWidth, levelCentre + levelCentre / 2.0f, -5.0f), *this));
	m_vecObjects.push_back(CObject::CreateObject(PLATFORM, m_vecShaders.at(3), glm::vec3(-3.0f * platformWidth, levelCentre + levelCentre / 2.0f, -5.0f), *this));
	m_vecObjects.push_back(CObject::CreateObject(PLATFORM, m_vecShaders.at(3), glm::vec3(-platformWidth - platformWidth / 2.0f, levelCentre, -5.0f), *this));
	m_vecObjects.push_back(CObject::CreateObject(PLATFORM, m_vecShaders.at(3), glm::vec3(-platformWidth / 2.0f, levelCentre, -5.0f), *this));

	m_vecObjects.push_back(CObject::CreateObject(PLATFORM, m_vecShaders.at(3), glm::vec3(platformWidth / 2.0f,levelCentre, -5.0f), *this));
	m_vecObjects.push_back(CObject::CreateObject(PLATFORM, m_vecShaders.at(3), glm::vec3(platformWidth + platformWidth / 2.0f, levelCentre, -5.0f), *this));
	m_vecObjects.push_back(CObject::CreateObject(PLATFORM, m_vecShaders.at(3), glm::vec3(3.0f * platformWidth, levelCentre + levelCentre / 2.0f, -5.0f), *this));
	m_vecObjects.push_back(CObject::CreateObject(PLATFORM, m_vecShaders.at(3), glm::vec3(4.0f * platformWidth, levelCentre + levelCentre / 2.0f, -5.0f), *this));
	m_vecObjects.push_back(CObject::CreateObject(PLATFORM, m_vecShaders.at(3), glm::vec3(3.0f * platformWidth, levelCentre / 2.0f, -5.0f), *this));
	m_vecObjects.push_back(CObject::CreateObject(PLATFORM, m_vecShaders.at(3), glm::vec3(4.0f * platformWidth, levelCentre / 2.0f, -5.0f), *this));

	// =================Players=====================
	switch (connectedPlayers)
	{
	case 4:
	{
		m_vecPlayers.push_back(CPlayer::CreatePlayer(m_vecShaders.at(2), glm::vec3((-4.0f * platformWidth - platformWidth / 2.0f - pillarWidth / 2.0f) + pillarWidth,
			levelCentre + platformHeight + levelCentre / 2.0f, -5.0f), *this, 4));
		m_vecPlayers.at(m_vecPlayers.size() - 1)->SetArrow(CArrow::CreateArrow(m_vecShaders.at(1), glm::vec3((-4.0f * platformWidth - platformWidth / 2.0f - pillarWidth / 2.0f) + pillarWidth,
			levelCentre + platformHeight + levelCentre / 2.0f, -5.0f), *this));
	}
	case 3:
	{
		m_vecPlayers.push_back(CPlayer::CreatePlayer(m_vecShaders.at(2), glm::vec3((4.0f * platformWidth + platformWidth / 2.0f + pillarWidth / 2.0f) - pillarWidth,
			levelCentre + platformHeight + levelCentre / 2.0f, -5.0f), *this, 3));
		m_vecPlayers.at(m_vecPlayers.size() - 1)->SetArrow(CArrow::CreateArrow(m_vecShaders.at(1), glm::vec3((4.0f * platformWidth + platformWidth / 2.0f + pillarWidth / 2.0f) - pillarWidth,
			levelCentre + platformHeight + levelCentre / 2.0f, -5.0f), *this));
	}
	case 2:
	{
		m_vecPlayers.push_back(CPlayer::CreatePlayer(m_vecShaders.at(2), glm::vec3((-4.0f * platformWidth - platformWidth / 2.0f - pillarWidth / 2.0f) + pillarWidth,
			platformHeight + levelCentre / 2.0f, -5.0f), *this, 2));
		m_vecPlayers.at(m_vecPlayers.size() - 1)->SetArrow(CArrow::CreateArrow(m_vecShaders.at(1), glm::vec3((-4.0f * platformWidth - platformWidth / 2.0f - pillarWidth / 2.0f) + pillarWidth,
			platformHeight + levelCentre / 2.0f, -5.0f), *this));
	}
	case 1:
	{
		m_vecPlayers.push_back(CPlayer::CreatePlayer(m_vecShaders.at(2), glm::vec3((4.0f * platformWidth + platformWidth / 2.0f + pillarWidth / 2.0f) - pillarWidth,
			platformHeight + levelCentre / 2.0f, -5.0f), *this, 1));
		m_vecPlayers.at(m_vecPlayers.size() - 1)->SetArrow(CArrow::CreateArrow(m_vecShaders.at(1), glm::vec3((4.0f * platformWidth + platformWidth / 2.0f + pillarWidth / 2.0f) - pillarWidth,
			platformHeight + levelCentre / 2.0f, -5.0f), *this));
	}
	default:
		break;
	}
	m_world->SetContactListener(&m_contactInstance);
}

void GameLevel4::Update()
{
	Level::Update();

	int alivePlayers = 0;
	int winningPlayerIndex = 99;

	for (size_t i = 0; i < m_vecPlayers.size(); ++i)
	{
		if (m_vecPlayers.at(i)->GetIsAlive() != true)
		{
			m_killList.push_back(m_vecPlayers[i]);
			m_vecPlayers.at(i)->SetPosition(glm::vec3(100.0f, 100.0f, 0.0f));

			m_vecPlayers.erase(m_vecPlayers.begin() + i);
			i--;
		}
		else
		{
			alivePlayers++;
			winningPlayerIndex = i;
		}
	}
	if (alivePlayers == 1)
	{
		// Do something with winningPlayerIndex
		CleanUp();
		Initialize(m_connectedPlayerData);
	}

	//Reset scene if player presses 'R'
	if (Input::Instance().GetKeyDown(GLFW_KEY_R))
	{
		CleanUp();
		Initialize(m_connectedPlayerData);
	}
}