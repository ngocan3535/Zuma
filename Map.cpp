#include <iostream>
#include <conio.h>
#include<windows.h>
#define R(x) ((int)(x+0.5))
#include "graphics.h"
#pragma comment (lib,"graphics.lib")
const int Ox = (1280/2);
const int Oy = (768/2);
int countName = 0;
char name[20];//name
int count = 0; 
#define Round(a) int (a+0.5)
#define max(a,b) (a>b) ? a:b
bool shoot = false;
void Mycircle(int xc, int yc, int r, int c, 
                 float pi,int rad,int alpha,int color=15);
POINT getMouseCoordinates();
int getLength(int x1,int y1,int x2,int y2);
double getAlpha(double cos);
double round(double d);
void laze();
void drawFog(int x,int y,int alpha);
void frogMove(int x,int y);
void shootBall(int x1,int y1,int x2,int y2,int alpha);
bool getMouseClickEvent(int alpha);
#define PI 3.14159265
int shootballcolor;
bool checkin = false;
using namespace std;

struct Ball{
	int x,y;
	int numb;
	int color;
	/*int type;*/ //The loai ball moi phat sinh -.- ??
};

Ball ball[400];

 struct Point 
{
	int x;
	int y;
};
 Point a[4];
 Ball b;

 void init(Point p)
{
	a[0] = p;
	a[1].x = a[0].x+100;
	a[1].y = a[0].y;
	a[2].x = a[0].x+100;
	a[2].y = a[0].y+40;
	a[3].x = a[0].x;
	a[3].y = a[0].y+40;
}
 void lineDDARad(int x1,int y1,int x2,int y2,double alpha,int color=15)
{
	double theta = (double)(alpha)*	PI / 180.0;
	int x3 = (x2 - Ox)* cos(theta)- (y2 - Oy)*sin(theta)+Ox;
	int y3 = (x2 - Ox)* sin(theta)+ (y2 - Oy)*cos(theta)+Oy;
	int x4 = (x1 - Ox)* cos(theta)- (y1 - Oy)*sin(theta)+Ox;
	int y4 = (x1 - Ox)* sin(theta)+ (y1 - Oy)*cos(theta)+Oy;
	x1 = x3;
	y1 = y3;
	x2 = x4;
	y2 =  y4;
	int Dx = x2 - x1, Dy = y2 - y1;
	float x_inc , y_inc;
	float step = max(abs(Dx),abs(Dy));
	x_inc = Dx / step;
	y_inc = Dy / step;
	double x = x1, y = y1;// Khoi tao cac gia tri ban dau
	putpixel(x, y, color);
	int k=1;
	while(k <= step){
		k++;
		x += x_inc;
		y += y_inc;
		
		putpixel(round(x),round(y),color);
	}
}	
 void lineDDA(int x1,int y1,int x2,int y2,int color)
{
     double m,x,y,xInc,yInc;
     x=x1;
     y=y1;
     if(x1==x2 && y1==y2)  
               putpixel(R(x1),R(y1),color);  
     else if(y1==y2) 
     {
          if(x1<x2)  
             xInc=1;  
          else
             xInc=-1; 
          while(x!=x2)  
          {
             putpixel(R(x),R(y),color);    
             x+=xInc;  
             Sleep(0.9);  
          } 
          putpixel(R(x),R(y),color); 
     }  
     else if(x1==x2)  
     {
          if(y1<y2)  
             yInc=1;
          else
             yInc=-1;  
          while(y!=y2)  
          {
             putpixel(R(x),R(y),color);   
             y=y+yInc; 
             Sleep(0.9); 
          } 
          putpixel(R(x),R(y),color);
     } 
     else if(abs(y2-y1)<abs(x2-x1))  
     {
          m=(y2-y1)/((double)(x2-x1));  
          if(x1<x2)  
          {
             xInc=1;
             yInc=m;
          }
          else  
          {
             xInc=-1;
             yInc=-m;
          }
          
          while(x!=x2)  
          {
             putpixel(R(x),R(y),color);  
             x+=xInc;  
             y=y+yInc; 
             Sleep(0.9);  
          } 
          putpixel(R(x),R(y),color);  
     }
     else 
     {
         m=(x2-x1)/((double)(y2-y1));  
         if(y1<y2)  
         {
            yInc=1;
            xInc=m;
         }
         else  
         {
             yInc=-1;
             xInc=-m;
         }
         while(y!=y2)  
         {
            putpixel(R(x),R(y),color);  
            x+=xInc; 
            y+=yInc; 
            Sleep(0.9); 
         }
         putpixel(R(x),R(y),color); 
     }
}  
void circlebres(float x1,float y1,float r)
{
	float x,y,p;
	x=0;
	y=r;
	p=3-(2*r);
	while(x<=y)
	{
		putpixel(x1+x,y1+y,YELLOW);
		putpixel(x1-x,y1+y,YELLOW);
		putpixel(x1+x,y1-y,YELLOW);
		putpixel(x1-x,y1-y,YELLOW);
		putpixel(x1+y,y1+x,YELLOW);
		putpixel(x1+y,y1-x,YELLOW);
		putpixel(x1-y,y1+x,YELLOW);
		putpixel(x1-y,y1-x,YELLOW);
		x=x+1;
		if(p<0)
		{
			p=p+4*(x)+6;
		}
		else
		{
			p=p+4*(x-y)+10;
			y=y-1;



		}
		delay(0.5);

	}
}
void draw(Point p)
{
	init(p);
	for (int i = 0;i < 3;i++)
	{
		line(a[i].x,a[i].y,a[i+1].x,a[i+1].y);
	}
	line(a[3].x,a[3].y,a[0].x,a[0].y);
}
void drawMap1(Point p)
{
	lineDDA(0,100,150,100,10);
	lineDDA(0,130,120,130,10);
	lineDDA(150,100,150,600,10);
	lineDDA(120,130,120,630,10);
	lineDDA(150,600,900,600,10);
	lineDDA(120,630,900,630,10);
	circlebres(938,615,40);
	circlebres(Ox,Oy,80);
	draw(p);
}
void drawMap2(Point p)
{
	lineDDA(0,100,150,100,10);//tren
	lineDDA(150,100,150,550,10);//tren
	lineDDA(150,550,850,550,10);//tren
	lineDDA(850,550,850,150,10);//tren
	lineDDA(850,150,1025,150,10);//tren
	lineDDA(1025,150,1025,427,10);//tren
	lineDDA(0,130,120,130,10);//duoi
	lineDDA(120,130,120,580,10);//duoi
	lineDDA(120,580,880,580,10);//duoi
	lineDDA(880,580,880,180,10);//duoi	
	lineDDA(880,180,995,180,10);//duoi	
	lineDDA(995,180,995,427,10);//duoi
	circlebres(1010,465,40);
	circlebres(Ox,Oy,80);
	draw(p);
}
void drawMap3(Point p)
{
	lineDDA(0,100,150,100,10);//tren
	lineDDA(150,100,150,550,10);//tren
	lineDDA(150,550,850,550,10);//tren
	lineDDA(850,550,850,150,10);//tren
	lineDDA(850,150,1025,150,10);//tren
	lineDDA(1025,150,1025,657,10);//tren
	lineDDA(40,657,1025,657,10);//tren
	lineDDA(80,40,80,627,10);//tren
	lineDDA(40,10,1180,10,10);//tren
	lineDDA(1180,10,1180,420,10);//tren
	lineDDA(0,130,120,130,10);//duoi
	lineDDA(120,130,120,580,10);//duoi
	lineDDA(120,580,880,580,10);//duoi
	lineDDA(880,580,880,180,10);//duoi	
	lineDDA(880,180,995,180,10);//duoi	
	lineDDA(995,180,995,627,10);//duoi
	lineDDA(80,627,995,627,10);//duoi
	lineDDA(050,10,050,657,10);//duoi
	lineDDA(80,40,1150,40,10);//duoi
	lineDDA(1150,40,1150,420,10);//duoi
	circlebres(1165,460,40);
	circlebres(Ox,Oy,80);
	draw(p);
}

//hàm menu và tên

void drawName()
{
	cleardevice();
	outtextxy(275-(countName*3),170,name);
}
void drawWarring()
{
	setcolor(RED);
	outtextxy(250-(countName*3),200,"QUA SO LUONG KI TU CHO PHEP!");
	setcolor(WHITE);
}	
void createName()
{
	char key = 0;
	cout << key;
	cleardevice();
	outtextxy(220,130,"HAY NHAP TEN CUA BAN!");
	while(countName!=-1)
	{
		outtextxy(220,130,"HAY NHAP TEN CUA BAN!");
		char tam[20]= "";
		key = getch();
		//OUT RANGE
		if (countName == 19 && key != 8)
		{
			countName =19;
			key = 0;
			drawWarring();
		}
		//SPECIAL KEY
		if (key == 32 && countName >= 1)
		{
			strcat(name, " ");
			drawName();
			countName ++;
		}
		if (key == 13 && countName >= 1)
		{
			countName =-1;
		}
		//CHAR KEY
		if (key == 65 || key == 97)
		{
			strcat(name, "A");
			drawName();
			countName ++;
		}
		if (key == 66 || key == 98)
		{
			strcat(name, "B");
			drawName();
			countName ++;
		}
		if (key == 67 || key == 99)
		{
			strcat(name, "C");
			drawName();
			countName ++;
		}
		if (key == 68 || key == 100)
		{
			strcat(name, "D");
			drawName();
			countName ++;
		}
		if (key == 69 || key == 101)
		{
			strcat(name, "E");
			drawName();
			countName ++;
		}
		if (key == 70 || key == 102)
		{
			strcat(name, "F");
			drawName();
			countName ++;
		}
		if (key == 71 || key == 103)
		{
			strcat(name, "G");
			drawName();
			countName ++;
		}
		if (key == 72 || key == 104)
		{
			strcat(name, "H");
			drawName();
			countName ++;
		}
		if (key == 73 || key == 105)
		{
			strcat(name, "I");
			drawName();
			countName ++;
		}
		if (key == 74 || key == 106)
		{
			strcat(name, "J");
			drawName();
			countName ++;
		}
		if (key == 75 || key == 107)
		{
			strcat(name, "K");
			drawName();
			countName ++;
		}
		if (key == 76 || key == 108)
		{
			strcat(name, "L");
			drawName();
			countName ++;	
		}
		if (key == 77 || key == 109)
		{
			strcat(name, "M");
			drawName();
			countName ++;	
		}
		if (key == 78 || key == 110)
		{
			strcat(name, "N");
			drawName();
			countName ++;	
		}
		if (key == 79 || key == 111)
		{
			strcat(name, "O");
			drawName();
			countName ++;	
		}
		if (key == 80 || key == 112)
		{
			strcat(name, "P");
			drawName();
			countName ++;	
		}
		if (key == 81 || key == 113)
		{
			strcat(name, "Q");
			drawName();
			countName ++;	
		}
		if (key == 82 || key == 114)
		{
			strcat(name, "R");
			drawName();
			countName ++;	
		}
		if (key == 83 || key == 115)
		{
			strcat(name, "S");
			drawName();
			countName ++;	
		}
		if (key == 84 || key == 116)
		{
			strcat(name, "T");
			drawName();
			countName ++;	
		}
		if (key == 85 || key == 117)
		{
			strcat(name, "U");
			drawName();
			countName ++;	
		}
		if (key == 86 || key == 118)
		{
			strcat(name, "V");
			drawName();
			countName ++;	
		}
		if (key == 87 || key == 119)
		{
			strcat(name, "W");
			drawName();
			countName ++;	
		}
		if (key == 88 || key == 120)
		{
			strcat(name, "X");
			drawName();
			countName ++;	
		}
		if (key == 89 || key == 121)
		{
			strcat(name, "Y");
			drawName();
			countName ++;	
		}
		if (key == 90 || key == 122)
		{
			strcat(name, "Z");
			drawName();
			countName ++;	
		}

		//NUMBER KEY
		if (key == 48)
		{
			strcat(name, "0");
			drawName();
			countName ++;	
		}
		if (key == 49)
		{
			strcat(name, "1");
			drawName();
			countName ++;	
		}
		if (key == 50)
		{
			strcat(name, "2");
			drawName();
			countName ++;	
		}
		if (key == 51)
		{
			strcat(name, "3");
			drawName();
			countName ++;	
		}
		if (key == 52)
		{
			strcat(name, "4");
			drawName();
			countName ++;	
		}
		if (key == 53)
		{
			strcat(name, "5");
			drawName();
			countName ++;	
		}
		if (key == 54)
		{
			strcat(name, "6");
			drawName();
			countName ++;	
		}
		if (key == 55)
		{
			strcat(name, "7");
			drawName();
			countName ++;	
		}
		if (key == 56)
		{
			strcat(name, "8");
			drawName();
			countName ++;	
		}
		if (key == 57)
		{
			strcat(name, "9");
			drawName();
			countName ++;	
		}
		//DEL KEY
		if (key == 8 && countName !=0)
		{
			countName --;	
			cout << endl;
			cout << name<<endl <<endl;
			strncpy(tam, name, countName);
			strncpy(name, tam, 20);
			cout <<name <<endl<< "     " <<countName;
			drawName();
		}
	}
}

void drawMenu()
{
	char key;
	int exit = 0, countMenu = 0;
	cleardevice();
		setcolor(YELLOW);
		outtextxy(200,200,">START");
		setcolor(WHITE);
		outtextxy(200,220,"EXIT");
	while(exit!=1)
	{
		key = getch();
		if (key == 72 || key == 80 || key == 75 || key == 77)
			if (countMenu == 0)
			{
				cleardevice();
				setcolor(WHITE);
				outtextxy(200,200," START");
				setcolor(YELLOW);
				outtextxy(200,220,">EXIT");
				countMenu++;
			}
			else
			{
				cleardevice();
				setcolor(YELLOW);
				outtextxy(200,200,">START");
				setcolor(WHITE);
				outtextxy(200,220," EXIT");
				countMenu--;
			}
		if (key == 13)
		{
			exit = 1;
			key =0;
		}
	}
}

void Create_ball(Ball ball[])
{
	ball[count].x = 0; 
	ball[count].y = 115;
	ball[count].numb = count;
	ball[count].color = rand() % 3 + 1;
}
//Xap nhap ball ban vao trong day ball
void addBall()
{
	int tmp;
	for(int i = b.numb; i < count; i++)
	{
		if(i == b.numb) 
		{
			tmp = ball[i].color;
			ball[i].color = b.color;
			count++;
		}
		else
		{
			swap(tmp, ball[i].color);
		}
		if(ball[i].y == 0)
			ball[i].y=100;
		cleardevice();
	}
	
}
//Xoa ball khi du 3+ vien
void put8pixel(int xc, int yc, int x, int y, int color)
{
    putpixel(x + xc, y + yc, color);
    putpixel(-x + xc, y + yc, color);
    putpixel(x + xc, -y + yc, color);
    putpixel(-x + xc, -y + yc, color);
    putpixel( y + xc, x + yc, color);
    putpixel(-y + xc, x + yc, color);
    putpixel(y + xc, -x + yc, color);
    putpixel(-y + xc, -x + yc, color);
}
void drawCircle(int xc, int yc, int r, int color)
{
    int x = 0, y = r;
    int f = 1 - r;

    put8pixel(xc, yc, x, y, color);

    while (x < y)
    {
        if (f < 0) f += (x << 1) + 3;
        else
        {
            y--;
            f += ((x - y) << 1) + 5;
        }
        x++;
        put8pixel(xc, yc, x, y, color);
    }
}
//Tang dich chuyen ball
void Move_ball(Ball ball[], int i)
{ 
	//chang 1
	if ( ball[i].x <= 130 && ball[i].y == 115)
	{
		ball[i].x += 33;
		if(ball[i].x > 130 && ball[i].x < 140)
			ball[i].y -= 33;

	}
//	//Chang 2 map 1
//	if ( ball[i].x > 130 && ball[i].x < 140 && ball[i].y < 610 )
//	{
//		ball[i].x = 135;
//		ball[i].y += 33;
//		if(ball[i].y >= 610 && ball[i].y < 640)
//		{
//			ball[i].x -= 33;
//			ball[i].y = 615;
//		}
//	}
////Chang 3 map 1
//	if ( ball[i].y >= 610 && ball[i].y < 640)
//	{
//		ball[i].x += 33;
//	}

	////Chang 2 map 2
	//if ( ball[i].x > 130 && ball[i].x < 140 && ball[i].y <= 550 )
	//{
	//	ball[i].x = 135;
	//	ball[i].y += 33;
	//	if ( ball[i].y >= 560 && ball[i].y < 580)
	//{
	//	ball[i].x -= 10;
	//}
	//}
	////Chang 3 map 2
	//if ( ball[i].y >= 560 && ball[i].y < 580 && ball[i].x < 860)
	//{
	//	ball[i].y = 565;
	//	ball[i].x += 33;
	//	if (ball[i].y >= 170 && ball[i].x >= 860 && ball[i].x <= 890)
	//		ball[i].y += 5;

	//}
	////Chang 4 map 2
	//if (ball[i].x >= 860 && ball[i].x <= 890 && ball[i].y >= 170)
	//{
	//	ball[i].y -= 33;
	//	ball[i].x = 865;
	//	if (ball[i].y <= 170 && ball[i].y >= 140  && ball[i].x <= 1000 && ball[i].x >= 700)
	//	{
	//		ball[i].x -= 3;
	//	}
	//}
	////Chang 5 map 2
	//if (ball[i].y <= 170 && ball[i].y >= 140  && ball[i].x <= 1000 && ball[i].x >= 700)
	//{
	//	ball[i].y = 165;
	//	ball[i].x += 33;
	//	if (ball[i].x >= 1001 && ball[i].x <= 1040 )
	//	{
	//		ball[i].y -= 5;
	//	}
	//}
	////Chang 6 map 2
	//if (ball[i].x > 1000 && ball[i].x <= 1040 )
	//{
	//	ball[i].y += 33;
	//	ball[i].x = 1010;
	//}

	//Chang2 map 3
	if ( ball[i].x > 130 && ball[i].x < 140 && ball[i].y <= 560 )
	{
		ball[i].x = 135;
		ball[i].y += 33;
		if(ball[i].y > 560 && ball[i].y < 590)
		{
			ball[i].x -= 10;
		}		
	}
	//Chang3 map 3
	if ( ball[i].y > 560 && ball[i].y < 590 && ball[i].x < 860 && ball[i].x >= 80)
	{
		ball[i].y = 565;
		ball[i].x += 33;
		if ( ball[i].y > 100 && ball[i].x < 890 && ball[i].x >= 860)
		{
		ball[i].y+=5;
		}
	}
	//Chang 4 map 3
	if ( ball[i].y >= 170 && ball[i].y <= 590 && ball[i].x < 890 && ball[i].x >= 860)
	{
		ball[i].x = 865;
		ball[i].y -= 33;
		if ( ball[i].y >= 140 && ball[i].y < 170 && ball[i].x >= 860 && ball[i].x <= 995 )
		{
			ball[i].x -= 2;
		}
	}
	//Chang 5 map 3
	if ( ball[i].y >= 140 && ball[i].y < 170 && ball[i].x >= 860 && ball[i].x <= 995 )
	{
		ball[i].y = 165;
		ball[i].x += 33;
		if ( ball[i].x >= 999 && ball[i].x <= 1030 && ball[i].y >= 160 && ball[i].y <= 620 )
		{
			ball[i].y -= 5;
		}
	}
	//Chang 6 map 3
	if ( ball[i].x >= 999 && ball[i].x <= 1030 && ball[i].y >= 160 && ball[i].y <= 630 )
	{
		ball[i].x = 1010;
		ball[i].y += 33;
		if ( ball[i].y <= 670 && ball[i].y >= 631 && ball[i].x <= 1020 && ball[i].x >= 61 )
		{
			ball[i].x +=8;
		}
	}
	//Chang 7 map 3
	if ( ball[i].y <= 670 && ball[i].y >= 631 && ball[i].x <= 1020 && ball[i].x >= 61 )
	{
		ball[i].y = 642;
		ball[i].x -= 33;
	}
	//Chang 8.1 map 3
	if ( ball[i].x <= 60 && ball[i].x >= 0 && ball[i].y <= 645 && ball[i].y >= 120 )
	{
		
		ball[i].x = 60;
		ball[i].y -= 33;
		if ( ball[i].x <= 60 && ball[i].x >= 0 && ball[i].y <= 120 && ball[i].y >= 90 )
		{
			ball[i].y = 114;
			
		}
	}
	//Chang 8.2
	if ( ball[i].x <= 60 && ball[i].x >= 0 && ball[i].y < 115 && ball[i].y >= 0 )
	{
		ball[i].x = 60;
		ball[i].y -= 33;
		if ( ball[i].y >= 0 && ball[i].y <= 29 && ball[i].x >= 50 && ball[i].x <= 1100 )
		{
			ball[i].x -= 9;
		}
	}
	//Chang 9 map 3
	if ( ball[i].y >= 0 && ball[i].y <= 29 && ball[i].x >= 50 && ball[i].x <= 1150 )
	{
		ball[i].y = 25;
		ball[i].x += 33;
		if ( ball[i].x >= 1151 && ball[i].x <= 1180  && ball[i].y >= 10 )
		{
			ball[i].y -= 11;
		}
	}
	//Chang 10
	if ( ball[i].x >= 1151 && ball[i].x <= 1180  && ball[i].y >= 10 )
	{
		ball[i].x = 1165;
		ball[i].y += 33;
	}

	/*cout << ball[0].x <<ball[0].y <<endl;*/
}
void delBall(int start, int end){
	// Remove ball from start to end
	for(int i = end; i >= end - start + 1; i--)
	{
		ball[i].color = ball[i-(end - start + 1)].color;
	}
	// Update ball index
	for(int i = 0; i <= count; i++)
	{
		ball[i] = ball[i + (end - start + 1)];
	}
	count -= (end - start + 1);
}
double calDistance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow((double) (x1 - x2), 2) + pow((double) (y1 - y2), 2));
}
int findClosestBall(){
	for(int i = 0; i <= count; i++){
		double d = calDistance(ball[i].x, ball[i].y, b.x, b.y);
		if (d <= 15)
			return i;
	}
	return -1;
}
void findSameColorIndex(int &start, int &end, Ball b1){
	int i = b1.numb;
	while(b1.color == ball[i].color && i >= 0){
		i--;
	}
	if(i++ > b.numb)
		start = i++;
	else
		start = i;

	i = b1.numb;
	while(b1.color == ball[i].color && i <= count){
		i++;
	}
	if(i-- < b1.numb)
		end = i--;
	else
		end = i;
}
void processCollision(){
	checkin = true; //
	int index = findClosestBall();
	int start, end;
	findSameColorIndex(start, end, ball[index]);
	if(b.color != ball[index].color || end - start + 1  < 2) 
	{
		b.numb = index;
		addBall();
	}
	else
	{
		if (start <= end) {
			delBall(start, end);
			// Chain reaction
			while(ball[start].color == ball[start-1].color){
				findSameColorIndex(start, end, ball[start]);
				delBall(start, end);
			}
		}
	}
	
		b.x=-1;
		b.y=-1;
}
void ballToball(int alpha)
{ 
	// b la bong ban ra
 ////map 2
	//if( b.x >= 110 && b.x <= 160 && b.y >= 100 && b.y <= 535 && alpha <= 295 && alpha>= 250)
	//	processCollision();  
	//if( b.x >= 120 && b.x <= 880 && b.y >= 520 && b.y <= 595 && alpha <= 249 && alpha>= 131)
	//	processCollision();  
	//if( b.x >= 830 && b.x <= 600 && b.y >= 535 && b.y <= 545 && alpha <= 130 && alpha>= 49)
	//	processCollision();  

////map 1
//	if( b.x >= 125 && b.x <= 160 && b.y >= 100 && b.y <= 590 && alpha <= 295 && alpha>= 245)
//		processCollision();  
//	if( b.x >= 130 && b.x <= 900 && b.y >= 560 && b.y <= 650 && alpha <= 244 && alpha>= 134)
//		processCollision();  
//map3
	if( b.x >= 40 && b.x <= 1000 && b.y >= 0 && b.y <= 70 && alpha >= 298 && alpha <= 359 && alpha >= 0 && alpha <= 41 )
		processCollision();  
	if( b.x >= 110 && b.x <= 160 && b.y >= 110 && b.y <= 540 && alpha <= 294 && alpha>= 250)
		processCollision();  
	if( b.x >= 120 && b.x <= 885 && b.y >= 530 && b.y <= 590 && alpha <= 249 && alpha>= 128)
		processCollision();  
	if( b.x >= 830 && b.x <= 895 && b.y >= 160 && b.y <= 530 && alpha <= 127 && alpha>= 40)
		processCollision(); 

}
void Run_ball()
{
		Create_ball(ball);
		//Ve ball
		for (int i=0; i<= count; i++)
		{
			drawCircle(ball[i].x, ball[i].y, 15, ball[i].color);
			Move_ball(ball, i);
		}
		cleardevice();
		count++;	
}

int main()
{
	int gd = DETECT, gm;
    initwindow(1280,768,"ZUMA GAME");
	int dx,dy,dx1,dy1,color;
	drawMenu();
	createName();
	Point f;
	f.x=900;
	f.y=739;/*drawMap3(f);*/
	shootballcolor = rand() % 3 + 1;;
	while(true)
	{
		frogMove(Ox,Oy);
		Sleep(30);
		cleardevice();
	}
	outtextxy(250,300,"THUA ROI NHA!");
	getch();
	return 0;
}

void drawFog(int x,int y,int alpha, double scale)
{

	//mat	
	Mycircle(x-35*scale,y-75*scale,20*scale,20*scale,0,360,alpha);
	Mycircle(x+35*scale,y-75*scale,20*scale,20*scale,0,360,alpha);
	//luoi
	Mycircle(x,y-100*scale,30*scale,70*scale,alpha,180,alpha);
	//than
	lineDDARad(x-50*scale,y-100*scale,x+50*scale,y-100*scale,alpha);
	lineDDARad(x-50*scale,y-100*scale,x-75*scale,y-25*scale,alpha);
	lineDDARad(x+50*scale,y-100*scale,x+75*scale,y-25*scale,alpha);
	lineDDARad(x+75*scale,y-25*scale,x+50*scale,y+100*scale,alpha);
	lineDDARad(x-75*scale,y-25*scale,x-50*scale,y+100*scale,alpha);
	lineDDARad(x-50*scale,y+100*scale,x+50*scale,y+100*scale,alpha);
	//tay phai
	lineDDARad(x+75*scale,y-10*scale,x+100*scale,y-10*scale,alpha);
	lineDDARad(x+75*scale,y-10*scale,x+120*scale,y-10*scale,alpha);
	lineDDARad(x+100*scale,y-25*scale,x+100*scale,y-100*scale,alpha);
	lineDDARad(x+120*scale,y-10*scale,x+120*scale,y-100*scale,alpha);
	lineDDARad(x+75*scale,y-25*scale,x+100*scale,y-25*scale,alpha);
	lineDDARad(x+120*scale,y-100*scale,x+100*scale,y-100*scale,alpha);
	//tay trai
	lineDDARad(x-75*scale,y-25*scale,x-100*scale,y-25*scale,alpha);
	lineDDARad(x-75*scale,y-10*scale,x-120*scale,y-10*scale,alpha);
	lineDDARad(x-100*scale,y-25*scale,x-100*scale,y-100*scale,alpha);
	lineDDARad(x-120*scale,y-10*scale,x-120*scale,y-100*scale,alpha);
	lineDDARad(x-100*scale,y-100*scale,x-120*scale,y-100*scale,alpha);
	//chan trai
	lineDDARad(x-55*scale,y+75*scale,x-120*scale,y+75*scale,alpha);
	lineDDARad(x-55*scale,y+85*scale,x-100*scale,y+85*scale,alpha);
	lineDDARad(x-120*scale,y+75*scale,x-120*scale,y+150*scale,alpha);
	lineDDARad(x-100*scale,y+85*scale,x-100*scale,y+150*scale,alpha);
	lineDDARad(x-120*scale,y+150*scale,x-100*scale,y+150*scale,alpha);
	//chan phai
	lineDDARad(x+55*scale,y+75*scale,x+120*scale,y+75*scale,alpha);
	lineDDARad(x+55*scale,y+85*scale,x+100*scale,y+85*scale,alpha);
	lineDDARad(x+120*scale,y+75*scale,x+120*scale,y+150*scale,alpha);
	lineDDARad(x+100*scale,y+85*scale,x+100*scale,y+150*scale,alpha);
	lineDDARad(x+120*scale,y+150*scale,x+100*scale,y+150*scale,alpha);
	//bong
	Mycircle(x,y-120*scale,20*scale,20*scale,0,360,alpha,shootballcolor);

}
void frogMove(int x,int y)
{
	POINT p = getMouseCoordinates();
	Point f;
	f.x=900;
	f.y=739;
	int lengthAC = getLength(getmaxx()/2,getmaxy()/2,p.x,p.y);//canh huyen
	int lengthAB = getLength(getmaxx()/2,getmaxy()/2,p.x,getmaxy()/2);//canh ke
	double cos = (lengthAB*1.0) / (lengthAC*1.0);
	double alpha = getAlpha(cos);
	alpha = alpha * 180 / PI;//doi tu rad sang dec
	if (p.x < getmaxx()/2 && p.y < getmaxy()/2)
		alpha += 270;
	else if (p.x < getmaxx()/2 && p.y > getmaxy()/2)
		alpha = 270 - alpha;
	else if (p.x > getmaxx()/2 && p.y > getmaxy()/2)
		alpha += 90;
	else if (p.x > getmaxx()/2 && p.y < getmaxy()/2)
		alpha = 90 - alpha;
	drawFog(Ox,Oy,alpha,0.5);
	drawMap3(f);//map 3
	//drawMap2(f);//map2
	//drawMap1(f);//map1
	Run_ball();
	ballToball(alpha);
	if (ball[0].x == 1165 && ball[0].y >= 500) //map 2 x= 1010 và y>= 500   //map 3 x= 1165 y >= 500 map1 ball[0].y == 615 && ball[0].x >= 900;
	{
		cleardevice();
		outtextxy(300,200,"BAN THUA ROI!");
		delay(2000); 
		closegraph();
	}
	getMouseClickEvent(alpha);
}
void shootBall(int x1,int y1,int x2,int y2,int alpha)
{

	double theta = (double)(alpha)*	PI / 180.0;
	int x3 = (x1 - Ox)* cos(theta)- (y1 - Oy)*sin(theta)+Ox;
	int y3 = (x1 - Ox)* sin(theta)+ (y1 - Oy)*cos(theta)+Oy;
	x1 = x3;
	y1 = y3;
	int Dx = x2 - x1, Dy = y2 - y1;
	float x_inc , y_inc;
	float step = max(abs(Dx),abs(Dy));
	x_inc = Dx / step;
	y_inc = Dy / step;
	double x = x1, y = y1;// Khoi tao cac gia tri ban da
	int k=1;
	if (shoot == false)
	{
		shoot = true;
		while(k <= step && x < getmaxx() && y < getmaxy() && x > 0 && y >0 ){
			k+=1;
			x += x_inc *45;//skip frame
			y += y_inc *45;

			b.x = x;
			b.y =y;
			b.color = shootballcolor;
			Mycircle(x,y,15,15,0,360,0,shootballcolor);// scale trai banh ban ra
			frogMove(Ox,Oy);
			Sleep(30);
			cleardevice();
			cout << ball[0].x << "   "<<ball[0].y<<endl;
		}
		shoot = false;
	}
}
void laze()
{
	POINT p = getMouseCoordinates();
	setcolor(RED);
	lineDDA(getmaxx()/2,getmaxy()/2,p.x,p.y,0);
}
bool getMouseClickEvent(int alpha)
{
	int x,y;
	checkin = false;
	if (ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, x, y);
			shootBall(Ox,Oy-120*0.5,x,y,alpha);// scale toa do tam
			shootballcolor = rand() % 3 + 1;;
			return true;
       }
	return false;
}
double round(double d)
{
  return floor(d + 0.5);
}
double getAlpha(double cos)
{
	double alpha = acos(cos);
	return alpha;	
}
int getLength(int x1,int y1,int x2,int y2)
{
	float length = sqrt(pow(x2-x1,2*1.0)+pow(y2-y1,2*1.0));
	return length;
}
POINT getMouseCoordinates()
{
	POINT Position;
	GetCursorPos(&Position);
	return Position;
}
void Mycircle(int xc, int yc, int r, int c, float pi,int rad,int alpha,int color)
{ 
	double rotatealpha = (double)(alpha)*	PI / 180.0;
	int x3 = (xc  - Ox)* cos(rotatealpha)- (yc  -  Oy)*sin(rotatealpha)+Ox;
	int y3 = (xc  - Ox)* sin(rotatealpha)+ (yc  - Oy)*cos(rotatealpha)+Oy;
	xc = x3;
	yc = y3;
    float t = 3.14 / 180;
    setcolor(color); 
    int theta; 
    // Filling each pixel corresponding 
    // to every angle from 0 to 360 
   for (int i = 0; i < rad; i += 1) { 
        theta = i; 
        int x = r * cos(t * theta) * cos(t * pi) 
                + c * sin(t * theta) * sin(t * pi); 
  
        int y = c * sin(t * theta) * cos(t * pi) 
                - r * cos(t * theta) * sin(t * pi); 
  
        putpixel(xc + x, yc - y, color);
    } 
}
