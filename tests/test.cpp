#define CATCH_CONFIG_MAIN

#include "../include/ScheduleManager.h"
#include "../include/TYSection.h"
#include "../include/KDSection.h"
#include "../include/ZASection.h"
#include "../include/LLSection.h"
#include "../include/WKSection.h"
#include "../include/PRSection.h"
#include "catch2/catch.hpp"
#include <boost/locale.hpp>

std::string boostEncode(const std::string& str)
{
	return boost::locale::conv::to_utf<char>(str, "windows-1250");
}


TEST_CASE("Sekcja TY", "[TY]")
{
	ScheduleManager schedManager;

	std::shared_ptr<TYSection> TYsection = std::make_shared<TYSection>(&schedManager);

	TYsection->processLine("   D1   PONIEDZIA�EK\r");
	REQUIRE(schedManager.dayTypes[0].id == "D1");
	REQUIRE(schedManager.dayTypes[0].name == "PONIEDZIA�EK");

	TYsection->processLine("   N5   NOC PI�TEK/SOBOTA\r");
	REQUIRE(schedManager.dayTypes[1].id == "N5");
	REQUIRE(schedManager.dayTypes[1].name == "NOC PI�TEK/SOBOTA");

	TYsection->processLine("   WW   WSZYSTKICH �WI�TYCH\r");
	REQUIRE(schedManager.dayTypes[2].id == "WW");
	REQUIRE(schedManager.dayTypes[2].name == "WSZYSTKICH �WI�TYCH");

	TYsection->processLine("   EX   ROZK�AD SPEC.\r");
	REQUIRE(schedManager.dayTypes[3].id == "EX");
	REQUIRE(schedManager.dayTypes[3].name == "ROZK�AD SPEC.");


}

//TEST_CASE("Sekcja KD", "[KD]")
//{
//	ScheduleManager schedManager;
//
//	std::shared_ptr<KDSection> KDsection = std::make_shared<KDSection>(&schedManager);
//
//	// Tutaj trzeba zmieni� na dat� dzisiejsz� lub da� w SchedManager jakis testMode
//	// Gdzie wstawia wybran� date
//
//	KDsection->processLine("   " + schedManager.getScheduleDate() + "  293");
//
//	KDsection->processLine("       10   DS");
//	REQUIRE(schedManager.getDayType("10") == "DS");
//
//	KDsection->processLine("      L-1   DS");
//	REQUIRE(schedManager.getDayType("L-1") == "DS");
//
//	KDsection->processLine("      L11   DS");
//	REQUIRE(schedManager.getDayType("L11") == "DS");
//
//	KDsection->processLine("      N02   NS");
//	REQUIRE(schedManager.getDayType("N02") == "NS");
//
//	KDsection->processLine("      N44   NO");
//	REQUIRE(schedManager.getDayType("N44") == "NO");
//
//	KDsection->processLine("       R7   DS");
//	REQUIRE(schedManager.getDayType("R7") == "DS");
//
//	KDsection->processLine("       RL   DS");
//	REQUIRE(schedManager.getDayType("RL") == "DS");
//
//	KDsection->processLine("       RL   DS");
//	REQUIRE(schedManager.getDayType("RL") == "DS");
//
//	KDsection->processLine("      WKD   DS");
//	REQUIRE(schedManager.getDayType("RL") == "DS");
//
//
//	KDsection->processLine("   2020-03-23  293");
//	KDsection->processLine("      N44   NS");
//	REQUIRE(schedManager.getDayType("N44") == "NO");
//
//
//}


TEST_CASE("Sekcja ZA", "[ZA]")
{
	ScheduleManager schedManager;

	std::shared_ptr<ZASection> ZAsection = std::make_shared<ZASection>(&schedManager);

	std::string line;

	line = "   4009   1 Sierpnia,                         --  WARSZAWA";
	ZAsection->processLine(boostEncode(line));
	REQUIRE(schedManager.stopGroups[0].id == 4009);
	REQUIRE(schedManager.stopGroups[0].name == boostEncode("1 Sierpnia"));
	REQUIRE(schedManager.stopGroups[0].regionId == "--");
	REQUIRE(schedManager.stopGroups[0].regionName == boostEncode("WARSZAWA"));

	line = "   2293   1.Praskiego Pu�ku,                  --  WARSZAWA";
	ZAsection->processLine(boostEncode(line));
	REQUIRE(schedManager.stopGroups[1].id == 2293);
	REQUIRE(schedManager.stopGroups[1].name == boostEncode("1.Praskiego Pu�ku"));
	REQUIRE(schedManager.stopGroups[1].regionId == "--");
	REQUIRE(schedManager.stopGroups[1].regionName == boostEncode("WARSZAWA"));

	line = "   1192   3 Maja,                             LG  LEGIONOWO";
	ZAsection->processLine(boostEncode(line));
	REQUIRE(schedManager.stopGroups[2].id == 1192);
	REQUIRE(schedManager.stopGroups[2].name == boostEncode("3 Maja"));
	REQUIRE(schedManager.stopGroups[2].regionId == "LG");
	REQUIRE(schedManager.stopGroups[2].regionName == boostEncode("LEGIONOWO"));

	line = "   2145   Abrahama,                           --  WARSZAWA";
	ZAsection->processLine(boostEncode(line));
	REQUIRE(schedManager.stopGroups[3].id == 2145);
	REQUIRE(schedManager.stopGroups[3].name == boostEncode("Abrahama"));
	REQUIRE(schedManager.stopGroups[3].regionId == "--");
	REQUIRE(schedManager.stopGroups[3].regionName == boostEncode("WARSZAWA"));

	line = "   3344   Agatowa,                            JS  J�ZEFOS�AW";
	ZAsection->processLine(boostEncode(line));
	REQUIRE(schedManager.stopGroups[4].id == 3344);
	REQUIRE(schedManager.stopGroups[4].name == boostEncode("Agatowa"));
	REQUIRE(schedManager.stopGroups[4].regionId == "JS");
	REQUIRE(schedManager.stopGroups[4].regionName == boostEncode("J�ZEFOS�AW"));

	line = "   1951   Akacjowa,                           NM  NOWY DW�R MAZ.";
	ZAsection->processLine(boostEncode(line));
	REQUIRE(schedManager.stopGroups[5].id == 1951);
	REQUIRE(schedManager.stopGroups[5].name == boostEncode("Akacjowa"));
	REQUIRE(schedManager.stopGroups[5].regionId == "NM");
	REQUIRE(schedManager.stopGroups[5].regionName == boostEncode("NOWY DW�R MAZ."));

	line = "   7087   al.Jana Paw�a II,                   --  WARSZAWA";
	ZAsection->processLine(boostEncode(line));
	REQUIRE(schedManager.stopGroups[6].id == 7087);
	REQUIRE(schedManager.stopGroups[6].name == boostEncode("al.Jana Paw�a II"));
	REQUIRE(schedManager.stopGroups[6].regionId == "--");
	REQUIRE(schedManager.stopGroups[6].regionName == boostEncode("WARSZAWA"));

	line = "   1301   al.\"Solidarno�ci\",                  --  WARSZAWA";
	ZAsection->processLine(boostEncode(line));
	REQUIRE(schedManager.stopGroups[7].id == 1301);
	REQUIRE(schedManager.stopGroups[7].name == boostEncode("al.\"Solidarno�ci\""));
	REQUIRE(schedManager.stopGroups[7].regionId == "--");
	REQUIRE(schedManager.stopGroups[7].regionName == boostEncode("WARSZAWA"));

	line = "   1301   al.\"Solidarno�ci\",                  --  WARSZAWA";
	ZAsection->processLine(boostEncode(line));
	REQUIRE(schedManager.stopGroups[8].id == 1301);
	REQUIRE(schedManager.stopGroups[8].name == boostEncode("al.\"Solidarno�ci\""));
	REQUIRE(schedManager.stopGroups[8].regionId == "--");
	REQUIRE(schedManager.stopGroups[8].regionName == boostEncode("WARSZAWA"));

	line = "   2025   Alpejska-Instytut,                  --  WARSZAWA";
	ZAsection->processLine(boostEncode(line));
	REQUIRE(schedManager.stopGroups[9].id == 2025);
	REQUIRE(schedManager.stopGroups[9].name == boostEncode("Alpejska-Instytut"));
	REQUIRE(schedManager.stopGroups[9].regionId == "--");
	REQUIRE(schedManager.stopGroups[9].regionName == boostEncode("WARSZAWA"));

	line = "   4184   Badylarska,                         OO  OPACZ-KOLONIA";
	ZAsection->processLine(boostEncode(line));
	REQUIRE(schedManager.stopGroups[10].id == 4184);
	REQUIRE(schedManager.stopGroups[10].name == boostEncode("Badylarska"));
	REQUIRE(schedManager.stopGroups[10].regionId == "OO");
	REQUIRE(schedManager.stopGroups[10].regionName == boostEncode("OPACZ-KOLONIA"));

	line = "   1888   Beniamin�wka,                       W4  W�LKA RADZYMI�SKA";
	ZAsection->processLine(boostEncode(line));
	REQUIRE(schedManager.stopGroups[11].id == 1888);
	REQUIRE(schedManager.stopGroups[11].name == boostEncode("Beniamin�wka"));
	REQUIRE(schedManager.stopGroups[11].regionId == "W4");
	REQUIRE(schedManager.stopGroups[11].regionName == boostEncode("W�LKA RADZYMI�SKA"));

	line = "   4005   Bitwy Warszawskiej 1920 r.,         --  WARSZAWA";
	ZAsection->processLine(boostEncode(line));
	REQUIRE(schedManager.stopGroups[12].id == 4005);
	REQUIRE(schedManager.stopGroups[12].name == boostEncode("Bitwy Warszawskiej 1920 r."));
	REQUIRE(schedManager.stopGroups[12].regionId == "--");
	REQUIRE(schedManager.stopGroups[12].regionName == boostEncode("WARSZAWA"));

	line = "   5037   Muzeum Powstania Warszawskiego      --  WARSZAWA";
	ZAsection->processLine(boostEncode(line));
	REQUIRE(schedManager.stopGroups[13].id == 5037);
	REQUIRE(schedManager.stopGroups[13].name == boostEncode("Muzeum Powstania Warszawskiego"));
	REQUIRE(schedManager.stopGroups[13].regionId == "--");
	REQUIRE(schedManager.stopGroups[13].regionName == boostEncode("WARSZAWA"));


}

TEST_CASE("Sekcja PR", "[PR]")
{
	ScheduleManager schedManager;

	std::shared_ptr<PRSection> PRsection = std::make_shared<PRSection>(&schedManager);
	std::string line;

	line = "         100101   2      Ul./Pl.: Targowa,                          Kier.: al.Zieleniecka,                   Y= 52.248455     X= 21.044827     Pu=0";
	PRsection->processLine(boostEncode(line));

    REQUIRE(schedManager.stops.size() == 1);
	REQUIRE(schedManager.stops[0].id == 100101);
	REQUIRE(schedManager.stops[0].groupId == 1001);
	REQUIRE(schedManager.stops[0].idInGroup == "01");
	REQUIRE(schedManager.stops[0].street == boostEncode("Targowa"));
	REQUIRE(schedManager.stops[0].direction == boostEncode("al.Zieleniecka"));
	REQUIRE(schedManager.stops[0].lat == static_cast<float>(52.248455));
	REQUIRE(schedManager.stops[0].lon == static_cast<float>(21.044827));

	line = "         100102   3      Ul./Pl.: Targowa,                          Kier.: Z�bkowska,                        Y= 52.249078     X= 21.044443     Pu=0";
	PRsection->processLine(boostEncode(line));

    REQUIRE(schedManager.stops.size() == 2);
    REQUIRE(schedManager.stops[1].id == 100102);
	REQUIRE(schedManager.stops[1].groupId == 1001);
	REQUIRE(schedManager.stops[1].idInGroup == "02");
	REQUIRE(schedManager.stops[1].street == boostEncode("Targowa"));
	REQUIRE(schedManager.stops[1].direction == boostEncode("Z�bkowska"));
	REQUIRE(schedManager.stops[1].lat == static_cast<float>(52.249078));
	REQUIRE(schedManager.stops[1].lon == static_cast<float>(21.044443));

	line = "         100106   1      Ul./Pl.: Kijowska,                         Kier.: Dw.Wschodni (Kijowska),           Y= 52.250008     X= 21.043710     Pu=0";
	PRsection->processLine(boostEncode(line));

    REQUIRE(schedManager.stops.size() == 3);
    REQUIRE(schedManager.stops[2].id == 100106);
	REQUIRE(schedManager.stops[2].groupId == 1001);
	REQUIRE(schedManager.stops[2].idInGroup == "06");
	REQUIRE(schedManager.stops[2].street == boostEncode("Kijowska"));
	REQUIRE(schedManager.stops[2].direction == boostEncode("Dw.Wschodni (Kijowska)"));
	REQUIRE(schedManager.stops[2].lat == static_cast<float>(52.250008));
	REQUIRE(schedManager.stops[2].lon == static_cast<float>(21.043710));

	line = "         100304   4      Ul./Pl.: al.\"Solidarno�ci\",                Kier.: Szwedzka,                         Y= 52.255099     X= 21.036174     Pu=0";
	PRsection->processLine(boostEncode(line));

    REQUIRE(schedManager.stops.size() == 4);
    REQUIRE(schedManager.stops[3].id == 100304);
	REQUIRE(schedManager.stops[3].groupId == 1003);
	REQUIRE(schedManager.stops[3].idInGroup == "04");
	REQUIRE(schedManager.stops[3].street == boostEncode("al.\"Solidarno�ci\""));
	REQUIRE(schedManager.stops[3].direction == boostEncode("Szwedzka"));
	REQUIRE(schedManager.stops[3].lat == static_cast<float>(52.255099));
	REQUIRE(schedManager.stops[3].lon == static_cast<float>(21.036174));

	line = "         100402   1      Ul./Pl.: Jagiello�ska,                     Kier.: pl.Hallera,                       Y= 52.257011     X= 21.028103     Pu=0";
	PRsection->processLine(boostEncode(line));

    REQUIRE(schedManager.stops.size() == 5);
    REQUIRE(schedManager.stops[4].id == 100402);
	REQUIRE(schedManager.stops[4].groupId == 1004);
	REQUIRE(schedManager.stops[4].idInGroup == "02");
	REQUIRE(schedManager.stops[4].street == boostEncode("Jagiello�ska"));
	REQUIRE(schedManager.stops[4].direction == boostEncode("pl.Hallera"));
	REQUIRE(schedManager.stops[4].lat == static_cast<float>(52.257011));
	REQUIRE(schedManager.stops[4].lon == static_cast<float>(21.028103));

	line = "         131103   1      Ul./Pl.: Pi�sudskiego,                     Kier.: ******************************    Y= 52.397531     X= 20.934246     Pu=0";
	PRsection->processLine(boostEncode(line));

    REQUIRE(schedManager.stops.size() == 6);
    REQUIRE(schedManager.stops[5].id == 131103);
	REQUIRE(schedManager.stops[5].groupId == 1311);
	REQUIRE(schedManager.stops[5].idInGroup == "03");
	REQUIRE(schedManager.stops[5].street == boostEncode("Pi�sudskiego"));
	REQUIRE(schedManager.stops[5].direction == boostEncode("******************************"));
	REQUIRE(schedManager.stops[5].lat == static_cast<float>(52.397531));
	REQUIRE(schedManager.stops[5].lon == static_cast<float>(20.934246));

	line = "         503602   1      Ul./Pl.: Grzybowska,                       Kier.: Muzeum Powstania Warszawskiego    Y= 52.234436     X= 20.989269     Pu=5";
	PRsection->processLine(boostEncode(line));

    REQUIRE(schedManager.stops.size() == 7);
    REQUIRE(schedManager.stops[6].id == 503602);
	REQUIRE(schedManager.stops[6].groupId == 5036);
	REQUIRE(schedManager.stops[6].idInGroup == "02");
	REQUIRE(schedManager.stops[6].street == boostEncode("Grzybowska"));
	REQUIRE(schedManager.stops[6].direction == boostEncode("Muzeum Powstania Warszawskiego"));
	REQUIRE(schedManager.stops[6].lat == static_cast<float>(52.234436));
	REQUIRE(schedManager.stops[6].lon == static_cast<float>(20.989269));

	line = "         503458   1      Ul./Pl.: Powsta�c�w �l�skich,              Kier.: ******************************    Y=yyy.yyyyyyyy   X=xxx.xxxxxxxx   Pu=?";
	PRsection->processLine(boostEncode(line));

    REQUIRE(schedManager.stops.size() == 8);
    REQUIRE(schedManager.stops[7].id == 503458);
	REQUIRE(schedManager.stops[7].groupId == 5034);
	REQUIRE(schedManager.stops[7].idInGroup == "58");
	REQUIRE(schedManager.stops[7].street == boostEncode("Powsta�c�w �l�skich"));
	REQUIRE(schedManager.stops[7].direction == boostEncode("******************************"));
	REQUIRE(schedManager.stops[7].lat == static_cast<float>(0));
	REQUIRE(schedManager.stops[7].lon == static_cast<float>(0));


}


TEST_CASE("Sekcja WK", "[WK]")
{
	ScheduleManager schedManager{2020, 5, 30};

	std::shared_ptr<KDSection> KDsection = std::make_shared<KDSection>(&schedManager);
    KDsection->processLine("        2020-05-30  1");
	KDsection->processLine("        1   DP");

	std::shared_ptr<LLSection> LLsection = std::make_shared<LLSection>(&schedManager);
	std::string line;
	line = "   Linia:   1  - LINIA TRAMWAJOWA";
	LLsection->processLine(boostEncode(line));

	std::shared_ptr<WKSection> WKsection = std::make_shared<WKSection>(&schedManager);
	WKsection->setParent(LLsection);

	line = "         TD-3ANNO/DP/04.13  324004 DP  4.16  B";
	WKsection->processLine(line);
	REQUIRE(schedManager.departures.size() == 1);
	REQUIRE(schedManager.departures[0].courseId == schedManager.getScheduleDate() + "_1_TD-3ANNO/DP/04.13");
	REQUIRE(schedManager.departures[0].stopId == 324004);
	REQUIRE(schedManager.departures[0].departureHour == 4);
	REQUIRE(schedManager.departures[0].departureMinute == 16);

	line = "         TD-3ANNO/DP/04.13  400201 DP  4.38   ";
	WKsection->processLine(line);

    REQUIRE(schedManager.departures.size() == 2);
	REQUIRE(schedManager.departures[1].courseId == schedManager.getScheduleDate() + "_1_TD-3ANNO/DP/04.13");
	REQUIRE(schedManager.departures[1].stopId == 400201);
	REQUIRE(schedManager.departures[1].departureHour == 4);
	REQUIRE(schedManager.departures[1].departureMinute == 38);

	line = "         TD-3ANNO/DP/04.13  108703 DP  5.15  P";
	WKsection->processLine(line);


    REQUIRE(schedManager.departures.size() == 3);
	REQUIRE(schedManager.departures[2].courseId == schedManager.getScheduleDate() + "_1_TD-3ANNO/DP/04.13");
	REQUIRE(schedManager.departures[2].stopId == 108703);
	REQUIRE(schedManager.departures[2].departureHour == 5);
	REQUIRE(schedManager.departures[2].departureMinute == 15);

	line = "         TD-3BAN/DP/04.31_  400507 DP  4.57   ";
	WKsection->processLine(line);

    REQUIRE(schedManager.departures.size() == 4);
	REQUIRE(schedManager.departures[3].courseId == schedManager.getScheduleDate() + "_1_TD-3BAN/DP/04.31_");
	REQUIRE(schedManager.departures[3].stopId == 400507);
	REQUIRE(schedManager.departures[3].departureHour == 4);
	REQUIRE(schedManager.departures[3].departureMinute == 57);

	
}

