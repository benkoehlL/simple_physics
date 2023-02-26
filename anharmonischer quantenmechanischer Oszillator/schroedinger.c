// schroedinger.c

#include <stdio.h>
#include <math.h>

#include "Xgraphics.h"

double e = 0.5, a = 0.0;
int export = 0, parity = 0;

int XMAX = 600, YMAX = 400;
Window mywindow;
World drawworld, printworld;
XEvent myevent;

void print(void);
double k(double);

double dx, dxstart = 0.01, y, ym1, yp1, de, destart = 0.1, x, xp1, xm1, ymax = 1.5, xmax = 7.5;

FILE *file;
char filename[FILENAME_MAX];

main()
{
   InitX();
   mywindow = CreateWindow(XMAX, YMAX, "Pertubated Harmonic Oscillator");

   drawworld = CreateWorld(mywindow, 1, 1, XMAX-100, YMAX-100, 0.0, ymax, xmax, -ymax, 1, 1);
   printworld = CreateWorld(mywindow, 1, YMAX-100, XMAX, 100, 0.0, 1.0, 1.0, 0.0, 1, 1);
   
   InitButtons(mywindow,"b,exit,e,b,lambda ++,l,b,energy ++,+,b,energy --,-,b,de/10,k,b,10*de,j,b,dx/2,d,b,start,s,b,parity,u,b,export,f",100);
               
   ShowWindow(mywindow);

   dx = dxstart; de = destart;

   while(1)
   {
     ClearWorld(drawworld);
     WDrawRectangle(drawworld, 0.0, ymax, xmax, -ymax, 2);
     WDrawLine(drawworld, 0.0, 0.0, xmax, 0.0, 4);
        
    if (parity == 0) {
      x = 0.5 * dx;
      y = ym1 = 1.0;
    } 
    else {
      x = dx;
      ym1 = 0.0;
      y = 1.5 * dx;
    }
    
    yp1 = 1.0;   
    while (fabs(yp1) < ymax) {
       xp1 = x + dx; xm1 = x - dx;
       yp1 = (2.0 * (1.0 - 5.0 / 12.0 * dx * dx * k(x)) * y - (1.0 + dx * dx / 12.0 * k(xm1)) * ym1)
           / (1.0 + dx * dx / 12.0 * k(xp1));
       WDrawLine(drawworld, x, y, xp1, yp1, 1);
       if (export != 0)
         fprintf(file,"%f %f\n", x, y);
       xm1 = x; x = xp1;
       ym1 = y; y = yp1;
      }
 	  export = 0;
 	  
     print();
     
     GetEvent(&myevent, 1);
     while(myevent.type != KeyPress) GetEvent(&myevent, 1);
        
     switch (ExtractChar(myevent))
	  {   
       case 'e': 
         ExitX(); 
         exit(1); 
         break;
	    case 'l': a += 0.01; break;
	    case '+': e += de; break;
	    case '-': e -= de; break;
	    case 's': 
	      de = destart; 
	      dx = dxstart; 
	      e = 0.1 * ((int) (10 * e));
	      break;
	    case 'k': de *= 0.1; break;
      case 'j': de *= 10.0; break;
	    case 'd': dx *= 0.5; break;
       case 'u': parity = 1 - parity; break;
       case 'f':
         if (file != 0)
            fclose(file);
         export = 1;
         sprintf(filename,"%.2f_%.10f_%.0e_%.2e.dat",a , e, de, dx);
         file = fopen(filename, "w");
         break;
	    default: break;
	  }
	  
   }
}

double k(double z)
{
   return -z*z - 2.0*a*z*z*z*z + 2.0*e;
}

void print()
{
  char str[100];
  sprintf(str, "lambda = %.2f      energy e = %.10f      de = %.0e      dx = %.2e", a, e, de, dx);
  WDrawString(printworld, 0.01, 0.5, str, 1);  
}

