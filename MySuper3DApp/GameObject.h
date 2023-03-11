#pragma once
#include "includes.h"

#include "RenderComponent.h"
#include "Component.h"

using namespace DirectX::SimpleMath;

class GameObject
{
public:

	Matrix world;
	Vector3 position;
	Quaternion rotation;
	GameObject* parent;

	RenderComponent* renderComponent;
	std::vector<Component*> components;
	DirectX::BoundingSphere* collisionSphere;

	Vector3 rotationAxis;
	float rotationSpeed;

	float radius;
	bool isKatamari;

	GameObject(GameObject* parent = nullptr);

	virtual void Update(float deltaTime);
	virtual void Initialize();
	virtual void UpdateWorld();

	virtual Matrix GetWorld() const;
	virtual Quaternion GetRotation() const;
	virtual Vector3 GetPosition() const;
	virtual void SetWorld(const Vector3& position, const Quaternion& rotation);
	virtual void SetRotation(const Quaternion& rotation);
	virtual void SetPosition(const Vector3& position);

	void CreateSphere(float radius, int sliceCount = 80, int stackCount = 80, DirectX::XMFLOAT4 color = Vector4::One);
};