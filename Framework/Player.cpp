#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "GameScene.h"
#include "AnimationRenderer.h"
#include "ListAnimation.h"
#include "SheetAnimation.h"
#include "GameScene2.h"

#define dt TimeManager::GetDeltaTime()

Player::Player()
	:GameObject(L"player.png"),		//GameObject(animRenderer = new AnimationRenderer), 애니메이션렌더러를 사용합니다. 일반적인 이미지 렌더러를 사용하시는 것은 TestObject를 참고하세요.
	moveSpeed(3.0f*80.0f),
	col(*transform, Vector2(28.0f, 29.0f))// 32, 29
{
	//애니메이션 적용 방법
	//ListAnimation(사진 여러장으로 애니메이션을 만듦)
	//SheetAnimation(사진 한장을 잘라서 애니메이션을 만듦, 애니메이션 시트 참조)
	//둘 중 하나를 동적할당을 통해 생성
	//~Animation 클래스는 한 애니메이션을 담당하는 클래스입니다.
	//처음 인수 state는 애니메이션 등록 번호를 의미합니다.(enum등으로 관리 가능)
	//state 값이 겹치지 않게 해주세요.
	//SheetAnimation* sanim = new SheetAnimation(1, 16.0f,L"sheet.png",128,128,16);	//애니메이션 생성, 해당 애니메이션의 state는 1, 초당 16회 그림
																					//pixelwidth, pixelheight는 애니메이션이 잘릴 가로, 세로를 의미합니다.
																					//SheetAnimation.h 참고

	//애니메이션을 AnimationRenderer에 등록해야 애니메이션 사용 가능
	//AnimationRenderer는 해당 객체에 등록된 모든 애니메이션을 관리합니다.
	//animRenderer->PushBackAnimation(sanim);

	//사운드 사용하기
	//SoundEvent클래스를 생성합니다.
	//SoundEvent객체 하나는 하나의 음악 파일을 담당합니다.
	//se = new SoundEvent();		//se = new SoundEvent(L"test.wav"); 처럼 사용할 수도 있습니다.
	//se->LoadFile(L"test.wav");		

	//객체의 위치, 각도, 크기조정은 transform에 등록되어있습니다. Transform.h, GameObject.h 참고
	transform->SetPosition(firstPos.x,firstPos.y);	//Player의 초기 위치 설정

	//현재 Scene을 얻어오고 싶으시다면 아래와 같이 사용하시면 됩니다.
	GameScene& scene = (GameScene&)Scene::GetCurrentScene();
}

void Player::Update()
{
	//state = 0;
	//키 입력받기
	//InputManager::GetMyKeyState(키값), 0보다 클 경우: 눌림, 0: 눌리지 않음, -1: 키를 방금 막 떼었음

	if (!isDie) {
		if (InputManager::GetMyKeyState(VK_RIGHT)) {
			transform->position.x += moveSpeed * dt;
			transform->SetScale(1.0f, 1.0);
		}
		if (InputManager::GetMyKeyState(VK_LEFT)) {
			transform->position.x -= moveSpeed * dt;
			transform->SetScale(-1.0f, 1.0);
		}
		if (InputManager::GetKeyDown(VK_SPACE)) {
			if (jumpCount == 0) {
				velocity.y = 0.0f;
			}
			else if (MaxjumpCount > jumpCount) {
				//velocity.y = 10000.0f*dt;
				velocity.y = 50.0f;
			}
			if (IsinAir&&jumpCount == 0) {
				velocity.y = 50.0f;
				//velocity.y = 10000.0f*dt;
			}
		}
		if (InputManager::GetMyKeyState(VK_SPACE)) {
			if (MaxjumpCount > jumpCount) {
				if (dtLimit <= 0.5f) {
					addForceY(-1 * jumpPower*dt);
					jumpPower -= 65000.0f*dt;
					if (jumpPower <= 0.0f)
						jumpPower = 0.0f;
					dtLimit += dt;
				}
			}
		}
		if (InputManager::GetKeyUp(VK_SPACE)) {
			if (jumpCount < MaxjumpCount)
				jumpCount++;
			if (!IsinAir) {
				IsinAir = true;
			}
			dtLimit = 0.0f;
			jumpPower = 8000.0f;
		}
		addForceY(1350.0f* dt);
	}
	if (InputManager::GetKeyDown('R')) {
		RestartScene();
	}
	//Scene 전환
	//if (InputManager::GetMyKeyState(VK_SPACE))
		//Scene::ChangeScene(new GameScene());
}

void Player::LateUpdate()
{
	IsinAir = true;
	for (auto& w : walls) {
		if (w->wallcol.Intersected(col)) {
			Vector2 vec = w->transform->position - transform->position;
			float angle = atan2(vec.x, vec.y);
			if (angle < -0.8f && angle >= -2.35f) {
				transform->position.x += moveSpeed * dt; //벽의 오른쪽과 부딪힘
			}
			else if (angle < 2.35f && angle >= 0.8f) {
				transform->position.x -= moveSpeed * dt; //벽의 왼쪽과 부딪힘
			}

		}
	}
	if (velocity.y >= 1200.0f)
		velocity.y = 1200.0f;
	transform->position.y += velocity.y * dt;

	for (auto& w : walls) {
		if (w->wallcol.Intersected(col)) {
			Vector2 vec = w->transform->position - transform->position;
			float angle = atan2(vec.x, vec.y);
			if (angle < 0.8f && angle >= -0.8f) { //바닥에 닿았을때
				velocity.y = 0;
				jumpCount = 0;
				IsinAir = false;
				//p->jumpCount = p->maxJumpCount;
				transform->position.y = w->transform->position.y - 16.0f - 14.5f;
			}
			//else if (angle < -0.8f && angle >= -2.35f) {
			//	transform->position.x += moveSpeed * dt; //벽의 오른쪽과 부딪힘
			//}
			//else if (angle < 2.35f && angle >= 0.8f) {
			//	transform->position.x -= moveSpeed * dt; //벽의 왼쪽과 부딪힘
			//}
			else if (angle > 2.35) {
				transform->position.y += moveSpeed * dt;
				velocity.y = 0;
			}
		}
	}


	for (auto& t : traps) {
		if (t->col->Intersected(col)) {
			isDie = true;
			transform->SetScale(0.0f, 0.0f);
		}
	}
	for (auto& s : saves) {
		if (s->col.Intersected(col)) {
			saveNumber = s->savenum;
			for (auto& a : saves) {
				if (a->savenum == saveNumber) {
					a->transform->SetScale(0.0f, 0.0f);
				}
				else {
					a->transform->SetScale(1.0f,1.0f);
				}
			}
		}
	}
	for (auto& j : jumps) {
		if (j->col.Intersected(col)) {
			if (!j->isUsed) {
				j->transform->SetScale(0.0f, 0.0f);
				j->isUsed = true;
				jumpCount--;
			}
		}
	}

	for (auto& n : nexts) {
		if (n->col.Intersected(col)) {
			Scene::ChangeScene(new GameScene2());
		}
	}

	if (isDie) { //죽었을때
		GameScene& gs = ((GameScene&)Scene::GetCurrentScene());
		gs.ydt->transform->SetScale(1.0f, 1.0f);
		gs.white->transform->SetScale(1.0f, 1.0f);
		gs.rst->transform->SetScale(1.0f, 1.0f);
	}
}

void Player::RestartScene()
{
	isDie = false;
	velocity.y = 0;
	transform->SetScale(1.0f, 1.0f);
	Vector2 tmp;
	if (saveNumber != -1) {
		tmp = saves[saveNumber]->pos;
	}
	else {
		tmp = firstPos;
	}
	transform->SetPosition(tmp.x, tmp.y);
	for (auto& j : jumps) {
		if (j->isUsed) {
			j->isUsed = false;
			j->transform->SetScale(1.0f, 1.0f);
		}
	}
	jumpCount = 0;
	GameScene& gs = ((GameScene&)Scene::GetCurrentScene());
	gs.ydt->transform->SetScale(0.0f, 0.0f);
	gs.white->transform->SetScale(0.0f, 0.0f);
	gs.rst->transform->SetScale(0.0f, 0.0f);
}


void Player::setForceX(float x)
{
	velocity.x = x;
}

void Player::setForceY(float y)
{
	velocity.y = y;

}

void Player::setForce(Vector2 v)
{
	velocity = v;
}

void Player::addForceX(float x)
{
	velocity.x += x;
}

void Player::addForceY(float y)
{
	velocity.y += y;
}

void Player::addForce(Vector2 v)
{
	velocity += v;
}
