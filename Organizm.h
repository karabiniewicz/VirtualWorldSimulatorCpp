#pragma once
#include "Swiat.h"
#include "Pozycja.h"

class Swiat;

class Organizm {
public:
	Organizm(Swiat& swiat, const Pozycja& pozycja, const char& symbol, const int& sila, const int& inicjatywa, const int& kolor);
	~Organizm ();

	virtual void Akcja() = 0;
	virtual bool Kolizja(Organizm* atakujacy) = 0;

	int GetSila() const;
	int GetWiek() const;
	char GetSymbol() const;
	int GetInicjatywa() const;
	Pozycja GetPozycja() const;
	virtual std::string GetNazwa() const;

	void SetPozycja(const Pozycja& pozycja);
	void SetPozycja(const int& x, const int& y);
	void SetInicjatywa(const int& inicjatywa);

	void AktualizujWiek();
	void AktualizujSile(const int& plus);

	void Rysuj();

	bool CzyZyje();

	virtual bool CzyOdbilAtak(Organizm* atakujacy);

	virtual bool Smierc(Organizm* atakujacy);

	virtual Organizm* dzieckoOrganizmu(const Pozycja& polozenie) = 0;

	virtual std::string NaString() const;

	virtual std::string ZapisStringa() const;

private:
	int wiek;
	int kolor;
	char symbol;
	bool czyZyje;
	int inicjatywa;
	Pozycja pozycja;
protected:
	int sila;
	Swiat& swiat;
};
