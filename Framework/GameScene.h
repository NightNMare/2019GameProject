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


//����� ������ ��ü�� �ʿ��մϴ�.
//Scene�� ��ӹ޾� ��ü�� �����մϴ�.
class GameScene :
	public Scene
{
public:
	virtual void Initialize();		//��� Scene���� �ݵ�� Initialize�Լ��� �־���մϴ�. (�߻� Ŭ���� ����)
public:
	Player* player;
	YouDieText* ydt;
	GameObject* white;
	RestartText* rst;
};
