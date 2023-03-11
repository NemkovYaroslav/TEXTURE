#include "GameObject.h"

#include "Game.h"
#include "Camera.h"
#include "CameraController.h"

GameObject::GameObject(GameObject* parent)
{
	this->world = Matrix::Identity;
	this->position = Vector3::Zero;
	this->rotation = Quaternion::Identity;
	this->parent = parent;

	this->renderComponent = nullptr;
	this->collisionSphere = nullptr;

	this->rotationAxis = Vector3::UnitY;
	this->rotationSpeed = 0;

	this->radius = 0.0f;
	this->isKatamari = false;
}

void GameObject::CreateSphere(float radius, int sliceCount, int stackCount, DirectX::XMFLOAT4 color)
{
	this->radius = radius;
	renderComponent = new RenderComponent("../Shaders/MyVeryFirstShader.hlsl", D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	renderComponent->AddSphere(radius, sliceCount, stackCount, color);
	components.push_back(renderComponent);
}

void GameObject::Initialize()
{
	for (const auto& component : components)
	{
		component->Initialize();
	}

	collisionSphere = new DirectX::BoundingSphere();
	collisionSphere->Center = position;
	collisionSphere->Radius = radius;
}

void GameObject::Update(float deltaTime)
{
	for (const auto& component : components)
	{
		component->Update();
	}

	///*
	for (const auto& gameObject : Game::GetInstance()->gameObjects)
	{
		if ((gameObject != Game::GetInstance()->gameObjects.at(0)) && (gameObject != Game::GetInstance()->gameObjects.at(1)))
		{
			if (Game::GetInstance()->gameObjects.at(1)->collisionSphere->Intersects(*(gameObject->collisionSphere)))
			{
				std::cout << gameObject << std::endl;
				gameObject->parent = Game::GetInstance()->gameObjects.at(1);
			}
			else
			{
				std::cout << "NO" << std::endl;
			}
		}
	}
	//*/

	if (isKatamari)
	{
		Matrix rotationMatrix = Matrix::CreateFromYawPitchRoll(Game::GetInstance()->GetCamera()->GetCameraController()->yaw, 0, 0);
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::A))
		{
			rotation *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Backward, rotationMatrix), rotationSpeed * deltaTime);
			position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Left, rotationMatrix);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::D))
		{
			rotation *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Forward, rotationMatrix), rotationSpeed * deltaTime);
			position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Right, rotationMatrix);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::W))
		{
			rotation *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Left, rotationMatrix), rotationSpeed * deltaTime);
			position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Forward, rotationMatrix);
		}
		if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::S))
		{
			rotation *= Quaternion::CreateFromAxisAngle(Vector3::Transform(Vector3::Right, rotationMatrix), rotationSpeed * deltaTime);
			position += deltaTime * rotationSpeed * Vector3::Transform(Vector3::Backward, rotationMatrix);
		}
		SetRotation(rotation);
	}
	else
	{
		SetRotation(Quaternion::Identity);
	}

	renderComponent->World = GetWorld();

	collisionSphere->Center = position;
	collisionSphere->Radius = radius;
}

void GameObject::UpdateWorld()
{
	world = Matrix::CreateFromQuaternion(rotation) * Matrix::CreateTranslation(position);
	if (parent)
	{
		//rotation = relRot * Game::GetInstance()->gameObjects.at(1)->rotation;
		//position = Game::GetInstance()->gameObjects.at(1)->position + Vector3::Transform(relPos, relRot * Game::GetInstance()->gameObjects.at(1)->rotation);
		world *= parent->GetWorld();
	}
	if (!isKatamari)
	{
		std::cout << " X: " << position.x << " Y: " << position.y << " Z: " << position.z << std::endl;
	}
}

Matrix GameObject::GetWorld() const        { return world;    }
Quaternion GameObject::GetRotation() const { return rotation; }
Vector3 GameObject::GetPosition() const    { return position; }
void GameObject::SetWorld(const Vector3& position, const Quaternion& potation) { this->rotation = rotation; this->position = position; UpdateWorld(); }
void GameObject::SetRotation(const Quaternion& rotation)                       { this->rotation = rotation;                            UpdateWorld(); }
void GameObject::SetPosition(const Vector3& position)                          { this->position = position;                            UpdateWorld(); }