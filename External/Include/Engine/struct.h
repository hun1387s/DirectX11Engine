#pragma once

// 정점
// 3D 공간의 좌표를 나타내는 단위
struct Vertex
{
	Vector3 vPos;
	Vector4 vColor;
	Vector2 vUV;
};


// ConstantBuffer 관련
struct Transform
{
	Vector4 Position;
	Vector4 Scale;
	
};
