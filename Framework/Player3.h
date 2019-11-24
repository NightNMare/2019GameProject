#pragma once
#include "GameObject.h"
#include "AABBCollider.h"
#include "Scene.h"
#include "WallObject.h"
#include <vector>
#include "TimeManager.h"
#include "Trap.h"
#include "SaveObject.h"
#include "JumpAdder.h"
#include "NextSceneBlock.h"
#include "BeforeSceneBlock.h"
#define dt TimeManager::GetDeltaTime()
//Player는 임의로 생성한 객체입니다.
//게임 내의 오브젝트는 GameObject객체를 상속받아 생성하여야합니다.
class Player3 :
	public GameObject
{
public:
	Vector2 velocity;
	float moveSpeed;
	int state;

	AABBCollider col;		//충돌을 관리할 변수
	std::vector<WallObject*> walls;
	std::vector<Trap*> traps;
	std::vector<SaveObject*> saves;
	std::vector<JumpAdder*> jumps;
	std::vector<NextSceneBlock*> nexts;
	std::vector<BeforeSceneBlock*> befores;
	Vector2 firstPos = { 48.0f,432.0f };

	int playerNumber; //1,2,3,4
	int MaxjumpCount = 2;
	int jumpCount = 0;
	float dtLimit = 0.0f;
	float jumpPower = 9000.0f;
	bool IsinAir = false;
	bool isDie = false;
	int saveNumber = -1;

	Player3();					//Player생성자
	virtual void Update();		//Update: 매 프레임 호출됩니다.
	virtual void LateUpdate();	//LateUpdate: 매 프레임 Update, Render가 실행된 이후 호출됩니다.
	void RestartScene();

	void setForceX(float x);
	void setForceY(float y);
	void setForce(Vector2 v);
	void addForceX(float x);
	void addForceY(float y);
	void addForce(Vector2 v);
};