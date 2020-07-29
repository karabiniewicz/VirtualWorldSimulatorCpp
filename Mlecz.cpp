#include "Mlecz.h"
#include "Guarana.h"

Mlecz::Mlecz(Swiat& swiat, const Pozycja& polozenie)
	:Roslina(swiat, polozenie, SYMBOL_MLECZA, SILA_ROSLINY, KOLOR_MLECZA) {}

Mlecz::Mlecz(Swiat& swiat, const Pozycja& polozenie, const int& sila)
	: Roslina(swiat, polozenie, SYMBOL_MLECZA, sila, KOLOR_MLECZA) {}

Mlecz::~Mlecz() {
}

std::string Mlecz::GetNazwa() const {
	return "Mlecz";
}

void Mlecz::Akcja() {
	for (int i = 0; i < PROBY_ROZSIEWU; ++i)
		ProbeRozmnozenia();
}

Organizm* Mlecz::dzieckoOrganizmu(const Pozycja& polozenie) {
	return new Mlecz(this->swiat, polozenie);
}
