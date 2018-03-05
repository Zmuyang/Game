#include <iostream>
#include <cstdlib>
#include <conio.h>  // kbhit()
#include <windows.h>
#include <graphics.h>  //C语言图形库

using namespace std;

#define window_height 480
#define window_width  640              //窗口大小

//IMAGE  保存图像的对象
IMAGE main_map;  
IMAGE character_vice;
IMAGE character;

int map_init_x, map_init_y;
int character_x, character_y;
int character_picture_i, character_picture_j;

char input;

void startup_show() {
	initgraph(640, 480);   //初始化绘图窗口。
	map_init_x = map_init_y = 0;
	character_x = 332;
	character_y = 86;
	character_picture_i = 0;
	character_picture_j= 0;
	loadimage(&main_map, _T("资源文件夹\\总地图.jpg"), 640, 1088);
	loadimage(&character_vice, _T("资源文件夹\\桌面行走图遮罩图.jpg", 197, 282));
	loadimage(&character, _T("资源文件夹\\桌面行走图.jpg", 197, 282));
	BeginBatchDraw();  //这个函数用于开始批量绘图。执行后，任何绘图操作都将暂时不输出到屏幕上，直到执行 FlushBatchDraw 或 EndBatchDraw 才将之前的绘图输出。
}

void map_show() {
	putimage(0, 0, window_width, window_height, &main_map, map_init_x, map_init_y);
	// 每个小人的像素是（65，70）
	// putimage  在当前绘图设备上绘制指定图像。
	// NOTSRCERASE 绘制出的像素颜色 = NOT (屏幕颜色 OR 图像颜色)
	// SRCINVERT 绘制出的像素颜色 = 屏幕颜色 XOR 图像颜色 
	putimage(character_x, character_y, 65, 70, &character_vice, character_picture_i * 65, character_picture_j * 70, NOTSRCERASE); 
	putimage(character_x, character_y, 65, 70, &character_vice, character_picture_i * 65, character_picture_j * 70, SRCINVERT);
	FlushBatchDraw();  //执行未完成的绘制任务。
}

void UpdateWithInput() {
	if (_kbhit()) {   //_kbhit()是一个C++函数，用于非阻塞地响应键盘输入事件。(检查当前是否有键盘输入，若有则返回一个非0值，否则返回0)
		input = _getch();  //按任意键继续
		if (character_picture_i == 2) {
			character_picture_i = -1;
		}
		if (input == 'A') {
			map_init_x -= 10;
			character_picture_j = 2;
		}
		if (input == 'D') {
			map_init_x += 10;
			character_picture_j = 1;
		}
		if (input == 'S') {
			map_init_y += 10;
			character_picture_j = 0;
		}
		if (input == 'W') {
			map_init_y -= 10;
			character_picture_j = 3;
		}
		character_picture_i++;
	}
}

void main() {
	startup_show();
	while(1){
		map_show();
		UpdateWithInput();
	}
	EndBatchDraw();   //结束批量绘制，并执行未完成的绘制任务。
	_getch();
}