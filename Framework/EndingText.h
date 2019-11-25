#pragma once
#include "GameObject.h"
#include "FontRenderer.h"

class EndingText :
	public GameObject
{
public:
	EndingText();
	~EndingText();

	Font* font;
	FontRenderer* fontRenderer;
	wchar_t str[100];
};

