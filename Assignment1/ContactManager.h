#pragma once

#include <Box2D\Box2D.h>

#include "object.h"
#include "player.h"
#include "audio.h"

class CContactManager : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact)
	{
		void* bodyOneUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyTwoUserData = contact->GetFixtureB()->GetBody()->GetUserData();

		// If there's a collision betweep players call their collide functions
		if (bodyOneUserData && bodyTwoUserData)
		{
			ModelType objOneType = static_cast<CObject*>(bodyOneUserData)->GetModelType();
			ModelType objTwoType = static_cast<CObject*>(bodyTwoUserData)->GetModelType();
			if (objOneType == objTwoType && objOneType == PLAYER)
			{
				static_cast<CPlayer*>(bodyOneUserData)->Collide(*contact->GetFixtureB()->GetBody());
				static_cast<CPlayer*>(bodyTwoUserData)->Collide(*contact->GetFixtureA()->GetBody());
				//CAudio::PlaySound("landing");
			}
		}
	}
};

