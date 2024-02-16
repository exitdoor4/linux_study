#include <stdio.h>
#include "include/calc_operations.h"

int main()
{
	int a,b;
	scanf("%d %d", &a, &b);

	printf("%d + %d = %d\n",a,b, add(a,b));

	printf("%d - %d= %d\n",a,b, sub(a,b));

	printf("%d * %d = %d\n",a,b, mult(a,b));

	printf("%d / %d  = %f\n", a,b,div(a,b));

}
