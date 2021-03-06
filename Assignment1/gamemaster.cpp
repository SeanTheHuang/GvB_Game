#include "gamemaster.h"

#include "mainlevel.h"
#include "mainmenulevel.h"
#include "lobbylevel.h"
#include "howtoplaylevel.h"
#include "AboutLevel.h"
#include "GameLevel1.h"
#include "GameLevel2.h"
#include "GameLevel3.h"
#include "GameLevel4.h"
#include "GameLevel5.h"
#include "endlevel.h"

GameMaster* GameMaster::s_instance = nullptr;

GameMaster::~GameMaster()
{
	for (auto it = m_mapLevels.begin(); it != m_mapLevels.end(); it++)
	{
		delete it->second;
	}
}

GameMaster& GameMaster::Instance()
{
	if (!s_instance)
		s_instance = new GameMaster();

	return (*s_instance);
}

void GameMaster::Destroy()
{
	//Nothing to destroy
	if (!s_instance)
		return;

	delete s_instance;
	
	s_instance = nullptr;
}

void GameMaster::Initialize()
{
	m_sNextLevelName = "";

	//Initialize GLFW and other objects
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//AA
	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_pWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "THE BEST GLFW TEMPLATE EVER MADE BY SEAN WHICH HE HOPES HE WONT NEED TO MAKE ANOTHER", NULL, NULL);
	if (m_pWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_pWindow);
	glfwSetFramebufferSizeCallback(m_pWindow, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glClearColor(0.05f, 0.00f, 0.07f, 1.0f);

	////Sissor test
	//int cutAmount = 60;
	//glEnable(GL_SCISSOR_TEST);
	//glScissor(0, cutAmount, WINDOW_WIDTH, WINDOW_HEIGHT - 2 * cutAmount);

	////BF culling
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);

	//=== Start game ===

	InitializeCallbacks();
	while (!glfwWindowShouldClose(m_pWindow))
	{
		Update();
		Render();
	}

	glfwTerminate();

	//=== Run Game here ===
	ApplicationCleanUp();
}

void GameMaster::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void GameMaster::ApplicationCleanUp()
{
	Time::Destroy();
	Input::Destroy();
}

void GameMaster::InitializeCallbacks()
{
	// Time
	Time::Instance().Initialize();

	// Mouse and keyboard input
	Input::Instance().Initialize();

	// Sounds
	CAudio::InitializeFMOD();
	CAudio::LoadAudio();

	// Game Levels
	InitializeLevels();
}

void GameMaster::ChangeLevel(std::string _levelName)
{
	// Will change level after current leve has finished updating.
	m_sNextLevelName = _levelName;
}

void GameMaster::StorePlayerInfo(std::vector<Player> _players)
{
	m_connectedPlayers.clear();
	m_connectedPlayers = _players;
}

std::vector<Player>& GameMaster::GetPlayerInfo()
{
	return m_connectedPlayers;
}

void GameMaster::Update()
{
	glfwPollEvents();
	Input::Instance().Update();
	Time::Instance().Update();
	m_pCurrentLevel->Update();

	if (m_sNextLevelName != "")
	{
		// Time to change level
		m_pCurrentLevel->CleanUp();
		m_pCurrentLevel = m_mapLevels[m_sNextLevelName];
		m_pCurrentLevel->Initialize();
		m_sNextLevelName = "";
	}

	Input::Instance().Clear();
}

void GameMaster::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	m_pCurrentLevel->Render();
	// Render UI elements ontop
	m_menu.RenderScene();
	glfwSwapBuffers(m_pWindow);
}

Level * GameMaster::GetCurrentLevel()
{
	return m_pCurrentLevel;
}

std::string GameMaster::NewLevel()
{
	int randomIndex = rand() % m_sLevelNamesName.size();
	std::string level = m_sLevelNamesName.at(randomIndex);
	m_sLevelNamesName.erase(m_sLevelNamesName.begin() + randomIndex);
	return level;
}

int GameMaster::GetRemainingLevels()
{
	return m_sLevelNamesName.size();
}

void GameMaster::EndGame()
{
	m_sLevelNamesName.clear();
	m_sLevelNamesName.push_back("Level1");
	m_sLevelNamesName.push_back("Level2");
	m_sLevelNamesName.push_back("Level3");
	m_sLevelNamesName.push_back("Level4");
	m_sLevelNamesName.push_back("Level5");
	m_sNextLevelName = "EndLevel";
}

GameMaster::GameMaster()
{
	m_pCurrentLevel = nullptr;
	m_pWindow = nullptr;

	//Make randomiser work
	srand((unsigned int)time(NULL));
}

void GameMaster::InitializeLevels()
{
	// Initialize UI elements
	m_menu.Initialize();

	// Create all levels here
	// First level put into level map will be start level
	// Entities and UI elements are Initialized here

	// ===== Main Menu Scene ======
	Level* mainMenu = new MainMenuLevel();
	m_mapLevels.insert(std::pair<std::string, Level*>("MainMenu", mainMenu));

	// ===== Lobby Scene ======
	Level* lobbyLevel = new LobbyLevel();
	m_mapLevels.insert(std::pair<std::string, Level*>("Lobby", lobbyLevel));

	// ===== How To Play Scene ======
	Level* HTPLevel = new HowToPlayLevel();
	m_mapLevels.insert(std::pair<std::string, Level*>("HowToPlay", HTPLevel));

	// ===== About Scene ======
	Level* aboutLevel = new AboutLevel();
	m_mapLevels.insert(std::pair<std::string, Level*>("AboutLevel", aboutLevel));


	// ===== Test Level Scene ======
	Level* inGameLevel = new MainLevel();
	m_mapLevels.insert(std::pair<std::string, Level*>("InGame", inGameLevel));

	// ===== Level 1 ======
	Level* Level1 = new GameLevel1();
	m_mapLevels.insert(std::pair<std::string, Level*>("Level1", Level1));
	m_sLevelNamesName.push_back("Level1");

	// ===== Level 2 ======
	Level* Level2 = new GameLevel2();
	m_mapLevels.insert(std::pair<std::string, Level*>("Level2", Level2));
	m_sLevelNamesName.push_back("Level2");

	// ===== Level 3 ======
	Level* Level3 = new GameLevel3();
	m_mapLevels.insert(std::pair<std::string, Level*>("Level3", Level3));
	m_sLevelNamesName.push_back("Level3");

	// ===== Level 4 ======
	Level* Level4 = new GameLevel4();
	m_mapLevels.insert(std::pair<std::string, Level*>("Level4", Level4));
	m_sLevelNamesName.push_back("Level4");

	// ===== Level 5 ======
	Level* Level5 = new GameLevel5();
	m_mapLevels.insert(std::pair<std::string, Level*>("Level5", Level5));
	m_sLevelNamesName.push_back("Level5");

	// ===== End Level ======
	Level* endLevel = new EndLevel();
	m_mapLevels.insert(std::pair<std::string, Level*>("EndLevel", endLevel));

	// Set first level in map as default level
	m_pCurrentLevel = m_mapLevels["MainMenu"];
	//m_pCurrentLevel = m_mapLevels["Level1"];
	m_pCurrentLevel->Initialize();
}
