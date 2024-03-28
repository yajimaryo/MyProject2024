
#include "common.hlsl" 

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float4 normal = normalize(In.Normal);

	float light = -dot(Light.Direction.xyz, normal.xyz);
	light = saturate(light);

	//テクスチャのピクセル色を取得
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse.rgb *= light + 0.3f;
	outDiffuse.a = In.Diffuse.a;


	//プリンフォン鏡面反射

	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev);

	float3 halfv = eyev + Light.Direction.xyz;
	halfv = normalize(halfv);

	float specular = -dot(halfv, normal.xyz);
	specular = saturate(specular);
	specular = pow(specular, 10);

	outDiffuse.rbg += specular;
}

