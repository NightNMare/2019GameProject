#pragma once
#include "Scene.h"
#include "Player2.h"
#include "WallObject.h"
#include "Trap.h"
#include "SaveObject.h"
#include "YouDieText.h"
#include "RestartText.h"
#include "JumpAdder.h"
#include "NextSceneBlock.h"

//����� ������ ��ü�� �ʿ��մϴ�.
//Scene�� ��ӹ޾� ��ü�� �����մϴ�.
class GameScene2 :
	public Scene
{
public:
	virtual void Initialize();		//��� Scene���� �ݵ�� Initialize�Լ��� �־���մϴ�. (�߻� Ŭ���� ����)
public:
	Player2* player;
	YouDieText* ydt;
	GameObject* white;
	RestartText* rst;
};
