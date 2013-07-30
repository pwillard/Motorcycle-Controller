#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <cmath>
#include <iostream>
#include <conio.h>

extern "C" {
#include "hid.h"
}

#define PI 3.14


using namespace std;
//This function reads in the data from the pipe
bool read_vector( double& xx, double& xy, double& xz, double& zx, double& zy, double& zz)
      
{	char one[250];
double t, p1, p2, p3;
    fgets(one, 250, stdin);

sscanf_s (one,"t=%lf p0=%lf p1=%lf p2=%lf x0=%lf x1=%lf x2=%lf z0=%lf z1=%lf z2=%lf",&t, &p1, &p2, &p3, &xx, &xy, &xz, &zx, &zy, &zz);
   
 return true;

}
//This function first asks for the data and then calculates the neccessary angles using basic trigonometry
bool get_angles(double &roll, double &pitch){
	
	double XX, XY, XZ, ZX, ZY, ZZ, x;
	
	read_vector(XX, XY, XZ, ZX, ZY, ZZ);	
	
	
			if (XX != 0 && XZ != 0){
			roll = atan(XY/sqrt(pow(XX,2)+pow(XZ,2)))*180/PI;
		}
		else{
			roll=0;
		}

		if (ZX != 0 && ZZ != 0){
			pitch= atan(ZY/sqrt(pow(ZX,2)+pow(ZZ,2)))*180/PI;
		}
		else{
			pitch=0;
		}
		

		return true;
	
	}



int main(){
	int i, r;
	int  buf[2];

	double roll, pitch;
	//Tests if the Teensy deice is plugged in and ready to recieve
		r = rawhid_open(1, 0x16C0, 0x0486, 0xFFAB, 0x0200);
		if (r <= 0) {
			printf("no rawhid device found\n");
			return -1;
		}
	
	printf("found rawhid device\n");
	
	//Sets the buffer to 128 and sends it in order to centre the hardware
	for (i=0; i<2; i++) {
				buf[i] = 128;
			}
	rawhid_send(0, buf, 2, 2);

	do{
	
		get_angles(roll, pitch);
		buf[0]=((roll+90)/180)*256;
		buf[1]=((pitch+90)/180)*256;
		
	
	}
	while(	rawhid_send(0, buf, 2, 20));
	

	}







