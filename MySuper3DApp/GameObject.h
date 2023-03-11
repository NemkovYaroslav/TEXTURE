#pragma once
#include "includes.h"

class TransformComponent;
class RenderComponent;
class Component;

using namespace DirectX::SimpleMath;

class GameObject
{
public:

	TransformComponent* transformComponent;
	RenderComponent* renderComponent;

	std::vector<Component*> components;

	Vector3 rotationAxis;
	float rotationSpeed;

	float radius;
	bool isKatamari;

	GameObject(GameObject* parent = nullptr);
	~GameObject();

	virtual void Update(float deltaTime);
	virtual void Initialize();

	void AddComponent(Component* component);

	void CreateSphere(float radius, int sliceCount = 80, int stackCount = 80, DirectX::XMFLOAT4 color = Vector4::One);
};