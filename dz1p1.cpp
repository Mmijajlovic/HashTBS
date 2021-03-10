#include <iostream>

using namespace std;

// main functios fwd
void formTable(int *&, bool *&, int &, int &);
void insertKey(int *&, bool *&, int &, int &);
void findKey(int *&, bool *&, int &, int &);
void deleteKey(int *&, bool *&, int &, int &);
void print(int *&, bool *&, int &, int &);


int main() {
	int option, *table, size, c;
	bool *vector,created=false;
	
	cout << "\n Izaberite jednu od opcija: \n [1] Formiranje tabele \n [2] Umetanje kljuca \n [3] Pretraga kljuca \n [4] Brisanje kljuca \n [5] Ispis \n [0] Kraj \n ";
	cin >> option;
	while (option != 0) {
		switch (option)
		{
		case 1:
			if (!created) {
				formTable(table, vector, size, c);
				created = true;
			}
			else {
				cout << "\n Tabela je vec formirana." << endl;
			}
			break;
		case 2:	
			if (created) {
				insertKey(table, vector, size, c);
			}
			else {
				cout << "\n Tabela nije formirana." << endl;
			}
			break;
		case 3:
			if (created) {
				findKey(table, vector, size, c);
			}
			else {
				cout << "\n Tabela nije formirana." << endl;
			}
			break;
		case 4:
			if (created) {
				deleteKey(table, vector, size, c);
			}
			else {
				cout << "\n Tabela nije formirana." << endl;
			}
			break;
		case 5:
			print(table, vector, size, c);
			break;
		default:cout << "\n Izabrana opcija ne postoji!";
			break;
		}
		cout << "\n Izaberite jednu od opcija: \n [1] Formiranje tabele \n [2] Umetanje kljuca \n [3] Pretraga kljuca \n [4] Brisanje kljuca \n [5] Ispis \n [0] Kraj \n ";
		cin >> option;
	}
	return 0;
}

/*
 * Utility functions.
 */

int binarySearch(int *&table, bool *&vector, int &size, int &c, int &key) {
	int low = 0, mid, high = size * c - 1;

	while (low <= high) { // moguca greska
		mid = (low + high) / 2;
		if (key == table[mid]) {
			//while (key == table[mid] && vector[mid] == false) mid--;
			return mid;
		}
		else if (key < table[mid]) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	return mid;
}

void expandTable(int *&table, bool *&vector, int &size, int &c) {
	size = size * 2 ; 
	int *temp = new int[size*c];
	bool *pom = new bool[size*c];

	for (int i = 0; i < size*c/2; i++) {
		temp[2 * i ] = table[i];
		pom[2 * i ] = vector[i];
		temp[2 * i + 1] = table[i];
		pom[2 * i + 1] = false;
	}
	delete[] table;
	delete[] vector;
	table = temp;
	vector = pom;
}

/*
 * Main menu functions.
 */

void formTable(int *&table, bool *&vector, int &size, int &c) {


	cout << "\n Unesite velicinu tabele" << endl;
	cin >> size;
	cout << "\n Unesite faktor uvecanja" << endl;
	cin >> c;
	
	table = new int[size*c];
	vector = new bool[size*c];

	for (int i = 0; i < size*c; i++) {
		if (i % c == 0) {
			cout << "\n Unesite " << i << ". broj: "  ;
			cin >> table[i];
			vector[i] = true;
		}
		else {
			table[i] = table[i - 1];
			vector[i] = false;
		}
	}
}

void insertKey(int *&table, bool *&vector, int &size, int &c) {
	int key;
	bool full = true;
	cout << "\n Unesite vrednost novog kljuca" << endl;
	cin >> key;
	int index = binarySearch(table, vector, size, c, key);

	for (int i = 0; i < size*c; i++) {
		if (vector[i] == false) {
			full = false;
			break;
		}
	}
	if (index < 0) { // prvi element u nizu
		index = 0;
	}

	if (index >= size*c) { // poslednji element u nizu
		index = size * c - 1;
	}

	if (table[index] == key) {
		while (index > 0 && table[index - 1] == key) index--; // trazimo najlevlji primerak broja
		vector[index] = true;
		return;
	}
	
	if (table[index] != key && vector[index] == false) {
		table[index] = key;
		vector[index] = true;
		for (int i = index + 1 ; i < size*c && vector[i] == false; i++) {
			table[i] = key;
		}
		return;
	}

	if (table[index] != key && vector[index] == true) {
		
		if (full) {
			expandTable(table, vector, size, c);
			index = index * 2;
		}
		if (key>table[index]) {
			
			bool flag=false;
			for (int i = index + 1; i < size*c; i++) { 
				if (vector[i] == false) {
					for (int j = i; j > index + 1; j--) {
						table[j] = table[j - 1];
						vector[j] = vector[j - 1];
					}
					index++;
					flag = true;
					break;
				}					
			}
			if (!flag) {
				for (int i = index - 1; i>= 0; i--) {
					if (vector[i] == false) {
						for (int j = i; j < index; j++) {
							table[j] = table[j + 1];
							vector[j] = vector[j + 1];
						}
						break;
					}
					
				}
			}
			
		}
		else if (key < table[index]) {
			
			bool flag = false;
			for (int i = index - 1; i >= 0; i--) {
				if (vector[i] == false) {
					for (int j = i; j < index - 1; j++) {
						table[j] = table[j + 1];
						vector[j] = vector[j + 1];
					}
					index--;
					flag = true;
					break;
				}
					
			}
				
			if (!flag) {
				for (int i = index + 1; i < size*c; i++) {
					if (vector[i] == false) {
						for (int j = i; j > index; j--) {
							table[j] = table[j - 1];
							vector[j] = vector[j - 1];
						}
						break;
					}
				}
			}
			
		}
		table[index] = key;
		vector[index] = true;
		// kopije desno
		for (int i = index + 1; i < size*c && vector[i] == false; i++) {
			table[i] = key;
		}

		
	}
}

void findKey(int *&table, bool *&vector, int &size, int &c) {
	int key;

	cout << "\n Unesite vrednost  kljuca" << endl;
	cin >> key;
	int index = binarySearch(table, vector, size, c, key);
	while (table[index] == key && vector[index] == false && index > 0)index--;
	if (table[index] == key) {
		cout << "Kljuc je pronadjen na lokaciji " << index << ".";
	}
	else {
		cout << "Kljuc nije pronadjen";
	}
}

void deleteKey(int *&table, bool *&vector, int &size, int &c) {
	int key;

	cout << "\n Unesite vrednost  kljuca" << endl;
	cin >> key;
	int index = binarySearch(table, vector, size, c, key);
	while (table[index] == key && vector[index] == false && index > 0)index--;
	if (table[index] == key) { // samo slucaj kada postoji validna kopija na pocetku podniza
		vector[index] = false;
	}
}

void print(int *&table, bool *&vector, int &size, int &c) {
	for (int i = 0; i < size*c; i++) {
		cout << table[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < size*c; i++) {
		cout << vector[i] << "\t";
	}
	cout << endl;
}