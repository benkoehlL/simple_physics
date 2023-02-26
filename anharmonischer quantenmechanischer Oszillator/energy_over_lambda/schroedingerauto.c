#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

double e = 0.5, a = 0.0;
int parity = 0, n =0;
double k(double);

double dx, dxstart = 0.01, y, ym1, yp1, de, destart = 0.1, x, xp1, xm1, ymax = 3.5, xmax = 3.5,epsilon = 1E-10,snow,sbefore;

main()
{
   for(; n < 11; n++)
   {
	dx = dxstart; 
	a = 0.0;
	e = 0.5 + n;		
	do 
	{	
		de = destart;

		if (n % 4 < 2)
		{
		sbefore = 1;		
		}
		else
		{
		sbefore =-1;
		}
		while (fabs(de) > epsilon)
		{
			if (parity == 0) 
			{
      				x = 0.5 * dx;
      				y = ym1 = 1.0;
    			} 
    			else {
      				x = dx;
      				ym1 = 0.0;
      				y = 1.5 * dx;
    			}
			yp1 = 1.0;
			while (fabs(yp1) < ymax)
			{
       				xp1 = x + dx;
				xm1 = x - dx;
       				yp1 = (2.0 * (1.0 - 5.0 / 12.0 * dx * dx * k(x)) * y - (1.0 + dx * dx / 12.0 * k(xm1)) * ym1)/ (1.0 + dx * dx / 12.0 * k(xp1));
				xm1 = x; x = xp1;
			        ym1 = y; y = yp1;
        	        }
			snow = yp1;
			if (snow * sbefore < 0)
			{
				de = -0.1* de;
			}
			e += de;
		 	sbefore = snow;
		}
	cout << n << '\t' << a << '\t' << e <<'\n';
	a += 0.001;
	} while (a < 0.1);
  parity = 1 - parity;
  e += 1;	
  }
}

double k(double z)
{
   return -z*z - 2.0*a*z*z*z*z + 2.0*e;
}
