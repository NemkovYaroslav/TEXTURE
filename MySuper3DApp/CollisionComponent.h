#pragma once
#include "Component.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

class CollisionComponent : public Component
{
public:

	DirectX::BoundingSphere* sphereCollision;

	CollisionComponent(Vector3 position, float radius);
	virtual void Update(float deltaTime) override;
};

