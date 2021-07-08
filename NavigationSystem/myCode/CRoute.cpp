#include "CRoute.h"
#include "CPOIDatabase.h"
#include<typeinfo>

using namespace std;
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CRoute.CPP
* Author          :	Sai Parimi
* Description     :	A route with multiple way points and POIs is created.
* 					Way points are user defined and POIs are extracted by linking
*					to the POI database and fetching the POI information
*					based on the user request. If available, a reference
*					to the POI is added to the local database. An evaluation
*			 		of the closest POI is done based on the user location.
****************************************************************************/

//Method Implementations

/*Adds a reference of the requested WP to the Route vector
 * @param : CWayPoint const &Wp, an object of class CWayPoint.
 * @return : Void.
 * */
void CRoute::AddWayPoint(WpKeyType NameWp)
{
	WpValueType *m_WPStore = NULL;
	if(m_pWpDatabase != NULL)
	{
		m_WPStore = m_pWpDatabase->GetPointerToWayPoint(NameWp);
		if(m_WPStore != NULL)
		{
			Route.push_back(m_WPStore);
		}
		else
		{
			cout << NameWp << " not available in waypoint database\n\n";
		}
	}
	else
	{
		cout << "No Way point database connected.\n\n";
	}
}

/*creates a reference to the POI database so that user requested POI can be retrieved from the pool
 * @param : CPOIDatabase *pPOIDB, an pointer to an object of class CPOIDatabase.
 * @return : Void.
 * */
void CRoute::ConnectToPOIDatabase(CPOIDatabase *pPOIDB)
{
	if(pPOIDB != NULL)//To ensure a NULL reference is not passed
	{
		m_pPoiDatabase = pPOIDB;
		cout << "POI Database connected." << endl;
	}
	else
	{
		cout << "No Database to connect to.\n" << endl;
	}
}

/*creates a reference to the waypoint database so that user requested WP can be retrieved from the pool
 * @param : CWpDatabase *pWpDB, an pointer to an object of class CWpDatabase.
 * @return : Void.
 * */
void CRoute::ConnectToWPDatabase(CWpDatabase *pWpDB)
{
	if(pWpDB != NULL)//To ensure a NULL reference is not passed
	{
		m_pWpDatabase = pWpDB;
		cout << "Waypoint Database connected." << endl;
	}
	else
	{
		cout << "No Database to connect to.\n" << endl;
	}
}

/*Checks if the user requested POI is available in the POIDatabase and if so,
 * adds a reference of that POI to local route after a specific WP "AfterWp"
 * @param : string NamePoi, Name of the POI that should be added to the route.
 * @return : Void.
 * */
void CRoute::AddPOI(POIKeyType NamePoi, string AfterWp)
{
	std::vector<WpValueType*>::reverse_iterator rit_route;
	bool NoWpFlag = true;
	WpValueType *m_POIStore = NULL;
	if((m_pPoiDatabase != NULL))//This check is to be done if we want to ensure WPDB was not disconnected, && (m_pWpDatabase != NULL))
	{
		m_POIStore = m_pPoiDatabase->GetPointerToPOI(NamePoi);
		if(m_POIStore != NULL)
		{
			for(rit_route = Route.rbegin(); rit_route != Route.rend(); ++rit_route)
			{
				if((AfterWp.compare((*rit_route)->GetName()) == 0) && (dynamic_cast<CPOI*>(*rit_route) == NULL))
				{
					Route.insert(rit_route.base(),m_POIStore);
					NoWpFlag = false;
					break;
				}
			}
		}
		else
		{
			cout << NamePoi << " not available in POI database\n\n";
		}
	}
	else
	{
		cout << "No valid database connected\n\n";
	}

	if(NoWpFlag && m_pPoiDatabase != NULL)
	{
		cout << "Couldn't find Waypoint " << AfterWp << " in route and hence, cannot insert POI " << NamePoi << endl << endl;
	}

}

/*Checks if the user requested Name is available in the POIDatabase or WPDatabase
 *and if so, adds a reference of that WP or POI to local route in the same order
 * @param : string Name, Name of the POI or waypoint that should be added to the route.
 * @return : Void.
 * */
CRoute& CRoute::operator+=(const WpKeyType Name)
{
	WpValueType *ObjectSearched = NULL;

	if(m_pWpDatabase != NULL && m_pPoiDatabase != NULL)
	{
		ObjectSearched = m_pWpDatabase->GetPointerToWayPoint(Name);
		if(ObjectSearched != NULL)
			Route.push_back(ObjectSearched);
		ObjectSearched = m_pPoiDatabase->GetPointerToPOI(Name);
		if(ObjectSearched != NULL)
			Route.push_back(ObjectSearched);
		if((m_pWpDatabase->GetPointerToWayPoint(Name) == NULL) && (m_pPoiDatabase->GetPointerToPOI(Name) == NULL))
		{
			cout << Name << " not available in either of the Databases\n\n";
		}
	}
	else
	{
		cout << "Database connect issues\n\n";
	}
	return *this;
}

/*After replacing the database using persistence, the old route will no longer be valid
 * This method provides means to clear out the existing route so that a new route
 * with the updated database can be created.
 *@param: Void.
 *@param: Void.
 * */
void CRoute::ClearRoute()
{
	Route.clear();
	cout << "Route Cleared." << endl;
}

/*Print the complete Route information i.e., Waypoints and POIs enroute
 *@param: Void.
 *@param: Void.
 * */
void CRoute::Print()
{
	/*Finding: Here, without dynamic cast, when we try to print out the route info,
	 *even the POI overloading would be directed to CWaypoint print.
	 *To avoid this, we use dynamic casting so that POI print is directed to CPOI
	 */
	POIValueType *POIObject;
	std::vector<WpValueType*>::iterator it_route;

	cout << "Route Info :" << endl << endl;
	for(it_route = Route.begin(); it_route != Route.end(); ++it_route)
	{
		POIObject = dynamic_cast<CPOI*>(*it_route);

		if(POIObject == NULL)
		{
			cout << "WayPoint\n====================================" << endl;
			cout << *(*it_route);
			cout << endl;
		}
		else
		{
			cout << "Point Of Interest\n====================================" << endl;
			cout << *POIObject;
			cout << endl;
		}
	}
}

/*Append the new route information to the current route
 *@param: CRoute& Route2, reference to the new route
 *@param: CRoute, object of the Croute class holding the updated route
 * */
CRoute& CRoute::operator+(CRoute& Route2)
{
	std::vector<WpValueType*>::iterator it_route;
	if((this->m_pPoiDatabase == Route2.m_pPoiDatabase) && (this->m_pWpDatabase == Route2.m_pWpDatabase))
	{
		for(it_route = Route2.Route.begin(); it_route != Route2.Route.end(); ++it_route)
		{
			this->Route.push_back(*it_route);
		}
	}
	else
	{
		cout << "Cannot add the routes as they are connected to different databases\n" << endl;
	}
	return *this;
}

/*un-allocates the memory that was allocated to various pointers*/
CRoute::~CRoute()
{

}
/*Default class constructor initializing the Database references to NULL*/
CRoute::CRoute()
{
	m_pPoiDatabase = 0;
	m_pWpDatabase = 0;
}
/*Copy constructor which performs deep copy of Route and Databases*/
CRoute::CRoute(CRoute& Origin)
{
	Route = Origin.Route;
	m_pWpDatabase = Origin.m_pWpDatabase;
	m_pPoiDatabase = Origin.m_pPoiDatabase;
	cout << "Copy Constructor called\n==================================================\n" << endl;
}

/*Copies the contents of RHS object to LHS
 *@param: CRoute& Robject, Source object
 *@param: CRoute&, object of the Croute class holding the updated route
 * */
CRoute& CRoute::operator =(CRoute& Robject)
{
	Route = Robject.Route;
	m_pWpDatabase = Robject.m_pWpDatabase;
	m_pPoiDatabase = Robject.m_pPoiDatabase;
	cout << "Assignment Operator called\n==================================================\n" << endl;
	return *this;
}

/* Return the vector storing the map information
 * @param: Void
 * @return: Vector<Cwaypoint*>, vector of waypoints and POIs
 */
const std::vector<const WpValueType*> CRoute::getRoute()
{
	vector<const WpValueType*> ConstVector(Route.begin(),Route.end());
	return ConstVector;
}
/*Unused in this exercise*/
/*Checks the current position of the user with the help of GPS sensor and directs to the nearest POI enroute
 *@param: const CWayPoint &wp,CPOI &POI, an object of WayPoint corrsponding to the users current position and an empty POI
 *The empty POI, since is not const, can be used to store the POI information that is closest to surrent user coorsinates
 *@return: distance(type double).
 * */
/*
double CRoute::GetDistanceNextPOI(const CWayPoint &wp,CPOI &POI)
{
	double ReturnedDistances;
	double ShortestDistance = 32767.0; //Setting to a random default distance so that the first evaluated distance will be less than this number;

	for(unsigned int i = 0; i < m_NextPoi; i++)
	{
		POI = *(m_pPoi[i]);
		ReturnedDistances = POI.CalculateDistance(wp);

		if(ReturnedDistances < ShortestDistance)
		{
			ShortestDistance = ReturnedDistances;
		}
		else
		{
			POI = *(m_pPoi[i-1]);//Retain the Previous POI as the current POI is not closer than the previous.
		}

	}

	return ShortestDistance;
}
*/
