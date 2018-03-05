#include <iostream>
#include <cstdlib>
#include <conio.h>  // kbhit()
#include <windows.h>
#include <graphics.h>  //C����ͼ�ο�

using namespace std;

#define window_height 480
#define window_width  640              //���ڴ�С

//IMAGE  ����ͼ��Ķ���
IMAGE main_map;  
IMAGE character_vice;
IMAGE character;

int map_init_x, map_init_y;
int character_x, character_y;
int character_picture_i, character_picture_j;

char input;

void startup_show() {
	initgraph(640, 480);   //��ʼ����ͼ���ڡ�
	map_init_x = map_init_y = 0;
	character_x = 332;
	character_y = 86;
	character_picture_i = 0;
	character_picture_j= 0;
	loadimage(&main_map, _T("��Դ�ļ���\\�ܵ�ͼ.jpg"), 640, 1088);
	loadimage(&character_vice, _T("��Դ�ļ���\\��������ͼ����ͼ.jpg", 197, 282));
	loadimage(&character, _T("��Դ�ļ���\\��������ͼ.jpg", 197, 282));
	BeginBatchDraw();  //����������ڿ�ʼ������ͼ��ִ�к��κλ�ͼ����������ʱ���������Ļ�ϣ�ֱ��ִ�� FlushBatchDraw �� EndBatchDraw �Ž�֮ǰ�Ļ�ͼ�����
}

void map_show() {
	putimage(0, 0, window_width, window_height, &main_map, map_init_x, map_init_y);
	// ÿ��С�˵������ǣ�65��70��
	// putimage  �ڵ�ǰ��ͼ�豸�ϻ���ָ��ͼ��
	// NOTSRCERASE ���Ƴ���������ɫ = NOT (��Ļ��ɫ OR ͼ����ɫ)
	// SRCINVERT ���Ƴ���������ɫ = ��Ļ��ɫ XOR ͼ����ɫ 
	putimage(character_x, character_y, 65, 70, &character_vice, character_picture_i * 65, character_picture_j * 70, NOTSRCERASE); 
	putimage(character_x, character_y, 65, 70, &character_vice, character_picture_i * 65, character_picture_j * 70, SRCINVERT);
	FlushBatchDraw();  //ִ��δ��ɵĻ�������
}

void UpdateWithInput() {
	if (_kbhit()) {   //_kbhit()��һ��C++���������ڷ���������Ӧ���������¼���(��鵱ǰ�Ƿ��м������룬�����򷵻�һ����0ֵ�����򷵻�0)
		input = _getch();  //�����������
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
	EndBatchDraw();   //�����������ƣ���ִ��δ��ɵĻ�������
	_getch();
}