
#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;

	//ワールド返還＊ビュー変換
	wvp = mul(World, View);
	//wvp＊プロジェクション変換
	wvp = mul(wvp, Projection);
	//入力された頂点座標を変換して出力先へ代入
	Out.Position = mul(In.Position, wvp);

	//入力されたUV座標を出力先へ変換
	Out.TexCoord = In.TexCoord;


	float4 worldNormal, normal;
	//回転情報だけを切り抜くための下準備
	normal = float4(In.Normal.xyz, 0.0f);
	//法線をワールド変換
	worldNormal = mul(normal, World);

	worldNormal = normalize(worldNormal);

	Out.Normal = worldNormal;
	
	//入力された頂点カラーを出力先へ変換
	Out.Diffuse = In.Diffuse;

	//Out.WorldPosition = float4(0.0, 0.0, 0.0, 0.0);

	//ワールド変換した頂点座標を出力
	Out.WorldPosition = mul(In.Position, World);
	
    //Out.Number = float4(0.0, 0.0, 0.0, 0.0);
}