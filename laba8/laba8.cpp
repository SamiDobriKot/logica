#include <iostream>
#include <queue>
#include <conio.h>
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

class List {
public:
	int data;
	List* next;

	List() {
		data = -1;
		next = nullptr;
	};
	List(int value) : data(value), next(nullptr) {};

	~List() {
		delete next;
	};

	void add(int value) {
		if (data == -1) {
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

	void delfirst() {
		data = next->data;
		if (next->next == nullptr) {
			delete next->next;
			next = nullptr;
		} else 
		next->delfirst();
	}

	int pop() {
		if (next == nullptr) {
			int out = data;
			data = -1;
			return out;
		}
		int out = data;
		delfirst();
		return out;
	}

	bool empty(){
		if (data == -1 && next == nullptr) return true; else return false;
	}

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
				cout << (int)mass[i][j] << " ";
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

	void posh(char type = 0) {
		Set set(size);

		while (!set.all()) {
			if (type == 0) BFS(set.firstfalse(), set);
			else if (type == 1) BFSlist(set.firstfalse(), set);
			else if (type == 2) BFSmylist(set.firstfalse(), set);
		}
	}
private:

	void BFS(int v, Set set) {
		queue<int> q;
		q.push(v);
		set.add(v);
		while (!q.empty()) {
			v = q.front();
			q.pop();
			cout << v + 1 << " " << ends;
			for (int i = 0; i < size; i++) {
				if (mass[v][i] == 1 && set.data[i] == false){
					q.push(i);
					set.add(i);
				}
			}
		}
	};

	void BFSlist(int v, Set set) {
		queue<int> q;
		q.push(v);
		set.add(v);
		while (!q.empty()){
			v = q.front();
			q.pop();
			cout << v + 1 << " " << ends;
			List* temp = &list[v];
			while (temp != nullptr) {
				if (set.data[temp->data - 1] == false) {
					q.push(temp->data - 1);
					set.add(temp->data - 1);
				}
				temp = temp->next;
			}
		}
	}

	void BFSmylist(int v, Set set) {
		List q;
		q.add(v);
		set.add(v);
		while (!q.empty()){
			v = q.pop();
			cout << v + 1 << " " << ends;
			List* temp = &list[v];
			while (temp != nullptr) {
				if (set.data[temp->data - 1] == false) {
					q.add(temp->data - 1);
					set.add(temp->data - 1);
				}
				temp = temp->next;
			}
		}
	}


};


int main() {
	Graf graf;
	srand(time(NULL));

	std::cout << "Enter graf size: ";
	std::cin >> graf.size;
	graf.init();
	graf.print();
	cout << endl;
	for (int i = 0; i < graf.size; i++) {
		cout << i + 1 << ": ";
		graf.list[i].print();
	}
	cout << endl << "Obhod grafa: " << endl;
	graf.posh();

	cout << endl << "Obhod list: " << endl;
	clock_t start, end;
	start = clock();
	graf.posh(1);
	end = clock();
	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\nIt took: " << time_spent << "s" << endl;

	cout << endl << "Obhod my queue: " << endl;
	start = clock();
	graf.posh(2);
	end = clock();
	time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\nIt took: " << time_spent << "s" << endl;


	graf.clear();
}