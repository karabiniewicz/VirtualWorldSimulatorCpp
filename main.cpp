#include "Swiat.h"
#include<time.h>

int main() {
	std::srand(time(NULL));

	Swiat swiat;
	swiat.MenuGlowne();
	while (!swiat.ZakonczSwiat()) {
		swiat.RysujSwiat();
		if (swiat.WczytajKlawisz())
			continue;
		swiat.WykonajTure();
	}
	return 0;
}