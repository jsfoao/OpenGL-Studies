#pragma once
#include <vector>
#include "glm_math.h"

using namespace std;

class NActor;
class NComponent;
class Transform;

namespace Nata
{
	class NObject
	{

	};

	class NActor
	{
	public:
		vector<NComponent*> Components;

	public:
		NActor();
		~NActor()
		{
			for (size_t i = 0; i < Components.size(); i++)
			{
				delete Components[i];
			}
		}

		virtual void Begin();
		virtual void Tick();

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			comp->Owner = this;
			Components.push_back(comp);
		}

		template <typename T>
		T* GetComponent()
		{
			for (NComponent* component : Components)
			{
				if (typeid(*component).name() == typeid(T).name())
				{
					return (T*)component;
				}
			}
		}
	};

	class NComponent
	{
	public:
		NActor* Owner;

	public:
		NComponent();
		~NComponent();

		virtual void Begin();
		virtual void Tick();
	};
}