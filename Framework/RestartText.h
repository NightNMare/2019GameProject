#pragma once
#include "GameObject.h"
#include "FontRenderer.h"
class RestartText :
	public GameObject
{
public:
	RestartText();
	~RestartText();

	Font* font;
	FontRenderer* fontRenderer;
	wchar_t str[100];
};

