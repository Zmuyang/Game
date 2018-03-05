#include <iostream>
#include <conio.h>
#include <windows.h>
#include <graphics.h>
#include <cmath>
#include <time.h>
#include <cstring>
#include "hanshuku.h"

#define window_height 480
#define window_width 640

#define pokemon_number 30

int map_init_x, map_init_y;
int character_x, character_y;
int character_picture_i, character_picture_j;
int canvas[1652][1416];   //���廭�����꣬ʹÿ�����ص�����Ϊ0

char input;

IMAGE main_map;
IMAGE character_vice;
IMAGE character;

struct pokemon {
	int x;
	int y;
	int attack;
	int bleed;
	int defence;
	int special_attack;
	int special_defence;
	int level;
	const char *name;
	const char *speciese;
	int skill_1;   //����ܵĻ����˺�
	int skill_2;
	int skill_3;
	int skill_4;
	int judge;
	int time;  //��һ��ʱ���Ժ󽫰�ԭλ�õľ�������ˢ�³���
}PK[pokemon_number];

//CHAR �� TCHAR ת���ĺ�����Ϊ�˽���ԴͼƬ��·�������ñ�����ʾ
void CharToTchar(const char *_char, TCHAR *tchar) {
	int iLength;
	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

void load_PK_picture(pokemon *PK) {
	char ch_path1[60] = "��Դ�ļ���\\";  //·��ǰ��
	char ch_path2[60] = "1.jpg";		//·�����
	char ch_path3[60] = "2.jpg";
	char ch_path4[60] = "��Դ�ļ���\\";
	strcat_s(ch_path1, PK->name);    //��·��������������
	strcat_s(ch_path1, ch_path2);
	strcat_s(ch_path4, PK->name);
	strcat_s(ch_path4, ch_path3);
	TCHAR p1[60];
	TCHAR p2[60];
	//��·�����ָĳ�TCHAR����������
	CharToTchar(ch_path1, p1);
	CharToTchar(ch_path4, p2);

	//�þ��鿴��������������
	static int jumpy_1 = 90;
	static int jump = 5;
	if (jump == 5) jumpy_1 = 90;
	if (jump == 10) {
		jump = 0;
		jumpy_1 = 95;
	}
	jump++;
	//��ʾ�з�����
	IMAGE im1, im2;
	loadimage(&im1, p1);
	loadimage(&im2, p2);
	putimage(400, jumpy_1, &im2, NOTSRCERASE);
	putimage(400, jumpy_1, &im1, SRCINVERT);
}

void startup_pokemon() { //�������Գ�ʼ��
	//Ƥ����
	//�����ڵ�ͼ�ϵ�����
	PK[0].x = 0;   
	PK[0].y = 0;

	PK[0].attack = 8;			//�չ�
	PK[0].bleed = 30;			//����ֵ
	PK[0].defence = 4;			//�շ�
	PK[0].special_attack = 9;		//�ع�
	PK[0].special_defence = 7;		//�ط�
	PK[0].level = 5;		//�ȼ�
	PK[0].name = "Ƥ����";			//����
	PK[0].speciese = "��";		//Ԫ������
	PK[0].skill_1 = 50;				//����1�˺�
	PK[0].skill_2 = 80;				//����2�˺�
	PK[0].skill_3 = 100;
	PK[0].skill_4 = 150;
	PK[0].judge = 1;
	PK[0].time = 0;

	//С����
	PK[1].x = 100;                      
	PK[1].y = 200;
	PK[1].attack = 8;                    
	PK[1].bleed = 30;                    
	PK[1].defence = 4;                  
	PK[1].special_attack = 9;            
	PK[1].special_defence = 7;           
	PK[1].level = 5;                  
	PK[1].name = "С����";             
	PK[1].speciese = "��";             
	PK[1].skill_1 = 50;                  
	PK[1].skill_2 = 80;                 
	PK[1].skill_3 = 0;
	PK[1].skill_4 = 0;
	PK[1].judge = 0;
	PK[1].time = 0;

	//��������//
	PK[2].x = 0;
	PK[2].y = 0;
	PK[2].attack = 6;
	PK[2].bleed = 28;
	PK[2].defence = 3;
	PK[2].special_attack = 8;
	PK[2].special_defence = 6;
	PK[2].level = 5;
	PK[2].name = "��������";
	PK[2].speciese = "��";
	PK[2].skill_1 = 30;
	PK[2].skill_2 = 40;
	PK[2].skill_3 = 0;
	PK[2].skill_4 = 0;
	PK[2].time = 0;

	//����������//
	PK[3].x = 0;
	PK[3].y = 0;
	PK[3].attack = 7;
	PK[3].bleed = 29;
	PK[3].defence = 5;
	PK[3].special_attack = 10;
	PK[3].special_defence = 6;
	PK[3].level = 5;
	PK[3].name = "����������";
	PK[3].speciese = "ˮ";
	PK[3].skill_1 = 70;
	PK[3].skill_2 = 80;
	PK[3].skill_3 = 0;
	PK[3].skill_4 = 0;
	PK[3].time = 0;

	//Сȭʯ//
	PK[4].x = 0;
	PK[4].y = 0;
	PK[4].attack = 8;
	PK[4].bleed = 30;
	PK[4].defence = 4;
	PK[4].special_attack = 9;
	PK[4].special_defence = 7;
	PK[4].level = 5;
	PK[4].name = "Сȭʯ";
	PK[4].speciese = "��ʯ";
	PK[4].skill_1 = 35;
	PK[4].skill_2 = 60;
	PK[4].skill_3 = 0;
	PK[4].skill_4 = 0;
	PK[4].time = 0;

	//�ƻ���
	PK[5].x = 0;
	PK[5].y = 0;
	PK[5].attack = 8;
	PK[5].bleed = 30;
	PK[5].defence = 4;
	PK[5].special_attack = 9;
	PK[5].special_defence = 7;
	PK[5].level = 5;
	PK[5].name = "�ƻ���";
	PK[5].speciese = "����";
	PK[5].skill_1 = 35;
	PK[5].skill_2 = 40;
	PK[5].skill_3 = 0;
	PK[5].skill_4 = 0;
	PK[5].time = 0;

	//��˹//
	PK[6].x = 0;
	PK[6].y = 0;
	PK[6].attack = 8;
	PK[6].bleed = 30;
	PK[6].defence = 4;
	PK[6].special_attack = 9;
	PK[6].special_defence = 7;
	PK[6].level = 5;
	PK[6].name = "��˹";
	PK[6].speciese = "���� ��";
	PK[6].skill_1 = 45;
	PK[6].skill_2 = 83;
	PK[6].skill_3 = 0;
	PK[6].skill_4 = 0;
	PK[6].time = 0;

	//����//
	PK[7].x = 0;
	PK[7].y = 0;
	PK[7].attack = 8;
	PK[7].bleed = 30;
	PK[7].defence = 4;
	PK[7].special_attack = 9;
	PK[7].special_defence = 7;
	PK[7].level = 5;
	PK[7].name = "����";
	PK[7].speciese = "����";
	PK[7].skill_1 = 50;
	PK[7].skill_2 = 80;
	PK[7].skill_3 = 0;
	PK[7].skill_4 = 0;
	PK[7].time = 0;

	//����//
	PK[8].x = 0;
	PK[8].y = 0;
	PK[8].attack = 8;
	PK[8].bleed = 30;
	PK[8].defence = 4;
	PK[8].special_attack = 9;
	PK[8].special_defence = 7;
	PK[8].level = 5;
	PK[8].name = "����";
	PK[8].speciese = "����";
	PK[8].skill_1 = 50;
	PK[8].skill_2 = 80;
	PK[8].skill_3 = 0;
	PK[8].skill_4 = 0;
	PK[8].time = 0;

	//����//
	PK[9].x = 0;
	PK[9].y = 0;
	PK[9].attack = 8;
	PK[9].bleed = 30;
	PK[9].defence = 4;
	PK[9].special_attack = 9;
	PK[9].special_defence = 7;
	PK[9].level = 5;
	PK[9].name = "����";
	PK[9].speciese = "��";
	PK[9].skill_1 = 50;
	PK[9].skill_2 = 80;
	PK[9].skill_3 = 0;
	PK[9].skill_4 = 0;
	PK[9].time = 0;

	//ƤƤȮ//
	PK[10].x = 0;
	PK[10].y = 0;
	PK[10].attack = 8;
	PK[10].bleed = 30;
	PK[10].defence = 4;
	PK[10].special_attack = 9;
	PK[10].special_defence = 7;
	PK[10].level = 5;
	PK[10].name = "ƤƤȮ";
	PK[10].speciese = "��";
	PK[10].skill_1 = 50;
	PK[10].skill_2 = 80;
	PK[10].skill_3 = 0;
	PK[10].skill_4 = 0;
	PK[10].time = 0;

	//����//
	PK[11].x = 0;
	PK[11].y = 0;
	PK[11].attack = 8;
	PK[11].bleed = 30;
	PK[11].defence = 4;
	PK[11].special_attack = 9;
	PK[11].special_defence = 7;
	PK[11].level = 5;
	PK[11].name = "����";
	PK[11].speciese = "����";
	PK[11].skill_1 = 50;
	PK[11].skill_2 = 80;
	PK[11].skill_3 = 0;
	PK[11].skill_4 = 0;
	PK[11].time = 0;
}

void startup_pokemon_destination() {  //����λ�ó�ʼ��
	PK[1].x = 488;
	PK[1].y = 553;
}

void startup_show() {  //��ͼ��ʼ��
	initgraph(window_width, window_height);   //��ʼ����ͼ����
	map_init_x = 298;
	map_init_y = 162;		//��ͼ��ʼʱʱ��ȡ�ӣ�500,500����ʼ�Ĳ���//
	character_x =  70;		 //����ĳ�ʼλ��
	character_y = 221;
	character_picture_i = 0;
	character_picture_j = 0;
	const char *s = "��Դ�ļ���\\�ռ���ͼ.jpg";
	TCHAR p[40];
	CharToTchar(s, p);
	loadimage(&main_map, p, 1652, 1416);
	loadimage(&character_vice, _T("��Դ�ļ���\\��������ͼ����ͼ.jpg"), 136, 200);
	loadimage(&character, _T("��Դ�ļ���\\��������ͼ.jpg"), 136, 200);
	BeginBatchDraw();

	for (int i = 0; i < 1652; i++) {
		for (int j = 0; j < 1416; j++) {
			if (i <= 425 || i >= 1223 - 45 || j <= 210 || j >= 1161 - 50) {  //��ͼ�����ܵ���ľ
				canvas[i][j] = 0;
			}
			else if ((i > 430 && i <= 552) && (j > 210 && j <= 320)) {  //���Ϸ��ķ���
				canvas[i][j] = 0;
			}
			else if ((i >= 540 - 45 && i <= 552) && (j > 320 && j <= 562)) {//���������һ����ľ
				canvas[i][j] = 0;
			}
			else if ((i >= 659 - 45 && i <= 690) && (j >= 300 && j <= 542)) {//�ڶ�����ľ
				canvas[i][j] = 0;
			}
			else if ((i >= 799 - 45 && i <= 821) && (j >= 211 && j <= 489)) {   //��������ľ
				canvas[i][j] = 0;
			}
			else if ((i >= 923 - 45 && i <= 1141) && (j >= 235 && j <= 357)) {  //���Ϸ��ĳ�������ľ
				canvas[i][j] = 0;
			}
			else if ((i >= 1121 - 45 && i < 1223) && (j >= 404 && j <= 521)) {
				canvas[i][j] = 0;
			}
			else if ((i >= 699 - 45 && i <= 731) && (j >= 513 && j <= 630)) {//�����￪ʼ���м��ɭ�ֿ鶨�����
				canvas[i][j] = 0;
			}
			else {
				canvas[i][j] = 0;
			}
		}
	}
}

void map_show() {   //��ͼ��ʾ����
	putimage(0, 0, window_width, window_height, &main_map, map_init_x, map_init_y);
	putimage(character_x, character_y, 45, 50, &character_vice, character_picture_i * 45, character_picture_j * 50, NOTSRCERASE); //ÿ��С�˵������ǣ�45,50��
	putimage(character_x, character_y, 45, 50, &character, character_picture_i * 45, character_picture_j * 50, SRCINVERT);
	FlushBatchDraw();
}

void UpdateWithInput() {  //������������µĺ���
	if (_kbhit()) {    //ÿ���ƶ�20�����ص�λ
		input = _getch();
		if (character_picture_i == 2) {    //ʵ���˽���ȡ����ͼ�Ĳ�ͬ����
			character_picture_i = -1;
		}
		if (input == 'A' || input == 'a'&&canvas[map_init_x + character_x - 20][map_init_y + character_y] != 0) {   //���ݷ�������������ݸ���
			map_init_x -= 10;                       //10Ϊ�˵Ĳ���//
			character_picture_j = 2;
		}
		else if (input == 'A' || input == 'a'&&canvas[map_init_x + character_x - 20][map_init_y + character_y] == 0){
			character_picture_j = 2;
		}
		if (input == 'D' || input == 'd'&&canvas[map_init_x + character_x + 20][map_init_y + character_y] != 0) {    //�����ж����ж��н������Ƿ�Ϊ�ϰ���//
			map_init_x += 10;
			character_picture_j = 1;
		}
		else if (input == 'D' || input == 'd'&&canvas[map_init_x + character_x + 20][map_init_y + character_y] == 0){
			character_picture_j = 1;
		}
		if (input == 'S' || input == 's'&&canvas[map_init_x + character_x][map_init_y + character_y + 20] != 0){
			map_init_y += 10;
			character_picture_j = 0;
		}
		else if (input == 'S' || input == 's'&&canvas[map_init_x + character_x][map_init_y + character_y + 20] == 0){
			character_picture_j = 0;
		}
		if (input == 'W' || input == 'w'&&canvas[map_init_x + character_x][map_init_y + character_y - 20] != 0){
			map_init_y -= 10;
			character_picture_j = 3;
		}
		else if (input == 'W' || input == 'w'&&canvas[map_init_x + character_x][map_init_y + character_y - 20] == 0){
			character_picture_j = 3;
		}
		character_picture_i++;
	}
}



void bleed_show(pokemon PK){

}

void enemy_fight_show(pokemon *PK_enemy){
	load_PK_picture(PK_enemy);
}

void pokemon_fight_show(pokemon *PK_enemy, pokemon *PK_own){/*
	//FlushBatchDraw();
	//�з����鿪ʼ�ͷż���//
	//if (PK_enemy.bleed >PK_own.bleed){
		//�ŵ�һ�����ܵĶ���//
		//PK_own.bleed=PK_own.bleed-((PK_enemy.level*0.4+2)*PK_enemy.skill_1*PK_enemy.attack/(PK_own.defence*50.0)+2);  //�˺�ֵ����//
	}
	//if (PK_enemy.bleed <=PK_own.bleed){
		//�ŵڶ������ܵĶ���//
		// PK_own.bleed=PK_own.bleed-((PK_enemy.level*0.4+2)*PK_enemy.skill_1*PK_enemy.attack/(PK_own.defence*50.0)+2);  //�˺�ֵ����//
	}
	//FlushBatchDraw();	*/
}


void fight_animation(){
	//����ʵ����ս��ǰ��������
	int i, j;
	i = 320, j = 0;                                            //�����Ϸ���ʼ��
	setlinecolor(BLACK);                              //������ɫ����Ϊ��ɫ
	while (!(i == 319 && j == 0)){
		line(320, 240, i, j);
		FlushBatchDraw();
		if (i == 640)   j++;
		if (i == 0)       j--;
		if (j == 600)   i--;
		if (j == 0)      i++;
	}
	//�����ﶯ������
}

void fight_show(pokemon *PK_enemy, pokemon *PK_own)
{
	int x = 30;
	int y = 365;                                       //����ѡ��ͼ������

	int choice_x = 370;
	int choice_y = 365;								//��ʼ����ѡ��
	int choose = 1;                                  //ѡ��ս��or���ܵ��ж�

	int jumpy = 150;                               //������������
	int jump = 5;									  //����ѭ����������
	char input;										  //�����жϱ���

	int fullbleed = PK_own->bleed;					//�ҷ���ѪѪ��
	int fullbleed2 = PK_enemy->bleed;                    //�ط���ѪѪ��

	int bleed_Width2 = 125;
	int bleed_Width1 = 180;							//�ҷ�Ѫ������


	while (1){
		IMAGE img1;
		loadimage(&img1, _T("��Դ�ļ���\\ս������1.jpg"));
		putimage(0, 0, &img1);
		//�ҷ�Ѫ����
		setlinestyle(PS_SOLID, 3);						   //�߿���
		setlinecolor(BLACK);							      //�߿���ɫ
		setfillcolor(RGB(255, 245, 220));               //�����ɫ
		fillroundrect(25, 50, 220, 130, 10, 10);      //�߿��С
													  //�з�Ѫ����
		setlinestyle(PS_SOLID, 3);                        //�߿���
		setlinecolor(BLACK);                              //�߿���ɫ
		setfillcolor(RGB(255, 245, 220));             //�����ɫ
		fillroundrect(330, 220, 580, 310, 10, 10); //�߿��С

		//���·����ܿ�
		setfillcolor(BLACK);
		solidrectangle(0, 335, 640, 480);            //��ɫ����   

		setfillcolor(LIGHTGRAY);
		solidroundrect(5, 340, 340, 475, 10, 10);
		setfillcolor(WHITE);
		solidroundrect(15, 350, 330, 465, 10, 10);//��߼��ܿ�

		setfillcolor(LIGHTGRAY);
		solidroundrect(345, 340, 635, 475, 10, 10);
		setfillcolor(WHITE);
		solidroundrect(355, 350, 625, 465, 10, 10);//�ұ߼��ܿ�

		enemy_fight_show(PK_enemy);     //��ʾ�з�����

		if (jump == 5)			jumpy = 150;                                //��������ѭ����������

		if (jump == 10)	{
			jumpy = 155;
			jump = 0;
		}
		jump++;


		//Ƥ����
		IMAGE im1, im2;
		loadimage(&im1, _T("��Դ�ļ���\\Ƥ����.jpg"));
		loadimage(&im2, _T("��Դ�ļ���\\Ƥ����2.jpg"));
		putimage(65, jumpy, &im2, NOTSRCERASE);
		putimage(65, jumpy, &im1, SRCINVERT);

		//�ҷ��ȼ�
		TCHAR Lv[5];
		_stprintf_s(Lv, _T("%d"), PK_own->level);
		outtextxy(500, 230, Lv);   //�������������ָ��λ������ַ�����
		outtextxy(460, 230, _T("Lv:"));

		//�ҷ�����Ѫ����ʾ
		outtextxy(490, 280, _T("/"));
		TCHAR HP2[5];
		_stprintf_s(HP2, _T("%d"), PK_own->bleed);
		outtextxy(430, 280, HP2);
		TCHAR HP2_1[5];
		_stprintf_s(HP2_1, _T("%d"), fullbleed);
		outtextxy(530, 280, HP2_1);
		//�ҷ�Ѫ��
		setlinestyle(PS_SOLID, 2);
		setlinecolor(LIGHTGRAY);
		setfillcolor(WHITE);
		fillroundrect(385, 260, 570, 270, 10, 10);

		setfillcolor(GREEN);
		solidroundrect(568 - bleed_Width1, 262, 568, 267, 10, 10);

		//�з��ȼ�
		TCHAR Lv_2[5];
		_stprintf_s(Lv_2, _T("%d"), PK_enemy->level);
		outtextxy(160, 70, Lv_2);
		outtextxy(120, 70, _T("Lv:"));
		//Ѫ��
		setlinestyle(PS_SOLID, 2);
		setlinecolor(LIGHTGRAY);
		setfillcolor(WHITE);
		fillroundrect(80, 100, 210, 110, 10, 10);

		setfillcolor(GREEN);
		solidroundrect(208 - bleed_Width2, 102, 208, 107, 10, 10);

		//ѡ��ս��or����
		if (choose == 1){
			setfillcolor(BLACK);
			POINT pts[] = { { choice_x, choice_y },{ choice_x,choice_y + 20 },{ choice_x + 15, choice_y + 10 } };
			solidpolygon(pts, 3);   //����������ڻ����Ķ���Σ��ޱ߿򣩡�

			char input;
			if (_kbhit()){
				input = _getch();
				if ((input == 'd' || input == 'D') && choice_x < 370 + 130)
					choice_x += 130;
				if ((input == 'a' || input == 'A') && choice_x > 370)
					choice_x -= 130;
				if ((input == 's' || input == 'S') && choice_y<365 + 50)
					choice_y += 50;
				if ((input == 'w' || input == 'W') && choice_y > 365)
					choice_y -= 50;
				if ((input == 'z' || input == 'Z') && choice_x == 370 && choice_y == 365)
					choose = 0;
				if ((input == 'z' || input == 'Z') && choice_x == 370 + 130 && choice_y == 365){
					PK_enemy->judge = 1;
					break;
				}
			}

			LOGFONT f;
			gettextstyle(&f);                     // ��ȡ��ǰ��������
			f.lfHeight = 20;                      // ��������߶�
			_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			settextstyle(&f);                     // ����������ʽ
			outtextxy(370 + 20, 365, _T("ս��"));
			outtextxy(500 + 20, 365, _T("����"));

			FlushBatchDraw();
		}

		//�ҷ�����
		if (choose == 0){
			//����ѡ��ͼ��
			setfillcolor(BLACK);
			POINT pts[] = { { x, y },{ x, y + 20 },{ x + 15, y + 10 } };
			solidpolygon(pts, 3);

			LOGFONT f;
			gettextstyle(&f);                     // ��ȡ��ǰ��������
			f.lfHeight = 20;                      // ��������߶�
			_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
			setbkmode(TRANSPARENT);    //���������������ͼ�������������ʱ�ı���ģʽ
			settextcolor(BLACK);
			settextstyle(&f);                      // ����������ʽ
			outtextxy(30 + 20, 365, _T("�콵����"));
			outtextxy(190 + 20, 365, _T("���"));
			outtextxy(30 + 20, 365 + 60, _T("��������"));

			//�жϵз�������û������//
			if (PK_enemy->bleed <= 0){
				LOGFONT f;
				gettextstyle(&f);                     // ��ȡ��ǰ��������
				f.lfHeight = 100;                     // ��������߶�
				_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
				setbkmode(TRANSPARENT);
				settextcolor(RED);
				settextstyle(&f);                     // ����������ʽ
				outtextxy(window_width / 2 - 150, window_height / 2 - 100, _T("victory"));    //��ʾ��Ϸ���//
				FlushBatchDraw();
				PK_enemy->judge = 1;
				Sleep(2000);
				fight_animation();                    //�˳�����//
				break;
			}


			//����ŵз�����ļ����ͷź���//
			pokemon_fight_show(PK_enemy, PK_own);

			//�жϼ���������û������//
			if (PK_own->bleed <= 0){
				TCHAR s[] = _T("defeated");
				settextstyle(16, 0, _T("����"));
				outtextxy(window_width / 2 - 10, window_height / 2, s);    //��ʾ��Ϸ���//
				PK_enemy->judge = 1;
				fight_animation();      //�˳�����//
				break;
			}

			//control���Ʋ���
			if (_kbhit()){		//�����ж�
				input = _getch();
				if ((input == 'd' || input == 'D') && x < 190)
					x += 160;
				if ((input == 'a' || input == 'A') && x > 30)
					x -= 160;
				if ((input == 's' || input == 'S') && y<365 + 60)
					y += 60;
				if ((input == 'w' || input == 'W') && y > 365)
					y -= 60;
				if (input == 'z' || input == 'Z'){
					if (x == 30 && y == 365){
						lighting();
						PK_enemy->bleed = PK_enemy->bleed - ((PK_own->level*0.4 + 2)*PK_own->skill_1*PK_own->attack / (PK_enemy->defence*50.0) + 2);  //�˺�ֵ����//
					}
					if (x == 190 && y == 365){
						scream();
						PK_enemy->bleed = PK_enemy->bleed - ((PK_own->level*0.4 + 2)*PK_own->skill_2*PK_own->attack / (PK_enemy->defence*50.0) + 2);  //�˺�ֵ����//
					}
					if (x == 30 && y == 365 + 60){
						flash();
						PK_enemy->bleed = PK_enemy->bleed - ((PK_own->level*0.4 + 2)*PK_own->skill_3*PK_own->attack / (PK_enemy->defence*50.0) + 2);  //�˺�ֵ����//
					}
					if (PK_enemy->bleed >= 0){
						bleed_Width2 = PK_enemy->bleed*1.0 / fullbleed2 * 125;
					}
					else{
						bleed_Width2 = 0 / fullbleed2 * 125;
					}
				}
				if (input == 'x' || input == 'X')
					choose = 1;
			}
			FlushBatchDraw();							  //������������
		}
	}
}

void fight(){
	int i;
	for (i = 0; i<pokemon_number; i++)	{		//����������������
		if (abs(map_init_x + character_x - PK[i].x) <= 15 && abs(map_init_y + character_y - PK[i].y) <= 15 && PK[i].judge == 0){
			fight_animation();						    //ս��ǰ����
			fight_show(&PK[i], &PK[0]);								    //ս����ʾ����
			break;
		}
	}
}

void pokemon_refresh() { //ʵ��һ��ʱ���Ժ��ͼ�ϵľ���ͻ��Զ�����ˢ����
	int i;
	for (i = 0; i<pokemon_number; i++){
		if (PK[i].judge == 1 && PK[i].time<10000) {  //��һ�����鱻���������judge�ͻ��Ϊ1��Ϊ1�����ʱ�������޷��������ģ�����10000��ѭ��������������ˢ�³���
			PK[i].time++;
		}
		else if (PK[i].judge == 1 && PK[i].time == 10000){
			PK[i].judge = 0;
			PK[i].time = 0;
		}
	}
}


int main(){
	startup_pokemon();							  //�Ծ������Խ��г�ʼ��
	startup_pokemon_destination();		      //�Ծ���λ�ý��г�ʼ��
	startup_show();                                     //�Ե�ͼ���г�ʼ��
	while (1){
		pokemon_refresh();
		map_show();										//��ͼ��ʾ����
		UpdateWithInput();								// ���ݲ������е�ͼ�ĸ���
		fight();												//ս������
	}
	return 0;
}
