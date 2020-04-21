#pragma once
#include <string>
#include <regex>
class LL_Parser
{
	enum class Podsekcje
	{
		NONE,
		LINIA,
		TR,
		START_LW,
		LW,
		RP,
		TD,
		WG,
		OD,
		OP,
		WK
	};

	int liczbaLinii;
	int counterLinii = 1;
	Podsekcje aktualnaSekcja;

	int liczbaPrzebiegowTras;
	int counterTR;

	int liczbaWierszyOpisuTrasyLW;
	int counterLW;

	int liczbaTabelOdjazdow;
	int counterRP;
	
	int aktualnyPrzystanek;

	int liczbaTypowDniKursowania;
	int counterTD;

	std::string typKursowania;

	int liczbaGodzin;
	int counterWG;

	int liczbaOdjazdow;
	int counterOD;

	int liczbaWierszyOpisu;
	int counterOP;

	int liczbaPrzebiegowKursow;
	int counterWK;
public:
	LL_Parser();
	void Parse(std::string);
	void ustawLiczbeLinii(int);
private:
	void ParseOtwarciePodsekcji(std::string);
	void ParseOpisLinii(std::string);
	void ParsePrzebiegTrasy(std::string);
	void ParseOpisPrzebiegu(std::string);
	void ParseRPPrzystanek(std::string);
	void ParseTypKursowania(std::string);
	void ParseGodzinyOdjazdow(std::string);
	void ParseOdjazdy(std::string);
	void ParsePrzebiegiKursow(std::string);

	void ResetujPodsekcje();
};

