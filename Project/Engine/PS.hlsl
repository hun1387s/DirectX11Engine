#include "Common.hlsl"


float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    
    return _in.vColor;
}
