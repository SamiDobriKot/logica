#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>

void grafinit(char** g, int size) {

	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			if (i == j) {
				g[i][j] = 0;
				continue;
			}
			g[i][j] = g[j][i] = rand() % 2;
		}
	}
}

void printg(char** g, int size) {
	for (int i = 0; i < size; i++) {
		int count = 0;
		for (int j = 0; j < size; j++) {
			if (i == j) printf("# "); else printf("%i ", g[i][j]);
			count += g[i][j];
		}
		if (count == 0) printf("Isolated");	else
			if (count == 1) printf("Alone"); else
				if (count == size - 1) printf("Dominating"); else
					printf("Normal");
		printf("\n");
	}
}

int grafsize(char** g, int size) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		for (int j = i; j < size; j++) {
			count += g[i][j];
		}
	}
	return(count);
}

//int

int main() {

	srand(time(NULL));
	int size;
	printf("Enter size:");
	scanf("%i", &size);
	char** graf = { new char* [size] };
	for (int i = 0; i < size; i++) {
		graf[i] = new char[size];
	}
	grafinit(graf, size);
	printg(graf, size);
	printf("Graf size is: %i\n", grafsize(graf, size));

	char** m;


}
