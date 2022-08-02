#pragma once
#include "MADRengine/MADRpch.h"
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Events.h"
#include "IDControl.h"
#include "Physics.h"


class MADREntity : public EventListener
{
	MADREntity* parent;
};
class Component : public EventListener
{
private:
	IDController::MADR_ID ID;
	MADREntity* owner;

public:
	IDController::MADR_ID GetID() { return ID; }

	void EventResponse(EVENT e)
	{

	}
};

void DeleteComponent(Component*);

namespace Transform {

	class Transform : public Component
	{
	private:
		PhysicsTransform t;
	public:

	};
} //End of Transform Namespace

namespace Colliders
{
	class Collier_2D {};
	struct CollisionData_2D 
	{
		Collier_2D* target;
	};

	class Collider_2D : public Component
	{
	private:
		int layer;
		//Position to the center of the hitbox
		glm::ivec3 localPosition;
		glm::ivec2 collDimensions;
		std::vector<int> mask;
	public:
		bool IsColliding() { return false; }
	};
} //End of Colliders Namespace