#include "gamemaster.h"

#include "mainlevel.h"

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

	//Sissor test
	int cutAmount = 60;
	glEnable(GL_SCISSOR_TEST);
	glScissor(0, cutAmount, WINDOW_WIDTH, WINDOW_HEIGHT - 2 * cutAmount);

	//BF culling
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

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
	//m_cAudio->PlaySound("attack", true);

	//TODO D:<<<<<

	// Game Levels
	InitializeLevels();
}

void GameMaster::ChangeLevel(std::string _levelName)
{

}

void GameMaster::Update()
{
	glfwPollEvents();
	Time::Instance().Update();
	m_pCurrentLevel->Update();

	Input::Instance().Clear();
}

void GameMaster::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	m_pCurrentLevel->Render();
	glfwSwapBuffers(m_pWindow);
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
	// Create all levels here
	// First level put into level map will be start level
	// Entities and UI elements are Initialized here

	// ===== Main Scene ======
	Level* mainMenu = new MainLevel();
	m_mapLevels.insert(std::pair<std::string, Level*>("MainMenu", mainMenu));


	// Initialize all levels now
	for (auto it = m_mapLevels.begin(); it != m_mapLevels.end(); it++)
	{
		it->second->Initialize();
	}

	// Set first level in map as default level
	m_pCurrentLevel = m_mapLevels.begin()->second;
}
