/** Commands
 * gcc test.c
 * size a.out
 * nm -s a.out
 */

#include <stdio.h>
#include <stdlib.h>

char pear[40];
static double peach;
int mango = 13;
static long melon = 2001;

int main(void)
{
	printf("This is a Runtime Test File.\n");
	
	int i=3, j, *ip;
	ip = malloc(sizeof(i));
	pear[5] = i;
	peach = 2.0 * mango;
	
	return 0;
}
