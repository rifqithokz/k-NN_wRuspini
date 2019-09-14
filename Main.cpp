#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>

#include <math.h>

using namespace std;

const bool decrement = false;
const bool increment = true;

bool tipeSorting;
int idx_element;

bool urutkan(const vector<int>& a, const vector<int>& b) {
	if (tipeSorting)return(a[idx_element] < b[idx_element]);
	else return(a[idx_element] > b[idx_element]);
}

int main() {
	int K = 1, x=0, y=0, jarak=0;
	char prosesLagi;
	string line;

	///////////////////////ambil dataset dari dataset.csv////////////////////////////////////////
	vector<vector<int>> dataSet;      /* vector of vector<int> for 2d array */
	ifstream f_dset("F:\\dataset.csv");	//sesuaikan nama dan alamat file

	while (getline(f_dset, line)) {         
		string val;                     
		vector<int> row;                
		stringstream s(line);          
		while (getline(s, val, ',')) {
			row.push_back(stoi(val));  
		}
		dataSet.push_back(row);        
	}
	f_dset.close();

	///////////////////////ambil dataset dari dataset.csv////////////////////////////////////////
	vector<vector<int>> dataClass;      
	ifstream f_class("F:\\class_label.csv");	//sesuaikan nama dan alamat file
	while (getline(f_class, line)) {    
		string val;                     
		vector<int> row;                
		stringstream s(line);          
		while (getline(s, val, ',')) {
			row.push_back(stoi(val));  
			row.push_back(0);
		}
		dataClass.push_back(row);      
	}
	f_class.close();

	while (true) {
		system("cls");
		idx_element = 0;
		tipeSorting = increment;
		sort(dataClass.begin(), dataClass.end(), urutkan);

		//inisialisasi data voting
		for (int i = 0; i < dataClass.size(); i++) {
			dataClass[i][1] = 0;
		}

		///////////////////////////////tentukan parameter K//////////////////////////////////////////
		cout << endl;
		cout << "Masukkan parameter k : "; cin >> K;
		cout << "Masukkan nilai attribut x : ";	cin >> x;
		cout << "Masukkan nilai attribut y : ";	cin >> y;
		
		///////////////////////////////hitung jarak euclidean////////////////////////////////////////
		//jarak = ((x-x1)^2) + ((y-y1)^2)
		vector<vector<int>> dataSet_w;
		int idx = 0;
		dataSet_w = dataSet;
		cout << endl;
		for (auto& row : dataSet_w) {
			jarak = (int)(pow(((double)dataSet_w[idx][0] - x), 2) +
	   					  pow(((double)dataSet_w[idx][1] - y), 2));

			dataSet_w[idx].push_back(jarak);
			idx++;
		}

		////////////////////Urutkan berdasarkan jarak terdekat dalam bentuk ranking//////////////////
		//cout << endl;
		//cout << "Sebelum diurutkan : " << endl;
		//for (auto& row : dataSet_w) {
		//	for (auto& val : row)
		//		cout << val << "  ";
		//	cout << endl;            
		//}

		//mengurutkan berdasarkan elemen ke-3 (jarak) yang ada di dalam vector.
		//sorting nya increment, mulai dari jarak yang terdekat/terkecil
		idx_element = 3;
		tipeSorting = increment;
		sort(dataSet_w.begin(), dataSet_w.end(), urutkan);
	
		//cout << endl;
		//cout << "Setelah diurutkan : " << endl;
		//for (auto& row : dataSet_w) {
		//	for (auto& val : row)
		//		cout << val << "  ";
		//	cout << endl;
		//}

		///////////////////////////////ambil NN sesuai jumlah parameter K////////////////////////////
		cout << endl;
		vector<vector<int>> rangking;
		for (int i = 0; i < K; i++) {
			rangking.push_back(dataSet_w[i]);
		}
		cout << endl;
		cout << "Data rangking NN : " << endl;
		cout << "---------------------------------" << endl;
		cout << "|attr-1 | attr-2 | class | jarak|" << endl;
		cout << "---------------------------------" << endl;
		for (auto& row : rangking) {
			for (auto& val : row)
				cout << "  " << val << "\t";
			cout << endl;
		}

		/////////////////////////////////Voting Class sesuai rangking NN/////////////////////////////
		cout << endl;
		idx = 0;
		for (auto& row : rangking) {
			for (int i = 1; i <= 4; i++) {
				if (row[2] == i)dataClass[i-1][1]++;
			}
		}
		cout << endl;
		cout << "Data Voting rangking NN : " << endl;
		for (int i = 0; i < dataClass.size();i++) {
			cout << "Class " << dataClass[i][0] << " : " << dataClass[i][1] << endl;
		}

		///////////////////////////////Hasil keputusan sesuai rangking NN////////////////////////////
		cout << endl;
		//mengurutkan berdasarkan elemen ke-1 (hasil voting) yang ada di dalam vector.
		//sorting nya increment, mulai dari hasil voting terbanyak
		idx_element = 1;
		tipeSorting = decrement;
		sort(dataClass.begin(), dataClass.end(), urutkan);
		cout << "Attribut x,y >> (" << x << ", " << y << ") merupakan class : " << dataClass[0][0] << endl;

		cout << endl << endl;
	inputUlang:
		cout << "Ingin mencoba dengan nilai attribut lain ? (y/n) : ";
		cin >> prosesLagi;
		if (prosesLagi == 'y' || prosesLagi == 'Y')continue;
		else if (prosesLagi == 'n' || prosesLagi == 'N')break;
		else {
			system("cls");
			goto inputUlang;
		}
	}

	system("pause");
	return 0;
}