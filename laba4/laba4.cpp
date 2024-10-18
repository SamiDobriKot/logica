#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>


struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* root;

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
	if (r == NULL) {

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
	//if (data == r->data) return(root); // **безповторений**
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

	if (r == NULL) {
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
	while (r->right != NULL) {
		num++;
		r = find(r->right, d);
	}
	return(num);
}

struct Node* findlast(struct Node* r, int d, int* l) {
	if (r == NULL) {
		l = 0;
		return(NULL);
	}
	if (r->data == d) {
		*l = *l + 1;
		r = findlast(r->right, d, l);
		return(r);

	}
	if (r->data > d) {
		*l = *l + 1;
		findlast(r->right, d, l);
		return(r);
	}
	else {
		*l = *l + 1;
		findlast(r->left, d, l);
		return(r);
	}
}

int main()
{
	system("chcp 1251");
	setlocale(LC_ALL, "Russian");
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

	printf("Выберите что вы хотите сделать: \nНайти ветку по числу - 1\nНайти на каком самом низком уровне число - 2\nНайти количество вхождений числа - 3\n");
	char mode = _getch();
	printf("Введите число: ");
	switch (mode) {
	case '1': {
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
	case '2': {
		scanf("%i", &D);
		int l = 0;
		if (findlast(root, D, &l) == NULL) {
			printf("Число не найдено");
			return(0);
		}
		printf("Число %i находится в %i уровне", D, l);

		break;
	}
	default: {
		scanf("%d", &D);
		printf("Количество вхождений числа: %i", findhowmany(root, D));
	}
	}
	getchar();
	getchar();
}
//7 6 8 6 7 3 8 9 1 6 1 7 1 4 1 3 1 -1