#include <iostream>
#include <time.h>

class Graf {
public:
	char** mass;
	int size;
	int grafsize;
	char** incid;

	Graf() {
		grafsize = 0;
	};

	void init() {
		mass = new char* [size];
		for (int i = 0; i < size; i++) {
			mass[i] = new char[size];
		}
		for (int i = 0; i < size; i++) {
			for (int j = i; j < size; j++) {
				if (i == j) mass[i][j] = 0;
				else {
					grafsize += mass[i][j] =  rand() % 2;
					if (mass[i][j] == 0) mass[j][i] = 0;
					if (mass[i][j] == 1) {
						mass[i][j] -= 2 * (rand() % 2);
						mass[j][i] = mass[i][j] == 1 ? -1 : 1;
					}
				}
//				else mass[i][j] =  rand() % 2;
//				grafsize += mass[i][j];
			}
		}
		incid = new char* [size];
		for (int i = 0; i < size; i++) {
			incid[i] = new char[grafsize];
		}
		int s = 0;
		for (int i = 0; i < size; i++) {
			for (int j = i; j < size; j++) {
				if (mass[i][j] == 0) continue;
				for (int k = 0; k < size; k++) {//(k == j || k == i) ? incid[k][s] =  mass[i][j]: incid[k][s] = 0;
					if ((k == j || k == i) && mass[i][j] == 1) {
						incid[k][s] = -1;
						mass[i][j] = -1;
					} else
						if ((k == j || k == i) && mass[i][j] == -1) {
						incid[k][s] = 1;
						mass[i][j] = 1;
					}else incid[k][s] = 0;
				}
				s++;
			}
		}
	}
	void print() {
		std::cout << std::endl;
		for (int i = 0; i < size; i++) {
			int count = 0;
			for (int j = 0; j < size; j++) {
				if (i == j) std::cout << " #";
//				else std::cout << (int)mass[i][j] << " ";
				else printf("%2i",mass[i][j]);
				count += mass[i][j];
			}
//			std::cout << ":" << count << " ";
//			if (count == 0) std::cout << " Isolated";
//			if (count == 1) std::cout << " Alone";
//			if (count == size - 1) std::cout << " Dominating";

			std::cout << std::endl;
		}
		std::cout << "Graf size:" << grafsize << std::endl;
	}
	void printincid() {
		std::cout << std::endl;
		for (int i = 0; i < size; i++) {
			int count = 0;
			for (int j = 0; j < grafsize; j++) {
				//std::cout << (int)incid[i][j] << " ";
				printf("%2i", incid[i][j]);
				count += incid[i][j];
			}
//			std::cout << ":" << count << " ";
//			if (count == 0) std::cout << " Isolated";
//			if (count == 1) std::cout << " Alone";
//			if (count == size - 1) std::cout << " Dominating";
			std::cout << std::endl;
		}
	}
	void clear() {
		for (int i = 0; i < size; i++) {
			delete(mass[i]);
			delete(incid[i]);
		}
		delete(mass);
		delete(incid);
	}
};


int main() {
	Graf graf;
	srand(time(NULL)); 

	std::cout << "Enter graf size: ";
	std::cin >> graf.size;
	graf.init();
	graf.print();
	graf.printincid();


	graf.clear();
}