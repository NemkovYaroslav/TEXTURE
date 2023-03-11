#include "KatamariDamacyGame.h"
#include "DebugObject.h"
#include "Camera.h"
#include "CameraController.h"
#include "FPSCameraController.h"
#include "KatamariControllerComponent.h"

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
	katamariController->katamariSpeed = 25.0f;
	katamari->AddComponent(katamariController);

	GameObject* camera = new GameObject();
	CameraComponent* cameraComponent = new CameraComponent();
	//FPSCameraControllerComponent* cameraFPSController = new FPSCameraControllerComponent();
	CameraArmControllerComponent* armCameraController = new CameraArmControllerComponent();
	camera->AddComponent(cameraComponent);
	//camera->AddComponent(cameraFPSController);
	armCameraController->aim = katamari->transformComponent;
	camera->AddComponent(armCameraController);
	Game::GetInstance()->currentCamera = cameraComponent;
	Game::GetInstance()->AddGameObject(camera);
	//camera->transformComponent->SetPosition(Vector3(0, 3, -5));

	katamariController->cameraTransform = camera->transformComponent;

	//GameObject* object = new GameObject();
	//object->isKatamari = false;
	//object->radius = 0.5f;
	//object->CreateSphere(object->radius);

	Game::GetInstance()->AddGameObject(grid);
	Game::GetInstance()->AddGameObject(katamari);
	//Game::GetInstance()->AddGameObject(object);
}

void KatamariDamacyGame::Run()
{
	Game::GetInstance()->Run();
}