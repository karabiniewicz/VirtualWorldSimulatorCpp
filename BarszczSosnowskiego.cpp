#include "BarszczSosnowskiego.h"
#include "Zwierze.h"

BarszczSosnowskiego::BarszczSosnowskiego(Swiat& swiat, const Pozycja& polozenie)
	:RoslinaTrujaca(swiat, polozenie, SYMBOL_BARSZCZU, SILA_BARSZCZU, KOLOR_BARSZCZU) {}

BarszczSosnowskiego::BarszczSosnowskiego(Swiat& swiat, const Pozycja& polozenie, const int& sila)
	: RoslinaTrujaca(swiat, polozenie, SYMBOL_BARSZCZU, sila, KOLOR_BARSZCZU) {}

BarszczSosnowskiego::~BarszczSosnowskiego() {
}

std::string BarszczSosnowskiego::GetNazwa() const {
	return "Barszcz Sosnowskiego";
}

void BarszczSosnowskiego::Akcja() {
	if (!this->CzyZyje())
		return;

	std::vector<Pozycja> wszystkieMo¿liwoœci = Pozycja::GetMozliweKierunki(this->GetPozycja());
	for (auto mozliwosc : wszystkieMo¿liwoœci) {
		Organizm* organizm = this->swiat.GetOrganizm(mozliwosc);
		if (organizm == nullptr)
			continue;
		else if (dynamic_cast<Zwierze*>(organizm) != nullptr)
			organizm->Kolizja(this);
	}

	this->ProbeRozmnozenia();
}

Organizm* BarszczSosnowskiego::dzieckoOrganizmu(const Pozycja& polozenie) {
	return new BarszczSosnowskiego(this->swiat, polozenie);
}

