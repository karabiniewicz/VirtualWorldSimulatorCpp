#pragma once
#include "Zwierze.h"

#define SILA_OWCY		4
#define INICJATYWA_OWCY 4
#define SYMBOL_OWCY		'O'
#define KOLOR_OWCY		248

class Owca : public Zwierze {
public:
	Owca(Swiat& swiat, const Pozycja& polozenie);
	Owca(Swiat& swiat, const Pozycja& polozenie, const int& sila);

	~Owca();
	
	std::string GetNazwa() const override;
	
	bool CzyTenSamGatunek(Organizm* organizm) override;	
	
	Organizm* dzieckoOrganizmu(const Pozycja& polozenie) override;
};
