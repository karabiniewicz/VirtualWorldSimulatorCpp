#include "Zolw.h"

Zolw::Zolw(Swiat& swiat, const Pozycja& polozenie)
	:Zwierze(swiat, polozenie, SYMBOL_ZOLWIA, SILA_ZOLWIA, INICJATYWA_ZOLWIA, KOLOR_ZOLWIA,
		DOMYSLNY_ZASIEG_RUCHU, SZANSA_RUCHU_PRZEZ_ZOLWIA) {}

Zolw::Zolw(Swiat& swiat, const Pozycja& polozenie, const int& sila)
	: Zwierze(swiat, polozenie, SYMBOL_ZOLWIA, sila, INICJATYWA_ZOLWIA, KOLOR_ZOLWIA,
		DOMYSLNY_ZASIEG_RUCHU, SZANSA_RUCHU_PRZEZ_ZOLWIA) {}

Zolw::~Zolw() {
}

std::string Zolw::GetNazwa() const {
	return "Zolw";
}

bool Zolw::CzyOdbilAtak(Organizm* atakujacy) {
	if (atakujacy->GetSila() < OBIJANE_ATAKI)
		return true;
	return false;
}

bool Zolw::CzyTenSamGatunek(Organizm* organizm) {
	return dynamic_cast<Zolw*>(organizm) != nullptr;
}

Organizm* Zolw::dzieckoOrganizmu(const Pozycja& polozenie) {
	return new Zolw(this->swiat, polozenie);
}
