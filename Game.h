#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>
#include<sstream>

using namespace sf;

#define GRIDSIZE 25
#define LVL1_WIDTH 9
#define LVL1_HEIGHT 9
#define LVL1_NUM 10
#define LVL2_WIDTH 16
#define LVL2_HEIGHT 16
#define LVL2_NUM 40
#define LVL3_WIDTH 30
#define LVL3_HEIGHT 16
#define LVL3_NUM 99

typedef enum GRIDSTATE
{
	ncNULL,
	ncUNDOWN,
	ncMINE,
	ncONE,
	ncTWO,
	ncTHREE,
	ncFOUR,
	ncFIVE,
	ncSIX,
	ncSEVEN,
	ncEIGHT,
	ncFLAG,
	ncQ,
	ncX,
	ncBOMBING,
	ncUNFOUND,
};

typedef enum GAMEOVERSTATE
{
	ncNO,
	ncWIN,
	ncLOSE,
};
class LEI
{
public:
	int mState;
	int mStateBackUp;
	bool isPress;

};

class Game
{
public:
	sf::RenderWindow window;
	Game();
	~Game();
	bool gameOver, gameQuit;
	bool mouseDlbClkReady;

	int window_width, window_height, stageWidth, stageHeight, mMineNum, mFlagCalc;
	int gamelvl, mTime;

	LEI mGameData[LVL3_HEIGHT][LVL3_WIDTH];
	bool isGameBegin;
	int isGameOverState;
	sf::Vector2i mCornPoint;

	int gridSize;                      //��Ĵ�С
	int imgBGNo, imgSkinNo;

	Texture tBackground, tTiles, tButtons,
		tNum, tTimer, tCounter, tGameOver;// �����������

	Sprite sBackground, sTiles, sButtons,
		sNum, sTimer, sCounter, sGameOver;// �����������

	sf::IntRect ButtonRectEasy, ButtonRectNormal, ButtonRectHard, ButtonRectBG, ButtonRectSkin, ButtonRectRestart, ButtonRectQuit;

	SoundBuffer sbWin, sbBoom;
	Sound soundWin, soundBoom;
	Music bkMusic;

	//SFML �� Clock ���ڶ���ʵ������ʱ�򼴿�ʼ��ʱ
	sf::Clock gameClock, mouseClickTimer;

	void Run(); //��Ϸ������ں���
	void Initial(); //��Ϸ��ʼ��
	void IniData();	
	void LoadMediaData();
	void MineSet(int Py, int Px);//����

	void Input(); //���뺯��
	void RButtonDown(Vector2i mPoint);//����һ�
	void LButtonDown(Vector2i mPoint);//������
	void LButtonDblClk(Vector2i mPoint);//������˫��

	void Logic(); //��Ϸ���߼��ж�
	void isWin();
	//void unCover();
	void NullClicke(int j,int i);

	void Draw(); //��Ϸ����������
	void DrawGrid();
	void DrawButton();
	void DrawScore();
	void DrawTimer();
	void DrawGameEnd();

	void unCover()
	{
		int i, j;
		for (j = 0; j < stageHeight; j++)
			for (i = 0; i < stageWidth; i++)
			{
				if (mGameData[j][i].isPress == false)
					if (mGameData[j][i].mState == ncMINE)
					{
						mGameData[j][i].isPress = true;
						mGameData[j][i].mState = ncUNFOUND;
					}
			}
	}

	void NullClick(int j, int i) //���ҿտ�
	{
		int k, l;
		for (k = j - 1; k < j + 2; k++)
			for (l = i - 1; l < i + 2; l++)
				if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth)
				{
					if (mGameData[k][l].isPress == false)
					{
						mGameData[k][l].isPress = true;
						if (mGameData[k][l].mState == ncNULL) //���״̬Ϊ��
							NullClick(k, l); //�ݹ����,��������
					}
				}
	}

};

