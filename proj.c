#include<GLUT/glut.h>
#include<OpenGL/gl.h>
//#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include<time.h>
#include<unistd.h>

#define CIRCLE_RADIUS 0.15f
#define pi 3.142857
#define discount 1

void final_page();
int bl = 0;

float q_matrix[16][4] = { {-10000, 0, 0, -10000},
							{0, 0, 0, -10000},
							{0, 0, 0, -10000},
							{0, -10000, 0, -10000},
							{-10000, 0, 0, 0},
							{0, 0, 0,0},
							{0, 0, 0, 0}, //WUMPUS
							{0, -10000, 0, 0},
							{10000, 10000, 10000, 10000}, //GOLD
							{0, 0, 0, 0},
							{0, 0, 0, 0},
							{0, -10000, 0, 0},
							{-10000, 0, -10000, 0}, //FINDS GOLD
							{0, 0, -10000, 0},
							{0, 0, -10000, 0},
                            {0, -10000, -10000, 0}
						};
int box = 0;
int cur_pos = 0;
float max =-1;
int next_pos = 0;
int action = 1;
float reward = -0.04;
void translate();
int j=0, i = 0, pos = 0, tx = 0, ty = 0;
float learning_rate = 0.5;
int select_action(int);
bool gameOver(int);
int circle_points = 100;
GLint a=0,b=0,flag=0;
GLfloat red=0,blue=1,green=.3;
GLfloat yr,xr;
int score = 505;
int choice = 0;
int iter = 0;

int last_death;


GLfloat p=0,q=0,r=0;
void mydisplay();
void wumpus();
void display();
void grid();
void frontsreen();
void drawstring(float x,float y,float z,char *string);
void square();
void setFont();
void update();
void control();
void helpscreen();
void menu();
void *currentfont;
void delay(unsigned int mseconds);
void move_square(int tx,int ty);
int count = 0;
int action_array[200];
int ctrl = 0;

int l = 0;
int o = 450;
int o1 = 500;
int o2 = 100;
int o3 = 150;

void move_square(tx,ty)
{
 		glClear(GL_COLOR_BUFFER_BIT);
        grid();
		
        wumpus();

        glBegin(GL_POLYGON);
			glColor3f(1.0,0.0,0.0);
			o = o+tx;
			o1 = o1+tx;
			o2 = o2+ty;
			o3 = o3+ty;
			sleep(10);
			//delay(10000);
			glVertex2f(o,o2);
			glVertex2f(o1,o2);
			glColor3f(0.0,1.0,0.0);
			glVertex2f(o,o3);
			glVertex2f(o1,o3);
			glColor3f(0.0,0.0,1.0);
			glVertex2f(o,o2);
			glVertex2f(o,o3);
			glColor3f(1.0,1.0,0.0);
			glVertex2f(o1,o2);
			glVertex2f(o1,o3);
			glEnd();
        glFlush();
}
/*
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock())
        ;
}
*/

void final_page()
{
	glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
	glClearColor(0,0.5,0.5,1.0); //grid background
	glLineWidth(2.5);
	glColor3f(0.0,0.0,0.0); //lines color
	glBegin(GL_LINE_STRIP);
        //0
		glVertex2f(400,50);
		glVertex2f(550,50);
		glVertex2f(550,200);
		glVertex2f(400,200);

		glVertex2f(400,50);
		glVertex2f(550,200);
		glVertex2f(550,50);
		glVertex2f(400,200);
		//1
		glVertex2f(550,50);
		glVertex2f(700,50);
		glVertex2f(700,200);
		glVertex2f(550,200);

		glVertex2f(550,50);
		glVertex2f(700,200);
		glVertex2f(700,50);
		glVertex2f(550,200);
		//2
		glVertex2f(700,50);
		glVertex2f(850,50);
		glVertex2f(850,200);
		glVertex2f(700,200);

		glVertex2f(700,50);
		glVertex2f(850,200);
		glVertex2f(850,50);
		glVertex2f(700,200);
		//3
		glVertex2f(850,50);
		glVertex2f(1000,50);
		glVertex2f(1000,200);
		glVertex2f(850,200);

		glVertex2f(850,50);
		glVertex2f(1000,200);
		glVertex2f(1000,50);
		glVertex2f(850,200);
		//4
		glVertex2f(400,200);
		glVertex2f(550,200);
		glVertex2f(550,350);
		glVertex2f(400,350);

		glVertex2f(400,200);
		glVertex2f(550,350);
		glVertex2f(550,200);
		glVertex2f(400,350);
		//5
		glVertex2f(550,200);
		glVertex2f(700,200);
		glVertex2f(700,350);
		glVertex2f(550,350);

		glVertex2f(550,200);
		glVertex2f(700,350);
		glVertex2f(700,200);
		glVertex2f(550,350);
		//6
		glVertex2f(700,200);
		glVertex2f(850,200);
		glVertex2f(850,350);
		glVertex2f(700,350);

		glVertex2f(700,200);
		glVertex2f(850,350);
		glVertex2f(850,200);
		glVertex2f(700,350);
		//7
		glVertex2f(850,200);
		glVertex2f(1000,200);
		glVertex2f(1000,350);
		glVertex2f(850,350);

		glVertex2f(850,200);
		glVertex2f(1000,350);
		glVertex2f(1000,200);
		glVertex2f(850,350);
		//8
		glVertex2f(400,350);
		glVertex2f(550,350);
		glVertex2f(550,500);
		glVertex2f(400,500);

		glVertex2f(400,350);
		glVertex2f(550,500);
		glVertex2f(550,350);
		glVertex2f(400,500);
		//9
		glVertex2f(550,350);
		glVertex2f(700,350);
		glVertex2f(700,500);
		glVertex2f(550,500);

		glVertex2f(550,350);
		glVertex2f(700,500);
		glVertex2f(700,350);
		glVertex2f(550,500);
		//10
		glVertex2f(700,350);
		glVertex2f(850,350);
		glVertex2f(850,500);
		glVertex2f(700,500);

		glVertex2f(700,350);
		glVertex2f(850,500);
		glVertex2f(850,350);
		glVertex2f(700,500);
		//11
		glVertex2f(850,350);
		glVertex2f(1000,350);
		glVertex2f(1000,500);
		glVertex2f(850,500);

		glVertex2f(850,350);
		glVertex2f(1000,500);
		glVertex2f(1000,350);
		glVertex2f(850,500);
		//12
		glVertex2f(400,500);
		glVertex2f(550,500);
		glVertex2f(550,650);
		glVertex2f(400,650);

		glVertex2f(400,500);
		glVertex2f(550,650);
		glVertex2f(550,500);
		glVertex2f(400,650);
		//13
		glVertex2f(550,500);
		glVertex2f(700,500);
		glVertex2f(700,650);
		glVertex2f(550,650);

		glVertex2f(550,500);
		glVertex2f(700,650);
		glVertex2f(700,500);
		glVertex2f(550,650);
		//14
		glVertex2f(700,500);
		glVertex2f(850,500);
		glVertex2f(850,650);
		glVertex2f(700,650);

		glVertex2f(700,500);
		glVertex2f(850,650);
		glVertex2f(850,500);
		glVertex2f(700,650);
		//15
		glVertex2f(850,500);
		glVertex2f(1000,500);
		glVertex2f(1000,650);
		glVertex2f(850,650);

		glVertex2f(850,500);
		glVertex2f(1000,650);
		glVertex2f(1000,500);
		glVertex2f(850,650);
	glEnd();
	glPopMatrix();
	
	//float n = q_matrix[0][0];
    //char buffer[10]={'\0'};
    //sprintf(buffer, "%f", n);
    
	//TODO
	for(int l = 0; l<16; l++)
	{
		for(int m = 0; m<4; m++)
		{
			float num = q_matrix[l][m];
			char snum[5];
			ftoa(num, snum, 10);    
			drawstring(450, 650 ,0, snum);
		}
	}
	
}

void translate()
{
	printf("In translate\n");
    //for(int z = 0; z < ctrl; z++) //till end of action array
	for(int z = last_death+25; z < ctrl; z++) //till end of action array
		{
			printf("z_value: %d\n", z);
			if(action_array[z] ==0 )
			{
				tx = -150.0;
				ty = 0.0;
				//glPushMatrix();
				move_square(tx,ty);
				printf("here: %d", bl++);
				//sleep(10);
				//delay(10000);
				//glPopMatrix();
			}
			else if (action_array[z] ==1 )
			{
				tx = 150.0;
				ty = 0.0;
				//glPushMatrix();
				move_square(tx,ty);
				printf("here: %d", bl++);
				//sleep(10);
				//delay(10000);
				//glPopMatrix();
			}
			else if(action_array[z] ==2 )
			{
				tx = 0.0;
				ty = 150.0;
				//glPushMatrix();
				move_square(tx,ty);
				printf("here: %d", bl++);
				//sleep(10);
				//delay(10000);
				//glPopMatrix();
			}
			else if( action_array[z] ==3 )
			{
				tx = 0.0;
				ty = -150.0;
				//glPushMatrix();
				move_square(tx,ty);
				printf("here: %d", bl++);
				//sleep(10);
				//delay(10000);
				//glPopMatrix();
			}
			else if( action_array[z] == 10) //death
			{
				o = 450;
				o1 = 500;
				o2 = 100;
				o3 = 150;
				move_square(0,0);
				printf("here: %d", bl++);
				//sleep(10);
				//delay(10000);
			}
		glFlush();
	}choice = 3;
}

void square()
{
	glPushMatrix();
	//glScaled(40.0,40.0,0.0);
	glColor3f(0.75,0.75,0.75);
    if(choice ==2)  //play
	{
		if(xr == 0 && yr == 150 || xr == 150 && yr == 300 || xr == 300 && yr == 150 || score < 0)
        {
			setFont(GLUT_BITMAP_TIMES_ROMAN_24);
			glClearColor(0,0.5,0.5,1.0);/*background for cover page and grid */
			glClear(GL_COLOR_BUFFER_BIT);
			drawstring(650.0,500.0,0.0,"You lost :-(");
			choice = 0;
			xr = 0;
			yr = 0;
			score = 505;
        }
        else if (xr == 0 && yr == 300)
        {
			setFont(GLUT_BITMAP_TIMES_ROMAN_24);
			glClearColor(0,0.5,0.5,1.0);/*background for cover page and grid */
			glClear(GL_COLOR_BUFFER_BIT);
			glColor3f(0,1,0);
			drawstring(450.0,350.0,0.0,"You win! :-)");
			choice = 0;
			xr = 0;
			yr = 0;
			score = 505;
        }
        else
	    {

			glBegin(GL_POLYGON);
				glColor3f(1.0,0.0,0.0);
				glVertex2f(xr+450,yr+100);
				glVertex2f(xr+500,yr+100);
				glColor3f(0.0,1.0,0.0);
				glVertex2f(xr+450,yr+150);
				glVertex2f(xr+500,yr+150);
				glColor3f(0.0,0.0,1.0);
				glVertex2f(xr+450,yr+100);
				glVertex2f(xr+450,yr+150);
				glColor3f(1.0,1.0,0.0);
				glVertex2f(xr+500,yr+100);
				glVertex2f(xr+500,yr+150);
			glEnd();

        }
 	}
 	glFlush();
}

void wumpus()
{
	//1
	int i;
		int triangleAmount = 20; //# of triangles used to draw circle

		//GLfloat radius = 0.8f; //radius
		GLfloat twicePi = 2.0f * pi;

		glBegin(GL_TRIANGLE_FAN);
		int x = 475;
		int y = 285;
		glVertex2f(x, y); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x + (50 * cos(i *  twicePi / triangleAmount)),
					y + (50 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x1 = 457;
		int y1 = 290;
		glVertex2f(x1, y1); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x1 + (15 * cos(i *  twicePi / triangleAmount)),
					y1 + (15 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x2 = 497;
		int y2 = 290;
		glVertex2f(x2, y2); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x2 + (15 * cos(i *  twicePi / triangleAmount)),
					y2 + (15 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x3 = 457;
		int y3 = 288;
		glVertex2f(x3, y3); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x3 + (7 * cos(i *  twicePi / triangleAmount)),
					y3 + (7 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x4 = 497;
		int y4 = 288;
		glVertex2f(x4, y4); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x4 + (7 * cos(i *  twicePi / triangleAmount)),
					y4 + (7 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
	//2
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x5 = 775;
		int y5 = 285;
		glVertex2f(x5, y5); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x5 + (50 * cos(i *  twicePi / triangleAmount)),
					y5 + (50 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x6 = 757;
		int y6 = 290;
		glVertex2f(x6, y6); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x6 + (15 * cos(i *  twicePi / triangleAmount)),
					y6 + (15 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x7 = 797;
		int y7 = 290;
		glVertex2f(x7, y7); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x7 + (15 * cos(i *  twicePi / triangleAmount)),
					y7 + (15 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x8 = 757;
		int y8 = 288;
		glVertex2f(x8, y8); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x8 + (7 * cos(i *  twicePi / triangleAmount)),
					y8 + (7 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x9 = 797;
		int y9 = 288;
		glVertex2f(x9, y9); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x9 + (7 * cos(i *  twicePi / triangleAmount)),
					y9 + (7 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();

	//3
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_TRIANGLE_FAN);
		int x10 = 625;
		int y10 = 435;
		glVertex2f(x10, y10); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x10 + (50 * cos(i *  twicePi / triangleAmount)),
					y10 + (50 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x11 = 607;
		int y11 = 440;
		glVertex2f(x11, y11); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x11 + (15 * cos(i *  twicePi / triangleAmount)),
					y11 + (15 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x12 = 647;
		int y12 = 440;
		glVertex2f(x12, y12); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x12 + (15 * cos(i *  twicePi / triangleAmount)),
					y12 + (15 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x13 = 607;
		int y13 = 438;
		glVertex2f(x13, y13); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x13 + (7 * cos(i *  twicePi / triangleAmount)),
					y13 + (7 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_TRIANGLE_FAN);
		int x14 = 647;
		int y14 = 438;
		glVertex2f(x14, y14); // center of circle
			for(i = 0; i <= triangleAmount;i++)
			{
				glVertex2f(
						x14 + (7 * cos(i *  twicePi / triangleAmount)),
					y14 + (7 * sin(i * twicePi / triangleAmount))
				);
			}
		glEnd();
		//gold
		glColor3f(0.94,0.89,0.22);
			glBegin(GL_POLYGON);
			glVertex3f(435.0, 405.0, 0.0);
			glColor3f(1.0,1.0,1.0);
			glVertex3f(515.0, 405.0, 0.0);
			glColor3f(0.94,0.89,0.22);
			glVertex3f(505.0, 465.0, 0.0);
			glColor3f(1.0,1.0,1.0);
			glVertex3f(445.0, 465.0, 0.0);
			glEnd();

}


void grid()
{
	glPushMatrix();
	//glScaled(40.0,40.0,0.0);
	glClearColor(0,0.5,0.5,1.0); //grid background
	glLineWidth(2.5);
	glColor3f(0.0,0.0,0.0); //lines color
	glBegin(GL_LINES);
		glVertex2f(400, 50);
		glVertex2f(1000, 50);
		glVertex2f(400,50);
		glVertex2f(400,650);

		glVertex2f(400, 650);
		glVertex2f(1000, 650);
		glVertex2f(1000,650);
		glVertex2f(1000,50);

		glVertex2f(400, 200);
		glVertex2f(1000, 200);
		glVertex2f(400,350);
		glVertex2f(1000,350);

		glVertex2f(400, 500);
		glVertex2f(1000, 500);
		glVertex2f(550,50);
		glVertex2f(550,650);

		glVertex2f(700, 50);
		glVertex2f(700, 650);
		glVertex2f(850,50);
		glVertex2f(850,650);
	glEnd();
	glPopMatrix();
}


void setFont(void *font)
{
	currentfont=font;
}


void drawstring(float x,float y,float z,char *string)
{
	char *c;
	glRasterPos3f(x,y,z);
	for(c=string;*c!='\0';c++)
	{	glColor3f(0.0,0.0,0.0);
		glutBitmapCharacter(currentfont,*c);
	}
}

void frontscreen(void) //ENTER SCREEN
{
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	//glClearColor(0.15,0.1,0.01,0);/*background for cover page*/
	glClearColor(1.0,1.0,1.0,1.0); //doesnt matter
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON); //1346, 728
		glColor3f(1.0,0.0,0.0);
		glVertex3f(0.0,0.0,0.0);
		glColor3f(0.0,1.0,0.0);
		glVertex3f(0.0,728.0,0.0);
		glColor3f(0.0,0.0,1.0);
		glVertex3f(1346.0,728.0,0.0);
		glColor3f(1.0,1.0,0.0);
		glVertex3f(1346.0,0.0,0.0);
	glEnd();
	//text and the text color
	//glColor3f(1,0,0);
	glColor3f(1,1,1);
	drawstring(450.0,650.0,0.0," PES INSTITUTE OF TECHNOLOGY ");
	//glColor3f(0.7,0,1);
	glColor3f(1,1,1);
	drawstring(330,600,0.0,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
	//glColor3f(1,0.5,0); //background for grid
	glColor3f(1,1,1);
	drawstring(530,500,0.0,"A MINI PROJECT ON");
	//glColor3f(1,0,0);
	glColor3f(1,1,1);
	drawstring(360,450,0.0,"WUMPUS WORLD PROBLEM - AN AI ALGORITHM");
	//glColor3f(1,0.5,0);
	glColor3f(1,1,1);
	drawstring(100,360,0.0,"BY:");
	glColor3f(1,1,1);
	drawstring(100,300,0.0,"Anisha Khetan      1PE16CS022");
	glColor3f(1,1,1);
	drawstring(100,240,0.0,"Ashwini Kelkar      1PE16CS034");
	//glColor3f(1,0.5,0);
	glColor3f(1,1,1);
	drawstring(930,360,0.0,"GUIDES:");
	glColor3f(1,1,1);
	drawstring(930,300,0.0,"Name");
	glColor3f(1,1,1);
	drawstring(930,240,0.0,"Name");
	//glColor3f(1,0.1,1);
	glColor3f(1,1,1);
	drawstring(543,100,0.0,"PRESS ENTER TO START");
	glFlush();
}

void helpscreen() //TODO
{
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glClearColor(0,0.5,0.5,1.0);/*background for cover page and grid */
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,1,0);
	drawstring(550.0,700.0,0.0,"RULES");
	glColor3f(1,0,0);
	drawstring(650.0,700.0,0.0,"TO");
	glColor3f(0,0,1);
	drawstring(750.0,700.0,0.0,"FOLLOW");
	glColor3f(0.5,0.1,0.2);
	drawstring(350.0,640.0,0.0,"*****                                           *****");
	glColor3f(0.5,0.1,0.3);
	drawstring(350.0,540.0,0.0,"*****                                           *****");
	glColor3f(0.5,0.1,0.4);
	drawstring(350.0,440.0,0.0,"*****                                           *****");
	glColor3f(0.4,0.1,0.5);
	drawstring(350.0,340.0,0.0,"*****                                           *****");
	glColor3f(0.5,0.1,0.6);
	drawstring(350.0,240.0,0.0,"*****                                           *****");
	glColor3f(0.5,0.1,0.7);
	drawstring(350.0,140.0,0.0,"*****                                           *****");
	glColor3f(0.5,0.1,0.8);
	drawstring(350.0,90.0,0.0,"*****                                           *****");
	glColor3f(0.5,0.1,0.9);
	drawstring(350.0,40.0,0.0,"Escape                                                                  PRESS 'ENTER'");
	glFlush();
}

void menu(int id)
{
	glClear(GL_COLOR_BUFFER_BIT);
	switch(id)
	{
		case 0: exit(0); break;
		case 1: choice = 1;//learn();
				break;
		case 2: choice = 2;//play
				break;
        //case 3: choice = 3;//final grid
               // break;
	}
	glutPostRedisplay();
}

int select_action(int i)
{
    for(j = 0; j< 4; j++ )
	{
		if(q_matrix[i][j] > -10000)
		{	if(q_matrix[i][j] > max)
			{
				max = q_matrix[i][j];
			}
		}
	}
	for(j = 0; j< 4; j++ )
	{
	    if(q_matrix[i][j] == max)
        {
            max = -1;
            return j;
        }
	}
}

bool gameOver(int cur_pos)
{
	if(cur_pos == 8)
	{
        return true;
	}return false;

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if(choice == 3)
    {
        final_page();
    }

	if(choice ==2) //play
	{
		grid();
		wumpus();
		square();
		glFlush();
	}
	else if(choice == 1) //learn
  {
		grid();
		wumpus();
		//square();
		glFlush();

		while(!gameOver(cur_pos) )
		{
			action = select_action(cur_pos);

			if(action == 0) //left
			{
				next_pos = cur_pos - 1; //new i value
			}
			if(action == 1) //right
			{
				next_pos = cur_pos +1;
			}
			if(action == 2) //top
			{
				next_pos = cur_pos +4;
			}
			if(action == 3) //bottom
			{
				next_pos = cur_pos - 4;
			}

            action_array[ctrl] = action;
            ctrl++;
			if(next_pos == 4 || next_pos == 6 || next_pos == 9)
			{
				next_pos = 0;
				learning_rate = 0;
				q_matrix[cur_pos][action] = -10000;
				action_array[ctrl] = 10;
				last_death = ctrl;
                ctrl++;
			}
			else 
			{
				learning_rate = 0.5;
			}

			int maxa = -1;
			for(int i1 = 0;i1<4;i1++)
            {
                if(q_matrix[next_pos][i1] > maxa)
                {
                    maxa = q_matrix[next_pos][i1];
                    pos = i1;
                }
            }
			q_matrix[cur_pos][action] = q_matrix[cur_pos][action] + learning_rate * ( reward + 1*(q_matrix[next_pos][pos]) - q_matrix[cur_pos][action] );
			cur_pos = next_pos;
		}


			for(int i = 0;i<ctrl;i++)
    {
        printf("%d  ",action_array[i]);
    }
	printf("done\n");
		translate();
		
  }

}

void myKeyboard( unsigned char key, int x, int y )
{
	switch(key)
	{
		case 13: //Ascii of 'enter' key is 13
			if(flag==1)
			{
				flag=2;
				mydisplay();
			}
			if(flag==0)
			{
				flag=1;
				mydisplay();
			}
			break;
		default:
			break;
	}
}

void mySpecial(int key, int x, int y)
{
	switch(key)
	{
			case GLUT_KEY_RIGHT:
							yr = yr+0;
							if(score > 0)
							{
								if(xr < 450)
								{
									xr = xr+150;
									score = score - 50;
								}
							}
									//if(xr == 0 && yr == 150)
							glutPostRedisplay();
							break;
    	case GLUT_KEY_LEFT:
							yr = yr+0;
							if(score >0)
							{
								if(xr > 0)
									xr = xr-150;
									score = score - 50;
							}
							glutPostRedisplay();
							break;
    	case GLUT_KEY_UP:
							xr = xr+0;
							if(score >0)
							{
								if(yr < 450)
									yr = yr+150;
									score = score - 50;
							}
							glutPostRedisplay();
							break;
    	case GLUT_KEY_DOWN:
							xr = xr+0;
							if(score >0)
							{
								if(yr > 0)
									yr = yr-150;
									score = score -50;
							}
							glutPostRedisplay();
							break;
			default:
							break;
	}

}

void mydisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	if(flag==0)
		frontscreen();
	if(flag==1)
		helpscreen();
	if(flag==2)
		display();
	glutSwapBuffers();
}

void myinit()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,1346.0,0.0,728.0);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1346,728);
	glutInitWindowPosition(0,0);
	glutCreateWindow("WumpusWorld");
	glutCreateMenu(menu);
	glutAddMenuEntry("Exit", 0);
	glutAddMenuEntry("Learn", 1);
	glutAddMenuEntry("Play", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutDisplayFunc(mydisplay);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecial);
	myinit();
	glutMainLoop();
}