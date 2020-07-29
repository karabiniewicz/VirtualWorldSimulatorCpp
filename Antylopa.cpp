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

	std::vector<Pozycja> wszystkieMo퓄iwo쐁i = Pozycja::GetMozliweKierunki(this->GetPozycja());
	while (wszystkieMo퓄iwo쐁i.size()) {
		int i = std::rand() % wszystkieMo퓄iwo쐁i.size();
		
		if (this->swiat.GetOrganizm(wszystkieMo퓄iwo쐁i[i]) != nullptr) {
			wszystkieMo퓄iwo쐁i.erase(wszystkieMo퓄iwo쐁i.begin() + i);
			continue;
		}

		this->swiat.Przenies(this, wszystkieMo퓄iwo쐁i[i]);
		this->swiat.GetWydarzenia().PowiadomOUniku(this, przeciwnik);
		return true;
	}

	return false;

}
