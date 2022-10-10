#include<conio.h>
#include<Windows.h>
#include<C:\Users\steve\source\repos\pruebadedda\glut.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>

using namespace std;

//Definimos las variables para usar el algoritmo DDA
int x_o, y_o, x_f, y_f, Pasos, dy, dx;
double Pendiente;

//Display, funcion que crea la imagen
//Descripcion geometrica de la imagen que se va a usar

void Display() //contiene el algoritmo
{
	//Delta
	dy = y_f - y_o;
	dx = x_f - x_o;

	//Pendiente de la recta
	Pendiente = (dy * 1.0) / (dx * 1.0);

	//Número de pasos
	Pasos = max(dy, dx);

	glClear(GL_COLOR_BUFFER_BIT);//muestra el color que le asignemos
	glColor3f(1, 1, 1);//establecemos el color
	glLoadIdentity();

	//Plano cartesiano
	glLineWidth(5.0);//anchura de la linea
	glColor3f(0.047, 0.7176, 0.949);//color de la linea
	glBegin(GL_LINES);//funcion para graficar lineas
	glVertex2d(-20, 0);//eje abscisas
	glVertex2d(20, 0);
	glVertex2d(0, 20);//eje ordenadas
	glVertex2d(0, -20);
	glEnd();

	//lineas cuadriculadas
	glLineWidth(2.0);//anchura de la linea
	glColor3f(0.0, 1.0, 0.0);//color de lineas
	glBegin(GL_LINES);
	for (int j = 21; j > -20; j--)//lineas horizontales
	{
		glVertex2f(-20, j + 0.5);
		glVertex2f(20, j + 0.5);
	}
	for (int j = 21; j > -20; j--)//lineas verticales
	{
		glVertex2f(j + 0.5, -20);
		glVertex2f(j + 0.5, 20);
	}
	glEnd();

	glPointSize(17);//define tamaño del pixel
	glBegin(GL_POINTS);//funcion para graficar primitivas
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glColor3f(0, 0, 0);

	double xi = x_o * 1.0;
	double yi = y_o * 1.0;
	if (Pendiente < 1)
	{
		for (int k = 0; k < Pasos + 1; k++)
		{
			glVertex2d(xi, round(yi));
			xi++;
			yi = yi + Pendiente;
		}
	}
	else
	{
		for (int k = 0; k < Pasos + 1; k++)
		{
			glVertex2d(round(xi), yi);
			yi++;
			xi = xi + 1.0 / Pendiente;
		}
	}
	glEnd();

	//Grafica de la linea
	glColor3f(1.0, 0.0, 0.0);//color de objeto
	glLineWidth(3.0);//ancho de la linea
	glBegin(GL_LINES);
	glVertex2d(x_o * 1.0, y_o * 1.0);
	glVertex2d(x_f * 1.0, y_f * 1.0);
	glEnd();

	glFlush();//procesa todas las subrutinas de OpenGL

}

void Init()
{
	glClearColor(1, 1, 1, 0);//color de pantalla en blanco
}

//Definir el sistemas de coordenadas para la ventana de visualización
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);//Tipo de proyeccion
	glLoadIdentity();//Asignar la matriz identidad como matriz de proyeccion
	glOrtho(-20, 20, -20, 20, -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

//Funcion principal
int main(int argc, char* argv[])
{
	//Leer los punto inicial y final de la recta a graficas
	cout << "Ingrese x_o: ", cin >> x_o;
	cout << "Ingrese y_o: ", cin >> y_o;
	cout << "Ingrese x_f: ", cin >> x_f;
	cout << "Ingrese y_f: ", cin >> y_f;

	glutInit(&argc, argv);//inicializa el GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//definir el modo de display de nuestra ventana
	glutInitWindowSize(800, 800);//alto y ancho de la ventana
	glutCreateWindow("Algoritmo DDA");//Crear ventana de visualizacion
	Init();//Ejecutamos el procedimiento de inicializacion
	glutDisplayFunc(Display);//Asigna la imagen a la ventana de visualizacion
	//Especifica qué va a contener la ventana de visualizacion
	//Envia los graficos a la ventana de visualizacion
	glutReshapeFunc(reshape);//cambiar el tamaño de la ventana actual
	glutMainLoop();//las ventanas que se hayan creado se muestren en otra pantalla
	return 0;
}