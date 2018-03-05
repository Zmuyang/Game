#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <graphics.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "hanshuku.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ȫ�ֱ���
#define window_height 480
#define window_width  640                  //���ڴ�С

#define pokemon_number 30              //��������

int game_status;
int map_init_x, map_init_y;
int character_x, character_y;
int character_picture_i, character_picture_j;
int pokemon_experiece = 0;                //�����ҷ����龭��
int exercise_Width = 0;                         //�ҷ�����۳���
int canvas[1652][1416] = { 0 };               //���廭������ ʹÿ�����ص�����Ϊ0

											  //NPC��λ������
int doctor_tong_x, doctor_tong_y;
int NPC_1_x, NPC_1_y;
int NPC_2_x, NPC_2_y;
int NPC_3_x, NPC_3_y;
int plot_judge;                       //�ж��ڵ�ͼˢ�µ�ʱ���Ƿ��������

char input;                                         //�����жϱ���

IMAGE main_map;                              //��ͼͼ�����
IMAGE character_vice;
IMAGE character;


//���徫�����ݵĽṹ��
struct pokemon
{
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
	int skill_1;                    //����ܵĻ����˺�//
	int skill_2;
	int skill_3;
	int skill_4;
	const char *skill_1_name;      //���ܵ�����
	const char *skill_2_name;
	int judge;
	int time;                             //��һ��ʱ���Ժ󽫰�ԭλ�õľ�������ˢ�³���
}PK[pokemon_number];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//���к�������
//һ�����麯��
void plot_1();
void plot_2();
void plot_3();
void plot_4();
void plot_5();
void plot_6();
void plot_7();
void plot_8();
void plot_9();
void plot_10();
void plot_11();
void plot_12();
void plot_13();
void plot_14();
void plot_15();
//�������溯�����ĵ������ȡ����
void start_menu();
void pause_menu();
void readfile();
void writefile();
//�������ݸ��º�����ս����������������
void starup_pokemon_judge();//����ʱ���ʼ��
void starup_pokemon();//����������Գ�ʼ��
void starup_pokemon_bleed();//����Ѫ����ʼ��
void starup_pokemon_desination();//����λ�ó�ʼ��
void starup_map_show();//��ͼ��ʼ��
void pokemon_refresh();//����ˢ��
void map_show();//��ͼ��ʾ����
void operate();//������������
void load_PK_picture(pokemon *PK);//����ط�����ͼƬ
void interface_change_animation();//�����л�����
void enemy_fight_show(pokemon *PK_enemy);//�з�����ͼƬ�����Լ�������ʾ
void fight_show(pokemon *PK_enemy, pokemon *PK_own);//ս����ʾ����
void fight();//ս������
			 ///////////////////////////////////////////////////////////////////////////////////////////////

			 //��Ϸ�����������ͣ����
void start_menu()
{
	IMAGE starup_window;

	loadimage(&starup_window, _T("��Դ�ļ���\\����\\��½����.jpg"), 640, 480);
	putimage(0, 0, 640, 480, &starup_window, 0, 0);

	//���õ�¼��������
	LOGFONT f;    //����ṹ�嶨������������ԡ�
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 30;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(300, 140, _T("1 ����Ϸ"));
	outtextxy(280, 240, _T("2 ��ȡ�浵"));
	outtextxy(310, 340, _T("3 �˳�"));

	LOGFONT t;
	gettextstyle(&t);                     // ��ȡ��ǰ��������
	t.lfHeight = 68;                      // ��������߶�Ϊ 48
	_tcscpy_s(t.lfFaceName, _T("����"));
	settextcolor(BLUE);
	t.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	settextstyle(&t);                     // ����������ʽ
	outtextxy(200, 40, _T("�ڴ�����"));

	LOGFONT m;
	gettextstyle(&m);                     // ��ȡ��ǰ��������
	m.lfHeight = 30;                      // ��������߶�Ϊ 48
	_tcscpy_s(m.lfFaceName, _T("����"));
	settextcolor(BLUE);
	t.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	settextstyle(&m);                     // ����������ʽ
	outtextxy(460, 70, _T("(�Ӻ���)"));
	FlushBatchDraw();

	input = _getch();
	if (input == '1')
	{
		game_status = 1;
	}
	else if (input == '2')
	{
		readfile();
		game_status = 1;
	}
	else if (input == '3')
	{
		game_status = 0;
		exit(0);
	}
}

void pause_menu()
{
	IMAGE starup_window;

	loadimage(&starup_window, _T("��Դ�ļ���\\����\\��½����.jpg"), 640, 480);
	putimage(0, 0, 640, 480, &starup_window, 0, 0);

	//������ͣ��������
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 30;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(300, 140, _T("1 ������Ϸ"));
	outtextxy(310, 240, _T("2 �浵"));
	outtextxy(310, 340, _T("3 �˳�"));
	FlushBatchDraw();

	input = _getch();
	if (input == '1')
	{
		game_status = 1;
	}
	else if (input == '2')
	{
		writefile();
		game_status = 1;
	}
	else if (input == '3')
	{
		game_status = 0;
		exit(0);
	}
}

//�����ʹ浵�ĺ���
void readfile()
{
	FILE *fp;
	fopen_s(&fp,"��Դ�ļ���\\��ʷ\\��Ϸ����.txt", "w");
	fscanf_s(fp, "%d %d %d %d ", map_init_x, map_init_y, character_picture_i, character_picture_j);
	fclose(fp);
}

void writefile()
{
	FILE *fp;
	fopen_s(&fp,"��Դ�ļ���\\��ʷ\\��Ϸ����.txt", "w");
	fprintf(fp, "%d %d %d %d", map_init_x, map_init_y, character_picture_i, character_picture_j);
	fclose(fp);
}

//����ʱ�����Գ�ʼ��
void startup_pokemon_judge()
{
	int i;
	for (i = 0; i <= pokemon_number; i++)
	{
		PK[i].time = 0;
	}
}
//����������Գ�ʼ��
void startup_pokemon()
{
	//Ƥ����//
	PK[0].level = 5;
	PK[0].x = 0;
	PK[0].y = 0;
	PK[0].attack = 8 + (PK[0].level - 5) * 2;
	PK[0].bleed = 32 + (PK[0].level - 5) * 3;
	PK[0].defence = 4 + (PK[0].level - 5);
	PK[0].special_attack = 9 + (PK[0].level - 5) * 2;
	PK[0].special_defence = 7 + (PK[0].level - 5);
	PK[0].name = "Ƥ����";
	PK[0].speciese = "��";
	PK[0].skill_1 = 50;
	PK[0].skill_2 = 0;
	PK[0].skill_3 = 60;
	PK[0].skill_4 = 100;
	PK[0].judge = 1;

	//С����//
	PK[1].x = 100;                       //�����ڵ�ͼ�ϵ�����//
	PK[1].y = 200;
	PK[1].attack = 8;                    //�չ�
	PK[1].bleed = 30;                    //����ֵ
	PK[1].defence = 4;                   //�շ�
	PK[1].special_attack = 9;            //�ع�
	PK[1].special_defence = 7;           //�ط�
	PK[1].level = 5;                   //�ȼ�
	PK[1].name = "С����";             //����
	PK[1].speciese = "��";             //Ԫ������
	PK[1].skill_1_name = "����"; //����1����
	PK[1].skill_2_name = "����"; //����2����
	PK[1].skill_1 = 50;                  //����1�˺�
	PK[1].skill_2 = 80;                  //����2�˺�
	PK[1].skill_3 = 0;
	PK[1].skill_4 = 0;
	PK[1].judge = 0;

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
	PK[2].skill_1_name = "����";
	PK[2].skill_2_name = "����";
	PK[2].skill_1 = 30;
	PK[2].skill_2 = 40;
	PK[2].skill_3 = 0;
	PK[2].skill_4 = 0;

	//������//
	PK[3].x = 0;
	PK[3].y = 0;
	PK[3].attack = 7;
	PK[3].bleed = 29;
	PK[3].defence = 5;
	PK[3].special_attack = 10;
	PK[3].special_defence = 6;
	PK[3].level = 5;
	PK[3].name = "������";
	PK[3].speciese = "ˮ";
	PK[3].skill_1_name = "����";
	PK[3].skill_2_name = "����";
	PK[3].skill_1 = 70;
	PK[3].skill_2 = 80;
	PK[3].skill_3 = 0;
	PK[3].skill_4 = 0;

	//������//
	PK[4].x = 0;
	PK[4].y = 0;
	PK[4].attack = 8;
	PK[4].bleed = 30;
	PK[4].defence = 4;
	PK[4].special_attack = 9;
	PK[4].special_defence = 7;
	PK[4].level = 5;
	PK[4].name = "������";
	PK[4].speciese = "��";
	PK[4].skill_1_name = "����";
	PK[4].skill_2_name = "����";
	PK[4].skill_1 = 35;
	PK[4].skill_2 = 60;
	PK[4].skill_3 = 0;
	PK[4].skill_4 = 0;

	//������//
	PK[5].x = 0;
	PK[5].y = 0;
	PK[5].attack = 8;
	PK[5].bleed = 30;
	PK[5].defence = 4;
	PK[5].special_attack = 9;
	PK[5].special_defence = 7;
	PK[5].level = 5;
	PK[5].name = "������";
	PK[5].speciese = "��";
	PK[5].skill_1_name = "����";
	PK[5].skill_2_name = "����";
	PK[5].skill_1 = 35;
	PK[5].skill_2 = 40;
	PK[5].skill_3 = 0;
	PK[5].skill_4 = 0;

	//���з//
	PK[6].x = 0;
	PK[6].y = 0;
	PK[6].attack = 8;
	PK[6].bleed = 30;
	PK[6].defence = 4;
	PK[6].special_attack = 9;
	PK[6].special_defence = 7;
	PK[6].level = 5;
	PK[6].name = "���з";
	PK[6].speciese = "ˮ";
	PK[6].skill_1_name = "����";
	PK[6].skill_2_name = "����";
	PK[6].skill_1 = 45;
	PK[6].skill_2 = 83;
	PK[6].skill_3 = 0;
	PK[6].skill_4 = 0;

	//·����ŷ//
	PK[7].x = 0;
	PK[7].y = 0;
	PK[7].attack = 8;
	PK[7].bleed = 30;
	PK[7].defence = 4;
	PK[7].special_attack = 9;
	PK[7].special_defence = 7;
	PK[7].level = 5;
	PK[7].name = "·����ŷ";
	PK[7].speciese = "��";
	PK[7].skill_1_name = "����";
	PK[7].skill_2_name = "����";
	PK[7].skill_1 = 50;
	PK[7].skill_2 = 80;
	PK[7].skill_3 = 0;
	PK[7].skill_4 = 0;

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
	PK[8].skill_1_name = "����";
	PK[8].skill_2_name = "����";
	PK[8].skill_1 = 50;
	PK[8].skill_2 = 80;
	PK[8].skill_3 = 0;
	PK[8].skill_4 = 0;

	//Ƥ��//
	PK[9].x = 0;
	PK[9].y = 0;
	PK[9].attack = 8;
	PK[9].bleed = 30;
	PK[9].defence = 4;
	PK[9].special_attack = 9;
	PK[9].special_defence = 7;
	PK[9].level = 5;
	PK[9].name = "Ƥ��";
	PK[9].speciese = "��";
	PK[9].skill_1_name = "����";
	PK[9].skill_2_name = "����";
	PK[9].skill_1 = 50;
	PK[9].skill_2 = 80;
	PK[9].skill_3 = 0;
	PK[9].skill_4 = 0;

	//С���//
	PK[10].x = 0;
	PK[10].y = 0;
	PK[10].attack = 8;
	PK[10].bleed = 30;
	PK[10].defence = 4;
	PK[10].special_attack = 9;
	PK[10].special_defence = 7;
	PK[10].level = 5;
	PK[10].name = "С���";
	PK[10].speciese = "��";
	PK[10].skill_1_name = "����";
	PK[10].skill_2_name = "����";
	PK[10].skill_1 = 50;
	PK[10].skill_2 = 80;
	PK[10].skill_3 = 0;
	PK[10].skill_4 = 0;

	//����è//
	PK[11].x = 0;
	PK[11].y = 0;
	PK[11].attack = 8;
	PK[11].bleed = 30;
	PK[11].defence = 4;
	PK[11].special_attack = 9;
	PK[11].special_defence = 7;
	PK[11].level = 5;
	PK[11].name = "����è";
	PK[11].speciese = "����";
	PK[11].skill_1_name = "����";
	PK[11].skill_2_name = "����";
	PK[11].skill_1 = 50;
	PK[11].skill_2 = 80;
	PK[11].skill_3 = 0;
	PK[11].skill_4 = 0;

	//�׹�
	PK[12].x = 0;
	PK[12].y = 0;
	PK[12].attack = 8;
	PK[12].bleed = 30;
	PK[12].defence = 4;
	PK[12].special_attack = 9;
	PK[12].special_defence = 7;
	PK[12].level = 5;
	PK[12].name = "�׹�";
	PK[12].speciese = "��";
	PK[12].skill_1_name = "����";
	PK[12].skill_2_name = "����";
	PK[12].skill_1 = 50;
	PK[12].skill_2 = 80;
	PK[12].skill_3 = 0;
	PK[12].skill_4 = 0;

	//�׵�
	PK[13].x = 0;
	PK[13].y = 0;
	PK[13].attack = 8;
	PK[13].bleed = 30;
	PK[13].defence = 4;
	PK[13].special_attack = 9;
	PK[13].special_defence = 7;
	PK[13].level = 5;
	PK[13].name = "�׵�";
	PK[13].speciese = "��";
	PK[13].skill_1_name = "����";
	PK[13].skill_2_name = "����";
	PK[13].skill_1 = 50;
	PK[13].skill_2 = 80;
	PK[13].skill_3 = 0;
	PK[13].skill_4 = 0;

}

//����Ѫ����ʼ��
void startup_pokemon_bleed()
{
	PK[0].bleed = 32 + (PK[0].level - 5) * 3;
	PK[1].bleed = 30;
	PK[2].bleed = 28;
	PK[3].bleed = 29;
	PK[4].bleed = 32;
	PK[5].bleed = 32;
	PK[6].bleed = 32;
	PK[7].bleed = 32;
	PK[8].bleed = 32;
	PK[9].bleed = 32;
	PK[10].bleed = 32;
	PK[11].bleed = 32;
}
//����λ�ó�ʼ��
void startup_pokemon_destination()
{
	PK[11].x = 488;
	PK[11].y = 553;
}


//��ͼ��ʼ��
void starup_map_show()
{
	initgraph(window_width, window_height);             //��ʼ����ͼ����

	map_init_x = 298;
	map_init_y = 162;                               //��ͼ��ʼʱʱ��ȡ�ӣ�298,162����ʼ�Ĳ���//

	character_x = 170;                                               //����ĳ�ʼλ��
	character_y = 221;

	doctor_tong_x = 444;                            //NPCλ��
	doctor_tong_y = 400;
	NPC_1_x = 914;
	NPC_1_y = 413;
	NPC_2_x = 1097;
	NPC_2_y = 1048;
	NPC_3_x = 632;
	NPC_3_y = 780;

	character_picture_i = 0;
	character_picture_j = 0;
	const char *s = "��Դ�ļ���\\����\\�ռ���ͼ.jpg";
	TCHAR p[40];
	CharToTchar(s, p);
	loadimage(&main_map, p, 1653, 1417);
	loadimage(&character_vice, _T("��Դ�ļ���\\����\\��������ͼ����ͼ.jpg", 136, 200));
	loadimage(&character, _T("��Դ�ļ���\\����\\��������ͼ.jpg", 136, 200));
	BeginBatchDraw();

	//��ͼ���ϰ����������ʽ���0��1��0Ϊ�ϰ������Թ���1Ϊ��ͨ��//
	for (int i = 0; i<1652; i++)
	{
		for (int j = 0; j<1416; j++)
		{
			if (i <= 425 || i >= 1223 - 45 || j <= 210 || j >= 1161 - 50)         //��ͼ�����ܵ���ľ//
			{
				canvas[i][j] = 0;
			}
			else if ((i>430 && i <= 552) && (j>210 && j <= 320))          //���Ϸ��ķ���
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 540 - 45 && i <= 552) && (j>320 && j <= 562))      //���������һ����ľ
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 659 - 45 && i <= 690) && (j >= 300 && j <= 542))     //�ڶ�����ľ
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 799 - 45 && i <= 821) && (j >= 211 && j <= 489))     //��������ľ
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 923 - 45 && i <= 1141) && (j >= 235 && j <= 357))    //���Ϸ��ĳ�������ľ    
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 1121 - 45 && i<1223) && (j >= 404 && j <= 521))
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 699 - 45 && i <= 721) && (j >= 513 && j <= 630))    //�����￪ʼ���м��ɭ�ֿ鶨�����//
			{
				canvas[i][j] = 0;
			}
			else if ((i>721 && i <= 770) && (j >= 543 && j <= 630))       //��������
			{
				canvas[i][j] = 0;
			}
			else if ((i>750 && i <= 917) && (j >= 543 && j <= 732))       //�м�
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 699 - 45 && i <= 917) && (j>702 && j <= 800))    //����
			{
				canvas[i][j] = 0;
			}
			else if ((i>897 && i <= 1007) && (j >= 435 && j <= 997))       //�ұ��������
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 402 && i<664) && (j >= 659 && j <= 725))         //�м䲿��ȫ��������ϣ���������ɢ����ľ�������
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 402 && i <= 587) && (j >= 817 && j <= 1000))       //����
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 646 && i <= 779) && (j >= 862 && j <= 1000))       //������
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 1092 && i<1223 - 45) && (j >= 862 && j <= 1000))   //����
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 828 && i <= 873) && (j >= 992 && j <= 1050))        //������С��
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 1077 && i <= 1125) && (j >= 602 && j <= 808))     //����һ��
			{
				canvas[i][j] = 0;
			}
			else
			{
				canvas[i][j] = 1;
			}
		}

	}
}

//����ˢ��
void pokemon_refresh()
{
	int i;
	for (i = 0; i<pokemon_number; i++)
	{
		if (PK[i].judge == 1 && PK[i].time<10000)       //��һ�����鱻���������judge�ͻ��Ϊ1��Ϊ1�����ʱ�������޷��������ģ�����10000��ѭ��������������ˢ�³���//
		{
			PK[i].time++;
		}
		else if (PK[i].judge == 1 && PK[i].time == 10000)
		{
			PK[i].judge = 0;
			PK[i].time = 0;
		}
	}
}

//��ͼ��ʾ����
void map_show()
{
	putimage(0, 0, window_width, window_height, &main_map, map_init_x, map_init_y);
	putimage(character_x, character_y, 45, 50, &character_vice, character_picture_i * 45, character_picture_j * 50, NOTSRCERASE); //ÿ��С�˵������ǣ�45,50��
	putimage(character_x, character_y, 45, 50, &character, character_picture_i * 45, character_picture_j * 50, SRCINVERT);
	if (plot_judge == 1)                                                                           //�����ж�
	{
		plot_1();
		input = _getch();
		if (input == 'z' || input == 'Z')
		{
			plot_2();
			input = _getch();
			if (input == 'Z' || input == 'z')
			{
				plot_3();
				_getch();
			}
		}
		plot_judge = 0;
	}
	else if (plot_judge == 2)
	{
		plot_4();
		input = _getch();
		if (input == 'z' || input == 'Z')
		{
			plot_5();
			_getch();
			interface_change_animation();		    //�����л�����
			fight_show(&PK[12], &PK[0]);				 //ս����ʾ����
			interface_change_animation();       //�����л�����
			startup_pokemon_bleed();           //���þ���Ѫ��
		}
		plot_judge = 5;
	}
	else if (plot_judge == 3)
	{
		plot_8();
		_getch();
		interface_change_animation();		    //�����л�����
		fight_show(&PK[13], &PK[0]);				 //ս����ʾ����
		interface_change_animation();       //�����л�����
		startup_pokemon_bleed();           //���þ���Ѫ��
		plot_judge = 6;
	}
	else if (plot_judge == 4)
	{
		plot_12();
		input = _getch();
		if (input == 'z' || input == 'Z')
		{
			plot_13();
			input = _getch();
			if (input == 'z' || input == 'Z')
			{
				plot_14();
				input = _getch();
				if (input == 'z' || input == 'Z')
				{
					plot_15();
					_getch();
					interface_change_animation();		    //�����л�����
					fight_show(&PK[7], &PK[0]);				 //ս����ʾ����
					interface_change_animation();       //�����л�����
					startup_pokemon_bleed();           //���þ���Ѫ��
				}
			}
		}
		_getch();
		plot_judge = 0;
	}
	if (plot_judge == 5)
	{
		plot_6();
		input = _getch();
		if (input == 'Z' || input == 'z')
		{
			plot_7();
			_getch();
		}
		plot_judge = 0;
	}
	if (plot_judge == 6)
	{
		plot_9();
		input = _getch();
		if (input == 'Z' || input == 'z')
		{
			plot_10();
			input = _getch();
			if (input == 'z' || input == 'Z')
			{
				plot_11();
				_getch();
			}
		}
		plot_judge = 0;
	}
	else
	{
		FlushBatchDraw();
	}
}

//������������
void operate()
{
	if (_kbhit())
	{                                                     //ÿ���ƶ�20�����ص�λ 
		input = _getch();
		if (character_picture_i == 2)               //ʵ���˽���ȡ����ͼ�Ĳ�ͬ����
		{
			character_picture_i = -1;
		}
		if ((input == 'A' || input == 'a') && canvas[map_init_x + character_x - 20][map_init_y + character_y] != 0)             //���ݷ�������������ݵĸ���
		{
			map_init_x -= 10;                       //10Ϊ�˵Ĳ���//
			character_picture_j = 2;
		}
		else if ((input == 'A' || input == 'a') && canvas[map_init_x + character_x - 20][map_init_y + character_y] == 0)
		{
			character_picture_j = 2;
		}
		if ((input == 'D' || input == 'd') && canvas[map_init_x + character_x + 20][map_init_y + character_y] != 0)           //�����ж����ж��н������Ƿ�Ϊ�ϰ���//
		{
			map_init_x += 10;
			character_picture_j = 1;
		}
		else if ((input == 'D' || input == 'd') && canvas[map_init_x + character_x + 20][map_init_y + character_y] == 0)
		{
			character_picture_j = 1;
		}
		if ((input == 'S' || input == 's') && canvas[map_init_x + character_x][map_init_y + character_y + 20] != 0)
		{
			map_init_y += 10;
			character_picture_j = 0;
		}
		else if ((input == 'S' || input == 's') && canvas[map_init_x + character_x][map_init_y + character_y + 20] == 0)
		{
			character_picture_j = 0;
		}
		if ((input == 'W' || input == 'w') && canvas[map_init_x + character_x][map_init_y + character_y - 20] != 0)
		{
			map_init_y -= 10;
			character_picture_j = 3;
		}
		else if ((input == 'W' || input == 'w') && canvas[map_init_x + character_x][map_init_y + character_y - 20] == 0)
		{
			character_picture_j = 3;
		}
		if ((input == 'Z' || input == 'z') && abs(map_init_x + character_x - doctor_tong_x) <= 30 && abs(map_init_y + character_y - doctor_tong_y) <= 30)
		{
			plot_judge = 1;
		}
		else if ((input == 'Z' || input == 'z') && abs(map_init_x + character_x - NPC_1_x) <= 30 && abs(map_init_y + character_y - NPC_1_y) <= 30)
		{
			plot_judge = 2;
		}
		else if ((input == 'Z' || input == 'z') && abs(map_init_x + character_x - NPC_2_x) <= 30 && abs(map_init_y + character_y - NPC_2_y) <= 30)
		{
			plot_judge = 3;
		}
		else if ((input == 'Z' || input == 'z') && abs(map_init_x + character_x - NPC_3_x) <= 30 && abs(map_init_y + character_y - NPC_3_y) <= 30)
		{
			plot_judge = 4;
		}
		if (input == 'q' || input == 'Q')
		{
			pause_menu();
		}
		character_picture_i++;
	}
}
//����з�����ͼƬ
void load_PK_picture(pokemon *PK)
{
	char ch_path1[60] = "��Դ�ļ���\\����\\";                                     //·��ǰ��
	char ch_path2[60] = ".jpg";                                            //·�����
	char ch_path3[60] = "bk.jpg";
	char ch_path4[60] = "��Դ�ļ���\\����\\";
	strcat_s(ch_path1, PK->name);          //��·��������������
	strcat_s(ch_path1, ch_path2);
	strcat_s(ch_path4, PK->name);
	strcat_s(ch_path4, ch_path3);
	TCHAR p1[60];
	TCHAR p2[60];
	CharToTchar(ch_path1, p1);
	CharToTchar(ch_path4, p2);
	//��·�����ָĳ�TCHAR����������//

	static int jumpy_1 = 90;          //�þ��鿴��������������
	static int jump = 5;
	if (jump == 5)
	{
		jumpy_1 = 90;
	}

	if (jump == 10)
	{
		jump = 0;
		jumpy_1 = 95;
	}
	jump++;
	//��ʾ�з�����//
	IMAGE im1, im2;
	loadimage(&im1, p1);           //��TCHAR��ʽ����ͼƬ
	loadimage(&im2, p2);
	putimage(400, jumpy_1, &im2, NOTSRCERASE);
	putimage(400, jumpy_1, &im1, SRCINVERT);
}
//�����л�����
void interface_change_animation()
{
	int i, j;
	i = 320, j = 0;                                            //�����Ϸ���ʼ��
	setlinecolor(BLACK);                              //������ɫ����Ϊ��ɫ
	while (!(i == 319 && j == 0))
	{
		line(320, 240, i, j);
		FlushBatchDraw();
		if (i == 640)
			j++;
		if (i == 0)
			j--;
		if (j == 600)
			i--;
		if (j == 0)
			i++;
	}
	//�����ﶯ������
}
//�з�����ͼƬ�����Լ�������ʾ
void enemy_fight_show(pokemon *PK_enemy)
{
	load_PK_picture(PK_enemy);
}
//ս����ʾ����
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

	int fullbleed = PK_own->bleed;				//�ҷ���ѪѪ��
	int fullbleed2 = PK_enemy->bleed;           //�з���ѪѪ��

	int bleed_Width2 = 125;
	int bleed_Width1 = 180;					    //�ҷ�Ѫ������

	int fullexercise_Width = 240;                  //������۳���

	while (1)
	{
		IMAGE img1;
		loadimage(&img1, _T("��Դ�ļ���\\����\\ս������1.jpg"));
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

		if (jump == 5)
		{
			jumpy = 150;                                //��������ѭ����������
		}

		if (jump == 10)
		{
			jumpy = 155;
			jump = 0;
		}
		jump++;


		//Ƥ����
		IMAGE im1, im2;
		loadimage(&im1, _T("��Դ�ļ���\\����\\Ƥ����.jpg"));
		loadimage(&im2, _T("��Դ�ļ���\\����\\Ƥ����bk.jpg"));
		putimage(65, jumpy, &im2, NOTSRCERASE);
		putimage(65, jumpy, &im1, SRCINVERT);

		//�ҷ��ȼ�
		TCHAR Lv[5];
		_stprintf_s(Lv, _T("%d"), PK_own->level);
		outtextxy(500, 230, Lv);
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

		//�ҷ������
		setlinestyle(PS_SOLID, 2);
		setlinecolor(LIGHTGRAY);
		setfillcolor(WHITE);
		fillroundrect(335, 300, 575, 305, 10, 10);

		setfillcolor(GREEN);
		solidroundrect(337, 302, 337 + exercise_Width, 302, 10, 10);

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
		if (choose == 1)
		{
			setfillcolor(BLACK);
			POINT pts[] = { { choice_x, choice_y },{ choice_x,choice_y + 20 },{ choice_x + 15, choice_y + 10 } };
			solidpolygon(pts, 3);

			char input;
			if (_kbhit())
			{
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
				if ((input == 'z' || input == 'Z') && choice_x == 370 + 130 && choice_y == 365)
				{
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
		if (choose == 0)
		{
			//����ѡ��ͼ��
			setfillcolor(BLACK);
			POINT pts[] = { { x, y },{ x, y + 20 },{ x + 15, y + 10 } };
			solidpolygon(pts, 3);

			LOGFONT f;
			gettextstyle(&f);                     // ��ȡ��ǰ��������
			f.lfHeight = 20;                      // ��������߶�
			_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			settextstyle(&f);                      // ����������ʽ
			outtextxy(30 + 20, 365, _T("ʮ�����"));
			outtextxy(190 + 20, 365, _T("���"));
			outtextxy(30 + 20, 365 + 60, _T("��Ų�"));
			outtextxy(190 + 20, 365 + 60, _T("����"));

			//�жϵз�������û������//
			if (PK_enemy->bleed <= 0)
			{
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
				pokemon_experiece += 30;   //�ҷ����龭������
				if (pokemon_experiece >= 200 + (PK_own->level - 5) * 100)
				{
					PK_own->level++;
					exercise_Width = (pokemon_experiece - 50 * PK_own->level*PK_own->level + 350 * PK_own->level - 500)*1.0 / (200 + (PK_own->level - 5) * 100)*fullexercise_Width;   //����ۿ��

				}
				else
				{
					if (PK_own->level == 5)
						exercise_Width = pokemon_experiece * 1.0 / 200 * fullexercise_Width;
					else if (PK_own->level>5)
						exercise_Width = (pokemon_experiece - 50 * PK_own->level*PK_own->level + 350 * PK_own->level - 500)*1.0 / (200 + (PK_own->level - 5) * 100)*fullexercise_Width;   //����ۿ��
				}
				break;


			}
			//�жϼ���������û������//
			if (PK_own->bleed <= 0)
			{
				TCHAR s[] = _T("defeated");
				settextstyle(16, 0, _T("����"));
				outtextxy(window_width / 2 - 10, window_height / 2, s);    //��ʾ��Ϸ���//
				PK_enemy->judge = 1;
				break;
			}

			//control���Ʋ���
			if (_kbhit())										 //�����ж�
			{
				input = _getch();
				if ((input == 'd' || input == 'D') && x < 190)
					x += 160;
				if ((input == 'a' || input == 'A') && x > 30)
					x -= 160;
				if ((input == 's' || input == 'S') && y<365 + 60)
					y += 60;
				if ((input == 'w' || input == 'W') && y > 365)
					y -= 60;
				if (input == 'z' || input == 'Z')
				{
					if (x == 30 && y == 365)
					{
						lighting();
						PK_enemy->bleed = PK_enemy->bleed - ((PK_own->level*0.4 + 2)*PK_own->skill_1*PK_own->attack / (PK_enemy->defence*50.0) + 2);  //�˺�ֵ����//
					}
					if (x == 190 && y == 365)
					{
						scream();
						PK_enemy->bleed = PK_enemy->bleed - ((PK_own->level*0.4 + 2)*PK_own->skill_2*PK_own->attack / (PK_enemy->defence*50.0) + 2);  //�˺�ֵ����//
					}
					if (x == 30 && y == 365 + 60)
					{
						flash();
						PK_enemy->bleed = PK_enemy->bleed - ((PK_own->level*0.4 + 2)*PK_own->skill_3*PK_own->attack / (PK_enemy->defence*50.0) + 2);  //�˺�ֵ����//
					}
					if (x == 190 && y == 365 + 60)
					{
						thunder();
						PK_enemy->bleed = PK_enemy->bleed - ((PK_own->level*0.4 + 2)*PK_own->skill_3*PK_own->attack / (PK_enemy->defence*50.0) + 2);  //�˺�ֵ����//
					}
					if (PK_enemy->bleed >= 0)
					{
						bleed_Width2 = PK_enemy->bleed*1.0 / fullbleed2 * 125;
					}
					else
					{
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
//ս������
void fight()
{
	int i;
	for (i = 0; i<pokemon_number; i++)				 //���������������飬
	{
		if (abs(map_init_x + character_x - PK[i].x) <= 15 && abs(map_init_y + character_y - PK[i].y) <= 15 && PK[i].judge == 0)
		{
			interface_change_animation();		    //�����л�����
			fight_show(&PK[i], &PK[0]);				 //ս����ʾ����
			interface_change_animation();       //�����л�����
			startup_pokemon_bleed();           //���þ���Ѫ��
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//���鲿��
void plot_1()
{
	setfillcolor(LIGHTGRAY);                   //�Ի���
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//���½�չ�ֶԻ�����
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(16, 350, _T("ͯ��ʿ����ӭ�����Ӻ�ɭ�ֹ�԰������������ѧУ��"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 375, _T("�ص�С���飬����һֱ��������������һƬɭ���У�"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 400, _T("�������ɭ���������һֻ���ޣ����ǵ�С�����"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 425, _T("��ʧ�ٻ������ˣ����������ټ�ȫУ����ʿ��������"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 450, _T("������ֻ���ޣ�������ҵر�ѡ���ˡ�"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_2()
{
	setfillcolor(LIGHTGRAY);                   //�Ի���
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//���½�չ�ֶԻ�����
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(16, 350, _T("�Ӻ���������һ���岻�ݴǣ�"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_3()
{
	setfillcolor(LIGHTGRAY);                   //�Ի���
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//���½�չ�ֶԻ�����
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(16, 350, _T("ͯ��ʿ������Ƥ�����ڽ�������̽�������������"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 375, _T("�����ҡ����꣬�¸ҵ�ǰ���ɣ����ҵ�ʧ�ٵ�ˮ����"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 400, _T("�������ڶ��޵������׹����"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_4()
{
	setfillcolor(LIGHTGRAY);                   //�Ի���
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//���½�չ�ֶԻ�����
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(16, 350, _T("�׾���С�Ӳ�����ˣ��Ҵ��ҵ���أ�"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_5()
{
	setfillcolor(LIGHTGRAY);                   //�Ի���
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//���½�չ�ֶԻ�����
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(16, 350, _T("�Ӻ���������˵�ϻ�����ս����"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_6()
{
	setfillcolor(LIGHTGRAY);                   //�Ի���
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//���½�չ�ֶԻ�����
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(16, 350, _T("ˮ����лл������ң�ǰ���·��������գ������"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 375, _T("��ɭ���ﲻ̫���Ƶľ��飬��������ħ��ǰ�������"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 400, _T("ͨ�����������Լ������ˣ��ҵ������׵۱���ħ����"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 425, _T("	�ˣ����ܾȾ���ô��"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_7()
{
	setfillcolor(LIGHTGRAY);                   //�Ի���
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//���½�չ�ֶԻ�����
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(16, 350, _T("�Ӻ���������Ȼû���⣡"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_8()
{
	setfillcolor(LIGHTGRAY);                   //�Ի���
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//���½�չ�ֶԻ�����
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(16, 350, _T("�׵ۣ���·��ͨ��"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_9()
{
	setfillcolor(LIGHTGRAY);                   //�Ի���
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//���½�չ�ֶԻ�����
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(16, 350, _T("�׵ۣ�����ô�ˡ�������ô�����"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_10()
{
	setfillcolor(LIGHTGRAY);                   //�Ի���
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//���½�չ�ֶԻ�����
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(16, 350, _T("�Ӻ�������ûʲô��ˮ�����ϵط������أ����ȥ�ɣ�"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_11()
{
	setfillcolor(LIGHTGRAY);                   //�Ի���
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//���½�չ�ֶԻ�����
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(16, 350, _T("�׵ۣ��ã�лл�㣡"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_12()
{
	setfillcolor(LIGHTGRAY);                   //�Ի���
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//���½�չ�ֶԻ�����
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(16, 350, _T("·�����ǣ�С�ӣ�������һֱ���ҵĵ�������Ұô��"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_13()
{
	setfillcolor(LIGHTGRAY);                   //�Ի���
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//���½�չ�ֶԻ�����
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(16, 350, _T("�Ӻ�������������˭����Ұ�������ǺӺ���԰������"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 375, _T("�о���ļ�!"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_14()
{
	setfillcolor(LIGHTGRAY);                   //�Ի���
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//���½�չ�ֶԻ�����
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(16, 350, _T("·�����ǣ������������ɣ�������˭�ĵ��̣�������"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 375, _T("ʵ��˵����!"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_15()
{
	setfillcolor(LIGHTGRAY);                   //�Ի���
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//���½�չ�ֶԻ�����
	LOGFONT f;
	gettextstyle(&f);                     // ��ȡ��ǰ��������
	f.lfHeight = 25;                      // ��������߶�
	_tcscpy_s(f.lfFaceName, _T("����"));    // ��������
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // ����������ʽ
	outtextxy(16, 350, _T("�Ӻ��������㡣�����ɶ񡣡���"));
	FlushBatchDraw();
	Sleep(1000);
}

////////////////////////
//������
void main()
{
	startup_pokemon_judge();					  //�Ծ���ʱ�����Խ��г�ʼ��
	startup_pokemon();						     //�Ծ���������Խ��г�ʼ��
	startup_pokemon_bleed();                   //�Ծ���Ѫ�����г�ʼ��
	startup_pokemon_destination();		      //�Ծ���λ�ý��г�ʼ��
	starup_map_show();                             //�Ե�ͼ���г�ʼ��
	start_menu();                                  //��½����
	while (1)
	{
		pokemon_refresh();                            //����ˢ��
		map_show();										//��ͼ��ʾ����
		fight();												//ս������
		operate();								// �ͻ���������
	}
}


