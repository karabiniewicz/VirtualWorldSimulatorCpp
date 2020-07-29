#include "Zwierze.h"

Zwierze::Zwierze(Swiat& swiat, const Pozycja& pozycja, const char& symbol, const int& sila,
	const int& inicjatywa, const int& kolor, const int& zasiegRuchu, const double& szansaRuchu)
	:Organizm(swiat, pozycja, symbol, sila, inicjatywa, kolor), zasiegRuchu(zasiegRuchu),
	szansaRuchu(szansaRuchu) {}

Zwierze::~Zwierze() {
}

void Zwierze::Akcja() {
	this->AktualizujWiek();

	if (this->CzyZyje() && this->CzyWykonalRuch())
		for (int i = 0; i < zasiegRuchu; ++i) {
			if (!WykonajRuch())
				break;
		}
}

bool Zwierze::Kolizja(Organizm* atakujacy) {
	if (this->sila > atakujacy->GetSila()) {
		if (!atakujacy->CzyOdbilAtak(this))
			atakujacy->Smierc(this);
		return false;
	}
	else {
		if (this->WykonajUnik(atakujacy))
			return true;
		else if (this->CzyOdbilAtak(atakujacy)) {
			return false;
			this->swiat.GetWydarzenia().PowiadomOOdbiciu(this, atakujacy);
		}
		else {
			this->Smierc(atakujacy);
			return true;
		}
	}
}

bool Zwierze::CzyWykonalRuch() {
	double los = (double)std::rand() / RAND_MAX;
	if (los <= szansaRuchu)
		return true;
	return false;
}

bool Zwierze::WykonajRuch() {
	Pozycja ostateczna = this->GetPozycjaOstateczna();

	if (ostateczna == this->GetPozycja())
		return false;

	Organizm* organizm = this->swiat.GetOrganizm(ostateczna);
	if (organizm == nullptr) {
		this->swiat.Przenies(this, ostateczna);
		return true;
	}
	else if (CzyTenSamGatunek(organizm)) {
		RozmnozSie(organizm);
		return false;
	}
	else if (organizm->Kolizja(this)) {
		swiat.Przenies(this, ostateczna);
		return false;
	}
}

Pozycja Zwierze::GetPozycjaOstateczna() {
	Pozycja pozycja = this->GetPozycja();
	Pozycja kierunek = Pozycja::GetLosowyKierunek();

	pozycja.Aktualizuj(kierunek);
	return pozycja;
}

bool Zwierze::RozmnozSie(Organizm* partner) {
	if ((this->GetWiek() < DOMYSLNY_WIEK_ROZMNAZANIA) || 
		(partner->GetWiek() < DOMYSLNY_WIEK_ROZMNAZANIA))
		return false;
	
	std::vector<Pozycja> dostepnePoz = GetPolaDlaDzieci(partner);

	while (dostepnePoz.size() > 0) {
		int losowa = std::rand() % dostepnePoz.size();

		if (this->swiat.GetOrganizm(dostepnePoz[losowa]) == nullptr) {
			Organizm* dziecko = this->dzieckoOrganizmu(dostepnePoz[losowa]);

			this->swiat.DodajOrganizm(dostepnePoz[losowa], dziecko);
			return true;
		}
		dostepnePoz.erase(dostepnePoz.begin() + losowa);
	}
	return false;
}

std::vector<Pozycja> Zwierze::GetPolaDlaDzieci(Organizm* partner) {
	std::vector<Pozycja> kierunki = Pozycja::GetKierunki();
	std::vector<Pozycja> wlasna, partnera;

	for (int i = 0; i < kierunki.size(); ++i) {
		wlasna.push_back(this->GetPozycja());
		partnera.push_back(partner->GetPozycja());

		wlasna[i].Aktualizuj(kierunki[i]);
		partnera[i].Aktualizuj(kierunki[i]);
	}
	wlasna.insert(wlasna.end(), partnera.begin(), partnera.end());
	return wlasna;
}

bool Zwierze::WykonajUnik(Organizm* atakujacy) {
	return false;
}
