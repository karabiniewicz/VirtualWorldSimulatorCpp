#include "Owca.h"


Owca::Owca(Swiat& swiat, const Pozycja& polozenie)
	:Zwierze(swiat, polozenie, SYMBOL_OWCY, SILA_OWCY, INICJATYWA_OWCY, KOLOR_OWCY) {}

Owca::Owca(Swiat& swiat, const Pozycja& polozenie, const int& sila)
	: Zwierze(swiat, polozenie, SYMBOL_OWCY, sila, INICJATYWA_OWCY, KOLOR_OWCY) {}

Owca::~Owca() {
}

std::string Owca::GetNazwa() const {
	return "Owca";
}

bool Owca::CzyTenSamGatunek(Organizm* organizm) {
	return dynamic_cast<Owca*>(organizm) != nullptr;
}

Organizm* Owca::dzieckoOrganizmu(const Pozycja& polozenie) {
	return new Owca(this->swiat, polozenie);	
}

