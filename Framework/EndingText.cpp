#include "stdafx.h"
#include "EndingText.h"


EndingText::EndingText() :GameObject(fontRenderer = new FontRenderer()), str(L"Congratulation!!")
{
	font = new Font(L"Arial", 30.0f);
	fontRenderer->font = this->font;
	fontRenderer->text = str;
}


EndingText::~EndingText()
{
	SAFE_DELETE(font);
}
