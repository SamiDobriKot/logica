#include <iostream>
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
	}
	Graf operator=(Graf &other);
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
	//		int count = 0;
			for (int j = 0; j < size; j++) {
				if (i == j) cout << "# ";
				else cout << (int)mass[i][j] << " ";
	//			count += mass[i][j];
			}
	//		if (count == 0) cout << "Isolated";
	//		if (count == 1) cout << "Alone";
	//		if (count == size - 1) cout << "Dominating";

			cout << endl;
		}
	//	cout << "Graf size:" << grafsize << endl;
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

Graf Graf::operator=(Graf &other){
	int minsize = min(Graf.size,other.size);
	for (int i = 0, i < minsize; i++){
	
	}
}

void otojd(Graf g1, Graf g2, char p1, char p2){
	for (int i = 0; i < g1.size; i++) {
		for (int j = 0; j < g1.size; j++) {
			
		}
	}
}

void printtwo(Graf g1, Graf g2){

	std::cout << std::endl;
	for (int i = 0; i < g1.size; i++) {
		for (int j = 0; j < g1.size; j++) {
			if (i == j) std::cout << "# ";
			else std::cout << (int)g1.mass[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "\033["<< g1.size <<"A";
	std::cout << "\033[" << g1.size*2 + 6 << "C";

	for (int i = 0; i < g2.size; i++) {
		for (int j = 0; j < g2.size; j++) {
			if (i == j) std::cout << "# ";
			else std::cout << (int)g2.mass[i][j] << " ";
		}
		std::cout << std::endl;
		std::cout << "\033[" << g2.size*2 + 6 << "C";
	}


}


int main() {
	Graf graf[3];
	char mode;
	srand(time(NULL));

	cout << "Graphs will be the same size? Y\n";
	cin >> mode;
	switch (tolower(mode)){
	case 'n':
	case '2':{
		cout << "Enter size of 1st graph: ";
		cin >> graf[0].size;
		cout << "Enter size of 2nd graph: ";
		cin >> graf[1].size;
		break;
	}
	default:{
		int size;
		cout << "Enter graph size: ";
		cin >> size;	
		graf[0].size = graf[1].size = graf[2].size = size;
	}
	}

//	size = 6;
	graf[0].init();
	graf[1].init();
	graf[2].init(0);
	printtwo(graf[0], graf[1]);
	cout << endl << "list of 1st matrix:" << endl;
	for (int i = 0; i < size; i++) {
		cout << i + 1 << ": ";
		graf[0].list[i].print();
	}
	cout << endl << "list of 2nd matrix:" << endl;
	for (int i = 0; i < size; i++) {
		cout << i + 1 << ": ";
		graf[1].list[i].print();
	}
	otojd(graf[0].mass, graf[1].mass, graf[2].mass, size);
	graf[2].print();

	graf[0].clear();
	graf[1].clear();
	getchar();
	getchar();
}
