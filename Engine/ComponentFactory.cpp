#include "ComponentFactory.h"


TransformComponent * ComponentFactory::MakeTransform(Vec2 position, float rotation, float scale)
{
	TransformComponent * transform = new TransformComponent();
	transform->SetPosition(position);
	transform->SetRotation(rotation);
	transform->SetScale(scale);

	return transform;
}

SpriteRendererComponent * ComponentFactory::MakeSpriteRenderer(std::string fileName, TransformComponent* transform, float width, float height, Vec2 offset)
{
	SpriteRendererComponent * spriteRenderer = new SpriteRendererComponent();
	spriteRenderer->SetFilename(fileName);
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	spriteRenderer->SetTransform(transform);
	spriteRenderer->SetOffset(offset);
	spriteRenderer->SetWidthHeight(width, height);

	return spriteRenderer;
}

SpriteAnimatorComponent * ComponentFactory::MakeSpriteAnimator(std::string fileName, TransformComponent * transform, float width, float height, std::vector<AnimationDesc> animDescs, int currentAnim)
{
	SpriteAnimatorComponent * spriteAnimator = new SpriteAnimatorComponent();
	spriteAnimator->SetFilename(fileName);
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	spriteAnimator->SetTransform(transform);
	spriteAnimator->SetAnimations(currentAnim, animDescs);
	spriteAnimator->SetWidthHeight(width, height);

	return spriteAnimator;
}

RigidBodyComponent * ComponentFactory::MakeRigidbody(float staticF, float dynamicF, float rest)
{
	RigidBodyComponent * rigidBody = new RigidBodyComponent(staticF, dynamicF, rest);
	
	return rigidBody;
}

TextRendererComponent * ComponentFactory::MakeTextRenderer(std::string text, TransformComponent * transform)
{
	TextRendererComponent * textRenderer = new TextRendererComponent();
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	textRenderer->SetTransform(transform);
	textRenderer->SetText(text);

	return textRenderer;
}

CircleColliderComponent * ComponentFactory::MakeCircleCollider(float radius, TransformComponent * transform, RigidBodyComponent * rigidbody)
{
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	if (rigidbody == nullptr)
	{
		throw std::exception("This object requires a rigidbody component.");
	}

	CircleColliderComponent * circleCollider = new CircleColliderComponent(transform, rigidbody);
	circleCollider->SetRadius(radius);
	circleCollider->ComputeMass(1);

	return circleCollider;
}

PolygonColliderComponent * ComponentFactory::MakePolygonCollider(Vec2 * verticies, int vertexCount, TransformComponent * transform, RigidBodyComponent * rigidbody)
{
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	if (rigidbody == nullptr)
	{
		throw std::exception("This object requires a rigidbody component.");
	}

	PolygonColliderComponent * polygonCollider = new PolygonColliderComponent(transform, rigidbody);
	polygonCollider->SetVerticies(verticies, vertexCount);
	polygonCollider->ComputeMass(0.3f);

	delete verticies;

	return polygonCollider;
}

BoxColliderComponent * ComponentFactory::MakeBoxCollider(float halfWidth, float halfHeight, TransformComponent * transform, RigidBodyComponent * rigidBody)
{
	if (transform == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	if (rigidBody == nullptr)
	{
		throw std::exception("This object requires a rigidbody component.");
	}

	BoxColliderComponent * boxCollider = new BoxColliderComponent(transform, rigidBody);
	boxCollider->SetBox(halfWidth, halfHeight);
	boxCollider->ComputeMass(0.3f);

	return boxCollider;
}

ColliderRendererComponent * ComponentFactory::MakeColliderRenderer(TransformComponent* trans, ColliderComponent* collider)
{
	if (trans == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	if (collider == nullptr)
	{
		throw std::exception("This object requires a collider component");
	}

	ColliderRendererComponent * colliderRenderer = new ColliderRendererComponent();
	colliderRenderer->SetCollider(collider);
	colliderRenderer->SetTransform(trans);

	return colliderRenderer;
}

TiledBGRenderer * ComponentFactory::MakeTiledBGRenderer(std::string spriteName, float spriteWidth, float spriteHeight, float moveRate, TiledBGDirection direction, TransformComponent * trans, TransformComponent * focusTrans)
{
	if (trans == nullptr)
	{
		throw std::exception("This object requires a transform component.");
	}
	if (focusTrans == nullptr)
	{
		throw std::exception("This object requires a focus transform component");
	}

	TiledBGRenderer * bgRenderer = new TiledBGRenderer();
	bgRenderer->SetTransform(trans);
	bgRenderer->SetFocusTrans(focusTrans);
	bgRenderer->SetMoveRate(moveRate);
	bgRenderer->SetDirection(direction);
	bgRenderer->SetSprite(spriteName, spriteWidth, spriteHeight);

	return bgRenderer;
}
