#pragma once

#include "IComponent.h"
#include "IMessageable.h"

#include "RecieveDamageMessage.h"

class DamageableComponent : public IComponent, public IMessageable
{
public:
	DamageableComponent(float startHealth);
	~DamageableComponent();

	void RecieveDamage(float dmg);
	virtual void RecieveMessage(IMessage &msg) override;

	bool IsDead() { return _isDead; }

private:
	float				_health;
	bool				_isDead;
};
