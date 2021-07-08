#ifndef CCONNECTTOWPDATABASE_H_
#define CCONNECTTOWPDATABASE_H_

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
class CConnectToWpDatabase: public CppUnit::TestFixture {
public:

	void ConnectToWpDB() {
		CRoute* route = new CRoute;
		CWpDatabase *WPDB = new CWpDatabase;
		CPOIDatabase *POIDB = new CPOIDatabase;
		CWayPoint WP("LuisenPlatz",50.5,65.75,WAYPOINT);
		CWayPoint WP2("Munich",70.65,90,WAYPOINT);
		WPDB->AddWayPoint(WP,WP.GetName());
		WPDB->AddWayPoint(WP2,WP2.GetName());
		route->ConnectToWPDatabase(WPDB);
		route->ConnectToPOIDatabase(POIDB);
		*route += "LuisenPlatz";
		route->AddWayPoint("Munich");
		route->AddWayPoint("Munichen");
		CPPUNIT_ASSERT_EQUAL(2,(int)route->getRoute().size());
		delete WPDB;
		delete route;
		delete POIDB;
	}

	void DisconnectToWpDB() {
		CRoute* route = new CRoute;
		CWpDatabase *WPDB = new CWpDatabase;
		CPOIDatabase *POIDB = new CPOIDatabase;
		CWayPoint WP("LuisenPlatz",50.5,65.75,WAYPOINT);
		WPDB->AddWayPoint(WP,WP.GetName());
		route->ConnectToWPDatabase(NULL);
		route->ConnectToPOIDatabase(POIDB);
		*route += "LuisenPlatz";
		route->AddWayPoint("LuisenPlatz");
		CPPUNIT_ASSERT_EQUAL(0,(int)route->getRoute().size());
		delete WPDB;
		delete route;
		delete POIDB;
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Connect to WPDB test");

		suite->addTest(new CppUnit::TestCaller<CConnectToWpDatabase>
				 ("Connect to WP DB", &CConnectToWpDatabase::ConnectToWpDB));

		suite->addTest(new CppUnit::TestCaller<CConnectToWpDatabase>
				 ("Disconnect to WP DB", &CConnectToWpDatabase::DisconnectToWpDB));

		return suite;
	}
};

#endif
