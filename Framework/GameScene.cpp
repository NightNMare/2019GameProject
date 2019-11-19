#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"
#include "FontObject.h"

void GameScene::Initialize()
{
	TestObject* t = (TestObject*)PushBackGameObject(new TestObject());		//테스트용 오브젝트입니다.
	t->transform->SetPosition(200.0f,100.0f);

	player = (Player*)PushBackGameObject(new Player());			//오브젝트를 생성하고 싶다면, PushBackGameObject함수를 호출하여 생성합니다.
	player->enemy = t;

	PushBackGameObject(new FontObject());		//글씨 출력은 FontObject.h, FontObjct.cpp 참고
}
