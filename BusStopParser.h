#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "ZP_Parser.h"
#include "LL_Parser.h"

struct ZespolPrzystankowy
{
	std::string nazwa;
	std::string symbolMiejscowosci;
	std::string miejscowosc;
};
class BusStopParser
{
public:
	enum class Categories
	{
		NONE,
		TY,
		KA,
		ZA,
		KD,
		SM,
		ZP,
		LL
	};

private:
	ZP_Parser* zpParser;
	LL_Parser* llParser;
	BusStopParser::Categories curCategory = Categories::NONE;
	int linesInCategory;
	int linesCounter;
	std::fstream* file;
	std::map<Categories, std::string> regexs;
	std::string curDate;

	std::vector<std::string> typyDniKursowania;
	std::map<std::string, std::string> typyDniKursowaniaOpis;

	std::vector<std::string> dzisiejszeTypyKursowania;

	std::vector<std::string> dzisiejszeLinie;
	std::map<std::string, std::string> typDzisiejszychLinii;

	std::vector<int> numeryZespolowPrzystankowych;
	std::map<int, ZespolPrzystankowy> zespolyPrzystankowe;

	std::vector<std::string> symboleMiejscowosci;
	std::map<std::string, std::string> miejscowosci;	
public:
	~BusStopParser();
	BusStopParser(std::string);
	BusStopParser(std::fstream*);
	void Parse();

private:
	BusStopParser();
	void PrepareDate();
	void ParseCategory(std::string);
	void ParseKA(std::string);
	void ParseTY(std::string);
	void ParseZA(std::string);
	void ParseKD(std::string);
	void ParseSM(std::string);
};

