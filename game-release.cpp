//============================================================================
// Name        : Tetris.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Tetris...
//============================================================================
#ifndef TETRIS_CPP_
#define TETRIS_CPP_
#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<string>
//#include<sys/wait.h>
//#include<stdlib.h>
//#include<stdio.h>
#include<unistd.h>
#include<sstream>
#include<cmath>      // for basic math functions such as cos, sin, sqrt
using namespace std;


void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
int cirx=10,ciry=20,size=1,herdal,blink1=0,chalna=0,line=0;
int counter1,counter2=0,foodx[5],foody[5],blink=0,bonusx,bonusy,power=0;
long int score=0;
int bodyx[999]={0},bodyy[999]={0},dis=0;
char game[65][65];
int level[4]={160,160,160,160},herdal1[4]={700,700,700,700},herdal2[4]={700,700,700,700},herdal3[4]={700,700,700,700};



void conversiontopixelforfood(int *pointer)
	{
		for (counter1=0;counter1<5;counter1++)
			pointer[counter1]=pointer[counter1]*10;
	}		



void conversiontoindexforfood(int *pointer1)
	{
		for (counter1=0;counter1<5;counter1++)
			pointer1[counter1]=pointer1[counter1]/10;
		
	}





void movementofsnake ()//This function is for the movement of the snake like if we press right it will start moving right and ......
{
	if (chalna==1)
		cirx-=1;
	if (chalna==2)
		cirx+=1;
	if (chalna==3)
		ciry+=1;
	if (chalna==4)
		ciry-=1;
}




void eatingoffood()
{
for(counter1=0;counter1<5;counter1++) 
	{
	if ( (cirx*10) ==(foodx[counter1]*10) &&  (ciry*10) ==(foody[counter1]*10))
		{
			score+=5;
			size++;
			level[line]+=10;
		if (level[line]==350)
		{
			line=line+1;
			dis=dis+1;
		}
			foodx[counter1]=rand()%50+5;
			foody[counter1]=rand()%50+5;
		}
	}
	
	if (cirx==bonusx && ciry==bonusy) 
	{
		score+=20;
		bonusx=700;
		bonusy=700;
	}
}







void regenerationofsnake()//This function is for the regeneration of the snake .like if it go from right it will reappear from left.
{
	if (cirx==64)
		cirx=1;
	if (cirx==0)
		cirx=63;
	if (ciry==64)
		ciry=1;			
	if (ciry==0)
		ciry=63;
}




void generationoffivefood()
{
if (blink==0)
{

srand(time(NULL));
	for (counter1=0;counter1<5;counter1++)
		foodx[counter1]=rand()%60;
	
	for (counter2=0;counter2<5;counter2++)
		foody[counter2]=rand()%60;
	for (counter1=1;counter1<5;counter1++)
	{
		while (foodx[0]==foodx[counter1] )
		foodx[counter1]=rand()%60;
		while (foody[0]==foody[counter1] )
		foody[counter1]=rand()%60;
	}
	while (foodx[1]==foodx[0] ||foodx[1]==foodx[2] ||foodx[1]==foodx[3] ||foodx[1]==foodx[4] )
		foodx[1]=rand()%60;
	while (foodx[2]==foodx[0] ||foodx[2]==foodx[1] ||foodx[2]==foodx[3] ||foodx[2]==foodx[4] )
		foodx[2]=rand()%60;
	while (foodx[3]==foodx[0] ||foodx[3]==foodx[2] ||foodx[3]==foodx[1] ||foodx[3]==foodx[4] )
		foodx[3]=rand()%60;
	while (foodx[4]==foodx[0] ||foodx[4]==foodx[2] ||foodx[4]==foodx[3] ||foodx[4]==foodx[1] )
		foodx[4]=rand()%60;

	while (foody[1]==foody[0] ||foody[1]==foody[2] ||foody[1]==foody[3] ||foody[1]==foody[4] )
		foody[1]=rand()%60;
	while (foody[2]==foody[0] ||foody[2]==foody[1] ||foody[2]==foody[3] ||foody[2]==foody[4] )
		foody[2]=rand()%60;
	while (foody[3]==foody[0] ||foody[3]==foody[2] ||foody[3]==foody[1] ||foody[3]==foody[4] )
		foody[3]=rand()%60;
	while (foody[4]==foody[0] ||foody[4]==foody[2] ||foody[4]==foody[3] ||foody[4]==foody[1] )
		foody[4]=rand()%60;


blink=75;
}
blink--;

	conversiontopixelforfood(foodx);
	conversiontopixelforfood(foody);
		DrawCircle( foodx[0]+5 ,foody[0]+5 , 5, colors[101]);
		DrawCircle( foodx[1]+5,foody[1]+5 , 5, colors[68]);
		DrawCircle( foodx[2]+5,foody[2]+5, 5, colors[84]);
		DrawCircle( foodx[3]+5,foody[3]+5, 5, colors[71]);
		DrawCircle( foodx[4]+5,foody[4]+5, 5, colors[16]);
	conversiontoindexforfood(foodx);
	conversiontoindexforfood(foody);
}






void generationofbody()
{
 
    
    for(counter1=size;counter1>=0;counter1--)
	{
		bodyx[0]=cirx;
       	bodyy[0]=ciry;
	
	    bodyx[counter1]=bodyx[counter1-1];
	    bodyy[counter1]=bodyy[counter1-1];
	 
	}    
    for (counter1=0;counter1<size;counter1++)
	DrawSquare( bodyx[counter1]*10+1 , bodyy[counter1]*10-2 ,10,colors[10]);	

} 




void killingofsnake()
{
	for (counter1=0;counter1<size;counter1++)
	{	if (cirx==bodyx[counter1] && ciry==bodyy[counter1])
		{
	
					DrawSquare( 0,0,650,colors[23]);
			DrawString( 350, 350, "GAME OVER", colors[DARK_SLATE_GRAY]);
	
			exit(1);
		}
		
	
	}

	if (cirx==(herdal1[0]+10) && ciry==(herdal1[1]+10))
	{
	//	exit(1);
	
			DrawSquare( 0,0,650,colors[23]);
	 DrawString( 350, 350, "GAME OVER", colors[DARK_SLATE_GRAY]);
	
		exit(1);
	}
	if (cirx==(herdal1[2]+10) && ciry==(herdal1[3]+10))
	{
	//	exit(1);
	
			DrawSquare( 0,0,650,colors[23]);
		DrawString( 350, 350, "GAME OVER", colors[DARK_SLATE_GRAY]);
	
		exit(1);
	}
	if (cirx==(herdal2[0]+10) && ciry==(herdal2[1]+10))
	{
	//	exit(1);
	
	DrawSquare( 0,0,650,colors[23]);
		DrawString( 350, 350, "GAME OVER", colors[DARK_SLATE_GRAY]);
	
		exit(1);
	}
	if (cirx==(herdal2[2]+10) && ciry==(herdal2[3]+10))
	{
	//	exit(1);
	
		DrawSquare( 0,0,650,colors[23]);
		DrawString( 350, 350, "GAME OVER", colors[DARK_SLATE_GRAY]);
	
		exit(1);
	}
	if (cirx==(herdal3[0]+10) && ciry==(herdal3[1]+10))
	{
	
	
		DrawSquare( 0,0,650,colors[23]);
		DrawString( 350, 350, "GAME OVER", colors[DARK_SLATE_GRAY]);
	
		exit(1);
	}
	if (cirx==(herdal3[2]+10) && ciry==(herdal3[3]+10))
	{
	
	
		DrawSquare( 0,0,650,colors[23]);
		DrawString( 350, 350, "GAME OVER", colors[DARK_SLATE_GRAY]);
		sleep(50);
		exit(1);
	}

}






void generationofherdal()
{
if (blink1==150)
{
	srand(time(NULL));
		herdal1[0]=rand()%60;
		herdal1[1]=rand()%60;
		
		herdal2[0]=rand()%60;
		herdal2[1]=rand()%60;
		
		herdal3[0]=rand()%60;
		herdal3[1]=rand()%60;
	for(counter1=0;counter1<5;counter1++)
		{
			while((herdal1[0]+20)==foodx[counter1] ||(herdal1[0]+20)==(herdal2[0]+20)  || (herdal1[0]+20)==(herdal3[0]+20) )
			herdal1[0]=rand()%60;
			//game[herdalx]='o';		
		}
	for(counter1=0;counter1<5;counter1++)
		{
			while((herdal1[1]+20)==foody[counter1] ||(herdal1[1]+20)==(herdal2[1]+20) || (herdal1[1]+20)==(herdal3[1]+20) )
			herdal1[1]=rand()%60;
			//game[herdaly]='o';
		}
for(counter1=0;counter1<5;counter1++)
		{
			while((herdal2[0]+20)==foodx[counter1] ||(herdal2[0]+20)==(herdal1[0]+20) || (herdal2[0]+20)==(herdal3[0]+20) )
			herdal2[0]=rand()%60;
			//game[herdalx]='o';		
		}
	for(counter1=0;counter1<5;counter1++)
		{
			while((herdal2[1]+20)==foody[counter1] ||(herdal2[1]+20)==(herdal1[1]+20) ||(herdal2[1]+20)==(herdal3[1]+20) )
			herdal2[1]=rand()%60;
			//game[herdaly]='o';
		}
for(counter1=0;counter1<5;counter1++)
		{
			while((herdal3[0]+20)==foodx[counter1] ||(herdal3[0]+20)==(herdal1[0]+20) || (herdal3[0]+20)==(herdal2[0]+20) )
			herdal3[0]=rand()%60;
			//game[herdalx]='o';		
		}
	for(counter1=0;counter1<5;counter1++)
		{
			while((herdal3[1]+20)==foody[counter1] ||(herdal3[1]+20)==(herdal1[1]+20) || (herdal3[0]+20)==(herdal2[0]+20) )
			herdal3[1]=rand()%60;
			//game[herdaly]='o';
		}

	herdal1[2]=herdal1[0];
	herdal1[3]=herdal1[1];

	herdal2[2]=herdal2[0];
	herdal2[3]=herdal2[1];

	herdal3[2]=herdal3[0];
	herdal3[3]=herdal3[1];
blink1=0;
}
	DrawSquare( herdal1[0]*10, herdal1[1]*10+11,30,colors[115]);
	DrawSquare( herdal1[2]*10, herdal1[3]*10+21,30,colors[115]);

	DrawSquare( herdal2[0]*10, herdal2[1]*10+11,30,colors[115]);
	DrawSquare( herdal2[2]*10, herdal2[3]*10+21,30,colors[115]);

	DrawSquare( herdal3[0]*10, herdal3[1]*10+11,30,colors[115]);
	DrawSquare( herdal3[2]*10, herdal3[3]*10+21,30,colors[115]);

blink1++;

}




void gamelevel()
{
	DrawString( 5, 610, " Game Level ", colors[MISTY_ROSE]);
    DrawLine( 160 , 615,350 , 615 , 5 , colors[MISTY_ROSE] );
  
    if (dis==0)
   	 DrawString( 30, 570, "LEVEL 1 ", colors[LIME_GREEN]);
    if (dis==1)
   	 DrawString( 30, 570, "LEVEL 2", colors[DARK_SLATE_GRAY]);
    if (dis==2)
   	 DrawString( 30, 570, "LEVEL 3", colors[CORN_FLOWER_BLUE]);
    if (dis==3)   
   	 DrawString( 30, 570, "LEVEL 4", colors[PLUM]);



    
    DrawLine( 160 , 615 ,level[0] ,615  , 5 , colors[LIME_GREEN] );
    DrawLine( 160 , 615 ,level[1], 615, 5 , colors[DARK_SLATE_GRAY] );
    DrawLine( 160 , 615 ,level[2], 615, 5 , colors[CORN_FLOWER_BLUE] );
    DrawLine( 160 , 615 ,level[3], 615 , 5 , colors[PLUM] );
   
   }





void displayingofscore()
{

   
    DrawString( 500, 600, "Score =", colors[DARK_RED]); 
    DrawString( 600, 600, std::to_string(score), colors[DARK_RED]);
    
}




void generationofbonus()
{

if (power==0)
{
	srand(time(NULL));
		bonusx=rand()%60;
		bonusy=rand()%60;
	for(counter1=0;counter1<5;counter1++)
		{
			while(bonusx==foodx[counter1])
			bonusx=rand()%60;
			//game[herdalx]='o';		
		}
	for(counter1=0;counter1<5;counter1++)
		{
			while(bonusy==foody[counter1])
			bonusy=rand()%60;
			//game[herdaly]='o';
		}
power=300;
}

DrawCircle( bonusx*10+5 , bonusy*10+3, 7 , colors[30]);
power--;
}





void function ()
{
regenerationofsnake();

generationofbody();
displayingofscore(); 

    DrawCircle( cirx*10+5 , ciry*10+3, 7 , colors[5]);

movementofsnake();
generationoffivefood();
eatingoffood();
generationofherdal();
generationofbonus();
killingofsnake();
gamelevel();
}


void Display(){

    glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
            0.0/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
    glClear(GL_COLOR_BUFFER_BIT);   //Update the colors


/*  for (counter1=0;counter1<65;counter1++)
   	for (counter2=0;counter2<65;counter2++)
    	{
			DrawSquare(counter1*10 ,counter2*10 ,10,colors[120]);
	}    		
    */
 function();
 

   glutSwapBuffers();
}





void NonPrintableKeys(int key, int x, int y)
 {
    if (key == GLUT_KEY_LEFT ) {
    
if (chalna!=2)
{    
    cirx-=1;
    chalna=1;
}	
      
    }
     else if (key == GLUT_KEY_RIGHT ) 
    {
if (chalna!=1)
{
	cirx+=1;
	
	chalna=2;
}
    }
     else if (key == GLUT_KEY_UP) 
    {
 	
 if (chalna!=4)
 {
 		ciry+=1;       
        
        chalna=3;
    }
    }
    else if (key == GLUT_KEY_DOWN)
    {
	if (chalna!=3)
	{
		ciry-=1;
		chalna=4;
}
    }
     glutPostRedisplay();



}



void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC/* Escape key ASCII*/) {
        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key=='r'/* Escape key ASCII*/) {
        //exit(1); // exit the program when escape key is pressed.
    	//aswangle+=90;
    }
    
    else if (int(key) == 13)
    {  
	}
    
    glutPostRedisplay();
}




void Timer(int m) {

// implement your functionality here
	glutPostRedisplay();
// once again we tell the library to call our Timer function after next 1000/FPS
    glutTimerFunc(1000.0 / FPS, Timer, 0);
}

/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) 
{

for (counter1=0;counter1<65;counter1++)
	for (counter2=0;counter2<65;counter2++)
	{
		game[counter1][counter2]=' ';
	}


    int width = 650, height =650; // i have set my window size to be 800 x 600
    InitRandomizer(); // seed the random number generator...
    glutInit(&argc, argv); // initialize the graphics library...

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
    glutInitWindowPosition(50, 50); // set the initial position of our window
    glutInitWindowSize(width, height); // set the size of our window
    glutCreateWindow("PF's Snake Game"); // set the title of our game window
    SetCanvasSize(width, height); // set the number of pixels...




    glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
    glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
    glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
    glutTimerFunc(5.0 / FPS, Timer, 0);



    glutMainLoop();
    return 1;
}
#endif /* Snake Game */
