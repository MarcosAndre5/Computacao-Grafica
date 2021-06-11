#include <GL/glut.h>

void Desenha(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glColor3f(0, 0, 0.8);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.25, 0.5);
		glVertex2f(0.5, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(0.10, 0.0);
		glVertex2f(0.40, 0.0);
		glColor3f(0, 0.8, 0);
		glVertex2f(0.40, -0.25);
		glVertex2f(0.10, -0.25);
	glEnd();
	glFlush();
}

void Inicializa(void){   
	glClearColor(0.5, 0.5, 0.5, 0.0);
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Seta Prova CG");
	glutDisplayFunc(Desenha);
	Inicializa();
	glutMainLoop();
}