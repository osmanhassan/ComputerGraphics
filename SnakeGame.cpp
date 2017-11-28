#include <GL/glut.h>
#include <stdlib.h>
#include<iostream>
#include<cstring>
using namespace std;
const int VM_N = 30;
const int VM_M = 23;
const int VM_Scale = 25;
const int VD_W = VM_N * VM_Scale;
const int VD_H = VM_M * VM_Scale;
char text[] = "Score : ";
int score=0;
int lavel;
float speed = 0.0f;
float savedSpeed = 0.0f;
bool paused = false;
struct snk {
	int x;
	int y;
};
int dir = 1, sh = 4;
snk s[100];
int step = 300;
int MX, myMX;
class fruct{
	public:
		int x, y;
		void gen() {
			x = rand() % VM_N; /*rand() is from stdlib.h header and it generates random value from 0 to max value*/
			y = rand() % VM_M;
		}

		void draw() {
            glClearColor(0.0,0.0,0.0,0);
			glColor3f(1,1,1);//set the color of target cube
			glRecti(x * VM_Scale - 1, y * VM_Scale, (x +1) * VM_Scale, (y + 1) * VM_Scale + 1);
		}
};



fruct fru;


class game {
	public:
		void over() {
			cout<<"Game Over ..."<<"\nLavel : "<<lavel<<"\nScore :"<<score<<endl<<endl;
			exit(0);
		}

		void drawField() {
			glColor3f(1, 1, 1);

			glBegin(GL_LINES);
				for(int i = 0; i < VM_N; i++) {
					glVertex2i(i * VM_Scale, 0);
					glVertex2i(i * VM_Scale, VD_H);
				}
				for(int i = 0; i < VM_M; i++) {
					glVertex2i(0, i * VM_Scale);
					glVertex2i(VD_W, i * VM_Scale);
				}
			glEnd();

		}

		void drawSnake() {
			glColor3f(1, 1, 1);
			glRecti(s[0].x * VM_Scale - 1, s[0].y * VM_Scale, (s[0].x + 1) * VM_Scale, (s[0].y + 1) * VM_Scale + 1);

            glColor3f(1, 0, 0);
			for(int i = 1; i < sh; i++)

				glRecti(s[i].x * VM_Scale - 1, s[i].y * VM_Scale, (s[i].x + 1) * VM_Scale, (s[i].y + 1) * VM_Scale + 1);
		}

		void stroke() {
			for(int i = sh; i > 0; i--) {
				s[i].x = s[i-1].x;
				s[i].y = s[i-1].y;
			}

            if(dir == 1)
				s[0].y += 1;
			if(dir == 2)
				s[0].x += 1;
			if(dir == 3)
				s[0].y -= 1;
			if(dir == 4)
				s[0].x -= 1;


			if(fru.x == s[0].x && fru.y == s[0].y) {
                if(lavel==1)
                    score++;
                if(lavel==2)
                    score+=2;
                if(lavel==3)
                    score+=4;
				sh++;
				fru.gen();

				if(sh > MX)
					myMX = sh;

				if(step > 1)
					step -= step / 20;
			}


			if(s[0].x < 0 || s[0].x >= VM_N || s[0].y < 0 || s[0].y >= VM_M)

				over();


			for(int i = 1; i < sh; i++)
				if(s[0].x == s[i].x && s[0].y == s[i].y)
					over();
		}



		static void keyboard(int key, int a, int b) {
			switch(key) {
				case 101:
					if(dir != 3)
						dir = 1;
				break;

				case 102:
					if(dir != 4)
						dir = 2;
				break;

				case 103:
					if(dir != 1)
						dir = 3;
				break;

				case 100:
					if(dir != 2)
						dir = 4;
				break;
			}
		}
};
game snake;
void Sprint( float x, float y, char *st)
{
    int l,i;


    l=strlen( st ); // see how many characters are in text string.
    glColor3f(0.0,1.0,0.7);
    //glDisable(GL_LIGHTING);
    glRasterPos2f( x, y); // location to start printing text
    for( i=0; i < l; i++) // loop until i is greater then l
    {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);

    }


}
void Sprint1( float x, float y)
{
    int l,i;


     // see how many characters are in text string.
    glColor3f(0.0,1.0,0.7);
    //glDisable(GL_LIGHTING);
    glRasterPos2f( x, y); // location to start printing text

       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, score);




}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);


	snake.drawField();
    Sprint(600,550,text);
    Sprint1(630,550);

	snake.drawSnake();

	fru.draw();


	glutSwapBuffers();
}



void timer(int = 0) {
	display();
	snake.stroke();
    if(score<=5){
        lavel=1;
        speed=400;
    }
    if(score>5 && score<=15){
        lavel=2;
        speed=200;
    }
    if(score>15){
        lavel=3;
        speed=100;
    }

	glutTimerFunc(speed, timer, 0);
}

void firstGameSetup() {
	for(int i = 0; i < sh; i++) {
		s[i].x = VM_N / 2;
		s[i].y = (VM_M + sh) / 2 - i;
	}


	fru.gen();
}


void firstSetup() {
	glClearColor(0, 0, 0, 0);
	glColor3f(0, 0, 0);
}




int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(VD_W, VD_H);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("C.G Snake");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, VD_W, 0, VD_H);


	firstSetup();
	firstGameSetup();
	//firstRecordSetup();


	glutSpecialFunc(game::keyboard);


	glutDisplayFunc(display);

	glutTimerFunc(step, timer, 0);


	glutMainLoop();



	return 0;
}


