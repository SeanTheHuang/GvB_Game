#include "mainlevel.h"
#include "modelloader.h"
#include "Arrow.h"

void MainLevel::Initialize()
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

	//m_vecObjects.push_back(CObject::CreateObject(CUBOID, m_vecShaders.at(1), glm::vec3(0.0f, 3.0f, -5.0f), *this));
	m_vecObjects.push_back(CObject::CreateObject(FLOOR, m_vecShaders.at(1), glm::vec3(0.0f, -5.0f, -5.0f), *this));

	/*if (m_connectedPlayerData.size() > 0)
	{
		m_vecPlayers.push_back(CPlayer::CreatePlayer(m_vecShaders.at(2), glm::vec3(3.0f, 2.0f, -5.0f), *this, 1));
		m_vecPlayers.at(0)->SetArrow(CArrow::CreateArrow(m_vecShaders.at(1), glm::vec3(3.0f, 2.0f, -5.0f), *this));
	}
	if (m_connectedPlayerData.size() > 1)
	{
		m_vecPlayers.push_back(CPlayer::CreatePlayer(m_vecShaders.at(2), glm::vec3(-3.0f, 3.0f, -5.0f), *this, 2));
		m_vecPlayers.at(1)->SetArrow(CArrow::CreateArrow(m_vecShaders.at(1), glm::vec3(-3.0f, 3.0f, -5.0f), *this));
	}*/

	m_vecObjects.push_back(CObject::CreateObject(PLATFORM, m_vecShaders.at(3), glm::vec3(0.0f, 0.0f, -5.0f), *this));
	m_vecObjects.push_back(CObject::CreateObject(PILLAR, m_vecShaders.at(3), glm::vec3(-7.0f, 1.0f, -5.0f), *this));
	//m_vecPlayers.push_back(CPlayer::CreatePlayer(m_vecShaders.at(2), glm::vec3(0, 1, -5.0f), *this, 2));

	m_world->SetContactListener(&m_contactInstance);

	//Creates all objects in the level.
	//IF WANT NEW LEVEL:
	//		- Create a new class override Level's Initialize for different levels

	/*for (size_t i = 0; i < 10; i++)
	{
		float even = i % 2 == 0 ? 1.0f : -1.0f;

		Entity* cat = new Entity(ModelLoader::Instance().GetModel("Jeffrey"), m_Camera);
		cat->Initialize(glm::vec3(12 * even, -5, 20 + 12 * floorf((float)i / 2)), glm::vec3(1),
			glm::vec3(0, 1, 0), 45 * even, glm::vec3(0.7f, 0.7f, 0.5f));
		cat->EnableStencil(glm::vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX));
		this->AddEntity(cat);
	}*/

	//Create quad
	/*Quad* quad = new Quad(m_Camera, "Resources/Images/weebLove.png");
	quad->Initialize(glm::vec3(0, 0, 40), glm::vec3(20), glm::vec3(0, 1, 0), 0, glm::vec4(1, 1, 1, 0.25f));
	this->AddQuad(quad);*/
}

void MainLevel::Update()
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
		Initialize();
	}

	//Reset scene if player presses 'R'
	if (Input::Instance().GetKeyDown(GLFW_KEY_R))
	{
		CleanUp();
		Initialize();
	}
}
