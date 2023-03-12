#pragma once
#include "includes.h"

class TransformComponent;
class RenderComponent;
class CollisionComponent;
class Component;

using namespace DirectX::SimpleMath;

class GameObject
{
public:

	TransformComponent* transformComponent;
	RenderComponent* renderComponent;
	CollisionComponent* collisionComponent;

	std::vector<Component*> components;

	float radius;

	GameObject(GameObject* parent = nullptr);
	~GameObject();

	virtual void Update(float deltaTime);
	virtual void Initialize();

	void AddComponent(Component* component);

	void CreateSphere(float radius, int sliceCount = 80, int stackCount = 80, DirectX::XMFLOAT4 color = Vector4::One);
	void CreateCube(float radius);
	void CreateMesh(float scaleRate);
};