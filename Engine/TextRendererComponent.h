#pragma once

#include "IComponent.h"
#include "IDrawable.h"

class TextRendererComponent : public IComponent, public IDrawable
{
public:
	TextRendererComponent();
	~TextRendererComponent();

	void SetText(std::string text) { mText = text; }

	virtual void Draw(ICamera* cam) override;

private:
	std::string mText;
};

