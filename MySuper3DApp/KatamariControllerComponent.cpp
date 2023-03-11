#include "KatamariControllerComponent.h"
#include "GameObject.h"
#include "Transform.h"

// ÏÐÎÅÊÖÈß

KatamariControllerComponent::KatamariControllerComponent()
{
	this->katamariSpeed = 0.0f;
	this->cameraTransform = nullptr;
}

void KatamariControllerComponent::Update(float deltaTime)
{
	if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::A))
	{

	}
	if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::D))
	{

	}
	if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::W))
	{
		gameObject->transformComponent->SetRotation(gameObject->transformComponent->GetRotation() *
			Quaternion::CreateFromAxisAngle(cameraTransform->GetLeft(), katamariSpeed * deltaTime / DirectX::XM_2PI));

		//gameObject->transformComponent->SetPosition(gameObject->transformComponent->GetPosition() + cameraTransform->GetForward());
	}
	if (Game::GetInstance()->GetInputDevice()->IsKeyDown(Keys::S))
	{

	}
}
