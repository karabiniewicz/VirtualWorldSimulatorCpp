#include "Trawa.h"

Trawa::Trawa(Swiat& swiat, const Pozycja& polozenie)
	:Roslina(swiat, polozenie, SYMBOL_TRWAY, SILA_ROSLINY, KOLOR_TRAWY) {}

Trawa::Trawa(Swiat& swiat, const Pozycja& polozenie, const int& sila)
	: Roslina(swiat, polozenie, SYMBOL_TRWAY, sila, KOLOR_TRAWY) {}

Trawa::~Trawa() {
}

std::string Trawa::GetNazwa() const {
	return "Trawa";
}

Organizm* Trawa::dzieckoOrganizmu(const Pozycja& polozenie) {
	return new Trawa(this->swiat, polozenie);
}

