#include "GameManagerComponent.h"

GameManagerComponent::GameManagerComponent(GUIButtonComponent* centreButton, GUITextComponent* centreButtonText, GUISpriteRendererComponent* centreButtonSprite, TriggerBoxComponent* finishTriggerBox, DamageableComponent* playerDamage)
	: mCentreButton(centreButton), mCentreButtonText(centreButtonText), mCentreButtonSprite(centreButtonSprite), mFinishTriggerBox(finishTriggerBox), mPlayerDamage(playerDamage)
{
	mWaitingOnInput = false;
}

GameManagerComponent::~GameManagerComponent()
{
}

void GameManagerComponent::Update(float deltaTime)
{
	if (mWaitingOnInput)
	{
		if (mCentreButton->Clicked())
		{
			throw;
		}

		return;
	}

	if (mPlayerDamage->IsDead())
	{
		mCentreButton->SetActive(true);

		mCentreButtonText->SetActive(true);
		mCentreButtonText->SetText("RESTART");

		mCentreButtonSprite->SetActive(true);
		mWaitingOnInput = true;
	}
	else if (mFinishTriggerBox->IsTriggered())
	{
		mCentreButton->SetActive(true);

		mCentreButtonText->SetActive(true);
		mCentreButtonText->SetText("PROGRESS");

		mCentreButtonSprite->SetActive(true);
		mWaitingOnInput = true;

		Audio::Instance().PlaySoundEffect("Win");
	}
}