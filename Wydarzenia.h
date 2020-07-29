#pragma once
#include "Pozycja.h"
#include <Windows.h>
#include <iostream>
#include <string>

#define KOLOR_TLO			96
#define KOLOR_PLANSZA		224
#define KOLOR_KRAWEDZ		15
#define KOLOR_OPOZNIONE		242
#define KOLOR_UCIEKL		107
#define KOLOR_SMIERC		100
#define KOLOR_TURA			104

class Organizm;

class Wydarzenia {
public:
	Wydarzenia();

	~Wydarzenia();

	Pozycja GetPozycjaWydarzen() const;

	void SetPozycjaWydarzen(const Pozycja& pozycja);

	static void PozycjaWypisu(const Pozycja& pozycjaPoczatkowa);

	void WypiszAutora();

	void NowaTura(const int& tura);

	void WczytajKlawisz();	
	void WczytajDaneCzlowieka();

	void WyczyscWydarzenia(Pozycja odkad, Pozycja dokad);

	void PowiadomOOdbiciu(Organizm* odbil, Organizm* odbity);
	void PowiadomOSmierciOrganizmu(Organizm* umierajacy, Organizm* atakujacy);
	void PowiadomOUniku(Organizm* uniknal, Organizm* tenCoAtakowal);
	void PowiadomOZdolnosci();	
	void PowiadomOZapisie();
	void PowiadomOWczytamiu();

private:
	Pozycja pozycjaWydarzen;

	void WyswietlWydarzenie(const std::string& komunikat, bool opoznienie = false);
};

