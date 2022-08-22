#include <stdio.h>
#include <stdlib.h>

void swap(int **a)
{
	a[3] = a[1];
}

int main()
{
	/* int *a = malloc(sizeof(int) * 5);
	a[0] = 1;
	a[1] = 9;
	a[2] = 3;
	a[3] = 5;
	a[4] = 2;
	swap(a);
	printf("%d\n", a[3]);*/
	int **a = malloc(sizeof(int *) * 5);
	int i = 0;
/* 	while (i < 5)
	{
		a[i] = malloc(sizeof(int) * 2);
		i++;
	} */
	a[3] = malloc(sizeof(int) * 2);
	a[3][0] = 42;
	a[3][1] = 69;
	a[1] = a[3];
	//swap(a);
	printf("%d %d\n", a[1][0], a[1][1]);
}