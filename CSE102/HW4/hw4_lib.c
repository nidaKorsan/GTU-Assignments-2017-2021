/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/
#include <stdio.h>
#include "hw4_lib.h"
#define MAXINTRV 20000000
#define MININTRV -20000000


double integral(double f(double x), double xs, double xe, double delta)
{
	int i,n,check;
	double result=0.0,sum=0.0;
	n = (xe - xs) / delta;
	
	for(i = 0;i <= n; i ++){
		if(i == 0 || i == n)
			check = 1;
		else
			check = 2;
		sum += check * f(xs + (i * delta));
		
	}
	
	result = (delta / 2) * sum;

	return result;
}
double integral2(double f(double x, double y), double xs, double xe, double ys, double ye, double delta)
{
	int i,j,n,m,checkX,checkY;
	double result = 0.0,sum = 0.0;
	n = (xe - xs) / delta;
	m = (ye - ys) / delta;
	for(i = 0; i <= n ; i++){
		if(i == 0 || i == n)
			checkX = 1;
		else
			checkX = 2;
		for(j = 0; j <= m ; j++){
			if(j == 0 || j == m)
				checkY = 1;
			else
				checkY = 2;

			sum += checkX * checkY * f((xs + (i * delta)),(ys + (j * delta)));

		}
	}
	result = (delta / 2) * (delta / 2) * sum;

	return result;
}
int derivatives(double f(double a), double x, double eps, double * d1, double * d2)
{
	if(eps == 0)
		return -1;
	*d1 = ( f(x + eps) - f(x - eps) ) / ( 2 * eps );
	*d2 = ( f(x + eps) - 2 * f(x) + f(x - eps) ) / ( eps * eps );
	return 1;
}
int compare_derivatives(double f(double a), double d1(double b), double d2(double b), double x, double eps, double * e1, double *e2)
{
	double d_1,d_2,check1,check2;
	if(-1 == derivatives(f,x,eps,&d_1,&d_2))
		return -1;
	check1 = d1(x) - d_1;
	check2 = d2(x) - d_2;
	if(check1 > 0)
		*e1 = check1;
	else
		*e1 = check1 * -1;
	if(check2 > 0)
		*e2 = check2;
	else
		*e2 = check2 * -1;
	return 1;
}
double findAbsolute(double num){/*This function is for absolute value,my intent was not using any extra libraries.*/
	if(num < 0)
		return -1 * num;
	else
		return num;
}
double derivativePoly(double f(double a),double x,int which){/*For usage in find_roots function.Takes a function, x value for numeric derivation and which for which degree*/ 
	
	double eps = 0.1;
	if(findAbsolute(x) > 1000)
		eps = 100000;
	if(which == 0)
		return f(x);
	else if(which == 1){
		return (f(x + eps)-f(x - eps)) / (2 * eps);
	}
	else {
		return (derivativePoly(f,x + eps,which-1) - derivativePoly(f,x - eps,which-1)) / (2 * eps);
	}

}
double bisection(double f(double fi(double x),double x,int which),double fi(double x),double which ,double min,double max)
{/*For usage in find_roots function. Finds the root of an interval.*/
	double fMin = f(fi,min,which);
	double fMax = f(fi,max,which);
	double mid,fMid,eps = 0.001;
	int rootFound = 0;
	if(f(fi,min,which) * f(fi,max,which) > 0){
		printf("No compatible root in this interval:%f,%f\n",min,max);
		return -100;
	}
	else{
		while(findAbsolute(fMax - fMin) > eps && rootFound==0)
		{
			mid = (max + min) / 2.0;
			fMid = f(fi,mid,which);
			if(findAbsolute(fMid) < eps){
				rootFound = 1;
				
			}
			else if(fMid * fMin < 0){
				max = mid;
				fMax = fMid;
			}
			else{
				min = mid;
				fMin = fMid;
			}	
		}
		return mid;
	}
}
int find_roots(double f(double x), double * x1, double * x2, double * x3, double * x4)
{	
	double intrv1,intrv2,intrv3,intrv4,intrv5,intrv6, j;/*for intervals*/
	int i,count,rootNumber;

	for(i = 0; i <= 5; i++ ){
		count =0;
		for(j = 5.00 ; j < 16 ; j += 5.0){
			if(findAbsolute(derivativePoly(f,j,i)) < 0.1)
				count++;		
		}
		if(count == 3){
			rootNumber = i -1;
			break;
		}

	}
	switch(rootNumber){/*Here we call bisection for finding intervals from numeric derivation.The process depends on root number. This works for upmost 4th degree polynomials.*/
		case 1:
			*x1 = bisection(derivativePoly,f,0,MININTRV,MAXINTRV);
			*x2 = 0;
			*x3 = 0;
			*x4 = 0;
			return rootNumber;
		case 2:	
			intrv1 = bisection(derivativePoly,f,1,MININTRV,MAXINTRV);
			*x1 = bisection(derivativePoly,f,0,MININTRV,intrv1);
			*x2 = bisection(derivativePoly,f,0,intrv1,MAXINTRV);
			*x3 = 0;
			*x4 = 0;
			return rootNumber;
		case 3:	
			intrv1 = bisection(derivativePoly,f,2,MININTRV,MAXINTRV);

			intrv2 = bisection(derivativePoly,f,1,MININTRV,intrv1);
			intrv3 = bisection(derivativePoly,f,1,intrv1,MAXINTRV);

			*x1 = bisection(derivativePoly,f,0,MININTRV,intrv2);
			*x2 = bisection(derivativePoly,f,0,intrv2,intrv3);
			*x3 = bisection(derivativePoly,f,0,intrv3,MAXINTRV);
			*x4 = 0;
			return rootNumber;
		case 4:
			intrv1 = bisection(derivativePoly,f,3,MININTRV,MAXINTRV);

			intrv2 = bisection(derivativePoly,f,2,MININTRV,intrv1);
			intrv3 = bisection(derivativePoly,f,2,intrv1,MAXINTRV);

			intrv4 = bisection(derivativePoly,f,1,MININTRV,intrv2);
			intrv5 = bisection(derivativePoly,f,1,intrv2,intrv3);
			intrv6 = bisection(derivativePoly,f,1,intrv3,MAXINTRV);

			*x1 = bisection(derivativePoly,f,0,MININTRV,intrv4);
			*x2 = bisection(derivativePoly,f,0,intrv4,intrv5);
			*x3 = bisection(derivativePoly,f,0,intrv5,intrv6);
			*x4 = bisection(derivativePoly,f,0,intrv6,MAXINTRV);
			return rootNumber;
		default:
			*x1 = 0;
			*x2 = 0;
			*x3 = 0;
			*x4 = 0;
			return 0;

	}
}