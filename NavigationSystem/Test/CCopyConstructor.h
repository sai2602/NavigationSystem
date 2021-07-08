#ifndef CCOPYCONSTRUCTOR_H_
#define CCOPYCONSTRUCTOR_H_

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
class CCopyConstructor: public CppUnit::TestFixture {
public:

	void CopyConstructor() {
		CWpDatabase *WpDB = new CWpDatabase;
		CPOIDatabase *PoiDB = new CPOIDatabase;
		CRoute route;
		CWayPoint WP1("Berliner Allee",10,20,WAYPOINT);
		CWayPoint WP2("Luisenplatz",15,25,WAYPOINT);
		CPOI POI1(RESTAURANT,"KFC","Good Food",18,26);
		CPOI POI2(TOURISTIC,"Museum","Good Know-how",-15,-63);
		WpDB->AddWayPoint(WP1,WP1.GetName());
		WpDB->AddWayPoint(WP2,WP2.GetName());
		PoiDB->AddPOI(POI1,POI1.GetName());
		PoiDB->AddPOI(POI2,POI2.GetName());

		route.ConnectToWPDatabase(WpDB);
		route.ConnectToPOIDatabase(PoiDB);
		route += "Berliner Allee";
		route += "KFC";
		CRoute route2(route);
		CPPUNIT_ASSERT_EQUAL(2,(int)route2.getRoute().size());
		delete WpDB;
		delete PoiDB;
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Copy Constructor");

		suite->addTest(new CppUnit::TestCaller<CCopyConstructor>
				 ("Case1:", &CCopyConstructor::CopyConstructor));
		return suite;
	}
};

#endif
