#pragma once
#include "Roslina.h"

#define SYMBOL_GUARANA	'g'
#define KOLOR_GUARANA	64
#define GUARANA_BONUS	3

class Guarana : public Roslina {
public:
	Guarana(Swiat& swiat, const Pozycja& polozenie);
	Guarana(Swiat& swiat, const Pozycja& polozenie, const int& sila);

	~Guarana();

	std::string GetNazwa() const override;

	bool Kolizja(Organizm* przeciwnik) override;

	Organizm* dzieckoOrganizmu(const Pozycja& polozenie) override;
};

