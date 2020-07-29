#pragma once
#include <Windows.h>
#include <algorithm> 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#include "Organizm.h"
#include "Pozycja.h"
#include "Wydarzenia.h"

#define ZALUDNIENIE			0.10
#define PRAWDOPODOBIENSTWO	0.10
#define POZ_SWIATA_X		3
#define POZ_SWIATA_Y		3
#define OBRAMOWANIE			2
#define STRZALKA			224

#define NOWA_GRA			'n'
#define WCZYTAJ				'r'
#define ZAKONCZ				'q'
#define ZAPISZ				's'

class Organizm;

class Swiat {
public:
	//Swiat (int wysokosc, int szerokosc);
	Swiat ();

	~Swiat ();
	
	Wydarzenia & GetWydarzenia();
	Organizm* GetOrganizm(const Pozycja& pozycjaOrg);
	std::vector<Organizm*> GetSasiednieOrganizmy(const Pozycja& polozenie);

	enum WyborOrganizmu {
		wilk,
		owca,
		lis,
		zolw,
		antylopa,
		trawa,
		mlecz,
		guarana,
		wilczeJagody,
		barszczSosnowskiego,
		brak
	};

	void MenuGlowne();

	void DodajOrganizm(const Pozycja& polozenieOrg, Organizm* organizm = nullptr);

	bool ZakonczSwiat();

	void RysujSwiat();

	bool WczytajKlawisz();

	void WykonajTure();

	bool Przenies(Organizm* oczekujacy, const Pozycja& docelowa);

	bool Usmiertelnij(Organizm* orgaznizmDoZabicia);


private:				
	int wysokosc;
	int szerokosc;
	int tura;
	bool zakoncz = false;

	Wydarzenia wydarzenia;

	struct PrzeniesDo {
		Pozycja poczatkowa, ostateczna;
		PrzeniesDo(const Pozycja& poczatkowa, const Pozycja& ostateczna)
			:poczatkowa(poczatkowa), ostateczna(ostateczna) {};
	};

	struct PorownanieInicjatywy {
		bool operator()(const Organizm* lewy, const Organizm* prawy) const;
	};

	std::vector< std::vector< Organizm* > > organizmy;
	std::vector< Organizm* > posortowaneOrganizmy;
	std::queue< Organizm* > noweOrganizmy;
	std::vector<PrzeniesDo> doPrzeniesienia;
	std::queue<Pozycja> doZabicia;

	bool WczytajSwiat();

	bool ZapiszSwiat();

	void NowaGra(const int& wysokosc, const int& szerokosc, bool losowePostacie = true);	


	void StworzSwiat(const int& wysokosc, const int& szerokosc, bool losowePostacie);

	void ZaludnijSwiat();

	void PoczatkowyStan();

	Pozycja KontrolaPozycji(const Pozycja& pozycja);

	void zaiinicjujNoweOrganizmy();

	void SortujOrganizmy();

	Organizm* GenerujLosowyOrganizm(const Pozycja& polozenie);

	void WalidujOrganizmy();

	void PrzeniesNow(const PrzeniesDo& przeniesDo);

	void UsmiertelnijNow(const Pozycja& Usmiertelnij);	

};
