#include <GL/glut.h>

float movimentoOmbro = 0, movimentoCotovelo = 0, movimentoMao = 0, dedoDireito = -1, dedoEsquerdo = 1;
GLUquadricObj *base; 

void montarRobo(void){
	glClear(GL_COLOR_BUFFER_BIT); // Superficie plana
	glColor3f(0, 1, 1);
	glBegin(GL_QUADS);
		glVertex2f(-12,-2);
		glVertex2f(-12, 0);
		glVertex2f( 12, 0);
		glVertex2f( 12,-2);
	glEnd();

	glPushMatrix();
		glRotatef(movimentoOmbro, 0, 0, 1);
		glColor3f(1, 1, 0);

		gluDisk(base, 0, 2, 16, 1); // Ombro
		
		glBegin(GL_QUADS); // Elo 1 - braço
			glVertex2f(0,-0.5);
			glVertex2f(0, 0.5);
			glVertex2f(6, 0.5);
			glVertex2f(6,-0.5);
		glEnd();

		glPushMatrix();
			glTranslatef(6, 0, 0);
			glRotatef(movimentoCotovelo, 0, 0, 1);
			glColor3f(1, 0, 0);
			gluDisk(base, 0, 0.8, 16, 1); // Cotovelo
			glBegin(GL_QUADS); // Elo 2 - antebraço
				glVertex2f(0,-0.3);
				glVertex2f(0, 0.3);
				glVertex2f(3, 0.3);
				glVertex2f(3,-0.3);
			glEnd();
			
			glPushMatrix();
				glTranslatef(3, 0, 0);
				glRotatef(movimentoMao, 0, 0, 1);
				glColor3f(0, 0, 1);
				gluDisk(base, 0, 0.8, 10, 1); // Munheca
				glBegin(GL_QUADS); // Elo 3 - Mão
					glVertex2f(0,-0.3);
					glVertex2f(0, 0.3);
					glVertex2f(2, 0.3);
					glVertex2f(2,-0.3);
				glEnd();
	
				glPushMatrix();
					glTranslatef(1, 0, 0);
					glColor3f(0, 0, 1);
					glBegin(GL_QUADS); // Palma Mão
						glVertex2f( 1 ,-1);
						glVertex2f( 1 , 1);
						glVertex2f(1.5, 1);
						glVertex2f(1.5,-1);
					glEnd();

					glBegin(GL_QUADS); // Dedo Esquerdo
						glVertex2f(1.5, dedoEsquerdo - 0.5);
						glVertex2f(1.5, dedoEsquerdo);
						glVertex2f( 3 , dedoEsquerdo);
						glVertex2f( 3 , dedoEsquerdo - 0.5);
					glEnd();
					
					glBegin(GL_QUADS); // Dedo Direito
						glVertex2f(1.5, dedoDireito);
						glVertex2f(1.5, dedoDireito + 0.5);
						glVertex2f( 3 , dedoDireito + 0.5);
						glVertex2f( 3 , dedoDireito);
					glEnd();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glFlush();
}

void controlarBraco(unsigned char botaoPressionado, int x, int y){
	switch(botaoPressionado){
		case 'n':
			if(dedoDireito >= -1.1 && dedoDireito <= -0.5)
				dedoDireito += 0.1;
			if(dedoEsquerdo >= 0.5 && dedoEsquerdo <= 1.1)
				dedoEsquerdo -= 0.1;
		break;

		case 'm':
			if(dedoDireito >= -0.9 && dedoDireito <= -0.4)
				dedoDireito -= 0.1;
			if(dedoEsquerdo >= 0.4 && dedoEsquerdo <= 0.9)
				dedoEsquerdo += 0.1;
		break;
		
		case 'z': movimentoOmbro += 5;
		break;
		
		case 'x': movimentoOmbro -= 5;
		break;

		case 'a': movimentoCotovelo += 7;
		break;
		  
		case 's': movimentoCotovelo -= 7;
		break;
		  
		case 'q': movimentoMao += 9;
		break;
		  
		case 'w': movimentoMao -= 9;
		break;
	}
	glutPostRedisplay(); // Atualiza a janela
}

void abrirJanela(void){
	glClearColor(0, 0, 0, 1); // RGBA
	gluOrtho2D(-13, 13, -13, 13); // Matriz 26 x 26
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow("Robo Articulado");
	
	base = gluNewQuadric();
	
	glutDisplayFunc(montarRobo);
	
	glutKeyboardFunc(controlarBraco);

	abrirJanela();

	glutMainLoop();
}
