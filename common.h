#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
**frame buffer 头文件
*/
#include <sys/mman.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/ioctl.h>
/*
**键盘 头
*/
#include <termios.h>
#include <unistd.h>


#define  RGB888(r, g, b)     ((0xff & r) << 16 | (0xff & g) << 8 | (b & 0xff))
struct termios tcsave;
int flsave;

#define UP 0x415b1b
#define DOWN 0x425b1b
#define LEFT 0x445b1b
#define RIGHT 0x435b1b
#define ENTER 0xa
#define ESC 0x1b
#define SPACE 0x20

//定义食物结构体,包含xy坐标
typedef struct food
{	
	int x;
	int y;
}F;
//定义贪吃蛇结构体
typedef struct snake
{
	int x;
	int y;
	struct snake *next;
}S;
//游戏功能函数
void create_snake(S**); //蛇的初始化

void create_food(F*,S*); //创建食物,随机产生食物（除去蛇身所在位置）

void move_snake(char , S*); 

int move_judge_snake(char,char); //如果前一方向与后一方向相反,返回 0,否则返回1

void eat(S*,F*); //蛇吃食物,调用l_snake加长蛇,并刷新食物位置

void l_snake(S*); //加长蛇
//结束函数

int outside(S*); //判断蛇是否越界

int head_body(S*); //判断蛇头是否碰到蛇身

void gameover(S*); //通过上面两个函数判断是否结束,并执行结束程序

//画图函数,将坐标信息对应到屏幕像素位置上
 
void draw_point(unsigned long*,int,int,int,int,int );  //在20*20的空间内,画一个指定的单元点,以及设定点的颜色

void draw_snake(unsigned long*,S*); //利用draw_point函数画蛇

void draw_food(unsigned long*,F*); //利用point来画食物

void draw_rim(unsigned long*); //画边框,rim

void mclear(unsigned long* );  //清除边框内的颜色


//键盘函数
int init_keyboard(void);  //初始化调用键盘

void recover_keyboard(void); //释放键盘调用

int get_key(void); //获取健值

int is_up(int);
int is_down(int);
int is_left(int);
int is_right(int);
int is_enter(int);
int is_esc(int);
int is_space(int);


#endif



