#pragma once
#include "includes.h"

class TransformComponent;
class RenderComponent;
class Component;

using namespace DirectX::SimpleMath;

class GameObject
{
public:

	DirectX::BoundingSphere* collisionSphere;

	TransformComponent* transformComponent;
	RenderComponent* renderComponent;

	std::vector<Component*> components;

	float radius;

	GameObject(GameObject* parent = nullptr);
	~GameObject();

	virtual void Update(float deltaTime);
	virtual void Initialize();

	void AddComponent(Component* component);

	void CreateSphere(float radius, int sliceCount = 80, int stackCount = 80, DirectX::XMFLOAT4 color = Vector4::One);
};