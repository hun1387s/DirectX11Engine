#ifndef _COMMON
#define _COMMON

cbuffer TRANSFORM : register(b0)
{
    float4 Position;
    float4 Scale;
}

struct VS_IN
{
    float3 vPos : POSITION; //  0은 생략 가능 POSITION0, POSITION
    float4 vColor : COLOR;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
};

#endif
