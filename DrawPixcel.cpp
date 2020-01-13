#include "DxLib.h"

//�F�̒�`
#define WHITE GetColor(255,255,255)
#define BLACK GetColor(0,0,0)
#define RED   GetColor(255,0,0)
#define GREEN GetColor(0,255,0)
#define BLUE  GetColor(0,0,255)

//�C�ӂ̃��b�Z�[�W��\������֐�

void disp_message(char* charname,char* msg) {
	DrawBox(30, 300, 100, 330, BLUE, TRUE);			//NameBox��`��
	DrawBox(10, 320, 630, 470, BLUE, TRUE);			//MsgBox��`��
	DrawString(35, 305, charname, WHITE);
	DrawString(20, 350, msg, WHITE);
	WaitKey();
	DrawBox(0, 0, 1000, 1000, BLACK, TRUE);		//��ʕ\�����Z�b�g
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int Result = 0;

	Result = ChangeWindowMode(TRUE);	//�E�B���h�E�T�C�Y�ύX

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	DrawPixel(320, 240, WHITE);	// �_��ł�

	if (Result == DX_CHANGESCREEN_OK) {
		DrawString(10, 10, "Succsess", WHITE);	//�E�B���h�E�T�C�Y�̕ύX�ɐ��������Ȃ�ASuccsess��\��
	}

	WaitKey();				// �L�[���͑҂�

	DrawBox(0, 0, 1000, 1000, BLACK, TRUE);		//��ʕ\�����Z�b�g

	WaitKey();				// �L�[���͑҂�

	char name[10] = "Taro";
	char msg[50] = "ABCDE";

	disp_message(name,msg);
	//����̉ۑ�̓R�R�ł��������錾���Ȃ����Ȃ��ŁA�w�肵�����O�ƃ��b�Z�[�W��\��������R�[�h�ɂ��邱��
	char name2[10]= "Hanako";
	char msg2[50] = "FGHJK";

	disp_message(name2, msg2);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I��
}