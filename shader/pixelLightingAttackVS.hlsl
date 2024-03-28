
#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
	matrix wvp;

	//���[���h�Ԋҁ��r���[�ϊ�
	wvp = mul(World, View);
	//wvp���v���W�F�N�V�����ϊ�
	wvp = mul(wvp, Projection);
	//���͂��ꂽ���_���W��ϊ����ďo�͐�֑��
	Out.Position = mul(In.Position, wvp);

	//���͂��ꂽUV���W���o�͐�֕ϊ�
	Out.TexCoord = In.TexCoord;


	float4 worldNormal, normal;
	//��]��񂾂���؂蔲�����߂̉�����
	normal = float4(In.Normal.xyz, 0.0f);
	//�@�������[���h�ϊ�
	worldNormal = mul(normal, World);

	worldNormal = normalize(worldNormal);

	Out.Normal = worldNormal;
	
	//���͂��ꂽ���_�J���[���o�͐�֕ϊ�
	Out.Diffuse = In.Diffuse;

	//Out.WorldPosition = float4(0.0, 0.0, 0.0, 0.0);

	//���[���h�ϊ��������_���W���o��
	Out.WorldPosition = mul(In.Position, World);
	
    //Out.Number = float4(0.0, 0.0, 0.0, 0.0);
}