#include "camera.h"
#include<Windows.h>
#include <gl/GLU.h>

camera::camera(vec3 pos) {
	m_pos = vec3(pos);
	m_dir = vec3(0, 0, -1);
	m_left = vec3(-1, 0, 0);
	m_up = vec3(0, 1, 0);
	m_velocidade = vec3(0, 0, 0);
}

camera::~camera() {

}

void camera::ativar()
{
	vec3 look = m_pos + m_dir;
	gluLookAt(m_pos.x, m_pos.y, m_pos.z, look.x, look.y, look.z, m_up.x, m_up.y, m_up.z);
}

void camera::frente()
{
	m_velocidade = m_dir * m_sc1;
	m_pos = m_pos + m_velocidade;
}

void camera::atras()
{
	m_velocidade = m_dir * (-m_sc1);
	m_pos = m_pos + m_velocidade;
}

void camera::esquerda()
{
	m_velocidade = m_left * m_sc1;
	m_pos = m_pos + m_velocidade;
}

void camera::direita()
{
	m_velocidade = m_left * (-m_sc1);
	m_pos = m_pos + m_velocidade;
}

void camera::updateYaw(float dYaw)
{
	m_yaw += dYaw;
}

void camera::update()
{
	float angulo = converterToRadiano(m_yaw);
	m_dir.x = sin(angulo);
	m_dir.z = -cos(angulo);
	m_dir.normalizar();
	m_left = m_up.produtoVetorial(m_dir);
}

float camera::converterToRadiano(float angulo)
{
	return (angulo * m_PI) / 180.0;
}


