#ifndef _COMMON
#define _COMMON

cbuffer TRANSFORM : register(b0)
{
    float4 Position;
    float4 Scale;
}

SamplerState g_Sam : register(s0);

Texture2D g_tex : register(t0);

struct VS_IN
{
    float3 vPos : POSITION; //  0은 생략 가능 POSITION0, POSITION
    float4 vColor : COLOR;
    float2 vUV :TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

#endif
