#pragma once
#include "Organizm.h"

#define INICJATYWA_ROSLINY		0
#define SILA_ROSLINY			0
#define SZANSA_ROZSIEWU_ROSLIN  0.1

class Roslina : public Organizm {
public:
	Roslina(Swiat& swiat, const Pozycja& polozenie, const char& symbol,
		const int& sila, const int& kolor, const double& rozsiew = SZANSA_ROZSIEWU_ROSLIN);

	virtual ~Roslina();

	virtual void Akcja() override;
	virtual bool Kolizja(Organizm* atakujacy) override;
private:
	double szansRozsiewu;
protected:
	double GetMozliwoscRozsiewu();
	bool ProbeRozmnozenia();
};

