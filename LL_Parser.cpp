#include "LL_Parser.h"
#include <iostream>

LL_Parser::LL_Parser()
{
	aktualnaSekcja = Podsekcje::LINIA;
}

void LL_Parser::Parse(std::string line)
{
	if (aktualnaSekcja == Podsekcje::NONE)
	{
		std::cout << "BRAK";
		// Pobieramy rodzaj podsekcji i iloœæ elementów
		ParseOtwarciePodsekcji(line);
	}
	else if (aktualnaSekcja == Podsekcje::LINIA)		// OK!
	{
		if (counterLinii <= liczbaLinii)
		{
			std::cout << "LINIA" << std::endl;
			// Pobieramy numer linii i jej charakter
			ParseOpisLinii(line);
			ResetujPodsekcje();
		}
	}
	else if (aktualnaSekcja == Podsekcje::TR)
	{
		std::cout << "TR: " << counterTR << std::endl;
		// Pobieramy opis przebiegu trasy
		if (counterTR <= liczbaPrzebiegowTras) 
			ParsePrzebiegTrasy(line);

		ResetujPodsekcje();
	}
	else if (aktualnaSekcja == Podsekcje::LW)    // OK!
	{
		std::cout << "LW: " << counterLW << std::endl;
		if (counterLW <= liczbaWierszyOpisuTrasyLW)
		{
			ParseOpisPrzebiegu(line);
			counterLW++;
		}
		else
			ResetujPodsekcje();
	}
	else if (aktualnaSekcja == Podsekcje::RP) // OK!
	{
		std::cout << "RP: " << counterRP << std::endl;
		if (counterRP <= liczbaTabelOdjazdow)
		{
			ParseRPPrzystanek(line);
			ResetujPodsekcje();
		}
		else
		{
			counterTR++;
			aktualnaSekcja = Podsekcje::TR;
		}
	}
	else if (aktualnaSekcja == Podsekcje::TD)	// OK!
	{
		std::cout << "TD: " << counterTD << std::endl;
		if (counterTD <= liczbaTypowDniKursowania)
		{
			ParseTypKursowania(line);
			ResetujPodsekcje();
		}
		else
			ResetujPodsekcje();
	}
	else if (aktualnaSekcja == Podsekcje::WG)    // OK!
	{
		std::cout << "WG: " << counterWG << std::endl;
		if (counterWG <= liczbaGodzin)
		{
			ParseGodzinyOdjazdow(line);
			counterWG++;
		}
		else
			ResetujPodsekcje();
	}
	else if (aktualnaSekcja == Podsekcje::OD)     // OK!
	{
		std::cout << "OD: " << counterOD << std::endl;
		if (counterOD <= liczbaOdjazdow)
		{
			ParseOdjazdy(line);
			counterOD++;
		}
		else
		{
			aktualnaSekcja = Podsekcje::TD;
			counterTD++;
		}
	}
	else if (aktualnaSekcja == Podsekcje::OP)     // OK!
	{
		std::cout << "OP: " << counterOP << std::endl;
		if (counterOP <= liczbaWierszyOpisu)
		{
			// TODO CO MA ROBIC

			counterOP++;
		}
		else
		{
			aktualnaSekcja = Podsekcje::RP;
			counterRP++;
		}
	}
	else if (aktualnaSekcja == Podsekcje::WK)		// OK!
	{
		std::cout << "WK: " << counterWK << std::endl;
		if (counterWK <= liczbaPrzebiegowKursow)
		{
			ParsePrzebiegiKursow(line);
			counterWK++;
		}
		else
		{
			aktualnaSekcja = Podsekcje::LINIA;
			counterLinii++;
		}
		
	}
}

void LL_Parser::ustawLiczbeLinii(int val)
{
	liczbaLinii = val;
}

void LL_Parser::ParseOtwarciePodsekcji(std::string line)
{
 	std::string regs = "[*](\\S{2})\\s+(\\d+)";
	std::regex reg(regs);
	std::smatch wynik;

	if (!std::regex_search(line, wynik, reg))
		return;

	// wynik[1] = jaka sekcja
	// wynik[2] = wartosc
	int wartosc = std::stoi(wynik[2]);
	
	std::cout << " " << wynik[1] << std::endl;
	if (wynik[1] == "TR")
	{
		aktualnaSekcja = Podsekcje::TR;
		liczbaPrzebiegowTras = wartosc;
		counterTR = 1;
	}
	else if (wynik[1] == "LW")
	{
		aktualnaSekcja = Podsekcje::LW;
		liczbaWierszyOpisuTrasyLW = wartosc;
		counterLW = 1;
	}
	else if (wynik[1] == "RP")
	{
		liczbaTabelOdjazdow = wartosc;
		aktualnaSekcja = Podsekcje::RP;
		counterRP = 1;
	}
	else if (wynik[1] == "TD")
	{
		aktualnaSekcja = Podsekcje::TD;
		liczbaTypowDniKursowania = wartosc;
		counterTD = 1;
	}
	else if (wynik[1] == "WG")
	{
		aktualnaSekcja = Podsekcje::WG;
		liczbaGodzin = wartosc;
		counterWG = 1;
	}
	else if (wynik[1] == "OD")
	{ 
		aktualnaSekcja = Podsekcje::OD;
		liczbaOdjazdow = wartosc;
		counterOD = 1;
	}
	else if (wynik[1] == "OP")
	{
		aktualnaSekcja = Podsekcje::OP;
		liczbaWierszyOpisu = wartosc;
		counterOP = 1;
	}
	else if (wynik[1] == "WK")
	{
		aktualnaSekcja = Podsekcje::WK;
		liczbaPrzebiegowKursow = wartosc;
		counterWK;
	}
}

void LL_Parser::ParseOpisLinii(std::string line)
{ 
	std::string regs = "Linia:\\s+(\\S{1,4})\\s+-\\s+(.*)";

	std::regex reg(regs);
	std::smatch wynik;

	std::regex_search(line, wynik, reg);

	// Wynik[1]  => numer linii
	// Wynik[2]  => Charakter linii
}

void LL_Parser::ParsePrzebiegTrasy(std::string line)
{

	//	TODO
	// POPRAWIÆ GDY NIE WYSTEPUJE PRZECINEK
	std::string regs = "\\s+(\\S+)\\s*,\\s*(.+?)[,]{0,1}\\s{2,}(\\S{2})\\s*==>\\s*(.+?)[,]{0,1}\\s{2,}(\\S{2})\\s*Kier\.\\s{1}(\\w{1})\\s*Poz.\\s{1}(.+)";

	std::regex reg(regs);
	std::smatch wynik;

	std::regex_search(line, wynik, reg);

	// wynik[1] = skrot opisujacy wariant trasy
	// wynik[2] = nazwa przystanku rozpoczynajacego trase
	// wynik[3] = symbol miejscowosci przystanku poczatkowego
	// wynik[4] = nazwa przystanku koncoweg
	// wynik[5] = symbol miejscowosci przystanku koncowego
	// wynik[6] = kierunek trasy
	// wynik[7] = poziom trasy
}
// Podsekcja LW
void LL_Parser::ParseOpisPrzebiegu(std::string line)
{
	// DODAC PRZECINEK TAK LUB NIE
	std::string regs = "\\s+(.*?)[,]{0,1}\\s{2,}(r){0,1}\\s*(\\d+)\\s+(.+?)[,]{0,1}\\s{2,}(\\S{2})\\s+(\\d{2})\\s+(N¯){0,1}\\s*[|](.{2})[|](.{2})[|]";
	
	std::regex reg(regs);
	std::smatch wynik;
	
	std::regex_search(line, wynik, reg);

	// wynik[1]  = ulica lub ""
	// wynik[2]  = r lub false
	// wynik[3]  = numer przystanku
	// wynik[4]  = ulica 2 (?)
	// wynik[5]  = kod miejscowosci
	// wynik[6] = numer przystanku w zespole
	// wynik[7] = N¯ lub false
	// wynik[8] = minimalny czas przejazdu
	// wynik[9] = maksymalny czas przejazdu

}

// Podsekcja RP
void LL_Parser::ParseRPPrzystanek(std::string line)
{
	std::string regs = "(\\d+)";
	std::regex reg(regs);
	std::smatch wynik;

	std::regex_search(line, wynik, reg);

	// wynik[1] = numer przystanku zgodny z sekcja "ZP"

	aktualnyPrzystanek = std::stoi(wynik[1]);
}

// Podsekcja TD
void LL_Parser::ParseTypKursowania(std::string line)
{
	std::string regs = "(\\S{2})";
	std::regex reg(regs);
	std::smatch wynik;

	std::regex_search(line, wynik, reg);

	// wynik[1] = typ kursowania/dnia - zgodny z sekcja "TY"
	typKursowania = wynik[1];
}

// Podsekcja WG
void LL_Parser::ParseGodzinyOdjazdow(std::string line)
{
	std::string regs = "G\\s+(\\d+)\\s+(\\d+):\\s+(.*)";
	std::regex reg(regs);
	std::smatch wynik;

	std::regex_search(line, wynik, reg);

	// wynik[1] = iloœæ odjazdow w ciagu godziny
	// wynik[2] = godzina
	// wynik[3] = minuty

	int iloscOdjazdow = std::stoi(wynik[1]);
	regs = "";
	for (int i = 0; i < iloscOdjazdow; i++)
		regs.append("[\[](\\S+)\\s*");

	reg = std::regex(regs);
	std::string minuty = wynik[3];
	
	std::regex_search(minuty, wynik, reg);

	int ostatniZnak;
	std::string minuta;
	for (int i = 1; i <= iloscOdjazdow; i++)
	{
		minuta = wynik[i];
		if (minuta.find("]") != std::string::npos)
			minuta.pop_back();

		// minuta TODO
	}
}

// Podsekcja OD
void LL_Parser::ParseOdjazdy(std::string line)
{
	std::string regs = "(\\S+)\\s+(.+?)/(.+?)/(\\S{5})";
	std::regex reg(regs);
	std::smatch wynik;

	std::regex_search(line, wynik, reg);

	// wynik[1] = godzina odjazdu
	// wynik[2] = wariant trasy
	// wynik[3] = typ, dzien kursowania
	// wynik[4] = godzina odjazdu z przystanku rozpoczynajacego kurs

	// wynik[2]/wynik[3]/wynik[4] = unikalny identyfikator trasy
}

// Podsekcja WK
void LL_Parser::ParsePrzebiegiKursow(std::string line)
{
	std::string regs = "\\s+(\\S+)\\s+(\\d{6})\\s+(\\S{2})\\s+(\\S+)\\s*([B|P]{0,1})";
	std::regex reg(regs);
	std::smatch wynik;

	std::regex_search(line, wynik, reg);

	// wynik[1] = identyfikator trasy
	// wynik[2] = numer przystanku
	// wynik[3] = typ, dzien kursowania
	// wynik[4] = godzina odjazdu z przystanku lub przyjazd na przystanek koncowy
	// wynik[5] = dodatkowy atrybut kursu (B lub P)
}

void LL_Parser::ResetujPodsekcje()
{
	aktualnaSekcja = Podsekcje::NONE;
}
