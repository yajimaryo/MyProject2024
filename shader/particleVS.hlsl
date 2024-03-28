
#include "common.hlsl"



void main(in VS_IN In, out PS_IN Out)
{
	Out.Position = In.Position;
    Out.Position.w = Param.baseColor.g;

	Out.Normal = In.Normal;
    Out.Normal.w = Param.baseColor.r;
	Out.TexCoord = In.TexCoord;
	Out.Diffuse = In.Diffuse;
    Out.WorldPosition = In.Position;

    //Out.Number = Param.baseColor;
}
