#include "Guarana.h"

Guarana::Guarana(Swiat& swiat, const Pozycja& polozenie)
	:Roslina(swiat, polozenie, SYMBOL_GUARANA, SILA_ROSLINY, KOLOR_GUARANA) {}

Guarana::Guarana(Swiat& swiat, const Pozycja& polozenie, const int& sila)
	: Roslina(swiat, polozenie, SYMBOL_GUARANA, sila, KOLOR_GUARANA) {}

Guarana::~Guarana() {
}

std::string Guarana::GetNazwa() const {
	return "Guarana";
}

bool Guarana::Kolizja(Organizm* przeciwnik) {
	przeciwnik->AktualizujSile(GUARANA_BONUS);

	this->Smierc(this);
	return true;
}

Organizm* Guarana::dzieckoOrganizmu(const Pozycja& polozenie) {
	return new Guarana(swiat, polozenie);
}

