#include "TextRendererComponent.h"



TextRendererComponent::TextRendererComponent()
{
	mType = "TextRenderer";
}


TextRendererComponent::~TextRendererComponent()
{
}

void TextRendererComponent::Draw(ICamera* cam)
{
	cam->DrawText(_text, GetTransform()->GetPosition());
}
