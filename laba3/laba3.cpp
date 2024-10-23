#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct node
{
	char inf[256];  // полезная информация
	int priority;
	struct node* next; // ссылка на следующий элемент 
};

struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка
int dlinna = 0;

struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];
	int prio;

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта ('.' чтобы закончить): \n");   // вводим данные
	scanf("%s", s);
	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	if (s[0] == '.') {
		printf("Окончание ввода\n");
		return(NULL);
	}
	strcpy(p->inf, s);

	printf("Введите приоритет объекта: \n");
	if (scanf("%i", &prio) == 0) prio = 0;
	p->priority = prio;

	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}
//a 0 b 1 v 0 n 3 m 1 d 0 .
void spstore(struct node* p)
{
	/*struct node* p = NULL;
	p = get_struct();*/
	if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL) // список уже есть, то вставляем в конец
	{
		struct node* search = head;
		while (search->priority > p->priority && search->next != NULL) {
			search = search->next;
		}
		if (search == head) {
			if (search->priority < p->priority) {
				p->next = search;
				head = p;
				if (search->next == NULL) last = search;
				return;
			}
			else {
				struct node* temp = search->next;
				search->next = p;
				p->next = temp;
				if (temp == NULL) last = p;
				return;
			}

		}
		if (search == last && search->priority > p->priority) {
			search->next = p;
			last = p;
			return;
		}
		struct node* prev = head;
		while (prev->next != search) {
			prev = prev->next;
		}
		prev->next = p;
		p->next = search;
		return;
		
	




		//if (search == head && search->priority > p->priority) {
		//	p->next = head;
		//	head = p;
		//	return;
		//}
		//if (search->next == null) {
		//	/*struct node* prev = head;
		//	while (prev->next != search){
		//		prev = prev->next;
		//	}
		//	prev->next = p;
		//	p->next = search;
		//	search->next = null;
		//	last = search;
		//	last->next = p;
		//	last = p;*/
		//	
		//}
		//else {
		//	p->next = search->next;
		//	search->next = p;
		//}
	}
	return;
}

void review(void)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		printf("Имя - %s, Приоритет - %i\n", struc->inf, struc->priority);
		struc = struc->next;
	}
	return;
}

struct node* find(char* name)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			return struc;
		}
		struc = struc->next;
	}
	printf("Элемент не найден\n");
	return NULL;
}

void del(char* name)
{
	struct node* struc = head; // указатель, проходящий по списку установлен на начало списка
	struct node* prev = NULL;// указатель на предшествующий удаляемому элемент
	int flag = 0;      // индикатор отсутствия удаляемого элемента в списке

	if (head == NULL) // если голова списка равна NULL, то список пуст
	{
		printf("Список пуст\n");
		return;
	}

	if (strcmp(name, struc->inf) == 0) // если удаляемый элемент - первый
	{
		flag = 1;
		head = struc->next; // установливаем голову на следующий элемент
		free(struc);  // удаляем первый элемент
		struc = head; // устанавливаем указатель для продолжения поиска
	}
	else
	{
		prev = struc;
		struc = struc->next;
	}

	while (struc) // проход по списку и поиск удаляемого элемента
	{
		if (strcmp(name, struc->inf) == 0) // если нашли, то
		{
			flag = 1;         // выставляем индикатор
			if (struc->next)  // если найденный элемент не последний в списке
			{
				prev->next = struc->next; // меняем указатели
				free(struc);		    // удаляем  элемент
				struc = prev->next; // устанавливаем указатель для продолжения поиска
			}
			else			// если найденный элемент последний в списке
			{
				prev->next = NULL; // обнуляем указатель предшествующего элемента
				free(struc);	// удаляем  элемент
				return;
			}
		}
		else // если не нашли, то
		{
			prev = struc; // устанавливаем указатели для продолжения поиска
			struc = struc->next;
		}
	}

	if (flag == 0)				// если флаг = 0, значит нужный элемент не найден
	{
		printf("Элемент не найден\n");
		return;
	}


}

int main() {

	system("chcp 1251");
	struct node* structura = get_struct();
	while (structura != NULL) {
		spstore(structura);
		structura = get_struct();
		//review();
	}
	review();
	char end = 0;
	getchar();
	while (end != 1) {
		printf("\n1 - продолжить, 2 - удалить, 3 - вывод");
		end = _getch();
		switch (end) {
		case '2': {
			printf("\nВведите удаляемый элемент: ");
			char search[265];
			scanf("%s", search);
			getchar();
			del(search);
			break;
		}
		case '3': {
			printf("\n");
			review();
			break;
		}
		default: {
			end = 1;
			break;
		}
		}
	}
}
