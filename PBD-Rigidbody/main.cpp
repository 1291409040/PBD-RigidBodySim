/*
    based on the paper
    "Position based dynamics"
    by zs @ sjtu
*/

#include <windows.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

#include "PBDSolver.h"
#include "particle.h"

#define ScreenX 800
#define ScreenY 600

PBDSolver solver;

void render(){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	glColor3f(0.0, 0.0, 0.5);
    glBegin(GL_LINES);
        for(GLfloat x = 0; x < SIMX; x += H){
            glVertex2f(x, 0.0);
            glVertex2f(x, SIMY);
        }
        for(GLfloat y = 0; y < SIMY; y += H){
            glVertex2f(0.0, y);
            glVertex2f(SIMX, y);
        }
    glEnd();

    glPointSize(5);

    glBegin(GL_POINTS);
    int num;
    Particle* particles = solver.getParticles(num);
    for(int i=0; i < num; ++i){
        Particle &pi = particles[i];
        glColor3f(1.0, 1.0, 0.5);
        glVertex2f(pi.pos.x, pi.pos.y);
    }
    glEnd();

	glutSwapBuffers();
}

void idle(){
    int it = 3;
    while(it--){
        solver.Update();
    }
	render();
}

/* Program entry point */
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize(ScreenX, ScreenY);
	glutCreateWindow("PBF");

	glutDisplayFunc(render);
	glutIdleFunc(idle);
//
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, SIMX, 0, SIMY);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_POINT_SMOOTH);
//
    solver.Init();

	glutMainLoop();

    return EXIT_SUCCESS;
}
