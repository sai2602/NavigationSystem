#include "CWpDatabase.h"


using namespace std;
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOIDatabase.CPP
* Author          :	Sai Parimi
* Description     :	This Class Creates a database which is a pool of all the
*					WP's defined by the user. Based on the route created,
*					the user can choose some or all of the WP's available
*					in the pool and add it to the defined route.
****************************************************************************/



//Method Implementations

/*Adds the WP information to the database, in this case MapOfWPs map
 *@param: CWayPoint const& WP, const reference to the CWayPoint object
 *@return: Void.
 */
void CWpDatabase::AddWayPoint(WpValueType const& WP, WpKeyType const& Key)
{
	if(!(AddLocationToMap(WP,Key)))
	{
		cout << "The WayPoint with key: " << Key << " already exists in the database." << endl << endl;
	}
}

/*default class constructor
 *@param: Void
 */
CWpDatabase::CWpDatabase()
{
}

/*Name(the dummy parameter in the function call) is the name of the WP that the user has requested to add EnRoute
 * This function now parses through all the objects available in the database (stored in the MapOfWPs map) and when
 * there is a hit while parsing, the address of the object is passed to the CRoute class. Passing the address of the
 * object instead of the entire object is useful as we are not creating a copy of the object in the Calling function.
 * Instead, we are only referring to the address where the POI is and using it when needed. This helps save memory.
 * @param: WP name which should be searched for in the database(string type)
 * @return: a pointer to the object whose name attribute matches to the requested name.
 * */
WpValueType* CWpDatabase::GetPointerToWayPoint(WpKeyType Name)
{
	return(GetPointerToLocation(Name));
}

/*Returns the map in which all the WPs are stored
 *@param: Void
 *@return: Map which has all the WPs in it.
 */
std::map<WpKeyType, WpValueType> CWpDatabase::GetWPMap() const
{
	return GetDBMap();
}

/*Clears the map in which all the WPs are stored
 *@param: Void
 *@return: bool value to signify clear status.
 */
bool CWpDatabase::ClearWPMap()
{
	ClearMap();
	return (MapOfLocations.size() == 0);
}

/*Prints info of all waypoints stored in the database
 *@param: Void
 *@return: Void.
 */
void CWpDatabase::Print()
{
	cout << "Available WapPoints in the database :\n========================================\n" << endl;
	PrintDB();
}

bool CWpDatabase::CopytoMap(std::map<WpKeyType, WpValueType> RHSMap)
{
	CopyToMap(RHSMap);
	return true;
}
