#include "Textura.h"
#include<Windows.h>
#include<gl/GL.h>
#include"stb_image.h"
#include<iostream>


Textura::Textura():
	t_id(0), t_largura(0), t_altura(0), t_canais(0)
{
}

Textura::~Textura()
{
	glDeleteTextures(1, &t_id);
}

void Textura::load(std::string filePath)
{
	unsigned char* imgData;

	stbi_set_flip_vertically_on_load(true); //ler a figura de cima para baixo

	imgData = stbi_load(filePath.c_str(), &t_largura, &t_altura, &t_canais, 4);

	if (imgData) {

		glGenTextures(1, &t_id); //diz que quer criar uma textura para um objeto 
		glBindTexture(GL_TEXTURE_2D, t_id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, t_largura, t_altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(imgData);
	}
	else {
		std::cout << "ERRO: Não foi possive carregar a textura" << filePath.c_str() << std::endl;

	}
}


void Textura::Bind()
{
	glBindTexture(GL_TEXTURE_2D, t_id);
}

void Textura::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
