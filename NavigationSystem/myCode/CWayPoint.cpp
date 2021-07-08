#include "CWayPoint.h"

using namespace std;

#define PI 3.14285
#define RadiusOfEarth 6378.18
#define DefaultLatitude 0
#define DefaultLongitude 0
#define PrintMemoryInformation 0// Make it 1 to turn verbose mode on


/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CWAYPOINT.CPP
* Author          :	Sai Parimi
* Description     :	The assignment of attributes to the CWayPoints to
*					provide a uniqueness to them is handled here.
*
****************************************************************************/

//Method Implementations

/* Set() method checks if the Name, Latitude and Longitude of the way point
 * are in bounds and if so assigns it to them. If they are out of bounds,
 * the necessary error handling happens.
 * @param: string Name, double Latitude, double Longitude, location name, its latitude and longitude
 * @return: Void*/
void CWayPoint::Set(string Name, double Latitude, double Longitude)
{
	bool m_LatitudeOutOfBounds = false,m_LongitudeOutOfBounds = false;
	if((Latitude >= -90) && (Latitude <= 90))
	{
		m_Latitude = Latitude;
		m_LatitudeOutOfBounds = false;
	}
	else
	{
		m_Latitude = DefaultLatitude;
		m_LatitudeOutOfBounds = true;
	}

	if((Longitude >= -180) && (Longitude <= 180))
	{
		m_Longitude = Longitude;
		m_LongitudeOutOfBounds = false;
	}
	else
	{
		m_Longitude = DefaultLongitude;
		m_LongitudeOutOfBounds = true;
	}

	if((Name.length() != 0) && isalnum(Name.at(0)))
	{
		m_LocationName = Name;
	}
	else
	{
		m_LocationName = "No_Location_Selected_or_missing_string";
	}

/*Verbose Mode Handling*/
	/*Another possible way of handling this would be to directly check for #if PrintMemoryInformation == 1
	 * and avoid defining SHOWADDRESS altogether.
	 */
	#if PrintMemoryInformation == 1
	#define SHOWADDRESS
	#endif

	#ifdef SHOWADDRESS

	cout << "Address of " << Name << " object is: " << this <<endl;

	/*The overall size of an object is the sum total of the size of
	 * each individual member in the class (Non-Static and Non-Virtual members)
 	 In this case, sizes of 2 doubles for latitude and longitude and size of string for name*/
	cout << Name << " Object occupies: " << (sizeof(Latitude) + sizeof(Longitude) + sizeof(Name)) << " Bytes of Memory" << endl;
	cout << sizeof(Name) << " Bytes of Data is needed to store the Name of the City" << endl;
	cout << sizeof(Latitude) << " Bytes of Data is needed to store the Latitude of the City" << endl;
	cout << sizeof(Longitude) << " Bytes of Data is needed to store the Longitude of the City" << endl;
	cout << "Attribute Values (Name : Latitude : Longitude) : " << m_LocationName << " : " << " : " << m_Latitude << " : " << m_Longitude << endl;
	cout << "Attribute Addresses (Name : Latitude : Longitude) : " << &m_LocationName << " : " << &m_Latitude << " : " << &m_Longitude << endl;

	cout << '\n';
	#endif
	#undef SHOWADDRESS

	if(m_LatitudeOutOfBounds)
	{
		cout << "Latitude out of bounds for " << m_LocationName << ". Please select in the range -90<= Latitude <= 90. \n"
				"Information for this location might produce erroneous outputs in other processes.\n"
				"Re-initializing the Latitude and Longitude to 0\n" << endl;
		m_Latitude = 0;
		m_Longitude = 0;
	}
	if(m_LongitudeOutOfBounds)
	{
		cout << "Longitude out of bounds for " << m_LocationName << ". Please select in the range -180<= Longitude <= 180.\n"
				"Information for this location might produce erroneous outputs in other processes.\n"
				"Re-initializing the Latitude and Longitude to 0\n" << endl;
		m_Longitude = 0;
		m_Latitude = 0;
	}
}

/*Retrieve the name of the current waypoint
 * @param: Void.
 * @return: Current objects name as a string
 * */
string CWayPoint::GetName() const
{
	return m_LocationName;
}

/*Retrieve the Latitude of the current waypoint
 * @param: Void.
 * @return: Current objects Latitude as a double
 * */
double CWayPoint::GetLatitude() const
{
	return m_Latitude;
}

/*Retrieve the Longitude of the current waypoint
 * @param: Void.
 * @return: Current objects longitude as a double
 * */
double CWayPoint::GetLongitude() const
{
	return m_Longitude;
}

/* Retrieve all the attributes associated with a certain waypoint
 * @param: Name(string type), latitude(double type), longitude(double type),
 * preferably all empty as the current object's attributes will be returned with these itself.
 * @return: Void.
 * */
void CWayPoint::GetAllCoordinatedata(string &Name, double &Latitude, double &Longitude,Wp_t Type)
{
	Name = m_LocationName;
	Latitude = m_Latitude;
	Longitude = m_Longitude;
	Type = m_Type;

	/*This section was done only to compare addresses of parameters in class to that of main file
	 * Un-comment this section to test the same.

	cout << "CLass parameter addresses :\n";
	cout << &m_LocationName << " " << &m_Latitude << " " << &m_Longitude << endl;
	*/
}


/*DEGREE and MMSS are #defined in CWayPoint.h header file.
 *Since the header file is also included in main.cpp,
  these standard definitions can be utilized in main.cpp and here as well.
  *@param: int format, to choose between only degree format or degree, minutes and seconds
  *@return: Void
  */

void CWayPoint::Print(int format)
{
	if(format == DEGREE)
	{
		cout << m_LocationName << " : Coordinates are : Latitude : " << m_Latitude << " deg , Longitude : " << m_Longitude << " deg\n" << endl;
	}
	else if(format == MMSS)
	{
		int deg,mm;
		double ss;
		LatitudeTodegmmss(deg,mm,ss);
		cout << m_LocationName << " : Coordinates are : Latitude : " << deg << " deg " << mm << " min " << ss << " sec ";
		LongitudeTodegmmss(deg,mm,ss);
		 cout << " , Longitude : " << deg << " deg " << mm << " min " << ss << " sec " << endl;
	}
	else
	{
		cout << "Please Enter a valid format choice(Either 1 or 2)\n" << endl;
	}
}

/*Triggers the print method which prints all the attributes of a WP i.e., Name,Latitude,Longitude,Type
 * @param: ostream& wpprint: stream write parameter, CWayPoint& WP: Object whose data should be printed
 * @return: ostream&, reference to the ostream object
 * */
std::ostream& operator<<(std::ostream& wpprint, CWayPoint& WP)
{
	WP.Print(MMSS);
	return wpprint;
}

/*Convert Longitude (in Degrees) to Degrees, Minutes and Seconds
 * @param: references to variables deg,mm,ss all of type int but double for ss
 * @return: Void, as the values are returned with the reference parameters only
 * */
void CWayPoint::LongitudeTodegmmss(int &deg, int &mm, double &ss)
{
	deg = (m_Longitude);
	float MantissaofLongitude_InDegree = m_Longitude - int(m_Longitude);
	float LongitudeMinutes = MantissaofLongitude_InDegree * 60;
	mm = abs(LongitudeMinutes);
	float MantissaofLongitude_InMinutes = LongitudeMinutes - int(LongitudeMinutes);
	ss = abs(MantissaofLongitude_InMinutes * 60);
}

/*Convert Latitude (in Degrees) to Degrees, Minutes and Seconds
 * @param: references to variables deg,mm,ss all of type int but double for ss
 * @return: Void, as the values are returned with the reference parameters only
 * */
void CWayPoint::LatitudeTodegmmss(int &deg, int &mm, double &ss)
{
	deg = (m_Latitude);
	float MantissaofLatitude_InDegree = m_Latitude - int(m_Latitude);
	float LatitudeMinutes = MantissaofLatitude_InDegree * 60;
	mm = abs(LatitudeMinutes);
	float MantissaofLatitude_InMinutes = LatitudeMinutes - int(LatitudeMinutes);
	ss = abs(MantissaofLatitude_InMinutes * 60);
}
/*This Constructor is to handle Objects which are created without any parameter list
 *@param: Void
 * */
CWayPoint::CWayPoint()
{
	m_Latitude = DefaultLatitude;
	m_Longitude = DefaultLongitude;
	m_LocationName = "No_Location_Selected";
	m_Type = WAYPOINT;
}

/*Parameterized constructor which accepts name, latitude and longitude setby user.
 *@param: Location Name of type string, Its latitude and longitude both of type double.
 */
CWayPoint::CWayPoint(string Name, double Latitude, double Longitude,Wp_t Type)
{
	Set(Name,Latitude,Longitude);
	m_Type = Type;
}

/*Destructor*/
CWayPoint::~CWayPoint()
{
}

/*Return the type of WayPoint
 *@param: Void.
 *@return: Enum type describing waypoint
 */
Wp_t CWayPoint::GetType() const
{
	return m_Type;
}

/*Unused in this exercise*/
/*Evaluates distance between 2 waypoints
 *@param: an object of the class CWaypoint (and this acts as the destination, while the calling object is the source)
 *@return: distance, of type double.
 * */
/*
double CWayPoint::CalculateDistance(const CWayPoint &wp)
{
	double SineMultiplications = sin(m_Latitude * (PI/180)) * sin(wp.m_Latitude * (PI/180));
	double LongitudeSubtraction = wp.m_Longitude - m_Longitude;
	double CosineMultiplications = cos(m_Latitude * (PI/180)) * cos(wp.m_Latitude * (PI/180)) * cos(LongitudeSubtraction * (PI/180));
	double CosineInverseParameter = SineMultiplications + CosineMultiplications;
	double Distance = RadiusOfEarth * acos(CosineInverseParameter);
	return Distance;
}
*/
