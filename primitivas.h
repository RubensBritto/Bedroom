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

void loadMaterial(color cor) {
	float matDiff[] = {cor[0],cor[1],cor[2],1.f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiff);
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



	float matSpecular[] = { 1.f,1.f,1.f,1.f };
	float matAmb[] = { 1.f,1.f,1.f,1.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0);
	
	//frente
	glNormal3f(0.f, 0.f, 1.f);
	loadMaterial(branco);
	rectTextura(v2,v3,v4,v1);

	//direita
	glNormal3f(1.f, 0.f, 0.f);
	loadMaterial(branco);
	rectTextura(v4, v3, v6, v5);

	//back
	glNormal3f(0.f, 0.f, -1.f);
	loadMaterial(branco);
	rectTextura(v5, v8, v7, v6);

	//esquerda
	glNormal3f(-1.f, 0.f, 0.f);
	loadMaterial(branco);
	rectTextura(v1, v8, v7, v2);

	//topo
	glNormal3f(0.f, 1.f, 0.f);
	loadMaterial(branco);
	rectTextura(v1, v4, v5, v8);

	//bottom
	glNormal3f(0.f, -1.f, 0.f);
	loadMaterial(branco);
	rectTextura(v2, v7, v6, v3);
	
	tex->UnBind();
	glEndList();
}
void desenharCubo(unsigned int& id, float largura, float altura, float expessura, color cor) {

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

	float matSpecular[] = { 1.f,1.f,1.f,1.f };
	float matAmb[] = { cor[0],cor[1],cor[2],1.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0);

	//frente
	glNormal3f(0.f, 0.f, 1.f);
	loadMaterial(cor);
	rect(v1, v2, v3, v4, cor);

	//direita
	glNormal3f(1.f, 0.f, 0.f);
	loadMaterial(cor);
	rect(v4, v3, v6, v5, cor);

	//back
	glNormal3f(0.f, 0.f, -1.f);
	loadMaterial(cor);
	rect(v5, v8, v7, v6, cor);

	//esquerda
	glNormal3f(-1.f, 0.f, 0.f);
	loadMaterial(cor);
	rect(v1, v8, v7, v2, cor);

	//topo
	glNormal3f(0.f, 1.f, 0.f);
	loadMaterial(cor);
	rect(v1, v4, v5, v8, cor);

	//bottom
	glNormal3f(0.f, -1.f, 0.f);
	loadMaterial(cor);
	rect(v2, v7, v6, v3, cor);

	glEndList();
}


void desenhaEsfera(unsigned int& id, color cor, GLfloat raio, GLuint nStack, GLuint nSectors) {

	std::vector<std::vector<GLuint>> indices;

	std::vector<vec3> pontos;
	const GLfloat PI = 3.141592f;

	GLfloat deltaPhi = PI / nStack;
	GLfloat deltaTheta = 2 * PI / nSectors;

	for (GLuint i = 0; i <= nStack; i++) {
		
		GLfloat phi = -PI / 2.0f + i * deltaPhi;
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
	glNewList(id, GL_COMPILE);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	float matSpecular[] = { 1.f,1.f,1.f,1.f };
	float matAmb[] = { cor[0],cor[1],cor[2],1.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0);

	for (GLuint i = 0; i < nStack; i++)
	{
		glColor3fv(cor);
		glBegin(GL_TRIANGLE_STRIP);
		
		for (GLuint j = 0; j < nSectors; j++) {
			GLuint index = indices[i][j];
			glVertex3fv(&pontos[index].x);
			glNormal3fv(&pontos[index].x);
			index = indices[i + 1][j];
			glVertex3fv(&pontos[index].x);
			glNormal3fv(&pontos[index].x);

			if (j == nSectors - 1) {
				GLuint index = indices[i][0];
				glVertex3fv(&pontos[index].x);
				glNormal3fv(&pontos[index].x);
				index = indices[i + 1][0];
				glVertex3fv(&pontos[index].x);
				glNormal3fv(&pontos[index].x);
			}
			loadMaterial(cor);
		}
		glEnd();
	}
	
	glDisable(GL_CULL_FACE);
	glEndList();

}

