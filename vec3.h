#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3 {

public:

  vec3(){};
  vec3(float x, float y, float z){this->x = x; this->y = y; this->z = z;};


  inline const vec3& operator+() const {return *this;}
  inline vec3 operator-() const {return vec3(-x,-y,-z);}

  inline vec3& operator+=(const vec3 &v){
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  inline vec3& operator-=(const vec3 &v){
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  inline vec3& operator*=(const vec3 &v){
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }

  inline vec3& operator/=(const vec3 &v){
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
  }

  inline vec3& operator+=(const float t){
    x += t;
    y += t;
    z += t;
    return *this;
  }

  inline vec3& operator-=(const float t){
    x -= t;
    y -= t;
    z -= t;
    return *this;
  }

  inline vec3& operator*=(const float t){
    x *= t;
    y *= t;
    z *= t;
    return *this;
  }

  inline vec3& operator/=(const float t){
    x /= t;
    y /= t;
    z /= t;
    return *this;
  }

  inline float length() const {return sqrt(x*x+y*y+z*z);}

  float x,y,z;

};


inline vec3 operator+(const vec3 &v1, const vec3 &v2){
  return vec3(v1.x+v2.x,v1.y+v2.y,v1.z+v2.z);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2){
  return vec3(v1.x-v2.x,v1.y-v2.y,v1.z-v2.z);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2){
  return vec3(v1.x*v2.x,v1.y*v2.y,v1.z*v2.z);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2){
  return vec3(v1.x/v2.x,v1.y/v2.y,v1.z/v2.z);
}


inline vec3 operator+(const vec3 &v, float t){
  return vec3(t+v.x,t+v.y,t+v.z);
}

inline vec3 operator+(float t,const vec3 &v){
  return vec3(t+v.x,t+v.y,t+v.z);
}

inline vec3 operator-(const vec3 &v, float t){
  return vec3(v.x-t,v.y-t,v.z-t);
}

inline vec3 operator-(float t,const vec3 &v){
  return vec3(t-v.x,t-v.y,t-v.z);
}

inline vec3 operator*(const vec3 &v, const float t){
  return vec3(t*v.x,t*v.y,t*v.z);
}

inline vec3 operator*(const float t,const vec3 &v){
  return vec3(t*v.x,t*v.y,t*v.z);
}

inline vec3 operator/(const vec3 &v,float t){
  return vec3(v.x/t,v.y/t,v.z/t);
}

inline float dot(const vec3 &v1, const vec3 &v2){
  return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
}

inline vec3 cross(const vec3 &v1, const vec3 &v2){
  return vec3(
    v1.y*v2.z-v1.z*v2.y,
    v1.z*v2.x-v1.x*v2.z,
    v1.x*v2.y-v1.y*v2.x
  );
}


inline vec3 normalize(const vec3 &v){
  return v/v.length();
}

inline vec3 reflect(const vec3 &v, const vec3 &n){
  return v - 2.0*dot(v,n)*n;
}

inline vec3 refract(const vec3 &v, const vec3 &n, float rir){
  float k = 1.0 - rir * rir * (1.0 - dot(n, v) * dot(n, v));
  if (k < 0.0){
      return vec3(0.0,0.0,0.0);
  }
  else{
    return rir * v - (rir * dot(n, v) + sqrt(k)) * n;
  }
}

inline vec3 clamp(const vec3 &v,float l, float h){
  return vec3(
    (fmax(fmin(v.x,h),l)),
    (fmax(fmin(v.y,h),l)),
    (fmax(fmin(v.z,h),l))
  );
}
