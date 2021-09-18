/*
** hw4_io.c:
**
** The source file implementing input and output functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/


#include "hw4_io.h"
#include <stdio.h>

int read_polynomial3(double * a0, double * a1, double * a2, double * a3)
{
	printf("Enter four coefficients: ");
	scanf("%lf %lf %lf %lf",a0,a1,a2,a3);
	return 0;
}
int read_polynomial4(double * a0, double * a1, double * a2, double * a3, double * a4)
{
	printf("Enter five coefficients: ");
	scanf("%lf %lf %lf %lf %lf",a0,a1,a2,a3,a4);
	return 0;
}
void write_polynomial3(double a0, double a1, double a2, double a3)
{
	if(a3 == -1)
		printf("-x^3");
	else if(a3 == 1)
		printf("x^3");
	else if(a3 != 0)
		printf("%.1fx^3",a3);

	if(a2 == -1)
		printf("-x^2");
	else if(a2 == 1)
		printf("+x^2");
	else if(a2 != 0){
		if(a2 < 0)
			printf("%.1fx^2",a2);
		else if(a3 == 0)
			printf("%1.fx^2",a2);
		else
			printf("+%.1fx^2",a2);
	}

	if(a1 == -1)
		printf("-x");
	else if(a1 == 1)
		printf("+x");
	else if(a1 != 0){
		if(a1 < 0)
			printf("%.1fx",a1);
		else if(a2 == 0 && a3 == 0)
			printf("%1.fx",a1);
		else
			printf("+%.1fx",a1);
	}

	if(a0 == -1)
		printf("-1");
	else if(a0 == 1)
		printf("+1");
	else if(a0 != 0){
		if(a0 < 0)
			printf("%.1f",a0);
		else if(a1 == 0 && a2 == 0 && a3 == 0)
			printf("%1.f",a0);
		else
			printf("+%.1f",a0);
	}

	printf("\n");
	 
}

void write_polynomial4(double a0, double a1, double a2, double a3, double a4)
{
	if(a4 == -1)
		printf("-x^4");
	else if(a4 == 1)
		printf("x^4");
	else if(a4 != 0)
		printf("%.1fx^4",a4);
	
	if(a3 == -1)
		printf("-x^3");
	else if(a3 == 1)
		printf("+x^3");
	else if(a3 != 0){
		if(a3 <0)
			printf("%1.fx^3",a3);
		else if(a4 == 0)
			printf("%1.fx^3",a3);
		else
			printf("+%1.fx^3",a3);
	}

	if(a2 == -1)
		printf("-x^2");
	else if(a2 == 1)
		printf("+x^2");
	else if(a2 != 0){
		if(a2 < 0)
			printf("%.1fx^2",a2);
		else if(a3 == 0 && a4 == 0)
			printf("%1.fx^2",a2);
		else
			printf("+%.1fx^2",a2);
	}

	if(a1 == -1)
		printf("-x");
	else if(a1 == 1)
		printf("+x");
	else if(a1 != 0){
		if(a1 < 0)
			printf("%.1fx",a1);
		else if(a2 == 0 && a3 == 0 && a4 == 0)
			printf("%1.fx",a1);
		else
			printf("+%.1fx",a1);
	}

	if(a0 == -1)
		printf("-1");
	else if(a0 == 1)
		printf("+1");
	else if(a0 != 0){
		if(a0 < 0)
			printf("%.1f",a0);
		else if(a1 == 0 && a2 == 0 && a3 == 0 && a4 == 0)
			printf("%1.f",a0);
		else
			printf("+%.1f",a0);
	}

	
}