#include "CPOIDatabase.h"

using namespace std;
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOIDatabase.CPP
* Author          :	Sai Parimi
* Description     :	This Class Creates a database which is a pool of all the
*					POI's defined by the user. Based on the route created,
*					the user can choose some or all of the POI's available
*					in the pool and add it to the defined route.
****************************************************************************/

//Method Implementations

/*Adds the POI information to the database, in this case MapOfPOIs map
 *@param: CPOI const& POI, const reference to the CPOI object
 *@return: Void.
 */
void CPOIDatabase::AddPOI(POIValueType const& POI, POIKeyType const& Key)
{
	if(!(AddLocationToMap(POI,Key)))
	{
		cout << "The POI with key: " << Key << " already exists in the database." << endl << endl;
	}
}
/*default class constructor
 *@param: Void
 */
CPOIDatabase::CPOIDatabase()
{

}

/*Name(the dummy parameter in the function call) is the name of the POI that the user has requested to add EnRoute
 * This function now parses through all the objects available in the database (stored in the MapOfPOIs map) and when
 * there is a hit while parsing, the address of the object is passed to the CRoute class. Passing the address of the
 * object instead of the entire object is useful as we are not creating a copy of the object in the Calling function.
 * Instead, we are only referring to the address where the POI is and using it when needed. This helps save memory.
 * @param: POI name which should be searched for in the database(string type)
 * @return: a pointer to the object whose name attribute matches to the requested name.
 * */
POIValueType* CPOIDatabase::GetPointerToPOI(POIKeyType Name)
{
	return(GetPointerToLocation(Name));
}

/*Returns the map in which all the POIs are stored
 *@param: Void
 *@return: Map which has all the POIs in it.
 */
std::map<POIKeyType, POIValueType> CPOIDatabase::GetPOIMap() const
{
	return GetDBMap();
}

/*Clears the map in which all the POIs are stored
 *@param: Void
 *@return: bool value to signify clear status.
 */
bool CPOIDatabase::ClearPOIMap()
{
	ClearMap();
	return (MapOfLocations.size() == 0);
}

bool CPOIDatabase::CopytoMap(std::map<POIKeyType, POIValueType> RHSPOIMap)
{
	CopyToMap(RHSPOIMap);
	return true;
}

void CPOIDatabase::Print()
{
	cout << "Available POIs in the database :\n========================================\n" << endl;
	PrintDB();
}
