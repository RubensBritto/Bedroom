#include<Windows.h>
#include <GLFW/glfw3.h>
#include <gl/GLU.h>
#include<iostream>
#include "cores.h"
#include "primitivas.h"
#include "camera.h"


static float angulo = 0.0;
static float lastMousePos = 0.0;
static bool firstTimeMouse = true;

//display list
unsigned int esferaID[3];
unsigned int cuboID[30];
camera cam(vec3(-100, 0, 0));

void teclado_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)) {//frente
		cam.frente();
	}
	else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)) {//tras
		cam.atras();
	}
	else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)) {//esquerda
		cam.esquerda();
	}
	else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)) {//direita
		cam.direita();
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	float descolamento;
	if (firstTimeMouse) {
		descolamento = 0;
		lastMousePos = xpos;
		firstTimeMouse = false;
	}
	descolamento = xpos - lastMousePos;
	lastMousePos = xpos;
	cam.updateYaw(descolamento);
	cam.update();
}


void init(GLFWwindow* window) {

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, teclado_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMaximizeWindow(window);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);
cuboID[0] = glGenLists(30);
cuboID[1] = cuboID[0] + 1;
cuboID[2] = cuboID[0] + 2;
cuboID[3] = cuboID[0] + 3;
cuboID[4] = cuboID[0] + 4;
cuboID[5] = cuboID[0] + 5;
cuboID[6] = cuboID[0] + 6;
cuboID[7] = cuboID[0] + 7;
cuboID[8] = cuboID[0] + 8;
cuboID[9] = cuboID[0] + 9;
cuboID[10] = cuboID[0] + 10;
cuboID[11] = cuboID[0] + 11;
cuboID[12] = cuboID[0] + 12;
cuboID[13] = cuboID[0] + 13;
cuboID[14] = cuboID[0] + 14;

//largura, altura, expessura
desenharCubo(cuboID[0], 30.0, 1.0, 30.0, amarelo); //piso
desenharCubo(cuboID[1], 30.0, 13.0, 1.0, vermelho); // parede fundo
desenharCubo(cuboID[2], 30.0, 13.0, 1.0, verde); //parede do lado direito
desenharCubo(cuboID[3], 30.0, 13.0, 1.0, branco); //parede do lado esquerdo
desenharCubo(cuboID[4], 30.0, 1.0, 30.0, branco_gelo); //topo
desenharCubo(cuboID[5], 15.0, 13.0, 1.0, branco_gelo); //parede da frente 1
desenharCubo(cuboID[6], 2.0, 4.0, 1.0, cinza); // janela 1
desenharCubo(cuboID[7], 2.0, 4.0, 1.0, cinza_escuro); // janela 2
desenharCubo(cuboID[8], 6.0, 10.0, 1.0, cinza_escuro); //portar
desenharCubo(cuboID[9], 3.0, 13.0, 1.0, branco_gelo); //parede fundo 2
desenharCubo(cuboID[10], 4.0, 4.5, 1.0, branco_gelo); //parede fundo 3
desenharCubo(cuboID[11], 4.0, 4.5, 1.0, branco_gelo); //parede fundo 4
desenharCubo(cuboID[12], 2.0, 10.0, 1.0, branco_gelo); //parede fundo 5
desenharCubo(cuboID[13], 8.0, 3.0, 1.0, branco_gelo); //parede fundo 5
}

void desenha(float dt, GLFWwindow* window) {

	float veloc_angular = 60.0 * dt; //60 graus por segundo

	glLoadIdentity();
	cam.ativar();

	//glCallList(terrenoID);

	//piso
	glPushMatrix();
	glTranslatef(0.0, -11.0, -50.0);
	glCallList(cuboID[0]);
	glPopMatrix();


	//parede fundo
	glPushMatrix();
	glTranslatef(0.0, 1.0, -80.0);
	glCallList(cuboID[1]);
	glPopMatrix();

	//parede lado direito
	glPushMatrix();
	glTranslatef(30.0, 1.0, -50.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glCallList(cuboID[2]);
	glPopMatrix();

	//parede lado esquerdo
	glPushMatrix();
	glTranslatef(-30.0, 1.0, -50.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glCallList(cuboID[3]);
	glPopMatrix();

	//topo
	glPushMatrix();
	glTranslatef(0.0, 15.0, -50.0);
	glCallList(cuboID[4]);
	glPopMatrix();


	//parede frente 1
	glPushMatrix();
	glTranslatef(15.0, 1.0, -20.0);
	glCallList(cuboID[5]);
	glPopMatrix();

	//janela 1
	glPushMatrix();
	glTranslatef(-2.0, 1.0, -20.0);
	glCallList(cuboID[6]);
	glPopMatrix();

	//janela 2
	glPushMatrix();
	glTranslatef(-6.0, 1.0, -20.0);
	glCallList(cuboID[7]);
	glPopMatrix();

	//portar
	glPushMatrix();
	glTranslatef(-20.0, -2.0, -20.0);
	glCallList(cuboID[8]);
	glPopMatrix();
	
	/* Abrir e fechar as portas
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS){
		glPushMatrix();
		glTranslatef(-20.0, -2.0, -25.0);
		glCallList(cuboID[8]);
		glPopMatrix();
	}
	*/
	
	//parede frente 2
	glPushMatrix();
	glTranslatef(-11.0, 1.0, -20.0);
	glCallList(cuboID[9]);
	glPopMatrix();
	
	//parede frente 3
	glPushMatrix();
	glTranslatef(-4.0, 9.5, -20.0);
	glCallList(cuboID[10]);
	glPopMatrix();

	//parede frente 3
	glPushMatrix();
	glTranslatef(-4.0, -7.5, -20.0);
	glCallList(cuboID[11]);
	glPopMatrix();

	//parede frente 4
	glPushMatrix();
	glTranslatef(-28.0, -2.0, -20.0);
	glCallList(cuboID[12]);
	glPopMatrix();

	//parede frente 5
	glPushMatrix();
	glTranslatef(-22.0, 11, -20.0);
	glCallList(cuboID[13]);
	glPopMatrix();

}
void redimensionar(int w, int h) {
	glViewport(0, 0, w, h);
	float aspect = (float)w / (float)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 500.0);

	glMatrixMode(GL_MODELVIEW);
}

int main(void)
{
	const int LARGURA = 800;
	const int ALTURA = 600;
	GLFWwindow* window;

	/* Initialize the library */
	glfwInit();


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(LARGURA, ALTURA, "Desenhar Esfera", NULL, NULL);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// -- inicio
	init(window);


	float valor = 0.0;
	float lasTime = 0.0;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		float currentTime = (float)glfwGetTime();
		float dt = currentTime - lasTime;
		lasTime = currentTime;

		/* Poll for and process events */
		glfwPollEvents();
		
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int largura, altura;
		glfwGetFramebufferSize(window, &largura, &altura);

		redimensionar(largura, altura);
		desenha(dt, window);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);


	}
	//glDeleteLists(cuboID[0], 5);//deletar esferas(variavel, range)
	glfwTerminate();
	return 0;
}