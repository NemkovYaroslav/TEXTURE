#include "GameObject.h"

#include "Transform.h"
#include "RenderComponent.h"
#include "Component.h"

#include "Game.h"
#include "Camera.h"
#include "CameraController.h"

GameObject::GameObject(GameObject* parent)
{
	this->transformComponent = new TransformComponent();
	AddComponent(transformComponent);
	this->renderComponent = nullptr;
	this->radius = 0.0f;
}

GameObject::~GameObject()
{
	for (auto component : components)
	{
		delete component;
	}
	components.clear();
}

void GameObject::CreateSphere(float radius, int sliceCount, int stackCount, DirectX::XMFLOAT4 color)
{
	this->radius = radius;
	//renderComponent = new RenderComponent("../Shaders/TexturedShader.hlsl", L".../Textures/Vladik.jpeg", D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	renderComponent = new RenderComponent("../Shaders/MyVeryFirstShader.hlsl", D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	renderComponent->AddSphere(radius, sliceCount, stackCount, color);
	collisionSphere = new DirectX::BoundingSphere();
	collisionSphere->Center = transformComponent->GetPosition();
	collisionSphere->Radius = radius;
	AddComponent(renderComponent);
}

void GameObject::Initialize()
{
	for (const auto& component : components)
	{
		component->Initialize();
	}
}

void GameObject::Update(float deltaTime)
{
	for (const auto& component : components)
	{
		component->Update(deltaTime);
	}

	/*
	std::cout
		<< " X: " << Game::GetInstance()->gameObjects.at(2)->transformComponent->GetPosition().x
		<< " Y: " << Game::GetInstance()->gameObjects.at(2)->transformComponent->GetPosition().y
		<< " Z: " << Game::GetInstance()->gameObjects.at(2)->transformComponent->GetPosition().z
	<< std::endl;
	*/

	Game::GetInstance()->gameObjects.at(2)->collisionSphere->Center = Game::GetInstance()->gameObjects.at(2)->transformComponent->GetPosition();

	std::cout
		<< " X: " << Game::GetInstance()->gameObjects.at(2)->collisionSphere->Center.x
		<< " Y: " << Game::GetInstance()->gameObjects.at(2)->collisionSphere->Center.y
		<< " Z: " << Game::GetInstance()->gameObjects.at(2)->collisionSphere->Center.z
	<< std::endl;

	/*
	// при столкновении
	if (true)
	{
		Game::GetInstance()->gameObjects.at(1); // катамари
		Game::GetInstance()->gameObjects.at(3); // объект

		Vector3 pos = Game::GetInstance()->gameObjects.at(3)->transformComponent->GetPosition();
		Quaternion rot = Game::GetInstance()->gameObjects.at(3)->transformComponent->GetRotation();
		Game::GetInstance()->gameObjects.at(3)->transformComponent->parent = Game::GetInstance()->gameObjects.at(1)->transformComponent;
		Game::GetInstance()->gameObjects.at(3)->transformComponent->SetPosition(pos);
		Game::GetInstance()->gameObjects.at(3)->transformComponent->SetRotation(rot);
	}
	*/
}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);
	component->gameObject = this;
}