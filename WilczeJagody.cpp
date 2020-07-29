#include "WilczeJagody.h"

WilczeJagody::WilczeJagody(Swiat& swiat, const Pozycja& polozenie)
	:RoslinaTrujaca(swiat, polozenie, SYMBOL_WILCZEJ_JAGODY, SILA_WILCZEJ_JAGODY, KOLOR_WILCZEJ_JAGODY) {}

WilczeJagody::WilczeJagody(Swiat& swiat, const Pozycja& polozenie, const int& sila)
	: RoslinaTrujaca(swiat, polozenie, SYMBOL_WILCZEJ_JAGODY, sila, KOLOR_WILCZEJ_JAGODY) {}

WilczeJagody::~WilczeJagody() {
}

std::string WilczeJagody::GetNazwa() const {
	return "Wilcze Jagody";
}

Organizm* WilczeJagody::dzieckoOrganizmu(const Pozycja& polozenie) {
	return new WilczeJagody(this->swiat, polozenie);
}
