#include "DxLib.h"

//色の定義
#define WHITE GetColor(255,255,255)
#define BLACK GetColor(0,0,0)
#define RED   GetColor(255,0,0)
#define GREEN GetColor(0,255,0)
#define BLUE  GetColor(0,0,255)

//任意のメッセージを表示する関数

void disp_message(char* charname,char* msg) {
	DrawBox(30, 300, 100, 330, BLUE, TRUE);			//NameBoxを描画
	DrawBox(10, 320, 630, 470, BLUE, TRUE);			//MsgBoxを描画
	DrawString(35, 305, charname, WHITE);
	DrawString(20, 350, msg, WHITE);
	WaitKey();
	DrawBox(0, 0, 1000, 1000, BLACK, TRUE);		//画面表示リセット
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int Result = 0;

	Result = ChangeWindowMode(TRUE);	//ウィンドウサイズ変更

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	DrawPixel(320, 240, WHITE);	// 点を打つ

	if (Result == DX_CHANGESCREEN_OK) {
		DrawString(10, 10, "Succsess", WHITE);	//ウィンドウサイズの変更に成功したなら、Succsessを表示
	}

	WaitKey();				// キー入力待ち

	DrawBox(0, 0, 1000, 1000, BLACK, TRUE);		//画面表示リセット

	WaitKey();				// キー入力待ち

	char name[10] = "Taro";
	char msg[50] = "ABCDE";

	disp_message(name,msg);
	//次回の課題はココでいちいち宣言しなおさないで、指定した名前とメッセージを表示させるコードにすること
	char name2[10]= "Hanako";
	char msg2[50] = "FGHJK";

	disp_message(name2, msg2);

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}