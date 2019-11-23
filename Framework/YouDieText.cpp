#include "stdafx.h"
#include "YouDieText.h"


YouDieText::YouDieText():GameObject(fontRenderer = new FontRenderer()),str(L"You Die!")
{
	font = new Font(L"Arial", 50.0f);
	fontRenderer->font = this->font;
	fontRenderer->text = str;
}

YouDieText::~YouDieText()
{
	SAFE_DELETE(font);
}
