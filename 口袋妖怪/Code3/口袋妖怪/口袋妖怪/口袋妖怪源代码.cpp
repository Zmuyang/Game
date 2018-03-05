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
int canvas[1652][1416];   //定义画布坐标，使每个像素点坐标为0

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
	int skill_1;   //四项技能的基础伤害
	int skill_2;
	int skill_3;
	int skill_4;
	int judge;
	int time;  //在一定时间以后将把原位置的精灵重新刷新出来
}PK[pokemon_number];

//CHAR 向 TCHAR 转化的函数，为了将资源图片的路径可以用变量表示
void CharToTchar(const char *_char, TCHAR *tchar) {
	int iLength;
	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

void load_PK_picture(pokemon *PK) {
	char ch_path1[60] = "资源文件夹\\";  //路径前端
	char ch_path2[60] = "1.jpg";		//路径后端
	char ch_path3[60] = "2.jpg";
	char ch_path4[60] = "资源文件夹\\";
	strcat_s(ch_path1, PK->name);    //将路径名称链接起来
	strcat_s(ch_path1, ch_path2);
	strcat_s(ch_path4, PK->name);
	strcat_s(ch_path4, ch_path3);
	TCHAR p1[60];
	TCHAR p2[60];
	//将路径名字改成TCHAR类型来调用
	CharToTchar(ch_path1, p1);
	CharToTchar(ch_path4, p2);

	//让精灵看起来在上下跳动
	static int jumpy_1 = 90;
	static int jump = 5;
	if (jump == 5) jumpy_1 = 90;
	if (jump == 10) {
		jump = 0;
		jumpy_1 = 95;
	}
	jump++;
	//显示敌方精灵
	IMAGE im1, im2;
	loadimage(&im1, p1);
	loadimage(&im2, p2);
	putimage(400, jumpy_1, &im2, NOTSRCERASE);
	putimage(400, jumpy_1, &im1, SRCINVERT);
}

void startup_pokemon() { //精灵属性初始化
	//皮卡丘
	//精灵在地图上的坐标
	PK[0].x = 0;   
	PK[0].y = 0;

	PK[0].attack = 8;			//普攻
	PK[0].bleed = 30;			//生命值
	PK[0].defence = 4;			//普防
	PK[0].special_attack = 9;		//特攻
	PK[0].special_defence = 7;		//特防
	PK[0].level = 5;		//等级
	PK[0].name = "皮卡丘";			//名称
	PK[0].speciese = "电";		//元素属性
	PK[0].skill_1 = 50;				//技能1伤害
	PK[0].skill_2 = 80;				//技能2伤害
	PK[0].skill_3 = 100;
	PK[0].skill_4 = 150;
	PK[0].judge = 1;
	PK[0].time = 0;

	//小火龙
	PK[1].x = 100;                      
	PK[1].y = 200;
	PK[1].attack = 8;                    
	PK[1].bleed = 30;                    
	PK[1].defence = 4;                  
	PK[1].special_attack = 9;            
	PK[1].special_defence = 7;           
	PK[1].level = 5;                  
	PK[1].name = "小火龙";             
	PK[1].speciese = "火";             
	PK[1].skill_1 = 50;                  
	PK[1].skill_2 = 80;                 
	PK[1].skill_3 = 0;
	PK[1].skill_4 = 0;
	PK[1].judge = 0;
	PK[1].time = 0;

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
	PK[2].skill_1 = 30;
	PK[2].skill_2 = 40;
	PK[2].skill_3 = 0;
	PK[2].skill_4 = 0;
	PK[2].time = 0;

	//鳍甲两栖兽//
	PK[3].x = 0;
	PK[3].y = 0;
	PK[3].attack = 7;
	PK[3].bleed = 29;
	PK[3].defence = 5;
	PK[3].special_attack = 10;
	PK[3].special_defence = 6;
	PK[3].level = 5;
	PK[3].name = "鳍甲两栖兽";
	PK[3].speciese = "水";
	PK[3].skill_1 = 70;
	PK[3].skill_2 = 80;
	PK[3].skill_3 = 0;
	PK[3].skill_4 = 0;
	PK[3].time = 0;

	//小拳石//
	PK[4].x = 0;
	PK[4].y = 0;
	PK[4].attack = 8;
	PK[4].bleed = 30;
	PK[4].defence = 4;
	PK[4].special_attack = 9;
	PK[4].special_defence = 7;
	PK[4].level = 5;
	PK[4].name = "小拳石";
	PK[4].speciese = "岩石";
	PK[4].skill_1 = 35;
	PK[4].skill_2 = 60;
	PK[4].skill_3 = 0;
	PK[4].skill_4 = 0;
	PK[4].time = 0;

	//科基拉
	PK[5].x = 0;
	PK[5].y = 0;
	PK[5].attack = 8;
	PK[5].bleed = 30;
	PK[5].defence = 4;
	PK[5].special_attack = 9;
	PK[5].special_defence = 7;
	PK[5].level = 5;
	PK[5].name = "科基拉";
	PK[5].speciese = "地面";
	PK[5].skill_1 = 35;
	PK[5].skill_2 = 40;
	PK[5].skill_3 = 0;
	PK[5].skill_4 = 0;
	PK[5].time = 0;

	//鬼斯//
	PK[6].x = 0;
	PK[6].y = 0;
	PK[6].attack = 8;
	PK[6].bleed = 30;
	PK[6].defence = 4;
	PK[6].special_attack = 9;
	PK[6].special_defence = 7;
	PK[6].level = 5;
	PK[6].name = "鬼斯";
	PK[6].speciese = "浮游 鬼";
	PK[6].skill_1 = 45;
	PK[6].skill_2 = 83;
	PK[6].skill_3 = 0;
	PK[6].skill_4 = 0;
	PK[6].time = 0;

	//凯西//
	PK[7].x = 0;
	PK[7].y = 0;
	PK[7].attack = 8;
	PK[7].bleed = 30;
	PK[7].defence = 4;
	PK[7].special_attack = 9;
	PK[7].special_defence = 7;
	PK[7].level = 5;
	PK[7].name = "凯西";
	PK[7].speciese = "超能";
	PK[7].skill_1 = 50;
	PK[7].skill_2 = 80;
	PK[7].skill_3 = 0;
	PK[7].skill_4 = 0;
	PK[7].time = 0;

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
	PK[8].skill_1 = 50;
	PK[8].skill_2 = 80;
	PK[8].skill_3 = 0;
	PK[8].skill_4 = 0;
	PK[8].time = 0;

	//腕力//
	PK[9].x = 0;
	PK[9].y = 0;
	PK[9].attack = 8;
	PK[9].bleed = 30;
	PK[9].defence = 4;
	PK[9].special_attack = 9;
	PK[9].special_defence = 7;
	PK[9].level = 5;
	PK[9].name = "腕力";
	PK[9].speciese = "格斗";
	PK[9].skill_1 = 50;
	PK[9].skill_2 = 80;
	PK[9].skill_3 = 0;
	PK[9].skill_4 = 0;
	PK[9].time = 0;

	//皮皮犬//
	PK[10].x = 0;
	PK[10].y = 0;
	PK[10].attack = 8;
	PK[10].bleed = 30;
	PK[10].defence = 4;
	PK[10].special_attack = 9;
	PK[10].special_defence = 7;
	PK[10].level = 5;
	PK[10].name = "皮皮犬";
	PK[10].speciese = "恶";
	PK[10].skill_1 = 50;
	PK[10].skill_2 = 80;
	PK[10].skill_3 = 0;
	PK[10].skill_4 = 0;
	PK[10].time = 0;

	//波波//
	PK[11].x = 0;
	PK[11].y = 0;
	PK[11].attack = 8;
	PK[11].bleed = 30;
	PK[11].defence = 4;
	PK[11].special_attack = 9;
	PK[11].special_defence = 7;
	PK[11].level = 5;
	PK[11].name = "波波";
	PK[11].speciese = "飞行";
	PK[11].skill_1 = 50;
	PK[11].skill_2 = 80;
	PK[11].skill_3 = 0;
	PK[11].skill_4 = 0;
	PK[11].time = 0;
}

void startup_pokemon_destination() {  //精灵位置初始化
	PK[1].x = 488;
	PK[1].y = 553;
}

void startup_show() {  //地图初始化
	initgraph(window_width, window_height);   //初始化绘图环境
	map_init_x = 298;
	map_init_y = 162;		//地图初始时时截取从（500,500）开始的部分//
	character_x =  70;		 //人物的初始位置
	character_y = 221;
	character_picture_i = 0;
	character_picture_j = 0;
	const char *s = "资源文件夹\\终极地图.jpg";
	TCHAR p[40];
	CharToTchar(s, p);
	loadimage(&main_map, p, 1652, 1416);
	loadimage(&character_vice, _T("资源文件夹\\桌面行走图遮罩图.jpg"), 136, 200);
	loadimage(&character, _T("资源文件夹\\桌面行走图.jpg"), 136, 200);
	BeginBatchDraw();

	for (int i = 0; i < 1652; i++) {
		for (int j = 0; j < 1416; j++) {
			if (i <= 425 || i >= 1223 - 45 || j <= 210 || j >= 1161 - 50) {  //地图最四周的树木
				canvas[i][j] = 0;
			}
			else if ((i > 430 && i <= 552) && (j > 210 && j <= 320)) {  //左上方的房子
				canvas[i][j] = 0;
			}
			else if ((i >= 540 - 45 && i <= 552) && (j > 320 && j <= 562)) {//房子下面的一排树木
				canvas[i][j] = 0;
			}
			else if ((i >= 659 - 45 && i <= 690) && (j >= 300 && j <= 542)) {//第二排树木
				canvas[i][j] = 0;
			}
			else if ((i >= 799 - 45 && i <= 821) && (j >= 211 && j <= 489)) {   //第三排树木
				canvas[i][j] = 0;
			}
			else if ((i >= 923 - 45 && i <= 1141) && (j >= 235 && j <= 357)) {  //右上方的长方形树木
				canvas[i][j] = 0;
			}
			else if ((i >= 1121 - 45 && i < 1223) && (j >= 404 && j <= 521)) {
				canvas[i][j] = 0;
			}
			else if ((i >= 699 - 45 && i <= 731) && (j >= 513 && j <= 630)) {//从这里开始将中间的森林块定义完毕
				canvas[i][j] = 0;
			}
			else {
				canvas[i][j] = 0;
			}
		}
	}
}

void map_show() {   //地图显示函数
	putimage(0, 0, window_width, window_height, &main_map, map_init_x, map_init_y);
	putimage(character_x, character_y, 45, 50, &character_vice, character_picture_i * 45, character_picture_j * 50, NOTSRCERASE); //每个小人的像素是（45,50）
	putimage(character_x, character_y, 45, 50, &character, character_picture_i * 45, character_picture_j * 50, SRCINVERT);
	FlushBatchDraw();
}

void UpdateWithInput() {  //随着输入而更新的函数
	if (_kbhit()) {    //每次移动20个像素单位
		input = _getch();
		if (character_picture_i == 2) {    //实现了交替取人物图的不同部分
			character_picture_i = -1;
		}
		if (input == 'A' || input == 'a'&&canvas[map_init_x + character_x - 20][map_init_y + character_y] != 0) {   //根据方向操作进行数据更新
			map_init_x -= 10;                       //10为人的步长//
			character_picture_j = 2;
		}
		else if (input == 'A' || input == 'a'&&canvas[map_init_x + character_x - 20][map_init_y + character_y] == 0){
			character_picture_j = 2;
		}
		if (input == 'D' || input == 'd'&&canvas[map_init_x + character_x + 20][map_init_y + character_y] != 0) {    //最后的判断是判断行进方向是否为障碍物//
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
	//敌方精灵开始释放技能//
	//if (PK_enemy.bleed >PK_own.bleed){
		//放第一个技能的动画//
		//PK_own.bleed=PK_own.bleed-((PK_enemy.level*0.4+2)*PK_enemy.skill_1*PK_enemy.attack/(PK_own.defence*50.0)+2);  //伤害值计算//
	}
	//if (PK_enemy.bleed <=PK_own.bleed){
		//放第二个技能的动画//
		// PK_own.bleed=PK_own.bleed-((PK_enemy.level*0.4+2)*PK_enemy.skill_1*PK_enemy.attack/(PK_own.defence*50.0)+2);  //伤害值计算//
	}
	//FlushBatchDraw();	*/
}


void fight_animation(){
	//这里实现了战斗前开场动画
	int i, j;
	i = 320, j = 0;                                            //从正上方开始画
	setlinecolor(BLACK);                              //画线颜色设置为黑色
	while (!(i == 319 && j == 0)){
		line(320, 240, i, j);
		FlushBatchDraw();
		if (i == 640)   j++;
		if (i == 0)       j--;
		if (j == 600)   i--;
		if (j == 0)      i++;
	}
	//到这里动画结束
}

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

	int fullbleed = PK_own->bleed;					//我方满血血量
	int fullbleed2 = PK_enemy->bleed;                    //地方满血血量

	int bleed_Width2 = 125;
	int bleed_Width1 = 180;							//我方血条长度


	while (1){
		IMAGE img1;
		loadimage(&img1, _T("资源文件夹\\战斗背景1.jpg"));
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

		if (jump == 5)			jumpy = 150;                                //己方精灵循环上下跳动

		if (jump == 10)	{
			jumpy = 155;
			jump = 0;
		}
		jump++;


		//皮卡丘
		IMAGE im1, im2;
		loadimage(&im1, _T("资源文件夹\\皮卡丘.jpg"));
		loadimage(&im2, _T("资源文件夹\\皮卡丘2.jpg"));
		putimage(65, jumpy, &im2, NOTSRCERASE);
		putimage(65, jumpy, &im1, SRCINVERT);

		//我方等级
		TCHAR Lv[5];
		_stprintf_s(Lv, _T("%d"), PK_own->level);
		outtextxy(500, 230, Lv);   //这个函数用于在指定位置输出字符串。
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
		if (choose == 1){
			setfillcolor(BLACK);
			POINT pts[] = { { choice_x, choice_y },{ choice_x,choice_y + 20 },{ choice_x + 15, choice_y + 10 } };
			solidpolygon(pts, 3);   //这个函数用于画填充的多边形（无边框）。

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
		if (choose == 0){
			//技能选择图标
			setfillcolor(BLACK);
			POINT pts[] = { { x, y },{ x, y + 20 },{ x + 15, y + 10 } };
			solidpolygon(pts, 3);

			LOGFONT f;
			gettextstyle(&f);                     // 获取当前字体设置
			f.lfHeight = 20;                      // 设置字体高度
			_tcscpy_s(f.lfFaceName, _T("楷体"));    // 设置字体
			setbkmode(TRANSPARENT);    //这个函数用于设置图案填充和文字输出时的背景模式
			settextcolor(BLACK);
			settextstyle(&f);                      // 设置字体样式
			outtextxy(30 + 20, 365, _T("天降神雷"));
			outtextxy(190 + 20, 365, _T("尖叫"));
			outtextxy(30 + 20, 365 + 60, _T("电力环绕"));

			//判断敌方精灵有没有死亡//
			if (PK_enemy->bleed <= 0){
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
				fight_animation();                    //退出动画//
				break;
			}


			//这里放敌方精灵的技能释放函数//
			pokemon_fight_show(PK_enemy, PK_own);

			//判断己方精灵有没有死亡//
			if (PK_own->bleed <= 0){
				TCHAR s[] = _T("defeated");
				settextstyle(16, 0, _T("楷体"));
				outtextxy(window_width / 2 - 10, window_height / 2, s);    //显示游戏结果//
				PK_enemy->judge = 1;
				fight_animation();      //退出动画//
				break;
			}

			//control控制部分
			if (_kbhit()){		//操作判断
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
						PK_enemy->bleed = PK_enemy->bleed - ((PK_own->level*0.4 + 2)*PK_own->skill_1*PK_own->attack / (PK_enemy->defence*50.0) + 2);  //伤害值计算//
					}
					if (x == 190 && y == 365){
						scream();
						PK_enemy->bleed = PK_enemy->bleed - ((PK_own->level*0.4 + 2)*PK_own->skill_2*PK_own->attack / (PK_enemy->defence*50.0) + 2);  //伤害值计算//
					}
					if (x == 30 && y == 365 + 60){
						flash();
						PK_enemy->bleed = PK_enemy->bleed - ((PK_own->level*0.4 + 2)*PK_own->skill_3*PK_own->attack / (PK_enemy->defence*50.0) + 2);  //伤害值计算//
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
			FlushBatchDraw();							  //结束批量绘制
		}
	}
}

void fight(){
	int i;
	for (i = 0; i<pokemon_number; i++)	{		//遍历精灵坐标数组
		if (abs(map_init_x + character_x - PK[i].x) <= 15 && abs(map_init_y + character_y - PK[i].y) <= 15 && PK[i].judge == 0){
			fight_animation();						    //战斗前动画
			fight_show(&PK[i], &PK[0]);								    //战斗显示函数
			break;
		}
	}
}

void pokemon_refresh() { //实现一段时间以后地图上的精灵就会自动重新刷出来
	int i;
	for (i = 0; i<pokemon_number; i++){
		if (PK[i].judge == 1 && PK[i].time<10000) {  //当一个精灵被遇到后就其judge就会变为1，为1的这段时间里是无法被遇到的，但在10000次循环后他将被重新刷新出来
			PK[i].time++;
		}
		else if (PK[i].judge == 1 && PK[i].time == 10000){
			PK[i].judge = 0;
			PK[i].time = 0;
		}
	}
}


int main(){
	startup_pokemon();							  //对精灵属性进行初始化
	startup_pokemon_destination();		      //对精灵位置进行初始化
	startup_show();                                     //对地图进行初始化
	while (1){
		pokemon_refresh();
		map_show();										//地图显示函数
		UpdateWithInput();								// 根据操作进行地图的更新
		fight();												//战斗函数
	}
	return 0;
}
