#pragma once

//色
class {
public:

	int whi;
	int bra;
	int red;
	int gre;
	int blu;

	void Read() {
		whi = GetColor(255, 255, 255);
		bra = GetColor(0, 0, 0);
		red = GetColor(255, 0, 0);
		gre = GetColor(0, 255, 0);
		blu = GetColor(0, 0, 255);
	}

private:

}Col;

//文字フォント
class {
public:
	int c[50 + 1];
	void Read() {
		for (int i = 0; i < 50 + 1; i++) {
			CreateFontToHandle("MS　ゴシック", i, 6, DX_FONTTYPE_NORMAL);
		}
	}
private:

}Font;

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
