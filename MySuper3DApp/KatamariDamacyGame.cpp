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
	katamari->radius = 1.0f;
	katamari->transformComponent->SetPosition(Vector3(0, katamari->radius, 0));
	katamari->CreateSphere(katamari->radius);
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

	GameObject* object0 = new GameObject();
	object0->radius = 0.5f;
	object0->CreateSphere(object0->radius);
	CollisionComponent* objectCollision0 = new CollisionComponent();
	object0->collisionComponent = objectCollision0;
	object0->AddComponent(objectCollision0);
	object0->transformComponent->SetPosition(Vector3(0, object0->radius, -1.5f));

	GameObject* object1 = new GameObject();
	object1->radius = 0.5f;
	object1->CreateSphere(object1->radius);
	CollisionComponent* objectCollision1 = new CollisionComponent();
	object1->collisionComponent = objectCollision1;
	object1->AddComponent(objectCollision1);
	object1->transformComponent->SetPosition(Vector3(0, object1->radius, 1.5f));

	Game::GetInstance()->AddGameObject(grid);
	Game::GetInstance()->AddGameObject(camera);
	Game::GetInstance()->AddGameObject(katamari);
	Game::GetInstance()->AddGameObject(object0);
	Game::GetInstance()->AddGameObject(object1);
}

void KatamariDamacyGame::Run()
{
	Game::GetInstance()->Run();
}