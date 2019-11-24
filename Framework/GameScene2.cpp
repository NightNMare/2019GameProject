#include "stdafx.h"
#include "GameScene2.h"
#include "Framework.h"
#include <vector>

void GameScene2::Initialize()
{
	std::vector<WallObject*> walls;
	std::vector<Trap*> traps;
	std::vector<SaveObject*> saves;
	std::vector<JumpAdder*> jumps;
	std::vector<NextSceneBlock*> nexts;

	int winwidth = Framework::GetInstance().GetWinApp().GetScreenWidth();
	int winheight = Framework::GetInstance().GetWinApp().GetScreenHeight();

	int a[] = { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,1,
				1,0,0,0,0,3,0,4,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
				1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,
				1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};
	int b = 0;
	int savenum = 0;
	for (int i = 16; i <= winheight; i += 32) {
		for (int j = 16; j <= winwidth; j += 32) {
			if (a[b] == 1) {
				WallObject* w1 = (WallObject*)PushBackGameObject(new WallObject());

				w1->lefttop.x = j - 16.0f;
				w1->lefttop.y = i - 16.0f;
				w1->rightbottom.x = j + 16.0f;
				w1->rightbottom.y = i + 16.0f;

				w1->transform->SetPosition((float)j, (float)i);

				walls.push_back(w1);
			}
			else if (a[b] == 2) {
				Trap* trap = (Trap*)PushBackGameObject(new Trap());
				trap->transform->SetPosition((float)j, (float)i);
				traps.push_back(trap);
			}
			else if (a[b] == 3) {
				SaveObject* save = (SaveObject*)PushBackGameObject(new SaveObject());
				save->pos = { (float)j,(float)i };
				save->transform->SetPosition((float)j, (float)i);
				save->savenum = savenum++;
				saves.push_back(save);
			}
			else if (a[b] == 4) {
				JumpAdder* jump = (JumpAdder*)PushBackGameObject(new JumpAdder());
				jump->transform->SetPosition((float)j, (float)i);
				jumps.push_back(jump);
			}
			else if (a[b] == -1) {
				NextSceneBlock* next = (NextSceneBlock*)PushBackGameObject(new NextSceneBlock());
				next->transform->SetPosition((float)j + 32, (float)i);
				nexts.push_back(next);
			}

			b++;
		}
	}
	player = (Player2*)PushBackGameObject(new Player2());			//오브젝트를 생성하고 싶다면, PushBackGameObject함수를 호출하여 생성합니다.
	player->traps = traps;
	player->walls = walls;
	player->saves = saves;
	player->jumps = jumps;
	player->nexts = nexts;

	white = (GameObject*)PushBackGameObject(new GameObject(L"alphawhite65.png"));
	white->transform->SetPosition(320.0f, 240.0f);
	white->transform->SetScale(0.0f, 0.0f);

	ydt = (YouDieText*)PushBackGameObject(new YouDieText());
	ydt->transform->SetPosition(320.0f - 96.0f, 240.0f - 70.0f);
	ydt->transform->SetScale(0.0f, 0.0f);

	rst = (RestartText*)PushBackGameObject(new RestartText());
	rst->transform->SetPosition(320.0f - 128.0f, 240.0f);
	rst->transform->SetScale(0.0f, 0.0f);
}

