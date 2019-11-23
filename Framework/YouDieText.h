#pragma once
#include "GameObject.h"
#include "FontRenderer.h"
class YouDieText :
	public GameObject
{
public:
	YouDieText();
	~YouDieText();

	Font* font;
	FontRenderer* fontRenderer;
	wchar_t str[100];
};

