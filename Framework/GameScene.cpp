#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"
#include "Framework.h"
#include <vector>

void GameScene::Initialize()
{
	std::vector<WallObject*> walls;
	
	int winwidth = Framework::GetInstance().GetWinApp().GetScreenWidth();
	int winheight = Framework::GetInstance().GetWinApp().GetScreenHeight();
	
	int a[] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};
	int b = 0;
	for (int i = 16; i <= winheight; i += 32) {
		for (int j = 16; j <= winwidth; j += 32) {
			if (a[b++] == 1){
				WallObject* w1 = (WallObject*)PushBackGameObject(new WallObject());

				w1->lefttop.x = j - 16.0f;
				w1->lefttop.y = i - 16.0f;
				w1->rightbottom.x = j + 16.0f;
				w1->rightbottom.y = i + 16.0f;

				w1->transform->SetPosition((float)j, (float)i);

				walls.push_back(w1);
			}
		}
	}
	

	player = (Player*)PushBackGameObject(new Player());			//오브젝트를 생성하고 싶다면, PushBackGameObject함수를 호출하여 생성합니다.
	player->walls = walls;
	//player->enemy = t;
	//PushBackGameObject(new FontObject());		//글씨 출력은 FontObject.h, FontObjct.cpp 참고
}
