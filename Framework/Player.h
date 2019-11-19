#pragma once
#include "GameObject.h"
#include "AABBCollider.h"
#include "Scene.h"
#include "WallObject.h"
#include <vector>

//Player는 임의로 생성한 객체입니다.
//게임 내의 오브젝트는 GameObject객체를 상속받아 생성하여야합니다.
class Player :
	public GameObject
{
public:
	Vector2 velocity;
	float moveSpeed;
	int state;

	AABBCollider col;		//충돌을 관리할 변수
	std::vector<WallObject*> walls;

	int playerNumber; //1,2,3,4

	Player();					//Player생성자
	virtual void Update();		//Update: 매 프레임 호출됩니다.
	virtual void LateUpdate();	//LateUpdate: 매 프레임 Update, Render가 실행된 이후 호출됩니다.

	void setForceX(float x);
	void setForceY(float y);
	void setForce(Vector2 v);
	void addForceX(float x);
	void addForceY(float y);
	void addForce(Vector2 v);

};