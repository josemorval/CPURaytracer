#include <math.h>
#include <stdlib.h>
#include <iostream>

class mat3 {

public:

  mat3(){}
  mat3(float x0, float x1, float x2, float x3, float x4, float x5, float x6, float x7, float x8){
    this->x0 = x0; this->x1 = x1; this->x2 = x2;
    this->x3 = x3; this->x4 = x4; this->x5 = x5;
    this->x6 = x6; this->x7 = x7; this->x8 = x8;

  };

  mat3(vec3 v1, vec3 v2, vec3 v3){
    this->x0 = v1.x; this->x1 = v1.y; this->x2 = v1.z;
    this->x3 = v2.x; this->x4 = v2.y; this->x5 = v2.z;
    this->x6 = v3.x; this->x7 = v3.y; this->x8 = v3.z;
  }

  float x0,x1,x2,x3,x4,x5,x6,x7,x8;

};

inline vec3 operator*(const mat3 &m, const vec3 &v){
  return vec3(
    m.x0*v.x+m.x3*v.y+m.x6*v.z,
    m.x1*v.x+m.x4*v.y+m.x7*v.z,
    m.x2*v.x+m.x5*v.y+m.x8*v.z
  );
}
