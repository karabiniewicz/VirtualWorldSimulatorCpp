#include "Pozycja.h"

Pozycja::Pozycja()
	:x(0), y(0) {}

Pozycja::Pozycja(const int& x, const int& y)
	: x(x), y(y) {}

Pozycja::~Pozycja() {
}

int Pozycja::GetX() const {
	return x;
}

int Pozycja::GetY() const {
	return y;
}

Pozycja Pozycja::GetLosowaPozycja(const int& xMin, const int& yMin, const int& xMax, const int& yMax) {
	int x = (std::rand() % xMax) + xMin;
	int y = (std::rand() % yMax) + yMin;
	return Pozycja(x, y);
}

Pozycja Pozycja::GetLosowyKierunek() {
	int kierunek = std::rand() % 4;
	switch (kierunek) {
	case 0:
		return Pozycja(0, -1);	//gora
	case 1:
		return Pozycja(1, 0);	//prawo
	case 2:
		return Pozycja(0, 1);	//dol
	case 3:
		return Pozycja(-1, 0);	//lewa
	}
}

std::vector<Pozycja> Pozycja::GetKierunki() {
	std::vector<Pozycja> vektor;
	vektor.push_back(Pozycja(0, -1));	// gora
	vektor.push_back(Pozycja(1, 0));	//prawo
	vektor.push_back(Pozycja(0, 1));	//dol
	vektor.push_back(Pozycja(-1, 0));	//lewo
	return vektor;
}

std::vector<Pozycja> Pozycja::GetMozliweKierunki(const Pozycja& pozycja) {
	std::vector<Pozycja> offsets;
	std::vector<Pozycja> unitVectors = GetKierunki();
	for (int i = 0; i < unitVectors.size(); ++i) {
		offsets.emplace_back(pozycja);
		offsets[i].Aktualizuj(unitVectors[i]);
	}
	return offsets;
}

int& Pozycja::RefX() {
	return x;
}

int& Pozycja::RefY() {
	return y;
}

void Pozycja::Set(const int& x, const int& y) {
	this->x = x;
	this->y = y;
}

void Pozycja::SetX(const int& x) {
	this->x = x;
}

void Pozycja::SetY(const int& y) {
	this->y = y;
}

void Pozycja::Aktualizuj(const Pozycja& point) {
	Aktualizuj(point.x, point.y);
}

void Pozycja::Aktualizuj(const int& x, const int& y) {
	AktualizujX(x);
	AktualizujY(y);
}

void Pozycja::AktualizujX(const int& x) {
	this->x += x;
}

void Pozycja::AktualizujY(const int& y) {
	this->y += y;
}


bool Pozycja::operator==(const Pozycja& porownaj) {
	return x == porownaj.x && y == porownaj.y;
}

bool Pozycja::operator!=(const Pozycja& porownaj) {
	return !(*this == porownaj);
}
