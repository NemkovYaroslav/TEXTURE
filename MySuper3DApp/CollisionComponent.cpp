#include "CollisionComponent.h"
#include "GameObject.h"
#include "Transform.h"

CollisionComponent::CollisionComponent(Vector3 position, float radius)
{
	this->sphereCollision = new DirectX::BoundingSphere();
	this->sphereCollision->Center = Vector3::Zero;
	this->sphereCollision->Radius = 0.0f;
}

void CollisionComponent::Initialize()
{
	this->sphereCollision->Center = gameObject->transformComponent->GetPosition();
	this->sphereCollision->Radius = gameObject->radius;
}

void CollisionComponent::Update(float deltaTime)
{
	sphereCollision->Center = gameObject->transformComponent->GetPosition();
}
