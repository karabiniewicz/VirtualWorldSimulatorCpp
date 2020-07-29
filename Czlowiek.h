#pragma once
#include "Zwierze.h"
#include <conio.h>

#define SILA_CZLOWIEKA			5
#define INICJATYWA_CZLOWIEKA	4
#define ILOSC_TUR_UMIEJETNOSCI	5
#define ILOSC_TUR_BLOKADY		5
#define SYMBOL_CZLOWIEKA		'C'
#define KOLOR_CZLOWIEKA			63
#define CALOPALENIE				'c'

#define STRZALKA_GORA			72
#define STRZALKA_DOL			80
#define STRZALKA_PRAWO			77
#define STRZALKA_LEWO			75

class Czlowiek : public Zwierze {
public:
	Czlowiek(Swiat& swiat, const Pozycja& polozenie);
	Czlowiek(Swiat& swiat, const Pozycja& polozenie, const int& sila, const int& zdolnosc, const int& cooldown);

	~Czlowiek();

	std::string GetNazwa() const override;
	Pozycja GetPozycjaOstateczna() override;

	void Akcja() override;
	
	bool CzyTenSamGatunek(Organizm* organizm) override;

	Organizm* dzieckoOrganizmu(const Pozycja& polozenie) override;

	std::string ZapisStringa() const override;

private:
	int czasZdolnosci, blokadaZdolnosci;

	bool AktywacjaZdolnosci();

	void ZdolnoscSpecjalna();

	void TuraZdolnosci();
};


