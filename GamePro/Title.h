#pragma once

enum MEN {
	MEN_00_Title,
	MEN_01_Action,
};

int sce = MEN::MEN_00_Title;
class Title{
public:
	void Out() {
		DrawGraph(0,0,Pic.title,TRUE);
		DrawFormatStringToHandle(0,0,Col.bra,Font.c[30],"Press Enter Key !");//c[]の[]内はフォント「サイズ」
		if (Key[KEY_INPUT_NUMPADENTER] == 1) { //エンターキーが押されたら
			sce = MEN::MEN_01_Action;
		}
	}
private:

};

Title tit;