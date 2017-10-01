#include <iostream>
#include "vec3.h"
#include "mat3.h"

//Testing raymarch
// float map(vec3 pos){
// 	return pos.length()-1.0;
// }
//
// float raymarch(vec3 ro, vec3 rd){
//
// 	float t = 0.;
// 	int i;
//
// 	for(i=0;i<64;i++){
//
// 		float f = map(ro+t*rd);
// 		if(f<0.01){break;}
// 		t+=f;
//
// 	}
//
// 	if(i>62){
// 		return -1.;
// 	}else{
// 		return t;
// 	}
// }

float intersectionSphere(vec3 center,float radius,vec3 ro,vec3 rd,vec3 &nor){
	float a = dot(rd,ro-center);
	float b = dot(ro-center,ro-center);
	float discriminant = a*a-b+radius*radius;
	float t;
  if (discriminant > 0) {
		t=-a-sqrt(discriminant);
		nor=normalize(ro+t*rd-center);
		return t;
	}else{
		nor=vec3(0.0,0.0,0.0);
		return -1.0;
	}
}

vec3 random_in_unit_sphere(){
	vec3 p;
	do{
		p = 2.0*vec3(drand48(),drand48(),drand48())-vec3(1.0,1.0,1.0);
	}while(dot(p,p)>=1.0);
	return p;
}

vec3 color(vec3 ro, vec3 rd,int depth){

	float matType=-1.0;
	vec3 matCol = vec3(0.0,0.0,0.0);
	vec3 nor,noraux;
	float f = 10000.0;

	float i = intersectionSphere(vec3(0.0,-101.0,0.0),100.0,ro,rd,noraux);
	if(i>0.0 && i<f){
		f=i;nor=noraux;matType=2.0;
		matCol = 0.6*vec3(0.54,0.0,0.54);
	}

	i = intersectionSphere(vec3(0.0,0.0,0.0),1.0,ro,rd,noraux);
	if(i>0.0 && i<f){
		f=i;nor=noraux;matType=1.0;
		matCol = vec3(1.,0.3,0.3);
	}

	i = intersectionSphere(vec3(2.0,0.0,0.0),1.0,ro,rd,noraux);
	if(i>0.0 && i<f){
		f=i;nor=noraux;matType=2.0;
		matCol = vec3(0.9,0.7,0.3);
	}

	i = intersectionSphere(vec3(-2.0,0.0,0.0),1.0,ro,rd,noraux);
	if(i>0.0 && i<f){
		f=i;nor=noraux;matType=3.0;
		matCol = vec3(1.0,1.0,1.0);
	}

	if(f<10000.0 && depth<10){
		vec3 newPos = ro+f*rd;
		if(matType<2.0){
			vec3 target = newPos+nor+random_in_unit_sphere();
			return 0.5*matCol*color(newPos,normalize(target-newPos),depth+1);
		}else if(matType<3.0){
			vec3 target = newPos+reflect(rd,nor)+0.05*random_in_unit_sphere();
			return matCol*color(newPos,normalize(target-newPos),depth+1);
		}else{
			float ratio =0.75;
			if(dot(rd,nor)>0.0){
				nor=-nor;
				ratio=1./ratio;
				vec3 target = newPos+refract(rd,nor,ratio);
				return color(newPos,normalize(target-newPos),depth+1);
			}else{
				if(drand48()>0.1){
					vec3 target = newPos+refract(rd,nor,ratio);
					return color(newPos,normalize(target-newPos),depth+1);
				}else{
					vec3 target = newPos+reflect(rd,nor)+0.1*random_in_unit_sphere();
					return matCol*color(newPos,normalize(target-newPos),depth+1);
				}
			}
		}

	}else{
		vec3 unit_direction = normalize(rd);
		float t = 0.5*unit_direction.y + 1.0;
		return (1.-t)*vec3(1.0,1.0,1.0) + t*vec3(0.8,0.9,1.0);
	}

}

mat3 setCamera(vec3 ro,vec3 ta)
{
	vec3 cw = normalize(ta-ro);
	vec3 cp = vec3(0.0,1.0,0.0);
	vec3 cu = normalize( cross(cw,cp) );
	vec3 cv = normalize( cross(cu,cw) );
	return mat3( cu, cv, cw );
}

int main(int argc,  char** argv){

	int nx = atoi(argv[1]);
	int ny = atoi(argv[2]);

	//std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	FILE *fp = fopen("second.ppm", "w"); /* b - binary mode */
  (void) fprintf(fp, "P6\n%d %d\n255\n", nx, ny);

	for(int j=ny-1;j>-1;j--){
		for(int i=0;i<nx;i++){

			vec3 col = vec3(0.0,0.0,0.0);

			int maxk = 500;
			for(int k=0;k<maxk;k++){
				//Texture coordinates
				vec3 uv = vec3(1.0*(i+drand48())/(nx-1.0),1.0*(j+drand48())/(ny-1.0),0.0);
				vec3 p = uv-0.5;
				p.x*=1.0*nx/ny;
				p.z = 0.0;

				float angle = 230./360.*2.*3.14159;
				vec3 ro = vec3(15.*cos(angle),5.,15.*sin(angle));
				vec3 ta = vec3(0.0,0.0,0.0);

				mat3 ca = setCamera(ro,ta);
				vec3 rd = ca * normalize( vec3(p.x,p.y,4.0) );
				col += color(ro,rd,0);
			}

			//Gamma correction
			col = clamp(col/float(maxk),0.0,1.0);
			col.x=sqrt(col.x);
			col.y=sqrt(col.y);
			col.z=sqrt(col.z);

			//Render col
			static unsigned char color[3];
      color[0] = int(255*col.x);  /* red */
      color[1] = int(255*col.y);  /* green */
      color[2] = int(255*col.z);  /* blue */
      (void) fwrite(color, 1, 3, fp);
		}
	}

	(void) fclose(fp);
	return 0;
}
