#include "CollisionComponent.h"
#include "GameObject.h"
#include "Transform.h"

CollisionComponent::CollisionComponent(Vector3 position, float radius)
{
	this->sphereCollision = new DirectX::BoundingSphere();
	this->sphereCollision->Center = position;
	this->sphereCollision->Radius = radius;
}

void CollisionComponent::Update(float deltaTime)
{
	//sphereCollision->Center = gameObject->transformComponent->GetPosition();
}
