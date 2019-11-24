#pragma once
#include "Scene.h"
#include "Player.h"
#include "WallObject.h"
#include "Trap.h"
#include "SaveObject.h"
#include "YouDieText.h"
#include "RestartText.h"
#include "JumpAdder.h"
#include "NextSceneBlock.h"


//장면을 관리할 객체가 필요합니다.
//Scene을 상속받아 객체를 생성합니다.
class GameScene :
	public Scene
{
public:
	virtual void Initialize();		//모든 Scene에는 반드시 Initialize함수가 있어야합니다. (추상 클래스 참고)
public:
	Player* player;
	YouDieText* ydt;
	GameObject* white;
	RestartText* rst;
};
