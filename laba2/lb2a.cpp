#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#define arraysize 10000

void main(void){
	clock_t start, end; // объявляем переменные для определения времени выполнения
	int i = 0, j = 0, r;
	int arraysize[7] = {100, 200, 400, 1000, 2000, 4000, 10000};
	for (char j = 0 ; j < 7 ; j++){
		char* a = (char*)malloc(arraysize[j] * arraysize[j]);
		char* b = (char*)malloc(arraysize[j] * arraysize[j]);
		int* c = (int*)malloc(arraysize[j] * arraysize[j]*sizeof(int));
		int elem_c;
		//char a[arraysize][arraysize], b[arraysize][arraysize], c[arraysize][arraysize], elem_c;
	
			srand(time(NULL)); // инициализируем параметры генератора случайных чисеk
			while (i < arraysize[j])
			{
				while (j < arraysize[j])
				{
					*(a + i * arraysize[j] + j) = rand() % 100 + 1; // заполняем массив случайными числами
					*(b + i * arraysize[j] + j) = rand() % 100 + 1; // заполняем массив случайными числами
					j++;
				}
				i++;
			}
			start = clock();
			for (i = 0; i < arraysize[j]; i++)
			{
				for (j = 0; j < arraysize[j]; j++)
				{
					elem_c = 0;
					for (r = 0; r < arraysize[j]; r++)
					{
						elem_c = (int) elem_c + *(a + i * arraysize[j] + r) * *(b + i * arraysize[j] + j);
						*(c + i * arraysize[j] + j) = elem_c;
					}
				}
			}
			end = clock();
			double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
			printf("%i - Time spent:%lf s",arraysize[j], time_spent);
		free(a);
		free(b);
		free(c);
	}
}


