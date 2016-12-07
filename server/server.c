#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "start.h"
#define MAX_CLIENT 4

int main()
{
	int n;
	printf("1.START\n");
	printf("2.THEM CAU HOI\n");
	printf("3.SUA CAU HOI\n");
	printf("4.QUIT\n");
	scanf("%d",&n);
	while(getchar()!='\n');
	if(n==1) start_server();
} 