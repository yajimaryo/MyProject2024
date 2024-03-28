#include "common.hlsl"

[maxvertexcount(39)]//float’l‚ª1024ŒÂ‚Ü‚Åo—Ío—ˆ‚é

void main(triangle PS_IN In[3], inout TriangleStream<PS_IN> triStream)
{
    float moveForce = In[0].Position.w;
	
	for (int i = 0; i < 2; i++)
	{
		PS_IN outData;
        float step = 0.008f * (i + 1);

		matrix wvp = mul(World, View);
		wvp = mul(wvp, Projection);

		float3 vec1 = In[1].Position.xyz - In[0].Position.xyz;
		float3 vec2 = In[2].Position.xyz - In[0].Position.xyz;
		float3 normal = normalize(cross(vec1, vec2));

		for (int n = 0; n < 3; n++)
		{
            float3 pos = In[n].Position.xyz + normal * step * In[n].Normal.w;
            pos.y -= (moveForce) * (i + n + In[n].Normal.w / 10.0f);
			outData.Position = mul(float4(pos, 1.0), wvp);

			outData.Diffuse = In[n].Diffuse;
			outData.TexCoord = In[n].TexCoord;

			outData.Normal = mul(float4(In[n].Normal.xyz, 0.0), World);
			
			outData.WorldPosition = mul(float4(pos, 1.0), World);

			triStream.Append(outData);
        }
        triStream.RestartStrip();
    }
}