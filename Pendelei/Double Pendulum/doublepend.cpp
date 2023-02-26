#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include "parameter.h"

using namespace std;

void Rk4Step(double,double*);
void eqnmotion(double, double*);

int main(){
    int t=0;
    double* theta = new double[4];
    double* ptheta = new double[4];
    double x1,x2,y1,y2,v1x,v1y,v2x,v2y,px1,px2,py1,py2,pv1x,pv1y,pv2x,pv2y;
    theta[0] = theta10;
    theta[1] = theta20;
    theta[2] = vtheta10;
    theta[3] = vtheta20;
    ptheta[0] = theta10+0.01*epsilon;
    ptheta[1] = theta20;
    ptheta[2] = vtheta10;
    ptheta[3] = vtheta20+epsilon;
    ostringstream fout1;
    ostringstream fout2;
    ostringstream fout3;
    fout1 << "Data/doublependlphasespace1_" << l1 << "l2_" << l2 << "m1_" << m1 << "m2_" << m2 << ".dat";
    fout2 << "Data/xycoordinatesl1_" << l1 << "l2_" << l2 << "m1_" << m1 << "m2_" << m2 << "pert.dat";
    fout3 << "Data/energytest.dat";
    ofstream write1(fout1.str().c_str());
    ofstream write2(fout2.str().c_str());
    ofstream write3(fout3.str().c_str());
    x1 = l1*sin(theta[0]);
    y1 = -l1*cos(theta[0]);
    x2 = x1 + l2*sin(theta[1]);
    y2 = y1 - l2*cos(theta[1]);
    v1x = l1*theta[2]*cos(theta[0]);
    v1y = l1*theta[2]*sin(theta[0]);
    v2x = v1x + l2*theta[3]*cos(theta[1]);
    v2y = v1y + l2*theta[3]*sin(theta[1]);
    px1 = l1*sin(ptheta[0]);
    py1 = -l1*cos(ptheta[0]);
    px2 = px1 + l2*sin(ptheta[1]);
    py2 = py1 - l2*cos(ptheta[1]);
    pv1x = l1*ptheta[2]*cos(ptheta[0]);
    pv1y = l1*ptheta[2]*sin(ptheta[0]);
    pv2x = pv1x + l2*ptheta[3]*cos(ptheta[1]);
    pv2y = pv1y + l2*ptheta[3]*sin(ptheta[1]);
    write1 << asin(sin(theta[0])) << '\t' << asin(sin(theta[2])) << '\t' << asin(sin(theta[1])) << '\t' << asin(sin(theta[3])) << '\n';
    write2 << t << '\t' << x1 <<'\t' << y1 << '\t' << x2 <<'\t' << y2 << '\t' << px1 <<'\t' << py1 << '\t' << px2 <<'\t' << py2 << '\n';
    write3 << 0.5*m1*(v1x*v1x+v1y*v1y)+0.5*m2*(v2x*v2x+v2y*v2y)+m1*g*y1+m2*g*y2 << '\n';
    for(t=0;t<tend/h;t++){
        Rk4Step(t*h,theta);
        Rk4Step(t*h,ptheta);
	if(!((t+1)%10)){ 
            write1 << asin(sin(theta[0])) << '\t' << asin(sin(theta[1])) << '\t' << asin(sin(theta[2])) << '\t' << asin(sin(theta[3])) << '\n';
            write2 << t << '\t' << x1 <<'\t' << y1 << '\t' << x2 <<'\t' << y2 << '\t' << px1 <<'\t' << py1 << '\t' << px2 <<'\t' << py2 << '\n';
            x1 = l1*sin(theta[0]);
            y1 = -l1*cos(theta[0]);
            x2 = x1 - l2*sin(theta[1]);
            y2 = y1 - l2*cos(theta[1]);
            v1x = l1*theta[2]*cos(theta[0]);
            v1y = -l1*theta[2]*sin(theta[0]);
            v2x = v1x + l2*theta[3]*cos(theta[1]);
            v2y = v1y - l2*theta[3]*sin(theta[1]);
            write3 << 0.5*m1*(v1x*v1x+v1y*v1y)+0.5*m2*(v2x*v2x+v2y*v2y)+m1*g*y1+m2*g*y2 << '\n';
	}
	
    }
    write1.close();
    write2.close();
    write3.close();
    return 0;
}

void eqnmotion(double t, double *theta){
    //theta[0]...theta1
    //theta[1]...theta2
    //theta[2]...vtheta1
    //theta[3]...vtheta2
    double helptheta[4];
    for(int i=0;i<4;i++){
        helptheta[i] = theta[i];
    }
    double prefactor1 = 1.0/((m1+m2*sin(theta[0]-theta[1])*sin(theta[0]-theta[1]))*l1);
    double prefactor2 = 1.0/((m1+m2*sin(theta[0]-theta[1])*sin(theta[0]-theta[1]))*l2);
    helptheta[0] = theta[2];
    helptheta[1] = theta[3];
    helptheta[2] = -prefactor1*(m2*l2*theta[3]*theta[3]*sin(theta[0]-theta[1])+(m1+m2)*g*sin(theta[0])+0.5*m2*l1*theta[2]*theta[2]*sin(2*(theta[0]-theta[1]))-m2*g*sin(theta[1])*cos(theta[0]-theta[1]));
    helptheta[3] = prefactor2*((m1+m2)*theta[2]*theta[2]*l1*sin(theta[0]-theta[1])+0.5*m2*l2*theta[3]*theta[3]*sin(2*(theta[0]-theta[1]))-(m1+m2)*g*sin(theta[1])+(m1+m2)*g*sin(theta[0])*cos(theta[0]-theta[1]));
    for(int i=0;i<4;i++){
        theta[i] = helptheta[i];
    }
}
    
    
void Rk4Step(double t, double *y){
    double* yn = new double[4];
    double k1[4],k2[4],k3[4],k4[4];
    for(int i=0;i<4;i++){
        yn[i] = y[i];
    }
    eqnmotion(t,yn);
    for(int i=0;i<4;i++){
        k1[i] = yn[i];
    }
    for(int i=0; i<4; i++){
        yn[i]= y[i]+(h/2)*k1[i];
    }
    eqnmotion(t+h/2,yn);
    for(int i=0;i<4;i++){
        k2[i] = yn[i];
    }
    for(int i=0; i<4; i++){
        yn[i]= y[i]+(h/2)*k2[i];
    }
    eqnmotion(t+h/2,yn);
    for(int i=0;i<4;i++){
        k3[i] = yn[i];
    }
    for(int i=0; i<4; i++){
        yn[i]=y[i]+h*k3[i];
    }
    eqnmotion(t+h,yn);
    for(int i=0;i<4;i++){
        k4[i] = yn[i];
    }
    for(int i=0; i<4; i++){
        y[i] = y[i]+(h/6)*(k1[i]+2*k2[i]+2*k3[i]+k4[i]);
    }
}
