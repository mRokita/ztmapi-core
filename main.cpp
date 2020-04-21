#include <fstream>
#include <iostream>
#include <string>
#include "BusStopParser.h"
#include "LL_Parser.h"

int main()
{
	//LL_Parser llparser;
	//llparser.ParsePrzebiegiKursow("");

	std::fstream rozklad;
	rozklad.open("RA200322.txt", std::ios::in);
	BusStopParser parser(&rozklad);
	parser.Parse();
	return 0;
}