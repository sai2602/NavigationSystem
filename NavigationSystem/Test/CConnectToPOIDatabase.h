#ifndef CCONNECTTOPOIDATABASE_H_
#define CCONNECTTOPOIDATABASE_H_

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
class CConnectToPOIDatabase: public CppUnit::TestFixture {
public:

	void ConnectToPoiDB() {
		CRoute* route = new CRoute;
		CPOIDatabase *POIDB = new CPOIDatabase;
		CPOI POI(UNIVERSITY,"H-DA","Good University",20.0,30.0);
		POIDB->AddPOI(POI,POI.GetName());
		route->ConnectToPOIDatabase(POIDB);
		route->AddPOI("H-DA","ABC");
		CPPUNIT_ASSERT(0 == route->getRoute().size());
		delete POIDB;
		delete route;
	}

	void DisconnectToPoiDB() {
		CRoute* route = new CRoute;
		CPOIDatabase *POIDB = new CPOIDatabase;
		CPOI POI(UNIVERSITY,"H-DA","Good University",20.0,30.0);
		POIDB->AddPOI(POI,POI.GetName());
		route->ConnectToPOIDatabase(NULL);
		*route += "H-DA";
		CPPUNIT_ASSERT(0 == route->getRoute().size());
		route->AddPOI("H-DA","ABC");
		delete POIDB;
		delete route;
	}

	static CppUnit::TestSuite* suite() {
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Connect to POIDB test");

		suite->addTest(new CppUnit::TestCaller<CConnectToPOIDatabase>
				 ("Connect to POI DB", &CConnectToPOIDatabase::ConnectToPoiDB));

		suite->addTest(new CppUnit::TestCaller<CConnectToPOIDatabase>
				 ("Disconnect to POI DB", &CConnectToPOIDatabase::DisconnectToPoiDB));

		return suite;
	}
};

#endif
