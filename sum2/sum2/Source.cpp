
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 256

int main(){

	char linebuf[BUFSIZE];
	double data=1;
	double sum = 0.0;
	double sum2 = 0.0;

	while (fgets(linebuf, BUFSIZE, stdin) != NULL){

		int AA=sscanf(linebuf, "%lf", &data);

		//sscanf(linebuf, "%lf", data);
		if ( AA != 0) {
			sum += data;
			sum2 += data*data;
			printf("%lf \t %lf \n", sum, sum2);

		}
	}
	return 0;
}