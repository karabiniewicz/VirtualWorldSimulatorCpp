#pragma once
#include "Zwierze.h"

#define SILA_ZOLWIA					2
#define INICJATYWA_ZOLWIA			1
#define SYMBOL_ZOLWIA				'Z'
#define SZANSA_RUCHU_PRZEZ_ZOLWIA	0.25
#define OBIJANE_ATAKI				5
#define KOLOR_ZOLWIA				32
class Zolw : public Zwierze {
public:
	Zolw(Swiat& swiat, const Pozycja& polozenie);
	Zolw(Swiat& swiat, const Pozycja& polozenie, const int& sila);
	
	~Zolw();
	
	std::string GetNazwa() const override;
	
	bool CzyOdbilAtak(Organizm* atakujacy) override;
	
	bool CzyTenSamGatunek(Organizm* organizm) override;
	
	Organizm* dzieckoOrganizmu(const Pozycja& polozenie) override;

};

