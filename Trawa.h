#pragma once
#include "Roslina.h"

#define SYMBOL_TRWAY	't'
#define KOLOR_TRAWY		171

class Trawa : public Roslina {
public:
	Trawa(Swiat& swiat, const Pozycja& polozenie);
	Trawa(Swiat& swiat, const Pozycja& polozenie, const int& sila);

	~Trawa();

	std::string GetNazwa() const override;

	Organizm* dzieckoOrganizmu(const Pozycja& polozenie) override;
};


