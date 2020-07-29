#include "Wilk.h"

Wilk::Wilk(Swiat& swiat, const Pozycja& pozycja)
	:Zwierze(swiat, pozycja, SYMBOL_WILKA, SILA_WILKA, INICJATYWA_WILKA, KOLOR_WILKA) {}

Wilk::Wilk(Swiat& swiat, const Pozycja& pozycja, const int& sila)
	: Zwierze(swiat, pozycja, SYMBOL_WILKA, sila, INICJATYWA_WILKA, KOLOR_WILKA) {}

Wilk::~Wilk() {
}

std::string Wilk::GetNazwa() const {
	return "Wilk";
}

bool Wilk::CzyTenSamGatunek(Organizm* organizm) {
	return dynamic_cast<Wilk*>(organizm) != nullptr;
}

Organizm* Wilk::dzieckoOrganizmu(const Pozycja& polozenie) {
	return new Wilk(this->swiat, polozenie);
}
