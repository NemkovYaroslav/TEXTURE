#include "KatamariDamacyGame.h"
#include "DebugObject.h"
#include "Camera.h"
#include "CameraController.h"
#include "FPSCameraController.h"
#include "KatamariControllerComponent.h"
#include "CollisionComponent.h"

KatamariDamacyGame::KatamariDamacyGame(LPCWSTR name, int clientWidth, int clientHeight) : Game(name, clientWidth, clientHeight)
{
	Game::CreateInstance(name, clientWidth, clientHeight);
	Initialize();
}

void KatamariDamacyGame::Initialize()
{
	DebugObject* grid = new DebugObject();
	grid->CreateGrid(20, 1.0f, Color(1.0f, 0.5f, 1.0f, 1.0f));

	GameObject* katamari = new GameObject();
	katamari->CreateSphere(1.0f);
	katamari->transformComponent->SetPosition(Vector3(0, katamari->radius, 0));
	KatamariControllerComponent* katamariController = new KatamariControllerComponent();
	katamariController->katamariSpeed = 5.0f;
	katamari->AddComponent(katamariController);
	CollisionComponent* katamariCollision = new CollisionComponent();
	katamari->collisionComponent = katamariCollision;
	katamari->AddComponent(katamariCollision);

	GameObject* camera = new GameObject();
	CameraComponent* cameraComponent = new CameraComponent();
	CameraArmControllerComponent* armCameraController = new CameraArmControllerComponent();
	camera->AddComponent(cameraComponent);
	armCameraController->aim = katamari->transformComponent;
	camera->AddComponent(armCameraController);
	Game::GetInstance()->currentCamera = cameraComponent;
	katamariController->cameraTransform = camera->transformComponent;

	/*
	GameObject* objectN;
	CollisionComponent* objectCollisionN;
	for (int i = 0; i < 50; i++)
	{
		objectN = new GameObject();
		objectN->CreateSphere(0.5f);
		objectCollisionN = new CollisionComponent();
		objectN->collisionComponent = objectCollisionN;
		objectN->AddComponent(objectCollisionN);
		objectN->transformComponent->SetPosition(Vector3( - 1.5f - objectN->radius * 2 * i, objectN->radius, 0));
		Game::GetInstance()->AddGameObject(objectN);
	}
	*/

	//GameObject* object = new GameObject();
	//object->CreateCube(20.0f);
	//object->transformComponent->SetRotation(Quaternion::CreateFromAxisAngle(Vector3::Right, DirectX::XM_PIDIV2));

	GameObject* object0 = new GameObject();
	object0->CreateMesh(1.0f);
	object0->transformComponent->SetPosition(Vector3(0,1,0));
	object0->transformComponent->SetRotation(Quaternion::CreateFromAxisAngle(Vector3::Right, DirectX::XM_PIDIV2));

	//Game::GetInstance()->AddGameObject(object);
	//Game::GetInstance()->AddGameObject(object0);

	Game::GetInstance()->AddGameObject(grid);
	Game::GetInstance()->AddGameObject(camera);
	Game::GetInstance()->AddGameObject(katamari);
	Game::GetInstance()->AddGameObject(object0);
}

void KatamariDamacyGame::Run()
{
	Game::GetInstance()->Run();
}