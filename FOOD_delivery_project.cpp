#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class Produs
{
private:
	int static id_produs;
	char* denumire;
	float cantitate;
	float pret;
public:

	int getid_produs()
	{
		return id_produs;
	}

	static void set_id_produs(const int id_produs_x)
	{
		id_produs = id_produs_x;
	}

	char* getdenumire()
	{
		return denumire;
	}


	void setdenumire(char* d)
	{
		if (this->denumire) delete[]this->denumire;
		denumire = new char[strlen(d) + 1];
		strcpy(this->denumire, d);
	}

	float getcantitate() {
		return cantitate;
	}
	void setcantitate(float cantitate)
	{
		if (cantitate > 0)
		{
			this->cantitate = cantitate;
		}
		else throw "Cantitate prea putina. /n";
	}

	//get si set pentru preturi
	float getpret() {

		return pret;
	}
	void setpreturi(float pret) {
		if (pret > 0) {
			this->pret = pret;
		}
		else throw "Nu exista produs /n";
	}

	//constructor fara parametri
	Produs()
	{
		this->denumire = new char[strlen("NU are denumire") + 1];
		strcpy(this->denumire, "NU are denumire");
		this->cantitate = 0;
		this->pret = 0;
		this->id_produs++;
	}

	//constructor cu parametri
	Produs(const char* denumire_x, float cantitate)
	{
		this->denumire = new char[strlen(denumire_x) + 1];
		strcpy(this->denumire, denumire_x);
		this->cantitate = cantitate;
		this->pret = 0.00;
		this->id_produs++;
	}


	//constructor cu parametri
	Produs(const char* denumire, float cantitate, float pret)
	{
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->cantitate = cantitate;
		this->pret = pret;
		this->id_produs++;
	}


	//constructor cu parametri
	Produs(int id_produs, const char* denumire, float cantitate, float pret)
	{
		this->id_produs = id_produs;
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->cantitate = cantitate;
		this->pret = pret;
	}

	//constructor de copiere
	Produs(Produs& c)
	{
		this->id_produs = c.getid_produs();
		this->denumire = new char[strlen(c.denumire) + 1];
		strcpy(this->denumire, c.denumire);
		this->cantitate = c.cantitate;
		this->pret = c.pret;
	}

	//~Destructor
	~Produs()
	{
		if (this->denumire)
			delete[]this->denumire;
		id_produs++;
	}

	//operator =
	Produs operator=(const Produs& p)
	{
		if (denumire != NULL)
			delete[]denumire;
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy(this->denumire, p.denumire);

		this->cantitate = p.cantitate;
		this->pret = p.pret;

		return *this;
	}

	//operator+
	Produs operator +(int val)
	{
		Produs p = *this;
		p.pret = this->pret + val;
		return p;
	}

	//operator ++
	Produs operator ++()
	{
		this->pret++;
		return *this;
	}
	//operator >>
	friend istream& operator>>(istream& cin, Produs& p)
	{
		char buffer[70];
		cout << "Denumire: ";
		cin >> buffer;
		if (p.denumire)
			delete[]p.denumire;
		p.denumire = new char[strlen(buffer) + 1];
		strcpy(p.denumire, buffer);
		cout << "Cantitate: ";
		cin >> p.cantitate;
		cout << "Pret: ";
		cin >> p.pret;
		return cin;
	}

	//operator<<
	friend ostream& operator<<(ostream& cout, Produs& p)
	{
		cout << "Id_produs: " << p.getid_produs() << endl;
		cout << "Denumire: " << p.getdenumire() << endl;
		cout << "Cantitate: " << p.getcantitate() << " gr" << endl;
		cout << "Pret: " << p.getpret() << " RON" << endl;
		return cout;
	}


	//afisare fisier
	friend ofstream& operator<<(ofstream& ecran, Produs& p)
	{
		ecran << p.getid_produs() << endl;
		ecran << p.getdenumire() << endl;
		ecran << p.getcantitate() << endl;
		ecran << p.getpret() << endl;
		return ecran;
	}

	//citirea din tastatura fisier
	friend ifstream& operator>>(ifstream& in, Produs& p) {
		char buffer[50];
		in >> buffer;
		if (p.denumire)
			delete[]p.denumire;
		p.denumire = new char[strlen(buffer + 1)];
		strcpy(p.denumire, buffer);
		in >> p.cantitate;
		in >> p.pret;
		return in;
	}

	void write() {
		ofstream out;
		out.open("Produse.csv", ios::app);
		out << this->id_produs << ",";
		out << this->denumire << ",";
		out << this->cantitate << ",";
		out << this->pret << endl;
		out.close();
	}
};

class RegistruProduse {
	int numar_produse;
	Produs** produse;
public:
	RegistruProduse() {
		this->numar_produse = 0;
		this->produse = NULL;
	}

	int get_numar_produse() {
		return this->numar_produse;
	}
	void setnumar_produse(int numar_produse) {
		if (numar_produse > 0)
		{
			this->numar_produse = numar_produse;
		}
	}

	~RegistruProduse() {
		delete[] this->produse;
	}

	void adauga_produs(Produs* p) {
		Produs** temp;
		temp = new Produs * [this->numar_produse + 1];
		for (int i = 0; i < this->numar_produse; i++) {
			temp[i] = this->produse[i];
		}
		temp[this->numar_produse] = p;
		this->numar_produse++;
		if (this->produse) {
			delete[] this->produse;
		}
		this->produse = temp;
	}

	void stergere_produs(string nume_produs) {
		Produs** lista_produse_actualizata;
		lista_produse_actualizata = new Produs * [this->numar_produse - 1];
		ofstream out;
		out.open("Produse.csv", ofstream::out | ofstream::trunc);
		out.close();

		for (int i = 0; i < this->numar_produse; i++) {
			Produs* produs_iterat;
			produs_iterat = this->produse[i];
			if (nume_produs != produs_iterat->getdenumire())
			{
				lista_produse_actualizata[i] = this->produse[i];
				this->produse[i]->write();
			}
		}
		this->numar_produse--;
		if (this->produse) {
			delete[] this->produse;
		}
		this->produse = lista_produse_actualizata;
	}


	void stergere_dupa_denumire_produs(string denumire_produs) {
		int  produs_gasit = false;
		for (int i = 0; i < this->numar_produse; i++) {
			if (this->produse[i]->getdenumire() == denumire_produs) {
				produs_gasit = true;
				this->stergere_produs(denumire_produs);
				cout << "Produsul " << denumire_produs << " a fost sters din meniu!" << endl;
			}
		}

		if (!produs_gasit) { cout << "Produsul " << denumire_produs << " nu este in meniu!" << endl; }
	}

	void afisare_produs() {
		cout << "Registrul de produse contine: " << endl;
		for (int i = 0; i < this->numar_produse; i++) {
			cout << this->produse[i]->getid_produs() << ", " << produse[i]->getdenumire() << ", " << produse[i]->getcantitate() << ", " << produse[i]->getpret() << endl;
		}
	}

	void afisare_Comanda() {
		cout << "Comanda contine: " << endl;
		for (int i = 0; i < this->numar_produse; i++) {
			cout << this->produse[i]->getdenumire() << ", " << produse[i]->getcantitate() << ", " << produse[i]->getpret() << endl;
		}
	}

	void afisare_meniu() {
		cout << "Alegeti un produs din meniu: " << endl;
		cout << "#########################################################" << endl;
		cout << "## " << left << setw(12) << "Cod Produs" << left << setw(18) << "Denumire" << left << setw(10) << "Pret:RON" << left << setw(10) << "Cantitate:gr" << "##" << endl;
		for (int i = 0; i < this->numar_produse; i++) {
			cout << "## " << left << setw(12) << i << left << setw(20) << produse[i]->getdenumire() << left << setw(10) << produse[i]->getpret() << left << setw(10) << produse[i]->getcantitate() << "##" << endl;
		}
		cout << "#########################################################" << endl;
	}

	Produs cautare_dupa_denumire_produs(string denumire_produs) {
		bool produs_gasit = false;
		for (int i = 0; i < this->numar_produse; i++) {
			if (this->produse[i]->getdenumire() == denumire_produs) {
				produs_gasit = true;
				cout << "Produsul " << denumire_produs << " a fost adaugat cu succes in comanda!" << endl;
				return *this->produse[i];
			}
		}

		if (!produs_gasit) { cout << "Produsul " << denumire_produs << " nu este in meniu!" << endl; }
	}

	void read() {
		ifstream in;
		in.open("Produse.csv", ifstream::in);

		char caracter_citit = in.get();
		char valoare_coloana[10000];
		int pozitia_caracter_col = 0;
		int numar_coloana = 0;
		bool coloana_cu_comma = false;

		Produs* produs_citit;
		produs_citit = new Produs();

		while (in.good()) {
			if (caracter_citit == '"') {
				coloana_cu_comma = !coloana_cu_comma;
				caracter_citit = in.get();
				continue;
			}

			if (caracter_citit == '\n') {
				valoare_coloana[pozitia_caracter_col] = '\0';
				pozitia_caracter_col = 0;
				produs_citit->setpreturi(atof(valoare_coloana));
				numar_coloana = 0;

				this->adauga_produs(produs_citit);
				produs_citit = new Produs();
				Produs produs_citit;
			}

			if (caracter_citit == ',' && coloana_cu_comma == false) {
				valoare_coloana[pozitia_caracter_col] = '\0';
				pozitia_caracter_col = 0;
				switch (numar_coloana) {
				case 0: {
					produs_citit->set_id_produs(atoi(valoare_coloana));
				}break;
				case 1: {
					produs_citit->setdenumire(valoare_coloana);
				}break;
				case 2: {
					produs_citit->setcantitate(atoi(valoare_coloana));
				}break;

				}
				numar_coloana++;
			}
			else {
				valoare_coloana[pozitia_caracter_col] = caracter_citit;
				pozitia_caracter_col++;
			}
			caracter_citit = in.get();
		}
		in.close();
	}


};


class Utilizator {
private:
	string nume_utilizator;
	string parola;
	string tip_utilizator;
	string nume;
	string prenume;

public:

	string get_nume_utilizator() {
		return nume_utilizator;
	}

	string get_parola() {
		return parola;
	}

	string get_tip_utilizator() {
		return tip_utilizator;
	}

	string get_nume() {
		return nume;
	}

	string get_prenume() {
		return prenume;
	}

	void set_nume_utilizator(string nume_utilizator_x) {
		if (nume_utilizator_x.length() >= 4) {
			this->nume_utilizator = nume_utilizator_x;
		}
		else throw "Nume utilizator trebuie sa contina cel putin 4 caractere!";
	}

	void set_parola(string parola_x) {
		if (parola_x.length() >= 6) {
			this->parola = parola_x;
		}
		else throw "Parola trebuie sa contina cel putin 6 caractere!";
	}

	void set_tip_utilizator(string tip_utilizator_x) {
		this->tip_utilizator = tip_utilizator_x;
	}

	void set_nume(string nume_x) {
		this->nume = nume_x;
	}

	void set_prenume(string prenume_x) {
		this->prenume = prenume_x;
	}

	Utilizator()
	{
		this->nume_utilizator = "NULL";
		this->parola = "NULL";
		this->tip_utilizator = "NULL";
		this->nume = "NULL";
		this->prenume = "NULL";

	}

	Utilizator(string nume_utilizator_x, string parola_x, string tip_utilizator_x, string nume_x)
	{
		this->nume_utilizator = nume_utilizator_x;
		this->parola = parola_x;
		this->tip_utilizator = tip_utilizator_x;
		this->nume = nume_x;
		this->prenume =" ";
	}
   
	Utilizator(string nume_utilizator_x, string parola_x, string tip_utilizator_x, string nume_x, string prenume_x)
	{
		this->nume_utilizator = nume_utilizator_x;
		this->parola = parola_x;
		this->tip_utilizator = tip_utilizator_x;
		this->nume = nume_x;
		this->prenume = prenume_x;
	}

	Utilizator(Utilizator& u)
	{
		this->nume_utilizator = u.nume_utilizator;
		this->parola =u.parola;
		this->tip_utilizator = u.tip_utilizator;
		this->nume = u.nume;
		this->prenume = u.prenume;
	}

	Utilizator operator=(const Utilizator& u) 
	{
		this->nume_utilizator = u.nume_utilizator;
		this->parola = u.parola;
		this->tip_utilizator = u.tip_utilizator;
		this->nume = u.nume;
		this->prenume = u.prenume;
		return *this;
	}

	~Utilizator() {}

	bool operator==(Utilizator &u)
	{
		return this->nume_utilizator == u.nume_utilizator;
	}

	friend ostream& operator<<(ostream& cout, Utilizator& u)
	{
		cout << "Nume de utilizator este: " << u.get_nume_utilizator() << endl;
		cout << "Tip utilizator este: " << u.get_tip_utilizator() << endl;
		cout << "Nume este: " << u.get_nume() << endl;
		cout << "Prenume este: " << u.get_prenume() << endl;
		return cout;
	}

	friend istream& operator>>(istream& cin, Utilizator& u)
	{
		cout << "Nume de utilizator: ";
		cin >> u.nume_utilizator;
		cout << "Introduceti parola: ";
		cin >>u.parola;
		cout << "Nume: ";
		cin >> u.nume;
        cout << "Prenume: ";
		cin >> u.prenume;
		cout << "Succes! Bine ati venit in aplicatia Food Delivery! '_'" << endl;
        return cin;
	}

	friend ofstream& operator<<(ofstream& ecran, Utilizator& u)
	{
		ecran << u.get_nume_utilizator() << endl;
		ecran << u.get_parola() << endl;
		ecran << u.get_tip_utilizator() << endl;
		ecran << u.get_nume() << endl;
		ecran << u.get_prenume() << endl;
		ecran << endl;
		return ecran;
	}
	

	void scriere_fisier() {
		ofstream out;
		out.open("Utilizatori.csv", ios::app);
		out << this->nume_utilizator << ",";
		out << this->parola << ",";
		out << this->tip_utilizator << ",";
		out << this->nume << ",";
		out << this->prenume;
		out << endl;
		out.close();
	}

	void citirea_fisier() {
		ifstream in;
		Utilizator utilizator;
		in.open("Utilizatori.csv", ios::in);
		in.seekg(0);
		in.read((char*)& utilizator, sizeof(Utilizator));
		cout <<utilizator.get_nume_utilizator();
		cout << utilizator.get_parola();
		cout << utilizator.get_tip_utilizator();
		cout << utilizator.get_nume();
		cout << utilizator.get_prenume();
		in.close();
	}

};

class RegistruUtilizatori {
	int numar_utilizatori;
	Utilizator** utilizatori;
public:
	RegistruUtilizatori() {
		this->numar_utilizatori = 0;
		this->utilizatori = NULL;
	}

	int get_numar_utilizatori() {
		return this->numar_utilizatori;
	}
	void set_numar_utilizatori(int numar_utilizatori) {
		if (numar_utilizatori > 0)
		{
			this->numar_utilizatori = numar_utilizatori;
		}
	}

	~RegistruUtilizatori() {
		delete[] this->utilizatori;
	}

	void adauga_utilizator(Utilizator* u) {
		Utilizator** temp;
		temp = new Utilizator * [this->numar_utilizatori + 1];
		for (int i = 0; i < this->numar_utilizatori; i++) {
			temp[i] = this->utilizatori[i];
		}
		temp[this->numar_utilizatori] = u;
		this->numar_utilizatori++;
		if (this->utilizatori) {
			delete[] this->utilizatori;
		}
		this->utilizatori = temp;
	}

	void afisare_utilizatori() {
		cout << "Registrul de utilizatori contine: " << endl;
		cout << left << setw(16) << "nume_utilizator" << left << setw(16) << "tip_utilizator" << left << setw(16) << "nume" << left << setw(16) << "prenume" << endl;
		for (int i = 0; i < this->numar_utilizatori; i++) {
			cout << left << setw(16) << this->utilizatori[i]->get_nume_utilizator() << left << setw(16) << utilizatori[i]->get_tip_utilizator() << left << setw(16) << utilizatori[i]->get_nume() << left << setw(16) << utilizatori[i]->get_prenume() << endl;
		}
	}

	bool verifiricare_utilizator_si_parola(string nume_utilizator_x, string parola_x ) {
		bool utilizator_gasit = false;
		bool autentificare_reusita = false;
		for (int i = 0; i < this->numar_utilizatori; i++) {
			if (this->utilizatori[i]->get_nume_utilizator() == nume_utilizator_x) {
				utilizator_gasit = true;

				if (this->utilizatori[i]->get_parola() == parola_x) { 
					autentificare_reusita = true;
					cout << "Autentificare cu succes!" << endl;
				}
				else { cout << "Parola este gresita!" << endl; }

				i = this->numar_utilizatori;
			}
		}

		if (!utilizator_gasit) { cout << "Utilizatorul " << nume_utilizator_x << " nu este inregistrat in sistem!" << endl; }
		return autentificare_reusita;
	}

	void creare_utilizator_nou() {
		Utilizator utilizator_nou;
		utilizator_nou.set_tip_utilizator("normal");

		string nume_utilizator;
		string parola;
		string nume;
		string prenume;

		bool utilizator_existent = false;
		do 
		{	
			utilizator_existent = false;
			cout << "Nume de utilizator: ";
			cin >> nume_utilizator;		
			for (int i = 0; i < this->numar_utilizatori; i++) {
				if (nume_utilizator == utilizatori[i]->get_nume_utilizator() || nume_utilizator == "admin") {
					cout << "Acest nume de utilizator deja exista in sistem!" << endl;
					utilizator_existent = true;
					break;
				}
			}

		} while (utilizator_existent);
		utilizator_nou.set_nume_utilizator(nume_utilizator);

		cout << "Introduceti parola: ";
		cin >> parola;
		utilizator_nou.set_parola(parola);

		cout << "Nume: ";
		cin >> nume;
		utilizator_nou.set_nume(nume);

		cout << "Prenume: ";
		cin >> prenume;
		utilizator_nou.set_prenume(prenume);
		this->adauga_utilizator(&utilizator_nou);
		utilizator_nou.scriere_fisier();
	}

	void read_utilizator() {
		ifstream in;
		in.open("Utilizatori.csv", ifstream::in);

		char caracter_citit = in.get();
		char valoare_coloana[10000];
		int pozitia_caracter_col = 0;
		int numar_coloana = 0;
		bool coloana_cu_comma = false;

		Utilizator* utilizatori_citit;
		utilizatori_citit = new Utilizator();

		while (in.good()) {
			if (caracter_citit == '"') {
				coloana_cu_comma = !coloana_cu_comma;
				caracter_citit = in.get();
				continue;
			}

			if (caracter_citit == '\n') {
				valoare_coloana[pozitia_caracter_col] = '\0';
				pozitia_caracter_col = 0;
				utilizatori_citit->set_prenume(valoare_coloana);
				numar_coloana = 0;

				this->adauga_utilizator(utilizatori_citit);
				utilizatori_citit = new Utilizator();
			}

			if (caracter_citit == ',' && coloana_cu_comma == false) {
				valoare_coloana[pozitia_caracter_col] = '\0';
				pozitia_caracter_col = 0;
				switch (numar_coloana) {
				case 0: {
					char nume_utilizator[1000];
					if (valoare_coloana[0] == '\n') {strcpy(valoare_coloana, valoare_coloana+1); }
					utilizatori_citit->set_nume_utilizator(valoare_coloana);
				}break;
				case 1: {
					utilizatori_citit->set_parola(valoare_coloana);
				}break;
				case 2: {
					utilizatori_citit->set_tip_utilizator(valoare_coloana);
				}break;
				case 3: {
					utilizatori_citit->set_nume(valoare_coloana);
				}break;

				}
				numar_coloana++;
			}
			else {
				valoare_coloana[pozitia_caracter_col] = caracter_citit;
				pozitia_caracter_col++;
			}
			caracter_citit = in.get();
		}
		in.close();
	}

};


class Comanda {
private:
	int const TVA;
	int static id_comanda;
	string nume_utilizator;
	string nume_produs;
	RegistruProduse *produse;
	int cantitate_produs;
	int numar_total_produse;
	float valoarea_comanda;
	string data_comenzii;
public:
	
	int get_TVA() {
		return TVA;
	}

	int  getid_comanda() {
		return id_comanda;
	} 

	string getnume_utilizator() {
		return nume_utilizator;
	}
	void setnume_utilizator(string nume) {
		this->nume_utilizator = nume;
	}

	string getnume_produs() {
		return nume_produs;
	}
	void setnume_produs(string nume_produs) {
		this->nume_utilizator = nume_produs;
	}
 
	float getvaloarea_comanda() {
		return valoarea_comanda;
	}
	void setvaloarea_comanda(float valoarea_comanda) {
		if (valoarea_comanda > 0) {
			this->valoarea_comanda = valoarea_comanda;
		}
		else throw "Nu exista produse alese /n";
	}

	int get_cantitate_produs() {
		return cantitate_produs;
	}
	void set_cantitate_produs(int cantitate_produs) {
		if (cantitate_produs > 0)
		{
			this->cantitate_produs = cantitate_produs;
		}
	}

	int get_numar_total_produse() {
		return numar_total_produse;
	}

	void set_numar_total_produse(int numar_total_produse) {
		if (numar_total_produse > 0)
		{
			this->numar_total_produse = numar_total_produse;
		}
	}

	string get_data_comenzii() {
		return data_comenzii;
	}
	void set_data_comenzii(string data_comenzii) {
		this->data_comenzii = data_comenzii;
	}

    //constructor fara parametri
	Comanda() :TVA(9)
	{   
		id_comanda++;
		this->nume_utilizator = "NULL";
		this->nume_produs = "NULL";
		this->cantitate_produs = 0;
		this->numar_total_produse = 0;
		this->produse = NULL;
		this->valoarea_comanda = 0;
		this->data_comenzii = "NULL";
	}

	Comanda(string nume_utilizator, string nume_produs, int cantitate_produs, int numar_total_produse, RegistruProduse* produs, string data_comenzii) :TVA(9) {
		this->nume_utilizator = nume_utilizator;
		this->nume_produs = nume_produs;
		this->cantitate_produs = cantitate_produs;
		this->numar_total_produse = numar_total_produse;
		produse = new RegistruProduse[this->numar_total_produse + 1];
		for (int i = 0; i < numar_total_produse; i++) {
			this->produse[i]= produs[i];
		}
		this->valoarea_comanda = 0;
		this->data_comenzii = data_comenzii;
		this->id_comanda++;
	}
	
	Comanda(string nume_utilizator, string nume_produs, int cantitate_produs, int numar_total_produse, RegistruProduse* produs, int valoarea_comanda, string data_comenzii) :TVA(9) {
		this->nume_utilizator = nume_utilizator;
		this->nume_produs = nume_produs;
		this->cantitate_produs = cantitate_produs;
		this->numar_total_produse = numar_total_produse;
		produse = new RegistruProduse[this->numar_total_produse + 1];
		for (int i = 0; i < numar_total_produse; i++) {
			this->produse[i] = produs[i];
		}
		this->valoarea_comanda = valoarea_comanda;
		this->data_comenzii = data_comenzii;
		this->id_comanda++;
	}
	
	
	Comanda operator=(const Comanda& co) {
		this->nume_utilizator = co.nume_utilizator;
		this->nume_produs = co.nume_produs;
		this->cantitate_produs = co.cantitate_produs;
		if (produse) {
			delete[] produse;
		}	
		this->numar_total_produse =co.numar_total_produse;
		this->nume_utilizator = co.nume_utilizator;
		numar_total_produse = co.numar_total_produse;
		produse = new RegistruProduse[co.numar_total_produse];
		for (int i = 0; i < co.numar_total_produse; i++) {
			produse[i] = co.produse[i];
		}
		this->valoarea_comanda = co.valoarea_comanda;
		this->data_comenzii = co.data_comenzii;
		return *this;
	}
	// destructor ... distrugere de obiecte 
	~Comanda() {
		
		id_comanda--;
	}
	
	//metode de prelucrare
	//float valoarea_totala() {
	//	float s = 0;
	//	for (int i = 0; i < this->numar_total_produse; i++)
	//		s = s +this->produse.produse[i].get_numar_produse();
	//	return s;
	//}
  
	//float cantitate_totala() {
	//	float c=0;
	//	for (int i = 0; i < this->numar_total_produse; i++)
	//		c = c + this->produse[i].getcantitate();
	//	return c;
	//}
};

int Produs::id_produs = 0;
int Comanda::id_comanda = 0;

int meniu_login() {
	cout << "#######################################################" << endl;
	cout << "###### Bun venit in aplicatia Food Delivery ###########" << endl;
	cout << "#######################################################" << endl;
	cout << "## Logheaza-te ca:                          ###########" << endl;
	cout << "## 1. administrator                         ###########" << endl;
	cout << "## 2. utilizator normal                     ###########" << endl;
	cout << "## 3. creeaza utilizator nou                ###########" << endl;
	cout << "## Alege una dintre optiuni (1, 2, 3)!      ###########" << endl;
	cout << "#######################################################" << endl;
	cout << "#######################################################" << endl;
	cout << "#######################################################" << endl;
	cout << "## Parola pentru admin este: parola123 ################" << endl;
	cout << "## User normal pentru test:            ################" << endl;
	cout << "## nume_utilizator: andrei             ################" << endl;
	cout << "## parola:          parola123          ################" << endl;
	cout << endl;
	cout << "Optiunea ta este: ";
	int optiunea_aleasa;
	cin >> optiunea_aleasa;
	return optiunea_aleasa;
}

void afisare_meniu_admin() {
	cout << "1. adauga produs nou" << endl;
	cout << "2. listeaza meniul" << endl;
	cout << "3. sterge produs din meniu" << endl;
	cout << "4. listeaza utilizatorii" << endl;
	cout << "0. revenire la meniul principal" << endl;	
}

void meniu_administrator() {
	RegistruProduse meniu;
	meniu.read();

	Utilizator admin("admin", "parola123", "admin", "Administrator", "Administrator");
	Utilizator test_user1("andrei", "parola123", "normal", "Popescu", "Andrei");
	Utilizator test_user2("alex", "parola123", "normal", "Ionescu", "Alexandru");
	RegistruUtilizatori lista_utilizatori;
	lista_utilizatori.read_utilizator();
	lista_utilizatori.adauga_utilizator(&test_user1);
	lista_utilizatori.adauga_utilizator(&test_user2);

	string parola_admin;
	cout << "Introduceti parola de administrator: ";
	cin >> parola_admin;
	if (parola_admin == admin.get_parola()) {
		int optiunea_aleasa;
		afisare_meniu_admin();

		do {
			cout << "Alegeti o optiune din meniu: ";
			cin >> optiunea_aleasa;
			cout << endl;

			if (optiunea_aleasa == 1) {
				Produs produs_nou;
				cin >> produs_nou;
				meniu.adauga_produs(&produs_nou);
				produs_nou.write();
			}

			if (optiunea_aleasa == 2) {
				RegistruProduse meniu;
				meniu.read();
				meniu.afisare_meniu();
			}

			if (optiunea_aleasa == 3) {
				RegistruProduse meniu;
				meniu.read();
				string denumire_produs;
				cout << "Introduceti denumirea produsului: ";
				cin >> denumire_produs;
				meniu.stergere_dupa_denumire_produs(denumire_produs);
			}

			if (optiunea_aleasa == 4) {
				lista_utilizatori.afisare_utilizatori();
			}

		} while (optiunea_aleasa != 0);
	}
	else { cout << "Parola este gresita!" << endl; }
}


void afisare_meniu_utilizator_normal() {
	cout << "1. listeaza meniul" << endl;
	cout << "2. adauga comanda" << endl;
	cout << "0. revenire la meniul principal" << endl;
}

void meniu_utilizator_normal() {
	RegistruProduse meniu;
	meniu.read();

	Utilizator test_user1("andrei", "parola123", "normal", "Popescu", "Andrei");
	Utilizator test_user2("alex", "parola123", "normal", "Ionescu", "Alexandru");
	RegistruUtilizatori lista_utilizatori;
	lista_utilizatori.read_utilizator();
	lista_utilizatori.adauga_utilizator(&test_user1);
	lista_utilizatori.adauga_utilizator(&test_user2);


	string nume_user;
	string parola;
	cout << "Introduceti nume de utilizator: ";
	cin >> nume_user;
	cout << "Introduceti parola: ";
	cin >> parola;
	bool autentificare_reusita = lista_utilizatori.verifiricare_utilizator_si_parola(nume_user, parola);
	if (autentificare_reusita) {
		cout<<endl << "Bun venit " << nume_user << endl;
		cout << "Aici alegi produse din meniu pentru comanda: " << endl;
		afisare_meniu_utilizator_normal();
		int optiunea_aleasa;

		do {
			cout << "Alegeti o optiune din meniu: ";
			cin >> optiunea_aleasa;
			cout << endl;

			if (optiunea_aleasa == 1) {
				meniu.afisare_meniu();
			}

			if (optiunea_aleasa == 2) {
				cout << "Se creeaza comanda ... " << endl;
				Comanda comanda_noua;
				string produs_ales;
				comanda_noua.setnume_utilizator(nume_user);
				RegistruProduse produse_selectate;
				Produs produs_selectat;
				int adauga_inca_un_produs = 0;
				do
				{
					cout << "Alegeti un produs din meniu (dupa nume): ";
					cin >> produs_ales;
					produs_selectat = meniu.cautare_dupa_denumire_produs(produs_ales);
					produse_selectate.adauga_produs(&produs_selectat);
					cout << "Mai adaugati alt produs in comanda (1-da/0-nu): ";
					cin >> adauga_inca_un_produs;

				} while (adauga_inca_un_produs == 1);
			
				produse_selectate.afisare_Comanda();
				
				
			}
		} while (optiunea_aleasa != 0);
	}
	else { cout << "Parola este gresita!" << endl; }
}

void meniu_creare_utilizator() {

	RegistruProduse meniu;
	meniu.read();

	Utilizator test_user1("andrei", "parola123", "normal", "Popescu", "Andrei");
	Utilizator test_user2("alex", "parola123", "normal", "Ionescu", "Alexandru");
	RegistruUtilizatori lista_utilizatori;
	lista_utilizatori.read_utilizator();
	lista_utilizatori.adauga_utilizator(&test_user1);
	lista_utilizatori.adauga_utilizator(&test_user2);

	lista_utilizatori.creare_utilizator_nou();
	cout << "Logheaza te in sistem cu utilizatorul nou creat" << endl;
	meniu_utilizator_normal();
}

int main()
{
	int optiunea_aleasa = 0;
	do
	{
		optiunea_aleasa = meniu_login();
		switch (optiunea_aleasa)
		{
		case 1: {
			meniu_administrator();
			break;
		}
		case 2: {
			meniu_utilizator_normal();
			break;
		}
		case 3: {
			meniu_creare_utilizator();
			break;
		}
		default:
			break;
		}

	} while (optiunea_aleasa != 0);

	return 0;
};