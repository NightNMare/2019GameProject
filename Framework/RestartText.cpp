#include "stdafx.h"
#include "RestartText.h"


RestartText::RestartText() :GameObject(fontRenderer = new FontRenderer()), str(L"Press R to Restart!!")
{
	font = new Font(L"Arial", 30.0f);
	fontRenderer->font = this->font;
	fontRenderer->text = str;
}


RestartText::~RestartText()
{
	SAFE_DELETE(font);
}
