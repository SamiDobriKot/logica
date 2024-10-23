#include <iostream>
#include <conio.h>
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
	int grafsize = 0;
	char** incid;
	List* list;

	Graf() {};

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
		if (yesno = 1){
			list = new List[size];
			for (int i = 0; i < size; i++) {
				for (int j = i; j < size; j++) {
					if (i == j) mass[i][j] = 0;
					else mass[i][j] = mass[j][i] = rand() % 2;
					if (mass[i][j]) {
						grafsize++;
						list[i].add(j + 1);
						list[j].add(i + 1);
					}
				}
				//			list[i].print();
			}
		}
		/*incid = new char* [size];
		for (int i = 0; i < size; i++) {
			incid[i] = new char[grafsize];
		}
		int s = 0;
		for (int i = 0; i < size; i++) {
			for (int j = i; j < size; j++) {
				if (mass[i][j] == 0) continue;
				for (int k = 0; k < size; k++) (k == i) || (k == j) ? incid[k][s] = 1 : incid[k][s] = 0;
				s++;
			}
		}*/
	}

	void print() {
		cout << endl;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << (int)mass[i][j] << " ";
			}
			cout << endl;
		}
	}

	void printincid() {
		std::cout << std::endl;
		for (int i = 0; i < size; i++) {
			int count = 0;
			for (int j = 0; j < grafsize; j++) {
				std::cout << (int)incid[i][j] << " ";
				count += incid[i][j];
			}
			if (count == 0) std::cout << "Isolated";
			if (count == 1) std::cout << "Alone";
			if (count == size - 1) std::cout << "Dominating";
			std::cout << std::endl;
		}
	}

	void clear() {
		for (int i = 0; i < size; i++) {
			delete(mass[i]);
		//	delete(incid[i]);
		}
		delete(mass);
		//delete(incid);
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
			if (j == p1) graph.mass[p1][i] = graph.mass[i][p1] = (g1.mass[p1][k] == 1 || g1.mass[p2][k] == 1) ? 1 : 0;
			else graph.mass[j][i] = graph.mass[i][j] = g1.mass[l][k];
			k += (i != p2-1) ? 1 : 2;
		}
		l += (j != p2-1) ? 1 : 2;
		k = 0;
	}
	return graph;
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
			if (j == p1) graph.mass[p1][i] = graph.mass[i][p1] = (g1.mass[p1][k] == 1 || g1.mass[p2][k] == 1) ? 1 : 0;
			if (j == p1 && j == i) graph.mass[j][i] = 0;
			else graph.mass[j][i] = graph.mass[i][j] = g1.mass[l][k];
			k += (i != p2 - 1) ? 1 : 2;
		}
		l += (j != p2 - 1) ? 1 : 2;
		k = 0;
	}
	return graph;
}

void printtwo(Graf g1, Graf g2) {

	std::cout << std::endl;
	for (int i = 0; i < g1.size; i++) {
		for (int j = 0; j < g1.size; j++) {
			if (i == j) std::cout << "\033[90m#\033[0m ";
			else std::cout << (int)g1.mass[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "\033[" << g1.size << "A";
	std::cout << "\033[" << g1.size * 2 + 6 << "C";

	for (int i = 0; i < g2.size; i++) {
		for (int j = 0; j < g2.size; j++) {
			if (i == j) std::cout << "\033[90m#\033[0m "; else
			std::cout << (int)g2.mass[i][j] << " ";
		}
		std::cout << std::endl;
		std::cout << "\033[" << g1.size * 2 + 6 << "C";
	}
	if (g2.size < g1.size) std::cout << "\033[" << g1.size - g2.size << "B";
}


int main() {
	system("chcp 1251");
	Graf graf[3];
//	srand(time(NULL));

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

	//	size = 6;
	graf[0].init();
	graf[1].init();
	printtwo(graf[0], graf[1]);
	bool end = true;
	bool islist = false;
	while (end){
		cout << "\nWhat to do?\n1 - закончить, 2 - переключиться на списки, 3 - отождествление, 4 - стягивание, 5 - расщепления вершины\n";
		mode = _getch();
		switch (mode) {
		case '1':{
			end = 0;
			break;
		}
		case '2': {
			islist = true;
			cout << endl << "list of 1st matrix:" << endl;
			for (int i = 0; i < graf[0].size; i++) {
				cout << i + 1 << ": ";
				graf[0].list[i].print();
			}
			cout << endl << "list of 2nd matrix:" << endl;
			for (int i = 0; i < graf[1].size; i++) {
				cout << i + 1 << ": ";
				graf[1].list[i].print();
			}
			break;
		}
		case '3': {
			short pick,p1,p2;
			if (islist) {
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
			}
			else {
				cout << "Выберите с какой матрицей работать (1/2): ";
				cin >> pick;
				cout << "\nВыберите два узла: ";
				cin >> p1 >> p2;
				graf[2] = styag(graf[pick - 1], p1 - 1, p2 - 1);
				graf[2].print();
				graf[2].clear();
			}
			break;
		}
		}
		
		
		
	}

	graf[0].clear();
	graf[1].clear();
}