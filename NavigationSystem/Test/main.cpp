#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
#include<stdlib.h>
#include<iostream>
#include "CConnectToPOIDatabase.h"
#include "CConnectToWpDatabase.h"
#include "CCreateRoute.h"
#include "COperatorOverload.h"
#include "CCopyConstructor.h"
#include "CPrint.h"
#include "CClear.h"

using namespace CppUnit;
using namespace std;

int main()
{
	TextUi::TestRunner runner;

	runner.addTest( CConnectToPOIDatabase::suite() );
	runner.addTest( CConnectToWpDatabase::suite() );
	runner.addTest( CCreateRoute::suite() );
	runner.addTest( COperatorOverload::suite() );
	runner.addTest( CCopyConstructor::suite() );
	runner.addTest( CPrint::suite() );
	runner.addTest( CClear::suite() );
	runner.run();

	return 0;
}
