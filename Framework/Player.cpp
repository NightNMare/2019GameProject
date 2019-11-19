#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "GameScene.h"
#include "AnimationRenderer.h"
#include "ListAnimation.h"
#include "SheetAnimation.h"
#include "TimeManager.h"

#define dt TimeManager::GetDeltaTime()

Player::Player()
	:GameObject(L"player.png"),		//GameObject(animRenderer = new AnimationRenderer), 애니메이션렌더러를 사용합니다. 일반적인 이미지 렌더러를 사용하시는 것은 TestObject를 참고하세요.
	moveSpeed(3.0f*80.0f),
	col(*transform, Vector2(32.0f, 29.0f))
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
	transform->SetPosition(300.0f, 300.0f);	//Player의 초기 위치 설정

	//현재 Scene을 얻어오고 싶으시다면 아래와 같이 사용하시면 됩니다.
	GameScene& scene = (GameScene&)Scene::GetCurrentScene();
}

void Player::Update()
{
	state = 0;
	//키 입력받기
	//InputManager::GetMyKeyState(키값), 0보다 클 경우: 눌림, 0: 눌리지 않음, -1: 키를 방금 막 떼었음
	if (InputManager::GetMyKeyState(VK_RIGHT)) {
		transform->position.x += moveSpeed * dt;
		transform->SetScale(1.0f, 1.0);
		state = 1;
	}
	if (InputManager::GetMyKeyState(VK_LEFT)) {
		transform->position.x -= moveSpeed * dt;
		transform->SetScale(-1.0f, 1.0);
		state = -1;
	}
	addForceY(1350.0f* dt);
	//Scene 전환
	//if (InputManager::GetMyKeyState(VK_SPACE))
		//Scene::ChangeScene(new GameScene());

}

void Player::LateUpdate()
{
	//static int count = 0;
	//if (col.Intersected(enemy->col2))
	//{
	//	printf("아야야 충돌중임%d\n",count++);
	//}

	transform->position += velocity * dt;
	//if (transform->position.y > 448 - 15) {
	//	velocity.y = 0;
	//	transform->position.y = 448 - 15;
	//}
	//for (auto a : walls) {
	//	if (a->rightbottom.x >= transform->position.x && transform->position.x >= a->lefttop.x) {
	//		if (state == 1) {//벽의 왼쪽과 플레이어가 부딪힘
	//			transform->position.x = a->lefttop.x;
	//			state = 0;
	//		}
	//		else if (state == -1) {//벽의 오른쪽과 플레이어가 부딪힘
	//			transform->position.x = a->rightbottom.x;
	//			state = 0;
	//		}
	//		if (a->rightbottom.y >= transform->position.y &&transform->position.y >= a->lefttop.y) {
	//			if (velocity.y > 0) {//벽의 위쪽과 부딪힘
	//				transform->position.y = a->lefttop.y-14.5f;
	//				velocity.y = 0;
	//			}
	//			else if (velocity.y < 0) {//벽의 밑쪽과 부딪힘
	//				transform->position.y = a->rightbottom.y+14.5f;
	//				velocity.y = 0;
	//			}
	//		}
	//	}
	//	/*if (col.Intersected(a->wallcol)) {
	//		std::cout << "ojife" << std::endl;
	//	}*/
	//}
	for (auto a : walls) {
		if (col.Intersected(a->wallcol)) {

			if (velocity.y > 0) {//벽의 위쪽과 부딪힘
				transform->position.y = a->lefttop.y - 14.6f;
				velocity.y = 0;
			}
			else if (velocity.y < 0) {//벽의 밑쪽과 부딪힘
				transform->position.y = a->rightbottom.y + 14.6f;
				velocity.y = 0;
			}
			if (state == 1) {//벽의 왼쪽과 플레이어가 부딪힘
				transform->position.x = a->lefttop.x - 16.1f;
			}
			else if (state == -1) {//벽의 오른쪽과 플레이어가 부딪힘
				transform->position.x = a->rightbottom.x + 16.1f;
			}

		}
		//if (col.Intersected(a->wallcol)) {
		//	std::cout << state << ":" << velocity.y << std::endl;

		//	//std::cout << "ojife" << std::endl;
		//}
	}
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
