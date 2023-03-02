#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<process.h>

int midX[8] = { 54, 112, 170, 228, 286, 344, 402, 460 };
int midY[8] = { 35, 93, 151, 209, 267, 325, 383, 441 };
char i[8] = {'0','0','0','0','0','0','0','0'};
char pb[8] = {'0','0','0','0','0','0','0','0'};
int count;

union REGS in,out;
int py, px;
int click;

void initM(){
	in.x.ax = 0;
	int86( 51, &in, &out );
}

void showM(){
	in.x.ax = 1;
	int86( 51, &in, &out );
}

void getMxy(){
	in.x.ax = 3;
	int86( 51, &in,  &out );
	click = out.x.bx;
	px = out.x.cx;
	py = out.x.dx;
}

void DrawAgain( int, int );
int checkW( int, int );
int checkB( int, int );
void CoorRajaW( int *, int * );
void CoorRajaB( int *, int * );

void hideM(){
	in.x.ax = 2;
	int86( 51, &in, &out );
}


void logo()
{
	setbkcolor(BROWN);
	rectangle(280,255,350,265);
	setfillstyle(1,BROWN);
	floodfill(281,257,WHITE);
	line(280,248,350,248);      //bottom
	line(280,248,272,200);      // left
	line(350,248,358,200);      // right
	line(272,200,276,198);      //  ***1
	line(358,200,354,198);      //	***2
	line(276,198,290,225);      // left
	line(354,198,340,225);      // right
	line(290,225,279,170);      // left line
	line(340,225,351,170);      // right line
	line(279,170,284,168);      //  ***1
	line(351,170,346,168);      //  ***2
	line(284,168,306,215);      // left line top
	line(346,168,324,215);      // right line top
	line(306,215,313,145);      // left ttp
	line(324,215,317,145);      // right ttp
	line(313,145,317,145);      // ***1
	setfillstyle(1,YELLOW);
	floodfill(300,199,WHITE);
	settextstyle(3,0,4);
	setcolor(BLACK);
	setfillstyle(1,BLACK);
	circle(315,230,140);
	circle(315,230,160);
	floodfill(600,230,BLACK);
	floodfill(2,230,BLACK);
	setfillstyle(1,10);
	floodfill(170,230,BLACK);
	outtextxy(235-10,330-50,"CHESS CLUB");
	outtextxy(236-10,330-50,"CHESS CLUB");
	outtextxy(234-10,330-50,"CHESS CLUB");
	outtextxy(235-10,331-50,"CHESS CLUB");
	outtextxy(235-10,329-50,"CHESS CLUB");

	setfillstyle(1,BLACK);
	circle(270,190,5);
	floodfill(270,190,BLACK);
	delay(300);         // left *1

	setfillstyle(1,BLACK);
	circle(360,190,5);
	floodfill(360,190,BLACK);
	delay(300);	    // left *2

	setfillstyle(1,BLACK);
	circle(278,160,5);
	floodfill(278,160,BLACK);
	delay(300);  	    // left *3

	setfillstyle(1,BLACK);
	circle(352,160,5);
	floodfill(352,160,BLACK);
	delay(300);	    // left *4

	setfillstyle(1,BLACK);
	circle(315,136,5);
	floodfill(315,136,BLACK);
	delay(500);

	int a;
	for(a=0;a<340;a++){
		setcolor(YELLOW);
		arc(315+a,230,270,90,160);
		delay(5);
	}
	delay(500);
	cleardevice();
	setbkcolor(BLACK);
	delay(500);
}



char plc[8][8] = {
	{'r','a','0','0','0','0','A','R'},
	{'s','b','0','0','0','0','B','S'},
	{'t','c','0','0','0','0','C','T'},
	{'q','d','0','0','0','0','D','Q'},
	{'k','e','0','0','0','0','E','K'},
	{'x','f','0','0','0','0','F','X'},
	{'y','g','0','0','0','0','G','Y'},
	{'z','h','0','0','0','0','H','Z'}
		};


void vajir( int x, int y, int col1, int col2 ){

	setcolor( col1 );

	line( x, y-20, x-20, y-10 );
	line( x, y-20, x+20, y-10 );
	line( x, y+20, x+20, y+10 );
	line( x, y+20, x-20, y+10 );
	line( x-20, y-10, x-20, y+10 );
	line( x+20, y-10, x+20, y+10 );

	line( x, y-23, x-22, y-13 );
	line( x, y-23, x+22, y-13 );
	line( x-23, y-12, x-23, y+12 );
	line( x+23, y-12, x+23, y+12 );
	line( x, y+23, x-22, y+13 );
	line( x, y+23, x+22, y+13 );

	setfillstyle(1,col2);
	floodfill( x, y, col1 );

	circle( x, y, 10 );
	circle( x, y, 8 );

	setcolor( 15 );

}
void raja( int x, int y, int col1, int col2 ){

	setcolor( col1 );

	line( x-10, y-20, x-20, y-10 );
	line( x-10, y-20, x+10, y-20 );
	line( x-20, y-10, x-20, y+10 );
	line( x-10, y+20, x-20, y+10 );
	line( x+10, y-20, x+20, y-10 );
	line( x+20, y-10, x+20, y+10 );
	line( x+20, y+10, x+10, y+20 );
	line( x-10, y+20, x+10, y+20 );

	line( x-12, y-23, x-22, y-13 );
	line( x-11, y-23, x+11, y-23 );
	line( x-23, y-12, x-23, y+12 );
	line( x-12, y+23, x-22, y+13 );
	line( x+12, y-23, x+22, y-13 );
	line( x+23, y-12, x+23, y+12 );
	line( x+22, y+13, x+12, y+23 );
	line( x-12, y+23, x+12, y+23 );

	setfillstyle( 1, col2 );
	floodfill( x, y, col1 );

	rectangle( x-8, y-8, x+8, y+8 );
	line( x, y-4, x, y+4 );
	line( x-4, y, x+4, y );

	line( x-8, y-8, x-15, y-15 );
	line( x-8, y+8, x-15, y+15 );
	line( x+8, y-8, x+15, y-15 );
	line( x+8, y+8, x+15, y+15 );
	line( x, y-8, x, y-20 );
	line( x, y+8, x, y+20 );
	line( x-8, y, x-20, y );
	line( x+8, y, x+20, y );

	setcolor( 15 );
}

void horseB( int x, int y, int col1, int col2 ){

	setcolor( col1 );

	line( x-20, y-20, x+20, y-20 );
	line( x-20, y-20, x-20, y );
	line( x+20, y-20, x+20, y );
	line( x, y+20, x+20, y );
	line( x, y+20, x-20, y );


	line( x-22, y-23, x+22, y-23 );
	line( x-23, y-23, x-23, y+3 );
	line( x+23, y-23, x+23, y+3 );
	line( x+23, y+3, x, y+23 );
	line( x-23, y+3, x, y+23 );

	setfillstyle( 1, col2 );
	floodfill( x, y, col1 );

	line( x-15, y-15, x+15, y-15 );
	line( x, y+12, x-15, y-15 );
	line( x, y+12, x+15, y-15 );

	setcolor( 15 );
}
void horseW( int x, int y, int col1, int col2 ){

	setcolor( col1 );

	line( x-20, y+20, x+20, y+20 );
	line( x-20, y+20, x-20, y );
	line( x+20, y+20, x+20, y );
	line( x, y-20, x-20, y );
	line( x, y-20, x+20, y );


	line( x-22, y+23, x+22, y+23 );
	line( x-23, y+23, x-23, y-3 );
	line( x+23, y+23, x+23, y-3 );
	line( x+23, y-3, x, y-23 );
	line( x-23, y-3, x, y-23 );

	setfillstyle( 1, col2 );
	floodfill( x, y, col1 );

	line( x-15, y+15, x+15, y+15 );
	line( x, y-12, x-15, y+15 );
	line( x, y-12, x+15, y+15 );

	setcolor( 15 );
}

void hathi( int x, int y, int col1, int col2 ){

	  setcolor( col1 );

	rectangle( x-23, y-23, x+23, y+23 );
	rectangle( x-20, y-20, x+20, y+20 );
	rectangle( x-10, y-20, x+10, y-13 );
	rectangle( x-20, y-10, x-13, y+10 );
	rectangle( x-10, y+20, x+10, y+13 );
	rectangle( x+20, y-10, x+13, y+10 );
	//rectangle( x-13, y-13, x+13, y+13 );
	setfillstyle( 1, col2 );
	floodfill( x+7, y+7, col1 );
	rectangle( x-6, y-6, x+6, y+6 );

	setcolor( 15 );

}

void pyada( int x, int y, int col1, int col2 ){

	setcolor( col1 );

	line( x-10, y-20, x-20, y-10 );
	line( x-10, y-20, x+10, y-20 );
	line( x-20, y-10, x-20, y+10 );
	line( x-10, y+20,  x-20, y+10 );
	line( x+10, y-20, x+20, y-10 );
	line( x+20, y-10, x+20, y+10 );
	line( x+20, y+10, x+10, y+20 );
	line( x-10, y+20, x+10, y+20 );

	setfillstyle( 1, col2 );
	floodfill( x, y, col1 );

	circle( x, y, 10 );

	setcolor( 15 );

}

void rani( int x, int y, int col1, int col2 ){

	setcolor( col1 );

	circle( x, y, 20 );
	circle( x, y, 23 );
	setfillstyle( 1, col2 );
	floodfill( x, y, col1 );

	arc( x, y, 65, 115, 6 );
	arc( x, y, 155, 215, 6 );
	arc( x, y, 245, 305, 6 );
	arc( x, y, 335, 395, 6 );

	arc( x, y, 10, 110, 12 );
	arc( x, y, 140, 220, 12 );
	arc( x, y, 250, 350, 12 );

	line( x-6, y-3, x+6, y+3 );
	line( x-6, y+3, x+6, y-3 );
	line( x+3, y-6, x-3, y+6 );
	line( x-3, y-6, x+3, y+6 );

	line( x-18, y-10, x-11, y-7 );
	line( x-18, y+10, x-11, y+7 );

	line( x-10, y-18, x-5, y-10 );
	line( x+12, y-3, x+19, y-6 );

	line( x-7, y+18, x-5, y+10 );
	line( x+12, y+3, x+19, y+6 );

	setcolor( 15 );

}

void loading()
{
	cleardevice();
	settextstyle(1,0,1);
	int a=-5;
	for(int v=0;v<=360;v++){
		setcolor(WHITE);
		arc(320,220,0,v,71);
		arc(320,220,0,v,72);
		arc(320,220,0,v,73);
		arc(320,220,0,v,74);
		arc(320,220,0,v,75);
		arc(320,220,0,v,76);
		arc(320,220,0,v,77);
		arc(320,220,0,v,78);
		arc(320,220,0,v,79);

		switch(v){

		case 0:raja(320,210,WHITE,BLACK);
		outtextxy(300,240,"KING");
		outtextxy(270,340,"LOADING.");break;

		case 60:cleardevice();
		settextstyle(1,0,1);
		rani(320,210,WHITE,BLACK);
		outtextxy(295,240,"QUEEN");
		outtextxy(270,340,"LOADING. .");break;

		case 120:cleardevice();
		settextstyle(1,0,1);
		vajir(320,210,WHITE,BLACK);
		outtextxy(295,240,"Bishop");
		outtextxy(270,340,"LOADING. . .");break;

		case 180:cleardevice();
		settextstyle(1,0,1);
		pyada(320,210,WHITE,BLACK);
		outtextxy(300,240,"Pawn");
		outtextxy(270,340,"LOADING. . .");break;

		case 240:cleardevice();
		settextstyle(1,0,1);
		hathi(320,210,WHITE,BLACK);
		outtextxy(300,240,"Rook");
		outtextxy(270,340,"LOADING. . . .");break;

		case 300:cleardevice();
		settextstyle(1,0,1);
		horseW(320,210,WHITE,BLACK);
		outtextxy(295,240,"Knight");
		outtextxy(270,340,"LOADING. . . . .");break;

		case 359:cleardevice();
		settextstyle(1,0,1);
		raja(320,210,WHITE,BLACK);
		outtextxy(300,240,"King");
		outtextxy(270,340,"LOADING. . . . .");break;

		default:;
		}
		if(v%18==0)
		{
		a=a+5;
		gotoxy(39,25);
		cout<<a;
		}
		settextstyle(2,0,5);
		outtextxy(340,383,"%");
		delay(10);
	}
	for(int d=5;d<400;d++)
	{
		setcolor(BROWN);
		circle(320,220,80+d);
		setcolor(WHITE);
		settextstyle(1,0,1);
		outtextxy(270,340,"LOADING. . . . .");
		settextstyle(2,0,5);

		outtextxy(305,383,"100");
		//gotoxy(39,25);
		//cout<<a;
		settextstyle(2,0,5);
		outtextxy(340,383,"%");
	}
	delay(500);
//	setfillstyle(1,BROWN);
  //	floodfill(633,0,15);

}

/*-------------------------------------------------------------------*/
/*===========================================================*/

void exitwindow();
void credits();
void help(int);
void basic();

void box()
{       cleardevice();
	int ii;
	for(ii=0;ii<150;ii++)
	{
		delay(2);
		setcolor(BROWN);
		line(70,120+ii,560,120+ii);
		line(70,380-ii,560,380-ii);
	}
	for(ii=0;ii<102;ii++)
	{
		delay(2);
		setcolor(15);
		line(100,150+ii,530,150+ii);
		line(100,350-ii,530,350-ii);
	}
	setcolor(0);
	settextstyle(3,0,4);
	outtextxy(251,161,"NOTE:-");
	outtextxy(250,160,"NOTE:-");
	outtextxy(150,210,"PLAYER 1 = WHITE");
	outtextxy(150,250,"PLAYER 2 = BLACK");
	settextstyle(2,0,6);
	outtextxy(160,320,"(PRESS ENTER FOR CONTINUE...)");
	getch();
	cleardevice();
}

void startmenu()
{
	delay(500);
	cleardevice();
	setcolor( 15 );
	settextstyle( 0,1,2 );
	outtextxy( 20, 70, "C    H    E    S    S");

	int x1=25,y1=6, x2=640, y2=472;
	rectangle( x1, y1, x2, y2 );
	rectangle( 5+x2, y1, 639, y2 );
	setfillstyle(1,BROWN);
	floodfill(x1+15,y1+5,WHITE);

	//setfillstyle(7,RED);
      //	floodfill(x1+15,y1+5,WHITE);



	int winx=200,winy=220,winx2=450,winy2=220;
	int win2x=200,win2y=220,win2x2=450,win2y2=220;

	for(int i=0;i<150;i++){
	setcolor(8);
	line(winx,winy--,winx2,winy2--);
	delay(3);
	line(win2x,win2y++,win2x2,win2y2++);
	}
	winx=240,winy=220,winx2=440,winy2=220;
	win2x=240,win2y=220,win2x2=440,win2y2=220;

	for(i=0;i<140;i++){
	setcolor(YELLOW);
	line(winx,winy--,winx2,winy2--);
	delay(2);
	line(win2x,win2y++,win2x2,win2y2++);
	}
	setcolor(RED);
	settextstyle(0,0,2);
	outtextxy(250,100,"--M E N U--");
	setcolor(BLACK);
	settextstyle( 0,0,3);
	int gap=100,val=50;
	outtextxy(250,gap+=val,"PLAY");
	delay(150);
	outtextxy(250,gap+=val,"HELP");
	delay(140);
	outtextxy(250,gap+=val,"CREDITS");
	delay(130);
	outtextxy(250,gap+=val,"EXIT");
	settextstyle(0,0,1);
	setcolor(YELLOW);
	//outtextxy(90,400,"keys: Use Numeric Keys to Select & 'y' or 'Enter' Key To Confrom");



     //---------------------------method1---------------------
	    /*	unsigned int opt=1;
		keylistner:
		switch(getch())
		{
			case 'w':
				  if(opt>4)
					break;
				  opt++;
				  break;
				  goto keylistneropt;
			case 's':
				  opt--;
			default:
				goto keylistner;
		}
		keylistneropt:
		switch(opt)
		{
			case 1 :
			case 2 :
			case 3 :
			case 4 :
			      setcolor(BLACK);
			      rectangle(245,140,350,180);
			      exitwindow();
			default:
				goto keylistner;
		}*/
//--------------------method2-----------------------
	 keylog:
	 setcolor(YELLOW);
	 rectangle(245,140,350,180);
	 rectangle(245,190,350,230);
	 rectangle(245,240,439,280);
	 rectangle(245,290,350,330);
	 int m=0,n=0;
	 showM();
	 do{
		getMxy();
		gotoxy(18,14);
		if(click==1)
		{
		      hideM();
		      m=px;
		      n=py;
		      showM();
		      break;
		}
	}while(!kbhit());
		if(m>245 && n>140 && m<350 && n<180)
		{
			 setcolor(BLACK);
			 rectangle(245,140,350,180);
			 box();
			 basic();
			 goto keylog;
		}
		else if(m>245 && n>190 && m<350 && n<230)
		{
			setcolor(BLACK);
			rectangle(245,190,350,230);
			 help(0);
			goto keylog;
		}
		else if(m>245 && n>240 && m<439 && n<280)
		{
			setcolor(BLACK);
			rectangle(245,240,439,280);
			credits();
			goto keylog;
		}
		else if(m>245 && n>290 && m<350 && n<330)
		{
			      setcolor(BLACK);
			      hideM();
			      rectangle(245,290,350,330);
			      exitwindow();
		}	      goto keylog;
		//else
		  //	goto keylog;

	//exitwindow();
       //	getch();
}
void exitwindow()
{
	int exwinx=100,exwiny=220,exwinx2=550,exwiny2=220;
	int exwin2x=100,exwin2y=220,exwin2x2=550,exwin2y2=220;

	for(int i=0;i<100;i++){
	setcolor(BLACK);
	line(exwinx,exwiny--,exwinx2,exwiny2--);
	delay(3);
	line(exwin2x,exwin2y++,exwin2x2,exwin2y2++);
	}
	exwinx=110,exwiny=220,exwinx2=540,exwiny2=220;
	exwin2x=110,exwin2y=220,exwin2x2=540,exwin2y2=220;

	for(i=0;i<90;i++){
	setcolor(YELLOW);
	line(exwinx,exwiny--,exwinx2,exwiny2--);
	delay(2);
	line(exwin2x,exwin2y++,exwin2x2,exwin2y2++);
	}
	setcolor(BLACK);
	settextstyle(0,0,2);
	outtextxy(200,150,"  ARE YOU SURE");
	outtextxy(200,170,"YOU WANT TO EXIT");
	setcolor(BLACK);

	outtextxy(130,280,"YES");

	outtextxy(480,280,"NO");
	settextstyle(0,0,1);
	setcolor(RED);
	outtextxy(150,200,"CAUTION: (All Current Progress Will Be Lost)");
	opt:
	setcolor(YELLOW);
	rectangle(120,275,180,300);
	rectangle(470,275,520,300);
	switch(getch()){
		case 'y':
			setcolor(BLACK);
			rectangle(120,275,180,300);
			if(getch()==13){
			hideM();
			exit(0);}
			goto opt;
		case 'n':
			setcolor(BLACK);
			rectangle(470,275,520,300);
			if(getch()==13){
			startmenu();}
			goto opt;
		case '1':
			setcolor(BLACK);
			rectangle(120,275,180,300);
			if(getch()==13){
			hideM();
			exit(0);}
			goto opt;
		case '2':
			setcolor(BLACK);
			rectangle(470,275,520,300);
			if(getch()==13){
			startmenu();}
			goto opt;
		default:
			exitwindow();
	}
}

void credits()
{
	int exwinx=70,exwiny=220,exwinx2=600,exwiny2=220;
	int exwin2x=70,exwin2y=220,exwin2x2=600,exwin2y2=220;

	for(int i=0;i<200;i++){
	setcolor(BLACK);
	line(exwinx,exwiny--,exwinx2,exwiny2--);
	delay(3);
	line(exwin2x,exwin2y++,exwin2x2,exwin2y2++);
	}
	exwinx=80,exwiny=220,exwinx2=590,exwiny2=220;
	exwin2x=80,exwin2y=220,exwin2x2=590,exwin2y2=220;



	/* ghosting	rectangle( x1, y1, x2, y2 );
	rectangle( 5+x2, y1, 639, y2 );
	setfillstyle(1,BROWN);
	floodfill(x1+15,y1+5,WHITE);
	//setfillstyle(7,RED);
      //	floodfill(x1+15,y1+5,WHITE);
	int winx=200,winy=220,winx2=450,winy2=220;
	int win2x=200,win2y=220,win2x2=450,win2y2=220;
	for(int i=0;i<150;i++){
	setcolor(8);
	line(winx,winy--,winx2,winy2--);
	delay(3);
	line(win2x,win2y++,win2x2,win2y2++);
	}
	winx=240,winy=220,winx2=440,winy2=220;
	win2x=240,win2y=220,win2x2=440,win2y2=220;
	for(i=0;i<140;i++){
	setcolor(YELLOW);
	line(winx,winy--,winx2,winy2--);
	delay(2);
	line(win2x,win2y++,win2x2,win2y2++);
	} */



	for(i=0;i<190;i++){
	setcolor(YELLOW);
	line(exwinx,exwiny--,exwinx2,exwiny2--);
	delay(2);
	line(exwin2x,exwin2y++,exwin2x2,exwin2y2++);
	}
	setcolor(BLACK);
	settextstyle(0,0,4);
	outtextxy(120,40,".::CREATORS::.");
	settextstyle(0,0,2);
	outtextxy(200,100,"DISHANT RATHI");
	outtextxy(200,150,"BCA 2rd Year");
	outtextxy(200,200,"ARYAN COLLEGE, AJMER");
	getch();
	startmenu();
}


void help(int call=1)
{
	hideM();
	int exwinx=70,exwiny=220,exwinx2=600,exwiny2=220;
	int exwin2x=70,exwin2y=220,exwin2x2=600,exwin2y2=220;

	for(int i=0;i<200;i++){
	setcolor(BLACK);
	line(exwinx,exwiny--,exwinx2,exwiny2--);
	delay(3);
	line(exwin2x,exwin2y++,exwin2x2,exwin2y2++);
	}
	exwinx=80,exwiny=220,exwinx2=590,exwiny2=220;
	exwin2x=80,exwin2y=220,exwin2x2=590,exwin2y2=220;

	for(i=0;i<190;i++){
	setcolor(YELLOW);
	line(exwinx,exwiny--,exwinx2,exwiny2--);
	delay(2);
	line(exwin2x,exwin2y++,exwin2x2,exwin2y2++);
	}
	setcolor(BLACK);
	settextstyle(0,0,4);
	outtextxy(120,40,"_.::HELP::._");

	settextstyle(0,0,1);

	outtextxy(358,112,"can move 1 square in any ");
	outtextxy(358,122,"direction");

	outtextxy(358,157,"can move forward backward, ");
	outtextxy(358,167,"or diagonally any amount of");
	outtextxy(358,177,"squares.");

	outtextxy(358,212,"can move diagonally any  ");
	outtextxy(358,222,"amount of squares.");

	outtextxy(358,257,"can move up 2 and over 1 or");
	outtextxy(358,267,"over 1 and up 2 in any");
	outtextxy(358,277,"direction");

	outtextxy(358,312,"can move forward or backward");
	outtextxy(358,322,"any amount of squares");

	outtextxy(358,347,"on first move, can move ");
	outtextxy(358,357,"forward 2 squares. On all ");
	outtextxy(358,367,"other moves, can forward 1 ");
	outtextxy(358,377,"square. Can only capture ");
	outtextxy(358,387,"pieces diagonally.");

	settextstyle(0,0,2);
	outtextxy(120,113,"      KING");
	outtextxy(120,163,"      QUEEN");
	outtextxy(120,213,"      BISHOP");
	outtextxy(120,263,"      KNIGHT");
	outtextxy(120,313,"      ROOK");
	outtextxy(120,363,"      PAWN");

	raja(130,120,0,15);
	rani(130,170,0,15);
	vajir(130,220,0,15);
	horseB(130,270,0,15);
	hathi(130,320,0,15);
	pyada(130,370,0,15);


	getch();
	if(call==0)
	startmenu();
	else{
		showM();
		basic();
	}
}

void exitmain()
{
	int exwinx=100,exwiny=220,exwinx2=550,exwiny2=220;
	int exwin2x=100,exwin2y=220,exwin2x2=550,exwin2y2=220;

	for(int i=0;i<100;i++){
	setcolor(BLACK);
	line(exwinx,exwiny--,exwinx2,exwiny2--);
	delay(3);
	line(exwin2x,exwin2y++,exwin2x2,exwin2y2++);
	}
	exwinx=110,exwiny=220,exwinx2=540,exwiny2=220;
	exwin2x=110,exwin2y=220,exwin2x2=540,exwin2y2=220;

	for(i=0;i<90;i++){
	setcolor(YELLOW);
	line(exwinx,exwiny--,exwinx2,exwiny2--);
	delay(2);
	line(exwin2x,exwin2y++,exwin2x2,exwin2y2++);
	}
	setcolor(BLACK);
	settextstyle(0,0,2);
	outtextxy(200,150,"  ARE YOU SURE");
	outtextxy(200,170,"YOU WANT TO EXIT");
	setcolor(BLACK);

	outtextxy(130,280,"YES");

	outtextxy(480,280,"NO");
	settextstyle(0,0,1);
	setcolor(RED);
	outtextxy(150,200,"CAUTION: (All Current Progress Will Be Lost)");
	opt:
	setcolor(YELLOW);
	rectangle(120,275,180,300);
	rectangle(470,275,520,300);
	switch(getch()){
		case 'y':
			setcolor(BLACK);
			rectangle(120,275,180,300);
			if(getch()==13){
			hideM();
			exit(0);}
			goto opt;
		case 'n':
			setcolor(BLACK);
			rectangle(470,275,520,300);
			if(getch()==13){
			cleardevice();
			basic();
			}
			goto opt;
		case '1':
			setcolor(BLACK);
			rectangle(120,275,180,300);
			if(getch()==13){
			hideM();
			exit(0);}
			goto opt;
		case '2':
			setcolor(BLACK);
			rectangle(470,275,520,300);
			if(getch()==13){
			cleardevice();
			basic();}
			goto opt;
		default:
			exitmain();
	}
}


/*-------------------------------------------------------------------------*/
/*=========================================================================*/


void BoardwithPiece(){
	int i,j;
	for( i = 0; i < 8; i++ ){
		for( j = 0; j < 8; j++ ){
			hideM();
			DrawAgain( i, j );
			showM();
		}
	}
}

void interface(){

	settextstyle( 0,1,2 );
	setcolor( 15 );
	outtextxy( 20, 70, "C    H    E    S    S");
	setcolor( DARKGRAY );

	int x1=25, y1=6, x2=489, y2=472;
	int gap=(y2-y1)/8;
	int inc=(gap+gap);
	int tempx=x1+gap;
	int tempy=y1+gap;
	int i,j;



	rectangle( x1, y1, x2, y2 );
	setcolor( 15 );
	rectangle( 5+x2, y1, 635, y2 );
	//rectangle( 10+x2, 10+y1, 625, y1+50 );
	//settextstyle( 2, 0, 7 );
	//outtextxy( x2+15, y1+15, "EXIT" );
	setcolor( DARKGRAY );

	for( i = tempx; i <= x2-gap; i+=gap )
		line( i, y1, i, y2 );

	for( j = tempy; j <= y2-gap; j+=gap )
		line( x1, j, x2, j );

	tempx=x1+(gap/2);
	tempy=y1+(gap/2);


	setfillstyle( 1, BROWN );
	for( i = tempx; i <= (tempx+(gap*6)); i+=inc ){
		for( j = tempy; j <= (tempy+(gap*6)); j+=inc ){
			floodfill( i,j,DARKGRAY );
		}
	}
	tempx=x1+gap+(gap/2);
	tempy=y1+gap+(gap/2);

	for( i = tempx; i <= (tempx+(gap*6)); i+=inc ){
		for( j = tempy; j <= (tempy+(gap*6)); j+=inc ){
			floodfill( i,j,DARKGRAY);
		}
	}

	tempx=x1+(gap/2);
	tempy=y1+gap+(gap/2);
	setfillstyle( 1, YELLOW );

	for( i = tempx; i <= (tempx+(gap*6)); i+=inc ){
		for( j = tempy; j <= (tempy+(gap*6)); j+=inc ){
			floodfill( i,j,DARKGRAY);
		}
	}

	tempx=x1+gap+(gap/2);
	tempy=y1+(gap/2);

	for( i = tempx; i <= (tempx+(gap*6)); i+=inc ){
		for( j = tempy; j <= (tempy+(gap*6)); j+=inc ){
			floodfill( i,j,DARKGRAY);
		}
	}
	setcolor(15);
	setfillstyle(1,BROWN);
	rectangle(500,20,620,50);
	floodfill(501,21,WHITE);
	rectangle(500,70,620,100);
	floodfill(501,71,WHITE);
	rectangle(500,120,620,150);
	floodfill(501,121,WHITE);

	settextstyle(1,0,2);
	outtextxy(510,22,"RESTART");
	outtextxy(510,72,"HELP");
	outtextxy(510,122,"EXIT");

	setcolor( 15 );

	showM();
}

void DrawAgain( int x, int y ){

	if( plc[x][y] == '0' )
		return;
	else if( plc[x][y] >= 65 && plc[x][y] <= 72 )
		pyada( midX[x], midY[y], 0, 15 );
	else if( plc[x][y] >= 97 && plc[x][y] <= 104 )
		pyada( midX[x], midY[y], 15, 0 );
	else if( plc[x][y] == 'R' || plc[x][y] == 'Z' )
		hathi( midX[x], midY[y], 0, 15 );
	else if( plc[x][y] == 'S' || plc[x][y] == 'Y' )
		horseW( midX[x], midY[y], 0, 15 );
	else if( plc[x][y] == 'T' || plc[x][y] == 'X' )
		vajir( midX[x], midY[y], 0, 15 );
	else if( plc[x][y] == 'Q' )
		rani( midX[x], midY[y], 0, 15 );
	else if( plc[x][y] == 'K' )
		raja( midX[x], midY[y], 0, 15 );
	else if( plc[x][y] == 'r' || plc[x][y] == 'z' )
		hathi( midX[x], midY[y], 15, 0 );
	else if( plc[x][y] == 's' || plc[x][y] == 'y' )
		horseB( midX[x], midY[y], 15, 0 );
	else if( plc[x][y] == 't' || plc[x][y] == 'x' )
		vajir( midX[x], midY[y], 15, 0 );
	else if( plc[x][y] == 'q' )
		rani( midX[x], midY[y], 15, 0 );
	else if( plc[x][y] == 'k' )
		raja( midX[x], midY[y], 15, 0 );
}

void fillblock( int x, int y ){
	int resx = x % 2;
	int resy = y % 2;

	if( resx == 0 && resy == 0 ){
		setfillstyle( 1, BROWN );
		floodfill( midX[x], midY[y], DARKGRAY );
	}
	else if( resx == 1 && resy == 1 ){
		setfillstyle( 1, BROWN );
		floodfill( midX[x], midY[y], DARKGRAY );
	}
	else if( resx == 1 && resy == 0 ){
		setfillstyle( 1, YELLOW );
		floodfill( midX[x], midY[y], DARKGRAY );
	}
	else if( resx == 0 && resy == 1 ){
		setfillstyle( 1, YELLOW );
		floodfill( midX[x], midY[y], DARKGRAY );
	}
}



void checkblock( int * x, int * y, int p1, int p2 ){
	if( p1 > 25 && p1 < 83 ){
	       *(x) = 0;
		if( p2 > 6 && p2 < 64 )
		       *(y) = 0;
		else if( p2 > 64 && p2 < 122 )
		       *(y) = 1;
		else if( p2 > 122 && p2 < 180 )
		       *(y) = 2;
		else if( p2 > 180 && p2 < 238 )
		       *(y) = 3;
		else if( p2 > 238 && p2 < 296 )
		       *(y) = 4;
		else if( p2 > 296 && p2 < 354 )
		       *(y) = 5;
		else if( p2 > 354 && p2 < 412 )
		       *(y) = 6;
		else if( p2 > 412 && p2 < 472 )
		       *(y) = 7;
	}
	if( p1 > 83 && p1 < 141 ){
	       *(x) = 1;
		if( p2 > 6 && p2 < 64 )
		       *(y) = 0;
		else if( p2 > 64 && p2 < 122 )
		       *(y) = 1;
		else if( p2 > 122 && p2 < 180 )
		       *(y) = 2;
		else if( p2 > 180 && p2 < 238 )
		       *(y) = 3;
		else if( p2 > 238 && p2 < 296 )
		       *(y) = 4;
		else if( p2 > 296 && p2 < 354 )
		       *(y) = 5;
		else if( p2 > 354 && p2 < 412 )
		       *(y) = 6;
		else if( p2 > 412 && p2 < 472 )
		       *(y) = 7;
	}
	if( p1 > 141 && p1 < 199 ){
	       *(x) = 2;
		if( p2 > 6 && p2 < 64 )
		       *(y) = 0;
		else if( p2 > 64 && p2 < 122 )
		       *(y) = 1;
		else if( p2 > 122 && p2 < 180 )
		       *(y) = 2;
		else if( p2 > 180 && p2 < 238 )
		       *(y) = 3;
		else if( p2 > 238 && p2 < 296 )
		       *(y) = 4;
		else if( p2 > 296 && p2 < 354 )
		       *(y) = 5;
		else if( p2 > 354 && p2 < 412 )
		       *(y) = 6;
		else if( p2 > 412 && p2 < 472 )
		       *(y) = 7;
	}
	if( p1 > 199 && p1 < 257 ){
	       *(x) = 3;
		if( p2 > 6 && p2 < 64 )
		       *(y) = 0;
		else if( p2 > 64 && p2 < 122 )
		       *(y) = 1;
		else if( p2 > 122 && p2 < 180 )
		       *(y) = 2;
		else if( p2 > 180 && p2 < 238 )
		       *(y) = 3;
		else if( p2 > 238 && p2 < 296 )
		       *(y) = 4;
		else if( p2 > 296 && p2 < 354 )
		       *(y) = 5;
		else if( p2 > 354 && p2 < 412 )
		       *(y) = 6;
		else if( p2 > 412 && p2 < 472 )
		       *(y) = 7;
	}
	if( p1 > 257 && p1 < 315 ){
	       *(x) = 4;
		if( p2 > 6 && p2 < 64 )
		       *(y) = 0;
		else if( p2 > 64 && p2 < 122 )
		       *(y) = 1;
		else if( p2 > 122 && p2 < 180 )
		       *(y) = 2;
		else if( p2 > 180 && p2 < 238 )
		       *(y) = 3;
		else if( p2 > 238 && p2 < 296 )
		       *(y) = 4;
		else if( p2 > 296 && p2 < 354 )
		       *(y) = 5;
		else if( p2 > 354 && p2 < 412 )
		       *(y) = 6;
		else if( p2 > 412 && p2 < 472 )
		       *(y) = 7;
	}
	if( p1 > 315 && p1 < 373 ){
	       *(x) = 5;
		if( p2 > 6 && p2 < 64 )
		       *(y) = 0;
		else if( p2 > 64 && p2 < 122 )
		       *(y) = 1;
		else if( p2 > 122 && p2 < 180 )
		       *(y) = 2;
		else if( p2 > 180 && p2 < 238 )
		       *(y) = 3;
		else if( p2 > 238 && p2 < 296 )
		       *(y) = 4;
		else if( p2 > 296 && p2 < 354 )
		       *(y) = 5;
		else if( p2 > 354 && p2 < 412 )
		       *(y) = 6;
		else if( p2 > 412 && p2 < 472 )
		       *(y) = 7;
	}
	if( p1 > 373 && p1 < 431 ){
	       *(x) = 6;
		if( p2 > 6 && p2 < 64 )
		       *(y) = 0;
		else if( p2 > 64 && p2 < 122 )
		       *(y) = 1;
		else if( p2 > 122 && p2 < 180 )
		       *(y) = 2;
		else if( p2 > 180 && p2 < 238 )
		       *(y) = 3;
		else if( p2 > 238 && p2 < 296 )
		       *(y) = 4;
		else if( p2 > 296 && p2 < 354 )
		       *(y) = 5;
		else if( p2 > 354 && p2 < 412 )
		       *(y) = 6;
		else if( p2 > 412 && p2 < 472 )
		       *(y) = 7;
	}
	if( p1 > 431 && p1 < 489 ){
	       *(x) = 7;
		if( p2 > 6 && p2 < 64 )
		       *(y) = 0;
		else if( p2 > 64 && p2 < 122 )
		       *(y) = 1;
		else if( p2 > 122 && p2 < 180 )
		       *(y) = 2;
		else if( p2 > 180 && p2 < 238 )
		       *(y) = 3;
		else if( p2 > 238 && p2 < 296 )
		       *(y) = 4;
		else if( p2 > 296 && p2 < 354 )
		       *(y) = 5;
		else if( p2 > 354 && p2 < 412 )
		       *(y) = 6;
		else if( p2 > 412 && p2 < 472 )
		       *(y) = 7;
	}
	if( p1 > 499 && p1 < 621 && p2 > 121 && p2 < 151 )
		exitmain();

	if(p1 > 501  && p1 < 621 && p2 > 21 && p2 < 51 )
	{
		int dplc[8][8] = {
			{'r','a','0','0','0','0','A','R'},
			{'s','b','0','0','0','0','B','S'},
			{'t','c','0','0','0','0','C','T'},
			{'q','d','0','0','0','0','D','Q'},
			{'k','e','0','0','0','0','E','K'},
			{'x','f','0','0','0','0','F','X'},
			{'y','g','0','0','0','0','G','Y'},
			{'z','h','0','0','0','0','H','Z'}
		};

		for(int q1=0;q1<8;q1++)
		{
			for(int q2=0;q2<8;q2++)
			{
				plc[q1][q2]=dplc[q1][q2];
			}
			i[q1]='0';
			pb[q1]='0';
		}



		count=0;
		basic();

	}

	if(p1 > 501  && p1 < 621 && p2 > 71 && p2 < 101 )
	{
		help(1);
	}
}

void checkMateW( int x, int y ){
	int check[9] = {0};
	if( checkW( x, y ) )
		check[0]=1;
	if( checkW( x-1, y ) || ( plc[x-1][y] >= 65 && plc[x-1][y] <= 90 ))
		check[1]=1;
	if( checkW( x+1, y )|| ( plc[x+1][y] >= 65 && plc[x+1][y] <= 90 ))
		check[2]=1;
	 if( checkW( x, y+1 ) || ( plc[x][y+1] >= 65 && plc[x][y+1] <= 90 ))
		check[3]=1;
	 if( checkW( x, y-1 )|| ( plc[x][y-1] >= 65 && plc[x][y-1] <= 90 ))
		check[4]=1;
	 if( checkW( x+1, y+1 )|| ( plc[x+1][y+1] >= 65 && plc[x+1][y+1] <= 90 ))
		check[5]=1;
	 if( checkW( x+1, y-1 )|| ( plc[x+1][y-1] >= 65 && plc[x+1][y-1] <= 90 ))
		check[6]=1;
	 if( checkW( x-1, y+1 )|| ( plc[x-1][y+1] >= 65 && plc[x-1][y+1] <= 90 ))
		check[7]=1;
	 if( checkW( x-1, y-1 )|| ( plc[x-1][y-1] >= 65 && plc[x-1][y-1] <= 90 ))
		check[8]=1;

	 int cnt=0;
	 for( int i = 0; i < 9; i++ ){
		if( check[i] == 1)
			cnt++;
	 }
	 if( cnt == 9  ){
		outtextxy( 500, 300, "CheckMate");
		outtextxy( 500, 400, "Player 1 win");
		getch();
		exit(0);
	 }

}
void checkMateB( int x, int y ){
	int check[9] = {0};
	if( checkB( x, y ) )
		check[0]=1;
	if( checkB( x-1, y )|| ( plc[x-1][y] >= 97 && plc[x-1][y] <= 122 ) )
		check[1]=1;
	if( checkB( x+1, y ) || ( plc[x+1][y] >= 97 && plc[x+1][y] <= 122 ) )
		check[2]=1;
	 if( checkB( x, y+1 )|| ( plc[x][y+1] >= 97 && plc[x][y+1] <= 122 ) )
		check[3]=1;
	 if( checkB( x, y-1 )|| ( plc[x][y-1] >= 97 && plc[x][y-1] <= 122 ) )
		check[4]=1;
	 if( checkB( x+1, y+1 )|| ( plc[x+1][y+1] >= 97 && plc[x+1][y+1] <= 122 ) )
		check[5]=1;
	 if( checkB( x+1, y-1 )|| ( plc[x+1][y-1] >= 97 && plc[x+1][y-1] <= 122 ) )
		check[6]=1;
	 if( checkB( x-1, y+1 )|| ( plc[x-1][y+1] >= 97 && plc[x-1][y+1] <= 122 ) )
		check[7]=1;
	 if( checkB( x-1, y-1 )|| ( plc[x-1][y-1] >= 97 && plc[x-1][y-1] <= 122 ) )
		check[8]=1;

	 int cnt=0;
	 for( int i = 0; i < 9; i++ ){
		if( check[i] == 1)
			cnt++;
	 }
	 if( cnt == 9  ){
		outtextxy( 500, 300, "CheckMate");
		outtextxy( 500, 400, "Player 2");
		getch();
		exit(0);
	 }

}
void checkKingW( int x, int y ){
	if( y+1 <= 7 ){
		if( plc[x][y+1] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x],midY[y+1], DARKGRAY );
		}
			if( checkW( x, y+1 ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x], midY[y+1], DARKGRAY );
				DrawAgain( x, y+1 );
			}
		else if( plc[x][y+1] >= 97 && plc[x][y+1] <= 122 ){
				setfillstyle( 1, RED );
				floodfill( midX[x], midY[y+1], DARKGRAY );
				DrawAgain( x, y+1 );
		}
	}
	if( y-1 >= 0 ){
		if( plc[x][y-1] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x], midY[y-1], DARKGRAY );
		}
			if( checkW( x, y-1 )  ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x], midY[y-1], DARKGRAY );
				DrawAgain( x, y-1 );
			}
		else if( plc[x][y-1] >= 97 && plc[x][y-1] <= 122 ){
				setfillstyle( 1, RED );
				floodfill( midX[x], midY[y-1], DARKGRAY );
				DrawAgain( x, y-1 );
		}
	}
	if( x-1 >= 0 ){
		if( plc[x-1][y] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x-1], midY[y], DARKGRAY );
		}
			if( checkW( x-1, y ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x-1], midY[y], DARKGRAY );
				DrawAgain( x-1, y );
			}
		else if( plc[x-1][y] >= 97 && plc[x-1][y] <= 122 ){
				setfillstyle( 1, RED );
				floodfill( midX[x-1], midY[y], DARKGRAY );
				DrawAgain( x-1, y );
		}
	}
	if( x+1 <= 7 ){
		if( plc[x+1][y] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x+1], midY[y], DARKGRAY );
		}
			if( checkW( x+1, y ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x+1], midY[y], DARKGRAY );
				DrawAgain( x+1, y );
			}
		else if( plc[x+1][y] >= 97 && plc[x+1][y] <= 122 ){
				setfillstyle( 1, RED );
				floodfill( midX[x+1], midY[y], DARKGRAY );
				DrawAgain( x+1, y );
		}
	}
	if( x+1 <= 7 && y+1 <= 7 ){
		if( plc[x+1][y+1] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x+1], midY[y+1], DARKGRAY );
		}
			if( checkW( x+1, y+1 ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x+1], midY[y+1], DARKGRAY );
				DrawAgain( x+1, y+1 );
			}
		else if( plc[x+1][y+1] >= 97 && plc[x+1][y+1] <= 122 ){
				setfillstyle( 1, RED );
				floodfill( midX[x+1], midY[y+1], DARKGRAY );
				DrawAgain( x+1, y+1 );
		}
	}
	if( x+1 <= 7 && y-1 >= 0 ){
		if( plc[x+1][y-1] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x+1], midY[y-1], DARKGRAY );
		}
			if( checkW( x+1, y-1 ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x+1], midY[y-1], DARKGRAY );
				DrawAgain( x+1, y-1 );
			}
		else if( plc[x+1][y-1] >= 97 && plc[x+1][y-1] <= 122 ){
				setfillstyle( 1, RED );
				floodfill( midX[x+1], midY[y-1], DARKGRAY );
				DrawAgain( x+1, y-1 );
		}
	}
	if( x-1 >= 0 && y+1 <= 7 ){
		if( plc[x-1][y+1] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x-1], midY[y+1], DARKGRAY );
		}
			if( checkW( x-1, y+1 ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x-1], midY[y+1], DARKGRAY );
				DrawAgain( x-1, y+1 );
			}
		else if( plc[x-1][y+1] >= 97 && plc[x-1][y+1] <= 122 ){
				setfillstyle( 1, RED );
				floodfill( midX[x-1], midY[y+1], DARKGRAY );
				DrawAgain( x-1, y+1 );
		}
	}
	if( x-1 >= 0 && y-1 >= 0 ){
		if( plc[x-1][y-1] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x-1], midY[y-1], DARKGRAY );
		}
		if( checkW( x-1, y-1 ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x-1], midY[y-1], DARKGRAY );
				DrawAgain( x-1, y-1 );
		}
		else if( plc[x-1][y-1] >= 97 && plc[x-1][y-1] <= 122 ){
				setfillstyle( 1, RED );
				floodfill( midX[x-1], midY[y-1], DARKGRAY );
				DrawAgain( x-1, y-1 );
		}
	}
	if( x >= 0 && y <= 7  && y >= 0 && x <= 7 ){
		if( plc[x][y] == 'K' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		if( checkW( x, y ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x], midY[y], DARKGRAY );
				DrawAgain( x, y );
			}
		else if( plc[x][y] >= 97 && plc[x][y] <= 122 ){
				setfillstyle( 1, RED );
				floodfill( midX[x], midY[y], DARKGRAY );
				DrawAgain( x, y );
		}
	}
}
void checkKingB( int x, int y ){
	if( y+1 <= 7 ){
		if( plc[x][y+1] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x],midY[y+1], DARKGRAY );
		}
			if( checkB( x, y+1 ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x], midY[y+1], DARKGRAY );
				DrawAgain( x, y+1 );
			}
		else if( plc[x][y+1] >= 65 && plc[x][y+1] <= 90 ){
				setfillstyle( 1, RED );
				floodfill( midX[x], midY[y+1], DARKGRAY );
				DrawAgain( x, y+1 );
		}
	}
	if( y-1 >= 0 ){
		if( plc[x][y-1] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x], midY[y-1], DARKGRAY );
		}
			if( checkB( x, y-1 )  ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x], midY[y-1], DARKGRAY );
				DrawAgain( x, y-1 );
			}
		else if( plc[x][y-1] >= 65 && plc[x][y-1] <= 90 ){
				setfillstyle( 1, RED );
				floodfill( midX[x], midY[y-1], DARKGRAY );
				DrawAgain( x, y-1 );
		}
	}
	if( x-1 >= 0 ){
		if( plc[x-1][y] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x-1], midY[y], DARKGRAY );
		}
			if( checkB( x-1, y ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x-1], midY[y], DARKGRAY );
				DrawAgain( x-1, y );
			}
		else if( plc[x-1][y] >= 65 && plc[x-1][y] <= 90 ){
				setfillstyle( 1, RED );
				floodfill( midX[x-1], midY[y], DARKGRAY );
				DrawAgain( x-1, y );
		}
	}
	if( x+1 <= 7 ){
		if( plc[x+1][y] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x+1], midY[y], DARKGRAY );
		}
			if( checkB( x+1, y ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x+1], midY[y], DARKGRAY );
				DrawAgain( x+1, y );
			}
		else if( plc[x+1][y] >= 65 && plc[x+1][y] <= 90 ){
				setfillstyle( 1, RED );
				floodfill( midX[x+1], midY[y], DARKGRAY );
				DrawAgain( x+1, y );
		}
	}
	if( x+1 <= 7 && y+1 <= 7 ){
		if( plc[x+1][y+1] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x+1], midY[y+1], DARKGRAY );
		}
			if( checkB( x+1, y+1 ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x+1], midY[y+1], DARKGRAY );
				DrawAgain( x+1, y+1 );
			}
		else if( plc[x+1][y+1] >= 65 && plc[x+1][y+1] <= 90 ){
				setfillstyle( 1, RED );
				floodfill( midX[x+1], midY[y+1], DARKGRAY );
				DrawAgain( x+1, y+1 );
		}
	}
	if( x+1 <= 7 && y-1 >= 0 ){
		if( plc[x+1][y-1] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x+1], midY[y-1], DARKGRAY );
		}
			if( checkB( x+1, y-1 ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x+1], midY[y-1], DARKGRAY );
				DrawAgain( x+1, y-1 );
			}
		else if( plc[x+1][y-1] >= 65 && plc[x+1][y-1] <= 90 ){
				setfillstyle( 1, RED );
				floodfill( midX[x+1], midY[y-1], DARKGRAY );
				DrawAgain( x+1, y-1 );
		}
	}
	if( x-1 >= 0 && y+1 <= 7 ){
		if( plc[x-1][y+1] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x-1], midY[y+1], DARKGRAY );
		}
			if( checkB( x-1, y+1 ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x-1], midY[y+1], DARKGRAY );
				DrawAgain( x-1, y+1 );
			}
		else if( plc[x-1][y+1] >= 65 && plc[x-1][y+1] <= 90 ){
				setfillstyle( 1, RED );
				floodfill( midX[x-1], midY[y+1], DARKGRAY );
				DrawAgain( x-1, y+1 );
		}
	}
	if( x-1 >= 0 && y-1 >= 0 ){
		if( plc[x-1][y-1] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x-1], midY[y-1], DARKGRAY );
		}
		if( checkB( x-1, y-1 ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x-1], midY[y-1], DARKGRAY );
				DrawAgain( x-1, y-1 );
		}
		else if( plc[x-1][y-1] >= 65 && plc[x-1][y-1] <= 90 ){
				setfillstyle( 1, RED );
				floodfill( midX[x-1], midY[y-1], DARKGRAY );
				DrawAgain( x-1, y-1 );
		}
	}
	if( x >= 0 && y <= 7  && y >= 0 && x <= 7 ){
		if( plc[x][y] == 'k' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		if( checkB( x, y ) ){
				setfillstyle( 1, LIGHTRED );
				floodfill( midX[x], midY[y], DARKGRAY );
				DrawAgain( x, y );
			}
		else if( plc[x][y] >= 65 && plc[x][y] <= 90 ){
				setfillstyle( 1, RED );
				floodfill( midX[x], midY[y], DARKGRAY );
				DrawAgain( x, y );
		}
	}
}

int checkW( int x, int y ){
	int tx=x,ty=y;
	y=ty;

	if( plc[x][y] >= 65  && plc[x][y] <= 90 && plc[x][y] != 'K' )
		return 0;

	if( plc[x][y] >= 97 && plc[x][y] <= 122 ){
		char ch = plc[x][y];
		plc[x][y] = '0';
		int res = checkW( x, y );
		plc[x][y] = ch;
		return res;
	}


	while( plc[x][y] == '0' || plc[x][y] == 'K' ) y--;
	if( y >= 0 && y <= 7 && (plc[x][y] == 'r' || plc[x][y] == 'z' || plc[x][y] == 'q' ))
		return 1;


	y=ty;
	while( plc[x][y] == '0' || plc[x][y] == 'K' ) y++;
	if( y >= 0 && y <= 7 && (plc[x][y] == 'r' || plc[x][y] == 'z' || plc[x][y] == 'q' ))
	 return 1;


	y=ty;
	x=tx;
	while( plc[x][y] == '0' || plc[x][y] == 'K') x--;
	if( x >= 0 && x <= 7 && (plc[x][y] == 'r' || plc[x][y] == 'z' || plc[x][y] == 'q' ))
		return 1;

	x=tx;
	while( plc[x][y] == '0' || plc[x][y] == 'K') x++;
	if( x >= 0 && x <= 7 &&(plc[x][y] == 'r' || plc[x][y] == 'z' || plc[x][y] == 'q' ))
		return 1;


	x=tx;
	y=ty;
	while( plc[x][y] == '0' || plc[x][y] == 'K'){ x++;	y++; }
	if( y >= 0 && y <= 7 &&x >= 0 && x <= 7 &&(plc[x][y] == 't' || plc[x][y] == 'x' || plc[x][y] == 'q' ))
		return 1;


	x=tx;
	y=ty;
	while( plc[x][y] == '0' || plc[x][y] == 'K'){ x--;	y--; }
	if( x >= 0 && x <= 7 &&y >= 0 && y <= 7 &&(plc[x][y] == 't' || plc[x][y] == 'x' || plc[x][y] == 'q' ))
		return 1;


	x=tx;
	y=ty;
	while( plc[x][y] == '0' || plc[x][y] == 'K'){ x++;	y--; }
	if( x >= 0 && x <= 7 &&y >= 0 && y <= 7 &&(plc[x][y] == 't' || plc[x][y] == 'x' || plc[x][y] == 'q' ))
		return 1;


	x=tx;
	y=ty;
	while( plc[x][y] == '0' || plc[x][y] == 'K'){ x--;	y++; }
	if( x >= 0 && x <= 7 &&y >= 0 && y <= 7 && ( plc[x][y] == 't' || plc[x][y] == 'x' || plc[x][y] == 'q') )
		return 1;


	x=tx;		y=ty;


	if( (y+1<=7 && plc[x][y+1] == 'k' )||( x-1 >= 0 && plc[x-1][y] == 'k' )|| ( x+1 <= 7 && plc[x+1][y] == 'k' )||( y-1 >= 0 && plc[x][y-1] == 'k') )
		return 1;


	if(x-1 >= 0 && y-1 >= 0 &&(plc[x-1][y-1] == 'k' || ( plc[x-1][y-1] >= 97 && plc[x-1][y-1] <= 104 )))
		return 1;

	if(x+1 <= 7 && y+1 <= 7 && (plc[x+1][y+1] == 'k' || ( plc[x+1][y+1] >= 97 && plc[x+1][y+1] <= 104 )))
		return 1;

	if(x+1 <= 7 && y-1 >= 0 && (plc[x+1][y-1] == 'k' || ( plc[x+1][y-1] >= 97 && plc[x+1][y-1] <= 104 )))
		return 1;

	if( x-1 >= 0 && y+1 <= 7 && (plc[x-1][y+1] == 'k' || ( plc[x-1][y+1] >= 97 && plc[x-1][y+1] <= 104 )))
		return 1;


	y=ty-2;
	x=tx;
	if( ( x+1 <= 7 && ( plc[x+1][y] == 's' || plc[x+1][y] == 'y' )) || ( x-1 >= 0 && ( plc[x-1][y] == 's' || plc[x-1][y] == 'y' ))){
		if( y >= 0 )
		return 1;
	}


	y=ty+2;
	x=tx;
	if( y <= 7 && ( x+1 <= 7 && ( plc[x+1][y] == 's' || plc[x+1][y] == 'y' )) || ( x-1 >= 0 && ( plc[x-1][y] == 's' || plc[x-1][y] == 'y' ))){
		if( y <= 7 )
		return 1;
	}

	x=tx+2;
	y=ty;
	if( x <= 7 && ( y+1 <= 7 && ( plc[x][y+1] == 's' || plc[x][y+1] == 'y' )) || ( y-1 >= 0 && ( plc[x][y-1] == 's' || plc[x][y-1] == 'y' ))){
		if( x <= 7 )
		return 1;
	}

	x=tx-2;
	y=ty;
	if( x >= 0 && ( y+1 <= 7 && ( plc[x][y+1] == 's' || plc[x][y+1] == 'y' )) || ( y-1 >= 0 && ( plc[x][y-1] == 's' || plc[x][y-1] == 'y' ))){
		if( x >= 0 )
		return 1;
	}


	return 0;

}
int checkB( int x, int y ){
	int tx=x,ty=y;
	y=ty;

	if( plc[x][y] >= 97 && plc[x][y] <= 122 && plc[x][y] != 'k' )
		return 0;

	if( plc[x][y] >= 65 && plc[x][y] <= 90 ){
		char ch = plc[x][y];
		plc[x][y] = '0';
		int res = checkB( x, y );
		plc[x][y] = ch;
		return res;
	}

	while( plc[x][y] == '0' || plc[x][y] == 'k' ) y--;
	if( y >= 0 && y <= 7 && (plc[x][y] == 'R' || plc[x][y] == 'Z' || plc[x][y] == 'Q' ))
		return 1;


	y=ty;
	while( plc[x][y] == '0' || plc[x][y] == 'k' ) y++;
	if( y >= 0 && y <= 7 && (plc[x][y] == 'R' || plc[x][y] == 'Z' || plc[x][y] == 'Q' ))
	 return 1;


	y=ty;
	x=tx;
	while( plc[x][y] == '0' || plc[x][y] == 'k' ) x--;
	if( x >= 0 && x <= 7 && (plc[x][y] == 'R' || plc[x][y] == 'Z' || plc[x][y] == 'Q' ))
		return 1;

	x=tx;
	while( plc[x][y] == '0' || plc[x][y] == 'k' ) x++;
	if( x >= 0 && x <= 7 &&(plc[x][y] == 'R' || plc[x][y] == 'Z' || plc[x][y] == 'Q' ))
		return 1;


	x=tx;
	y=ty;
	while( plc[x][y] == '0' || plc[x][y] == 'k' ){ x++;	y++; }
	if( y >= 0 && y <= 7 &&x >= 0 && x <= 7 &&(plc[x][y] == 'T' || plc[x][y] == 'X' || plc[x][y] == 'Q' ))
		return 1;


	x=tx;
	y=ty;
	while( plc[x][y] == '0' || plc[x][y] == 'k' ){ x--;	y--; }
	if( x >= 0 && x <= 7 &&y >= 0 && y <= 7 &&(plc[x][y] == 'T' || plc[x][y] == 'X' || plc[x][y] == 'Q' ))
		return 1;


	x=tx;
	y=ty;
	while( plc[x][y] == '0' || plc[x][y] == 'k' ){ x++;	y--; }
	if( x >= 0 && x <= 7 &&y >= 0 && y <= 7 &&(plc[x][y] == 'T' || plc[x][y] == 'X' || plc[x][y] == 'Q' ))
		return 1;


	x=tx;
	y=ty;
	while( plc[x][y] == '0' || plc[x][y] == 'k' ){ x--;	y++; }
	if( x >= 0 && x <= 7 &&y >= 0 && y <= 7 && ( plc[x][y] == 'T' || plc[x][y] == 'X' || plc[x][y] == 'Q') )
		return 1;


	x=tx;		y=ty;


	if( (y+1<=7 && plc[x][y+1] == 'K' )||( x-1 >= 0 && plc[x-1][y] == 'K' )|| ( x+1 <= 7 && plc[x+1][y] == 'K' )||( y-1 >= 0 && plc[x][y-1] == 'K') )
		return 1;


	if(x-1 >= 0 && y-1 >= 0 &&(plc[x-1][y-1] == 'K' || ( plc[x-1][y-1] >= 65 && plc[x-1][y-1] <= 90 )))
		return 1;

	if(x+1 <= 7 && y+1 <= 7 && (plc[x+1][y+1] == 'K' || ( plc[x+1][y+1] >= 65 && plc[x+1][y+1] <= 90 )))
		return 1;

	if(x+1 <= 7 && y-1 >= 0 && (plc[x+1][y-1] == 'K' || ( plc[x+1][y-1] >= 65 && plc[x+1][y-1] <= 90 )))
		return 1;

	if( x-1 >= 0 && y+1 <= 7 && (plc[x-1][y+1] == 'K' || ( plc[x-1][y+1] >= 65 && plc[x-1][y+1] <= 90 )))
		return 1;


	y=ty-2;
	x=tx;
	if( y >= 0 && ( x+1 <= 7 && ( plc[x+1][y] == 'S' || plc[x+1][y] == 'Y' )) || ( x-1 >= 0 && ( plc[x-1][y] == 'S' || plc[x-1][y] == 'Y' ))){
		if( y >= 0 )
		return 1;
	}


	y=ty+2;
	x=tx;
	if( y <= 7 && ( x+1 <= 7 && ( plc[x+1][y] == 'S' || plc[x+1][y] == 'Y' )) || ( x-1 >= 0 && ( plc[x-1][y] == 'S' || plc[x-1][y] == 'Y' ))){
		if( y <= 7 )
		return 1;
	}


	x=tx+2;
	y=ty;
	if( x <= 7 && ( y+1 <= 7 && ( plc[x][y+1] == 'S' || plc[x][y+1] == 'Y' )) || ( y-1 >= 0 && ( plc[x][y-1] == 'S' || plc[x][y-1] == 'Y' ))){
		if( x<= 7 )
		return 1;

	}

	x=tx-2;
	y=ty;
	if( x >= 0 && ( y+1 <= 7 && ( plc[x][y+1] == 'S' || plc[x][y+1] == 'Y' )) || ( y-1 >= 0 && ( plc[x][y-1] == 'S' || plc[x][y-1] == 'Y' ))){
		if( x>= 0)
		return 1;
	}



	return 0;

}


void checkmoves( int x, int y, char ch ){

	hideM();
	if( ch >= 65 && ch <= 72 ){

		if( i[ch-65] == '0'&& plc[x][y-1] == '0' && plc[x][y-2] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x], midY[y--], DARKGRAY );
			floodfill( midX[x], midY[y--], DARKGRAY );
			floodfill( midX[x], midY[y], DARKGRAY );
			pyada( midX[x], midY[y+2], 0, 15 );

			if( plc[x+1][y+1] >= 97 && plc[x+1][y+1] <= 122 ){
				setfillstyle( 1, RED );
				floodfill( midX[x+1], midY[y+1], DARKGRAY );
				DrawAgain( x+1, y+1 );
			}
			if( plc[x-1][y+1] >= 97 && plc[x-1][y+1] <= 122 ){
				setfillstyle( 1, RED );
				floodfill( midX[x-1], midY[y+1], DARKGRAY );
				DrawAgain( x-1, y+1 );
			}
		}
		else{
			if( plc[x][y-1] == '0' && y-1 >= 0 ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x], midY[y], DARKGRAY );
				floodfill( midX[x], midY[y-1], DARKGRAY );
				pyada( midX[x], midY[y], 0, 15 );
			}
			if( plc[x-1][y-1] >= 97 && plc[x-1][y-1] <= 122 && x-1 >= 0 && y-1 >= 0 ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x], midY[y], DARKGRAY );
				pyada( midX[x], midY[y], 0, 15 );
				setfillstyle( 1, RED );
				floodfill( midX[x-1], midY[y-1], DARKGRAY );
				DrawAgain( x-1, y-1 );
			}
			if( plc[x+1][y-1] >= 97 && plc[x+1][y-1] <= 122 && x+1 >= 0 && y-1 >= 0 ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x], midY[y], DARKGRAY );
				pyada( midX[x], midY[y], 0, 15 );
				setfillstyle( 1, RED );
				floodfill( midX[x+1], midY[y-1], DARKGRAY );
				DrawAgain( x+1, y-1 );
			}
		}
	}
	else if( ch == 'S' || ch == 'Y' ){

		int tx=x, ty=y;
		setfillstyle( 1, GREEN );
		floodfill( midX[x], midY[y], DARKGRAY );
		horseW( midX[x], midY[y], 0, 15 );

		y-=2;
		if( (y+1) >= 1 && ( x+1 > 8 || ( x+1 >= 0 && x+1 <= 7 ))){
			if( plc[x+1][y] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x+1], midY[y], DARKGRAY );
			}
			else if( plc[x+1][y] >= 97 && plc[x+1][y] <= 122 ){
				setfillstyle( 1, RED );
				floodfill( midX[x+1], midY[y], DARKGRAY );
				DrawAgain( x+1, y );
			}
			if( plc[x-1][y] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x-1], midY[y], DARKGRAY );
			}
			else if( plc[x-1][y] >= 97 && plc[x-1][y] <= 122 && ( x-1 > 0 || ( x-1 >= 0  && x-1 <= 7))){
				setfillstyle( 1, RED );
				floodfill( midX[x-1], midY[y], DARKGRAY );
				DrawAgain( x-1, y );
			}
		}
		y=ty+2;
		if( (y-1) < 7 && ( x+1 > 8 || ( x+1 >= 0 && x+1 <= 7 )) ){
			if( plc[x+1][y] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x+1], midY[y], DARKGRAY );
			}
			else if( plc[x+1][y] >= 97 && plc[x+1][y] <= 122 ){
				setfillstyle( 1, RED );
				floodfill( midX[x+1], midY[y], DARKGRAY );
				DrawAgain( x+1, y );
			}
			if( plc[x-1][y] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x-1], midY[y], DARKGRAY );
			}
			else if( plc[x-1][y] >= 97 && plc[x-1][y] <= 122 && ( x-1 > 0 || ( x-1 >= 0  && x-1 <= 7)) ){
				setfillstyle( 1, RED );
				floodfill( midX[x-1], midY[y], DARKGRAY );
				DrawAgain( x-1, y );
			}
		}
		y=ty;
		x=tx-2;
		if( (x+1) >= 1 && ( y+1 > 8 || ( y+1 >= 0 && y+1 <= 7 ))){
			if( plc[x][y+1] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x], midY[y+1], DARKGRAY );
			}
			else if( plc[x][y+1] >= 97 && plc[x][y+1] <= 122 ){
				setfillstyle( 1, RED );
				floodfill( midX[x], midY[y+1], DARKGRAY );
				DrawAgain( x, y+1 );
			}
			if( plc[x][y-1] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x], midY[y-1], DARKGRAY );
			}
			else if(plc[x][y-1] >= 97 && plc[x][y-1] <= 122 && ( y-1 > 0 || ( y-1 >= 0  && y-1 <= 7))){
				setfillstyle( 1, RED );
				floodfill( midX[x], midY[y-1], DARKGRAY );
				DrawAgain( x, y-1 );
			}
		}
		y=ty;
		x=tx+2;
		if( (x-1) < 7 && ( y+1 > 8 || ( y+1 >= 0 && y+1 <= 7 ))){
			if( plc[x][y+1] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x], midY[y+1], DARKGRAY );
			}
			else if( plc[x][y+1] >= 97 && plc[x][y+1] <= 122 ){
				setfillstyle( 1, RED );
				floodfill( midX[x], midY[y+1], DARKGRAY );
				DrawAgain( x, y+1 );
			}
			if( plc[x][y-1] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x], midY[y-1], DARKGRAY );
			}
			else if( plc[x][y-1] >= 97 && plc[x][y-1] <= 122 && ( y-1 > 0 || ( y-1 >= 0  && y-1 <= 7))){
				setfillstyle( 1, RED );
				floodfill( midX[x], midY[y-1], DARKGRAY );
				DrawAgain( x, y-1 );
			}
		}

	}
	else if( ch == 'R' || ch == 'Z' ){

		int tx = x, ty = y;
		setfillstyle( 1, GREEN );
		floodfill( midX[x], midY[y], DARKGRAY );
		hathi( midX[x], midY[y--], 0, 15 );

		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && y >= 0 )
			floodfill( midX[x], midY[y--], DARKGRAY );

		if(  plc[x][y] >= 97 && plc[x][y] <= 122 && y >= 0 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}

		y=ty+1;
		x=tx;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && y < 8 )
			floodfill( midX[x], midY[y++], DARKGRAY );

		if( plc[x][y] >= 97 && plc[x][y] <= 122 && y < 8){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}

		x=tx-1;
		y=ty;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x >= 0 )
			floodfill( midX[x--], midY[y], DARKGRAY );

		if( x >= 0 && plc[x][y] >= 97 && plc[x][y] <= 122 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		x=tx+1;
		y=ty;

		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x < 8 )
			floodfill( midX[x++], midY[y], DARKGRAY );

		if(  plc[x][y] >= 97 && plc[x][y] <= 122 && x < 8){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}

	}
	else if( ch == 'Q' ){

		int tx = x, ty = y;
		setfillstyle( 1, GREEN );
		floodfill( midX[x], midY[y], DARKGRAY );
		rani( midX[x], midY[y--], 0, 15 );

		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && y >= 0 )
			floodfill( midX[x], midY[y--], DARKGRAY );

		if( y >= 0 && plc[x][y] >= 97 && plc[x][y] <= 122 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}

		y=ty+1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && y < 8 )
			floodfill( midX[x], midY[y++], DARKGRAY );

		if( y < 8  && plc[x][y] >= 97 && plc[x][y] <= 122 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}

		x--;
		y=ty;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x >= 0 )
			floodfill( midX[x--], midY[y], DARKGRAY );

		if( x >= 0 && plc[x][y] >= 97 && plc[x][y] <= 122 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		x=tx+1;
		y=ty;

		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x < 8 )
			floodfill( midX[x++], midY[y], DARKGRAY );

		if( x < 8 && plc[x][y] >= 97 && plc[x][y] <= 122 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		x=tx+1;
		y=ty+1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x < 8 && y < 8 )
			floodfill( midX[x++], midY[y++], DARKGRAY );

		if( x<8 && y<8 && plc[x][y] >= 97 && plc[x][y] <= 122 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		x=tx+1;
		y=ty-1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x < 8 && y >= 0 )
			floodfill( midX[x++], midY[y--], DARKGRAY );

		if( x<8 && y >=0 && plc[x][y] >= 97 && plc[x][y] <= 122 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		x=tx-1;
		y=ty-1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x >= 0 && y >= 0 )
			floodfill( midX[x--], midY[y--], DARKGRAY );

		if( x >=0  && y >= 0 && plc[x][y] >= 97 && plc[x][y] <= 122 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		x=tx-1;
		y=ty+1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x >= 0 && y < 8 )
			floodfill( midX[x--], midY[y++], DARKGRAY );

		if( x>=0 && y <8 && plc[x][y] >= 97 && plc[x][y] <= 122 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
	}
	else if( plc[x][y] == 'T' || plc[x][y] == 'X' ){

		int tx = x, ty = y;
		setfillstyle( 1, GREEN );
		floodfill( midX[x], midY[y], DARKGRAY );
		vajir( midX[x--], midY[y--], 0, 15 );

		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && y >= 0 && x >= 0 )
			floodfill( midX[x--], midY[y--], DARKGRAY );

		if( y >= 0 && x >= 0 && plc[x][y] >= 97 && plc[x][y] <= 122 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}

		y=ty+1;
		x=tx-1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && y < 8 && x >= 0 )
			floodfill( midX[x--], midY[y++], DARKGRAY );

		if( y < 8 && x>=0 && plc[x][y] >= 97 && plc[x][y] <= 122 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}

		x=tx+1;
		y=ty+1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x < 8 && y < 8 )
			floodfill( midX[x++], midY[y++], DARKGRAY );

		if( x < 8 && y < 8 && plc[x][y] >= 97 && plc[x][y] <= 122 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		x=tx+1;
		y=ty-1;

		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x < 8 && y >= 0 )
			floodfill( midX[x++], midY[y--], DARKGRAY );

		if( x < 8 && y >= 0 && plc[x][y] >= 97 && plc[x][y] <= 122 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
	}

	else if( ch >= 97 && ch <= 104 ){

		if( pb[ch-97] == '0' && plc[x][y+1] == '0' && plc[x][y+2] == '0' ){
			setfillstyle( 1, GREEN );
			floodfill( midX[x], midY[y], DARKGRAY );
			floodfill( midX[x], midY[y+1], DARKGRAY );
			floodfill( midX[x], midY[y+2], DARKGRAY );
			pyada( midX[x], midY[y], 15, 0 );

			if( plc[x+1][y+1] >= 65 && plc[x+1][y+1] <= 90 ){
				setfillstyle( 1, RED );
				floodfill( midX[x+1], midY[y+1], DARKGRAY );
				DrawAgain( x+1, y+1 );
			}
			if( plc[x-1][y+1] >= 65 && plc[x-1][y+1] <= 90 ){
				setfillstyle( 1, RED );
				floodfill( midX[x-1], midY[y+1], DARKGRAY );
				DrawAgain( x-1, y+1 );
			}

		}
		else{
			if( plc[x][y+1] == '0' && y+1 < 8){
				setfillstyle( 1, GREEN );
				floodfill( midX[x], midY[y], DARKGRAY );
				floodfill( midX[x], midY[y+1], DARKGRAY );
				pyada( midX[x], midY[y], 15, 0 );
			}
			if( plc[x+1][y+1] <= 90 && plc[x+1][y+1] >= 65 && x+1 < 8 && y+1 < 8 ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x], midY[y], DARKGRAY );
				pyada( midX[x], midY[y], 15, 0 );
				setfillstyle( 1, RED );
				floodfill( midX[x+1], midY[y+1], DARKGRAY );
				DrawAgain( x+1, y+1 );
			}
			if( plc[x-1][y+1] <= 90 && plc[x-1][y+1] >= 65 && x-1 < 8 && y+1 < 8 ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x], midY[y], DARKGRAY );
				pyada( midX[x], midY[y], 15, 0 );
				setfillstyle( 1, RED );
				floodfill( midX[x-1], midY[y+1], DARKGRAY );
				DrawAgain( x-1, y+1 );
			}
		}
	}
	else if( ch == 'r' || ch == 'z' ){

		int tx = x, ty = y;
		setfillstyle( 1, GREEN );
		floodfill( midX[x], midY[y], DARKGRAY );
		hathi( midX[x], midY[y], 15, 0 );

		y = ty-1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && y >= 0 )
			floodfill( midX[x], midY[y--], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90 && y >= 0 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}

		y=ty+1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && y < 8 )
			floodfill( midX[x], midY[y++], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90  && y < 8 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}

		x--;
		y=ty;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x >= 0 )
			floodfill( midX[x--], midY[y], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90 && x>=0  ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		x=tx+1;
		y=ty;

		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x < 8 )
			floodfill( midX[x++], midY[y], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90 && x<8 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}

	}
	else if( ch == 'q' ){
		int tx = x, ty = y;
		setfillstyle( 1, GREEN );
		floodfill( midX[x], midY[y], DARKGRAY );
		rani( midX[x], midY[y], 15, 0 );
		y=ty-1;

		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && y >= 0 )
			floodfill( midX[x], midY[y--], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90 && y>=0 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}

		y=ty+1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && y < 8 )
			floodfill( midX[x], midY[y++], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90 && y < 8 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}

		x--;
		y=ty;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x >= 0 )
			floodfill( midX[x--], midY[y], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90 && x >= 0 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		x=tx+1;
		y=ty;

		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x < 8 )
			floodfill( midX[x++], midY[y], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90 && x < 8 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		x=tx+1;
		y=ty+1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x < 8 && y < 8 )
			floodfill( midX[x++], midY[y++], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90 && x < 8 && y < 8  ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		x=tx+1;
		y=ty-1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x < 8 && y >= 0 )
			floodfill( midX[x++], midY[y--], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90 && x < 8 && y >= 0 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		x=tx-1;
		y=ty-1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x >= 0 && y >= 0 )
			floodfill( midX[x--], midY[y--], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90 && x >= 0 && y >= 0){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		x=tx-1;
		y=ty+1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x >= 0 && y < 8 )
			floodfill( midX[x--], midY[y++], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90 &&  x>= 0 && y < 8){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
	}
	else if( plc[x][y] == 't' || plc[x][y] == 'x' ){

		int tx = x, ty = y;
		setfillstyle( 1, GREEN );
		floodfill( midX[x], midY[y], DARKGRAY );
		vajir( midX[x--], midY[y--], 15, 0 );

		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && y >= 0 && x >= 0 )
			floodfill( midX[x--], midY[y--], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90 && x>=0 && y>= 0  ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}

		y=ty+1;
		x=tx-1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && y < 8 && x >= 0 )
			floodfill( midX[x--], midY[y++], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90 && x>=0 && y < 8  ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}

		x=tx+1;
		y=ty+1;
		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x < 8 && y < 8 )
			floodfill( midX[x++], midY[y++], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90 && x < 8 && y < 8 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
		x=tx+1;
		y=ty-1;

		setfillstyle( 1, GREEN );
		while( plc[x][y] == '0' && x < 8 && y >= 0 )
			floodfill( midX[x++], midY[y--], DARKGRAY );

		if( plc[x][y] >= 65 && plc[x][y] <= 90 && x < 8 && y >= 0 ){
			setfillstyle( 1, RED );
			floodfill( midX[x], midY[y], DARKGRAY );
			DrawAgain( x, y );
		}
	}
	else if( ch == 's' || ch == 'y' ){

		int tx=x, ty=y;
		setfillstyle( 1, GREEN );
		floodfill( midX[x], midY[y], DARKGRAY );
		horseB( midX[x], midY[y], 15, 0 );

		y-=2;
		if( (y+1) >= 1 && ( x+1 > 8 || ( x+1 >= 0 && x+1 <= 7 ))){
			if( plc[x+1][y] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x+1], midY[y], DARKGRAY );
			}
			else if( plc[x+1][y] >= 65 && plc[x+1][y] <= 90 ){
				setfillstyle( 1, RED );
				floodfill( midX[x+1], midY[y], DARKGRAY );
				DrawAgain( x+1, y );
			}
			if( plc[x-1][y] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x-1], midY[y], DARKGRAY );
			}
			else if( plc[x-1][y] >= 65 && plc[x-1][y] <= 90 && ( x-1 > 0 || ( x-1 >= 0  && x-1 <= 7))){
				setfillstyle( 1, RED );
				floodfill( midX[x-1], midY[y], DARKGRAY );
				DrawAgain( x-1, y );
			}
		}
		y=ty+2;
		if( (y-1) < 7 && ( x+1 > 8 || ( x+1 >= 0 && x+1 <= 7 ))){
			if( plc[x+1][y] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x+1], midY[y], DARKGRAY );
			}
			else if( plc[x+1][y] >= 65 && plc[x+1][y] <= 90 ){
				setfillstyle( 1, RED );
				floodfill( midX[x+1], midY[y], DARKGRAY );
				DrawAgain( x+1, y );
			}
			if( plc[x-1][y] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x-1], midY[y], DARKGRAY );
			}
			else if( plc[x-1][y] >= 65 && plc[x-1][y] <= 90 && ( x-1 > 0 || ( x-1 >= 0  && x-1 <= 7))){
				setfillstyle( 1, RED );
				floodfill( midX[x-1], midY[y], DARKGRAY );
				DrawAgain( x-1, y );
			}
		}
		y=ty;
		x=tx-2;
		if( (x+1) >= 1 && ( y+1 > 8 || ( y+1 >= 0 && y+1 <= 7 ))){
			if( plc[x][y+1] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x], midY[y+1], DARKGRAY );
			}
			else if( plc[x][y+1] >= 65 && plc[x][y+1] <= 90 ){
				setfillstyle( 1, RED );
				floodfill( midX[x], midY[y+1], DARKGRAY );
				DrawAgain( x, y+1 );
			}
			if( plc[x][y-1] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x], midY[y-1], DARKGRAY );
			}
			else if( plc[x][y-1] >= 65 && plc[x][y-1] <= 90 && ( y-1 > 0 || ( y-1 >= 0  && y-1 <= 7)) ){
				setfillstyle( 1, RED );
				floodfill( midX[x], midY[y-1], DARKGRAY );
				DrawAgain( x, y-1 );
			}
		}
		y=ty;
		x=tx+2;
		if( (x-1) < 7 && ( y+1 > 8 || ( y+1 >= 0  && y+1 <= 7)) ){
			if( plc[x][y+1] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x], midY[y+1], DARKGRAY );
			}
			else if( plc[x][y+1] >= 65 && plc[x][y+1] <= 90  ){
				setfillstyle( 1, RED );
				floodfill( midX[x], midY[y+1], DARKGRAY );
				DrawAgain( x, y+1 );
			}
			if( plc[x][y-1] == '0' ){
				setfillstyle( 1, GREEN );
				floodfill( midX[x], midY[y-1], DARKGRAY );
			}
			else if( plc[x][y-1] >= 65 && plc[x][y-1] <= 90 && ( y-1 > 0 || ( y-1 >= 0  && y-1 <= 7)) ){
				setfillstyle( 1, RED );
				floodfill( midX[x], midY[y-1], DARKGRAY );
				DrawAgain( x, y-1 );
			}
		}
	}
	else if( plc[x][y] == 'K' ){
		checkKingW( x, y );
	}
	else if( plc[x][y] == 'k' ){
		checkKingB( x, y );
	}
	showM();
}
int conForBlank( int x, int y, int x1, int y1, int tx, int ty ){

	if( x1 == x && y1 == y ){
		fillblock( x, y );
		plc[x1][y1] = plc[tx][ty];
		plc[tx][ty] = '0';
		count++;
		return 1;
	}
	return 0;
}
void conForOpponent( int x, int y, int x1, int y1, int tx, int ty ){
	if( plc[x][y] >= 97 && plc[x][y] <= 122 && x1 == x && y1 == y){
		fillblock( x, y );
		plc[x1][y1] = plc[tx][ty];
		plc[tx][ty] = '0';
		count++;
	}
}
void conForOpponent2( int x, int y, int x1, int y1, int tx, int ty ){
	if( plc[x][y] >= 65 && plc[x][y] <= 90 && x1 == x && y1 == y){
		fillblock( x, y );
		plc[x1][y1] = plc[tx][ty];
		plc[tx][ty] = '0';
		count++;
	}
}
void moveRaniB( int x, int y, int x1, int y1 ){
	int tx=x, ty=y;
	y--;
	while( plc[x][y] == '0' && y >= 0 ){
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );


	y=ty+1;
	while( plc[x][y] == '0' ){
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
	}

	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty;
	x=tx-1;
	while( plc[x][y] == '0' ) {
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;

		x--;
	}

	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty;
	x=tx+1;
	while( plc[x][y] == '0' ) {
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;

		x++;
	}

	conForOpponent2( x,y, x1, y1, tx, ty );

	y = ty-1;
	x = tx-1;
	while(  plc[x][y] == '0' && y >= 0 && x >= 0){
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		x--;		y--;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty+1;
	x=tx-1;
	while(  plc[x][y] == '0' && y < 8 && x >= 0 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
		x--;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty+1;
	x=tx+1;
	while(  plc[x][y] == '0' && y < 8 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
		x++;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty-1;
	x=tx+1;
	while(  plc[x][y] == '0'  && y >= 0 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
		x++;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );


}

void moveRaniW( int x, int y, int x1, int y1 ){
	int tx=x, ty=y;
	y--;
	while( plc[x][y] == '0' && y >= 0 ){
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
	}
	conForOpponent( x,y, x1, y1, tx, ty );


	y=ty+1;
	while( plc[x][y] == '0' ){
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
	}

	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty;
	x=tx-1;
	while( plc[x][y] == '0' ) {
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;

		x--;
	}

	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty;
	x=tx+1;
	while( plc[x][y] == '0' ) {
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;

		x++;
	}

	conForOpponent( x,y, x1, y1, tx, ty );

	y = ty-1;
	x = tx-1;
	while(  plc[x][y] == '0' && y >= 0 && x >= 0){
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		x--;		y--;
	}
	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty+1;
	x=tx-1;
	while(  plc[x][y] == '0' && y < 8 && x >= 0 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
		x--;
	}
	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty+1;
	x=tx+1;
	while(  plc[x][y] == '0' && y < 8 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
		x++;
	}
	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty-1;
	x=tx+1;
	while(  plc[x][y] == '0'  && y >= 0 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
		x++;
	}
	conForOpponent( x,y, x1, y1, tx, ty );


}
void moveHathiW( int x, int y, int x1, int y1 ){

	int tx=x, ty=y;
	y--;
	while( plc[x][y] == '0' && y >= 0 ){
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
	}
	conForOpponent( x,y, x1, y1, tx, ty );


	y=ty+1;
	while( plc[x][y] == '0' ){
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
	}

	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty;
	x=tx-1;
	while( plc[x][y] == '0' ) {
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;

		x--;
	}

	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty;
	x=tx+1;
	while( plc[x][y] == '0' ) {
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;

		x++;
	}

	conForOpponent( x,y, x1, y1, tx, ty );
}
void moveHathiB( int x, int y, int x1, int y1 ){

	int tx=x, ty=y;
	y--;
	while( plc[x][y] == '0' && y >= 0 ){
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );


	y=ty+1;
	while( plc[x][y] == '0' ){
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
	}

	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty;
	x=tx-1;
	while( plc[x][y] == '0' ) {
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;

		x--;
	}

	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty;
	x=tx+1;
	while( plc[x][y] == '0' ) {
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;

		x++;
	}

	conForOpponent2( x,y, x1, y1, tx, ty );
}


void moveVajirW( int x, int y, int x1, int y1 ){

	int tx=x, ty=y;
	y--;
	x--;
	while(  plc[x][y] == '0' && y >= 0 && x >= 0){
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		x--;		y--;
	}
	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty+1;
	x=tx-1;
	while(  plc[x][y] == '0' && y < 8 && x >= 0 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
		x--;
	}
	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty+1;
	x=tx+1;
	while(  plc[x][y] == '0' && y < 8 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
		x++;
	}
	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty-1;
	x=tx+1;
	while(  plc[x][y] == '0'  && y >= 0 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
		x++;
	}
	conForOpponent( x,y, x1, y1, tx, ty );

}
void moveVajirB( int x, int y, int x1, int y1 ){

	int tx=x, ty=y;
	y--;
	x--;
	while(  plc[x][y] == '0' && y >= 0 && x >= 0){
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		x--;		y--;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty+1;
	x=tx-1;
	while(  plc[x][y] == '0' && y < 8 && x >= 0 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
		x--;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty+1;
	x=tx+1;
	while(  plc[x][y] == '0' && y < 8 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
		x++;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty-1;
	x=tx+1;
	while(  plc[x][y] == '0'  && y >= 0 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
		x++;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );

}
void moveGhodaW(int x, int y, int x1, int y1)
{

	int tx=x, ty=y;
	y-=2;
	x--;
	while(  plc[x][y] == '0' && y >= 0 && x >= 0){
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		x--;		y--;
	}
	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty-2;
	x=tx+1;
	while(  plc[x][y] == '0' && y < 8 && x >= 0 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
		x--;
	}
	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty+2;
	x=tx+1;
	while(  plc[x][y] == '0' && y < 8 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
		x++;
	}
	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty+2;
	x=tx-1;
	while(  plc[x][y] == '0'  && y >= 0 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
		x++;
	}
	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty+1;
	x=tx-2;
	while(  plc[x][y] == '0' &&  y >= 0 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
		x++;
	}
	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty+1;
	x=tx+2;
	while(  plc[x][y] == '0' &&  y >= 0 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
		x++;
	}
	conForOpponent( x,y, x1, y1, tx, ty );


	y=ty-1;
	x=tx+2;
	while(  plc[x][y] == '0' &&  y >= 0 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
		x++;
	}
	conForOpponent( x,y, x1, y1, tx, ty );

	y=ty-1;
	x=tx-2;
	while(  plc[x][y] == '0' &&  y >= 0 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
		x++;
	}
	conForOpponent( x,y, x1, y1, tx, ty );

}
void moveGhodaB(int x, int y, int x1, int y1)
{
	int tx=x, ty=y;
	y-=2;
	x--;
	while(  plc[x][y] == '0' && y >= 0 && x >= 0){
		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		x--;		y--;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty-2;
	x=tx+1;
	while(  plc[x][y] == '0' && y < 8 && x >= 0 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
		x--;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty+2;
	x=tx+1;
	while(  plc[x][y] == '0' && y < 8 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y++;
		x++;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty+2;
	x=tx-1;
	while(  plc[x][y] == '0'  && y >= 0 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
		x++;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty+1;
	x=tx-2;
	while(  plc[x][y] == '0' &&  y >= 0 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
		x++;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty+1;
	x=tx+2;
	while(  plc[x][y] == '0' &&  y >= 0 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
		x++;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );


	y=ty-1;
	x=tx+2;
	while(  plc[x][y] == '0' &&  y >= 0 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
		x++;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );

	y=ty-1;
	x=tx-2;
	while(  plc[x][y] == '0' &&  y >= 0 && x < 8 ){

		if( conForBlank( x, y, x1, y1, tx, ty ))
			break;
		y--;
		x++;
	}
	conForOpponent2( x,y, x1, y1, tx, ty );

}

char opt(int a,int b)
{
	setfillstyle(1,BROWN);
	rectangle(510,200,620,450);
	rectangle(511,201,621,451);
	floodfill(555,222,15);

	rani(565,236,a,b);
	vajir(565,297,a,b);
	horseB(565,358,a,b);
	hathi(565,419,a,b);

	while(1){
		showM();
		getMxy();
		if( click == 1 ){
			if(px>536 && px<594 && py>210 && py<265)
			{
				if(a==0)
				{
					return 'Q';
				}
				return 'q';
			}
			else if(px>536 && px<594 && py>268 && py<326)
			{
				if(a==0)
				{
					return 'X';
				}
				return 'x';
			}
			else if(px>536 && px<594 && py>329 && py<387)
			{
				if(a==0)
				{
					return 'Y';
				}
				return 'y';
			}
			else if(px>536 && px<594 && py>390 && py<448)
			{
				if(a==0)
				{
					return 'Z';
				}
				return 'z';
			}
		}
	}

}

void movepyadaW( int x, int y, int x1, int y1, char ch ){

	if( i[ch-65] == '0' && x == x1 ){
		if( y-1 == y1 && plc[x1][y1] == '0' ){
			pyada( midX[x1], midY[y1], 0, 15 );
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			fillblock( x, y );
			i[ch-65] = '1';
			count++;
		}
		else if( y-2 == y1 && plc[x1][y1] == '0' ){
			pyada( midX[x1], midY[y1], 0, 15 );
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			fillblock( x, y );
			i[ch-65] = '1';
			count++;
		}
		else if( y-1 == y1 && ( x-1 == x1 || x+1 == x1 ) && ( plc[x1][y1] >= 97 && plc[x1][y1] <= 122 )){
			pyada( midX[x1], midY[y1], 0, 15 );
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			fillblock( x, y );
			i[ch-65] = '1';
			count++;
		}

	}
	else{
		if( y-1 == y1 && plc[x1][y1] == '0' && x == x1 ){
			fillblock( x1, y1 );
			pyada( midX[x1], midY[y1], 0, 15 );
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			fillblock( x, y );
			count++;
		}
		else if( y-1 == y1 && (x+1 == x1 || x-1 == x1) && ( plc[x1][y1] >= 97 && plc[x1][y1] <= 122 ) ){
			fillblock( x1, y1 );
			pyada( midX[x1], midY[y1], 0, 15 );
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			fillblock( x, y );
			count++;
		}
	}
	for(int i=0;i<8;i++)
	{
		if(plc[i][0]>=65 && plc[i][0]<=72)
		{
			plc[x1][y1]=opt(0,15);
			break;
		}
	}
}
void movepyadaB( int x, int y, int x1, int y1, char ch ){

	if( pb[ch-97] == '0' && x == x1 ){
		if( y+1 == y1 && plc[x1][y1] == '0' ){
			pyada( midX[x1], midY[y1], 15, 0 );
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			fillblock( x, y );
			pb[ch-97] = '1';
			count++;
		}
		else if( y+2 == y1 && plc[x1][y1] == '0' ){
			pyada( midX[x1], midY[y1], 15, 0 );
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			fillblock( x, y );
			pb[ch-97] = '1';
			count++;
		}
		else if( y-1 == y1 && ( x-1 == x1 || x+1 == x1 )  && ( plc[x1][y1] >= 65 && plc[x1][y1] <= 90 )){
			fillblock( x1, y1 );
			pyada( midX[x1], midY[y1], 15, 0 );
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			fillblock( x, y );
			pb[ch-97] = '1';
			count++;
		}
	}
	else{
		if( y+1 == y1 && plc[x1][y1] == '0' && x == x1 ){
			fillblock( x1, y1 );
			pyada( midX[x1], midY[y1], 15, 0 );
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			fillblock( x, y );
			count++;
		}
		else if( y+1 == y1 && (x+1 == x1 || x-1 == x1) && ( plc[x1][y1] >= 65 && plc[x1][y1] <= 90 ) ){
			fillblock( x1, y1 );
			pyada( midX[x1], midY[y1], 15, 0 );
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			fillblock( x, y );
			count++;
		}
	}
	for(int i=0;i<8;i++)
	{
		if(plc[i][7]>='a' && plc[i][7]<='h')
		{
			plc[x1][y1]=opt(15,0);
			break;
		}
	}
}
void moveRajaW( int x, int y, int x1, int y1 ){

	if( x+1 == x1 && y == y1 && x+1 <= 7 ){
		if( checkW( x+1, y ))
			return;
		else if( plc[x+1][y] == '0' || (plc[x+1][y] >= 97 && plc[x+1][y] <= 122) ){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}
	else if( x-1 == x1 && y == y1 && x-1 >= 0 ){
		if( checkW( x-1, y ))
			return;
		else if( plc[x-1][y] == '0' || ( plc[x-1][y] >= 97 && plc[x-1][y] <= 122)){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}
	else if( x == x1 && y-1 == y1 && y-1 >= 0){
		if( checkW( x, y-1 ))
			return;
		else if( plc[x][y-1] == '0' || (plc[x][y-1] >= 97 && plc[x][y-1] <= 122)){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}
	else if( x == x1 && y+1 == y1 && y+1 <= 7 ){
		if( checkW( x, y+1 ))
			return;
		else if( plc[x][y+1] == '0'|| (plc[x][y+1] >= 97 && plc[x][y+1] <= 122) ){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}
	else if( x-1 == x1 && y-1 == y1 && ( x-1 >= 0 && y-1 >= 0 )){
		if( checkW( x-1, y-1 ))
			return;
		else if( plc[x-1][y-1] == '0' || (plc[x-1][y-1] >= 97 && plc[x-1][y-1] <= 122) ){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}
	else if( x-1 == x1 && y+1 == y1&& ( x-1 >= 0 && y+1 <= 7 ) ){
		if( checkW( x-1, y+1 ))
			return;
		else if( plc[x-1][y+1] == '0' || (plc[x-1][y+1] >= 97 && plc[x-1][y+1] <= 122)){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}
	else if( x+1 == x1 && y+1 == y1 && ( x+1 <= 7 && y+1 <= 7 ) ){
		if( checkW( x+1, y+1 ))
			return;
		else if( plc[x+1][y+1] == '0' || (plc[x+1][y+1] >= 97 && plc[x+1][y+1] <= 122) ){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}
	else if( x+1 == x1 && y-1 == y1 && ( x+1 <= 7 && y-1 >= 0 ) ){
		if( checkW( x+1, y-1 ))
			return;
		else if( plc[x+1][y-1] == '0' || (plc[x+1][y-1] >= 97 && plc[x+1][y-1] <= 122)){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}

}
void moveRajaB( int x, int y, int x1, int y1 ){

	if( x+1 == x1 && y == y1&& x+1 <= 7 ){
		if( checkB( x+1, y ))
			return;
		else if( plc[x+1][y] == '0' || (plc[x+1][y] >= 65 && plc[x+1][y] <= 90) ){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}
	else if( x-1 == x1 && y == y1&& x-1 <= 0 ){
		if( checkB( x-1, y ))
			return;
		else if( plc[x-1][y] == '0' || (plc[x-1][y] >= 65 && plc[x-1][y] <= 90) ){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}
	else if( x == x1 && y-1 == y1 && y-1 >= 0 ){
		if( checkB( x, y-1 ))
			return;
		else if( plc[x][y-1] == '0' || (plc[x][y-1] >= 65 && plc[x][y-1] <= 90) ){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}
	else if( x == x1 && y+1 == y1 && y+1 <= 7 ){
		if( checkB( x, y+1 ))
			return;
		else if( plc[x][y+1] == '0' || (plc[x][y+1] >= 65 && plc[x][y+1] <= 90) ){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}
	else if( x-1 == x1 && y-1 == y1&& ( x-1 >= 0 && y-1 >= 0 ) ){
		if( checkB( x-1, y-1 ))
			return;
		else if( plc[x-1][y-1] == '0' || (plc[x-1][y-1] >= 65 && plc[x-1][y-1] <= 90) ){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}
	else if( x-1 == x1 && y+1 == y1 && ( x-1 >= 0 && y+1 <= 7 ) ){
		if( checkB( x-1, y+1 ))
			return;
		else if( plc[x-1][y+1] == '0' || (plc[x-1][y+1] >= 65 && plc[x-1][y+1] <= 90)){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}
	else if( x+1 == x1 && y+1 == y1 && ( x+1 <= 7 && y+1 <= 7 ) ){
		if( checkB( x+1, y+1 ))
			return;
		else if( plc[x+1][y+1] == '0'|| (plc[x+1][y+1] >= 65 && plc[x+1][y+1] <= 90) ){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}
	else if( x+1 == x1 && y-1 == y1 && ( x+1 <= 7 && y-1 >= 0 ) ){
		if( checkB( x+1, y-1 ))
			return;
		else if( plc[x+1][y-1] == '0' || (plc[x+1][y-1] >= 65 && plc[x+1][y-1] <= 90) ){
			plc[x1][y1] = plc[x][y];
			plc[x][y] = '0';
			count++;
		}
	}

}
void checkpiece( int x, int y, int x1, int y1, char ch ){
	if( ch == 'A' ){
		if( plc[x][y] >= 65 && plc[x][y] <= 72 )
			movepyadaW( x, y, x1, y1, plc[x][y] );
		else if( plc[x][y] == 'R' || plc[x][y] == 'Z' )
			moveHathiW( x, y, x1, y1 );
		else if( plc[x][y] == 'S' || plc[x][y] == 'Y' )
			moveGhodaW( x, y, x1, y1 );
		else if( plc[x][y] == 'T' || plc[x][y] == 'X' )
			moveVajirW( x, y, x1, y1 );
		else if( plc[x][y] == 'Q' )
			moveRaniW( x, y, x1, y1 );
		else if( plc[x][y] == 'K' )
			moveRajaW( x, y, x1, y1 );
	}
	else if( ch == 'a' ){
		if( plc[x][y] >= 97 && plc[x][y] <= 104 )
			movepyadaB( x, y, x1, y1, plc[x][y] );
		else if( plc[x][y] == 'r' || plc[x][y] == 'z' )
			moveHathiB( x, y, x1, y1 );
		else if( plc[x][y] == 's' || plc[x][y] == 'y' )
			moveGhodaB( x, y, x1, y1 );
		else if( plc[x][y] == 't' || plc[x][y] == 'x' )
			moveVajirB( x, y, x1, y1 );
		else if( plc[x][y] == 'q' )
			moveRaniB( x, y, x1, y1 );
		else if( plc[x][y] == 'k' )
			moveRajaB( x, y, x1, y1 );
	}
}

void player1(){
	setcolor(BROWN);
	settextstyle(3,0,3);
	outtextxy(511,271,"PLAYER 1");
	outtextxy(521,301,"CHANCE");
	outtextxy(510,270,"PLAYER 1");
	outtextxy(520,300,"CHANCE");
	int x, y;
	int x1, y1;
	int k1, k2;
	while( 1 ){
		CoorRajaW( &k1, &k2 );
		if( checkW( k1, k2 ) )
			outtextxy( 500, 400, "Check");

		getMxy();
		if( click == 1 ){
			hideM();
			checkblock( & x, & y, px, py );
			checkmoves( x, y, plc[x][y] );
			showM();
			while(1){
				click = 2;
				getMxy();
				if( click == 2 ){
					hideM();
					checkblock( &x1, &y1, px, py );
					checkpiece( x, y, x1, y1, 'A' );
					showM();
					break;
				}
			}
			break;
		}
	}
}

void player2(){
	setcolor(BROWN);
	settextstyle(3,0,3);
	outtextxy(511,271,"PLAYER 2");
	outtextxy(521,301,"CHANCE");
	outtextxy(510,270,"PLAYER 2");
	outtextxy(520,300,"CHANCE");
	int x, y;
	int x1, y1;
	int k1, k2;
	while( 1 ){
		getMxy();
		CoorRajaB( &k1, &k2 );
		if( checkB( k1, k2 ) )
			outtextxy( 500, 400, "Check");

		if( click == 1 ){
			hideM();
			checkblock( & x, & y, px, py );
			checkmoves( x, y, plc[x][y] );
			showM();
			while(1){
				click = 2;
				getMxy();
				if( click == 2 ){
					hideM();
					checkblock( &x1, &y1, px, py );
					checkpiece( x, y, x1, y1, 'a' );
					showM();
					break;
				}
			}
			break;
		}
	}
}

void main(){
	int gd=0, gm;
	clrscr();
	initgraph( &gd, &gm, "C:\\turboc3\\bgi");

	logo();
	cleardevice();
	loading();
	cleardevice();

	startmenu();
	cleardevice();
	hideM();

	initM();
	showM();
}
void CoorRajaB( int * x, int * y ){
	char status = 'f';
	for( int i = 0; i < 8; i++ ){
		for( int j = 0; j < 8; j++ ){
			if( plc[i][j] == 'k' ){
				   *(x) = i;
				   *(y) = j;
				   status = 't';
			}
		}
	}
	if( status == 'f' ){
		outtextxy( 500, 400, "player 1 win");
		getch();
		exit(0);
	}

}
void basic()
{
	int k1, k2, K1, K2;
	showM();
	while(1){
		hideM();
		if( count % 2 == 0 ){
			cleardevice();
			interface();
			showM();
			BoardwithPiece();
			CoorRajaW( &K1, &K2 );
			checkMateW( K1, K2 );
			player1();
		}
		else{
			hideM();
			cleardevice();
			interface();
			showM();
			BoardwithPiece();
			CoorRajaB( &k1, &k2 );
			checkMateB( k1, k2 );
			player2();
		}

	}
}

void CoorRajaW( int * x, int * y ){
	char status = 'f';
	for( int i = 0; i < 8; i++ ){
		for( int j = 0; j < 8; j++ ){
			if( plc[i][j] == 'K' ){
				   *(x) = i;
				   *(y) = j;
				   status = 't';
			}
		}
	}
	if( status == 'f' ){
		outtextxy( 500, 300, "Player 2 win");
		getch();
		exit(0);
	}
}