#include "Swiat.h"

#include "Czlowiek.h"
#include "Mlecz.h"
#include "Trawa.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "BarszczSosnowskiego.h"
#include "Antylopa.h"

#define KOLOR_TLO			96
#define KOLOR_PLANSZA		224
#define KOLOR_KRAWEDZ		15

Swiat::Swiat() {
}

Swiat::~Swiat() {
	for (int y = 0; y < wysokosc; ++y) {
		for (int x = 0; x < szerokosc; ++x)
			if (organizmy[y][x] != nullptr)
				delete organizmy[y][x];
	}
}

Wydarzenia& Swiat::GetWydarzenia() {
	return this->wydarzenia;
}

void Swiat::MenuGlowne() {
	char c = '0';
	while (c != NOWA_GRA && c != WCZYTAJ) {
		GetWydarzenia().WypiszAutora();

		std::cout << "\n	   Wizualizacja Swiata!\n\n";
		std::cout << "Nowy Swiat( n/N ) lub Wczytaj Swiat( r/R ) >>";
		c = _getch();
		c = tolower(c);

		system("cls");
	}

	if (c == NOWA_GRA) {
		int w, s;

		std::cout << "Podaj wymiary planszy\n";
		std::cout << "\n	Wysokosc >>";
		std::cin >> w;
		std::cout << "\n	Szerokosc >>";
		std::cin >> s;

		NowaGra(w, s);
	}
	else if (c == WCZYTAJ)
		WczytajSwiat();
}

bool Swiat::WczytajSwiat() {
	std::ifstream input("StanGry.txt");
	int iloscOrganizmow, szer, wys;

	if (!input)
		return false;

	input >> szer;
	input >> wys;
	input >> iloscOrganizmow;

	this->NowaGra(wys, szer, false);

	for (int i = 0; i < iloscOrganizmow; ++i) {
		Organizm* organizm = nullptr;
		int wejscia[5];
		int symbol;

		input >> symbol;

		for (int i = 0; i < 3; ++i)
			input >> wejscia[i];
		
		if (symbol == SYMBOL_CZLOWIEKA) {
			input >> wejscia[3];
			input >> wejscia[4];
		}

		switch (symbol) {
		case SYMBOL_CZLOWIEKA:
			organizm = new Czlowiek(*this, Pozycja(wejscia[0], wejscia[1]), wejscia[2], wejscia[3], wejscia[4]);
			break;
		case SYMBOL_ANTYLOPY:
			organizm = new Antylopa(*this, Pozycja(wejscia[0], wejscia[1]), wejscia[2]);
			break;
		case SYMBOL_LISA:
			organizm = new Lis(*this, Pozycja(wejscia[0], wejscia[1]), wejscia[2]);
			break;
		case SYMBOL_OWCY:
			organizm = new Owca(*this, Pozycja(wejscia[0], wejscia[1]), wejscia[2]);
			break;
		case SYMBOL_WILKA:
			organizm = new Wilk(*this, Pozycja(wejscia[0], wejscia[1]), wejscia[2]);
			break;
		case SYMBOL_ZOLWIA:
			organizm = new Zolw(*this, Pozycja(wejscia[0], wejscia[1]), wejscia[2]);
			break;
		case SYMBOL_BARSZCZU:
			organizm = new BarszczSosnowskiego(*this, Pozycja(wejscia[0], wejscia[1]), wejscia[2]);
			break;
		case SYMBOL_GUARANA:
			organizm = new Guarana(*this, Pozycja(wejscia[0], wejscia[1]), wejscia[2]);
			break;
		case SYMBOL_MLECZA:
			organizm = new Mlecz(*this, Pozycja(wejscia[0], wejscia[1]), wejscia[2]);
			break;
		case SYMBOL_TRWAY:
			organizm = new Trawa(*this, Pozycja(wejscia[0], wejscia[1]), wejscia[2]);
			break;
		case SYMBOL_WILCZEJ_JAGODY:
			organizm = new WilczeJagody(*this, Pozycja(wejscia[0], wejscia[1]), wejscia[2]);
			break;
		default:
			organizm = nullptr;
		}

		if (organizm != nullptr)
			this->DodajOrganizm(organizm->GetPozycja(), organizm);
	}
	this->zaiinicjujNoweOrganizmy();

	GetWydarzenia().PowiadomOWczytamiu();
	return true;
}

bool Swiat::ZapiszSwiat() {
	const std::string file_name{ "StanGry.txt" };

	std::ofstream output{ file_name,std::ofstream::trunc };

	if (!output) {
		return false;
	}

	output << szerokosc << ' ';
	output << wysokosc << '\n';
	output << posortowaneOrganizmy.size() << '\n';

	for (auto organism : posortowaneOrganizmy)
		output << organism->ZapisStringa();

		GetWydarzenia().PowiadomOZapisie();
		return true;
}

void Swiat::NowaGra(const int& wysokosc, const int& szerokosc, bool losowePostacie) {
	this->PoczatkowyStan();
	this->StworzSwiat(wysokosc, szerokosc, losowePostacie);
}

void Swiat::PoczatkowyStan() {
	system("cls");
	GetWydarzenia().WypiszAutora();

	this->organizmy.clear();
	this->posortowaneOrganizmy.clear();
	this->doPrzeniesienia.clear();
}

void Swiat::StworzSwiat(const int& wysokosc, const int& szerokosc, bool losowePostacie) {
	this->wysokosc = wysokosc;
	this->szerokosc = szerokosc;
	this->tura = 1;
	this->wydarzenia.SetPozycjaWydarzen(Pozycja((POZ_SWIATA_X + OBRAMOWANIE * 2 + this->szerokosc), (POZ_SWIATA_Y)));
	for (int y = 0; y < wysokosc; ++y) {
		organizmy.push_back(std::vector<Organizm*>());
		for (int x = 0; x < szerokosc; ++x)
			organizmy[y].push_back(nullptr);
	}
	if(losowePostacie)
		ZaludnijSwiat();
}

void Swiat::ZaludnijSwiat() {
	int zaludnienie = floor(ZALUDNIENIE * wysokosc * szerokosc);
	int ilosOrganizmow = 1;

	DodajOrganizm(Pozycja::GetLosowaPozycja(0, 0, this->szerokosc, this->wysokosc), new Czlowiek(*this, Pozycja()));

	while (ilosOrganizmow < zaludnienie) {
		int x = std::rand() % szerokosc;
		int y = std::rand() % wysokosc;

		if (organizmy[y][x] == nullptr) {
			DodajOrganizm(Pozycja(x, y), nullptr);
			++ilosOrganizmow;
		}
	}
	zaiinicjujNoweOrganizmy();
	SortujOrganizmy();
}

void Swiat::DodajOrganizm(const Pozycja& polozenieOrg, Organizm* organizm) {
	Pozycja polozenie = KontrolaPozycji(polozenieOrg);

	if (organizmy[polozenie.GetY()][polozenie.GetX()] != nullptr)
		return;

	Organizm* nowyOrganizm = organizm;
	if (nowyOrganizm == nullptr)
		nowyOrganizm = GenerujLosowyOrganizm(polozenie);
	else
		nowyOrganizm->SetPozycja(polozenie);

	organizmy[polozenie.GetY()][polozenie.GetX()] = nowyOrganizm;
	noweOrganizmy.push(nowyOrganizm);
}

Pozycja Swiat::KontrolaPozycji(const Pozycja& pozycja) {
	Pozycja pozDocelowa = pozycja;
	if (pozycja.GetX() < 0)
		pozDocelowa.AktualizujX(szerokosc);
	if (pozycja.GetX() >= szerokosc)
		pozDocelowa.AktualizujX(-szerokosc);
	if (pozycja.GetY() < 0)
		pozDocelowa.AktualizujY(wysokosc - 1);
	if (pozycja.GetY() >= wysokosc)
		pozDocelowa.AktualizujY(-wysokosc);
	return pozDocelowa;
}


Organizm* Swiat::GenerujLosowyOrganizm(const Pozycja& polozenie) {
	Organizm* nowyOrganizm = nullptr;
	double liczba = (double)std::rand() / RAND_MAX;

	WyborOrganizmu wybor = brak;
	double przedzial = 0;
	for (int i = 0; i < wybor; ++i) {
		przedzial += PRAWDOPODOBIENSTWO;
		if (liczba <= przedzial) {
			wybor = WyborOrganizmu(i);
			break;
		}
	}
	//zmienno-przecinkowy przypadek
	if (przedzial > 0.9999 && wybor == brak)
		wybor = WyborOrganizmu(brak - 1);

	switch (wybor) {
	case wilk:
		nowyOrganizm = new Wilk(*this, polozenie);
		break;
	case owca:
		nowyOrganizm = new Owca(*this, polozenie);
		break;
	case lis:
		nowyOrganizm = new Lis(*this, polozenie);
		break;
	case zolw:
		nowyOrganizm = new Zolw(*this, polozenie);
		break;
	case antylopa:
		nowyOrganizm = new Antylopa(*this, polozenie);
		break;
	case trawa:
		nowyOrganizm = new Trawa(*this, polozenie);
		break;
	case mlecz:
		nowyOrganizm = new Mlecz(*this, polozenie);
		break;
	case guarana:
		nowyOrganizm = new Guarana(*this, polozenie);
		break;
	case wilczeJagody:
		nowyOrganizm = new WilczeJagody(*this, polozenie);
		break;
	case barszczSosnowskiego:
		nowyOrganizm = new BarszczSosnowskiego(*this, polozenie);
		break;
	default:
		return nullptr;
	}

	return nowyOrganizm;
}

void Swiat::zaiinicjujNoweOrganizmy() {
	if (noweOrganizmy.size() == 0)
		return;
	while (noweOrganizmy.size() > 0) {
		posortowaneOrganizmy.push_back(noweOrganizmy.front());
		noweOrganizmy.pop();
	}
	this->SortujOrganizmy();
}

bool Swiat::ZakonczSwiat() {
	return zakoncz;
}

void Swiat::RysujSwiat() {
	Pozycja pRys(Pozycja(POZ_SWIATA_X, POZ_SWIATA_Y));
	GetWydarzenia().PozycjaWypisu(pRys);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), KOLOR_KRAWEDZ);

	for (int i=0; i < szerokosc + OBRAMOWANIE; ++i)
		std::cout<<"X";

	pRys.AktualizujY(1);
	for (int y = 0; y < wysokosc; ++y, pRys.AktualizujY(1)) {
		GetWydarzenia().PozycjaWypisu(pRys);
		std::cout << "X";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), KOLOR_PLANSZA);
		for (int x = 0; x < szerokosc; ++x)
		{
			if (organizmy[y][x] == nullptr)
				std::cout << " ";
			else
				organizmy[y][x]->Rysuj();
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), KOLOR_KRAWEDZ);
		std::cout << "X";
	}

	GetWydarzenia().PozycjaWypisu(pRys);
	for (int i = 0; i < szerokosc + OBRAMOWANIE; ++i)
		std::cout << "X";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), KOLOR_TLO);
}

bool Swiat::WczytajKlawisz() {
	GetWydarzenia().WczytajKlawisz();
	int c = _getch();

	if (c == STRZALKA) {
		c = _getch();
	}

	c = tolower(c);
	switch (c) {
	case ZAKONCZ:
		this->zakoncz = true;
		GetWydarzenia().PozycjaWypisu(Pozycja(0, this->wysokosc + POZ_SWIATA_Y + OBRAMOWANIE));
		return true;
	case ZAPISZ:
		this->ZapiszSwiat();
		return false;
	default:
		return false;
	}
}

void Swiat::SortujOrganizmy() {
	std::stable_sort(posortowaneOrganizmy.begin(), posortowaneOrganizmy.end(), PorownanieInicjatywy());
}

bool Swiat::PorownanieInicjatywy::operator()(const Organizm* lewy, const Organizm* prawy) const {
	return lewy->GetInicjatywa() > prawy->GetInicjatywa();
}

void Swiat::WykonajTure() {
	Pozycja ostatnia = GetWydarzenia().GetPozycjaWydarzen();
	GetWydarzenia().SetPozycjaWydarzen(Pozycja((POZ_SWIATA_X + OBRAMOWANIE * 2 + this->szerokosc), (POZ_SWIATA_Y)));
	Pozycja aktualna = GetWydarzenia().GetPozycjaWydarzen();

	GetWydarzenia().WyczyscWydarzenia(aktualna, ostatnia);

	GetWydarzenia().NowaTura(this->tura);
	++tura;

	for (auto organizm : posortowaneOrganizmy)
		organizm->Akcja();

	WalidujOrganizmy();
	this->zaiinicjujNoweOrganizmy();
	//std::this_thread::sleep_for(std::chrono::milliseconds(CZAS_TRWANIA_RUCHU * 5));

}

void Swiat::WalidujOrganizmy() {
	for (int i = 0; i < posortowaneOrganizmy.size(); ++i) {
		Organizm* organizm = GetOrganizm(posortowaneOrganizmy[i]->GetPozycja());

		if (organizm != posortowaneOrganizmy[i]) {
			delete posortowaneOrganizmy[i];
			posortowaneOrganizmy.erase(posortowaneOrganizmy.begin() + i);
			--i;
		}
	}
}

Organizm* Swiat::GetOrganizm(const Pozycja& pozycjaOrg) {
	Pozycja pozycja = KontrolaPozycji(pozycjaOrg);

	return organizmy[pozycja.GetY()][pozycja.GetX()];
}

bool Swiat::Przenies(Organizm* oczekujacy, const Pozycja& docelowa) {
	if (oczekujacy == nullptr)
		return false;
	Pozycja p = KontrolaPozycji(docelowa);

	doPrzeniesienia.emplace_back(oczekujacy->GetPozycja(), p);
	PrzeniesNow(doPrzeniesienia.front());
	doPrzeniesienia.pop_back();
	return true;
}

void Swiat::PrzeniesNow(const PrzeniesDo& przeniesDo) {
	int x1 = przeniesDo.poczatkowa.GetX();
	int	y1 = przeniesDo.poczatkowa.GetY();
	int	x2 = przeniesDo.ostateczna.GetX();
	int y2 = przeniesDo.ostateczna.GetY();

	if (organizmy[y1][x1] != nullptr && organizmy[y2][x2] != nullptr)
		return;
	else if (organizmy[y1][x1] == nullptr && organizmy[y2][x2] == nullptr)
		return;

	std::swap(organizmy[y1][x1], organizmy[y2][x2]);
	if (organizmy[y1][x1] != nullptr)
		organizmy[y1][x1]->SetPozycja(x1, x2);
	if (organizmy[y2][x2] != nullptr)
		organizmy[y2][x2]->SetPozycja(x2, y2);
}

bool Swiat::Usmiertelnij(Organizm* orgaznizmDoZabicia) {
	if (orgaznizmDoZabicia == nullptr)
		return false;

	doZabicia.push(orgaznizmDoZabicia->GetPozycja());
	UsmiertelnijNow(doZabicia.front());
	doZabicia.pop();
	return true;
}

void Swiat::UsmiertelnijNow(const Pozycja& Usmiertelnij) {
	Organizm* organizm = organizmy[Usmiertelnij.GetY()][Usmiertelnij.GetX()];
	if (organizm == nullptr)
		return;

	for (int i = 0; i < doPrzeniesienia.size(); ++i) {
		if (doPrzeniesienia[i].poczatkowa == Usmiertelnij) {
			doPrzeniesienia.erase(doPrzeniesienia.begin() + i);
			--i;
		}
	}

	organizmy[Usmiertelnij.GetY()][Usmiertelnij.GetX()] = nullptr;
}

std::vector<Organizm*> Swiat::GetSasiednieOrganizmy(const Pozycja& polozenie) {
	std::vector<Pozycja> mozliweKierunki = Pozycja::GetMozliweKierunki(polozenie);
	std::vector<Organizm*> sasiednieOrganizmy;

	for (int i = 0; i < mozliweKierunki.size(); ++i)
		sasiednieOrganizmy.push_back(this->GetOrganizm(mozliweKierunki[i]));

	return sasiednieOrganizmy;
}

