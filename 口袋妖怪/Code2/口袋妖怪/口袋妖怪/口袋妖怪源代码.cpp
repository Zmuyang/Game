#include <iostream>
#include <conio.h>
#include <windows.h>
#include <graphics.h>
#include <cmath>
#include <time.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "hanshuku.h"

using namespace std;

#define window_height 480
#define window_width 640
#define pokemon_number 30 //��������

IMAGE main_map;   //��ͼͼ�����
IMAGE character_vice;
IMAGE character;

int map_init_x, map_init_y;
int character_x, character_y;
int character_picture_i, character_picture_j;
int canvas[1000][10000] = { 0 }; //���廭�����꣬ʹÿ�����ص�����Ϊ0

char input; //�����жϱ���

struct pokemon {   //�������ݵĽṹ��
	int x;
	int y;
	int attract;
	int bleed;
	int wufang;
	int special_attract;
	int special_fangyu;
	int level;
	const char* name;    //���� const �ᱨ��
	const char* speciese;
}PK[pokemon_number];

void startup_pokemon() { //�������Գ�ʼ��
	PK[1].x = 100;
	PK[1].y = 200;
	PK[1].attract = 8;
	PK[1].bleed = 30;
	PK[1].wufang = 4;
	PK[1].special_attract = 9;
	PK[1].special_fangyu = 7;
	PK[1].level = 5;
	PK[1].name = "Ƥ����";
	PK[1].speciese = "��";
}

//��ʼ����ͼ
void startup_show() {   
	initgraph(window_width, window_height);   //��ʼ����ͼ����
	map_init_x = map_init_y = 500;
	character_x = 320;
	character_y = 240;
	character_picture_i = 0;
	character_picture_j = 0;
	loadimage(&main_map, _T("��Դ�ļ���\\���ͼ.jpg"), 5000, 5000);
	loadimage(&character_vice, _T("��Դ�ļ���\\��������ͼ����ͼ.jpg", 136, 200));
	loadimage(&character, _T("��Դ�ļ���\\��������ͼ.jpg",136,200));
	BeginBatchDraw();
}

void map_show() {  //��ͼ��ʾ����
	putimage(0, 0, window_width, window_height, &main_map, map_init_x, map_init_y);  //����ȡͼ����ĸ��¶���ʾ��ͼ���ƶ�
	putimage(character_x, character_y, 45, 50, &character_vice, character_picture_i * 45, character_picture_j * 50, NOTSRCERASE); //ÿ��С�˵������ǣ�45��50��
	putimage(character_x, character_y, 45, 50, &character, character_picture_i * 45, character_picture_j * 50, SRCINVERT);
	FlushBatchDraw();
}

void UpdateWithInput() {   //������������µĺ���
	if (_kbhit()) {
		input = _getch();
		if (character_picture_i == 2) {
			character_picture_i = -1;
		}
		if (input == 'A' || input == 'a') {
			map_init_x -= 20;
			character_picture_j = 2;
		}
		if (input == 'D' || input == 'd') {
			map_init_x += 20;
			character_picture_j = 1;
		}
		if (input == 'S' || input == 's') {
			map_init_y += 20;
			character_picture_j = 0;
		}
		if (input == 'W' || input == 'w') {
			map_init_y -= 20;
			character_picture_j = 3;
		}
		character_picture_i++;
	}
}

void UpdateWithoutInput() {   //�����鸳��λ��
	for (int i = 1; i < pokemon_number; i++) {   //��pokemon�����ʼ����λ��
		PK[i].x = 10000 * i;
		PK[i].y = 100000 * i;
	}
}

void fight_animation() {  //ս��ǰ��������
	int i = 320, j=0; //�����Ϸ���ʼ��
	setlinecolor(BLACK); //������ɫ����Ϊ��ɫ
	while (!(i == 319 && j == 0)) {
		line(320, 240, i, j);
		FlushBatchDraw();
		if (i == 640)  j++;
		if (i == 0) j--;
		if (j == 600) i--;
		if (j == 0) i++;
	} //��������
}

void fight_show() {
	int x(30), y(365); //����ѡ��ͼ������
	int jumpy(150); //������������
	int jump(5); //����ѭ����������
	char input; //�����жϱ���

	while (1) {
		//background ����
		IMAGE img1;
		loadimage(&img1, _T("��Դ�ļ���\\ս������1.jpg"));
		putimage(0, 0, &img1);

		//�ҷ�Ѫ����
		setlinestyle(PS_SOLID, 3); //�߿���
		setlinecolor(BLACK);
		setfillcolor(RGB(255, 245, 220));  //�����ɫ
		fillroundrect(25, 50, 220, 130, 10, 10); //�߿��С

		//���·����ܿ�
		setfillcolor(BLACK);
		solidrectangle(0, 335, 640, 480);   //����������ڻ������Σ��ޱ߿򣩡�
		setfillcolor(LIGHTGRAY);
		solidroundrect(5, 340, 340, 475, 10, 10);   //����������ڻ����Բ�Ǿ��Σ��ޱ߿򣩡�
		setfillcolor(WHITE);
		solidroundrect(15, 350, 330, 465, 10, 10); //��߼��ܿ�

		setfillcolor(LIGHTGRAY);
		solidroundrect(345, 340, 635, 475, 10, 10);
		setfillcolor(WHITE);
		solidroundrect(355, 350, 625, 465, 10, 10);

		if (jump == 5)  jumpy = 150;
		if (jump == 10) {
			jumpy = 155;
			jump = 0;
		}
		jump++;

		//Ƥ����
		pokemon_fight_show(PK[1].name, jumpy);

		//����ѡ��ͼ��
		setfillcolor(BLACK);
		POINT pts[] = { {x,y},{x,y + 20},{x + 15,y + 10} };
		solidpolygon(pts, 3);   //����������ڻ����Ķ���Σ��ޱ߿򣩡�

		//control ���Ʋ���
		if (_kbhit) {   //�����ж�
			input = _getch();
			if ((input == 'd' || input == 'D') && x < 190)  x += 160;
			if ((input == 'a' || input == 'A') && x > 30) x -= 160;
			if ((input == 's' || input == 'S') && y < 365 + 60) y += 60;
			if ((input == 'w' || input == 'W') && y > 365) y -= 60;
			if (input == 'z' || input == 'Z') {
				if (x == 30 && y == 365) {
					lighting();
				}
				if (x == 190 && y == 365) {
					scream();
				}
			}
		}
		FlushBatchDraw(); //������������
	}
}

void fight() {
	//���������������飬���������ĳ���������С��ĳ����ʱ����ս��
	for (int i = 0; i < pokemon_number; i++) {
		if (abs(map_init_x + window_width / 2 - PK[i].x) <= 15 && abs(map_init_y + window_height / 2 - PK[i].y) <= 15) {
			fight_animation(); //ս��ǰ����
			fight_show(); //ս����ʾ����
		}
	}
}

void main() {
	startup_pokemon(); //�Ծ������Խ��г�ʼ��
	startup_show(); //�ȶԵ�ͼ���г�ʼ��
	while (1) {
		map_show();
		UpdateWithInput();
		UpdateWithoutInput();
		fight();   //ս������
	}
	EndBatchDraw();
	_getch();
}