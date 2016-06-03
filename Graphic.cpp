#include "DxLib.h"

#include "Graphic.hpp"
#include <string.h>


Graphic::Graphic()
{
	LoadDivGraph("GRAPH/char_blue_7x9.png"  , 28, 7, 4, 7, 9, h_blueChar);
	LoadDivGraph("GRAPH/char_orange_7x9.png", 28, 7, 4, 7, 9, h_orangeChar);
	LoadDivGraph("GRAPH/num_blue_7x9.png"   , 10, 10, 1, 7, 9, h_blueNum);
	LoadDivGraph("GRAPH/num_orange_7x9.png" , 10, 10, 1, 7, 9, h_orangeNum);

	LoadDivGraph("GRAPH/blueFonts.png", 49, 7, 7, 7, 9, h_blueFonts);
	LoadDivGraph("GRAPH/orangeFonts.png", 49, 7, 7, 7, 9, h_orangeFonts);
}


Graphic::~Graphic()
{
	for (int i = 0; i < 28; i++)
	{
		DeleteGraph(h_blueChar[i]);
		DeleteGraph(h_orangeChar[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(h_blueNum[i]);
		DeleteGraph(h_orangeNum[i]);
	}
}


void Graphic::DrawMyString(const int PosiX, const int PosiY, char* sentence, const int space, const bool IsBlueColor)
{
	// ����t�H���g�摜�̕����̔ԍ��ɓ�����
	int num[20];
	int charNum = strlen(sentence);

	//�A�X�L�[�R�[�h���O�`�X�̐����ɕϊ�
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < charNum; j++)
		{
			if (sentence[j] == 65 + i)	num[j] = i;  // �A���t�@�x�b�g
			if (sentence[j] == 33)		num[j] = 26; // �u�I�v
			if (sentence[j] == 63)		num[j] = 27; // �u�H�v
		}
	}

	// �����̕`��
	for (int i = 0; i < charNum; i++)
	{
		if (IsBlueColor)
		{
			DrawRotaGraph(PosiX + (i * space), PosiY, 1.0, 0.0, h_blueChar[num[i]], true);
			continue;
		}
		DrawRotaGraph(PosiX + (i * space), PosiY, 1.0, 0.0, h_orangeChar[num[i]], true);
	}
}


void Graphic::DrawMyString2(const int PosiX, const int PosiY, char* sentence, const int space, const bool IsBlueColor, const double exrate)
{
	// ����t�H���g�摜�̕����̔ԍ��ɓ�����
	int num[500];
	int charNum = strlen(sentence);

	for (int i = 0; i < charNum; i++)
	{
		for (int j = 0; j < AllFontNum; j++)
		{
			// �A���t�@�x�b�g 0�Ԃ���
			for (int k = 0; k < 26; k++)
			{
				if (sentence[j] == 65 + k)
				{
					num[j] = k;
					break;
				}
			}

			// !
			if (sentence[j] == 33)
			{
				num[j] = 26;
				continue;
			}

			// ?
			if (sentence[j] == 63)
			{
				num[j] = 27;
				continue;
			}

			// ���� 29�Ԃ���
			for (int k = 0; k < 10; k++)
			{
				if(sentence[j] == 48 + k)
				{
					num[j] = 28 + k;
					break;
				}
			}
			// % (39)
			if (sentence[j] == 37)
			{
				num[j] = 38;
				continue;
			}

			// ^ (40)
			if (sentence[j] == 94)
			{
				num[j] = 39;
				continue;
			}

			// (
			if (sentence[j] == 40)
			{
				num[j] = 40;
				continue;
			}

			// )
			if (sentence[j] == 41)
			{
				num[j] = 41;
				continue;
			}

			// - (�n�C�t��)
			if (sentence[j] == 45)
			{
				num[j] = 42;
				continue;
			}

			// ;
			if (sentence[j] == 59)
			{
				num[j] = 43;
				continue;
			}

			// �n�[�g -> ��������h
			if (sentence[j] == 104)
			{
				num[j] = 44;
				continue;
			}

			// �ق� -> ��������s
			if (sentence[j] == 115)
			{
				num[j] = 45;
				continue;
			}

			// �c�C�b�^�[�}�[�N -> ��������t
			if (sentence[j] == 116)
			{
				num[j] = 46;
				continue;
			}

			// ���イ�� -> ��������k
			if (sentence[j] == 107)
			{
				num[j] = 47;
				continue;
			}

			// ��
			if (sentence[j] == 32)	num[j] = 48;
		}
	}

	// �����̕`��
	for (int i = 0; i < charNum; i++)
	{
		// �F
		if (IsBlueColor)
		{
			DrawRotaGraph(PosiX + (i * space), PosiY, exrate, 0.0, h_blueFonts[num[i]], true);
			continue;
		}

		// �I�����W
		DrawRotaGraph(PosiX + (i * space), PosiY, exrate, 0.0, h_orangeFonts[num[i]], true);
	}
}


void Graphic::DrawMyNumbers(const int PosiX, const int PosiY, char* sentence, const int space, const bool IsBlueColor)
{
	// ����t�H���g�摜�̕����̔ԍ��ɓ�����
	int num[20];
	int charNum = strlen(sentence);

	// �����̕����𐔎��t�H���g�ԍ��ɒu��
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < charNum; j++)
			if (sentence[j] == 48 + i)	num[j] = i; // 0 ~ 9 �̐���
	}

	// �����t�H���g�̕`��
	for (int i = 0; i < charNum; i++)
	{
		if (IsBlueColor)
		{
			DrawRotaGraph(PosiX + (i * space), PosiY, 1.0, 0.0, h_blueNum[num[i]], true);
			continue;
		}
		DrawRotaGraph(PosiX + (i * space), PosiY, 1.0, 0.0, h_orangeNum[num[i]], true);
	}
}


void Graphic::DrawMyNumbersNotChar(const int PosiX, const int PosiY, int number, const int space)
{
	
}


void Graphic::DrawScore(const int PosX, const int PosY, int score, const int space, const double exrate)
{
	for (int i = 0; i < 8; i++)
	{
		DrawRotaGraph(PosX - (space * i), PosY, exrate, 0.0, h_blueNum[score % 10], true);
		score /= 10;
	}
}