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

	this->rotationAxis = Vector3::UnitY;
	this->rotationSpeed = 0;

	this->radius = 0.0f;
	this->isKatamari = false;
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
	
	AddComponent(renderComponent);
}

void GameObject::Initialize()
{
	for (const auto& component : components)
	{
		component->Initialize();
	}
}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);
	component->gameObject = this;
}

void GameObject::Update(float deltaTime)
{
	for (const auto& component : components)
	{
		component->Update(deltaTime);
	}

	/*
	for (const auto& gameObject : Game::GetInstance()->gameObjects)
	{
		if ((gameObject != Game::GetInstance()->gameObjects.at(0)) && (gameObject != Game::GetInstance()->gameObjects.at(1)))
		{
			if (Game::GetInstance()->gameObjects.at(1)->collisionSphere->Intersects(*(gameObject->collisionSphere)))
			{
				std::cout << gameObject << std::endl;
				//gameObject->parent = Game::GetInstance()->gameObjects.at(1);
			}
			else
			{
				std::cout << "NO" << std::endl;
			}
		}
	}
	*/

	if (isKatamari)
	{
		//Matrix rotationMatrix = Matrix::CreateFromYawPitchRoll(Game::GetInstance()->GetCamera()->GetCameraController()->yaw, 0, 0);
		
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::A))
		{

			//rotation *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Backward, rotationMatrix), rotationSpeed * deltaTime);
			//position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Left, rotationMatrix);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::D))
		{

			//rotation *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Forward, rotationMatrix), rotationSpeed * deltaTime);
			//position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Right, rotationMatrix);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::W))
		{

			//rotation *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Left, rotationMatrix), rotationSpeed * deltaTime);
			//position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Forward, rotationMatrix);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::S))
		{

			//rotation *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Right, rotationMatrix), rotationSpeed * deltaTime);
			//position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Backward, rotationMatrix);
		}
		//SetRotation(rotation);
	}
	else
	{
		//SetRotation(Quaternion::Identity);
	}
}