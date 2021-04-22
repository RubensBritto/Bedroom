#pragma once
#pragma once
#include<cmath>

struct vec3 {
	float x, y, z;
	vec3() :x(0.0), y(0.0), z(0.0) {}
	vec3(float x_, float y_, float z_) :x(x_), y(y_), z(z_) {}
	vec3 operator+(const vec3& v)const { return vec3(x + v.x, y + v.y, z + v.z); }
	vec3 operator*(float k) { return vec3(x*k, y*k, z*k); }
	float mag() { return sqrt(x * x + y * y + z * z); } //maguinitude do vetor
	void normalizar() {
		float m = mag();
		x = x / m;
		y = y / m;
		z = z / m;
		//normalizar o vetor
	}
	vec3 produtoVetorial(vec3 v) {
		return vec3(y*v.z - z * v.y, z*v.x - x * v.z, x*v.y - y * v.x);
	}


};

