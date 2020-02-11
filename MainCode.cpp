//���̉ۑ�
//�n�`�����Ɠ����蔻��

#include "DxLib.h"

//�F�̒�`
#define WHITE GetColor(255,255,255)
#define BLACK GetColor(0,0,0)
#define RED   GetColor(255,0,0)
#define GREEN GetColor(0,255,0)
#define BLUE  GetColor(0,0,255)

//�t���O���̒�`
enum FLAG_NAME {
	GAME_END,
	TAROU_TALK,
	YAMADA_TALK,
	FLAG_MAX
};
bool FLAGS[FLAG_MAX];	//�t���O�Ǘ��p�̔z��

//�L�������Ǘ��N���X
class Charactor {
public:
	int chara_pic;	//�L�����摜
	int chara_x;	//�L�������W(x)
	int chara_y;	//�L�������W(y)
	Charactor()
	{
		chara_pic = 0;
		chara_x = 0;
		chara_y = 0;
	}
};

//�e�X�g�Q�[���Ŏg���L�����N�^����
Charactor Obatyan;

//�C�ӂ̃��b�Z�[�W��\������֐�
void disp_msg(const char* charname, const char* msg) {
	//NameBox��`��
	DrawBox(30, 295, 100, 325, BLUE, TRUE);
	DrawBox(30, 295, 100, 325, WHITE, FALSE);
	//MsgBox��`��
	DrawBox(10, 320, 630, 470, BLUE, TRUE);
	DrawBox(10, 320, 630, 470, WHITE, FALSE);

	// �L�������\��
	DrawString(35, 300, charname, WHITE);
	//���b�Z�[�W�\��
	DrawString(20, 340, msg, WHITE);
	ScreenFlip();
	//���̃L�[���͂���������ƕςȋ����ɂȂ�̂ł�����Ƒ҂�
	WaitTimer(100);

	//Z�L�[���������܂ŕ\����������
	while (CheckHitKey(KEY_INPUT_Z) == 0) {
	}

	//���ꂾ�ƑS�����������Ⴄ�̂ŁA�L�����摜���ĕ\�������Ă����B
	ClearDrawScreen();
	DrawExtendGraph(0 + Obatyan.chara_x, 0 + Obatyan.chara_y, 30 + Obatyan.chara_x, 30 + Obatyan.chara_y, Obatyan.chara_pic, TRUE);
	ScreenFlip();
	//���̃L�[���͂���������ƕςȋ����ɂȂ�̂ł�����Ƒ҂�
	WaitTimer(100);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//���[�J���ϐ���`��

	//��ʃT�C�Y���E�B���h�E���[�h��
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) {
		return -1;
	}
	//�`���ʂ𗠂�
	SetDrawScreen(DX_SCREEN_BACK);

	//�^�C�g����ʏ���
	LoadGraphScreen(0, 0, "Picture/title.bmp", TRUE);
	DrawString(100, 260, "�Q�[�����J�n����ɂ͉����L�[�������Ă�������...", BLACK);
	ScreenFlip();
	WaitKey();

	ClearDrawScreen();
	ScreenFlip();

	//�\���摜�n���h���ǂݍ���
	Obatyan.chara_pic = LoadGraph("Picture/walking6_oldwoman.png");

	//���C���������J�n
	while (FLAGS[GAME_END] == 0) {
		//�L�[������
		if (CheckHitKey(KEY_INPUT_UP) == 1)     Obatyan.chara_y -= 10;	//��L�[
		if (CheckHitKey(KEY_INPUT_DOWN) == 1)   Obatyan.chara_y += 10;	//���L�[
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1)  Obatyan.chara_x += 10;	//�E�L�[
		if (CheckHitKey(KEY_INPUT_LEFT) == 1)   Obatyan.chara_x -= 10;	//���L�[
		//���E�l����
		if (Obatyan.chara_y <= 0)Obatyan.chara_y = 0;
		if (Obatyan.chara_x <= 0)Obatyan.chara_x = 0;
		if (Obatyan.chara_y >= 450)Obatyan.chara_y = 450;
		if (Obatyan.chara_x >= 610)Obatyan.chara_x = 610;

		if (CheckHitKey(KEY_INPUT_Z) == 1) {				//Z�L�[
			disp_msg("HANAKO", "����ɂ��́I\n2�s�̃e�X�g���b�Z�[�W�ł��I");
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) FLAGS[GAME_END] = TRUE;	//ESC�L�[

		WaitTimer(10);
		ClearDrawScreen();
		DrawExtendGraph(0 + Obatyan.chara_x, 0 + Obatyan.chara_y, 30 + Obatyan.chara_x, 30 + Obatyan.chara_y, Obatyan.chara_pic, TRUE);
		ScreenFlip();
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}