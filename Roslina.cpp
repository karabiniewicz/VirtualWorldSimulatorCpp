#include "Roslina.h"


Roslina::Roslina(Swiat& swiat, const Pozycja& pozycja, const char& symbol, const int& sila, const int& kolor,
	const double& prawdopodobienstwo_rozmnozenia_sie)
	:Organizm(swiat, pozycja, symbol, sila, INICJATYWA_ROSLINY, kolor),
	szansRozsiewu(prawdopodobienstwo_rozmnozenia_sie) {}

Roslina::~Roslina() {
}

void Roslina::Akcja() {
	if (this->CzyZyje())
		this->ProbeRozmnozenia();
}

bool Roslina::Kolizja(Organizm* atakujacy) {
	this->Smierc(atakujacy);
	return true;
}

double Roslina::GetMozliwoscRozsiewu() {
	return szansRozsiewu;
}

bool Roslina::ProbeRozmnozenia() {
	double szansa = (double)std::rand() / RAND_MAX;

	if (szansa > this->GetMozliwoscRozsiewu())
		return false;

	Pozycja ostateczaPozycja = this->GetPozycja();
	ostateczaPozycja.Aktualizuj(Pozycja::GetLosowyKierunek());

	Organizm* org = this->swiat.GetOrganizm(ostateczaPozycja);
	if (org != nullptr)
		return false;

	Organizm* dziecko = dzieckoOrganizmu(ostateczaPozycja);
	this->swiat.DodajOrganizm(ostateczaPozycja, dziecko);
	return true;
}