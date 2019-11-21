#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"
#include "GameScene.h"
#include "AnimationRenderer.h"
#include "ListAnimation.h"
#include "SheetAnimation.h"

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
	//state = 0;
	//Ű �Է¹ޱ�
	//InputManager::GetMyKeyState(Ű��), 0���� Ŭ ���: ����, 0: ������ ����, -1: Ű�� ��� �� ������

	if (InputManager::GetMyKeyState(VK_RIGHT)) {
		transform->position.x += moveSpeed * dt;
		transform->SetScale(1.0f, 1.0);
	}
	if (InputManager::GetMyKeyState(VK_LEFT)) {
		transform->position.x -= moveSpeed * dt;
		transform->SetScale(-1.0f, 1.0);
	}
	if (InputManager::GetKeyDown(VK_SPACE)) {
		if (MaxjumpCount-1 == jumpCount) {
			velocity.y = 100.0f;
		}
	}
	static int a = 0;
	if (InputManager::GetMyKeyState(VK_SPACE)) {
		if (MaxjumpCount > jumpCount) {
			if (dtLimit <= 0.5f) { //���� ���� ���̵�
				std::cout << a++ << std::endl;
				addForceY(-1 * jumpPower*dt);
				jumpPower -= 70000.0f*dt;
				if (jumpPower <= 0.0f)
					jumpPower = 0.0f;
				dtLimit += dt;
			}
		}
	}
	if ( InputManager::GetKeyUp(VK_SPACE)) {
		a = 0;
		if (jumpCount < MaxjumpCount)
			jumpCount++;
		if (!IsinAir) {
			IsinAir = true;
		}
		dtLimit = 0.0f;
		jumpPower = 9000.0f;
	}
	addForceY(1350.0f* dt);
	
	//Scene ��ȯ
	//if (InputManager::GetMyKeyState(VK_SPACE))
		//Scene::ChangeScene(new GameScene());

}

void Player::LateUpdate()
{
	if (velocity.y >= 1200.0f)
		velocity.y = 1200.0f;
	transform->position.y += velocity.y * dt;


	for (auto& w : walls) {
		if (w->wallcol.Intersected(col)) {
			Vector2 vec = w->transform->position - transform->position;
			float angle = atan2(vec.x, vec.y);
			if (angle < 0.8f && angle >= -0.8f) { //�ٴڿ� �������
				velocity.y = 0;
				jumpCount = 0;
				IsinAir = false;
				//p->jumpCount = p->maxJumpCount;
				transform->position.y = w->transform->position.y - 16.0f - 14.5f;
			}
			else if (angle < -0.8f && angle >= -2.35f) {
				transform->position.x += moveSpeed * dt; //���� �����ʰ� �ε���
			}
			else if (angle < 2.35f && angle >= 0.8f) {
				transform->position.x -= moveSpeed * dt; //���� ���ʰ� �ε���
			}
			else {
				transform->position.y += moveSpeed * dt;
				velocity.y = 0;
			}
		}
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
