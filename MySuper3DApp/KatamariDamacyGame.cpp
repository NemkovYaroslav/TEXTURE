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
	katamari->CreateSphere(katamari->radius);
	KatamariControllerComponent* katamariController = new KatamariControllerComponent();
	katamariController->katamariSpeed = 5.0f;
	katamari->AddComponent(katamariController);
	katamari->AddComponent(new CollisionComponent(katamari->transformComponent->GetPosition(), katamari->radius));
	katamari->transformComponent->SetPosition(Vector3(0, katamari->radius, 0));

	GameObject* camera = new GameObject();
	CameraComponent* cameraComponent = new CameraComponent();
	CameraArmControllerComponent* armCameraController = new CameraArmControllerComponent();
	camera->AddComponent(cameraComponent);
	armCameraController->aim = katamari->transformComponent;
	camera->AddComponent(armCameraController);
	Game::GetInstance()->currentCamera = cameraComponent;
	katamariController->cameraTransform = camera->transformComponent;

	GameObject* object = new GameObject();
	object->radius = 0.5f;
	object->CreateSphere(object->radius);
	object->AddComponent(new CollisionComponent(object->transformComponent->GetPosition(), object->radius));
	object->transformComponent->SetPosition(Vector3(0, object->radius, -1.5f));

	Game::GetInstance()->AddGameObject(grid);
	Game::GetInstance()->AddGameObject(camera);
	Game::GetInstance()->AddGameObject(katamari);
	Game::GetInstance()->AddGameObject(object);
}

void KatamariDamacyGame::Run()
{
	Game::GetInstance()->Run();
}