#pragma once

#include "IComponent.h"

#include "Consts.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"

class ColliderComponent : public IComponent
{
public:
	RigidBodyComponent* GetRigidbodyComponent() { return rigidyBodyComponent; }
	TransformComponent* GetTransformComponent() { return transformComponent; }

	void SetTransformComponent(TransformComponent* trans) { transformComponent = trans; }
	void SetRigidbodyComponent(RigidBodyComponent* rb) { rigidyBodyComponent = rb; }

	virtual Collider ReturnCollider() = 0;

protected:
	ColliderType colliderType;
	TransformComponent* transformComponent;
	RigidBodyComponent* rigidyBodyComponent;
};
