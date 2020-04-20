#include <fstream>
#include <iostream>
#include <string>
#include "BusStopParser.h"

int main()
{
	std::fstream rozklad;
	//rozklad.open("RA200322.txt", std::ios::in);
	rozklad.open("pliki/ZP.txt", std::ios::in);
	BusStopParser parser(&rozklad);
	parser.Parse();
	return 0;
}