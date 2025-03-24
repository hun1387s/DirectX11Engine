#include "Common.hlsl"


VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    output.vPosition = float4((_in.vPos * Scale.xyz) + Position.xyz, 1.f) + Position;
    output.vColor = _in.vColor;
    return output;
}
