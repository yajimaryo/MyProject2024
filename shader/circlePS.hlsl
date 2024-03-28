
#include "common.hlsl"

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	float2 uv = In.TexCoord - 0.5f;

	outDiffuse.rgb = float3(0.0f, 1.0f, 0.2f);
	float dist = length(uv) / 0.5f;
	outDiffuse.a = (1.0f - step(1.0f, dist)) * step(0.0f, dist);

	if (outDiffuse.a == 1.0f)
	{
		outDiffuse = Param.baseColor;
	}

    float alpha = (1.0f - step(Param.hp.x, dist)) * step(Param.hp.x - 0.01f, dist);

    if (alpha == 1.0f)
    {
        outDiffuse = Param.diffColor;
    }

}
