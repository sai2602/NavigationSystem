#include "CPOI.h"
#define DefaultLatitude 0
#define DefaultLongitude 0

using namespace std;
/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOI.CPP
* Author          :	Sai Parimi
* Description     :	Creates POI's which fall under the given categories
*					(defined in the Enum) and assigns the necessary attributes
*					to them (Some of which are inherited from CWayPoint)
****************************************************************************/

//Method Implementations

/*Prints the Current POI's attributes i.e., Name,Description,Latitude,Longitude,Type in the specified format
 * @param : int format, format in which the data is to be printed
 * @return : Void
 * */
void CPOI::Print(int format)
{
	string TypeName;
	switch(m_Type)
	{
	case RESTAURANT:
		TypeName = "RESTAURANT";
		break;
	case TOURISTIC:
		TypeName = "TOURISTIC";
		break;
	case GASSTATION:
		TypeName = "GASSTATION";
		break;
	case UNIVERSITY:
		TypeName = "UNIVERSITY";
		break;

	}

	cout << "Of Type : " << TypeName << " : " << m_Description << " : " << endl;
	CWayPoint::Print(MMSS);
	cout << "\n";
}

/*Triggers the print method which prints all the attributes of a POI i.e., Name,Description,Latitude,Longitude,Type
 * @param : ostream& poiprint: stream write parameter, CPOI& POI: Object whose data should be printed
 * @return : ostream&, reference to the ostream object
 * */
std::ostream& operator<<(std::ostream& poiprint,CPOI& POI)
{
	POI.Print(MMSS);
	return poiprint;
}

/*Fetches all the attributes of a POI i.e., Name,Description,Latitude,Longitude,Type
 * @param : Void
 * @return : Void
 * The return type is void since the attributes are returned to the calling function via reference parameters
 * */
void CPOI::GetAllDataByReference(string &name,double &latitude,double &longitude,Poi_t &type,string &description)
{
	name = m_LocationName;
	latitude = m_Latitude;
	longitude = m_Longitude;
	type = m_Type;
	description = m_Description;
}

/*Parameterized constructor to set the members to default values defined by the user while creating the object
 * @param : Type(type enum), Name(type string), Description(type string), Latitude(type double), Longitude(type double)
 * */
CPOI::CPOI(Poi_t Type,string Name,string Description,double Latitude,double Longitude)
{
	m_Type = Type;
	m_Description = Description.empty() == 0 ? Description : "No Description";
	CWayPoint::Set(Name,Latitude,Longitude);
}
/* Default Constructor added as well to handle no parameterized constructs*/
CPOI::CPOI()
{
	m_Type = UNIVERSITY;
	m_LocationName = "HDA";
	m_Description = "Description";
	m_Latitude = DefaultLatitude;
	m_Longitude = DefaultLongitude;
}

/*Returns the type of POI
 * @param : Void
 * @return: POI Enum type
 **/
Poi_t CPOI::GetPOIType() const
{
	return m_Type;
}

/*Returns the description of POI
 * @param : Void
 * @return: string type
 **/
std::string CPOI::GetDescription() const
{
	return m_Description;
}
