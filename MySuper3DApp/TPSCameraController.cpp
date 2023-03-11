#include "TPSCameraController.h"

#include "Game.h"
#include "InputDevice.h"
#include "Camera.h"
#include "GameObject.h"

TPSCameraController::TPSCameraController() : CameraController()
{
	Game::GetInstance()->GetInputDevice()->MouseMove.AddRaw(this, &TPSCameraController::MouseEventHandler);
}

void TPSCameraController::Update(float deltaTime)
{
	Vector3 cameraPos        = Game::GetInstance()->gameObjects.at(1)->GetPosition();
	Vector3 cameraTarget     = Game::GetInstance()->GetCamera()->target;
	Vector3 cameraForward    = cameraTarget - cameraPos;
	cameraForward.Normalize();
	Matrix translateToArm    = Matrix::CreateTranslation(cameraForward * armLength + cameraPos);
	Matrix translateToZero   = Matrix::CreateTranslation( - cameraPos);
	rotationMatrix           = Matrix::CreateFromYawPitchRoll(yaw, pitch, 0);
	cameraForward            = Vector3::Transform(Vector3::Forward, rotationMatrix);
	Matrix translateToNewPos = Matrix::CreateTranslation( - cameraForward * armLength);
	cameraPos                = Vector3::Transform(cameraPos, translateToZero * rotationMatrix * translateToArm);
	cameraPos                = Vector3::Transform(cameraPos, translateToNewPos);
	
	cameraTarget             = cameraPos + Vector3::Transform(Vector3::Forward, rotationMatrix);

	Game::GetInstance()->GetCamera()->target = cameraTarget;
	Game::GetInstance()->GetCamera()->position = cameraPos;
}

void TPSCameraController::MouseEventHandler(const InputDevice::MouseMoveEventArgs& mouseData)
{
	yaw   -= mouseData.Offset.x * cameraRotationSpeed;
	pitch -= mouseData.Offset.y * cameraRotationSpeed;
	if (pitch >   DirectX::XM_PIDIV2 - 0.01) { pitch =   DirectX::XM_PIDIV2 - 0.01;  }
	if (pitch < - DirectX::XM_PIDIV2 + 0.01) { pitch = - DirectX::XM_PIDIV2 + 0.01; }
}