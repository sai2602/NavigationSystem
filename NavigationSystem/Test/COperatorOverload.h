#ifndef COPERATOROVERLOAD_H_
#define COPERATOROVERLOAD_H_

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
class COperatorOverload: public CppUnit::TestFixture {
public:

	void PlusEqualWithoutDB() {
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

		route->ConnectToWPDatabase(NULL);
		route->ConnectToPOIDatabase(NULL);
		*route += "Berliner Allee";
		*route += "KFC";
		CPPUNIT_ASSERT(0 == (int)route->getRoute().size());
		delete WpDB;
		delete PoiDB;
		delete route;
	}

	void PlusEqualWithDBandWP() {

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
		*route += "Berliner Allee";
		*route += "ABC";
		CPPUNIT_ASSERT(1 == (int)route->getRoute().size());
		delete WpDB;
		delete PoiDB;
		delete route;
	}

	void PlusEqualWithDBandPOI() {

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
		*route += "Berlinerallee";
		*route += "KFC";
		CPPUNIT_ASSERT(1 == (int)route->getRoute().size());
		delete WpDB;
		delete PoiDB;
		delete route;
	}

	void PlusEqualWithDBandNoObjects() {

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
		*route += "Berlinerallee";
		*route += "KFC2";
		CPPUNIT_ASSERT(0 == (int)route->getRoute().size());
		delete WpDB;
		delete PoiDB;
		delete route;
	}

	void EqualOverload(){
		CWpDatabase *WpDB = new CWpDatabase;
		CPOIDatabase *PoiDB = new CPOIDatabase;
		CRoute *route = new CRoute;
		CRoute *route2 = new CRoute;
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
		*route += "Berliner Allee";
		*route += "KFC";
		*route2 = *route;
		CPPUNIT_ASSERT(2 == (int)route2->getRoute().size());
		delete WpDB;
		delete PoiDB;
		delete route;
		delete route2;
	}

	void PlusWithSameDB(){
		CWpDatabase *WpDB = new CWpDatabase;
		CPOIDatabase *PoiDB = new CPOIDatabase;
		CRoute *route = new CRoute;
		CRoute *route2 = new CRoute;
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
		route2->ConnectToWPDatabase(WpDB);
		route2->ConnectToPOIDatabase(PoiDB);
		*route += "Berliner Allee";
		*route += "KFC";
		*route2 += "KFC";
		*route2 + *route;
		CPPUNIT_ASSERT(3 == (int)route2->getRoute().size());
		delete WpDB;
		delete PoiDB;
		delete route;
		delete route2;

	}

	void PlusWithDifferentDB(){
		CWpDatabase *WpDB = new CWpDatabase;
		CPOIDatabase *PoiDB = new CPOIDatabase;
		CRoute *route = new CRoute;
		CRoute *route2 = new CRoute;
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
		route2->ConnectToWPDatabase(WpDB);
		route2->ConnectToPOIDatabase(NULL);
		*route += "Berliner Allee";
		*route += "KFC";
		*route2 += "Berliner Allee";
		*route2 + *route;
		CPPUNIT_ASSERT(0 == (int)route2->getRoute().size());
		delete WpDB;
		delete PoiDB;
		delete route;
		delete route2;


	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Overload Testing");

		suite->addTest(new CppUnit::TestCaller<COperatorOverload>
				 ("Case1:", &COperatorOverload::PlusEqualWithoutDB));

		suite->addTest(new CppUnit::TestCaller<COperatorOverload>
				 ("Case2:", &COperatorOverload::PlusEqualWithDBandWP));

		suite->addTest(new CppUnit::TestCaller<COperatorOverload>
				 ("Case3:", &COperatorOverload::PlusEqualWithDBandPOI));

		suite->addTest(new CppUnit::TestCaller<COperatorOverload>
				 ("Case4:", &COperatorOverload::PlusEqualWithDBandNoObjects));

		suite->addTest(new CppUnit::TestCaller<COperatorOverload>
				 ("Case5:", &COperatorOverload::EqualOverload));

		suite->addTest(new CppUnit::TestCaller<COperatorOverload>
				 ("Case6:", &COperatorOverload::PlusWithSameDB));

		suite->addTest(new CppUnit::TestCaller<COperatorOverload>
				 ("Case7:", &COperatorOverload::PlusWithDifferentDB));

		return suite;
	}
};

#endif
