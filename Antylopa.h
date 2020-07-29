#pragma once
#include "Zwierze.h"

#define ZASIEG_ANTYLOPY			2
#define SZANSA_UNIKU			0.5
#define SILA_ANTYLOPY			4
#define INICJATYWA_ANTYLOPY		4
#define SYMBOL_ANTYLOPY			'A'
#define KOLOR_ANTYLOPY			206

class Antylopa : public Zwierze {
public:
	Antylopa(Swiat& swiat, const Pozycja& polozenie);
	Antylopa(Swiat& swiat, const Pozycja& polozenie, const int& sila);

	~Antylopa();

	std::string GetNazwa() const override;
	
	bool CzyTenSamGatunek(Organizm* organizm) override;

	bool WykonajUnik(Organizm* atakujacy) override;

	Organizm* dzieckoOrganizmu(const Pozycja& polozenie) override;
};


