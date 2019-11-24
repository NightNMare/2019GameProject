#pragma once
#include "GameObject.h"
#include "AABBCollider.h"
class NextSceneBlock :
	public GameObject
{
public:
	NextSceneBlock();
	AABBCollider col;
	~NextSceneBlock();
};

