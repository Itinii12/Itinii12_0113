#include "DxLib.h"

//色の定義
#define WHITE GetColor(255,255,255)
#define BLACK GetColor(0,0,0)
#define RED   GetColor(255,0,0)
#define GREEN GetColor(0,255,0)
#define BLUE  GetColor(0,0,255)

//フラグ名称定義
enum FLAG_NAME{
	GAME_END,
	TAROU_TALK,
	YAMADA_TALK,
	FLAG_MAX
};
bool FLAGS[FLAG_MAX];

//任意のメッセージを表示する関数
void disp_msg(const char* charname,const char* msg) {

	DrawBox(30, 295, 100, 325, BLUE, TRUE);	//NameBoxを描画
	DrawBox(30, 295, 100, 325, WHITE, FALSE);
	DrawBox(10, 320, 630, 470, BLUE, TRUE);	//MsgBoxを描画
	DrawBox(10, 320, 630, 470, WHITE, FALSE);

	DrawString(35, 300, charname, WHITE);	//キャラ名表示
	DrawString(20, 340, msg, WHITE);		//メッセージ表示

	ScreenFlip();
	WaitKey();
	ClearDrawScreen();
	ScreenFlip();
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//変数定義部
	int Result = 0;	 //スクリーン変更結果
	int Picture = 0; //画像表示ハンドル
	int x = 0;
	int y = 0;

	Result = ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1){  
		return -1;			  
	}
	SetDrawScreen(DX_SCREEN_BACK);

	if (Result == DX_CHANGESCREEN_OK) {
		DrawString(10, 10, "画面サイズ変更に成功しました\n続行するには何かキーを押してください...", WHITE);
		ScreenFlip();
	}

	WaitKey();
	ClearDrawScreen();

	//表示画像ハンドル読み込み
	Picture = LoadGraph("Picture/walking6_oldwoman.png");

	//メイン処理部開始
	while (FLAGS[GAME_END] == 0) {
		//キー処理部
		if (CheckHitKey(KEY_INPUT_UP) == 1)     y -= 10;	//上キー
		if (CheckHitKey(KEY_INPUT_DOWN) == 1)   y += 10;	//下キー
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1)  x += 10;	//右キー
		if (CheckHitKey(KEY_INPUT_LEFT) == 1)   x -= 10;	//左キー

		if (CheckHitKey(KEY_INPUT_Z) == 1) {				//Zキー
			disp_msg("HANAKO", "こんにちは！\n2行のテストメッセージです！");
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) FLAGS[GAME_END] = TRUE;	//ESCキー
		ClearDrawScreen();
		DrawExtendGraph(0+x, 0+y, 20+x, 20+y, Picture, TRUE);
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}