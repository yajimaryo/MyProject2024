
#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureNormal : register(t1);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float4 normalMap = g_TextureNormal.Sample(g_SamplerState, (In.TexCoord * Param.diffColor.r) + Param.baseColor.rg);

	normalMap.rgb = normalMap.rgb * 2.0f - 1.0f;

	float4 normal;
	normal.x = -normalMap.r;
	normal.y = normalMap.b;
	normal.z = normalMap.g;
	normal.w = 0.0f;
	normal = normalize(normal);


	float light = -dot(Light.Direction.xyz, normal.xyz);
	light = saturate(light);

	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord * Param.diffColor.r);
	outDiffuse.rgb *= light;
	outDiffuse.a = Param.baseColor.a;

	float3 evev = In.WorldPosition.xyz - CameraPosition.xyz;
	evev = normalize(evev);
	float3 halfv = evev + Light.Direction.xyz;
	halfv = normalize(halfv);

	float specular = -dot(halfv, normal.xyz);
	saturate(specular);
	specular = pow((specular), Param.baseColor.b);
	outDiffuse.rgb = saturate(outDiffuse.rgb + specular);
}
