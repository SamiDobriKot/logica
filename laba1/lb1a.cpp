#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	srand(time(NULL));
	int size_mass, max = -1000, min = 1000, mama=0;
	printf("enter array z\size: ");
	scanf("%i",&size_mass);
//	int *mass = (int *)malloc(sizeof(int)*size_mass);
	int **bigmass = (int **)malloc(sizeof(int*)*size_mass);
	for (int i = 0;i<size_mass;i++){
		*(bigmass+i*sizeof(int**)) = (int *)malloc(sizeof(int)*size_mass);
	}
	for (int j = 0; j < size_mass;j++){
		for (int i = 0; i < size_mass; i++){
			*(*(bigmass + j * sizeof(int**)) + i * sizeof(int*)) = rand() % 50;
			printf(" %i,", *(*(bigmass + j * sizeof(int**)) + i * sizeof(int*)));
		}
		printf("\n");
	}
	for (int j = 0; j < size_mass; j++) {
		for (int i = 0; i < size_mass; i++) {
			if (*(*(bigmass + j * sizeof(int**)) + i * sizeof(int*)) > max) max = *(*(bigmass + j * sizeof(int**)) + i * sizeof(int*));
			if (*(*(bigmass + j * sizeof(int**)) + i * sizeof(int*)) < min) min = *(*(bigmass + j * sizeof(int**)) + i * sizeof(int*));
			if (*(*(bigmass + j * sizeof(int**)) + i * sizeof(int*)) % 3 == 0) mama++;
		}
	}
	printf("\nmax: %i min: %i, diff = %i, count of mod 3: %i", max, min, max-min,mama);
	/*int a[2][10], otv;
	for (int i = 0; i<10;i++){
		a[0][i] = rand() % 100;
		a[1][i] = rand() % 100;
		otv = a[0][i] + a[1][i];
		printf("%i, %i, sum = %i\n", a[0][i],a[1][i], otv);
	}*/
	for (int i = 0; i < size_mass; i++) {
		free(*(bigmass + i * sizeof(int**)));
	}
	free(bigmass);
}
