
#include "common.hlsl"

static const float pi = 3.1415926535f;

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	outDiffuse = float4(0.0f, 0.0f, 0.0f, 1.0f);
	
	float nowhp = Param.hp.x;
	float maxhp = Param.hp.y;
	float oldhp = Param.hp.z;

	float gauge = In.TexCoord.x * maxhp;

	//グレー部分を作る
	outDiffuse.rgb += Param.lostColor.rgb * step(oldhp, gauge);
	//緑部分を作る
	outDiffuse.rgb += Param.baseColor.rgb * (1.0f - step(nowhp, gauge));
	//赤部分を作る
	outDiffuse.rgb += Param.diffColor.rgb * (1.0f - step(oldhp, gauge)) * step(nowhp, gauge);

	outDiffuse.a = Param.baseColor.a;
}
