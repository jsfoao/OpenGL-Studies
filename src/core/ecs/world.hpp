#pragma once
#include "entity.hpp"

namespace Nata
{
	class Entity;

	class World
	{
	public:
	private:
		vector<Entity*> m_Entities;

	public:
		World()
		{
		}

		World(const World& world) = delete;
		World& operator=(const World&) = delete;

		Entity* CreateEntity()
		{
			Entity* newEntity = new Entity(this);
			m_Entities.push_back(newEntity);
			return newEntity;
		}

		void DestroyEntity(Entity* entity)
		{
			entity->OnDestroy();
		}

		vector<Entity*> GetAllEntities()
		{
			return m_Entities;
		}

		unsigned int GetEntityCount()
		{
			return m_Entities.size();
		}

		void Begin()
		{
			for (auto entity : m_Entities)
			{
				entity->Begin();
			}
		}

		void Tick()
		{
			for (auto entity : m_Entities)
			{
				entity->Tick();
			}
		}
	};
}