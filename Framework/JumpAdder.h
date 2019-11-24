#pragma once
#include "GameObject.h"
#include "AABBCollider.h"

class JumpAdder :
	public GameObject
{
public:
	JumpAdder();
	~JumpAdder();
	AABBCollider col;
	void addJump();
	bool isUsed = false;
};

