#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double polynomial(double x, int p, double* c)
{
	double y = 0;
	int i;

	for(i=0;i<=p;i++)
	{
		y +=  c[i] * pow(x,i);
	}

	return y;
}

int main(int argc, char**argv)
{

}