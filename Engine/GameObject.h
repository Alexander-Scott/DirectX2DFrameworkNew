#pragma once

#include "Graphics.h"
#include "Consts.h"

#include "IComponent.h"
#include "IUpdateable.h"
#include "IDrawable.h"
#include "IMessageable.h"

class GameObject
{
public:
	~GameObject();

	void Draw(Graphics& gfx) const;
	virtual void Update(float deltaTime);
	void SendMessageToComponents(IMessage& message);

	void AddComponent(IComponent* component);

	template<class T>
	T * GetComponent()
	{
		for (auto component : _components)
		{
			T* tComponent = dynamic_cast<T *> (component);

			if (tComponent != nullptr)
			{
				return tComponent;
			}
		}

		return nullptr;
	}

	template<class T>
	std::vector<T*> GetComponents()
	{
		std::vector<T*> components;
		for (auto component : _components)
		{
			T* tComponent = dynamic_cast<T *> (component);

			if (tComponent != nullptr)
			{
				components.push_back(tComponent);
			}
		}

		return components;
	}

protected:
	std::vector<IComponent*> _components;
};
