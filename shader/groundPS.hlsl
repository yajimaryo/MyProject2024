
#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureR : register(t1);
Texture2D g_TextureG : register(t2);
Texture2D g_TextureB : register(t3);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float3 color = g_Texture.Sample(g_SamplerState, In.TexCoord * 0.07).rgb;

	float3 R = g_TextureR.Sample(g_SamplerState, In.TexCoord).rgb;
	float3 G = g_TextureG.Sample(g_SamplerState, In.TexCoord).rgb;
	float3 B = g_TextureB.Sample(g_SamplerState, In.TexCoord).rgb;

	
	float3 result = lerp(G, R, color.r);
	result = lerp(result, B, color.b);
	result = lerp(result, G, color.g);

	outDiffuse.rgb = result;
	outDiffuse.a = 1.0f;
}
