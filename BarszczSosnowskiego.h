#pragma once
#include "RoslinaTrujaca.h"

#define SYMBOL_BARSZCZU 'b'
#define KOLOR_BARSZCZU	178
#define SILA_BARSZCZU	10

class BarszczSosnowskiego : public RoslinaTrujaca {
public:
	BarszczSosnowskiego(Swiat& swiat, const Pozycja& polozenie);
	BarszczSosnowskiego(Swiat& swiat, const Pozycja& polozenie, const int& sila);

	~BarszczSosnowskiego();

	std::string GetNazwa() const override;

	void Akcja() override;

	Organizm* dzieckoOrganizmu(const Pozycja& polozenie) override;
};

