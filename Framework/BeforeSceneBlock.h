#pragma once
#include "GameObject.h"
#include "AABBCollider.h"

class BeforeSceneBlock :
	public GameObject
{
public:
	BeforeSceneBlock();
	AABBCollider col;
	~BeforeSceneBlock();
};

