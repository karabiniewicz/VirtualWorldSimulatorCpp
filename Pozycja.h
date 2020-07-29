#pragma once
#include <cstdlib>
#include <vector>

class Pozycja {
public:
	Pozycja ();
	Pozycja (const int& x, const int& y);

	~Pozycja ();

	int GetX() const;
	int GetY() const;
	static Pozycja GetLosowaPozycja(const int& xMin, const int& yMin, const int& xMax, const int& yMax);
	static Pozycja GetLosowyKierunek();
	static std::vector<Pozycja> GetKierunki();
	static std::vector<Pozycja> GetMozliweKierunki(const Pozycja& pozycja);

	void Set(const int& x, const int& y);
	void SetX(const int& x);
	void SetY(const int& y);

	int& RefX();
	int& RefY();

	void Aktualizuj(const Pozycja& pozycja);
	void Aktualizuj(const int& x, const int& y);
	void AktualizujX(const int& x);
	void AktualizujY(const int& y);

	bool operator==(const Pozycja& porownaj);
	bool operator!=(const Pozycja& porownaj);

private:
	int x;
	int y;
};