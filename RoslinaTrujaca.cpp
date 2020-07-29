#include "RoslinaTrujaca.h"

RoslinaTrujaca::RoslinaTrujaca(Swiat& swiat, const Pozycja& pozycja,
	const char& symbol, const int& sila, const int& kolor, const double& rozsiew)
	:Roslina(swiat, pozycja, symbol, sila, kolor, rozsiew) {}

RoslinaTrujaca::~RoslinaTrujaca() {
}

bool RoslinaTrujaca::Kolizja(Organizm* atakujacy) {
	if (!this->CzyZyje())
		return true;

	if (this->sila > atakujacy->GetSila()) {
		atakujacy->Smierc(this);
		return false;
	}
	else {
		this->Smierc(atakujacy);
		return true;
	}
}
