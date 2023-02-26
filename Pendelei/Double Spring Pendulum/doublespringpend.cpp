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
    double* state = new double[8];
    double* pstate = new double[8];
    double x1,x2,y1,y2,v1x,v1y,v2x,v2y,px1,px2,py1,py2,pv1x,pv1y,pv2x,pv2y;
    state[0] = alpha0;
    state[1] = beta0;
    state[2] = a0;
    state[3] = b0;
    state[4] = valpha0;
    state[5] = vbeta0;
    state[6] = va0;
    state[7] = vb0;
    pstate[0] = alpha0;
    pstate[1] = beta0;
    pstate[2] = a0+epsilon;
    pstate[3] = b0-epsilon;
    pstate[4] = valpha0;
    pstate[5] = vbeta0;
    pstate[6] = va0;
    pstate[7] = vb0;
    
    ostringstream fout1;
    ostringstream fout2;
    ostringstream fout3;
    fout1 << "Data/xycoordinatesl1_" << l1 << "l2_" << l2 << "m1_" << m1 << "m2_" << m2 << "k1_" << k1 << "k2_" << k2 << "pert.dat";
    fout2 << "Data/energytest.dat";
    ofstream write1(fout1.str().c_str());
    ofstream write2(fout2.str().c_str());
    x1 = state[2]*sin(state[0]);
    y1 = -state[2]*cos(state[0]);
    x2 = x1 + state[3]*sin(state[1]);
    y2 = y1 - state[3]*cos(state[1]);
    v1x = state[2]*state[4]*cos(state[0]) + state[6]*sin(state[0]);
    v1y = state[2]*state[4]*sin(state[0]) - state[6]*cos(state[0]);
    v2x = v1x + state[3]*state[5]*cos(state[1]) + state[7]*sin(state[1]);
    v2y = v1y + state[3]*state[5]*sin(state[1]) - state[7]*cos(state[1]);

    px1 = pstate[2]*sin(pstate[0]);
    py1 = -pstate[2]*cos(pstate[0]);
    px2 = px1 + pstate[3]*sin(pstate[1]);
    py2 = py1 - pstate[3]*cos(pstate[1]);
    pv1x = pstate[2]*pstate[4]*cos(pstate[0]) + pstate[6]*sin(pstate[0]);
    pv1y = pstate[2]*pstate[4]*sin(pstate[0]) - pstate[6]*cos(pstate[0]);
    pv2x = pv1x + pstate[3]*pstate[5]*cos(pstate[1]) + pstate[7]*sin(pstate[1]);
    pv2y = pv1y + pstate[3]*pstate[5]*sin(pstate[1]) - state[7]*cos(state[1]);
            
    write1 << t << '\t' << x1 <<'\t' << y1 << '\t' << x2 <<'\t' << y2 << '\t' << px1 <<'\t' << py1 << '\t' << px2 <<'\t' << py2 << '\n';
    write2 << 0.5*m1*(v1x*v1x+v1y*v1y) + 0.5*m2*(v2x*v2x+v2y*v2y) + m1*g*y1 + m2*g*y2 + 0.5*k1*(state[2]-l1)*(state[2]-l1) + 0.5*k2*(state[3]-l2)*(state[3]-l2) << '\n';
            
    for(t=0;t<tend/h;t++){
        Rk4Step(t*h,state);
        Rk4Step(t*h,pstate);
	if(!((t+1)%10)){
            x1 = state[2]*sin(state[0]);
            y1 = -state[2]*cos(state[0]);
            x2 = x1 + state[3]*sin(state[1]);
            y2 = y1 - state[3]*cos(state[1]);
            v1x = state[2]*state[4]*cos(state[0]) + state[6]*sin(state[0]);
            v1y = state[2]*state[4]*sin(state[0]) - state[6]*cos(state[0]);
            v2x = v1x + state[3]*state[5]*cos(state[1]) + state[7]*sin(state[1]);
            v2y = v1y + state[3]*state[5]*sin(state[1]) - state[7]*cos(state[1]);

            px1 = pstate[2]*sin(pstate[0]);
            py1 = -pstate[2]*cos(pstate[0]);
            px2 = px1 + pstate[3]*sin(pstate[1]);
            py2 = py1 - pstate[3]*cos(pstate[1]);
            pv1x = pstate[2]*pstate[4]*cos(pstate[0]) + pstate[6]*sin(pstate[0]);
            pv1y = pstate[2]*pstate[4]*sin(pstate[0]) - pstate[6]*cos(pstate[0]);
            pv2x = pv1x + pstate[3]*pstate[5]*cos(pstate[1]) + pstate[7]*sin(pstate[1]);
            pv2y = pv1y + pstate[3]*pstate[5]*sin(pstate[1]) - pstate[7]*cos(pstate[1]);
            
            write1 << t << '\t' << x1 <<'\t' << y1 << '\t' << x2 <<'\t' << y2 << '\t' << px1 <<'\t' << py1 << '\t' << px2 <<'\t' << py2 << '\n';
            write2 << 0.5*m1*(v1x*v1x+v1y*v1y) + 0.5*m2*(v2x*v2x+v2y*v2y) + m1*g*y1 + m2*g*y2 + 0.5*k1*(state[2]-l1)*(state[2]-l1) + 0.5*k2*(state[3]-l2)*(state[3]-l2) << '\n';
	}
	
    }
    write1.close();
    write2.close();
    return 0;
}

void eqnmotion(double t, double *state){
    //state[0]...alpha
    //state[1]...beta
    //state[2]...a
    //state[3]...b
    //state[4]...valpha
    //state[5]...vbeta
    //state[6]...va
    //state[7]...vb
    
    double helpstate[8];
    for(int i=0;i<8;i++){
        helpstate[i] = state[i];
    }
    double prefactor1 = 1.0/(state[2]);
    double prefactor2 = 1.0/(state[3]);
    
    helpstate[0] = state[4];
    helpstate[1] = state[5];
    helpstate[2] = state[6];
    helpstate[3] = state[7];
    helpstate[4] = -prefactor1*(g*sin(state[0]) + k2*(state[3]-l2)*sin(state[0]-state[1])/m1 + 2*state[6]*state[4]);
    helpstate[5] = prefactor2*(k1*(state[2]-l1)*sin(state[0]-state[1])/m1 - 2*state[7]*state[5]);
    helpstate[6] = k1*(l1-state[2])/m1 + g*cos(state[0]) + k2*(state[3]-l2)*cos(state[0]-state[1])/m1 + state[2]*state[4]*state[4];
    helpstate[7] = k1*(state[2]-l1)/m1*cos(state[0]-state[1]) - (m1+m2)*k2*(state[3]-l2)/(m1*m2) + state[3]*state[5]*state[5];
    
    for(int i=0;i<8;i++){
        state[i] = helpstate[i];
    }
}
    
    
void Rk4Step(double t, double *y){
    double* yn = new double[8];
    double c1[8],c2[8],c3[8],c4[8];
    for(int i=0;i<8;i++){
        yn[i] = y[i];
    }
    eqnmotion(t,yn);
    for(int i=0;i<8;i++){
        c1[i] = yn[i];
    }
    for(int i=0; i<8; i++){
        yn[i]= y[i]+(h/2)*c1[i];
    }
    eqnmotion(t+h/2,yn);
    for(int i=0;i<8;i++){
        c2[i] = yn[i];
    }
    for(int i=0; i<8; i++){
        yn[i]= y[i]+(h/2)*c2[i];
    }
    eqnmotion(t+h/2,yn);
    for(int i=0;i<8;i++){
        c3[i] = yn[i];
    }
    for(int i=0; i<8; i++){
        yn[i]=y[i]+h*c3[i];
    }
    eqnmotion(t+h,yn);
    for(int i=0;i<8;i++){
        c4[i] = yn[i];
    }
    for(int i=0; i<8; i++){
        y[i] = y[i]+(h/6)*(c1[i]+2*c2[i]+2*c3[i]+c4[i]);
    }
}
