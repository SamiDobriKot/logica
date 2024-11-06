#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;

class List {
public:
	int data;
	List* next;

	List() {
	data = NULL;
	next = nullptr; 
	};
	List(int value) : data(value), next(nullptr) {};

	~List() {
		delete next;
	};

	void add(int value) {
		if (data == NULL) {
			data = value;
			return;
		}
		if (next == nullptr) {
			next = new List(value);
		}
		else next->add(value);
	}

	void setadd(int value) {
		if (data == NULL) {
			data = value;
			return;
		}
		else if (value == data) return;
		else if (value < data) {
			List* temp = next;
			next = new List(data);
			next->next = temp;
			data = value;
		}
		else if (next == nullptr && data != value) {
			next = new List(value);
		}
		else next->setadd(value);
	}

	bool isin(int value) {
		if (data == value) return true;
		else if (next != nullptr) return next->isin(value);
		return false;
	}

	void print() {
		cout << data << " ";
		if (next != nullptr) next->print();
		else {
			cout << endl;
			return;
		}
	};

};

class Graf {
public:
	char** mass;
	int size;
	int grafsize;
	char** incid;
	List* list;

	Graf() {
		grafsize = 0;
	};

	Graf(int yoursize) : size(yoursize) {
		mass = new char* [size];
		for (int i = 0; i < size; i++) {
			mass[i] = new char[size];
		}
	}

	void init(char yesno = 1) {
		mass = new char* [size];
		for (int i = 0; i < size; i++) {
			mass[i] = new char[size];
		}
		if (yesno == 1){
			list = new List[size];
			for (int i = 0; i < size; i++) {
				for (int j = i; j < size; j++) {
					if (i == j) mass[i][j] = 0;
					else mass[i][j] = mass[j][i] = rand() % 2;
					if (mass[i][j]) {
						grafsize++;
						mass[i][j] -= 2 * (rand() % 2);
						mass[j][i] = mass[i][j] * -1;
						list[i].add(j + 1);
						list[j].add(i + 1);
					}
				}
			}
		}
	}

	void print() {
		cout << endl;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				printf("%2i", mass[i][j]);
				//cout << (int)mass[i][j] << " ";
			}
			cout << endl;
		}
	}

	void clear() {
		for (int i = 0; i < size; i++) {
			delete(mass[i]);
		}
		delete(mass);
	}
};

Graf otojd(Graf g1, char p1, char p2) {
	Graf graph(g1.size - 1);
	{
		short temp = min(p1, p2);
		p1 = max(p1, p2);
		p2 = p1;
		p1 = temp;
	}
	int k, l;
	k = l = 0;
	for (int j = 0; j < graph.size; j++) {
		for (int i = 0; i < graph.size; i++) {
			if (j == p1) {
				if (g1.mass[p1][k] != 0 || g1.mass[p2][k] != 0) {
					if (g1.mass[p1][k] == -1 || g1.mass[p2][k] == -1) graph.mass[j][i] = -1;
					if (g1.mass[p1][k] == 1 || g1.mass[p2][k] == 1) graph.mass[j][i] = 1;
				} else graph.mass[j][i] = 0;
			} else if (i == p1) {
					if (g1.mass[l][p1] != 0 || g1.mass[l][p2] != 0) {
						if (g1.mass[l][p1] == -1 || g1.mass[l][p2] == -1) graph.mass[j][i] = -1;
						if (g1.mass[l][p1] == 1 || g1.mass[l][p2] == 1) graph.mass[j][i] = 1;
				} else graph.mass[j][i] = 0;
			} else {
				graph.mass[j][i] = g1.mass[l][k];
			}
//			cout << (int)graph.mass[j][i] << " " << ends;;
			k += (i != p2 - 1) ? 1 : 2;
		}
//		cout << endl;;

		l += (j != p2 - 1) ? 1 : 2;
		k = 0;
	}
	return graph;
}

List *otojdlist(List* ls, char p1, char p2, int size) {
	List* list = new List[size-1];
	{
		short temp = min(p1, p2);
		p1 = max(p1, p2);
		p2 = p1;
		p1 = temp;
	}
	int k = 0;
	for (int i = 0; i < size -1; i++) {
		if (i == p2) {
			List *temp = &ls[p2];
			while (temp != nullptr) {
				list[p1].setadd(temp->data <= p2 ? temp->data : temp->data - 1);
				temp = temp->next;
			}
			k++;
		}
		else {
			List* temp = &ls[i+k];
			while (temp != nullptr) {
				if (temp->data == p2 + 1) list[i].setadd(p1+1); else
				list[i].setadd(temp->data <= p2 ? temp->data : temp->data - 1);
				temp = temp->next;
			}
		}

	}
	return list;
}

Graf styag(Graf g1, char p1, char p2) {
	Graf graph(g1.size - 1);
	{
		short temp = min(p1, p2);
		p1 = max(p1, p2);
		p2 = p1;
		p1 = temp;
	}
	int k, l;
	k = l = 0;
	for (int j = 0; j < graph.size; j++) {
		for (int i = 0; i < graph.size; i++) {
			if (j == p1) {
				if (g1.mass[p1][k] != 0 || g1.mass[p2][k] != 0) {
					if (g1.mass[p1][k] == -1 || g1.mass[p2][k] == -1) graph.mass[j][i] = -1;
					if (g1.mass[p1][k] == 1 || g1.mass[p2][k] == 1) graph.mass[j][i] = 1;
				}
				else graph.mass[j][i] = 0;
			}
			else if (i == p1) {
				if (g1.mass[l][p1] != 0 || g1.mass[l][p2] != 0) {
					if (g1.mass[l][p1] == -1 || g1.mass[l][p2] == -1) graph.mass[j][i] = -1;
					if (g1.mass[l][p1] == 1 || g1.mass[l][p2] == 1) graph.mass[j][i] = 1;
				}
				else graph.mass[j][i] = 0;
			}
			else {
				graph.mass[j][i] = g1.mass[l][k];
			}
//			cout << (int)graph.mass[j][i] << " " << ends;;
			k += (i != p2 - 1) ? 1 : 2;
		}
//		cout << endl;;

		l += (j != p2 - 1) ? 1 : 2;
		k = 0;
	}
	graph.mass[p1][p1] = 0;
	return graph;
}

List *styaglist(List* ls, char p1, char p2, int size) {
	List* list = new List[size - 1];
	{
		short temp = min(p1, p2);
		p1 = max(p1, p2);
		p2 = p1;
		p1 = temp;
	}
	int k = 0;
	for (int i = 0; i < size - 1; i++) {
		if (i == p2) {
			List* temp = &ls[p2];
			while (temp != nullptr) {
				if (temp->data != p1+1 && temp->data != p2+1) list[p1].setadd(temp->data <= p2 ? temp->data : temp->data - 1);
				temp = temp->next;
			}
			k++;
		}
		else {
			List* temp = &ls[i + k];
			while (temp != nullptr) {
				if (i == p1 && (temp->data == p1 + 1 || temp->data == p2 + 1)) {
					temp = temp->next;
					continue;
				}
				if (temp->data == p2 + 1) list[i].setadd(p1 + 1); else
					list[i].setadd(temp->data <= p2 ? temp->data : temp->data - 1);
				temp = temp->next;
			}
		}

	}
	return list;
}

Graf rasch(Graf g1, char p) {
	Graf graph(g1.size + 1);
	for (int j = 0; j < graph.size; j++) {
		for (int i = j; i < graph.size; i++) {
			if (i == graph.size - 1) {
				graph.mass[j][i] = graph.mass[j][p];
				graph.mass[i][j] = graph.mass[j][i] * -1;

				if (i == j == graph.size - 1) graph.mass[j][i] = 0;
			}
			else {
				graph.mass[j][i] = g1.mass[j][i];
				graph.mass[i][j] = graph.mass[j][i] * -1;
			}
		}
	}
	return graph;
}

List *rashlist(List* ls, char p, int size) {
	List* list = new List[size + 1];
	for (int i = 0; i < size; i++) {
		list[i] = ls[i];
		if (list[i].isin(p+1)) list[i].setadd(size+1);
	}
	list[size] = ls[p];
	return list;

}

Graf obied(Graf g1, Graf g2) {
	Graf out(max(g1.size,g2.size));
	for (int i = 0; i < g1.size; i++) {
		for (int j = i; j < g1.size; j++) {
			out.mass[i][j] = out.mass[j][i] = g1.mass[i][j];
		}
	}
	for (int i = 0; i < g2.size; i++) {
		for (int j = i; j < g2.size; j++) {
			out.mass[i][j] = out.mass[j][i] = (g2.mass[i][j] == 1 || out.mass[i][j] == 1) ? 1 : 0;
		}
	}
	return out;
}

Graf peres(Graf g1, Graf g2) {
	Graf out(max(g1.size, g2.size));
	for (int i = 0; i < g1.size; i++) {
		for (int j = i; j < g1.size; j++) {
			out.mass[i][j] = out.mass[j][i] = g1.mass[i][j];
		}
	}
	for (int i = 0; i < g2.size; i++) {
		for (int j = i; j < g2.size; j++) {
			out.mass[i][j] = out.mass[j][i] = (g2.mass[i][j] == 1 && out.mass[i][j] == 1) ? 1 : 0;
		}
	}
	return out;
}

Graf colsumm(Graf g1, Graf g2) {
	Graf out(max(g1.size, g2.size));
	for (int i = 0; i < g1.size; i++) {
		for (int j = i; j < g1.size; j++) {
			out.mass[i][j] = out.mass[j][i] = g1.mass[i][j];
		}
	}
	for (int i = 0; i < g2.size; i++) {
		for (int j = i; j < g2.size; j++) {
			out.mass[i][j] = out.mass[j][i] = ((g2.mass[i][j] == 1) ^ (out.mass[i][j] == 1)) ? 1 : 0;
		}
	}
	return out;
}

Graf decmul(Graf g1, Graf g2) {
	Graf out(g1.size * g2.size);
	for (int x1 = 0; x1 < g1.size; x1++) {
		for (int x2 = 0; x2 < g2.size; x2++) {
			for (int y1 = 0; y1 < g1.size; y1++) {
				for (int y2 = 0; y2 < g2.size; y2++) {
					if ((x1 == y1 && g2.mass[x2][y2] == 1) || (x2 == y2) && g1.mass[x1][y1] == 1) 
						out.mass[x1 * g2.size + x2][y1 * g2.size + y2] = 1;
					else out.mass[x1 * g2.size + x2][y1 * g2.size + y2] = 0;
				}
			}
		}
	}
	
	return out;
}

void printtwo(Graf g1, Graf g2) {

	std::cout << std::endl;
	for (int i = 0; i < g1.size; i++) {
		for (int j = 0; j < g1.size; j++) {
			if (i == j) cout << " \033[90m#\033[0m";
			else printf("%2i",g1.mass[i][j]);
		}
		std::cout << std::endl;
	}
	std::cout << "\033[" << g1.size << "A";
	std::cout << "\033[" << g1.size * 2 + 6 << "C";

	for (int i = 0; i < g2.size; i++) {
		for (int j = 0; j < g2.size; j++) {
			if (i == j) cout << " \033[90m#\033[0m";
			else printf("%2i",g2.mass[i][j]);
		}
		std::cout << std::endl;
		std::cout << "\033[" << g1.size * 2 + 6 << "C";
	}
	if (g2.size < g1.size) std::cout << "\033[" << g1.size - g2.size << "B";
}

void printlist(List* ls, int size){
	for (int i = 0; i < size; i++) {
		cout << i + 1 << ": ";
		ls[i].print();
	}
}

int main() {
	system("chcp 1251");
	Graf graf[3];
	srand(time(NULL));
//	srand(6);

	cout << "Graphs will be the same size? Y\\n\n";
	char mode = _getch();
	switch (tolower(mode)) {
	case 'n':
	case '2': {
		cout << "Enter size of 1st graph: ";
		cin >> graf[0].size;
		cout << "Enter size of 2nd graph: ";
		cin >> graf[1].size;
		break;
	}
	default: {
		int size;
		cout << "Enter graph size: ";
		cin >> size;
		graf[0].size = graf[1].size = graf[2].size = size;
	}
	}

	//graf[0].size = 6;
	//graf[1].size = 6;

	graf[0].init();
	graf[1].init();

	//graf[0].print();
	//graf[2] = rasch(graf[0], 0);

	//graf[2].print();


	printtwo(graf[0], graf[1]);
	bool end = true;
	bool islist = false;
	while (end){
		if (!islist) cout << "\nWhat to do?\n1 - закончить, 2 - переключиться на списки, 3 - отождествление, 4 - стягивание, 5 - расщепления вершины\n\
6 - объеденение, 7 - пересечение, 8 - кольцевая сумма, 9 - декартово произведение\n";
		else cout << "\nWhat to do?\n1 - закончить, 2 - переключиться на графы, 3 - отождествление, 4 - стягивание, 5 - расщепления вершины\n";
		mode = _getch();
		switch (mode) {
		case '1':{
			end = 0;
			break;
		}
		case '2': {
			if (islist) {
				islist = false;
				printtwo(graf[0], graf[1]);
			}
			else{
				islist = true;
				cout << endl << "list of 1st matrix:" << endl;
				printlist(graf[0].list, graf[0].size);

				cout << endl << "list of 2nd matrix:" << endl;
				printlist(graf[1].list, graf[1].size);
			}
			break;
		}
		case '3': {
			short pick,p1,p2;
			if (islist) {
				cout << "Выберите с каким списком работать (1/2): ";
				cin >> pick;
				cout << "\nВыберите два узла: ";
				cin >> p1 >> p2;
				List* list = otojdlist(graf[pick - 1].list, p1 - 1, p2 - 1, graf[pick - 1].size);
				printlist(list, graf[pick - 1].size - 1);
				
			}
			else {
				cout << "Выберите с какой матрицей работать (1/2): ";
				cin >> pick;
				cout << "\nВыберите два узла: ";
				cin >> p1 >> p2;
				graf[2] = otojd(graf[pick-1], p1-1, p2-1);
				graf[2].print();
				graf[2].clear();
			}
			break;
		}
		case '4': {
			short pick, p1, p2;
			if (islist) {
			cout << "Выберите с какой матрицей работать (1/2): ";
				cin >> pick;
				cout << "\nВыберите два узла: ";
				cin >> p1 >> p2;
				while (graf->mass[p1][p2] != 1) {
					cout << "\nВыбраны неверные узлы.\n";
					cin >> p1 >> p2;
				}
				List* list = styaglist(graf[pick - 1].list, p1 - 1, p2 - 1, graf[pick - 1].size);
				printlist(list, graf[pick - 1].size - 1);
			}
			else {
				cout << "Выберите с какой матрицей работать (1/2): ";
				cin >> pick;
				cout << "\nВыберите два узла: ";
				cin >> p1 >> p2;
				while (graf->mass[p1][p2] != 1) {
					cout << "\nВыбраны неверные узлы.\n";
					cin >> p1 >> p2;
				}
				graf[2] = styag(graf[pick - 1], p1 - 1, p2 - 1);
				graf[2].print();
				graf[2].clear();
			}
			break;
		}
		case '5': {
			short pick, p;
			if (islist) {
				cout << "Выберите с каким списком работать (1/2): ";
				cin >> pick;
				cout << "\nВыберите узел: ";
				cin >> p;
				List* list = rashlist(graf[pick - 1].list, p - 1, graf[pick - 1].size);
				printlist(list, graf[pick - 1].size + 1);
			}
			else {
				cout << "Выберите с какой матрицей работать (1/2): ";
				cin >> pick;
				cout << "\nВыберите узел: ";
				cin >> p;
				graf[2] = rasch(graf[pick - 1], p - 1);
				graf[2].print();
				graf[2].clear();
			}
			break;
		}
		case '6': {
			graf[2] = obied(graf[0], graf[1]);
			graf[2].print();
			graf[2].clear();
			break;
		}
		case '7': {
			graf[2] = peres(graf[0], graf[1]);
			graf[2].print();
			graf[2].clear();
			break;
		}
		case '8': {
			graf[2] = colsumm(graf[0], graf[1]);
			graf[2].print();
			graf[2].clear();
			break;
		}
		case '9': {
			if (graf[0].size < graf[1].size) graf[2] = decmul(graf[0], graf[1]);
			else graf[2] = decmul(graf[1], graf[0]);
			graf[2].print();
			graf[2].clear();
			break;
		}
		}
	}

	graf[0].clear();
	graf[1].clear();
}