#include "Wydarzenia.h"
#include "Organizm.h"
#include <chrono>
#include <thread>

Wydarzenia::Wydarzenia() 
:pozycjaWydarzen(Pozycja(0,0)) {}

Wydarzenia::~Wydarzenia() {
}

void Wydarzenia::SetPozycjaWydarzen(const Pozycja& pozycja) {
	this->pozycjaWydarzen = pozycja;
}

Pozycja Wydarzenia::GetPozycjaWydarzen() const {
	return pozycjaWydarzen;
}

void Wydarzenia::PozycjaWypisu(const Pozycja& pozycja) {
	COORD kursor = { pozycja.GetX(), pozycja.GetY() };	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), kursor);
}

void Wydarzenia::WypiszAutora() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), KOLOR_TLO);
	std::cout << "	Adam Karabiniewicz, 180009\n";
}

void Wydarzenia::WczytajDaneCzlowieka() {
	std::string komunikat = "Czlowiek:(strzalki lub c-\"calopalenie\"): ";
	this->WyswietlWydarzenie(komunikat);
}

void Wydarzenia::WyczyscWydarzenia(Pozycja odkad, Pozycja dokad) {
	while (odkad != dokad) {
		PozycjaWypisu(odkad);
		std::cout << "                                                                  ";
		odkad.AktualizujY(1);
	}
}

void Wydarzenia::WczytajKlawisz() {
	std::string komunikat = "Zapis stan( s ), Zakoncz( q ), Pomin( inny ):  ";
	this->WyswietlWydarzenie(komunikat);
}

void Wydarzenia::WyswietlWydarzenie(const std::string& komunikat, bool opoznienie) {
	PozycjaWypisu(GetPozycjaWydarzen());
	pozycjaWydarzen.AktualizujY(1);
	if(opoznienie)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), KOLOR_OPOZNIONE);

	std::cout << "~" << komunikat;

	if (opoznienie) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), KOLOR_TLO);
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}

void Wydarzenia::NowaTura(const int& tura) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), KOLOR_TURA);
	std::string komunikat = "Oto tura numer " + std::to_string(tura);
	this->WyswietlWydarzenie(komunikat);
}

void Wydarzenia::PowiadomOSmierciOrganizmu(Organizm* umierajacy, Organizm* atakujacy) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), KOLOR_SMIERC);
	std::string komunikat;
	if (atakujacy == nullptr)
		komunikat = umierajacy->NaString() + " umiera";
	else
		komunikat = umierajacy->NaString() + " zostal zabity przez " + atakujacy->NaString();

	this->WyswietlWydarzenie(komunikat);
}

void Wydarzenia::PowiadomOUniku(Organizm* uniknal, Organizm* tenCoAtakowal) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), KOLOR_UCIEKL);
	std::string komunikat = uniknal->NaString() + " wykonal unik przed " + tenCoAtakowal->NaString();
	this->WyswietlWydarzenie(komunikat);
}

void Wydarzenia::PowiadomOOdbiciu(Organizm* odbil, Organizm* odbity) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), KOLOR_UCIEKL);
	std::string komunikat = odbil->NaString() + " odbil atak" + odbity->NaString();
	this->WyswietlWydarzenie(komunikat);
}

void Wydarzenia::PowiadomOZdolnosci() {
	std::string komunikat = "Specjalna umiejetnosc Czlowieka aktywowowana!";
	this->WyswietlWydarzenie(komunikat, true);
}

void Wydarzenia::PowiadomOZapisie() {
	std::string komunikat = "Swiat zostal poprawnie zapisany!";
	this->WyswietlWydarzenie(komunikat, true);
}

void Wydarzenia::PowiadomOWczytamiu() {
	std::string komunikat = "Wczytano ostani zapis Swiata!";
	this->WyswietlWydarzenie(komunikat, true);
}
