#ifndef _STD2D
#define _STD2D

cbuffer TRANSFORM : register(b0)
{
    float4 Position;
}

struct VS_IN
{
    float3 vPos : POSITION; // 0은 생략 가능 POSITION0, POSITION
    float4 vColor : COLOR;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
};

VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = float4(_in.vPos, 1.f) + Position;
    output.vColor = _in.vColor;
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    
    return _in.vColor;
}





#endif



