#pragma once
#include "Component.h"

using namespace DirectX::SimpleMath;

class TransformComponent : public Component
{
public:

    Vector3 localPosition;
    Quaternion localRotation;
    TransformComponent* parent;

    TransformComponent();

    void Initialize();
    void Update();

    Vector3 GetPosition() const;
    Quaternion GetRotation() const;
    void SetPosition(const Vector3& position);
    void SetRotation(const Quaternion& rotation);
    Matrix GetView() const;
    Matrix GetLocalView() const;
    Matrix GetModel() const;
    Matrix GetLocalModel() const;
};