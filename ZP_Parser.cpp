#include "ZP_Parser.h"
#include <iostream>
#include <regex>

ZP_Parser::ZP_Parser()
{
	liczbaZespolowPrzystankowych = 0;
	aktualnyZespolPrzystankowyCounter = 0;
	aktualnyZespolPrzystankowy = 0;

	liczbaPrzystankow = 0;
	aktualnyPrzystanekCounter = 0;
	aktualnyPrzystanek = -1;

	int liczbaWskazanLinii = 0;
	int wskazaniaLiniiCounter = 0;
}

void ZP_Parser::setLiczbaZespolowPrzystankowych(int val)
{
	liczbaZespolowPrzystankowych = val;
}

void ZP_Parser::Parse(std::string line)
{
	if (line == "#ZP")
	{
		return;
	}
	if (aktualnyZespolPrzystankowyCounter > liczbaZespolowPrzystankowych)
	{
		// Koniec sekcji "ZP"
		// Zrobiæ informacjê dla BusStopParser;
		return;
	}
	
	

	if (aktualnyPrzystanekCounter > liczbaPrzystankow)
	{
		// Konczymy zespó³ przystanków
		aktualnyZespolPrzystankowy = 0;
		aktualnyPrzystanek = 0;
		aktualnyPrzystanekCounter = 0;
		liczbaPrzystankow = 0;
		aktualnyZespolPrzystankowyCounter++;
	}
	else if (aktualnyZespolPrzystankowy == 0)
	{
		// Rozpoczynamy nowy zespó³ przystankowy
		aktualnyZespolPrzystankowy = std::stoi(line.substr(3, 4));
	}
	else if (liczbaPrzystankow == 0)
	{
		// Pobieramy liczbê przystanków
		liczbaPrzystankow = ParseLiczbaPrzystankow(line);
		aktualnyPrzystanekCounter = 1;
	}
	else if (liczbaWskazanLinii == 0)
	{
		// Rozpoczynamy nowy przystanek
		ParsePrzystanek(line);
		wskazaniaLiniiCounter = 1;
	}
	else
	{
		// Parsujemy wskazania linii
		ParseLinia(line);
		wskazaniaLiniiCounter++;

		if (wskazaniaLiniiCounter > liczbaWskazanLinii)
		{
			// Koñczymy przystanek
			wskazaniaLiniiCounter = 0;
			liczbaWskazanLinii = 0;
			aktualnyPrzystanekCounter++;
		}
	}


}

int ZP_Parser::ParseLiczbaPrzystankow(std::string line)
{
	std::regex reg("(\\d+)");
	std::smatch wynik;
	std::regex_search(line, wynik, reg);

	// wynik[1] = Liczba przystanków w zespole

	return std::stoi(wynik[1]);
}

void ZP_Parser::ParsePrzystanek(std::string line)
{
	std::regex reg("(\\d{6})\\s+(\\d+)\\s+Ul\./Pl\.:\\s+(.+?)[,]{0,1}\\s{2,}Kier\.:\\s+(.+?)[,]{0,1}\\s{2,}Y=\\s{0,1}(\\S+)\\s+X=\\s{0,1}(\\S+)\\s+Pu=(.?)");
	std::smatch wynik;
	std::regex_search(line, wynik, reg);
	

	// wynik[1] = Numer przystanku
	// wynik[2] = liczba wykazow linii
	// wynik[3] = ulica, na ktorej jest przystanek (równie¿ pobrane wczeœniej)
	// wynik[4] = kierunek zbiorczy dla przystanku
	// wynik[5] = gps X
	// wynik[6] = gps Y
	// wynik[7] = Pu (?)

	Przystanek przystanek;
	przystanek.numer = std::stoi(wynik[1]);
	przystanek.kierunek = wynik[4];
	przystanek.X = wynik[5];
	przystanek.Y = wynik[6];
	przystanek.Pu = wynik[7];

	przystanki[przystanek.numer] = przystanek;

	liczbaWskazanLinii = std::stoi(wynik[2]);
	aktualnyPrzystanek = przystanek.numer;
}

void ZP_Parser::ParseLinia(std::string line)
{
	std::string regs = "L\\s+(\\d+)\\s+-\\s+(.*):\\s+(.*)";

	std::regex reg(regs);
	std::smatch wynik;
	std::regex_search(line, wynik, reg);

	// wynik[1] = linia linii w danym zakresie
	// wynik[2] = charkter linii
	// wynik[3] = linie

	int linii = std::stoi(wynik[1]);
	std::string linie = wynik[3];
	CHARAKTER_LINII charakter = jakiCharakterLinii(wynik[2]);

	regs = "";
	for (int i = 0; i < linii; i++)
		regs.append("(\\S+)\\s+");
	
	reg = std::regex(regs);
	std::regex_search(linie, wynik, reg);

	for (int i = 1; i <= linii; i++)
	{
		przystanki[aktualnyPrzystanek].linie.push_back(wynik[i]);
		przystanki[aktualnyPrzystanek].charakterLinii[wynik[i]] = charakter;
	}

}

CHARAKTER_LINII ZP_Parser::jakiCharakterLinii(std::string charakter)
{
	if (charakter == "sta³y")
		return CHARAKTER_LINII::STALY;
	else if (charakter == "na ¿¹danie")
		return CHARAKTER_LINII::NA_ZADANIE;
	else if (charakter == "dla wsiadaj¹cych")
		return CHARAKTER_LINII::DLA_WSIADAJACYCH;
	else if (charakter == "dla wysiadaj¹cych")
		return CHARAKTER_LINII::DLA_WYSIADAJACYCH;
	else if (charakter == "krañcowy")
		return CHARAKTER_LINII::KRANCOWY;
	else if (charakter == "postojowy")
		return CHARAKTER_LINII::POSTOJOWY;
}

