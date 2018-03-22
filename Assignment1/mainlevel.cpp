#include "mainlevel.h"
#include "modelloader.h"

void MainLevel::Initialize()
{
	//Create Camera(s) for the level
	m_pCamera = new Camera();

	//Creates all objects in the level.
	//IF WANT NEW LEVEL:
	//		- Create a new class override Level's Initialize for different levels

	for (size_t i = 0; i < 10; i++)
	{
		float even = i % 2 == 0 ? 1.0f : -1.0f;

		Entity* cat = new Entity(ModelLoader::Instance().GetModel("Jeffrey"), m_pCamera);
		cat->Initialize(glm::vec3(12 * even, -5, 20 + 12 * floorf((float)i / 2)), glm::vec3(1),
			glm::vec3(0, 1, 0), 45 * even, glm::vec3(0.7f, 0.7f, 0.5f));
		cat->EnableStencil(glm::vec3((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX));
		this->AddEntity(cat);
	}

	//Create quad
	Quad* quad = new Quad(m_pCamera, "Resources/Images/weebLove.png");
	quad->Initialize(glm::vec3(0, 0, 40), glm::vec3(20), glm::vec3(0, 1, 0), 0, glm::vec4(1, 1, 1, 0.25f));
	this->AddQuad(quad);
}

void MainLevel::Update()
{
	Level::Update();

	//Reset scene if player presses 'R'
	if (Input::Instance().GetKeyDown('r'))
	{
		CleanUp();
		Initialize();
	}
}
