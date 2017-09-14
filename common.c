#include "common.h"


void create_snake(S**head)
{
	*head = malloc(sizeof(S));
	S* end = malloc(sizeof(S));
	srand(time(0));
	(*head) ->x = rand() % 15 + 3;
	(*head) ->y = rand() % 15 + 3;
	(*head) -> next = end;
	end ->x = (*head) ->x;
	end ->y = ((*head) ->y) + 1;
	end -> next = NULL;
}
void create_food(F*f,S*head)
{
	int a[20][20];
	
	S* find = head;
	int len = 1;
	int n,i,j,key;
	key = 0;
	for(i = 0;i < 20; i++)
	
		for(j = 0;j < 20;j++)
			a[i][j] = 0;
	
	while(find)
	{
		a[find->y][find->x] = 1;
		find = find -> next;
		len++;
	}
	srand(time(0));
	n = rand() % (399 - len);
	for (i = 0; (i<19) && (key<n); i++)
		for (j = 0; (j<19) && (key<n); j++)
		{
			if (a[i][j] == 0)
			key++;
		}
	
	f->x = j - 1;
	f->y = i - 1;
}
void move_snake(char toward,S*head)
{
	S* find = head -> next;
	int sx,sy,tx,ty;
	sx = find->x;
	sy = find->y;
	find -> x = head ->x;
	find -> y = head ->y;
	switch(toward)
	{	
	case 'w':
		head->y -= 1;
		break;
	case 's':
		head->y += 1;
		break;
	case 'a':
		head->x -= 1;
		break;
	case 'd':
		head->x += 1;
		break;
	}
	while(find->next != NULL)
	{
		tx = find ->next ->x;
		ty = find ->next ->y;
		find -> next ->x = sx;
		find -> next ->y = sy;
		sx = tx;
		sy = ty;
		find = find ->next;
	}
}
int move_judge_snake(char bef,char aft)
{
	if(bef == 'w'&& aft == 's'||bef == 's' && aft == 'w'||bef == 'a'&& aft == 'd'||bef == 'd'&& aft == 'a')
		return 0;
	else
		return 1;
}
void eat(S* head ,F* f)
{
	if(head ->x == f->x && head ->y == f->y)
	{
		l_snake(head);
		create_food(f,head);
	}
}
void l_snake(S* head)
{
	S*find = head;
	S*tmp = NULL;
	S*new = malloc(sizeof(S));
	new->next = NULL;
	while(find->next->next)
	{
		find = find ->next;
	}
	tmp = find -> next;
	tmp -> next = new;
	new ->x = tmp -> x + tmp ->x - find -> x;
	new ->y = tmp -> y + tmp ->y - find -> y;
	
}

int outside(S* head)
{
	if(head->x < 0||head ->y <0||head ->x >19||head ->y>19)
		return 1;
	else
		return 0;
}
int head_body(S* head)
{
	S*find = head->next;
	while(find)
	{
		if(find->x == head->x&&find ->y ==head ->y)
			return 1;
		find = find ->next;
		
	}
	return 0;
}
void gameover(S*head)
{
	if(outside(head)||head_body(head))
	{
		system("clear");
		printf("GAME OVER\n");
		recover_keyboard();
		exit(EXIT_SUCCESS);	
	}
}
void draw_point(unsigned long*addr,int dx,int dy,int r,int g,int b)
{
	int i,j,x,y;
	x = dx * 10 + 200;
	y = dy * 20 + 200;
	for(i = y; i <y + 20; i++){
		for(j = x; j <x + 10;j++)
			*(addr + i*960 + j) = RGB888(r,g,b);

		
	}
	
}
void draw_snake(unsigned long * addr,S* head)
{
	S* find = head;
	while(find)
	{
		draw_point(addr,find ->x ,find ->y,0,255,0);
		find = find ->next;
	}
	
} 
void draw_food(unsigned long * addr,F*f)
{
	draw_point(addr, f->x,f->y,255,0,0);
}

void draw_rim(unsigned long* addr)
{
	int i,j;
	for(i = 180;i < 200;i++)
	{
		for(j = 190; j < 410; j++)
			*(addr+i*960+j) = RGB888(0,0,255);
	}
	for(i = 600; i < 620;i++)
	{
		for(j = 190; j < 410; j++)
			*(addr+i*960+j) = RGB888(0,0,255);
	}
	for(i = 200; i < 600;i++)
	{
		for(j = 190; j < 200;j++ )	
			*(addr+i*960+j) = RGB888(0,0,255);
	}
	for(i = 200;i < 600; i++)
	{
		for(j = 400;j < 410;j++)
			*(addr+i*960+j) = RGB888(0,0,255);
	}
	/*for(j = 190;j < 410; j++)
  	{
 		for(i = 180;i < 200;i++)
			*(addr+i*960+j) = RGB888(0,0,255);
		for(i = 600;i< 620;i++)
			*(addr+i*960 + j) = RGB888(0,0,255);
  	}
	for(i = 200;i < 600;i++)
	{
		for(j =190; j< 200;j++)
			*(addr+i*960+j) = RGB888(0,0,255);
		for(j = 400;j < 410;j++)
			*(addr+i*960+j) = RGB888(0,0,255);
	}
	*/
}
void mclear(unsigned long* addr)
{
	int i,j;
	for(i = 200;i < 600; i++)
	{
		for(j = 200; j < 400;j++)
			*(addr+i*960+j) = RGB888(0,0,0);
	}
}

int init_keyboard(void)
{
	int ret;
	struct termios tc;
	ret = tcgetattr(0,&tcsave);
	if(ret < 0)
		return -1;
	tc = tcsave;
	tc.c_lflag &= ~(ECHO|ICANON);
	ret = tcsetattr(0, TCSANOW,&tc);
	if(ret < 0)
		return -1;
	flsave = fcntl(0,F_GETFL);
	fcntl(0,F_SETFL,flsave|O_NONBLOCK);
	return 0;
}
void recover_keyboard(void)
{
	tcsetattr(0,TCSANOW,&tcsave);
	fcntl(0,F_SETFL,flsave);
}
int get_key(void)
{
	unsigned char buf[3];
	
	int ret = read(0,buf,sizeof(buf));
	if(ret < 0)
		return -1;
	int i = 0, key = 0;
	for(i = 0;i < ret; i++)
	{
		key += (buf[i]<<(i*8));
	}
	return key;
}
int is_up(int key)
{
	return key == UP;
}
int is_down(int key)
{
	return key ==DOWN;
}
int is_left(int key)
{
	return key == LEFT;
}
int is_right(int key)
{
	return key == RIGHT;
}
int is_enter(int key)
{
	return key == ENTER;
}
int is_esc(int key)
{
	return key  == ESC;
}
int is_space(int key)
{
	return key == SPACE;
}





