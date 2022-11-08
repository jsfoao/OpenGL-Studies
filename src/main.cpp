#pragma once
#include "nata.h"
#include "exercises/exercises.hpp"
#include "core/ecs.h"

using namespace Nata;
using namespace glm;

class foo
{
public:
	static int ID;
};

int foo::ID = 2;

int main(int argc, char** argv)
{
	World* world = new World();

	world->CreateEntity();
	world->CreateEntity();

	vector<Entity*> ents = world->GetAllEntities();
}