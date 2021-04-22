#include<iostream>


class Textura
{
private:
	unsigned int t_id;
	int t_largura, t_altura, t_canais;

public:
	Textura();
	~Textura();
	void load(std::string filePath);
	void Bind(); //vincular a textura ao objeto
	void UnBind(); //desvincular a textura ao objeto
};
