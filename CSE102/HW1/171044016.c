#include <stdio.h>
#include <math.h>

#define PI 3.14

double circle_area(double radius);
double calc_hypotenuse(int side1, int side2);
double calc_radius_of_smallest_circle(int side1, int side2);
double calc_radius_of_largest_circle(int side1, int side2);
double calc_area_of_smallest_circle(int side1, int side2);
double calc_area_of_largest_circle(int side1, int side2);
double calc_area_of_smallest_square(int side1, int side2);
double calc_area_of_largest_square(int side1, int side2);
double calc_area_of_square (int side);
void display_results(double largest_circle,double largest_square,double smallest_circle,double smallest_square);


int main()
{
	/*We take the edges of the rectangle for coming-up uses.*/
	int side1,side2;
	printf("Enter first side for rectangle: ");
	scanf("%d",&side1);
	printf("Enter second side for rectangle: ");
	scanf("%d",&side2);
	
	display_results(calc_area_of_largest_circle(side1,side2),calc_area_of_largest_square(side1,side2),calc_area_of_smallest_circle(side1,side2),calc_area_of_smallest_square(side1,side2));
	return 0;
}
/*To calculate the circle area*/
double circle_area(double radius)
{
	double area;
	area = PI * pow(radius,2.0);

	return area;
}
/*It'll be used in calculating the radius of smallest circle*/
double calc_hypotenuse(int side1, int side2)
{
	double hypo;
	hypo = sqrt((pow(side1,2.0)+pow(side2,2.0)));
	return hypo;
}
/*To calculate the radius of the smallest circle that surrounds the recatngle*/
double calc_radius_of_smallest_circle(int side1, int side2)
{
	double radius;
	
	radius = calc_hypotenuse(side1,side2)/2.0;
	
	return radius;
}
/*To calculate the radius of the largest circle that fits in the rectangle*/
double calc_radius_of_largest_circle(int side1, int side2)
{ 
	double radius;
	if(side1<side2)
	{
		radius = side1 / 2.0;
	}
	else
	{
		radius = side2 / 2.0;
	}

	return radius;
}
/*By using calc_radius... func we calculate area*/
double calc_area_of_smallest_circle(int side1, int side2)
{
	double area;
	area = circle_area(calc_radius_of_smallest_circle(side1,side2));
	return area;
}
/*By using calc_radius... func we calculate area*/
double calc_area_of_largest_circle(int side1, int side2)
{
	double area;
	area = circle_area(calc_radius_of_largest_circle(side1,side2));
	return area;
}
/*by using area_of _square func we calculate the square area*/
double calc_area_of_smallest_square(int side1, int side2)
{
	double area;
	if(side1<side2)
	{
		area = calc_area_of_square(side2);
	}
	else
	{
		area = calc_area_of_square(side1);
	}

	return area;
}
/*to calculate the largest square which fits in the rectangle*/
double calc_area_of_largest_square(int side1, int side2)
{
	double area;
	if(side1<side2)
	{
		area = calc_area_of_square(side1);
	}
	else
	{
		area = calc_area_of_square(side2);
	}
	return area;
}
/*to calculate the area of the square*/
double calc_area_of_square(int side)
{
	int area;
	area = pow(side,2);
	return area;
}

void display_results(double largest_circle,double largest_square,double smallest_circle,double smallest_square)
{

/*to display results we call each area function*/
	printf("The area of the largest circle that fits inside a rectangle:\t\t %.2f\n",largest_circle);
	printf("The area of the largest square that fits inside the rectangle:\t\t %.2f\n",largest_square);
	printf("The area of the smallest circle that surrounds the same rectangle:\t %.2f\n",smallest_circle);
	printf("The area of the smallest square that surrounds the same rectangle:\t %.2f\n",smallest_square);	
}
