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
//全局变量
#define window_height 480
#define window_width  640                  //窗口大小

#define pokemon_number 30              //精灵数量

int game_status;
int map_init_x, map_init_y;
int character_x, character_y;
int character_picture_i, character_picture_j;
int pokemon_experiece = 0;                //定义我方精灵经验
int exercise_Width = 0;                         //我方经验槽长度
int canvas[1652][1416] = { 0 };               //定义画布坐标 使每个像素点坐标为0

											  //NPC的位置坐标
int doctor_tong_x, doctor_tong_y;
int NPC_1_x, NPC_1_y;
int NPC_2_x, NPC_2_y;
int NPC_3_x, NPC_3_y;
int plot_judge;                       //判断在地图刷新的时候是否切入剧情

char input;                                         //输入判断变量

IMAGE main_map;                              //地图图像对象
IMAGE character_vice;
IMAGE character;


//定义精灵数据的结构体
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
	int skill_1;                    //四项技能的基础伤害//
	int skill_2;
	int skill_3;
	int skill_4;
	const char *skill_1_name;      //技能的名称
	const char *skill_2_name;
	int judge;
	int time;                             //在一定时间以后将把原位置的精灵重新刷新出来
}PK[pokemon_number];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//所有函数声明
//一、剧情函数
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
//二、界面函数，文档保存读取函数
void start_menu();
void pause_menu();
void readfile();
void writefile();
//三、数据更新函数，战斗函数，动画函数
void starup_pokemon_judge();//精灵时间初始化
void starup_pokemon();//精灵基础属性初始化
void starup_pokemon_bleed();//精灵血量初始化
void starup_pokemon_desination();//精灵位置初始化
void starup_map_show();//地图初始化
void pokemon_refresh();//精灵刷新
void map_show();//地图显示函数
void operate();//交互操作函数
void load_PK_picture(pokemon *PK);//导入地方精灵图片
void interface_change_animation();//界面切换动画
void enemy_fight_show(pokemon *PK_enemy);//敌方精灵图片加载以及技能显示
void fight_show(pokemon *PK_enemy, pokemon *PK_own);//战斗显示函数
void fight();//战斗函数
			 ///////////////////////////////////////////////////////////////////////////////////////////////

			 //游戏开场界面和暂停界面
void start_menu()
{
	IMAGE starup_window;

	loadimage(&starup_window, _T("资源文件夹\\其它\\登陆界面.jpg"), 640, 480);
	putimage(0, 0, 640, 480, &starup_window, 0, 0);

	//设置登录画面文字
	LOGFONT f;    //这个结构体定义了字体的属性。
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 30;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(300, 140, _T("1 新游戏"));
	outtextxy(280, 240, _T("2 读取存档"));
	outtextxy(310, 340, _T("3 退出"));

	LOGFONT t;
	gettextstyle(&t);                     // 获取当前字体设置
	t.lfHeight = 68;                      // 设置字体高度为 48
	_tcscpy_s(t.lfFaceName, _T("楷体"));
	settextcolor(BLUE);
	t.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&t);                     // 设置字体样式
	outtextxy(200, 40, _T("口袋妖怪"));

	LOGFONT m;
	gettextstyle(&m);                     // 获取当前字体设置
	m.lfHeight = 30;                      // 设置字体高度为 48
	_tcscpy_s(m.lfFaceName, _T("楷体"));
	settextcolor(BLUE);
	t.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&m);                     // 设置字体样式
	outtextxy(460, 70, _T("(河海版)"));
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

	loadimage(&starup_window, _T("资源文件夹\\其它\\登陆界面.jpg"), 640, 480);
	putimage(0, 0, 640, 480, &starup_window, 0, 0);

	//设置暂停画面文字
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 30;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(300, 140, _T("1 继续游戏"));
	outtextxy(310, 240, _T("2 存档"));
	outtextxy(310, 340, _T("3 退出"));
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

//读档和存档的函数
void readfile()
{
	FILE *fp;
	fopen_s(&fp,"资源文件夹\\历史\\游戏数据.txt", "w");
	fscanf_s(fp, "%d %d %d %d ", map_init_x, map_init_y, character_picture_i, character_picture_j);
	fclose(fp);
}

void writefile()
{
	FILE *fp;
	fopen_s(&fp,"资源文件夹\\历史\\游戏数据.txt", "w");
	fprintf(fp, "%d %d %d %d", map_init_x, map_init_y, character_picture_i, character_picture_j);
	fclose(fp);
}

//精灵时间属性初始化
void startup_pokemon_judge()
{
	int i;
	for (i = 0; i <= pokemon_number; i++)
	{
		PK[i].time = 0;
	}
}
//精灵基础属性初始化
void startup_pokemon()
{
	//皮卡丘//
	PK[0].level = 5;
	PK[0].x = 0;
	PK[0].y = 0;
	PK[0].attack = 8 + (PK[0].level - 5) * 2;
	PK[0].bleed = 32 + (PK[0].level - 5) * 3;
	PK[0].defence = 4 + (PK[0].level - 5);
	PK[0].special_attack = 9 + (PK[0].level - 5) * 2;
	PK[0].special_defence = 7 + (PK[0].level - 5);
	PK[0].name = "皮卡丘";
	PK[0].speciese = "电";
	PK[0].skill_1 = 50;
	PK[0].skill_2 = 0;
	PK[0].skill_3 = 60;
	PK[0].skill_4 = 100;
	PK[0].judge = 1;

	//小火龙//
	PK[1].x = 100;                       //精灵在地图上的坐标//
	PK[1].y = 200;
	PK[1].attack = 8;                    //普攻
	PK[1].bleed = 30;                    //生命值
	PK[1].defence = 4;                   //普防
	PK[1].special_attack = 9;            //特攻
	PK[1].special_defence = 7;           //特防
	PK[1].level = 5;                   //等级
	PK[1].name = "小火龙";             //名称
	PK[1].speciese = "火";             //元素属性
	PK[1].skill_1_name = "打雷"; //技能1名称
	PK[1].skill_2_name = "打雷"; //技能2名称
	PK[1].skill_1 = 50;                  //技能1伤害
	PK[1].skill_2 = 80;                  //技能2伤害
	PK[1].skill_3 = 0;
	PK[1].skill_4 = 0;
	PK[1].judge = 0;

	//妙蛙种子//
	PK[2].x = 0;
	PK[2].y = 0;
	PK[2].attack = 6;
	PK[2].bleed = 28;
	PK[2].defence = 3;
	PK[2].special_attack = 8;
	PK[2].special_defence = 6;
	PK[2].level = 5;
	PK[2].name = "妙蛙种子";
	PK[2].speciese = "草";
	PK[2].skill_1_name = "打雷";
	PK[2].skill_2_name = "打雷";
	PK[2].skill_1 = 30;
	PK[2].skill_2 = 40;
	PK[2].skill_3 = 0;
	PK[2].skill_4 = 0;

	//鲤鱼王//
	PK[3].x = 0;
	PK[3].y = 0;
	PK[3].attack = 7;
	PK[3].bleed = 29;
	PK[3].defence = 5;
	PK[3].special_attack = 10;
	PK[3].special_defence = 6;
	PK[3].level = 5;
	PK[3].name = "鲤鱼王";
	PK[3].speciese = "水";
	PK[3].skill_1_name = "打雷";
	PK[3].skill_2_name = "打雷";
	PK[3].skill_1 = 70;
	PK[3].skill_2 = 80;
	PK[3].skill_3 = 0;
	PK[3].skill_4 = 0;

	//不良蛙//
	PK[4].x = 0;
	PK[4].y = 0;
	PK[4].attack = 8;
	PK[4].bleed = 30;
	PK[4].defence = 4;
	PK[4].special_attack = 9;
	PK[4].special_defence = 7;
	PK[4].level = 5;
	PK[4].name = "不良蛙";
	PK[4].speciese = "毒";
	PK[4].skill_1_name = "打雷";
	PK[4].skill_2_name = "打雷";
	PK[4].skill_1 = 35;
	PK[4].skill_2 = 60;
	PK[4].skill_3 = 0;
	PK[4].skill_4 = 0;

	//电力怪//
	PK[5].x = 0;
	PK[5].y = 0;
	PK[5].attack = 8;
	PK[5].bleed = 30;
	PK[5].defence = 4;
	PK[5].special_attack = 9;
	PK[5].special_defence = 7;
	PK[5].level = 5;
	PK[5].name = "电力怪";
	PK[5].speciese = "电";
	PK[5].skill_1_name = "打雷";
	PK[5].skill_2_name = "打雷";
	PK[5].skill_1 = 35;
	PK[5].skill_2 = 40;
	PK[5].skill_3 = 0;
	PK[5].skill_4 = 0;

	//大螃蟹//
	PK[6].x = 0;
	PK[6].y = 0;
	PK[6].attack = 8;
	PK[6].bleed = 30;
	PK[6].defence = 4;
	PK[6].special_attack = 9;
	PK[6].special_defence = 7;
	PK[6].level = 5;
	PK[6].name = "大螃蟹";
	PK[6].speciese = "水";
	PK[6].skill_1_name = "打雷";
	PK[6].skill_2_name = "打雷";
	PK[6].skill_1 = 45;
	PK[6].skill_2 = 83;
	PK[6].skill_3 = 0;
	PK[6].skill_4 = 0;

	//路卡利欧//
	PK[7].x = 0;
	PK[7].y = 0;
	PK[7].attack = 8;
	PK[7].bleed = 30;
	PK[7].defence = 4;
	PK[7].special_attack = 9;
	PK[7].special_defence = 7;
	PK[7].level = 5;
	PK[7].name = "路卡利欧";
	PK[7].speciese = "格斗";
	PK[7].skill_1_name = "打雷";
	PK[7].skill_2_name = "打雷";
	PK[7].skill_1 = 50;
	PK[7].skill_2 = 80;
	PK[7].skill_3 = 0;
	PK[7].skill_4 = 0;

	//伊布//
	PK[8].x = 0;
	PK[8].y = 0;
	PK[8].attack = 8;
	PK[8].bleed = 30;
	PK[8].defence = 4;
	PK[8].special_attack = 9;
	PK[8].special_defence = 7;
	PK[8].level = 5;
	PK[8].name = "伊布";
	PK[8].speciese = "正常";
	PK[8].skill_1_name = "打雷";
	PK[8].skill_2_name = "打雷";
	PK[8].skill_1 = 50;
	PK[8].skill_2 = 80;
	PK[8].skill_3 = 0;
	PK[8].skill_4 = 0;

	//皮丘//
	PK[9].x = 0;
	PK[9].y = 0;
	PK[9].attack = 8;
	PK[9].bleed = 30;
	PK[9].defence = 4;
	PK[9].special_attack = 9;
	PK[9].special_defence = 7;
	PK[9].level = 5;
	PK[9].name = "皮丘";
	PK[9].speciese = "电";
	PK[9].skill_1_name = "打雷";
	PK[9].skill_2_name = "打雷";
	PK[9].skill_1 = 50;
	PK[9].skill_2 = 80;
	PK[9].skill_3 = 0;
	PK[9].skill_4 = 0;

	//小火猴//
	PK[10].x = 0;
	PK[10].y = 0;
	PK[10].attack = 8;
	PK[10].bleed = 30;
	PK[10].defence = 4;
	PK[10].special_attack = 9;
	PK[10].special_defence = 7;
	PK[10].level = 5;
	PK[10].name = "小火猴";
	PK[10].speciese = "火";
	PK[10].skill_1_name = "打雷";
	PK[10].skill_2_name = "打雷";
	PK[10].skill_1 = 50;
	PK[10].skill_2 = 80;
	PK[10].skill_3 = 0;
	PK[10].skill_4 = 0;

	//优雅猫//
	PK[11].x = 0;
	PK[11].y = 0;
	PK[11].attack = 8;
	PK[11].bleed = 30;
	PK[11].defence = 4;
	PK[11].special_attack = 9;
	PK[11].special_defence = 7;
	PK[11].level = 5;
	PK[11].name = "优雅猫";
	PK[11].speciese = "正常";
	PK[11].skill_1_name = "打雷";
	PK[11].skill_2_name = "打雷";
	PK[11].skill_1 = 50;
	PK[11].skill_2 = 80;
	PK[11].skill_3 = 0;
	PK[11].skill_4 = 0;

	//雷公
	PK[12].x = 0;
	PK[12].y = 0;
	PK[12].attack = 8;
	PK[12].bleed = 30;
	PK[12].defence = 4;
	PK[12].special_attack = 9;
	PK[12].special_defence = 7;
	PK[12].level = 5;
	PK[12].name = "雷公";
	PK[12].speciese = "电";
	PK[12].skill_1_name = "打雷";
	PK[12].skill_2_name = "打雷";
	PK[12].skill_1 = 50;
	PK[12].skill_2 = 80;
	PK[12].skill_3 = 0;
	PK[12].skill_4 = 0;

	//炎帝
	PK[13].x = 0;
	PK[13].y = 0;
	PK[13].attack = 8;
	PK[13].bleed = 30;
	PK[13].defence = 4;
	PK[13].special_attack = 9;
	PK[13].special_defence = 7;
	PK[13].level = 5;
	PK[13].name = "炎帝";
	PK[13].speciese = "火";
	PK[13].skill_1_name = "打雷";
	PK[13].skill_2_name = "打雷";
	PK[13].skill_1 = 50;
	PK[13].skill_2 = 80;
	PK[13].skill_3 = 0;
	PK[13].skill_4 = 0;

}

//精灵血量初始化
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
//精灵位置初始化
void startup_pokemon_destination()
{
	PK[11].x = 488;
	PK[11].y = 553;
}


//地图初始化
void starup_map_show()
{
	initgraph(window_width, window_height);             //初始化绘图环境

	map_init_x = 298;
	map_init_y = 162;                               //地图初始时时截取从（298,162）开始的部分//

	character_x = 170;                                               //人物的初始位置
	character_y = 221;

	doctor_tong_x = 444;                            //NPC位置
	doctor_tong_y = 400;
	NPC_1_x = 914;
	NPC_1_y = 413;
	NPC_2_x = 1097;
	NPC_2_y = 1048;
	NPC_3_x = 632;
	NPC_3_y = 780;

	character_picture_i = 0;
	character_picture_j = 0;
	const char *s = "资源文件夹\\其它\\终极地图.jpg";
	TCHAR p[40];
	CharToTchar(s, p);
	loadimage(&main_map, p, 1653, 1417);
	loadimage(&character_vice, _T("资源文件夹\\其它\\桌面行走图遮罩图.jpg", 136, 200));
	loadimage(&character, _T("资源文件夹\\其它\\桌面行走图.jpg", 136, 200));
	BeginBatchDraw();

	//地图上障碍以数组的形式存放0，1，0为障碍不可以过，1为可通行//
	for (int i = 0; i<1652; i++)
	{
		for (int j = 0; j<1416; j++)
		{
			if (i <= 425 || i >= 1223 - 45 || j <= 210 || j >= 1161 - 50)         //地图最四周的树木//
			{
				canvas[i][j] = 0;
			}
			else if ((i>430 && i <= 552) && (j>210 && j <= 320))          //左上方的房子
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 540 - 45 && i <= 552) && (j>320 && j <= 562))      //房子下面的一排树木
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 659 - 45 && i <= 690) && (j >= 300 && j <= 542))     //第二排树木
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 799 - 45 && i <= 821) && (j >= 211 && j <= 489))     //第三排树木
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 923 - 45 && i <= 1141) && (j >= 235 && j <= 357))    //右上方的长方形树木    
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 1121 - 45 && i<1223) && (j >= 404 && j <= 521))
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 699 - 45 && i <= 721) && (j >= 513 && j <= 630))    //从这里开始将中间的森林块定义完毕//
			{
				canvas[i][j] = 0;
			}
			else if ((i>721 && i <= 770) && (j >= 543 && j <= 630))       //中上两棵
			{
				canvas[i][j] = 0;
			}
			else if ((i>750 && i <= 917) && (j >= 543 && j <= 732))       //中间
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 699 - 45 && i <= 917) && (j>702 && j <= 800))    //左下
			{
				canvas[i][j] = 0;
			}
			else if ((i>897 && i <= 1007) && (j >= 435 && j <= 997))       //右边最长的两排
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 402 && i<664) && (j >= 659 && j <= 725))         //中间部分全部设置完毕，将四周零散的树木设置完毕
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 402 && i <= 587) && (j >= 817 && j <= 1000))       //左下
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 646 && i <= 779) && (j >= 862 && j <= 1000))       //左下中
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 1092 && i<1223 - 45) && (j >= 862 && j <= 1000))   //右下
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 828 && i <= 873) && (j >= 992 && j <= 1050))        //单独的小树
			{
				canvas[i][j] = 0;
			}
			else if ((i >= 1077 && i <= 1125) && (j >= 602 && j <= 808))     //右中一排
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

//精灵刷新
void pokemon_refresh()
{
	int i;
	for (i = 0; i<pokemon_number; i++)
	{
		if (PK[i].judge == 1 && PK[i].time<10000)       //当一个精灵被遇到后就其judge就会变为1，为1的这段时间里是无法被遇到的，但在10000次循环后他将被重新刷新出来//
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

//地图显示函数
void map_show()
{
	putimage(0, 0, window_width, window_height, &main_map, map_init_x, map_init_y);
	putimage(character_x, character_y, 45, 50, &character_vice, character_picture_i * 45, character_picture_j * 50, NOTSRCERASE); //每个小人的像素是（45,50）
	putimage(character_x, character_y, 45, 50, &character, character_picture_i * 45, character_picture_j * 50, SRCINVERT);
	if (plot_judge == 1)                                                                           //剧情判断
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
			interface_change_animation();		    //界面切换动画
			fight_show(&PK[12], &PK[0]);				 //战斗显示函数
			interface_change_animation();       //界面切换动画
			startup_pokemon_bleed();           //重置精灵血量
		}
		plot_judge = 5;
	}
	else if (plot_judge == 3)
	{
		plot_8();
		_getch();
		interface_change_animation();		    //界面切换动画
		fight_show(&PK[13], &PK[0]);				 //战斗显示函数
		interface_change_animation();       //界面切换动画
		startup_pokemon_bleed();           //重置精灵血量
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
					interface_change_animation();		    //界面切换动画
					fight_show(&PK[7], &PK[0]);				 //战斗显示函数
					interface_change_animation();       //界面切换动画
					startup_pokemon_bleed();           //重置精灵血量
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

//交互操作函数
void operate()
{
	if (_kbhit())
	{                                                     //每次移动20个像素单位 
		input = _getch();
		if (character_picture_i == 2)               //实现了交替取人物图的不同部分
		{
			character_picture_i = -1;
		}
		if ((input == 'A' || input == 'a') && canvas[map_init_x + character_x - 20][map_init_y + character_y] != 0)             //根据方向操作进行数据的更新
		{
			map_init_x -= 10;                       //10为人的步长//
			character_picture_j = 2;
		}
		else if ((input == 'A' || input == 'a') && canvas[map_init_x + character_x - 20][map_init_y + character_y] == 0)
		{
			character_picture_j = 2;
		}
		if ((input == 'D' || input == 'd') && canvas[map_init_x + character_x + 20][map_init_y + character_y] != 0)           //最后的判断是判断行进方向是否为障碍物//
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
//导入敌方精灵图片
void load_PK_picture(pokemon *PK)
{
	char ch_path1[60] = "资源文件夹\\其它\\";                                     //路径前端
	char ch_path2[60] = ".jpg";                                            //路径后端
	char ch_path3[60] = "bk.jpg";
	char ch_path4[60] = "资源文件夹\\其它\\";
	strcat_s(ch_path1, PK->name);          //将路径名称链接起来
	strcat_s(ch_path1, ch_path2);
	strcat_s(ch_path4, PK->name);
	strcat_s(ch_path4, ch_path3);
	TCHAR p1[60];
	TCHAR p2[60];
	CharToTchar(ch_path1, p1);
	CharToTchar(ch_path4, p2);
	//将路径名字改成TCHAR类型来调用//

	static int jumpy_1 = 90;          //让精灵看起来在上下跳动
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
	//显示敌方精灵//
	IMAGE im1, im2;
	loadimage(&im1, p1);           //以TCHAR形式导入图片
	loadimage(&im2, p2);
	putimage(400, jumpy_1, &im2, NOTSRCERASE);
	putimage(400, jumpy_1, &im1, SRCINVERT);
}
//界面切换动画
void interface_change_animation()
{
	int i, j;
	i = 320, j = 0;                                            //从正上方开始画
	setlinecolor(BLACK);                              //画线颜色设置为黑色
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
	//到这里动画结束
}
//敌方精灵图片加载以及技能显示
void enemy_fight_show(pokemon *PK_enemy)
{
	load_PK_picture(PK_enemy);
}
//战斗显示函数
void fight_show(pokemon *PK_enemy, pokemon *PK_own)
{
	int x = 30;
	int y = 365;                                       //技能选择图标坐标

	int choice_x = 370;
	int choice_y = 365;								//开始界面选择
	int choose = 1;                                  //选择战斗or逃跑的判断

	int jumpy = 150;                               //己方精灵坐标
	int jump = 5;									  //精灵循环跳动变量
	char input;										  //输入判断变量

	int fullbleed = PK_own->bleed;				//我方满血血量
	int fullbleed2 = PK_enemy->bleed;           //敌方满血血量

	int bleed_Width2 = 125;
	int bleed_Width1 = 180;					    //我方血条长度

	int fullexercise_Width = 240;                  //满经验槽长度

	while (1)
	{
		IMAGE img1;
		loadimage(&img1, _T("资源文件夹\\其它\\战斗背景1.jpg"));
		putimage(0, 0, &img1);
		//我方血条框
		setlinestyle(PS_SOLID, 3);						   //边框宽度
		setlinecolor(BLACK);							      //边框颜色
		setfillcolor(RGB(255, 245, 220));               //填充颜色
		fillroundrect(25, 50, 220, 130, 10, 10);      //边框大小
													  //敌方血条框
		setlinestyle(PS_SOLID, 3);                        //边框宽度
		setlinecolor(BLACK);                              //边框颜色
		setfillcolor(RGB(255, 245, 220));             //填充颜色
		fillroundrect(330, 220, 580, 310, 10, 10); //边框大小

												   //最下方技能框
		setfillcolor(BLACK);
		solidrectangle(0, 335, 640, 480);            //黑色背景   

		setfillcolor(LIGHTGRAY);
		solidroundrect(5, 340, 340, 475, 10, 10);
		setfillcolor(WHITE);
		solidroundrect(15, 350, 330, 465, 10, 10);//左边技能框

		setfillcolor(LIGHTGRAY);
		solidroundrect(345, 340, 635, 475, 10, 10);
		setfillcolor(WHITE);
		solidroundrect(355, 350, 625, 465, 10, 10);//右边技能框

		enemy_fight_show(PK_enemy);     //显示敌方精灵

		if (jump == 5)
		{
			jumpy = 150;                                //己方精灵循环上下跳动
		}

		if (jump == 10)
		{
			jumpy = 155;
			jump = 0;
		}
		jump++;


		//皮卡丘
		IMAGE im1, im2;
		loadimage(&im1, _T("资源文件夹\\其它\\皮卡丘.jpg"));
		loadimage(&im2, _T("资源文件夹\\其它\\皮卡丘bk.jpg"));
		putimage(65, jumpy, &im2, NOTSRCERASE);
		putimage(65, jumpy, &im1, SRCINVERT);

		//我方等级
		TCHAR Lv[5];
		_stprintf_s(Lv, _T("%d"), PK_own->level);
		outtextxy(500, 230, Lv);
		outtextxy(460, 230, _T("Lv:"));

		//我方精灵血量显示
		outtextxy(490, 280, _T("/"));
		TCHAR HP2[5];
		_stprintf_s(HP2, _T("%d"), PK_own->bleed);
		outtextxy(430, 280, HP2);
		TCHAR HP2_1[5];
		_stprintf_s(HP2_1, _T("%d"), fullbleed);
		outtextxy(530, 280, HP2_1);

		//我方血条
		setlinestyle(PS_SOLID, 2);
		setlinecolor(LIGHTGRAY);
		setfillcolor(WHITE);
		fillroundrect(385, 260, 570, 270, 10, 10);

		setfillcolor(GREEN);
		solidroundrect(568 - bleed_Width1, 262, 568, 267, 10, 10);

		//我方经验槽
		setlinestyle(PS_SOLID, 2);
		setlinecolor(LIGHTGRAY);
		setfillcolor(WHITE);
		fillroundrect(335, 300, 575, 305, 10, 10);

		setfillcolor(GREEN);
		solidroundrect(337, 302, 337 + exercise_Width, 302, 10, 10);

		//敌方等级
		TCHAR Lv_2[5];
		_stprintf_s(Lv_2, _T("%d"), PK_enemy->level);
		outtextxy(160, 70, Lv_2);
		outtextxy(120, 70, _T("Lv:"));
		//血条
		setlinestyle(PS_SOLID, 2);
		setlinecolor(LIGHTGRAY);
		setfillcolor(WHITE);
		fillroundrect(80, 100, 210, 110, 10, 10);

		setfillcolor(GREEN);
		solidroundrect(208 - bleed_Width2, 102, 208, 107, 10, 10);

		//选择战斗or逃跑
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
			gettextstyle(&f);                     // 获取当前字体设置
			f.lfHeight = 20;                      // 设置字体高度
			_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			settextstyle(&f);                     // 设置字体样式
			outtextxy(370 + 20, 365, _T("战斗"));
			outtextxy(500 + 20, 365, _T("逃跑"));

			FlushBatchDraw();
		}

		//我方技能
		if (choose == 0)
		{
			//技能选择图标
			setfillcolor(BLACK);
			POINT pts[] = { { x, y },{ x, y + 20 },{ x + 15, y + 10 } };
			solidpolygon(pts, 3);

			LOGFONT f;
			gettextstyle(&f);                     // 获取当前字体设置
			f.lfHeight = 20;                      // 设置字体高度
			_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			settextstyle(&f);                      // 设置字体样式
			outtextxy(30 + 20, 365, _T("十万伏特"));
			outtextxy(190 + 20, 365, _T("尖叫"));
			outtextxy(30 + 20, 365 + 60, _T("电磁波"));
			outtextxy(190 + 20, 365 + 60, _T("打雷"));

			//判断敌方精灵有没有死亡//
			if (PK_enemy->bleed <= 0)
			{
				LOGFONT f;
				gettextstyle(&f);                     // 获取当前字体设置
				f.lfHeight = 100;                     // 设置字体高度
				_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
				setbkmode(TRANSPARENT);
				settextcolor(RED);
				settextstyle(&f);                     // 设置字体样式
				outtextxy(window_width / 2 - 150, window_height / 2 - 100, _T("victory"));    //显示游戏结果//
				FlushBatchDraw();
				PK_enemy->judge = 1;
				Sleep(2000);
				pokemon_experiece += 30;   //我方精灵经验增加
				if (pokemon_experiece >= 200 + (PK_own->level - 5) * 100)
				{
					PK_own->level++;
					exercise_Width = (pokemon_experiece - 50 * PK_own->level*PK_own->level + 350 * PK_own->level - 500)*1.0 / (200 + (PK_own->level - 5) * 100)*fullexercise_Width;   //经验槽宽度

				}
				else
				{
					if (PK_own->level == 5)
						exercise_Width = pokemon_experiece * 1.0 / 200 * fullexercise_Width;
					else if (PK_own->level>5)
						exercise_Width = (pokemon_experiece - 50 * PK_own->level*PK_own->level + 350 * PK_own->level - 500)*1.0 / (200 + (PK_own->level - 5) * 100)*fullexercise_Width;   //经验槽宽度
				}
				break;


			}
			//判断己方精灵有没有死亡//
			if (PK_own->bleed <= 0)
			{
				TCHAR s[] = _T("defeated");
				settextstyle(16, 0, _T("楷体"));
				outtextxy(window_width / 2 - 10, window_height / 2, s);    //显示游戏结果//
				PK_enemy->judge = 1;
				break;
			}

			//control控制部分
			if (_kbhit())										 //操作判断
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
						PK_enemy->bleed = PK_enemy->bleed - ((PK_own->level*0.4 + 2)*PK_own->skill_1*PK_own->attack / (PK_enemy->defence*50.0) + 2);  //伤害值计算//
					}
					if (x == 190 && y == 365)
					{
						scream();
						PK_enemy->bleed = PK_enemy->bleed - ((PK_own->level*0.4 + 2)*PK_own->skill_2*PK_own->attack / (PK_enemy->defence*50.0) + 2);  //伤害值计算//
					}
					if (x == 30 && y == 365 + 60)
					{
						flash();
						PK_enemy->bleed = PK_enemy->bleed - ((PK_own->level*0.4 + 2)*PK_own->skill_3*PK_own->attack / (PK_enemy->defence*50.0) + 2);  //伤害值计算//
					}
					if (x == 190 && y == 365 + 60)
					{
						thunder();
						PK_enemy->bleed = PK_enemy->bleed - ((PK_own->level*0.4 + 2)*PK_own->skill_3*PK_own->attack / (PK_enemy->defence*50.0) + 2);  //伤害值计算//
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
			FlushBatchDraw();							  //结束批量绘制
		}
	}
}
//战斗函数
void fight()
{
	int i;
	for (i = 0; i<pokemon_number; i++)				 //遍历精灵坐标数组，
	{
		if (abs(map_init_x + character_x - PK[i].x) <= 15 && abs(map_init_y + character_y - PK[i].y) <= 15 && PK[i].judge == 0)
		{
			interface_change_animation();		    //界面切换动画
			fight_show(&PK[i], &PK[0]);				 //战斗显示函数
			interface_change_animation();       //界面切换动画
			startup_pokemon_bleed();           //重置精灵血量
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//剧情部分
void plot_1()
{
	setfillcolor(LIGHTGRAY);                   //对话框
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//往下将展现对话内容
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(16, 350, _T("童博士：欢迎来到河海森林公园，这里有我们学校独"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 375, _T("特的小精灵，它们一直和睦地生活在这一片森林中，"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 400, _T("但是最近森林深处出现了一只恶兽，我们的小精灵很"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 425, _T("多失踪或者受伤，现在我们召集全校的勇士帮助我们"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 450, _T("击败这只恶兽，你很荣幸地被选中了。"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_2()
{
	setfillcolor(LIGHTGRAY);                   //对话框
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//往下将展现对话内容
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(16, 350, _T("河海宝宝：我一定义不容辞！"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_3()
{
	setfillcolor(LIGHTGRAY);                   //对话框
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//往下将展现对话内容
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(16, 350, _T("童博士：这是皮卡丘，在接下来的探险中它将陪伴你"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 375, _T("的左右。少年，勇敢地前进吧，先找到失踪的水君，"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 400, _T("它可能在恶兽的手下雷公那里。"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_4()
{
	setfillcolor(LIGHTGRAY);                   //对话框
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//往下将展现对话内容
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(16, 350, _T("雷君：小子不想活了，敢闯我的领地！"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_5()
{
	setfillcolor(LIGHTGRAY);                   //对话框
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//往下将展现对话内容
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(16, 350, _T("河海宝宝：少说废话！来战斗吧"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_6()
{
	setfillcolor(LIGHTGRAY);                   //对话框
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//往下将展现对话内容
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(16, 350, _T("水君：谢谢你救了我，前面的路会更加凶险，你会碰"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 375, _T("到森林里不太友善的精灵，在遇见大魔王前，你可以"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 400, _T("通过他们历练自己！对了，我的朋友炎帝被大魔王黑"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 425, _T("	了，你能救救他么？"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_7()
{
	setfillcolor(LIGHTGRAY);                   //对话框
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//往下将展现对话内容
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(16, 350, _T("河海宝宝：当然没问题！"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_8()
{
	setfillcolor(LIGHTGRAY);                   //对话框
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//往下将展现对话内容
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(16, 350, _T("炎帝：此路不通！"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_9()
{
	setfillcolor(LIGHTGRAY);                   //对话框
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//往下将展现对话内容
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(16, 350, _T("炎帝：我怎么了。。。怎么在这里？"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_10()
{
	setfillcolor(LIGHTGRAY);                   //对话框
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//往下将展现对话内容
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(16, 350, _T("河海宝宝：没什么，水君在老地方等你呢，快回去吧！"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_11()
{
	setfillcolor(LIGHTGRAY);                   //对话框
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//往下将展现对话内容
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(16, 350, _T("炎帝：好，谢谢你！"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_12()
{
	setfillcolor(LIGHTGRAY);                   //对话框
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//往下将展现对话内容
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(16, 350, _T("路卡利亚：小子！就是你一直在我的地盘上撒野么！"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_13()
{
	setfillcolor(LIGHTGRAY);                   //对话框
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//往下将展现对话内容
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(16, 350, _T("河海宝宝：到底是谁在撒野！这里是河海公园，是所"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 375, _T("有精灵的家!"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_14()
{
	setfillcolor(LIGHTGRAY);                   //对话框
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//往下将展现对话内容
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(16, 350, _T("路卡利亚：哈哈哈，幼稚，到底是谁的地盘，还是用"));
	FlushBatchDraw();
	Sleep(1000);
	outtextxy(16, 375, _T("实力说话吧!"));
	FlushBatchDraw();
	Sleep(1000);
}

void plot_15()
{
	setfillcolor(LIGHTGRAY);                   //对话框
	solidroundrect(5, 340, 630, 475, 10, 10);
	setfillcolor(WHITE);
	solidroundrect(15, 350, 620, 465, 10, 10);

	//往下将展现对话内容
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(&f);                     // 设置字体样式
	outtextxy(16, 350, _T("河海宝宝：你。。。可恶。。。"));
	FlushBatchDraw();
	Sleep(1000);
}

////////////////////////
//主函数
void main()
{
	startup_pokemon_judge();					  //对精灵时间属性进行初始化
	startup_pokemon();						     //对精灵基础属性进行初始化
	startup_pokemon_bleed();                   //对精灵血量进行初始化
	startup_pokemon_destination();		      //对精灵位置进行初始化
	starup_map_show();                             //对地图进行初始化
	start_menu();                                  //登陆界面
	while (1)
	{
		pokemon_refresh();                            //精灵刷新
		map_show();										//地图显示函数
		fight();												//战斗函数
		operate();								// 客户交互函数
	}
}


