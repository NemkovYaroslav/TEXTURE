#include "Transform.h"

TransformComponent::TransformComponent() : Component()
{
	localPosition = Vector3::Zero;
	localRotation = Quaternion::Identity;
	parent = nullptr;
}

void TransformComponent::Initialize()
{

}

void TransformComponent::Update()
{

}

Vector3 TransformComponent::GetPosition() const
{
	return Vector3::Transform(localPosition, GetModel());
}

Quaternion TransformComponent::GetRotation() const
{
	if (parent)
	{
		return parent->GetRotation() * localRotation;
	}
	else
	{
		return localRotation;
	}
}

void TransformComponent::SetPosition(const Vector3& position)
{
	localPosition = Vector3::Transform(position, GetView());
}

void TransformComponent::SetRotation(const Quaternion& rotation)
{
	if (parent)
	{
		Quaternion quaternion;
		parent->GetRotation().Inverse(quaternion);
		localRotation = quaternion * rotation;
	}
	else
	{
		localRotation = rotation;
	}
}

Matrix TransformComponent::GetView() const
{
	if (parent)
	{
		return parent->GetView() * GetLocalView();
	}
	else
	{
		return GetLocalView();
	}
}

Matrix TransformComponent::GetLocalView() const
{
	return Matrix::CreateTranslation( - localPosition) * Matrix::CreateFromQuaternion(localRotation).Transpose();
}

Matrix TransformComponent::GetModel() const
{
	if (parent)
	{
		return GetLocalModel() * parent->GetModel();
	}
	else
	{
		return GetLocalModel();
	}
}

Matrix TransformComponent::GetLocalModel() const
{
	return Matrix::CreateFromQuaternion(localRotation) * Matrix::CreateTranslation(localPosition);
}
