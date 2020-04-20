#pragma once
#include <string>
#include <vector>
#include <map>

enum class CHARAKTER_LINII {
	STALY,
	NA_ZADANIE,
	DLA_WSIADAJACYCH,
	DLA_WYSIADAJACYCH,
	KRANCOWY,
	POSTOJOWY
};
struct Przystanek
{
	int numer;
	std::string kierunek;
	std::string X;
	std::string Y;
	std::string Pu;
	std::vector<std::string> linie;
	std::map<std::string, CHARAKTER_LINII> charakterLinii;
};

class ZP_Parser
{
	int liczbaZespolowPrzystankowych;
	int aktualnyZespolPrzystankowyCounter;
	int aktualnyZespolPrzystankowy;


	int liczbaPrzystankow;
	int aktualnyPrzystanekCounter;
	int aktualnyPrzystanek;

	int liczbaWskazanLinii;
	int wskazaniaLiniiCounter;

	std::map<int, Przystanek> przystanki;
public:
	ZP_Parser();
	void setLiczbaZespolowPrzystankowych(int);
	void Parse(std::string);
	

private:
	int ParseLiczbaPrzystankow(std::string);
	void ParsePrzystanek(std::string);
	void ParseLinia(std::string);


	CHARAKTER_LINII jakiCharakterLinii(std::string);
};

