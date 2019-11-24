#include "stdafx.h"
#include "Player2.h"
#include "InputManager.h"
#include "GameScene.h"
#include "AnimationRenderer.h"
#include "ListAnimation.h"
#include "SheetAnimation.h"
#include "GameScene2.h"

#define dt TimeManager::GetDeltaTime()

Player2::Player2()
	:GameObject(L"player.png"),		//GameObject(animRenderer = new AnimationRenderer), �ִϸ��̼Ƿ������� ����մϴ�. �Ϲ����� �̹��� �������� ����Ͻô� ���� TestObject�� �����ϼ���.
	moveSpeed(3.0f*80.0f),
	col(*transform, Vector2(28.0f, 29.0f))// 32, 29
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
	transform->SetPosition(firstPos.x, firstPos.y);	//Player�� �ʱ� ��ġ ����

	//���� Scene�� ������ �����ôٸ� �Ʒ��� ���� ����Ͻø� �˴ϴ�.
	GameScene2& scene = (GameScene2&)Scene::GetCurrentScene();
}

void Player2::Update()
{
	//state = 0;
	//Ű �Է¹ޱ�
	//InputManager::GetMyKeyState(Ű��), 0���� Ŭ ���: ����, 0: ������ ����, -1: Ű�� ��� �� ������

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
			if (MaxjumpCount > jumpCount) {
				velocity.y = 10000.0f*dt;
			}

		}
		if (InputManager::GetMyKeyState(VK_SPACE)) {
			if (MaxjumpCount > jumpCount) {
				if (dtLimit <= 0.5f) {
					addForceY(-1 * jumpPower*dt);
					jumpPower -= 70000.0f*dt;
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
			jumpPower = 9000.0f;
		}
		addForceY(1350.0f* dt);
	}
	if (InputManager::GetKeyDown('R')) {
		RestartScene();
	}
	//Scene ��ȯ
	//if (InputManager::GetMyKeyState(VK_SPACE))
		//Scene::ChangeScene(new GameScene());

}

void Player2::LateUpdate()
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
					a->transform->SetScale(1.0f, 1.0f);
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

	if (isDie) { //�׾�����
		GameScene2& gs = ((GameScene2&)Scene::GetCurrentScene());
		gs.ydt->transform->SetScale(1.0f, 1.0f);
		gs.white->transform->SetScale(1.0f, 1.0f);
		gs.rst->transform->SetScale(1.0f, 1.0f);
	}
}

void Player2::RestartScene()
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
	GameScene2& gs = ((GameScene2&)Scene::GetCurrentScene());
	gs.ydt->transform->SetScale(0.0f, 0.0f);
	gs.white->transform->SetScale(0.0f, 0.0f);
	gs.rst->transform->SetScale(0.0f, 0.0f);
}


void Player2::setForceX(float x)
{
	velocity.x = x;
}

void Player2::setForceY(float y)
{
	velocity.y = y;

}

void Player2::setForce(Vector2 v)
{
	velocity = v;
}

void Player2::addForceX(float x)
{
	velocity.x += x;
}

void Player2::addForceY(float y)
{
	velocity.y += y;
}

void Player2::addForce(Vector2 v)
{
	velocity += v;
}