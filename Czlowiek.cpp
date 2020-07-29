#include "Czlowiek.h"

Czlowiek::Czlowiek(Swiat& swiat, const Pozycja& polozenie)
	:Zwierze(swiat, polozenie, SYMBOL_CZLOWIEKA, SILA_CZLOWIEKA, INICJATYWA_CZLOWIEKA, KOLOR_CZLOWIEKA),
	czasZdolnosci(0), blokadaZdolnosci(0) {}

Czlowiek::Czlowiek(Swiat& swiat, const Pozycja& polozenie, const int& sila,
	const int& zdolnosc, const int& cooldown)
	: Zwierze(swiat, polozenie, SYMBOL_CZLOWIEKA, sila, INICJATYWA_CZLOWIEKA, KOLOR_CZLOWIEKA),
	czasZdolnosci(zdolnosc), blokadaZdolnosci(cooldown) {}

Czlowiek::~Czlowiek() {
}

std::string Czlowiek::GetNazwa() const {
	return "Czlowiek";
}

bool Czlowiek::AktywacjaZdolnosci() {
	if (blokadaZdolnosci > 0 || czasZdolnosci > 0)
		return false;
	czasZdolnosci = ILOSC_TUR_UMIEJETNOSCI;
	blokadaZdolnosci = ILOSC_TUR_BLOKADY;
	ZdolnoscSpecjalna();

	this->swiat.GetWydarzenia().PowiadomOZdolnosci();
	return true;
}

void Czlowiek::ZdolnoscSpecjalna() {
	if (czasZdolnosci == 0)
		return;

	bool odswiez = false;
	std::vector<Organizm*> sasiedzi = this->swiat.GetSasiednieOrganizmy(this->GetPozycja());
	for (auto sasiad : sasiedzi) {
		if (sasiad == nullptr)
			continue;
		sasiad->Smierc(this);
		odswiez = true;
	}

	if (odswiez)
		this->swiat.RysujSwiat();
}

void Czlowiek::TuraZdolnosci() {
	if (czasZdolnosci > 0)
		--czasZdolnosci;
	else if (blokadaZdolnosci > 0)
		--blokadaZdolnosci;
}

Organizm* Czlowiek::dzieckoOrganizmu(const Pozycja& polozenie) {
	return new Czlowiek(this->swiat, polozenie);
}

bool Czlowiek::CzyTenSamGatunek(Organizm* organizm) {
	return dynamic_cast<Czlowiek*>(organizm) != nullptr;
}

Pozycja Czlowiek::GetPozycjaOstateczna() {
	Pozycja pozycja = this->GetPozycja();
	if (!this->CzyZyje())
		return pozycja;

	this->swiat.RysujSwiat();
	this->swiat.GetWydarzenia().WczytajDaneCzlowieka();
	int c = _getch();
	if (c == STRZALKA) {
		switch (c = _getch()) {
		case STRZALKA_GORA:
			pozycja.Aktualizuj(Pozycja(0, -1));	// gora
			return pozycja;
		case STRZALKA_PRAWO:
			pozycja.Aktualizuj(Pozycja(1, 0));		//praw			
			return pozycja;
		case STRZALKA_DOL:
			pozycja.Aktualizuj(Pozycja(0, 1));		//dol
			return pozycja;
		case STRZALKA_LEWO:
			pozycja.Aktualizuj(Pozycja(-1, 0));	//lewo
			return pozycja;
		default:
			return pozycja;
		}
	}
	c = tolower(c);
	if(c== CALOPALENIE)
		this->AktywacjaZdolnosci();

	return pozycja;
}

void Czlowiek::Akcja() {
	ZdolnoscSpecjalna();
	if (CzyWykonalRuch())
		for (int i = 0; i < zasiegRuchu; ++i) {
			if (!WykonajRuch())
				break;
		}
	ZdolnoscSpecjalna();
	TuraZdolnosci();
}

std::string Czlowiek::ZapisStringa() const {		//zrobic
	std::string str="";
	str += std::to_string(this->GetSymbol()) + " ";
	str += std::to_string(this->GetPozycja().GetX()) + " ";
	str += std::to_string(this->GetPozycja().GetY()) + " ";
	str += std::to_string(this->GetSila()) + " ";
	str += std::to_string(this->czasZdolnosci) + " ";
	str += std::to_string(this->blokadaZdolnosci) + '\n';

	return str;
}

