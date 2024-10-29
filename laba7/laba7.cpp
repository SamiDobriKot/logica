#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;

class Set {
private:
	int setsize;

public:
	bool* data;
	
	Set() {};

	Set(int size) {
		setsize = size;
		data = new bool[size];
		for (int i = 0; i < size; i++) data[i] = false;
	};

	bool add(int newdata) {
		if (newdata <= setsize && newdata >= 0 && data[newdata] == false) {
			data[newdata] = true;
			return true;
		}
		else return false;

	}

	bool all() {
		for (int i = 0; i < setsize; i++) if (data[i] == false) return false;
	}

	int firstfalse() {
		for (int i = 0; i < setsize; i++) if (data[i] == false) return i;
	}

};

class Graf {
public:
	char** mass;
	int size;
	int grafsize;
	char** incid;

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
		if (yesno = 1) {
			for (int i = 0; i < size; i++) {
				for (int j = i; j < size; j++) {
					if (i == j) mass[i][j] = 0;
					else mass[i][j] = mass[j][i] = rand() % 2;
					if (mass[i][j]) {
						grafsize++;
					}
				}
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
				for (int k = 0; k < size; k++) (k == i) || (k == j) ? incid[k][s] = 1 : incid[k][s] = 0;
				s++;
			}
		}
	}

	void print() {
		cout << endl;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (i == j) cout << "# "; else
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

	void obhod(int start = 0,bool isincid = false) {
		Set set(size);
		
		if (isincid == false) DFS(start, set); 
		else DFSINCID(start, set);

		while (!set.all()) {
			if (isincid == false) DFS(set.firstfalse(), set);
			else DFSINCID(set.firstfalse(), set);
		}
	}

	void obhodnorec(int start = 0) {
		Set set(size);
		int r = start, prev = 0, a = 0;
		bool end = false;

		while (!set.all()) {
			end = false;
			for (int i = 0; i < size; i++) {
				if (set.add(r)) cout << r + 1 << " " << ends;
				if (mass[r][i] == 1 && set.data[i] == false) {
					r = i;
					end = true;
					break;
				}
			}
			if (!end) {	
				for (int i = 0;i<size; i++){
					if (mass[r][i] == 1){
							r = i;
							break;
						}
						
					} 
				r = set.firstfalse();
			}
		}
	}

private:
	void DFS(int v, Set set) {
		set.add(v);
		cout << v+1<< " " << ends;
		for (int i = 0; i < size; i++) {
			if (mass[v][i] == 1 && set.data[i] == false) DFS(i, set);
		}
	}

	void DFSINCID(int v, Set set) {
		set.add(v);
		cout << v + 1 << " " << ends;
		int r = 0;
		for (int i = 0; i < grafsize; i++) 
			if (incid[v][i] == 1) {
				r = i;
				break;
			}
		for (int i = v + 1; i < size; i++) {
			if (incid[i][r] == 1 && set.data[i] == false) DFSINCID(i, set);
		}
	}
};


int main() {
	system("chcp 1251");
	Graf graf;
	srand(time(NULL)); 
//	srand(1);

	std::cout << "Enter graf size: ";
	std::cin >> graf.size;
	graf.init();
	graf.print();
	graf.printincid();
	cout << "\nВведите начальную вершину: " << endl;
	int p;
	cin >> p;
	p--;
	cout << endl << "Обход матрицы смежности: " << endl;
	graf.obhod(p);
	cout << endl << "Обход матрицы инцидентности: " << endl;
	graf.obhod(p, true);
	cout << endl << "Обход без рекурсии: " << endl;
	graf.obhodnorec(p);
	getchar();
	getchar();
	
	graf.clear();
}