#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Y 20
#define X 40
int score,/* ��һ��ʳ���1�� */
last,/* �ж���Ϸ�������Ƿ���� 1 to retry, 0 to end */
ex,/* xβ��λ��end */
ey,/* yβ��λ��end */
sx,/* xͷ��λ��start */
sy,/* yͷ��λ��start */
delay = 200; /* ��ÿdelay��ʱ����һ�� */;
char base[2][Y][X],/* base[0][Y][X]��¼ͼ��, base[1][Y][X]��¼����,
				   -1Ϊʳ��,-2ΪΧǽ,0Ϊ�ո�,1Ϊ��ͷ,2,3...����Ϊ����*/
	food = 5,
    head = 1,
	body = 2;
void print_d(char a[2][Y][X])
/* ��ӡ��ά����a[2][Y][X]�Ķ�ά����a[0][Y][X] */
{
	int y, x;
	for (y = 0; y < Y; y++){
		for (x = 0; x < X; x++){
			printf("%c", a[0][y][x]);
			if (x == X - 1)printf("\n");
		}
	}
}
void wall()
/* ���Χǽ */
{
	int y, x;
	for (y = 0; y < Y; y++){
		for (x = 0; x < X; x++){
			if (y == 0 || y == Y - 1){
				base[0][y][x] = '+';
				base[1][y][x] = -2;
			}
			else {
				if (x == 0 || x == X - 1){
					base[0][y][x] = '+';
					base[1][y][x] = -2;
				}
				else {
					base[0][y][x] = ' ';
					base[1][y][x] = 0;
				}
			}
		}
	}
}
int jud_food()
/* �����Ƿ����ʳ��, 1 ������0 ������ */
{
	int y, x;
	for (y = 0; y < Y; y++)
		for (x = 0; x < X; x++)
			if (base[0][y][x] == food)return 0;
	return 1;
}
void eva_food()
/* ����ʳ�� */
{
	int ry, rx;
	time_t t;
	srand((unsigned) time(&t));
	while (1){
		ry = 1 + rand() % (Y - 2);
		rx = 1 + rand() % (X - 2);
		if (base[0][ry][rx] == ' '){
			base[0][ry][rx] = food;
			base[1][ry][rx] = -1;
			break;
		}
	}
	score++;
}
void eva_head()
/* ������ͷ�Լ��������� */
{
	int ry, rx;
	while (1){
		ry = 1 + rand() % 38;
		rx = 1 + rand() % 18;
		if (base[0][ry][rx] == ' ' && base[0][ry][rx + 1] == ' ' && base[0][ry][rx + 2] == ' '){
			sx = rx;
			sy = ry;
			base[0][sy][sx] = head;
			base[1][sy][sx] = 1;
			ey = ry;
			ex = rx + 2;
			base[0][ey][ex - 1] = body;
			base[1][ey][ex - 1] = 2;
			base[0][ey][ex] = body;
			base[1][ey][ex] = 3;
			break;
		}
	}
}
void sort(int y, int x)
/* ����ʱ����,��β����ͷ */
{
	if (base[1][y][x] == 1);
	else if (base[1][y][x + 1] == base[1][y][x] - 1){
		sort(y, x + 1);
		base[1][y][x + 1]++;
	}
	else if (base[1][y][x - 1] == base[1][y][x] - 1){
		sort(y, x - 1);
		base[1][y][x - 1]++;
	}
	else if (base[1][y + 1][x] == base[1][y][x] - 1){
		sort(y + 1, x);
		base[1][y + 1][x]++;
	}
	else if (base[1][y - 1][x] == base[1][y][x] - 1){
		sort(y - 1, x);
		base[1][y - 1][x]++;
	}
}
void f_least()
/* Ĩȥ��β,�ҳ���βǰһ��,����ֵ����β */
{
	char temp = base[1][ey][ex];
	base[0][ey][ex] = ' ';
	base[1][ey][ex] = 0;
	if (base[1][ey][ex + 1] == temp)ex++;
	else if (base[1][ey][ex - 1] == temp)ex--;
	else if (base[1][ey + 1][ex] == temp)ey++;
	else if (base[1][ey - 1][ex] == temp)ey--;
}
void move_up()
/* �����˶� */
{
	base[0][sy][sx] = body;
	sy--;
	if (base[0][sy][sx] == ' '){
		sort(ey, ex);
		f_least();
	}
	base[0][sy][sx] = head;
	base[1][sy][sx] = 1;
}
void move_down()
/* �����˶� */
{
	base[0][sy][sx] = body;
	sy++;
	if (base[0][sy][sx] == ' '){
		sort(ey, ex);
		f_least();
	}
	base[0][sy][sx] = head;
	base[1][sy][sx] = 1;
}
void move_left()
/* �����˶� */
{
	base[0][sy][sx] = body;
	sx--;
	if (base[0][sy][sx] == ' '){
		sort(ey, ex);
		f_least();
	}
	base[0][sy][sx] = head;
	base[1][sy][sx] = 1;
}
void move_right()
/* �����˶� */
{
	base[0][sy][sx] = body;
	sx++;
	if (base[0][sy][sx] == ' '){
		sort(ey, ex);
		f_least();
	}
	base[0][sy][sx] = head;
	base[1][sy][sx] = 1;
}
void title()
/* ��Ϸ˵�� */
{
	printf("Greedy Snake\n");
	printf("snake head  %c\t\tsnake body  %c\n", head, body);
	printf("food  %c    wasd to control    score %d\n", food, score);
}
void in_move()
/* move�����е�һ���� */
{
	if (jud_food())eva_food();
	system("cls");
	title();
	print_d(base);
}
void move()
{
	char c;
	while (1){
		c=_getch();
		if (c == 'w')
		while (!_kbhit()){
			if (base[0][sy - 1][sx] == '+' || base[0][sy - 1][sx] == body) return;
			Sleep(delay);
			move_up();
			in_move();
		}
		else if (c == 's')
		while (!_kbhit()){
			if (base[0][sy + 1][sx] == '+' || base[0][sy + 1][sx] == body) return;
			Sleep(delay);
			move_down();
			in_move();
		}
		else if (c == 'a')
		while (!_kbhit()){
			if (base[0][sy][sx-1] == '+' || base[0][sy][sx-1] == body) return;
			Sleep(delay);
			move_left();
			in_move();
		}
		else if (c == 'd')
		while (!_kbhit()){
			if (base[0][sy][sx+1] == '+' || base[0][sy][sx+1] == body) return;
			Sleep(delay);
			move_right();
			in_move();
		}
	}
}
void beg()
/* ��Ϸ��ʼ */
{
	wall();
	eva_food();
	eva_head();
	print_d(base);
	score = 0;
}
void gameover()
{
	char a[11][25] = {0};
	int y, x, n = 35;
	for (x = 0; x < 4; x++)a[0][x] = n;
	for (x = 6; x < 10; x++)a[0][x] = n;
	for (x = 12; x < 19; x++)a[0][x] = n;
	for (x = 21; x < 25; x++)a[0][x] = n;
	for (y = 1; y < 5; y++)a[y][0] = n;
	for (y = 2; y < 5; y++)a[y][3] = n;
	for (y = 1; y < 5; y++)a[y][6] = n;
	for (y = 1; y < 5; y++)a[y][9] = n;
	for (y = 1; y < 5; y++)a[y][12] = n;
	for (y = 1; y < 5; y++)a[y][15] = n;
	for (y = 1; y < 5; y++)a[y][18] = n;
	for (y = 1; y < 5; y++)a[y][21] = n;
	a[2][2] = a[3][7] = a[3][8] = a[2][22] = a[2][23] = a[4][1] = a[4][2] = n;
	for (x = 22; x < 25; x++)a[4][x] = n;
	for (x = 0; x < 4; x++)a[6][x] = n;
	for (x = 12; x < 16; x++)a[6][x] = n;
	for (x = 18; x <22; x++)a[6][x] = n;
	for (y = 7; y < 11; y++)a[y][0] = n;
	for (y = 7; y < 11; y++)a[y][3] = n;
	for (y = 6; y < 10; y++)a[y][6] = n;
	for (y = 6; y < 10; y++)a[y][9] = n;
	for (y = 7; y < 11; y++)a[y][12] = n;
	for (y = 7; y < 11; y++)a[y][18] = n;
	for (x = 13; x < 15; x++)a[8][x] = n;
	for (x = 19; x < 22; x++)a[8][x] = n;
	a[10][1] = a[10][2] = a[10][7] = a[10][8] = a[10][13] = a[10][14] = a[10][15] = a[10][21] = a[9][20] = a[7][21] = n;
	for (y = 0; y < 11; y++)
		for (x = 0; x < 25; x++){
			printf("%c", a[y][x]);
			if (x == 24)printf("\n");
		}
}
void end()
/* ��Ϸ��β */
{
	gameover();
	printf("score %d\n", score);
	printf("enter 1 to retry, 0 to end\n");
}
int main()
{
	system("color 0E");
loop:title();
	beg();
	move();
	end();
	scanf("%d", &last);
	if (last == 1)goto loop;
	else system("exit");
}