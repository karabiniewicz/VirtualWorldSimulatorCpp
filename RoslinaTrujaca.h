#pragma once
#include "Roslina.h"
#define SZANSA_ROZSIEWU_ROSLIN 0.1

class RoslinaTrujaca : public Roslina {
public:
	RoslinaTrujaca(Swiat& swiat, const Pozycja& polozenie, const char& symbol,
		const int& sila, const int& kolor, const double& rozsiew = SZANSA_ROZSIEWU_ROSLIN);

	virtual ~RoslinaTrujaca();

	virtual bool Kolizja(Organizm* atakujacy) override;
};

