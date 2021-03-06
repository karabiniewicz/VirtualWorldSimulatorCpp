#include "Antylopa.h"
#include "Zwierze.h"


Antylopa::Antylopa(Swiat& swiat, const Pozycja& polozenie)
	:Zwierze(swiat, polozenie, SYMBOL_ANTYLOPY, SILA_ANTYLOPY, INICJATYWA_ANTYLOPY, KOLOR_ANTYLOPY, ZASIEG_ANTYLOPY) {}

Antylopa::Antylopa(Swiat& swiat, const Pozycja& polozenie, const int& sila)
	: Zwierze(swiat, polozenie, SYMBOL_ANTYLOPY, sila, INICJATYWA_ANTYLOPY, KOLOR_ANTYLOPY) {}

Antylopa::~Antylopa() {
}

std::string Antylopa::GetNazwa() const {
	return "Antylopa";
}

Organizm* Antylopa::dzieckoOrganizmu(const Pozycja& polozenie) {
	return new Antylopa(this->swiat, polozenie);
}

bool Antylopa::CzyTenSamGatunek(Organizm* organizm) {
	return dynamic_cast<Antylopa*>(organizm);
}

bool Antylopa::WykonajUnik(Organizm* przeciwnik) {
	if (dynamic_cast<Zwierze*>(przeciwnik) == nullptr)
		return false;

	double szansa = (double)std::rand() / RAND_MAX;

	if (szansa > SZANSA_UNIKU)
		return false;

	std::vector<Pozycja> wszystkieMożliwości = Pozycja::GetMozliweKierunki(this->GetPozycja());
	while (wszystkieMożliwości.size()) {
		int i = std::rand() % wszystkieMożliwości.size();
		
		if (this->swiat.GetOrganizm(wszystkieMożliwości[i]) != nullptr) {
			wszystkieMożliwości.erase(wszystkieMożliwości.begin() + i);
			continue;
		}

		this->swiat.Przenies(this, wszystkieMożliwości[i]);
		this->swiat.GetWydarzenia().PowiadomOUniku(this, przeciwnik);
		return true;
	}

	return false;

}
