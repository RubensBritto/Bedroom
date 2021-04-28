#include<Windows.h>
#include <GLFW/glfw3.h>
#include <gl/GLU.h>
#include<iostream>
#include "cores.h"
#include "primitivas.h"
#include "camera.h"


static float lastMousePos = 0.0;
static bool firstTimeMouse = true;
int porta_aberta = 0;
int janela_aberta = 0;
int luz_0 = 0; //spot
int luz_1 = 1; // geral
float angulo_vent = 0;

//display list
unsigned int esferaID[1];
unsigned int cuboID[70];

enum { BRICK, PAINTED, MASK, WOOD, 
		MURO, LENCOL, QUADRO, MADEIRA, 
		TECIDO, TETO, PISO, PORTA, 
		FUNDO_ARMARIO, ARMARIO, TAPETE, 
		RELOGIO, NOTEBOOK, LIVRO, SOFA
};

Textura cuboTextura[30]; //Array para colocar o enum das texturas
camera cam(vec3(0, 0, -45.0)); //Onde a camera inicia

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
	else if (key == GLFW_KEY_P && (action == GLFW_PRESS)) {

		porta_aberta = (porta_aberta + 1) % 2;
	}
	else if (key == GLFW_KEY_J && (action == GLFW_PRESS)) {

		janela_aberta = (janela_aberta + 1) % 2;
	}
	else if (key == GLFW_KEY_L && (action == GLFW_PRESS)) {

		luz_0 = (luz_0 + 1) % 2;
	}
	else if (key == GLFW_KEY_K && (action == GLFW_PRESS)) {

		luz_1 = (luz_1 + 1) % 2;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	float descolamento;
	if (firstTimeMouse) {
		descolamento = 0;
		lastMousePos = (float)xpos;
		firstTimeMouse = false;
	}
	descolamento = (float)xpos - lastMousePos;
	lastMousePos = (float)xpos;
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
	glEnable(GL_TEXTURE_2D);
	
	//Luz
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	float globalAmb[] = { 0.2f,0.2f,0.2f,1.f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

	float light0[3][4]{
		{ 0.2f,0.2f,0.2f,1.f }, // ambiente
		{ 0.8f,0.8f,0.8f,1.f },	// difusa
		{ 1.f,1.f,1.f,1.f },	// especular
	};
	glLightfv(GL_LIGHT0, GL_AMBIENT, &light0[0][0]);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &light0[1][0]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, &light0[2][0]);

	float light1[4][4]{
		{ 0.2f,0.2f,0.2f,1.f }, // ambiente
		{ 0.8f,0.8f,0.8f,1.f },	// difusa
		{ 1.f,1.f,1.f,1.f },	// especular
		{0.0f, 4.0f, -40.f,1.f} // position
	};

	glLightfv(GL_LIGHT1, GL_AMBIENT, &light1[0][0]);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, &light1[1][0]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, &light1[2][0]);
	glLightfv(GL_LIGHT1, GL_POSITION, &light1[3][0]);

	Textura *tex0,*tex1, *tex2, *tex3, *tex4, *tex5, *tex6, *tex7, *tex8, *tex9, *tex10, *tex11, *tex12, *tex13, *tex14, *tex15;
	cuboTextura[MURO].load("imagens/muro_branco.png");
	cuboTextura[WOOD].load("imagens/wood.png");
	cuboTextura[LENCOL].load("imagens/lencol.png");
	cuboTextura[QUADRO].load("imagens/quadro.png");
	cuboTextura[MADEIRA].load("imagens/madeira.png");
	cuboTextura[TECIDO].load("imagens/tecido.png");
	cuboTextura[TETO].load("imagens/teto.png");
	cuboTextura[PISO].load("imagens/piso.png");
	cuboTextura[PORTA].load("imagens/porta.png");
	cuboTextura[FUNDO_ARMARIO].load("imagens/fundo.png");
	cuboTextura[ARMARIO].load("imagens/guardaroupa.png");
	cuboTextura[TAPETE].load("imagens/tapete.png");
	cuboTextura[RELOGIO].load("imagens/relogio.png");
	cuboTextura[NOTEBOOK].load("imagens/notebook.png");
	cuboTextura[LIVRO].load("imagens/livro.png");
	cuboTextura[SOFA].load("imagens/sofa.png");

	
	glClearColor(0.0, 0.0, 0.0,2.0);
	
	esferaID[0] = glGenLists(1);

	// TEMOS 67 OBJETOS
	for (int i = 0; i < 70; i++) {
		if (i == 0)
			cuboID[0] = glGenLists(70);
		else
			cuboID[i] = cuboID[0] + i;
	}

	//inicializar texturas
	tex0 = &cuboTextura[TETO];
	tex1 = &cuboTextura[MURO];
	tex2 = &cuboTextura[WOOD];
	tex3 = &cuboTextura[LENCOL];
	tex4 = &cuboTextura[QUADRO];
	tex5 = &cuboTextura[MADEIRA];
	tex6 = &cuboTextura[TECIDO];
	tex7 = &cuboTextura[PISO];
	tex8 = &cuboTextura[PORTA];
	tex9 = &cuboTextura[ARMARIO]; 
	tex10 = &cuboTextura[FUNDO_ARMARIO];
	tex11 = &cuboTextura[TAPETE];
	tex12 = &cuboTextura[RELOGIO];
	tex13 = &cuboTextura[NOTEBOOK];
	tex14 = &cuboTextura[LIVRO];
	tex15 = &cuboTextura[SOFA];

	//largura, altura, expessura
	desenharCuboTextura(cuboID[0], 90.0f, 50.0f, 1.0f,tex7); //piso
	desenharCuboTextura(cuboID[1], 90.0f, 13.0f, 1.0f, tex1); // parede fundo
	desenharCuboTextura(cuboID[2], 50.0f, 13.0f, 1.0f, tex1); //parede do lado direito
	desenharCuboTextura(cuboID[3], 50.0f, 13.0f, 1.0f, tex1); //parede do lado esquerdo
	desenharCuboTextura(cuboID[4], 30.0f, 50.0f, 0.05f, tex0); //topo

	desenharCuboTextura(cuboID[5], 50.0f, 13.0f, 1.0f, tex1); //parede da frente 1
	desenharCuboTextura(cuboID[6], 4.0f, 5.0f, 1.0f, tex2); // janela 1 -esquerda
	desenharCuboTextura(cuboID[7], 4.0f, 5.0f, 1.0f, tex2); // janela 2 - direita
	desenharCuboTextura(cuboID[8], 6.0f, 10.0f, 1.0f, tex8); //porta
	desenharCuboTextura(cuboID[9], 12.0f, 13.0f, 1.0f, tex1); //parede frente 2
	desenharCuboTextura(cuboID[10], 15.0f, 3.5f, 1.0f, tex1); //parede frente 3
	desenharCuboTextura(cuboID[11], 15.0f, 4.5f, 1.0f, tex1); //parede frente 4
	desenharCuboTextura(cuboID[12], 7.0f, 13.0f, 1.0f, tex1); //parede frente 5
	desenharCuboTextura(cuboID[13], 6.0f, 3.0f, 1.0f, tex1); //parede frente 6
	desenharCuboTextura(cuboID[14], 6.9f, 5.0f, 1.0f, tex1); //parede frente 7

	desenharCubo(cuboID[15], 1.0f, 2.0f, 1.0f, preto); //pé da cama superior direito
	desenharCubo(cuboID[16], 1.0f, 2.0f, 1.0f, preto); //pé da cama superior esquerdo
	desenharCuboTextura(cuboID[17], 10.0f, 5.0f, 1.0f, tex5); //cabeceira
	desenharCubo(cuboID[18], 1.0f, 2.0f, 1.0f, preto); //pé da cama inferior direito
	desenharCubo(cuboID[19], 1.0f, 2.0f, 1.0f, preto); //pé da cama inferior esquerdo
	desenharCubo(cuboID[20], 15.0f, 10.0f, 1.0f, preto); //base da cama
	desenharCuboTextura(cuboID[21], 15.0f, 10.0f, 2.0f, tex3); //colhao

	desenharCuboTextura(cuboID[22], 7.0f, 7.0f, 1.0f, tex4); //quadro

	desenharCubo(cuboID[23], 0.5f, 5.0f, 0.5f, preto); //pé da mesa superior direito
	desenharCubo(cuboID[24], 0.5f, 5.0f, 0.5f, preto); //pé da mesa superior esquerdo
	desenharCubo(cuboID[25], 0.5f, 5.0f, 0.5f, preto); //pé da mesa inferior esquerdo
	desenharCubo(cuboID[26], 0.5f, 5.0f, 0.5f, preto); //pé da mesa inferior direito
	desenharCuboTextura(cuboID[27], 15.0f, 5.0f, 0.357f, tex5); //base da mesa

	desenharCuboTextura(cuboID[28], 3.0f, 3.0f, 3.0f, tex6); //puff

	desenharCubo(cuboID[29], 0.2f, 2.5f, 0.2f, preto); //pé da cadeira superior direito
	desenharCubo(cuboID[30], 0.2f, 2.5f, 0.2f, preto); //pé da cadeira superior esquerdo
	desenharCubo(cuboID[31], 0.2f, 2.5f, 0.2f, preto); //pé da cadeira inferior direito
	desenharCubo(cuboID[32], 0.2f, 2.5f, 0.2f, preto); //pé da cadeira inferior esquerdo
	desenharCubo(cuboID[33], 3.0f, 4.0f, 0.157f, preto); //assento caderia
	desenharCubo(cuboID[34], 4.0f, 3.0f, 0.2f, preto); //encosto caderia

	desenharCuboTextura(cuboID[35], 15.0f, 12.0f, 5.0f, tex10);	//fundo armario
	desenharCuboTextura(cuboID[36], 15.0f, 12.0f, 0.15f, tex9);	// armario


	desenharCuboTextura(cuboID[37], 20.0f, 20.0f, 0.2f, tex11);		//tapete
	desenharCuboTextura(cuboID[38], 2.0f, 2.0f, 0.15f, tex12);	//relogio
	
	desenharCubo(cuboID[39], 2.0f, 10.0f, 0.3f, preto); //perna estante 1
	desenharCubo(cuboID[40], 2.0f, 10.0f, 0.3f, preto); //perna estante 2
	desenharCuboTextura(cuboID[41], 5.0f, 2.0f, 0.15f, tex5); // partileira 1
	desenharCuboTextura(cuboID[42], 5.0f, 2.0f, 0.15f, tex5); // partileira 2
	desenharCuboTextura(cuboID[43], 5.0f, 2.0f, 0.15f, tex5); // partileira 3
	desenharCuboTextura(cuboID[44], 5.0f, 2.0f, 0.1f, tex13); //notebook
	desenharCuboTextura(cuboID[45], 2.0f, 4.0f, 0.3f, tex14); //livro

	desenharCubo(cuboID[46], 3.0f, 3.0f, 8.0f, preto); //comoda
	desenharCuboTextura(cuboID[47], 0.2f, 2.0f, 0.2f, tex5); //pes comoda - superior direito 
	desenharCuboTextura(cuboID[48], 0.2f, 2.0f, 0.2f, tex5); //pes comoda - inferior direito 
	desenharCuboTextura(cuboID[49], 0.2f, 2.0f, 0.2f, tex5); //pes comoda - superior esquerdo 
	desenharCuboTextura(cuboID[50], 0.2f, 2.0f, 0.2f, tex5); //pes comoda - inferior esquerdo 
	desenharCuboTextura(cuboID[51], 0.1f, 0.9f, 6.0f, tex5); //gaveta comoda 1
	desenharCuboTextura(cuboID[52], 0.1f, 0.9f, 6.0f, tex5); //gaveta comoda 2

	desenharCubo(cuboID[53], 2.0f, 0.2f, 2.0f, preto); //base ventilador
	desenharCubo(cuboID[54], 0.2f, 7.0f, 0.2f, preto); //tubo ventilador
	desenharCubo(cuboID[55], 0.2f, 1.0f, 0.2f, preto); //parafuso ventilador
	desenharCubo(cuboID[56], 3.5f, 0.3f, 0.01f, vermelho); //helice 1 ventilador
	desenharCubo(cuboID[57], 3.5f, 0.3f, 0.01f, vermelho); //helice 2 ventilador
	desenharCubo(cuboID[58], 3.5f, 0.3f, 0.01f, vermelho); //helice 3 ventilador
	desenharCubo(cuboID[59], 3.5f, 0.3f, 0.01f, vermelho); //helice 4 ventilador
	
	desenharCuboTextura(cuboID[60], 5.0f, 0.7f, 20.0f, tex6); // assento sofa
	desenharCuboTextura(cuboID[61], 0.2f, 2.0f, 0.2f, tex5); //pe sofa -  superior esquerdo
	desenharCuboTextura(cuboID[62], 0.2f, 2.0f, 0.2f, tex5); //pe sofa - superior direito 
	desenharCuboTextura(cuboID[63], 0.2f, 2.0f, 0.2f, tex5); //pe sofa - inferior esquerdo 
	desenharCuboTextura(cuboID[64], 0.2f, 2.0f, 0.2f, tex5); // pe sofa - inferior direito
	desenharCuboTextura(cuboID[65], 3.0f, 0.7f, 18.0f, tex6); // encosto sofa

	desenharCubo(cuboID[66], 2.0f, 0.089f, 2.0f, preto); //base luminaria
	desenharCubo(cuboID[67], 0.1f, 2.0f, 0.1f, preto); //aste luuminaria
	desenhaEsfera(esferaID[0], branco, 1.5, 10, 10); //luminaria
}

void desenharQuarto() {
	//piso
	glPushMatrix();
	glTranslatef(0.0f, -13.8f, -51.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glCallList(cuboID[0]);
	glPopMatrix();


	//parede fundo
	glPushMatrix();
	glTranslatef(0.0f, -1.0f, -100.0f);
	glCallList(cuboID[1]);
	glPopMatrix();

	//parede lado direito
	glPushMatrix();
	glTranslatef(90.0f, -1.0f, -50.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glCallList(cuboID[2]);
	glPopMatrix();

	//parede lado esquerdo
	glPushMatrix();
	glTranslatef(-90.0f, -1.0f, -50.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glCallList(cuboID[3]);
	glPopMatrix();

	//topo
	glPushMatrix();
	glTranslatef(0.0f, 12.3f, -49.5f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glScalef(3.0f, 1.0f, 3.0f);
	glCallList(cuboID[4]);
	glPopMatrix();

	//PARTES DAS PAREDES DA PORTA E SALA

	//parede frente 1
	glPushMatrix();
	glTranslatef(40.0f, -1.0f, 1.0f);
	glCallList(cuboID[5]);
	glPopMatrix();

	//parede frente 2
	glPushMatrix();
	glTranslatef(-52.0f, -1.0f, 1.0f);
	glCallList(cuboID[9]);
	glPopMatrix();

	//parede frente 3
	glPushMatrix();
	glTranslatef(-25.0f, 8.5f, 1.0f);
	glCallList(cuboID[10]);
	glPopMatrix();

	//parede frente 4
	glPushMatrix();
	glTranslatef(-25.0f, -9.5f, 1.0f);
	glCallList(cuboID[11]);
	glPopMatrix();

	//parede frente 5
	glPushMatrix();
	glTranslatef(-83.0f, -1.0f, 1.0f);
	glCallList(cuboID[12]);
	glPopMatrix();

	//parede frente 6
	glPushMatrix();
	glTranslatef(-70.0f, 9.0f, 1.0f);
	glCallList(cuboID[13]);
	glPopMatrix();

	//parede frente 7
	glPushMatrix();
	glTranslatef(-17.0f, 0.0f, 1.0f);
	glCallList(cuboID[14]);
	glPopMatrix();
}

void desenharPortasEJanelas() {
	//janela 1
	glPushMatrix();
	if (janela_aberta == 0) {
		glTranslatef(-28.0f, 0.0f, 1.0f);
	}
	else {
		glTranslatef(-25.0f, 0.0f, 3.0f);
		glRotated(90.0f, 0.0f, -1.0f, 0.0f);
	}
	glCallList(cuboID[6]);
	glPopMatrix();

	//janela 2
	glPushMatrix();
	if (janela_aberta == 0) {
		glTranslatef(-36.0f, 0.0f, 1.0f);
	}
	else {
		glTranslatef(-39.0f, 0.0f, 3.0f);
		glRotated(90.0f, 0.0f, -1.0f, 0.0f);
	}
	glCallList(cuboID[7]);
	glPopMatrix();

	//porta

	glPushMatrix();

	if (porta_aberta == 0) {
		glTranslatef(-70.0f, -4.0f, 1.0f);
	}
	else {
		glTranslatef(-75.0f, -4.0f, 6.0f);
		glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	}

	glCallList(cuboID[8]);
	glPopMatrix();
}

void desenharObjObrigatorios() {

	// cama, mesa, cadeira, ventilador e quadro;

	// pes da cama - superior direito
	glPushMatrix();
	glTranslatef(85.0f, -10.0f, -31.0f);
	glCallList(cuboID[15]);
	glPopMatrix();

	//pes da cama - superior esquedo
	glPushMatrix();
	glTranslatef(85.0f, -10.0f, -49.0f);
	glCallList(cuboID[16]);
	glPopMatrix();

	//cabeceira
	glPushMatrix();
	glTranslatef(85.0f, -3.0f, -40.0f);
	glRotated(90.0, 0.0, 1.0, 0.0);
	glCallList(cuboID[17]);
	glPopMatrix();


	//pes da cama - inferior direito
	glPushMatrix();
	glTranslatef(55.0f, -10.0f, -31.0f);
	glCallList(cuboID[18]);
	glPopMatrix();

	//pes da cama - inferior esquerdo
	glPushMatrix();
	glTranslatef(55.0f, -10.0f, -49.0f);
	glCallList(cuboID[19]);
	glPopMatrix();

	//base cama
	glPushMatrix();
	glTranslatef(69.0f, -7.0f, -40.0f);
	glRotated(90.0f, 1.0f, 0.0f, 0.0f);
	glCallList(cuboID[20]);
	glPopMatrix();

	//colhão
	glPushMatrix();
	glTranslatef(69.0f, -5.0f, -40.0f);
	glRotated(90.0f, 1.0f, 0.0f, 0.0f);
	glCallList(cuboID[21]);
	glPopMatrix();

	//quadro
	glPushMatrix();
	glTranslatef(0.0f, 3.0f, -99.0f);
	glCallList(cuboID[22]);
	glPopMatrix();

	//pes da mesa - superior direito
	glPushMatrix();
	glTranslatef(85.0f, -10.0f, -97.0f);
	glCallList(cuboID[23]);
	glPopMatrix();

	//pes da mesa - superior esquerdo
	glPushMatrix();
	glTranslatef(65.0f, -10.0f, -97.0f);
	glCallList(cuboID[24]);
	glPopMatrix();

	//pes da mesa - inferior esquerdo
	glPushMatrix();
	glTranslatef(65.0f, -10.0f, -89.0f);
	glCallList(cuboID[25]);
	glPopMatrix();

	//pes da mesa - inferior dirito
	glPushMatrix();
	glTranslatef(85.0f, -10.0f, -89.0f);
	glCallList(cuboID[26]);
	glPopMatrix();


	//base da mesa
	glPushMatrix();
	glTranslatef(75.0f, -5.0f, -93.0f);
	glRotated(90.0f, 1.0f, 0.0f, 0.0f);
	glCallList(cuboID[27]);
	glPopMatrix();

	//pes da cadeira - superior direito
	glPushMatrix();
	glTranslatef(77.0f, -10.0f, -87.0f);
	glCallList(cuboID[29]);
	glPopMatrix();

	//pes da cadeira - superior esquerdo
	glPushMatrix();
	glTranslatef(72.0f, -10.0f, -87.0f);
	glCallList(cuboID[30]);
	glPopMatrix();

	//pes da cadeira - inferior direito
	glPushMatrix();
	glTranslatef(77.0f, -10.0f, -83.0f);
	glCallList(cuboID[31]);
	glPopMatrix();


	//pes da cadeira - inferior esquerdo
	glPushMatrix();
	glTranslatef(72.0f, -10.0f, -83.0f);
	glCallList(cuboID[32]);
	glPopMatrix();

	//assento da cadeira
	glPushMatrix();
	glTranslatef(74.5f, -7.3f, -85.0f);
	glRotated(90.0f, 1.0f, 0.0f, 0.0f);
	glCallList(cuboID[33]);
	glPopMatrix();


	//encosto da cadeira
	glPushMatrix();
	glTranslatef(74.5f, -3.7f, -80.9f);
	glRotated(90.0f, 0.0f, 0.0f, 1.0f);
	glCallList(cuboID[34]);
	glPopMatrix();


	//base ventilador
	glPushMatrix();
	glTranslatef(-80.0f, -12.0f, -10.0f);
	glCallList(cuboID[53]);
	glPopMatrix();

	//tubo ventilador
	glPushMatrix();
	glTranslatef(-80.0f, -6.0f, -10.0f);
	glCallList(cuboID[54]);
	glPopMatrix();

	//parafuso ventilador
	glPushMatrix();
	glTranslatef(-79.0f, 0.0f, -10.0f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glCallList(cuboID[55]);
	glPopMatrix();

	//helice 1 ventilador
	glPushMatrix();
	glTranslatef(-78.0f, 0.0f, -10.0f);
	glRotatef(angulo_vent, -1.0f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glCallList(cuboID[56]);
	glPopMatrix();

	//helice 2 ventilador
	glPushMatrix();
	glTranslatef(-77.9f, 0.0f, -10.0f);
	glRotatef(angulo_vent, -1.0f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 1.0f);
	glCallList(cuboID[57]);
	glPopMatrix();

	//helice 3 ventilador
	glPushMatrix();
	glTranslatef(-77.8f, 0.0f, -10.0f);
	glRotatef(angulo_vent, -1.0f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, -1.0f);
	glCallList(cuboID[58]);
	glPopMatrix();

	//helice 4 ventilador
	glPushMatrix();
	glTranslatef(-77.7f, 0.0f, -10.0f);
	glRotatef(angulo_vent, -1.0f, 0.0f, 0.0f);
	glRotatef(120.0f, 1.0f, 1.0f, 1.0f);
	glCallList(cuboID[59]);
	glPopMatrix();

	angulo_vent += 0.5;
	if (angulo_vent >= 360) {
		angulo_vent = 0.0;
	}

	// lampada luminaria
	glPushMatrix();
	glTranslatef(70.0f, 0.4f, -95.0f);
	glCallList(esferaID[0]);
	glPopMatrix();
	float position_light[] = { 70.f, 0.4f, -95.f,1.f };
	float direction_light[] = { 0.0f, -1.0f, 0.0f,1.f};
	glLightfv(GL_LIGHT0, GL_POSITION, position_light);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction_light);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80.0);

	// base luminara
	glPushMatrix();
	glTranslatef(70.0f, -4.5f, -95.0f);
	glCallList(cuboID[66]);
	glPopMatrix();

	// aste luminara
	glPushMatrix();
	glTranslatef(70.0f, -3.0f, -95.0f);
	glCallList(cuboID[67]);
	glPopMatrix();
}

void desenharObjExtras() {

	// puf
	glPushMatrix();
	glTranslatef(50.0f, -9.0f, -93.0f);
	glCallList(cuboID[28]);
	glPopMatrix();

	//fundo armario
	glPushMatrix();
	glTranslatef(-45.0f, -1.0f, -94.0f);
	glCallList(cuboID[35]);
	glPopMatrix();
	
	//armario
	glPushMatrix();
	glTranslatef (- 45.0f, -1.0f, -89.1f);
	glCallList(cuboID[36]);
	glPopMatrix();

	//tapete
	glPushMatrix();
	glTranslatef(0.0f, -12.0f, -45.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glCallList(cuboID[37]);
	glPopMatrix();

	//relogio
	glPushMatrix();
	glTranslatef(88.0f, 9.0f, -40.0f);
	glRotatef(90.0f, 0.0f, -1.0f, 0.0f);
	glCallList(cuboID[38]);
	glPopMatrix();

	//perna estante 1
	glPushMatrix();
	glTranslatef(30.2f, -5.0f, -5.0f);
	glRotated(180.0f, 1.0f, 0.0f, 1.0f);
	glCallList(cuboID[39]);
	glPopMatrix();

	//perna estante 2
	glPushMatrix();
	glTranslatef(19.8f, -5.0f, -5.0f);
	glRotated(180.0f, 1.0f, 0.0f, 1.0f);
	glCallList(cuboID[40]);
	glPopMatrix();

	//partileira 1 estante
	glPushMatrix();
	glTranslatef(25.0f, -8.0f, -5.0f);
	glRotated(90.0f, 1.0f, 0.0f, 0.0f);
	glCallList(cuboID[41]);
	glPopMatrix();

	//partileira 2 estante
	glPushMatrix();
	glTranslatef(25.0f, -2.0f, -5.0f);
	glRotated(90.0f, 1.0f, 0.0f, 0.0f);
	glCallList(cuboID[42]);
	glPopMatrix();

	//partileira 3 estante
	glPushMatrix();
	glTranslatef(25.0f, 5.0f, -5.0f);
	glRotated(90.0f, 1.0f, 0.0f, 0.0f);
	glCallList(cuboID[43]);
	glPopMatrix();

	//notebook
	glPushMatrix();
	glTranslatef(80.0f, -4.5f, -93.0f);
	glRotated(90.0f, 1.0f, 0.0f, 0.0f);
	glCallList(cuboID[44]);
	glPopMatrix();

	
	//livro
	glPushMatrix();
	glTranslatef(65.0f, -4.5f, -93.0f);
	glRotated(90.0f, 1.0f, 0.0f, 0.0f);
	glCallList(cuboID[45]);
	glPopMatrix();

	//comoda
	glPushMatrix();
	glTranslatef(80.0f, -6.0f, -15.0f);
	glCallList(cuboID[46]);
	glPopMatrix();

	//comoda pes direito superior
	glPushMatrix();
	glTranslatef(85.0f, -11.0f, -9.0f);
	glRotated(15.0f, -1.0f, 0.0f, 0.0f);
	glCallList(cuboID[47]);
	glPopMatrix();

	//comoda pes direito inferior
	glPushMatrix();
	glTranslatef(80.0f, -11.0f, -9.0f);
	glRotated(15.0f, -1.0f, 0.0f, 0.0f);
	glCallList(cuboID[48]);
	glPopMatrix();

	//comoda pes esquerdo superior
	glPushMatrix();
	glTranslatef(85.0f, -11.0f, -20.0f);
	glRotated(15.0f, 1.0f, 0.0f, 0.0f);
	glCallList(cuboID[49]);
	glPopMatrix();

	//comoda pes direito inferior
	glPushMatrix();
	glTranslatef(80.0f, -11.0f, -20.0f);
	glRotated(15.0f, 1.0f, 0.0f, 0.0f);
	glCallList(cuboID[50]);
	glPopMatrix();

	//gaveta comoda - 1
	glPushMatrix();
	glTranslatef(76.9f, -4.5f, -15.0f);
	glCallList(cuboID[51]);
	glPopMatrix();

	//gaveta comoda - 2
	glPushMatrix();
	glTranslatef(76.9f, -7.0f, -15.0f);
	glCallList(cuboID[52]);
	glPopMatrix();

	//assento sofa
	glPushMatrix();
	glTranslatef(-80.0f, -8.4f, -50.0f);
	glCallList(cuboID[60]);
	glPopMatrix();

	//sofa pes superior esquerdo
	glPushMatrix();
	glTranslatef(-85.0f, -11.0f, -35.0f);
	glRotated(15.0f, -1.0f, 0.0f, 0.0f);
	glCallList(cuboID[61]);
	glPopMatrix();

	//sofa pes superior direito
	glPushMatrix();
	glTranslatef(-85.0f, -11.0f, -67.0f);
	glRotated(15.0f, 1.0f, 0.0f, 0.0f);
	glCallList(cuboID[62]);
	glPopMatrix();

	//sofa pes inferior esquerdo
	glPushMatrix();
	glTranslatef(-75.0f, -11.0f, -35.0f);
	glRotated(15.0f, -1.0f, 0.0f, 0.0f);
	glCallList(cuboID[63]);
	glPopMatrix();

	//sofa pe inferior direito
	glPushMatrix();
	glTranslatef(-75.0f, -11.0f, -67.0f);
	glRotated(15.0f, 1.0f, 0.0f, 0.0f);
	glCallList(cuboID[64]);
	glPopMatrix();

	//encosto sofa
	glPushMatrix();
	glTranslatef(-84.5f, -4.7f, -50.0f);
	glRotated(90.0f, 0.0f, 0.0f, 1.0f);
	glCallList(cuboID[65]);
	glPopMatrix();
}
void desenha(GLFWwindow* window) {

	glLoadIdentity();
	cam.ativar();

	//desenha os itens do quarto
	desenharQuarto();
	desenharPortasEJanelas();
	desenharObjObrigatorios();
	desenharObjExtras();

	if (luz_0 == 1) {
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}
	if (luz_1 == 1) {
		glEnable(GL_LIGHT1);
	}
	else {
		glDisable(GL_LIGHT1);
	}
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
	window = glfwCreateWindow(LARGURA, ALTURA, "Bedroom", NULL, NULL);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// -- inicio
	init(window);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		/* Poll for and process events */
		glfwPollEvents();
		
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		int largura, altura;
		glfwGetFramebufferSize(window, &largura, &altura);

		redimensionar(largura, altura);
		desenha(window);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);


	}
	//glDeleteLists(cuboID[0], 5);//deletar esferas(variavel, range)
	glfwTerminate();
	return 0;
}