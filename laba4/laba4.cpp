#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* root;

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
	if (r == NULL){

		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			printf("Ошибка выделения памяти");
			exit(0);
		}

		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;

		if (data > root->data)	root->left = r;
		else root->right = r;
		return r;
	}
	//if (data == r->data) return(root); // **без повторений**
	if (data > r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);

	return root;
}

void print_tree(struct Node* r, int l)
{

	if (r == NULL)
	{
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++)
	{
		printf(" - ");
	}

	printf(" %d \n", r->data);
	print_tree(r->left, l + 1);
}

struct Node* find(struct Node* r, int d) {

	if (r == NULL){
		return(NULL);
	}
	if (r->data == d) return(r); 
	if (r->data > d) {
		find(r->right, d);
	}
	else {
		find(r->left, d);
	}
}

int findhowmany(struct Node* r, int d) {
	r = find(r, d);
	if (r == NULL) return(0);
	int num = 1;
	while (r->right->data == d) {
		num++;
		r = r->right;
	}
	return(num);
}

int main()
{
	system("chcp 1251");
	int D, start = 1;

	root = NULL;
	printf("-1 - окончание построения дерева\n");
	while (start)
	{
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D == -1)
		{
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, D);

	}

	print_tree(root, 0);

	printf("Выберите что вы хотите сделать: \nНайти ветку по числу - 1\nНайти количество вхождений числа - 2\n");
	char mode = _getch();
	printf("Введите число: ");
	switch (mode) {
	case '1':{
		scanf("%d", &D);
		struct Node* temp = find(root, D);
		if (temp != NULL) {
			printf("Найденная ветка:\n");
			print_tree(temp, 0);
		}
		else {
			printf("Число не найдено!");
		}
		break;
	}
	default: {
		scanf("%d", &D);
		printf("Количество вхождений числа: %i", findhowmany(root, D));
	}
	}
}
