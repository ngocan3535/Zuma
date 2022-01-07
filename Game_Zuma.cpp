#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <iostream>
#include "graphics.h"
#pragma comment(lib, "graphics.lib")
using namespace std;
#define R(x) ((int)(x+0.5))
#define Round(a) int (a+0.5)
#define max(a,b) (a>b) ? a:b

int count = 0; //Dem so ball hien huu

//NOTE: Nho kiem tra lai he mau coi chung dinh mau den/trang;
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
//Ve hinh tron
 struct Point 
{
	int x;
	int y;
};
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
 void drawMap3()
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
}
 void drawMap1()
{
	lineDDA(0,100,150,100,10);
	lineDDA(0,130,120,130,10);
	lineDDA(150,100,150,600,10);
	lineDDA(120,130,120,630,10);
	lineDDA(150,600,900,600,10);
	lineDDA(120,630,900,630,10);
}
void drawMap2()
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
}
//Tao mang chua ball
struct Ball{
	int x,y;
	int numb;
	int color;
	/*int type;*/ //The loai ball moi phat sinh -.- ??
};

Ball ball[500];

//Tao ball
void Create_ball(Ball ball[])
{
	ball[count].x = 60;//1074; 
	ball[count].y = 180;//25;
	ball[count].numb = count;
	//Kiem tra khong cho 3 vien lien tuc cung mau
	if (count > 1 && ball[count-1].color == ball[count-2].color)
	{	int check_color = ball[count-1].color;
		int avai_color = ball[count-1].color;
		while(avai_color == check_color)
		{
			avai_color = rand() % 15;
		}
		ball[count].color = avai_color;
	}
	else 
		ball[count].color = rand() % 15;
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
	////Chang 2 map 1
	//if ( ball[i].x > 130 && ball[i].x < 140 && ball[i].y < 610 )
	//{
	//	ball[i].x = 135;
	//	ball[i].y += 33;
	//	if(ball[i].y >= 610 && ball[i].y < 640)
	//	{
	//		ball[i].x -= 33;
	//		ball[i].y = 615;
	//	}
	//}
////Chang 3 map 1
	//if ( ball[i].y >= 610 && ball[i].y < 640)
	//{
	//	ball[i].x += 33;
	//}

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
			ball[i].y = 115;
			
		}
	}
	//Chang 8.2
	if ( ball[i].x <= 60 && ball[i].x >= 0 && ball[i].y <= 115 && ball[i].y >= 0 )
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

	cout << ball[0].x <<ball[0].y <<endl;
}

//Thuc Thi ball
void Run_ball(Ball ball[])
{
	do{
		drawMap3();
		Create_ball(ball);
		//Ve ball
		for (int i=0; i<=count; i++)
		{
			drawCircle(ball[i].x, ball[i].y, 15, ball[i].color);
			Move_ball(ball, i);
		}
		//cap nhat ball
		/*for (int i=0; i<=count; i++)
		{
			Move_ball(ball, i);
		}*/
		Sleep(50);
		cleardevice();
		count++;
	}while(count!=500);
	
	outtextxy( 200,200, "THUA ROI BA OI");
}
//kiem tra vi tri bal bay toi va lay toa do
int Check_local_Ball(int a, int b//a: balmang, b: ballban
	)
{
	for (int i=0; i <= count; i++)
	{
		if ( a==0 // toa do x cua balban > toa do balmang va <balmang +1      //Cai nay cung check xem ball co phu hop de them vao mang hay khong!
			)
			return a; //a: la numb cua balmang tai balmang +1
	}

}
//Xap nhap ball ban vao trong day ball
void Add_ball(Ball ball[])
{
	int a,b;//tam de k eror xoa sau
	int ball_demo; // ball ban ra
	//Neu ball ban == toa do y cua mot doi tuong bat ki trong mang, tuong doi cung duoc
	int get_ball_local = Check_local_Ball(a,b);
	//thi tao vong lap
	for (int i = count+1; i>=0; i--)
	{
		//gan gia tri cua toan bo balmang[i-1] cho balmang[i]
		//neu toi toa do get_ball_local thi gan vo va ket thuc vong lap
	}
	//Tao diem dich chuyen de hoi y kien moi nguoi
	for (int i=0; i<=count; i++)
	{
		Move_ball(ball, i);
	}
}
//Xoa ball khi du 3+ vien
void Del_ball();// wait for order moldune; them ham check lay tong so vien cung mau va vi tri ball dau ball cuoi va xap nhap len!
	
int main()
{
int gd = DETECT, gm; 
initwindow(1280,768, "c:\\tc\\bgi");
drawCircle(100,100,50, 1); //demo cir
drawMap3();
Run_ball(ball);
getch();
closegraph();
return 0;
}