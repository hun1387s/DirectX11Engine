#include "Common.hlsl"


float4 PS_Std2D(VS_OUT _in) : SV_Target
{

    float4 vColor = g_tex.Sample(g_Sam, _in.vUV);
    //float4 vColor = g_tex.Sample(g_Sam, 0.5);
    return vColor;
}
