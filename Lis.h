#pragma once
#include "Zwierze.h"

#define SILA_LISA		3
#define INICJATYWA_LISA	7
#define SYMBOL_LISA		'L'
#define KOLOR_LISA		110

class Lis : public Zwierze {
public:
	Lis(Swiat& swiat, const Pozycja& polozenie);
	Lis(Swiat& swiat, const Pozycja& polozenie,	const int& sila);

	~Lis();
	
	std::string GetNazwa() const override;
	Pozycja GetPozycjaOstateczna() override;
	
	bool CzyTenSamGatunek(Organizm* organizm) override;
	
	Organizm* dzieckoOrganizmu(const Pozycja& polozenie) override;
};


