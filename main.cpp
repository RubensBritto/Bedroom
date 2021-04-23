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
float angulo_vent = 0;

//display list
unsigned int esferaID[3];
unsigned int cuboID[100];

enum { BRICK, PAINTED, MASK, WOOD, 
		MURO, LENCOL, QUADRO, MADEIRA, 
		TECIDO, TETO, PISO, PORTA, 
		PORTA_ARMARIO, ARMARIO, TAPETE, 
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
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
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
	cuboTextura[PORTA_ARMARIO].load("imagens/porta_armario.png");
	cuboTextura[ARMARIO].load("imagens/armario.png");
	cuboTextura[TAPETE].load("imagens/tapete.png");
	cuboTextura[RELOGIO].load("imagens/relogio.png");
	cuboTextura[NOTEBOOK].load("imagens/notebook.png");
	cuboTextura[LIVRO].load("imagens/livro.png");
	cuboTextura[SOFA].load("imagens/sofa.png");
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//glEnable(GL_DEPTH_TEST);
	cuboID[0] = glGenLists(100);
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
	cuboID[15] = cuboID[0] + 15;
	cuboID[16] = cuboID[0] + 16;
	cuboID[17] = cuboID[0] + 17;
	cuboID[18] = cuboID[0] + 18;
	cuboID[19] = cuboID[0] + 19;
	cuboID[20] = cuboID[0] + 20;
	cuboID[21] = cuboID[0] + 21;
	cuboID[22] = cuboID[0] + 22;
	cuboID[23] = cuboID[0] + 23;
	cuboID[24] = cuboID[0] + 24;
	cuboID[25] = cuboID[0] + 25;
	cuboID[26] = cuboID[0] + 26;
	cuboID[27] = cuboID[0] + 27;
	cuboID[28] = cuboID[0] + 28;
	cuboID[29] = cuboID[0] + 29;
	cuboID[30] = cuboID[0] + 30;
	cuboID[31] = cuboID[0] + 31;
	cuboID[32] = cuboID[0] + 32;
	cuboID[33] = cuboID[0] + 33;
	cuboID[34] = cuboID[0] + 34;
	cuboID[35] = cuboID[0] + 35;
	cuboID[36] = cuboID[0] + 36;
	cuboID[37] = cuboID[0] + 37;
	cuboID[38] = cuboID[0] + 38;
	cuboID[39] = cuboID[0] + 39;
	cuboID[40] = cuboID[0] + 40;
	cuboID[41] = cuboID[0] + 41;
	cuboID[42] = cuboID[0] + 42;
	cuboID[43] = cuboID[0] + 43;
	cuboID[44] = cuboID[0] + 44;
	cuboID[45] = cuboID[0] + 45;
	cuboID[46] = cuboID[0] + 46;
	cuboID[47] = cuboID[0] + 47;
	cuboID[48] = cuboID[0] + 48;
	cuboID[49] = cuboID[0] + 49;
	cuboID[50] = cuboID[0] + 50;
	cuboID[51] = cuboID[0] + 51;
	cuboID[52] = cuboID[0] + 52;
	cuboID[53] = cuboID[0] + 53;
	cuboID[54] = cuboID[0] + 54;
	cuboID[55] = cuboID[0] + 55;
	cuboID[56] = cuboID[0] + 56;
	cuboID[57] = cuboID[0] + 57;
	cuboID[58] = cuboID[0] + 58;
	cuboID[59] = cuboID[0] + 59;
	cuboID[60] = cuboID[0] + 60;
	cuboID[61] = cuboID[0] + 61;
	cuboID[62] = cuboID[0] + 62;
	cuboID[63] = cuboID[0] + 63;
	cuboID[64] = cuboID[0] + 64;
	cuboID[65] = cuboID[0] + 65;
	cuboID[66] = cuboID[0] + 66;
	cuboID[67] = cuboID[0] + 67;


	
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
	tex9 = &cuboTextura[PORTA_ARMARIO];
	tex10 = &cuboTextura[ARMARIO];
	tex11 = &cuboTextura[TAPETE];
	tex12 = &cuboTextura[RELOGIO];
	tex13 = &cuboTextura[NOTEBOOK];
	tex14 = &cuboTextura[LIVRO];
	tex15 = &cuboTextura[SOFA];

	//largura, altura, expessura
	desenharCuboTextura(cuboID[0], 90.0, 50.0, 1.0,tex7); //piso
	desenharCuboTextura(cuboID[1], 90.0, 13.0, 1.0, tex1); // parede fundo
	desenharCuboTextura(cuboID[2], 50.0, 13.0, 1.0, tex1); //parede do lado direito
	desenharCuboTextura(cuboID[3], 50.0, 13.0, 1.0, tex1); //parede do lado esquerdo
	desenharCuboTextura(cuboID[4], 30.0, 50.0, 0.05, tex0); //topo

	desenharCuboTextura(cuboID[5], 50.0, 13.0, 1.0, tex1); //parede da frente 1
	desenharCuboTextura(cuboID[6], 4.0, 5.0, 1.0, tex2); // janela 1 -esquerda
	desenharCuboTextura(cuboID[7], 4.0, 5.0, 1.0, tex2); // janela 2 - direita
	desenharCuboTextura(cuboID[8], 6.0, 10.0, 1.0, tex8); //porta
	desenharCuboTextura(cuboID[9], 12.0, 13.0, 1.0, tex1); //parede frente 2
	desenharCuboTextura(cuboID[10], 15.0, 3.5, 1.0, tex1); //parede frente 3
	desenharCuboTextura(cuboID[11], 15.0, 4.5, 1.0, tex1); //parede frente 4
	desenharCuboTextura(cuboID[12], 7.0, 13.0, 1.0, tex1); //parede frente 5
	desenharCuboTextura(cuboID[13], 6.0, 3.0, 1.0, tex1); //parede frente 6
	desenharCuboTextura(cuboID[14], 6.9, 5.0, 1.0, tex1); //parede frente 7

	desenharCubo(cuboID[15], 1.0, 2.0, 1.0, preto); //pé da cama superior direito
	desenharCubo(cuboID[16], 1.0, 2.0, 1.0, preto); //pé da cama superior esquerdo
	desenharCuboTextura(cuboID[17], 10.0, 5.0, 1.0, tex5); //cabeceira
	desenharCubo(cuboID[18], 1.0, 2.0, 1.0, preto); //pé da cama inferior direito
	desenharCubo(cuboID[19], 1.0, 2.0, 1.0, preto); //pé da cama inferior esquerdo
	desenharCubo(cuboID[20], 15.0, 10.0, 1.0, preto); //base da cama
	desenharCuboTextura(cuboID[21], 15.0, 10.0, 2.0, tex3); //colhao

	desenharCuboTextura(cuboID[22], 7.0, 7.0, 1.0, tex4); //quadro

	desenharCubo(cuboID[23], 0.5, 5.0, 0.5, preto); //pé da mesa superior direito
	desenharCubo(cuboID[24], 0.5, 5.0, 0.5, preto); //pé da mesa superior esquerdo
	desenharCubo(cuboID[25], 0.5, 5.0, 0.5, preto); //pé da mesa inferior esquerdo
	desenharCubo(cuboID[26], 0.5, 5.0, 0.5, preto); //pé da mesa inferior direito
	desenharCuboTextura(cuboID[27], 15.0, 5.0, 0.357, tex5); //base da mesa

	desenharCuboTextura(cuboID[28], 3.0, 3.0, 3.0, tex6); //puff

	desenharCubo(cuboID[29], 0.2, 2.5, 0.2, preto); //pé da cadeira superior direito
	desenharCubo(cuboID[30], 0.2, 2.5, 0.2, preto); //pé da cadeira superior esquerdo
	desenharCubo(cuboID[31], 0.2, 2.5, 0.2, preto); //pé da cadeira inferior direito
	desenharCubo(cuboID[32], 0.2, 2.5, 0.2, preto); //pé da cadeira inferior esquerdo
	desenharCubo(cuboID[33], 3.0, 4.0, 0.157, preto); //assento caderia
	desenharCubo(cuboID[34], 4.0, 3.0, 0.2, preto); //encosto caderia

	desenharCuboTextura(cuboID[35], 9, 12, 5.0, tex10);	//armario
	desenharCuboTextura(cuboID[36], 3.5, 9.0, 0.5, tex9);		//porta do armario 1
	desenharCuboTextura(cuboID[37], 3.5, 9.0, 0.5, tex9);		//porta do armario 2
	desenharCuboTextura(cuboID[38], 20.0, 20.0, 0.2, tex11);		//tapete
	desenharCuboTextura(cuboID[39], 2.0, 2.0, 0.15, tex12);	//relogio
	
	desenharCubo(cuboID[40], 2.0, 10.0, 0.3, preto); //perna estante 1
	desenharCubo(cuboID[41], 2.0, 10.0, 0.3, preto); //perna estante 2
	desenharCuboTextura(cuboID[42], 5.0, 2.0, 0.15, tex5); // partileira 1
	desenharCuboTextura(cuboID[43], 5.0, 2.0, 0.15, tex5); // partileira 2
	desenharCuboTextura(cuboID[44], 5.0, 2.0, 0.15, tex5); // partileira 3
	desenharCuboTextura(cuboID[45], 5.0, 2.0, 0.1, tex13); //notebook
	desenharCuboTextura(cuboID[46], 2.0, 4.0, 0.3, tex14); //livro

	desenharCubo(cuboID[47], 3.0, 3.0, 8.0, preto); //comoda
	desenharCuboTextura(cuboID[48], 0.2, 2.0, 0.2, tex5); //pes comoda - superior direito 
	desenharCuboTextura(cuboID[49], 0.2, 2.0, 0.2, tex5); //pes comoda - inferior direito 
	desenharCuboTextura(cuboID[50], 0.2, 2.0, 0.2, tex5); //pes comoda - superior esquerdo 
	desenharCuboTextura(cuboID[51], 0.2, 2.0, 0.2, tex5); //pes comoda - inferior esquerdo 
	desenharCuboTextura(cuboID[52], 0.1, 0.9, 6.0, tex5); //gaveta comoda 1
	desenharCuboTextura(cuboID[53], 0.1, 0.9, 6.0, tex5); //gaveta comoda 2

	desenharCubo(cuboID[54], 2.0, 0.2, 2.0, preto); //base ventilador
	desenharCubo(cuboID[55], 0.2, 7.0, 0.2, preto); //tubo ventilador
	desenharCubo(cuboID[56], 0.2, 1.0, 0.2, preto); //parafuso ventilador
	desenharCubo(cuboID[57], 3.5, 0.3, 0.01, vermelho); //helice 1 ventilador
	desenharCubo(cuboID[58], 3.5, 0.3, 0.01, vermelho); //helice 2 ventilador
	desenharCubo(cuboID[59], 3.5, 0.3, 0.01, vermelho); //helice 3 ventilador
	desenharCubo(cuboID[60], 3.5, 0.3, 0.01, vermelho); //helice 4 ventilador
	
	desenharCuboTextura(cuboID[61], 5.0, 0.7, 20.0, tex6); // assento sofa
	desenharCuboTextura(cuboID[62], 0.2, 2.0, 0.2, tex5); //pe sofa -  superior esquerdo
	desenharCuboTextura(cuboID[63], 0.2, 2.0, 0.2, tex5); //pe sofa - superior direito 
	desenharCuboTextura(cuboID[64], 0.2, 2.0, 0.2, tex5); //pe sofa - inferior esquerdo 
	desenharCuboTextura(cuboID[65], 0.2, 2.0, 0.2, tex5); // pe sofa - inferior direito
	desenharCuboTextura(cuboID[66], 3.0, 0.7, 18.0, tex6); // encosto sofa
}

void desenha(GLFWwindow* window) {

	glLoadIdentity();
	cam.ativar();

	//piso
	glPushMatrix();
	glTranslatef(0.0, -13.8, -51.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[0]);
	glPopMatrix();


	//parede fundo
	glPushMatrix();
	glTranslatef(0.0, -1.0, -100.0);
	glCallList(cuboID[1]);
	glPopMatrix();

	//parede lado direito
	glPushMatrix();
	glTranslatef(90.0, -1.0, -50.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glCallList(cuboID[2]);
	glPopMatrix();

	//parede lado esquerdo
	glPushMatrix();
	glTranslatef(-90.0, -1.0, -50.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glCallList(cuboID[3]);
	glPopMatrix();

	//topo
	glPushMatrix();
	glTranslatef(0.0, 12.3, -49.5);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glScalef(3.0, 1.0, 3.0);
	glCallList(cuboID[4]);
	glPopMatrix();


	//parede frente 1
	glPushMatrix();
	glTranslatef(40.0, -1.0, 1.0);
	glCallList(cuboID[5]);
	glPopMatrix();

	//janela 1
	glPushMatrix();
	if (janela_aberta == 0) {
		glTranslatef(-28.0, 0.0, 1.0);
	}
	else {
		glTranslatef(-25.0, 0.0,3.0);
		glRotated(90, 0, -1, 0);
	}
	glCallList(cuboID[6]);
	glPopMatrix();

	//janela 2
	glPushMatrix();
	if (janela_aberta == 0) {
		glTranslatef(-36.0, 0.0, 1.0);		
	}
	else {
		glTranslatef(-39.0, 0.0, 3.0);
		glRotated(90, 0, -1, 0);
	}
	glCallList(cuboID[7]);
	glPopMatrix();

	//porta

	glPushMatrix();

	if (porta_aberta == 0) {
	glTranslatef(-70.0, -4.0, 1.0);
	}
	else {
		glTranslatef(-75.0, -4.0, 6.0);
		glRotated(90.0, 0, 1, 0);
	}
	
	glCallList(cuboID[8]);
	glPopMatrix();
	
	//parede frente 2
	glPushMatrix();
	glTranslatef(-52.0, -1.0, 1.0);
	glCallList(cuboID[9]);
	glPopMatrix();
	
	//parede frente 3
	glPushMatrix();
	glTranslatef(-25.0, 8.5, 1.0);
	glCallList(cuboID[10]);
	glPopMatrix();

	//parede frente 4
	glPushMatrix();
	glTranslatef(-25.0, -9.5, 1.0);
	glCallList(cuboID[11]);
	glPopMatrix();

	//parede frente 5
	glPushMatrix();
	glTranslatef(-83.0, -1.0, 1.0);
	glCallList(cuboID[12]);
	glPopMatrix();

	//parede frente 6
	glPushMatrix();
	glTranslatef(-70.0, 9.0, 1.0);
	glCallList(cuboID[13]);
	glPopMatrix();

	//parede frente 7
	glPushMatrix();
	glTranslatef(-17.0, 0.0, 1.0);
	glCallList(cuboID[14]);
	glPopMatrix();

	//pes da cama - superior direito
	glPushMatrix();
	glTranslatef(85.0, -10.0, -31.0);
	glCallList(cuboID[15]);
	glPopMatrix();
	
	//pes da cama - superior esquedo
	glPushMatrix();
	glTranslatef(85.0, -10.0, -49.0);
	glCallList(cuboID[16]);
	glPopMatrix();

	//cabeceira
	glPushMatrix();
	glTranslatef(85.0, -3.0, -40.0);
	glRotated(90.0, 0.0, 1.0, 0.0);
	glCallList(cuboID[17]);
	glPopMatrix();


	//pes da cama - inferior direito
	glPushMatrix();
	glTranslatef(55.0, -10.0, -31.0);
	glCallList(cuboID[18]);
	glPopMatrix();

	//pes da cama - inferior esquerdo
	glPushMatrix();
	glTranslatef(55.0, -10.0, -49.0);
	glCallList(cuboID[19]);
	glPopMatrix();

	//base cama
	glPushMatrix();
	glTranslatef(69.0, -7.0, -40.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[20]);
	glPopMatrix();

	//colhão
	glPushMatrix();
	glTranslatef(69.0, -5.0, -40.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[21]);
	glPopMatrix();

	//quadro
	glPushMatrix();
	glTranslatef(0.0, 3.0, -99.0);
	//glRotated(180, 0.0, 0.0, 1.0);
	glCallList(cuboID[22]);
	glPopMatrix();

	//pes da mesa - superior direito
	glPushMatrix();
	glTranslatef(85.0, -10.0, -97.0);
	glCallList(cuboID[23]);
	glPopMatrix();

	//pes da mesa - superior esquerdo
	glPushMatrix();
	glTranslatef(65.0, -10.0, -97.0);
	glCallList(cuboID[24]);
	glPopMatrix();

	//pes da mesa - inferior esquerdo
	glPushMatrix();
	glTranslatef(65.0, -10.0, -89.0);
	glCallList(cuboID[25]);
	glPopMatrix();

	//pes da mesa - inferior dirito
	glPushMatrix();
	glTranslatef(85.0, -10.0, -89.0);
	glCallList(cuboID[26]);
	glPopMatrix();


	//base da mesa
	glPushMatrix();
	glTranslatef(75.0, -5.0, -93.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[27]);
	glPopMatrix();

	//puf
	glPushMatrix();
	glTranslatef(50.0, -9.0, -93.0);
	//glRotated(90.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[28]);
	glPopMatrix();

	//pes da cadeira - superior direito
	glPushMatrix();
	glTranslatef(77.0, -10.0, -87.0);
	glCallList(cuboID[29]);
	glPopMatrix();

	//pes da cadeira - superior esquerdo
	glPushMatrix();
	glTranslatef(72.0, -10.0, -87.0);
	glCallList(cuboID[30]);
	glPopMatrix();
	
	//pes da cadeira - inferior direito
	glPushMatrix();
	glTranslatef(77.0, -10.0, -83.0);
	glCallList(cuboID[31]);
	glPopMatrix();


	//pes da cadeira - inferior esquerdo
	glPushMatrix();
	glTranslatef(72.0, -10.0, -83.0);
	glCallList(cuboID[32]);
	glPopMatrix();

	//assento da cadeira
	glPushMatrix();
	glTranslatef(74.5, -7.3, -85.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[33]);
	glPopMatrix();


	//encosto da cadeira
	glPushMatrix();
	glTranslatef(74.5, -3.7, -80.9);
	glRotated(90.0, 0.0, 0.0, 1.0);
	glCallList(cuboID[34]);
	glPopMatrix();

	//armario
	glPushMatrix();
	glTranslatef(-45, -1.0, -94.0);
	glCallList(cuboID[35]);
	glPopMatrix();

	//porta do armario 1
	glPushMatrix();
	glTranslatef(-41, 0.0, -89.0);
	glCallList(cuboID[36]);
	glPopMatrix();

	//porta do armario 2
	glPushMatrix();
	glTranslatef(-49, 0.0, -89.0);
	glCallList(cuboID[37]);
	glPopMatrix();
	
	//tapete
	glPushMatrix();
	glTranslatef(0.0, -12.0, -45.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[38]);
	glPopMatrix();

	//relogio
	glPushMatrix();
	glTranslatef(88.0, 9.0, -40.0);
	glRotatef(90.0, 0.0, -1.0, 0.0);
	glCallList(cuboID[39]);
	glPopMatrix();

	//perna estante 1
	glPushMatrix();
	glTranslatef(30.2, -5.0, -5.0);
	glRotated(180.0, 1.0, 0.0, 1.0);
	glCallList(cuboID[40]);
	glPopMatrix();

	//perna estante 2
	glPushMatrix();
	glTranslatef(19.8, -5.0, -5.0);
	glRotated(180.0, 1.0, 0.0, 1.0);
	glCallList(cuboID[41]);
	glPopMatrix();

	//partileira 1 estante
	glPushMatrix();
	glTranslatef(25.0, -8.0, -5.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[42]);
	glPopMatrix();

	//partileira 2 estante
	glPushMatrix();
	glTranslatef(25.0, -2.0, -5.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[43]);
	glPopMatrix();

	//partileira 3 estante
	glPushMatrix();
	glTranslatef(25.0, 5.0, -5.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[44]);
	glPopMatrix();
	
	//notebook
	glPushMatrix();
	glTranslatef(75.0, -4.5, -93.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[45]);
	glPopMatrix();

	//livro
	glPushMatrix();
	glTranslatef(65.0, -4.5, -93.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[46]);
	glPopMatrix();

	//comoda
	glPushMatrix();
	glTranslatef(80.0, -6.0, -15.0);
	glCallList(cuboID[47]);
	glPopMatrix();

	//comoda pes direito superior
	glPushMatrix();
	glTranslatef(85.0, -11.0, -9.0);
	glRotated(15.0, -1.0, 0.0, 0.0);
	glCallList(cuboID[48]);
	glPopMatrix();

	//comoda pes direito inferior
	glPushMatrix();
	glTranslatef(80.0, -11.0, -9.0);
	glRotated(15.0, -1.0, 0.0, 0.0);
	glCallList(cuboID[49]);
	glPopMatrix();

	//comoda pes esquerdo superior
	glPushMatrix();
	glTranslatef(85.0, -11.0, -20.0);
	glRotated(15.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[50]);
	glPopMatrix();

	//comoda pes direito inferior
	glPushMatrix();
	glTranslatef(80.0, -11.0, -20.0);
	glRotated(15.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[51]);
	glPopMatrix();

	//gaveta comoda - 1
	glPushMatrix();
	glTranslatef(76.9, -4.5, -15.0);
	glCallList(cuboID[52]);
	glPopMatrix();

	//gaveta comoda - 2
	glPushMatrix();
	glTranslatef(76.9, -7.0, -15.0);
	glCallList(cuboID[53]);
	glPopMatrix();
	
	//base ventilador
	glPushMatrix();
	glTranslatef(-80, -12.0, -10.0);
	glCallList(cuboID[54]);
	glPopMatrix();

	//tubo ventilador
	glPushMatrix();
	glTranslatef(-80, -6.0, -10.0);
	glCallList(cuboID[55]);
	glPopMatrix();

	//parafuso ventilador
	glPushMatrix();
	glTranslatef(-79, 0.0, -10.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glCallList(cuboID[56]);
	glPopMatrix();

	//helice 1 ventilador
	glPushMatrix();
	glTranslatef(-78.0, 0.0, -10.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glRotatef(-angulo_vent, 0, 0, 1);
	glCallList(cuboID[57]);
	glPopMatrix();

	//helice 2 ventilador
	glPushMatrix();
	glTranslatef(-77.7, 0.0, -10.0);
	glRotatef(90.0, 0.0, 1.0, 1.0);
	glRotatef(-angulo_vent, 0, 0, 1);
	glCallList(cuboID[58]);
	glPopMatrix();

	//helice 3 ventilador
	glPushMatrix();
	glTranslatef(-77.3, 0.0, -10.0);
	glRotatef(90.0, 0.0, 1.0, -1.0);
	glRotatef(-angulo_vent, 0, 0, 1);
	glCallList(cuboID[59]);
	glPopMatrix();

	//helice 4 ventilador
	glPushMatrix();
	glTranslatef(-77, 0.0, -10.0);
	glRotatef(120.0, 1.0, 1.0, 1.0);
	glRotatef(-angulo_vent, 0, 0, 1);
	glCallList(cuboID[60]);
	glPopMatrix();

	angulo_vent += 0.5;
	if (angulo_vent >= 360) {
		angulo_vent = 0.0;
	}

	//assento sofa
	glPushMatrix();
	glTranslatef(-80.0, -8.4, -50.0);
	glCallList(cuboID[61]);
	glPopMatrix();

	//sofa pes superior esquerdo
	glPushMatrix();
	glTranslatef(-85.0, -11.0, -35.0);
	glRotated(15.0, -1.0, 0.0, 0.0);
	glCallList(cuboID[62]);
	glPopMatrix();

	//sofa pes superior direito
	glPushMatrix();
	glTranslatef(-85.0, -11.0, -67.0);
	glRotated(15.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[63]);
	glPopMatrix();

	//sofa pes inferior esquerdo
	glPushMatrix();
	glTranslatef(-75.0, -11.0, -35.0);
	glRotated(15.0, -1.0, 0.0, 0.0);
	glCallList(cuboID[64]);
	glPopMatrix();

	//sofa pe inferior direito
	glPushMatrix();
	glTranslatef(-75.0, -11.0, -67.0);
	glRotated(15.0, 1.0, 0.0, 0.0);
	glCallList(cuboID[65]);
	glPopMatrix();

	//encosto sofa
	glPushMatrix();
	glTranslatef(-84.5, -4.7, -50.0);
	glRotated(90.0, 0.0, 0.0, 1.0);
	glCallList(cuboID[66]);
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