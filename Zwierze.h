#pragma once
#include "Organizm.h"

#define DOMYSLNY_ZASIEG_RUCHU		1
#define DOMYSLNA_SZANSA_RUCHU		1
#define DOMYSLNY_WIEK_ROZMNAZANIA	4

class Zwierze : public Organizm {
public:
	Zwierze(Swiat& swiat, const Pozycja& pozycja, const char& symbol, const int& sila,
		const int& inicjatywa, const int& kolor, const int& zasiegRuchu = DOMYSLNY_ZASIEG_RUCHU,
		const double& szansaRuchu = DOMYSLNA_SZANSA_RUCHU);

	virtual ~Zwierze();

	virtual void Akcja() override;

	virtual bool Kolizja(Organizm* atakujacy) override;

protected:
	int zasiegRuchu;
	double szansaRuchu;

	bool CzyWykonalRuch();
	
	virtual bool WykonajRuch();
	
	virtual Pozycja GetPozycjaOstateczna();
	
	virtual bool CzyTenSamGatunek(Organizm* organizm) = 0;
	
	virtual bool RozmnozSie(Organizm* partner);
	
	std::vector<Pozycja> GetPolaDlaDzieci(Organizm* partner);

	virtual bool WykonajUnik(Organizm* atakujacy);
};

