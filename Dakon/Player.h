#include <iostream>
#include <string>
using namespace std;

class Player {
private:
	string nama;
	int jumlah;
public:
	Player() {
		nama = "";
		jumlah = 0;
	}

	void setNama(string _nama){
		nama = _nama;
	}

	string getNama(){
		return nama;
	}

	void addBiji(){
		jumlah++;
	}

	int getJumlah(){
		return jumlah;
	}
};