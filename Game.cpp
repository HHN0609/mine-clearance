#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<Windows.h>
#include<iostream>
#include<sstream>
#include"Game.h"

using namespace sf;

Game::Game()
{
		 window_width = 860;
		 window_height = 600;
		
			 gamelvl = 2;
			 imgBGNo = 1;
			 imgSkinNo = 1;
		 window.create(sf::VideoMode(window_width, window_height), L"ɨ�� by hhn");
}

 Game::~Game()
{

}

void Game::Initial()
{
	window.setFramerateLimit(10); //ÿ������Ŀ��֡��
    gridSize = GRIDSIZE; //�����λ�õĿ�Ĵ�С


	switch (gamelvl)
		 {
		 case 1:
			 stageWidth = LVL1_WIDTH;
			 stageHeight = LVL1_HEIGHT;
			 mMineNum = LVL1_NUM;
			 break;
		 case 2:
			 stageWidth = LVL2_WIDTH;
			 stageHeight = LVL2_HEIGHT;
		     mMineNum = LVL2_NUM;
			 break;
		 case 3:
			 stageWidth = LVL3_WIDTH;
		     stageHeight = LVL3_HEIGHT;
			 mMineNum = LVL3_NUM;
			 break;
		 default:
			 break;
			 }

	 gameOver = false;
	 gameQuit = false;

	 isGameOverState = ncNO; //��ʼ����Ϸ�Ľ���״̬
	 mFlagCalc = 0; //��ʼ�����ӵ�����
	 isGameBegin = false; //��ʼ����Ϸ�Ƿ�ʼ
	 mTime = 0; //��ʼ����Ϸ���е�ʱ��
	
	mCornPoint.x = (window_width - stageWidth * GRIDSIZE) / 2; //������̨�����Ͻ�����
	mCornPoint.y = (window_height - stageHeight * GRIDSIZE) / 2;

	IniData(); //��ʼ������
	LoadMediaData(); //�����ز�
}

 void Game::IniData()//���ݳ�ʼ��
 {
	int i, j;
	
	for (j = 0; j < stageHeight; j++) //���п���Ϊ����δ���
	 for (i = 0; i < stageWidth; i++)
	 {
		 mGameData[j][i].mState = ncUNDOWN;
		 mGameData[j][i].isPress = false;
	 }
}
void Game::LoadMediaData()//�����ز�
{
	 std::stringstream ss;
	 ss << "data/images/BK0" << imgBGNo << ".jpg";
	 if (!tBackground.loadFromFile(ss.str()))
		 std::cout << "BK image û���ҵ�" << std::endl;

	 ss.str(""); //����ַ���

	 ss << "data/images/Game" << imgSkinNo << ".jpg";
	 if (!tTiles.loadFromFile(ss.str()))
		 std::cout << "Game Skin image û���ҵ�" << std::endl;

	 if (!tNum.loadFromFile("data/images/num.jpg"))
		 std::cout << "num.jpg û���ҵ�" << std::endl;

	 if (!tTimer.loadFromFile("data/images/jishiqi.jpg"))
		 std::cout << "jishiqi.jpg û���ҵ�" << std::endl;

	 if (!tCounter.loadFromFile("data/images/jishuqi.jpg"))
		 std::cout << "jishuqi.jpg û���ҵ�" << std::endl;

	 if (!tButtons.loadFromFile("data/images/button.jpg"))
		 std::cout << "button.jpg û���ҵ�" << std::endl;

	 if (!tGameOver.loadFromFile("data/images/gameover.jpg"))
		 std::cout << "gameover.jpg û���ҵ�" << std::endl;
	
	 sBackground.setTexture(tBackground);
	 sTiles.setTexture(tTiles);
	 sButtons.setTexture(tButtons);
	 sNum.setTexture(tNum);
	 sTimer.setTexture(tTimer);
	 sCounter.setTexture(tCounter);
	 sGameOver.setTexture(tGameOver);
 }

//���׺���
void Game::MineSet(int Py, int Px)
{

	int mCount, i, j, k, l;
	mCount = 0;
	
	srand(time(NULL)); //�õ�ǰϵͳʱ����Ϊ�����������������
	 //�������
	do {
		 bool flag = true;//����ѭ���Ƿ��׵��ж�����
		 k = rand() % stageHeight; //���������
		 l = rand() % stageWidth;

		 for (i = Py - 1; i < Py + 2; i++) //����һ�µ��������Χ 8 ����
		    for (j = Px - 1; j < Px + 2; j++)
			 if (i >= 0 && i < stageHeight && j >= 0 && j < stageWidth)//9��������̨�еĲ��ֽ��к����ж�
			    if (k == i && l == j)
			        flag = false;//������������� 9 ���񸲸Ƿ�Χ����Ҫ����

		if (flag && mGameData[k][l].mState == ncUNDOWN)
		{
			 mGameData[k][l].mState = ncMINE;
			 mGameData[k][l].mStateBackUp = ncMINE; //����״̬
			 mCount++;
		}
	} while (mCount != mMineNum);

	 //����ֵ
  for (i = 0; i < stageHeight; i++)
	for (j = 0; j < stageWidth; j++)
	{
		 if (mGameData[i][j].mState != ncMINE)
		 {
			 mCount = 0;
			 for (k = i - 1; k < i + 2; k++)
			   for (l = j - 1; l < j + 2; l++)
				 if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth)
				 {
				     if (mGameData[k][l].mState == ncMINE)
					 mCount++;
				 }//����(i,j)��Χ�׵���Ŀ
			
				 switch (mCount)//����״̬
				 {
				 case 0:
					 mGameData[i][j].mState = ncNULL; break;
				 case 1:
					 mGameData[i][j].mState = ncONE; break;
				 case 2:
					 mGameData[i][j].mState = ncTWO; break;
				 case 3:
					 mGameData[i][j].mState = ncTHREE; break;
				 case 4:
					 mGameData[i][j].mState = ncFOUR; break;
				 case 5:
					 mGameData[i][j].mState = ncFIVE; break;
				 case 6:
					 mGameData[i][j].mState = ncSIX; break;
				 case 7:
					 mGameData[i][j].mState = ncSEVEN; break;
				 case 8:
					 mGameData[i][j].mState = ncEIGHT; break;
				 }
		 }
	}

}

void Game::Input()
{
	sf::Event event;
	while (window.pollEvent(event))
		{
		if (event.type == sf::Event::Closed)
			{
			  window.close();//�������Ҫ�رգ���Ҫ�Լ�ȥ���� close()����
			gameQuit = true;
			}
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
			{
			   window.close();
			   gameQuit = true;
			}
		if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Left)
			{
			if (isGameOverState == ncNO)
				{
				if (mouseClickTimer.getElapsedTime().asMilliseconds() > 300 && event.type != sf::Event::MouseMoved)
					LButtonDown(Mouse::getPosition(window));//�����ε���ļ������ 300 ���룬���ж�Ϊ��굥��
				else
				    LButtonDblClk(Mouse::getPosition(window));//�����ε���ļ��С�� 300 ���룬���ж�Ϊ���˫��
				}
			}

		if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			if (isGameOverState == ncNO)
			    mouseClickTimer.restart();//��ʱ���¿�ʼ

		if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Right)
			if (isGameOverState == ncNO)
			   RButtonDown(Mouse::getPosition(window));//����һ�
	}


	if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
	{
		if (isGameOverState == ncNO)
		{
			mouseClickTimer.restart(); 
			Vector2i P1 = Mouse::getPosition(window);

		 //��ť�ж�
		   if (isGameBegin == false)
		   {
			if (ButtonRectEasy.contains(event.mouseButton.x, event.mouseButton.y))
				gamelvl = 1;
			if (ButtonRectNormal.contains(event.mouseButton.x, event.mouseButton.y))
				gamelvl = 2;
			if (ButtonRectHard.contains(event.mouseButton.x, event.mouseButton.y))
				gamelvl = 3;
			Initial();//��ʱˢ����̨
		   }
		}
		if (ButtonRectBG.contains(event.mouseButton.x, event.mouseButton.y))
		{
			imgBGNo++;
			if (imgBGNo > 7)//���ڱ���ͼ������ʱ��
				imgBGNo = 1;//�����ֻ�����ͼ
			LoadMediaData();
		}
		if (ButtonRectSkin.contains(event.mouseButton.x, event.mouseButton.y))
		{
			imgSkinNo++;
			if (imgSkinNo > 6)//����Ƥ��ͼ������ʱ��
				imgSkinNo = 1;//�����ֻ�Ƥ��ͼ
			LoadMediaData();
			}
		if (ButtonRectRestart.contains(event.mouseButton.x, event.mouseButton.y))
			Initial();
		if (ButtonRectQuit.contains(event.mouseButton.x, event.mouseButton.y))
			window.close(); gameQuit = true; 
	}

	/*sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			gameQuit = true;
		}
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			window.close();
			gameQuit = true;
		}

		if (event.type == sf::Event::EventType::MouseButtonPressed && event.key.code == sf::Mouse::Left)
		{
			if (mouseClickTimer.getElapsedTime().asMilliseconds()>500)
			{
              std::cout << "Mous::Left Pressed" << std::endl;
			}
			else
				std::cout << "Mous::Left Double Clicked" << std::endl;
		}
		if (event.type == sf::Event::EventType::MouseButtonReleased && event.key.code == sf::Mouse::Left)
		{
			mouseClickTimer.restart();
			std::cout << "Mous::Left Released" << std::endl;
		}
		if (event.type == sf::Event::EventType::MouseButtonPressed && event.key.code == sf::Mouse::Right)
		{
			std::cout << "Mous::Right Pressed" << std::endl;
		}
		if (event.type == sf::Event::EventType::MouseButtonReleased && event.key.code == sf::Mouse::Right)
		{
			std::cout << "Mous::Right Released" << std::endl;
		}
	}*/

}

void Game::RButtonDown(Vector2i mPoint) //����һ�
{
	int i, j;
	i = (mPoint.x - mCornPoint.x) / gridSize;
	j = (mPoint.y - mCornPoint.y) / gridSize;
	
	if (i >= 0 && i < stageWidth&&j >= 0 && j < stageHeight && isGameBegin == true)//����̨��  
																				   //����Ϸ��ʼ����һ����������֮���ܽ����Ҽ����
	{
		if (mGameData[j][i].isPress == false)
		{
			mGameData[j][i].isPress = true;
			mGameData[j][i].mStateBackUp = mGameData[j][i].mState;
			mGameData[j][i].mState = ncFLAG;
			mFlagCalc++;
		}
		else
		{
			if (mGameData[j][i].mState == ncFLAG)
			{
				mGameData[j][i].isPress = true;
				mGameData[j][i].mState = ncQ;
				mFlagCalc--;
			}
			else if (mGameData[j][i].mState == ncQ)
			{
				mGameData[j][i].isPress = false;
				mGameData[j][i].mState = mGameData[j][i].mStateBackUp;
			}
		}
	}
}
void Game::LButtonDown(Vector2i mPoint) //������
{
	int i, j;
	i = (mPoint.x - mCornPoint.x) / gridSize; //��ȡ��굱ǰ����Ŀ��λ��
	j = (mPoint.y - mCornPoint.y) / gridSize;
	
	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight) //�������̨��
	{
		if (isGameBegin == false)//�����Ϸδ��ʼ
		{
			isGameBegin = true;//��Ϸ��ʼ
			gameClock.restart();
			MineSet(j, i); //���֮�����������
		}
		if (mGameData[j][i].mState != ncFLAG)//���״̬��������
			if (mGameData[j][i].isPress == false)
			{
			 mGameData[j][i].isPress = true; //��ǰ�鱻���
			if (mGameData[j][i].mState == ncMINE) //�����ǰΪ��
			{
				isGameBegin = false;
				isGameOverState = ncLOSE;
				mGameData[j][i].mState = ncBOMBING;
				unCover(); //�ҿ�ʣ��δ���ҵ�����
				}
			if (mGameData[j][i].mState == ncNULL) //�����ǰ��Ϊ��
				NullClick(j, i); //����δ������Ŀտ�
			}
	}
}

void Game::LButtonDblClk(Vector2i mPoint) //������˫��
{
	int i, j, k, l, lvl;
	i = (mPoint.x - mCornPoint.x) / gridSize;
	j = (mPoint.y - mCornPoint.y) / gridSize;
	
	if (i >= 0 && i < stageWidth && j >= 0 && j < stageHeight)//�����ڷ�Χ��
	{
		if (mGameData[j][i].isPress == true)//����ѱ����
		{
			if (mGameData[j][i].mState != ncFLAG)//�����ǰ�鲻������
				for (k = j - 1; k < j + 2; k++)
				   for (l = i - 1; l < i + 2; l++)//������Χ 8 ������
				      if (k >= 0 && k < stageHeight && l >= 0 && l < stageWidth)
				      {
				         if (mGameData[k][l].mState == ncFLAG)//��������
					     {
					        if (mGameData[k][l].mStateBackUp != ncMINE)
						    {
						      isGameOverState = ncLOSE;
						      isGameBegin = false;
						      unCover();
						    }
				         }
				         else //���״̬��������
				         {
				            if (mGameData[k][l].isPress == false)
						    {
						        mGameData[k][l].isPress = true;
						    if (mGameData[k][l].mState == ncMINE)
							{
							   isGameOverState = ncLOSE;
						       isGameBegin = false;
							   mGameData[k][l].mState = ncBOMBING;
							   unCover();
							}
						    if (mGameData[k][l].mState == ncNULL)
							    NullClick(k, l);
						    }
				         }
				      }
		}
	}
}

void Game::Logic()
{
	isWin();
}

void Game::isWin()
{
	int i, j, c = 0;
	
	if (isGameOverState != ncLOSE)
	{
		for (i = 0; i < stageWidth; i++)
			for (j = 0; j < stageHeight; j++)
			{ 
				if (mGameData[j][i].isPress == false || mGameData[j][i].mState == ncFLAG)
				c++;
			}
	}
	
	if (c == mMineNum)//����������Ӷ�Ӧ�����ף���Ϸʤ��������
	{
		isGameBegin = false;
		isGameOverState = ncWIN;
	}
}

void Game::Draw()
{
	window.clear(); //����
					//���Ʊ���
	sBackground.setPosition(0, 0);
	window.draw(sBackground);
	//������̨
	DrawGrid();
	DrawButton();
	DrawTimer();
	DrawScore();
	if (isGameOverState)
		DrawGameEnd();
	window.display(); //����ʾ�����������ݣ���ʾ����Ļ�ϡ�SFML ���õ���˫�������
}

void Game::DrawGrid()
{
	for (int j = 0; j < stageHeight; j++)
		for (int i = 0; i < stageWidth; i++)
		{
			if (mGameData[j][i].isPress == true)
			{
				sTiles.setTextureRect(IntRect(mGameData[j][i].mState * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
				sTiles.setPosition(mCornPoint.x + i * GRIDSIZE, mCornPoint.y + j * GRIDSIZE);
			}
			else
			{
				sTiles.setTextureRect(IntRect(ncUNDOWN * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
				//sTiles.setTextureRect(IntRect(mGameData[j][i].mState * GRIDSIZE, 0, GRIDSIZE, GRIDSIZE));
				sTiles.setPosition(mCornPoint.x + i * GRIDSIZE, mCornPoint.y + j * GRIDSIZE);
			}
			window.draw(sTiles);
		}
}

void Game::DrawButton()
{
		Vector2i LeftCorner;
		int ButtonWidth = 60;
		int ButtonHeight = 36;
		int detaX;
		detaX = (window_width - ButtonWidth * 7) / 8; //7 ����ť�ڽ����ϵȷֿ��
		LeftCorner.y = window_height - GRIDSIZE * 3; //ָ���߶�

		//ButtonRectEasy
		LeftCorner.x = detaX;
		sButtons.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
		sButtons.setPosition(LeftCorner.x, LeftCorner.y); //���ð�ť��λ������
		ButtonRectEasy.left = LeftCorner.x;
		ButtonRectEasy.top = LeftCorner.y;
		ButtonRectEasy.width = ButtonWidth;
		ButtonRectEasy.height = ButtonHeight;
		window.draw(sButtons);

		//ButtonRectNormal
		LeftCorner.x = detaX * 2 + ButtonWidth;
		sButtons.setTextureRect(IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
		sButtons.setPosition(LeftCorner.x, LeftCorner.y); //���ð�ť��λ������
		ButtonRectNormal.left = LeftCorner.x;
		ButtonRectNormal.top = LeftCorner.y;
		ButtonRectNormal.width = ButtonWidth;
		ButtonRectNormal.height = ButtonHeight;
		window.draw(sButtons);

		//ButtonRectHard
		LeftCorner.x = detaX * 3 + ButtonWidth * 2;
		sButtons.setTextureRect(IntRect(2 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
		sButtons.setPosition(LeftCorner.x, LeftCorner.y); //���ð�ť��λ������
		ButtonRectHard.left = LeftCorner.x;
		ButtonRectHard.top = LeftCorner.y;
		ButtonRectHard.width = ButtonWidth;
		ButtonRectHard.height = ButtonHeight;
		window.draw(sButtons);

		//ButtonRectBG
		LeftCorner.x = detaX * 4 + ButtonWidth * 3;
		sButtons.setTextureRect(IntRect(3 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
		sButtons.setPosition(LeftCorner.x, LeftCorner.y); //���ð�ť��λ������
		ButtonRectBG.left = LeftCorner.x;
		ButtonRectBG.top = LeftCorner.y;
		ButtonRectBG.width = ButtonWidth;
		ButtonRectBG.height = ButtonHeight;
		window.draw(sButtons);

		//ButtonRectSkin
		LeftCorner.x = detaX * 5 + ButtonWidth * 4;
		sButtons.setTextureRect(IntRect(4 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
		sButtons.setPosition(LeftCorner.x, LeftCorner.y); //���ð�ť��λ������
		ButtonRectSkin.left = LeftCorner.x;
		ButtonRectSkin.top = LeftCorner.y;
		ButtonRectSkin.width = ButtonWidth;
		ButtonRectSkin.height = ButtonHeight;
		window.draw(sButtons);

		//ButtonRectRestart
		LeftCorner.x = detaX * 6 + ButtonWidth * 5;
		sButtons.setTextureRect(IntRect(5 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
		sButtons.setPosition(LeftCorner.x, LeftCorner.y); //���ð�ť��λ������
		ButtonRectRestart.left = LeftCorner.x;
		ButtonRectRestart.top = LeftCorner.y;
		ButtonRectRestart.width = ButtonWidth;
		ButtonRectRestart.height = ButtonHeight;
		window.draw(sButtons);

		//ButtonRectQuit
		LeftCorner.x = detaX * 7 + ButtonWidth * 6;
		sButtons.setTextureRect(IntRect(6 * ButtonWidth, 0, ButtonWidth, ButtonHeight));//��ȡ��ť����������
		sButtons.setPosition(LeftCorner.x, LeftCorner.y);
		//���ð�ť��λ������
		ButtonRectQuit.left = LeftCorner.x;
		ButtonRectQuit.top = LeftCorner.y;
		ButtonRectQuit.width = ButtonWidth;
		ButtonRectQuit.height = ButtonHeight;

		window.draw(sButtons);
}

void Game::DrawScore()
{
	Vector2i LeftCorner;
	LeftCorner.x = window_width - sCounter.getLocalBounds().width * 1.25;
	LeftCorner.y = sCounter.getLocalBounds().height * 0.5;
	sCounter.setPosition(LeftCorner.x, LeftCorner.y); //�������������ͼλ��
	window.draw(sCounter);
	
	int NumSize = sNum.getLocalBounds().height;
	LeftCorner.x = LeftCorner.x + sCounter.getLocalBounds().width - NumSize;
	LeftCorner.y = LeftCorner.y + sCounter.getLocalBounds().height * 0.5 - NumSize * 0.5;
	
	int mScore = mMineNum - mFlagCalc;
	//���Ƹ�λ��������
	int a = mScore % 10;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize)); //����ͼ��ȡ��Ӧ�����ַ���������ͼ
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//����ʮλ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSize;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize)); //����ͼ��ȡ��Ӧ�����ַ���������ͼ
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
	//���ư�λ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSize;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize)); //����ͼ��ȡ��Ӧ�����ַ���������ͼ
	sNum.setPosition(LeftCorner.x, LeftCorner.y);
	window.draw(sNum);
}

void Game::DrawTimer()
{
	Vector2i LeftCorner;
	LeftCorner.x = sTimer.getLocalBounds().width*0.25;
	LeftCorner.y = sTimer.getLocalBounds().height*0.5;
	sTimer.setPosition(LeftCorner.x, LeftCorner.y); //�������������ͼλ��
	window.draw(sTimer);

	if (isGameBegin)
	mTime = gameClock.getElapsedTime().asSeconds();
	int mScore = mTime;

	if (mScore > 999)
		mScore = 999;

	int NumSize = sNum.getLocalBounds().height;
	LeftCorner.x = LeftCorner.x + sTimer.getLocalBounds().width - NumSize * 1.5;
	LeftCorner.y = LeftCorner.y + sTimer.getLocalBounds().height*0.5 - NumSize * 0.5;
	//���Ƹ�λ��������
	int a = mScore % 10;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));//������ȡ��������
	sNum.setPosition(LeftCorner.x, LeftCorner.y);//�ں�λ��
	window.draw(sNum);
	//����ʮλ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSize;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));//������ȡ��������
	sNum.setPosition(LeftCorner.x, LeftCorner.y);//�ں�λ��
	window.draw(sNum);
	//���ư�λ��������
	mScore = mScore / 10;
	a = mScore % 10;
	LeftCorner.x = LeftCorner.x - NumSize;
	sNum.setTextureRect(IntRect(a * NumSize, 0, NumSize, NumSize));//������ȡ��������
	sNum.setPosition(LeftCorner.x, LeftCorner.y);//�ں�λ��
	window.draw(sNum);
}
void Game::DrawGameEnd()
{
	Vector2i LeftCorner;
	int ButtonWidth = 200;
	int ButtonHeight = sGameOver.getLocalBounds().height;
	LeftCorner.x = (window_width - ButtonWidth) / 2; //ָ����������
	LeftCorner.y = (window_height - ButtonHeight) / 2;//ָ����������

	sGameOver.setPosition(LeftCorner.x, LeftCorner.y); //���ð�ť��λ������
	
	if (isGameOverState == ncWIN)
		sGameOver.setTextureRect(IntRect(0 * ButtonWidth, 0, ButtonWidth, ButtonHeight)); //��ȡ��ť����������
	if(isGameOverState == ncLOSE)
		sGameOver.setTextureRect(IntRect(1 * ButtonWidth, 0, ButtonWidth, ButtonHeight)); //��ȡ��ť����������
	
	window.draw(sGameOver);
}

void Game::Run()
{
	do
	{
		Initial();
		while (window.isOpen() && gameOver == false)
		{
			Input();
			Logic();
			Draw();

		}
	} while (window.isOpen() && !gameQuit);

}