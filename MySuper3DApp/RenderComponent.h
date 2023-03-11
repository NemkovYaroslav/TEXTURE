#pragma once
#include "Component.h"

#include <vector>

using namespace DirectX::SimpleMath;

class RenderComponent : public Component
{
public:

    Matrix World;

    //RenderComponent(std::string shaderFileName, D3D_PRIMITIVE_TOPOLOGY topology);
    RenderComponent(std::string shaderFileName, D3D_PRIMITIVE_TOPOLOGY topology);
    RenderComponent(std::string shaderFileName, LPCWSTR textureFileName, D3D_PRIMITIVE_TOPOLOGY topology);
    RenderComponent() = delete;
    ~RenderComponent();

    void Initialize();
    void Update();

    void Draw();
    void AddGrid(int gridSize, float cellSize, Color color);
    void AddCube(float radius);
    void AddSphere(float radius, int sliceCount, int stackCount, DirectX::XMFLOAT4 color);

protected:

    std::string shaderFileName;
    D3D_PRIMITIVE_TOPOLOGY topology;
    std::vector<Vector4> points;
    std::vector<int> indices;

    bool isTexture;

    Microsoft::WRL::ComPtr<ID3D11VertexShader>    vertexShader;
    Microsoft::WRL::ComPtr<ID3D11PixelShader>     pixelShader;
    Microsoft::WRL::ComPtr<ID3D11InputLayout>     inputLayout;
    Microsoft::WRL::ComPtr<ID3D11Buffer>          vertexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer>          indexBuffer;
    Microsoft::WRL::ComPtr<ID3D11Buffer>          constBuffer;
    Microsoft::WRL::ComPtr<ID3D11RasterizerState> rastState;

    LPCWSTR textureFileName;
    Microsoft::WRL::ComPtr<ID3D11Resource> texture;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> textureView;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;

    D3D11_FILL_MODE fillMode;
};
