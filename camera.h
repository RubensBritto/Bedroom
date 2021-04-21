#pragma once

#include "cg.h"

class camera
{
private:
	vec3 m_pos;
	vec3 m_dir;
	vec3 m_left;
	vec3 m_up;
	vec3 m_velocidade;
	float m_sc1 = 1; //escala
	float m_yaw;
	float m_PI = 3.14159;
public:
	camera(vec3 pos);
	~camera();
	void ativar();

	void frente();
	void atras();
	void esquerda();
	void direita();
	void updateYaw(float dYaw);
	void update();

private:
	float converterToRadiano(float angulo);
};

