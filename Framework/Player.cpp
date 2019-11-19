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
	:GameObject(L"player.png"),		//GameObject(animRenderer = new AnimationRenderer), �ִϸ��̼Ƿ������� ����մϴ�. �Ϲ����� �̹��� �������� ����Ͻô� ���� TestObject�� �����ϼ���.
	moveSpeed(3.0f*80.0f),
	col(*transform, Vector2(32.0f, 29.0f))
{
	//�ִϸ��̼� ���� ���
	//ListAnimation(���� ���������� �ִϸ��̼��� ����)
	//SheetAnimation(���� ������ �߶� �ִϸ��̼��� ����, �ִϸ��̼� ��Ʈ ����)
	//�� �� �ϳ��� �����Ҵ��� ���� ����
	//~Animation Ŭ������ �� �ִϸ��̼��� ����ϴ� Ŭ�����Դϴ�.
	//ó�� �μ� state�� �ִϸ��̼� ��� ��ȣ�� �ǹ��մϴ�.(enum������ ���� ����)
	//state ���� ��ġ�� �ʰ� ���ּ���.
	//SheetAnimation* sanim = new SheetAnimation(1, 16.0f,L"sheet.png",128,128,16);	//�ִϸ��̼� ����, �ش� �ִϸ��̼��� state�� 1, �ʴ� 16ȸ �׸�
																					//pixelwidth, pixelheight�� �ִϸ��̼��� �߸� ����, ���θ� �ǹ��մϴ�.
																					//SheetAnimation.h ����

	//�ִϸ��̼��� AnimationRenderer�� ����ؾ� �ִϸ��̼� ��� ����
	//AnimationRenderer�� �ش� ��ü�� ��ϵ� ��� �ִϸ��̼��� �����մϴ�.
	//animRenderer->PushBackAnimation(sanim);

	//���� ����ϱ�
	//SoundEventŬ������ �����մϴ�.
	//SoundEvent��ü �ϳ��� �ϳ��� ���� ������ ����մϴ�.
	//se = new SoundEvent();		//se = new SoundEvent(L"test.wav"); ó�� ����� ���� �ֽ��ϴ�.
	//se->LoadFile(L"test.wav");		

	//��ü�� ��ġ, ����, ũ�������� transform�� ��ϵǾ��ֽ��ϴ�. Transform.h, GameObject.h ����
	transform->SetPosition(300.0f, 300.0f);	//Player�� �ʱ� ��ġ ����

	//���� Scene�� ������ �����ôٸ� �Ʒ��� ���� ����Ͻø� �˴ϴ�.
	GameScene& scene = (GameScene&)Scene::GetCurrentScene();
}

void Player::Update()
{
	state = 0;
	//Ű �Է¹ޱ�
	//InputManager::GetMyKeyState(Ű��), 0���� Ŭ ���: ����, 0: ������ ����, -1: Ű�� ��� �� ������
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
	//Scene ��ȯ
	//if (InputManager::GetMyKeyState(VK_SPACE))
		//Scene::ChangeScene(new GameScene());

}

void Player::LateUpdate()
{
	//static int count = 0;
	//if (col.Intersected(enemy->col2))
	//{
	//	printf("�ƾ߾� �浹����%d\n",count++);
	//}

	transform->position += velocity * dt;
	//if (transform->position.y > 448 - 15) {
	//	velocity.y = 0;
	//	transform->position.y = 448 - 15;
	//}
	//for (auto a : walls) {
	//	if (a->rightbottom.x >= transform->position.x && transform->position.x >= a->lefttop.x) {
	//		if (state == 1) {//���� ���ʰ� �÷��̾ �ε���
	//			transform->position.x = a->lefttop.x;
	//			state = 0;
	//		}
	//		else if (state == -1) {//���� �����ʰ� �÷��̾ �ε���
	//			transform->position.x = a->rightbottom.x;
	//			state = 0;
	//		}
	//		if (a->rightbottom.y >= transform->position.y &&transform->position.y >= a->lefttop.y) {
	//			if (velocity.y > 0) {//���� ���ʰ� �ε���
	//				transform->position.y = a->lefttop.y-14.5f;
	//				velocity.y = 0;
	//			}
	//			else if (velocity.y < 0) {//���� ���ʰ� �ε���
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

			if (velocity.y > 0) {//���� ���ʰ� �ε���
				transform->position.y = a->lefttop.y - 14.6f;
				velocity.y = 0;
			}
			else if (velocity.y < 0) {//���� ���ʰ� �ε���
				transform->position.y = a->rightbottom.y + 14.6f;
				velocity.y = 0;
			}
			if (state == 1) {//���� ���ʰ� �÷��̾ �ε���
				transform->position.x = a->lefttop.x - 16.1f;
			}
			else if (state == -1) {//���� �����ʰ� �÷��̾ �ε���
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
