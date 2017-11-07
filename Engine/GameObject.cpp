#include "GameObject.h"

void GameObject::Init(const std::string& fileName)
{
	_fileName = fileName;
}

GameObject::~GameObject()
{
	for (auto component : _components)
	{
		delete component;
		component = nullptr;
	}
}

void GameObject::AddComponent(IComponent * component)
{
	if (component != nullptr)
	{
		_components.push_back(component);
	}
}

void GameObject::Draw(Graphics& gfx) const
{
	for (auto component : _components)
	{
		// Cast component to IDrawable
		IDrawable * drawableComponent = dynamic_cast<IDrawable *> (component);

		if (drawableComponent != nullptr)
		{
			// Is drawable
			drawableComponent->Draw(gfx);
		}
	}
}

void GameObject::Update(float deltaTime)
{
	// Update all updateable components
	for (auto component : _components)
	{
		// Cast component to IUpdateable - This is bad!!
		IUpdateable * updateableComponent = dynamic_cast<IUpdateable *> (component);

		if (updateableComponent != nullptr)
		{
			// Is updateable
			updateableComponent->Update(deltaTime);
		}
	}
}