#pragma once
#include <vector>
#include <cmath>
#include "cg.h"
#include "Textura.h"



void rect(vec3 p1, vec3 p2, vec3 p3, vec3 p4, color cor) {
	glColor3fv(cor);
	glBegin(GL_QUADS);
	glVertex3fv(&p1.x);
	glVertex3fv(&p2.x);
	glVertex3fv(&p3.x);
	glVertex3fv(&p4.x);
	glEnd();
}

void rectTextura(vec3 p1, vec3 p2, vec3 p3, vec3 p4) {
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3fv(&p1.x);
	glTexCoord2f(1.0, 0.0); glVertex3fv(&p2.x);
	glTexCoord2f(1.0, 1.0); glVertex3fv(&p3.x);
	glTexCoord2f(0.0, 1.0); glVertex3fv(&p4.x);
	glEnd();
}
void desenharCuboTextura(unsigned int& id, float largura, float altura, float expessura, Textura* tex) {
	//float d = s / 2.0;

	vec3 v1(-largura, altura, expessura);
	vec3 v2(-largura, -altura, expessura);
	vec3 v3(largura, -altura, expessura);
	vec3 v4(largura, altura, expessura);

	vec3 v5(largura, altura, -expessura);
	vec3 v6(largura, -altura, -expessura);
	vec3 v7(-largura, -altura, -expessura);
	vec3 v8(-largura, altura, -expessura);

	glNewList(id, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	tex->Bind();
	
	//frente
	rectTextura(v2,v3,v4,v1);

	//direita
	rectTextura(v4, v3, v6, v5);

	//back
	rectTextura(v5, v8, v7, v6);

	//esquerda
	rectTextura(v1, v8, v7, v2);

	//topo
	rectTextura(v1, v4, v5, v8);

	//bottom
	rectTextura(v2, v7, v6, v3);
	
	tex->UnBind();
	glEndList();
}
void desenharCubo(unsigned int& id, float largura, float altura, float expessura, color cor) {
	//float d = s / 2.0;

	vec3 v1(-largura, altura, expessura);
	vec3 v2(-largura, -altura, expessura);
	vec3 v3(largura, -altura, expessura);
	vec3 v4(largura, altura, expessura);

	vec3 v5(largura, altura, -expessura);
	vec3 v6(largura, -altura, -expessura);
	vec3 v7(-largura, -altura, -expessura);
	vec3 v8(-largura, altura, -expessura);

	glNewList(id, GL_COMPILE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//frente
	rect(v1, v2, v3, v4, cor);

	//direita
	rect(v4, v3, v6, v5, cor);

	//back
	rect(v5, v8, v7, v6, cor);

	//esquerda
	rect(v1, v8, v7, v2, cor);

	//topo
	rect(v1, v4, v5, v8, cor);

	//bottom
	rect(v2, v7, v6, v3, cor);

	glEndList();
}


void desenhaEsfera(unsigned int& id, color cor, GLfloat raio, GLuint nStack, GLuint nSectors) {

	std::vector<std::vector<GLuint>> indices;

	std::vector<vec3> pontos;
	const GLfloat PI = 3.141592;

	GLfloat deltaPhi = PI / nStack;
	GLfloat deltaTheta = 2 * PI / nSectors;

	for (GLuint i = 0; i <= nStack; i++) {
		GLfloat phi = -PI / 2.0 + i * deltaPhi;
		GLfloat temp = raio * cos(phi);
		GLfloat y = raio * sin(phi);

		std::vector<GLuint>pt;

		for (GLuint j = 0; j < nSectors; j++)
		{
			GLfloat theta = j * deltaTheta;
			GLfloat x = temp * sin(theta);
			GLfloat z = temp * cos(theta);

			pontos.push_back(vec3(x, y, z));
			GLuint index = pontos.size() - 1;
			pt.push_back(index);

		}//next j

		indices.push_back(pt);

	}//next i

	// -- plotar pontos
	/*
	glColor3fv(vermelho);
	glPointSize(2.5);
	glBegin(GL_POINTS);
	for(GLuint i = 0; i < pontos.size(); i++){
		glVertex3fv(&pontos[i].x);
	}
	glEnd();
	*/


	glNewList(id, GL_COMPILE);
	glColor3fv(cor);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	for (GLuint i = 0; i < nStack; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);

		for (GLuint j = 0; j < nSectors; j++) {
			GLuint index = indices[i][j];
			glVertex3fv(&pontos[index].x);
			index = indices[i + 1][j];
			glVertex3fv(&pontos[index].x);

			if (j == nSectors - 1) {
				GLuint index = indices[i][0];
				glVertex3fv(&pontos[index].x);
				index = indices[i + 1][0];
				glVertex3fv(&pontos[index].x);
			}
		}
		glEnd();
	}
	glDisable(GL_CULL_FACE);
	glEndList();

}

void desenharTerreno(unsigned int id) {
	float L = 500.0;
	float incr = 1.0;
	float y = -0.5;
	glNewList(id, GL_COMPILE);
	glColor3fv(branco_gelo);
	glBegin(GL_LINES);
	for (float i = -L; i <= L; i += incr) {

		//verticais
		glVertex3f(i, y, -L);
		glVertex3f(i, y, L);

		//horizontais
		glVertex3f(-L, y, i);
		glVertex3f(L, y, i);
	}

	glEnd();
	glEndList();
}