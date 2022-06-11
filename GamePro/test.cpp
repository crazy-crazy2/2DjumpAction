#include "DxLib.h"

//#include "Sub.h"
//#include "Pic.h"
//#include "Title.h"
//#include "Stage.h"

#define WINDOW_WIDTH (1600)
#define WINDOW_HEIGHT (900)
#define WIN_POS_X 0
#define WIN_POS_Y 0

#define POS_MAX_X 6600
#define POS_MAX_Y 450
#define CELL 30

#define STAGE_MAX_X 6600 / 30
#define STAGE_MAX_Y 450 / 30


int camera_x;

enum e_Type {
    e_sky,//空ブロック
    e_earth,//地面ブロック
    e_player,//プレイヤー
};

struct Pic {
    int handle;
    int w; //幅
    int h; //厚み

};

enum e_Ani {
    e_Normal,
    e_Walk1,
    e_Walk2,
    e_Jump,
    e_End,
    e_Ani_Total,
};

struct Ract {
    int x;
    int y;
    int haba;
    int atumi;
    int syurui;
    double r;
    Pic p[e_Ani::e_Ani_Total];
    int ani;
    bool muki;
    int j;
    bool c;
};

struct Text {
    int kind;
    int x;
    int y;
};

Text** stage;

int STAGE_TOTAL;
int STAGE_WIDTH;
int STAGE_HEIGHT;

struct Color {
    unsigned int r;
    unsigned int g;
    unsigned int b;
};

int Key[256];

int GetKey() {
    char allKey[256];
    GetHitKeyStateAll(allKey);

    for (int i = 0; i < 256; i++)
    {
        if (allKey[i] == 1) {
            Key[i] += 1;
        }
        else if (allKey[i] == 0) {
            Key[i] = 0;
        }
    }
    return 0;
}

Color col;

//1次元配列のブロック
Ract* block;

void Block_Ini(Ract* b) {
    b->x = 0;
    b->y = 0;
    b->haba = 0;
    b->atumi = e_Type::e_sky;
    b->syurui = 0;
    b->r = 0.;
    
    for (int i = 0; i < e_Ani::e_Ani_Total; i++) {
        b->p[0].handle = 0;
        b->p[0].w = 0;
        b->p[0].h = 0;
    }

    b->ani = e_Ani::e_Normal;
    b->muki = FALSE;
    b->j = 0;
    b->c = FALSE;
}

void Game_Ini() {

    char name[] = { "C:/Users/USER/source/repos/GamePro/GamePro/stage_data2.txt" };
    FILE* fp = NULL;
    errno_t error = fopen_s(&fp,name,"r");

    //ステージ情報を取得
    if (fp != NULL && error == NULL) {
        //背景色の取得
        //fscanf_s(fp, "%d\n", &col.r);
        //fscanf_s(fp, "%d\n", &col.g);
        //fscanf_s(fp, "%d\n", &col.b);
        SetBackgroundColor(126, 179, 255);
        //SetBackgroundColor(col.r, col.g, col.b);
        ////ステージのサイズを取得
        //fscanf_s(fp, "%d\n", &STAGE_TOTAL);
        //fscanf_s(fp, "%d\n", &STAGE_WIDTH);
        //fscanf_s(fp, "%d\n", &STAGE_HEIGHT);
        STAGE_TOTAL = 3600;
        STAGE_WIDTH = 160;
        STAGE_HEIGHT = 18;
        //メモリ確保、動的配列
        stage = new Text * [STAGE_WIDTH];
        for (int i = 0; i < STAGE_WIDTH; i++) {
            stage[i] = new Text[STAGE_HEIGHT];
        }
        //ブロックのx番号、y番号、種類読み込み
        for (int y = 0; y < STAGE_HEIGHT; y++) {
            for (int x = 0; x < STAGE_WIDTH; x++) {
                fscanf_s(fp, "%d", &stage[x][y].kind);
                stage[x][y].x = x;
                stage[x][y].y = y;
            }
        }

        //ファイルを閉じる
        fclose(fp);
    }

    //メモリ確保
    block = new Ract[STAGE_TOTAL];

    //Text型からRact型に変換して、
    int i = 0;
    for (int y = 0; y < STAGE_HEIGHT; y++) {
        for (int x = 0; x < STAGE_WIDTH; x++) {
            if (stage[x][y].kind == e_Type::e_sky) { //ブロックなしの場合
                Block_Ini(&block[i]); //ブロック初期化
            }
            else { //ブロックありの場合
                switch (stage[x][y].kind) {
                case e_Type::e_earth:

                    //ブロック画像ロード
                    block[i].p[0].handle = LoadGraph("C:/Users/USER/source/repos/GamePro/GamePro/back.png");

                    //ブロックの向き
                    block[i].muki = FALSE;
                    //キャラクタかどうか
                    block[i].c = FALSE;

                    break;
                case e_Type::e_player:

                    block[i].p[e_Ani::e_Normal].handle = LoadGraph("C:/Users/USER/source/repos/GamePro/GamePro/obake_run_01.png");
                    block[i].p[e_Ani::e_Walk1].handle = LoadGraph("C:/Users/USER/source/repos/GamePro/GamePro/obake_run_02.png");
                    block[i].p[e_Ani::e_Walk2].handle = LoadGraph("C:/Users/USER/source/repos/GamePro/GamePro/obake_run_03.png");
                    block[i].p[e_Ani::e_Jump].handle = LoadGraph("C:/Users/USER/source/repos/GamePro/GamePro/obake_run_02.png");
                    block[i].p[e_Ani::e_End].handle = LoadGraph("C:/Users/USER/source/repos/GamePro/GamePro/obake_end.png");

                    block[i].muki = FALSE;

                    block[i].c = TRUE;
                }
                //ブロック写真から幅と厚みを取得
                GetGraphSize(block[i].p[0].handle, &block[i].p[0].w, &block[i].p[0].h);
                //幅と厚みを代入
                block[i].haba = block[i].p[0].w;
                block[i].atumi = block[i].p[0].h;

                block[i].x = stage[x][y].x * 50;
                block[i].x = stage[x][y].x * 50;
                block[i].syurui = stage[x][y].kind;
                block[i].r = 0.;
                block[i].r = 0.;
                block[i].ani = e_Ani::e_Normal;

            }
            i++;
        }
    }
    //メモリ解放
    for (int i = 0; i < STAGE_WIDTH; i++) {
        delete[] stage[i];
    }
    delete[] stage;

    camera_x = 0;
}

void Game_Draw() {
    for (int i = 0; i < STAGE_TOTAL; i++) {
        switch (block[i].muki) {
        case FALSE:
            DrawTurnGraph(block[i].x + camera_x, block[i].y, block[i].p[0].handle, TRUE);
            break;
        case TRUE:
            DrawGraph(block[i].x + camera_x, block[i].y, block[i].p[0].handle, TRUE);
            break;


        }


    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    SetWindowInitPosition(WIN_POS_X, WIN_POS_Y);
    ChangeWindowMode(TRUE); //ウィンドウモードで起動
    DxLib_Init();
    
    SetMainWindowText("まりおもどき");
    SetWindowInitPosition(0, 0);
    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
    SetDrawScreen(DX_SCREEN_BACK);

    Game_Ini();

    while (ScreenFlip() == 0 && ClearDrawScreen() == 0 && ProcessMessage() == 0 && GetKey() == 0) {


    }

    //WaitKey(); //キー入力待ち

    DxLib_End(); //DxLibの終了

    return 0;

}

