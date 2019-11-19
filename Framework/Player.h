#pragma once
#include "GameObject.h"
#include "AABBCollider.h"
#include "Scene.h"
#include "WallObject.h"
#include <vector>

//Player�� ���Ƿ� ������ ��ü�Դϴ�.
//���� ���� ������Ʈ�� GameObject��ü�� ��ӹ޾� �����Ͽ����մϴ�.
class Player :
	public GameObject
{
public:
	Vector2 velocity;
	float moveSpeed;
	int state;

	AABBCollider col;		//�浹�� ������ ����
	std::vector<WallObject*> walls;

	int playerNumber; //1,2,3,4

	Player();					//Player������
	virtual void Update();		//Update: �� ������ ȣ��˴ϴ�.
	virtual void LateUpdate();	//LateUpdate: �� ������ Update, Render�� ����� ���� ȣ��˴ϴ�.

	void setForceX(float x);
	void setForceY(float y);
	void setForce(Vector2 v);
	void addForceX(float x);
	void addForceY(float y);
	void addForce(Vector2 v);

};