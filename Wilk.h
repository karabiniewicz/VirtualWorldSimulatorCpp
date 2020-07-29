#pragma once
#include "Zwierze.h"

#define SILA_WILKA			9
#define INICJATYWA_WILKA	5
#define SYMBOL_WILKA		'W'
#define KOLOR_WILKA			135

class Wilk : public Zwierze {
public:
	Wilk(Swiat& swiat, const Pozycja& pozycja);
	Wilk(Swiat& swiat, const Pozycja& polozenie, const int& sila);

	~Wilk();
	
	std::string GetNazwa() const override;
	
	bool CzyTenSamGatunek(Organizm* organizm) override;
	
	Organizm* dzieckoOrganizmu(const Pozycja& polozenie) override;
};

