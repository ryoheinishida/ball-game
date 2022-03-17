//�O���[�o��
cbuffer global
{
	matrix g_mW;//���[���h�s��
	matrix g_mWVP; //���[���h����ˉe�܂ł̕ϊ��s��
	float4 g_vLightDir;  //���C�g�̕����x�N�g��
	float4 g_Diffuse = float4(1, 0, 0, 0); //�g�U����(�F�j
};

//�\����
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR0;
};

//
//�o�[�e�b�N�X�V�F�[�_�[
//
VS_OUTPUT VS(float4 Pos : POSITION, float4 Normal : NORMAL)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.Pos = mul(Pos, g_mWVP);
	Normal.w = 0;//w=0�ňړ������𔽉f�����Ȃ��i�����̓V�F�[�_�[�O�����ڂ����j
	Normal = mul(Normal, g_mW);
	Normal = normalize(Normal);

	output.Color = 1.2 * g_Diffuse * dot(Normal, g_vLightDir);//���̎��̓����o�[�g�̗]����
	output.Color.a = 1.0;
	return output;
}

//
//�s�N�Z���V�F�[�_�[
//
float4 PS(VS_OUTPUT input) : SV_Target
{
	return input.Color;
}