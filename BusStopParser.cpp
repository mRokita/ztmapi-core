#include "BusStopParser.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>

BusStopParser::BusStopParser()
{
	PrepareDate();
	llParser = new LL_Parser();
	zpParser = new ZP_Parser();
}
BusStopParser::~BusStopParser()
{
	delete llParser;
	delete zpParser;
}
BusStopParser::BusStopParser(std::string fileName) : BusStopParser()
{
	file->open(fileName, std::ios::in);
}

BusStopParser::BusStopParser(std::fstream* fileRef) : BusStopParser()
{
	file = fileRef;
}

void BusStopParser::PrepareDate()
{
	//auto t = std::time(nullptr);
	//auto tm = *std::localtime(&t);
	//std::cout << std::put_time(&tm, "%F");
	//std::stringstream curdate;
	//curdate << std::put_time(&tm, "%F");
	//curDate = curdate.str();


	curDate = "2020-03-22";
	//curDate = "2018-12-30";
}

void BusStopParser::Parse()
{
	std::string line;

	while (std::getline(*file, line))
	{
		switch (curCategory)
		{
		case Categories::NONE:
			ParseCategory(line);
			break;
		case Categories::TY:
			ParseTY(line);
			break;

		case Categories::KA:
			ParseKA(line);
			break;
		case Categories::ZA:
			ParseZA(line);
			break;
		case Categories::KD:
			ParseKD(line);
			break;
		case Categories::SM:
			ParseSM(line);
			break;
		case Categories::ZP:
			zpParser->Parse(line);
			break;
		case Categories::LL:
			llParser->Parse(line);
			break;
		}

	}
}

void BusStopParser::ParseCategory(std::string line)
{
	std::string regs = "[\*](\\S{2})\\s+(\\d+)";

	std::regex reg(regs);
	std::smatch wynik;

	if (!std::regex_search(line, wynik, reg))
		return;

	// wynik[1] = kategoria
	// wynik[2] = ilosc wynikow

	if (wynik[1] == "TY")
		curCategory = Categories::TY;
	else if (wynik[1] == "KA")
		curCategory = Categories::KA;
	else if (wynik[1] == "ZA")
		curCategory = Categories::ZA;
	else if (wynik[1] == "KD")
		curCategory = Categories::KD;
	else if (wynik[1] == "SM")
		curCategory = Categories::SM;
	else if (wynik[1] == "ZP")
	{
		curCategory = Categories::ZP;
		std::regex reg("(\\d+)");
		std::smatch wynik;
		std::regex_search(line, wynik, reg);
		zpParser->setLiczbaZespolowPrzystankowych(std::stoi(wynik[1]));
	}
	else if (wynik[1] == "LL")
	{
		curCategory = Categories::LL;
		std::regex reg("(\\d+)");
		std::smatch wynik;
		std::regex_search(line, wynik, reg);
		llParser->ustawLiczbeLinii(std::stoi(wynik[1]));
	}

	linesInCategory = std::stoi(wynik[2]);
	linesCounter = 0;
}

void BusStopParser::ParseKA(std::string line)
{
	std::string regs = curDate + "\\s*(\\d+)\\s*(.*)";

	std::regex reg(regs);
	std::smatch wynik;
	if (!std::regex_search(line, wynik, reg))
		return;

	// wynik[1] = liczbe typów dni kursowania
	// wynik[2] = lista typów dni kursowania

	int counter = std::stoi(wynik[1]);
	std::string newRegs = "";
	for (int i = 0; i < counter; i++)
		newRegs.append("(\\S{2})\\s*");

	reg = std::regex(newRegs);
	std::string temp = wynik[2];
	std::regex_search(temp, wynik, reg);

	for (int i = 1; i <= counter; i++)
		dzisiejszeTypyKursowania.push_back(wynik[i]);

	std::cout << dzisiejszeTypyKursowania[1];
}


void BusStopParser::ParseTY(std::string line)
{
	std::string regs = "(\\S{2})\\s+(.*)";

	std::regex reg(regs);
	std::smatch wynik;

	std::regex_search(line, wynik, reg);

	// wynik[1] = symbol typu dnia
	// wynik[2] = opis typu dnia

	typyDniKursowania.push_back(wynik[1]);
	typyDniKursowaniaOpis[wynik[1]] = wynik[2];
}

void BusStopParser::ParseZA(std::string line)
{
	ZespolPrzystankowy data;

	std::string regs = "(\\d{4})\\s+(.+?)[,]{0,1}\\s{2,}(\\S{2})\\s+(.*)";

	std::regex reg(regs);
	std::smatch wynik;
	std::regex_search(line, wynik, reg);

	// wynik[1] = unikalny numer zespo³u przystankowego
	// wynik[2] = nazwa zespo³u przystankowego
	// wynik[3] = symbol miejscowosci
	// wynik[4] = nazwa miejscowosci

	int numer = std::stoi(wynik[1]);
	numeryZespolowPrzystankowych.push_back(numer);

	data.nazwa = wynik[2];
	data.symbolMiejscowosci = wynik[3];
	data.miejscowosc = wynik[4];
	zespolyPrzystankowe[numer] = data;
}

void BusStopParser::ParseKD(std::string line)
{
	//		TODO
	// Poprawic zeby pomijalo date
	if (line.find(curDate) != std::string::npos)
		return;

	std::string regs = "\\s+(\\S+)\\s+(\\S{2})";

	std::regex reg(regs);
	std::smatch wynik;
	std::regex_search(line, wynik, reg);
	
	// wynik[1] = numer linii
	// wynik[2] = typ dnia kursowania

	dzisiejszeLinie.push_back(wynik[1]);
	typDzisiejszychLinii[wynik[1]] = wynik[2];
}

void BusStopParser::ParseSM(std::string line)
{
	std::string regs = "(\\S{2})\\s+(.+?)\\s{2,}";

	std::regex reg(regs);
	std::smatch wynik;
	std::regex_search(line, wynik, reg);

	// wynik[1] = symbol miejscowosci
	// wynik[2] = miejscowosc

	symboleMiejscowosci.push_back(wynik[1]);
	miejscowosci[wynik[1]] = wynik[2];
}

