#pragma once
#include "Roslina.h"

#define SYMBOL_MLECZA	'm'
#define KOLOR_MLECZA	120
#define PROBY_ROZSIEWU	3

class Mlecz : public Roslina {
public:
	Mlecz(Swiat& swiat, const Pozycja& polozenie);
	Mlecz(Swiat& swiat, const Pozycja& polozenie, const int& sila);
	
	virtual ~Mlecz();

	std::string GetNazwa() const override;

	virtual void Akcja() override;

	Organizm* dzieckoOrganizmu(const Pozycja& polozenie) override;
};
