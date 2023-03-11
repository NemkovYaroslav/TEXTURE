#include "KatamariDamacyGame.h"
#include "DebugObject.h"

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
	katamari->isKatamari = true;
	katamari->radius = 1.0f;
	katamari->SetPosition(Vector3(0, katamari->radius, 0));
	katamari->CreateSphere(katamari->radius);
	katamari->rotationAxis = Vector3::Zero;
	katamari->rotationSpeed = 5;

	GameObject* object = new GameObject();
	object->isKatamari = false;
	object->radius = 0.5f;
	object->SetPosition(Vector3(3.0f, object->radius, 3.0f));
	object->CreateSphere(object->radius);

	Game::GetInstance()->AddGameObject(grid);
	Game::GetInstance()->AddGameObject(katamari);
	Game::GetInstance()->AddGameObject(object);
}

void KatamariDamacyGame::Run()
{
	Game::GetInstance()->Run();
}