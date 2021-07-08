#include "CNavigationSystem.h"

using namespace std;

#define ReadMode 0 //0: Merge; 1: Replace

/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CNavigationSystem.CPP
* Author          :	Sai Parimi
* Description     :	This class links 3 different classes. CPOIDatabase creates
*					a pool of POIs which later acts as a reference to CRoute
*					class to add POIs to the user chosen route which is an
*					array of waypoints. Croute also uses the CGPSSensor class
*					to position the user and evaluate the distance to the
*					next available nearest POI.
****************************************************************************/
CRoute NewRoute;
//Method Implementations

/*This method activates the entire navigation system and the subsequent processes to follow
 *@param : Void
 *@return : Void
 **/
void CNavigationSystem::Run()
{
	/*Route Operations*/
	//Start
	TestCase1_CreateDB();
/*
	TestCase2_AddRoute();

	TestCase3_PrintRoute();

	TestCase4_OverloadedRoute();

	TestCase3_PrintRoute();

	TestCase5_AddRoutes();

	CRoute CopyConstructor = m_Route;

	CRoute Assignment1;

	 Assignment1 = m_Route;

	 //Addition of 2 routes which are connected to different databases
	 CRoute Dummyroute,Voidroute;

	 Voidroute = Dummyroute + m_Route;

	//End

	/*Persistance Operations*/
	 //begin
/*	CCSV DataObject;

	TestCase6_PersistanceWrite(DataObject);

	TestCase7_PersistanceRead(DataObject);*/

	/*To be performed only after REPLACE DB occurred since the old route will not be compatible to the new DB
	m_Route.ClearRoute();
	*/
	//end
	/*JSON Reader*/
	//Begin
	CJSON JSONObject;

	TestCase8_JSONRead(JSONObject);

	TestCase9_JSONWrite(JSONObject);
	//End

}

/*This method allow the user to enter the route i.e., define multiple waypoints and POIs and store them in an array (Vector)
 *@param : CRoute& RouteCheck, the member into whom the route is to be entered
 *@return : Void
 */
void CNavigationSystem::EnterRoute(CRoute& RouteCheck)
{
	RouteCheck.AddWayPoint("Darmstadt");
	RouteCheck.AddWayPoint("Berlin");
	RouteCheck.AddWayPoint("Darmstadt");
	RouteCheck.AddWayPoint("Tokyo");
	RouteCheck.AddWayPoint("LuisenPlatz");
	RouteCheck.AddPOI("KFC","Darmstadt");
	RouteCheck.AddPOI("Museum","LuisenPlatz");
	RouteCheck.AddPOI("Museum","Hello");
}

/*Prints the entire route designed by the user i.e., display all the waypoints and POIs chosen for the route
 *@param : CRoute& PrintRoute, object whose data is to printed
 *@return : Void
 * */
void CNavigationSystem::PrintRoute(CRoute& PrintRoute)
{
	PrintRoute.Print();
}

/*Default Constructor for Class*/
CNavigationSystem::CNavigationSystem()
{

}

/*Test case execution. Function definitions of all the defined test cases*/
//Functions Begin


/*Connects to the POI Database and creates a route by defining waypoints and POIs
 *@param : Void
 *@return : Void
 */
void CNavigationSystem::TestCase2_AddRoute()
{
	m_Route.ConnectToPOIDatabase(&m_PoiDatabase);
	m_Route.ConnectToWPDatabase(&m_WpDatabase);
	EnterRoute(m_Route);
	NewRoute.ConnectToPOIDatabase(&m_PoiDatabase);
	NewRoute.ConnectToWPDatabase(&m_WpDatabase);
	EnterRoute(NewRoute);

}

/*Prints the route i.e., the route's waypoint and POI information
 *@param : Void
 *@return : Void
 */
void CNavigationSystem::TestCase3_PrintRoute()
{
	PrintRoute(m_Route);
}

/*Creates the waypoint and poi DBs
 *@param : Void
 *@return : Void
*/
void CNavigationSystem::TestCase1_CreateDB()
{
	/*POI DB Creation*/
	CPOI POI1(UNIVERSITY,"H-DA","Good University",10.0,20.0);
	m_PoiDatabase.AddPOI(POI1,POI1.GetName());
	CPOI POI2(GASSTATION,"Shell","Good Fuel Quality",25.0,35.0);
	m_PoiDatabase.AddPOI(POI2,POI2.GetName());
	CPOI POI3(TOURISTIC,"Frankenstein Castle","Good Scenery",-30.0,-40.0);
	m_PoiDatabase.AddPOI(POI3,POI3.GetName());
	CPOI POI5(RESTAURANT,"KFC","Reasonable Price",70.0,80.0);
	m_PoiDatabase.AddPOI(POI5,POI5.GetName());
	CPOI POI6(TOURISTIC,"Museum","Historic Know-How",-75.0,-85.0);
	m_PoiDatabase.AddPOI(POI6,POI6.GetName());
	CPOI POI7(TOURISTIC,"LuisenPlatz","Shopping",63.50,39.75);
	m_PoiDatabase.AddPOI(POI7,POI7.GetName());

	/*WP DB Creation*/
	CWayPoint WP1("Tokyo",-30.0,-40.0,WAYPOINT);
	m_WpDatabase.AddWayPoint(WP1,WP1.GetName());
	CWayPoint WP2("Munich",70.0,80.0,WAYPOINT);
	m_WpDatabase.AddWayPoint(WP2,WP2.GetName());
	CWayPoint WP3("Stuttgart",-75.0,-85.0,WAYPOINT);
	m_WpDatabase.AddWayPoint(WP3,WP3.GetName());
	CWayPoint WP4("LuisenPlatz",63.50,39.75,WAYPOINT);
	m_WpDatabase.AddWayPoint(WP4,WP4.GetName());
}

/*Adds 2 routes and returns the resultant concatenated route
 *@param : Void
 *@return : Void
*/

void CNavigationSystem::TestCase5_AddRoutes()
{
	CRoute UpdatedRoute;
	UpdatedRoute = m_Route + NewRoute;
	cout << "Appended Route(+ overloading)\n=========================================\n" << endl;
	UpdatedRoute.Print();
}

/*Adds POI and Waypoints to the route with the overloaded += operator
 *@param : Void
 *@return : Void
*/
void CNavigationSystem::TestCase4_OverloadedRoute()
{
	m_Route+="Munich";
	m_Route+="Frankenstein Castle";
	m_Route+="Hello";//Something that is not in databases
	cout << "Overloaded with +=\n=====================================\n" << endl;
}

/*Writes the current DB information into the CSV files
 *@param : Object of CCSV class
 *@return : Void
*/
void CNavigationSystem::TestCase6_PersistanceWrite(CCSV Object)
{
	Object.setMediaName("WriteBefore");
	Object.writeData(m_WpDatabase,m_PoiDatabase);
}

/*Writes the CSV file information into the DBs
 *@param : Object of CCSV class
 *@return : Void
*/
void CNavigationSystem::TestCase7_PersistanceRead(CCSV Object)
{
	CCSV::MergeMode MergeOption;
	MergeOption = (ReadMode == 0) ? CCSV::MERGE : CCSV::REPLACE;
	Object.setMediaName("Exercise2");
	Object.readData(m_WpDatabase,m_PoiDatabase,MergeOption);
	Object.setMediaName("WriteAfter");
	Object.writeData(m_WpDatabase,m_PoiDatabase);
}

void CNavigationSystem::TestCase8_JSONRead(CJSON Object)
{
	bool Status;
	Object.setMediaName("JSONInput");
	Status = Object.readData(m_WpDatabase,m_PoiDatabase,
			ReadMode == 0 ? CJSON::MERGE : CJSON::REPLACE);
	if(Status)
	{
		cout << "Read operation successful" << endl;
	}
	else
	{
		cout << "Read operation failed" << endl;
	}
}

void CNavigationSystem::TestCase9_JSONWrite(CJSON Object)
{
	bool Status;
	Object.setMediaName("JSON");
	Status = Object.writeData(m_WpDatabase,m_PoiDatabase);
	if(Status)
	{
		cout << "Write operation successful" << endl;
	}
	else
	{
		cout << "Write operation failed" << endl;
	}
}
//Functions End
