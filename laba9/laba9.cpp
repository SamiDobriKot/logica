#include <iostream>
#include <queue>
#include <time.h>

using namespace std;

class Set {
private:
	int setsize;

public:
	char* data;

	Set() {};

	Set(int size) {
		setsize = size;
		data = new char[size];
		for (int i = 0; i < size; i++) data[i] = -1;
	};

	bool add(int newdata) {
		if (newdata <= setsize && newdata >= 0 && data[newdata] == false) {
			data[newdata]++;
			return true;
		}
		else return false;

	}

	bool all() {
		for (int i = 0; i < setsize; i++) if (data[i] == -1) return false;
	}

	int firstfalse() {
		for (int i = 0; i < setsize; i++) if (data[i] == -1) return i;
	}

	void print() {
		for (int i = 0; i < setsize; i++) {
			cout << (int)data[i] << " " << ends;
		}
	}

};

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
		if (yesno == 1) {
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
			}
		}
	}

	void print() {
		cout << endl;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (i == j) cout << "\033[90m#\033[0m ";
				else cout << (int)mass[i][j] << " ";
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

	void posh(int v, bool islist = false) {
		Set dist(size);
		cout << endl;
		
		if (!islist) BFSD(v, dist);
		else BFSDlist(v, dist);
		
		cout << endl;
		dist.print();
	}

	void obhod(int v, bool islist = false) {
		Set dist(size);
		cout << endl;

		dist.data[v] = 0;

		if (!islist) DFS(v, dist);
		else DFSlist(v, dist);

		cout << endl;
		dist.print();
	}

private:
	void BFSD(int v, Set dist) {
		queue<int> q;
		q.push(v);
		dist.data[v] = 0;
		while (!q.empty()) {
			v = q.front();
			q.pop();
			cout << v + 1 << ", " << ends;
			for (int i = 0; i < size; i++) {
				if (mass[v][i] == 1 && dist.data[i] == -1) {
					q.push(i);
					dist.data[i] = dist.data[v] + 1;

				}

			}
		}

	}

	void BFSDlist(int v, Set dist){
		queue<int> q;
		q.push(v);
		dist.data[v] = 0;
		while (!q.empty()) {
			v = q.front();
			q.pop();
			cout << v + 1 << ", " << ends;
			List* temp = &list[v];
			while (temp != nullptr) {
				if (dist.data[temp->data - 1] == -1) {
					q.push(temp->data - 1 );
					dist.data[temp->data - 1] = dist.data[v] + 1;
				}
				else {
					temp = temp->next;
				}

			}
		}


	}

	void DFS(int v, Set set) {
		cout << v + 1 << ", " << ends;
		for (int i = 0; i < size; i++) {
			if (mass[v][i] == 1 && (set.data[i] == -1 || set.data[i] > set.data[v] + 1)) {
				set.data[i] = set.data[v] + 1;
				DFS(i, set);
			}
		}
	}

	void DFSlist(int v, Set set) {
		cout << v + 1 << ", " << ends;
		List* temp = &list[v];
		while (temp != nullptr) {
			if (set.data[temp->data - 1] == -1 || set.data[temp->data - 1] > set.data[v] + 1) {
				set.data[temp->data - 1] = set.data[v] + 1;
				DFSlist(temp->data - 1, set);
			}
			else temp = temp->next;
		}

	}
};




int main() {
	Graf graf;
	srand(time(NULL));

	std::cout << "Enter graf size: ";
	std::cin >> graf.size;
//	graf.size = 6;

	graf.init();
	graf.print();
	cout << endl;
	for (int i = 0; i < graf.size; i++) {
		cout << i + 1 << ": ";
		graf.list[i].print();
	}
	cout << endl << "Enter start point:\n";
	int p;
	cin >> p;
	p--;
	
	clock_t start, end;
	cout << "\nShirina, smejnost: ";
	start = clock();
	graf.posh(p);
	end = clock();
	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\nIt took: " << time_spent << "s" << endl;

	cout << "\n\nShirina, list: ";
	start = clock();
	graf.posh(p, true);
	end = clock();
	time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\nIt took: " << time_spent << "s" << endl;
	
	cout << "\n\nGlubina, smejnost: ";
	start = clock();
	graf.obhod(p);
	end = clock();
	time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\nIt took: " << time_spent << "s" << endl;
	
	cout << "\n\nGlubina, list: ";
	start = clock();
	graf.obhod(p, true); 
	end = clock();
	time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\nIt took: " << time_spent << "s" << endl;

	
	graf.clear();
}