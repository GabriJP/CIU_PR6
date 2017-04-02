#include <stdio.h>
#include <cmath>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Espacio para las variables globales de la ventana
float gl_fovy = 60.0f;
float gl_cerca = 1.0, gl_lejos = 100.0; //cambiar según el proyecto
float gl_center = 7.0;
int w_ancho = 500, w_alto = 500;

// Espacio para otras variables globales
double theta = M_PI_2, phi = 0.0;
double radio = 10.0;

// Espacio para la declaración de funciones
void InitGlew();
void InitGL();
void Display();
void ReshapeSize(int ancho, int alto);
void PosicionRaton(int x, int y);

//main
int main(int argc, char *argv[]){

	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(w_ancho, w_alto);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("OpenGL Practica ");
	InitGlew(); // despues de crear la primera ventana
	InitGL();
	glutDisplayFunc(Display); // registra la funcion de rendering
	glutReshapeFunc(ReshapeSize);
	glutMotionFunc(PosicionRaton);

	glutMainLoop(); // bucle principal

	return 0;
}

void InitGlew(){

	// para poder utilizar trasnparentemente todas las extensiones de OpenGL

	GLenum glew_init = glewInit();
	if (glew_init != GLEW_OK)
	{
		// Problem: glewInit failed, something is seriously wrong.
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_init));
	}
	else
		fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

void setViewport(){
	int ancho = glutGet(GLUT_WINDOW_WIDTH);
	int alto = glutGet(GLUT_WINDOW_HEIGHT);
	glViewport(0, 0, ancho, alto);
}

void setProjection(){
	int ancho = glutGet(GLUT_WINDOW_WIDTH);
	int alto = glutGet(GLUT_WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(gl_fovy, (float)ancho / (float)alto, gl_cerca, gl_lejos);
}

void setModelView(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void InitGL(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	// para cambiar el criterio de lo que se ve. LESS es el de defecto: se ve lo que tiene menor profundidad
	glDepthFunc(GL_LESS);
	// TO DO

	setViewport();
	setProjection();
}


// cambio de dimensiones de la ventana, manteniendo la dimension de los objetos
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
void ReshapeSize(int ancho, int alto){
#pragma clang diagnostic pop
	setViewport();
	setProjection();
	glutPostRedisplay();
}

// función de gestion de ventana
void Display(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra todo lo existente en el framebuffer
	setModelView(); // a partie de aqui empieza poner modelos y transformarlos.
	// TO DO

	glTranslatef(0.0f, 0.0f, -gl_center);

	float x = (float)(radio*sin(theta)*sin(phi));
	float y = (float)(radio*cos(theta));
	float z = (float)(radio*sin(theta)*cos(phi));
	gluLookAt(x, y, z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glutWireTeapot(2.0f);

	glFlush(); // actualiza el framebuffer
	glutSwapBuffers(); // en caso de animacion
}

void PosicionRaton(int x, int y){
	int ancho = glutGet(GLUT_WINDOW_WIDTH);
	int alto = glutGet(GLUT_WINDOW_HEIGHT);

	theta = M_PI*(double)y / (double)alto;
	phi = -M_PI + 2 * M_PI *(double)x / (double)ancho;
	glutPostRedisplay();
}