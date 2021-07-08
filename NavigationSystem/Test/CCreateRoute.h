#ifndef CCREATEROUTE_H_
#define CCREATEROUTE_H_

#include <string>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestCase.h>

#include "../myCode/CRoute.h"

/**
 * This class implements several test cases related to connecting to
 * available databases. Each test case is implemented
 * as a method testXXX. The static method suite() returns a TestSuite
 * in which all tests are registered.
 */
class CCreateRoute: public CppUnit::TestFixture {

public:

	void AddRouteWithoutDB() {

		CWpDatabase *WpDB = new CWpDatabase;
		CPOIDatabase *PoiDB = new CPOIDatabase;
		CRoute *route = new CRoute;
		CWayPoint WP1("Berliner Allee",10,20,WAYPOINT);
		CWayPoint WP2("Luisenplatz",15,25,WAYPOINT);
		CPOI POI1(RESTAURANT,"KFC","Good Food",18,26);
		CPOI POI2(TOURISTIC,"Museum","Good Know-how",-15,-63);
		WpDB->AddWayPoint(WP1,WP1.GetName());
		WpDB->AddWayPoint(WP2,WP2.GetName());
		PoiDB->AddPOI(POI1,POI1.GetName());
		PoiDB->AddPOI(POI2,POI2.GetName());

		route->ConnectToWPDatabase(WpDB);
		route->ConnectToPOIDatabase(NULL);
		route->AddWayPoint("LuisenPlatz");
		route->AddPOI("KFC","LuisenPlatz");
		CPPUNIT_ASSERT(0 == (int)route->getRoute().size());
		delete WpDB;
				delete PoiDB;
				delete route;
	}

	void AddRouteWithDB() {

		CWpDatabase *WpDB = new CWpDatabase;
		CPOIDatabase *PoiDB = new CPOIDatabase;
		CRoute *route = new CRoute;
		CWayPoint WP1("Berliner Allee",10,20,WAYPOINT);
		CWayPoint WP2("Luisenplatz",15,25,WAYPOINT);
		CPOI POI1(RESTAURANT,"KFC","Good Food",18,26);
		CPOI POI2(TOURISTIC,"Museum","Good Know-how",-15,-63);
		WpDB->AddWayPoint(WP1,WP1.GetName());
		WpDB->AddWayPoint(WP2,WP2.GetName());
		PoiDB->AddPOI(POI1,POI1.GetName());
		PoiDB->AddPOI(POI2,POI2.GetName());

		route->ConnectToWPDatabase(WpDB);
		route->ConnectToPOIDatabase(PoiDB);
		route->AddWayPoint("Luisenplatz");
		route->AddPOI("KFC","Luisenplatz");
		CPPUNIT_ASSERT_EQUAL(2,(int)route->getRoute().size());
		delete WpDB;
				delete PoiDB;
				delete route;
	}

	void AddRouteWithNoWPFromDB() {

		CWpDatabase *WpDB = new CWpDatabase;
		CPOIDatabase *PoiDB = new CPOIDatabase;
		CRoute *route = new CRoute;
		CWayPoint WP1("Berliner Allee",10,20,WAYPOINT);
		CWayPoint WP2("Luisenplatz",15,25,WAYPOINT);
		CPOI POI1(RESTAURANT,"KFC","Good Food",18,26);
		CPOI POI2(TOURISTIC,"Museum","Good Know-how",-15,-63);
		WpDB->AddWayPoint(WP1,WP1.GetName());
		WpDB->AddWayPoint(WP2,WP2.GetName());
		PoiDB->AddPOI(POI1,POI1.GetName());
		PoiDB->AddPOI(POI2,POI2.GetName());

		route->ConnectToWPDatabase(WpDB);
		route->ConnectToPOIDatabase(PoiDB);
		route->AddWayPoint("Munich");
		route->AddPOI("KFC","Luisenplatz");
		CPPUNIT_ASSERT_EQUAL(0,(int)route->getRoute().size());
		delete WpDB;
				delete PoiDB;
				delete route;
	}

	void AddRouteWithNoPOIFromDB() {

		CWpDatabase *WpDB = new CWpDatabase;
		CPOIDatabase *PoiDB = new CPOIDatabase;
		CRoute *route = new CRoute;
		CWayPoint WP1("Berliner Allee",10,20,WAYPOINT);
		CWayPoint WP2("Luisenplatz",15,25,WAYPOINT);
		CPOI POI1(RESTAURANT,"KFC","Good Food",18,26);
		CPOI POI2(TOURISTIC,"Museum","Good Know-how",-15,-63);
		WpDB->AddWayPoint(WP1,WP1.GetName());
		WpDB->AddWayPoint(WP2,WP2.GetName());
		PoiDB->AddPOI(POI1,POI1.GetName());
		PoiDB->AddPOI(POI2,POI2.GetName());

		route->ConnectToWPDatabase(WpDB);
		route->ConnectToPOIDatabase(PoiDB);
		route->AddWayPoint("Luisenplatz");
		route->AddPOI("ABC","Luisenplatz");
		CPPUNIT_ASSERT_EQUAL(1,(int)route->getRoute().size());
		delete WpDB;
				delete PoiDB;
				delete route;
	}

	void AddRouteWithPOIandNoNextWP() {

		CWpDatabase *WpDB = new CWpDatabase;
		CPOIDatabase *PoiDB = new CPOIDatabase;
		CRoute *route = new CRoute;
		CWayPoint WP1("Berliner Allee",10,20,WAYPOINT);
		CWayPoint WP2("Luisenplatz",15,25,WAYPOINT);
		CPOI POI1(RESTAURANT,"KFC","Good Food",18,26);
		CPOI POI2(TOURISTIC,"Museum","Good Know-how",-15,-63);
		WpDB->AddWayPoint(WP1,WP1.GetName());
		WpDB->AddWayPoint(WP2,WP2.GetName());
		PoiDB->AddPOI(POI1,POI1.GetName());
		PoiDB->AddPOI(POI2,POI2.GetName());

		route->ConnectToWPDatabase(WpDB);
		route->ConnectToPOIDatabase(PoiDB);
		route->AddWayPoint("LuisenPlatz");
		route->AddPOI("KFC","ABC");
		CPPUNIT_ASSERT_EQUAL(0,(int)route->getRoute().size());
		delete WpDB;
				delete PoiDB;
				delete route;
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Route Creation");

		suite->addTest(new CppUnit::TestCaller<CCreateRoute>
				 ("Case1:", &CCreateRoute::AddRouteWithoutDB));

		suite->addTest(new CppUnit::TestCaller<CCreateRoute>
				 ("Case2:", &CCreateRoute::AddRouteWithDB));

		suite->addTest(new CppUnit::TestCaller<CCreateRoute>
				 ("Case3:", &CCreateRoute::AddRouteWithNoWPFromDB));

		suite->addTest(new CppUnit::TestCaller<CCreateRoute>
				 ("Case4:", &CCreateRoute::AddRouteWithNoPOIFromDB));

		suite->addTest(new CppUnit::TestCaller<CCreateRoute>
				 ("Case5:", &CCreateRoute::AddRouteWithPOIandNoNextWP));

		return suite;
	}
};

#endif
