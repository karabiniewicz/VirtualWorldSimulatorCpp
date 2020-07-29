#include "Lis.h"


Lis::Lis(Swiat& swiat, const Pozycja& polozenie)
	:Zwierze(swiat, polozenie, SYMBOL_LISA, SILA_LISA, INICJATYWA_LISA, KOLOR_LISA) {}

Lis::Lis(Swiat& swiat, const Pozycja& polozenie, const int& sila)
	: Zwierze(swiat, polozenie, SYMBOL_LISA, sila, INICJATYWA_LISA, KOLOR_LISA) {}

Lis::~Lis() {
}

std::string Lis::GetNazwa() const {
	return "Lis";
}

Organizm* Lis::dzieckoOrganizmu(const Pozycja& polozenie) {
	return new Lis(this->swiat, polozenie);
}

bool Lis::CzyTenSamGatunek(Organizm* organizm) {
	return dynamic_cast<Lis*>(organizm) != nullptr;
}

Pozycja Lis::GetPozycjaOstateczna() {
	std::vector<Pozycja> mozliwePozycje = Pozycja::GetMozliweKierunki(this->GetPozycja());
	while (mozliwePozycje.size() > 0) {
		int i = std::rand() % mozliwePozycje.size();
		std::vector<Organizm*> sasiadujaceOrganizmy = this->swiat.GetSasiednieOrganizmy(mozliwePozycje[i]);
		bool bezpieczniePole = true;
		for (auto organizm : sasiadujaceOrganizmy) {
			if ((organizm != nullptr) && (organizm->GetSila() > this->GetSila())) {
				bezpieczniePole = false;
				break;
			}
		}
		if (bezpieczniePole)
			return mozliwePozycje[i];
		else
			mozliwePozycje.erase(mozliwePozycje.begin() + i);
	}
	return this->GetPozycja();
}
