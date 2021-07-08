/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CNavigationSystem.H
* Author          :	Sai Parimi
* Description     :	This class links 3 different classes i.e., CGPSSensor,
*					CRoute and CPOIDatabase. These help the user create a
*					route and evaluate POI distances.
****************************************************************************/
#include<string>
#include<iostream>
#include <stdlib.h>
#include "CGPSSensor.h"
#include "CRoute.h"
#include "CPOIDatabase.h"
#include "CWpDatabase.h"
#include "CCSV.h"
#include "CJSON.h"



#ifndef CNAVIGATIONSYSTEM_H
#define CNAVIGATIONSYSTEM_H


class CNavigationSystem {
private:

CGPSSensor m_GPSSensor;
CRoute m_Route;
CPOIDatabase m_PoiDatabase;
CWpDatabase m_WpDatabase;

//void PrintDistanceCurPosNextPoi();

void EnterRoute(CRoute& RouteCheck);

void PrintRoute(CRoute& PrintRoute);


public:

	void Run();

	CNavigationSystem();

	/*For Test Case Purposes only*/
	void TestCase1_CreateDB();

	void TestCase2_AddRoute();

	void TestCase3_PrintRoute();

	void TestCase4_OverloadedRoute();

	void TestCase5_AddRoutes();

	void TestCase6_PersistanceWrite(CCSV Object);

	void TestCase7_PersistanceRead(CCSV Object);

	void TestCase8_JSONRead(CJSON Object);

	void TestCase9_JSONWrite(CJSON Object);

};
/********************
**  CLASS END
*********************/
#endif /* CNAVIGATIONSYSTEM_H */


