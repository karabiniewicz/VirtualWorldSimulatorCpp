#include "Organizm.h"

Organizm::Organizm(Swiat& swiat, const Pozycja& pozycja, const char& symbol,
	const int& sila, const int& inicjatywa, const int& kolor)
	:swiat(swiat), pozycja(pozycja), symbol(symbol), sila(sila), inicjatywa(inicjatywa), kolor(kolor), wiek(0) {}

Organizm ::~Organizm() {
}

int Organizm::GetWiek() const {
	return wiek;
}

int Organizm::GetSila() const {
	return sila;
}

char Organizm::GetSymbol() const {
	return symbol;
}

int Organizm::GetInicjatywa() const {
	return inicjatywa;
}

Pozycja Organizm::GetPozycja() const {
	return pozycja;
}

std::string Organizm::GetNazwa() const {
	char buf[256];
	sprintf_s(buf, "%p", this);
	return std::string(buf);
}

void Organizm::SetPozycja(const Pozycja& pozycja) {
	this->pozycja = pozycja;
}

void Organizm::SetPozycja(const int& x, const int& y) {
	SetPozycja(Pozycja(x, y));
}

void Organizm::SetInicjatywa(const int& inicjatywa) {
	this->inicjatywa = inicjatywa;
}

void Organizm::AktualizujSile(const int& plus) {
	sila += plus;
}

void Organizm::AktualizujWiek() {
	wiek += 1;
}

void Organizm ::Rysuj() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), kolor);
	std::cout << symbol;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), KOLOR_PLANSZA);
}

bool Organizm::CzyZyje() {
	return czyZyje;
}

bool Organizm::CzyOdbilAtak(Organizm* atakujacy) {
	return false;
}

bool Organizm::Smierc(Organizm* atakujacy) {
	this->swiat.GetWydarzenia().PowiadomOSmierciOrganizmu(this, atakujacy);
	czyZyje = false;
	swiat.Usmiertelnij(this);
	return true;
}

std::string Organizm::NaString() const {
	return std::string(this->GetNazwa() + "(" +
		std::to_string(this->GetPozycja().GetX())+ "," +
		std::to_string(this->GetPozycja().GetY()) + ")");
}

std::string Organizm::ZapisStringa() const {
	std::string str="";
	str += std::to_string(this->GetSymbol()) + " ";
	str += std::to_string(this->GetPozycja().GetX()) + " ";
	str += std::to_string(this->GetPozycja().GetY()) + " ";
	str += std::to_string(this->GetSila()) + '\n';

	return str;
}
