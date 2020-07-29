#pragma once
#include "RoslinaTrujaca.h"

#define SYMBOL_WILCZEJ_JAGODY	'j'
#define SILA_WILCZEJ_JAGODY		99
#define KOLOR_WILCZEJ_JAGODY	80


class WilczeJagody : public RoslinaTrujaca {
public:
	WilczeJagody(Swiat& swiat, const Pozycja& polozenie);
	WilczeJagody(Swiat& swiat, const Pozycja& polozenie, const int& sila);

	~WilczeJagody();

	std::string GetNazwa() const override;

	Organizm* dzieckoOrganizmu(const Pozycja& polozenie) override;
};

