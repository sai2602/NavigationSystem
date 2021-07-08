#ifndef CCLEAR_H_
#define CCLEAR_H_

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
class CClear: public CppUnit::TestFixture {
public:

	void ClearRoute() {
		CRoute* route = new CRoute;
		CWpDatabase *WPDB = new CWpDatabase;
		CPOIDatabase *POIDB = new CPOIDatabase;
		CWayPoint WP("LuisenPlatz",50.5,65.75,WAYPOINT);
		CWayPoint WP2("Munich",70.65,90,WAYPOINT);
		CPOI POI(UNIVERSITY,"H-DA","Good University",27.5,38.75);
		WPDB->AddWayPoint(WP,WP.GetName());
		WPDB->AddWayPoint(WP2,WP2.GetName());
		POIDB->AddPOI(POI,POI.GetName());
		route->ConnectToWPDatabase(WPDB);
		route->ConnectToPOIDatabase(POIDB);
		*route += "LuisenPlatz";
		route->AddWayPoint("Munich");
		route->AddPOI("H-DA","Munich");
		route->AddWayPoint("Munichen");
		route->ClearRoute();
		CPPUNIT_ASSERT_EQUAL(0,(int)route->getRoute().size());
		delete WPDB;
		delete route;
		delete POIDB;
	}


	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Clear Route Test");

		suite->addTest(new CppUnit::TestCaller<CClear>
				 ("Clear Route", &CClear::ClearRoute));
		return suite;
	}
};

#endif
