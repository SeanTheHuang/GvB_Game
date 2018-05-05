#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <memory>

#include "include.h"
#include "camera.h"
#include "entity.h"
#include "quad.h"
#include "shaderhelper.h"
#include "object.h"
#include "player.h"
#include "ContactManager.h"
#include "buttonUI.h"
#include "sprite.h"

class Level
{
//== Methods
public:
	Level();
	~Level();

	//Fill level with objects. Initialize all objects
	virtual void Initialize() = 0;
	//Destroy all objects
	virtual void CleanUp();
	//Update all objects. Apply level logic
	virtual void Update();
	void addToKillList(CObject* toKill);
	//Render all objects
	virtual void Render();

	b2Body* addObject(std::unique_ptr<CObject> obj);

	void removeObjects();

	static const float s_kPixelsPerMeter;
	static const float s_kGravity;

protected:
	Level(const Level&) = delete;
	void operator=(Level const&) = delete;

//== Members
protected:
	CCamera m_Camera;
	std::vector<GLuint> m_vecShaders;
	std::vector<CObject*> m_vecObjects;
	std::vector<CPlayer*> m_vecPlayers;
	std::unique_ptr<b2World> m_world;

	std::vector<CObject*> m_killList;
	std::vector<CSprite*> m_sprites;
	std::vector<CButtonUI*> m_buttons;

	std::vector<std::unique_ptr<CObject>> m_objs;
	CContactManager m_contactInstance;

	int m_highlightedButton;
	float m_delayLength = 0.25f;
	float m_delayStamp;
};

#endif // __LEVEL_H__