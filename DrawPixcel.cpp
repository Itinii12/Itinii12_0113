//次の課題
//地形生成と当たり判定


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
bool FLAGS[FLAG_MAX];	//フラグ管理用の配列

//キャラ情報管理クラス
class Charactor {
public:
	int chara_pic;	//キャラ画像
	int chara_x;	//キャラ座標(x)
	int chara_y;	//キャラ座標(y)
	Charactor()
	{
		chara_pic = 0;
		chara_x = 0;
		chara_y = 0;
	}
};

//テストゲームで使うキャラクタ生成
Charactor Obatyan;

//任意のメッセージを表示する関数
void disp_msg(const char* charname,const char* msg) {

	//NameBoxを描画
	DrawBox(30, 295, 100, 325, BLUE, TRUE);	
	DrawBox(30, 295, 100, 325, WHITE, FALSE);
	//MsgBoxを描画
	DrawBox(10, 320, 630, 470, BLUE, TRUE);	
	DrawBox(10, 320, 630, 470, WHITE, FALSE);

	// キャラ名表示
	DrawString(35, 300, charname, WHITE);
	//メッセージ表示
	DrawString(20, 340, msg, WHITE);		
	ScreenFlip();
	//次のキー入力が早すぎると変な挙動になるのでちょっと待つ
	WaitTimer(100);	

	//Zキーが押されるまで表示し続ける
	while (CheckHitKey(KEY_INPUT_Z) == 0) {
		
	}

	//これだと全部一回消えちゃうので、キャラ画像を再表示させておく。
	ClearDrawScreen();
	DrawExtendGraph(0 + Obatyan.chara_x, 0 + Obatyan.chara_y, 30 + Obatyan.chara_x, 30 + Obatyan.chara_y,Obatyan.chara_pic, TRUE);
	ScreenFlip();
	//次のキー入力が早すぎると変な挙動になるのでちょっと待つ
	WaitTimer(100);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ローカル変数定義部

	//画面サイズをウィンドウモードに
	ChangeWindowMode(TRUE);	
	if (DxLib_Init() == -1){  
		return -1;			  
	}
	//描画画面を裏に
	SetDrawScreen(DX_SCREEN_BACK);

	//タイトル画面処理
	LoadGraphScreen(0,0,"Picture/title.bmp",TRUE);
	DrawString(100,260,"ゲームを開始するには何かキーを押してください...",BLACK);
	ScreenFlip();
	WaitKey();

	ClearDrawScreen();
	ScreenFlip();


	//表示画像ハンドル読み込み
	Obatyan.chara_pic= LoadGraph("Picture/walking6_oldwoman.png");

	//メイン処理部開始
	while (FLAGS[GAME_END] == 0) {
		//キー処理部
		if (CheckHitKey(KEY_INPUT_UP) == 1)     Obatyan.chara_y -= 10;	//上キー
		if (CheckHitKey(KEY_INPUT_DOWN) == 1)   Obatyan.chara_y += 10;	//下キー
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1)  Obatyan.chara_x += 10;	//右キー
		if (CheckHitKey(KEY_INPUT_LEFT) == 1)   Obatyan.chara_x -= 10;	//左キー
		//境界値処理
		if (Obatyan.chara_y <= 0)Obatyan.chara_y = 0;
		if (Obatyan.chara_x <= 0)Obatyan.chara_x = 0;
		if (Obatyan.chara_y >= 450)Obatyan.chara_y = 450;
		if (Obatyan.chara_x >= 610)Obatyan.chara_x = 610;

		if (CheckHitKey(KEY_INPUT_Z) == 1) {				//Zキー
			disp_msg("HANAKO", "こんにちは！\n2行のテストメッセージです！");
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) FLAGS[GAME_END] = TRUE;	//ESCキー

		WaitTimer(10);
		ClearDrawScreen();
		DrawExtendGraph(0+Obatyan.chara_x, 0+ Obatyan.chara_y, 30+ Obatyan.chara_x, 30+ Obatyan.chara_y, Obatyan.chara_pic, TRUE);
		ScreenFlip();
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}