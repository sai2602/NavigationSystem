#include "CGPSSensor.h"
#include <sstream>
using namespace std;

/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSensor.CPP
* Author          :	Sai Parimi
* Description     :	An instance to CWayPoint with the current location is
*					created and these co-ordinates are used henceforth
*					for route information evaluations.
****************************************************************************/

//Method Implementations

CGPSSensor::CGPSSensor()
{
	/* No Default members to construct*/
}

/*
 *This function reads the current position of the user and returns the corresponding coordinates.
 *@param : Void
 *@return : CWayPoint object
 */
CWayPoint CGPSSensor::GetCurrentPosition()
{
	double UserLatitude,UserLongitude;
	bool LatitudeSet = false, LongitudeSet = false;
	cout << "GPS Sensor Function Example :" << endl;
	cout << "===========================" << endl << endl;
	cout << "Enter Latitude of Current Position : " << endl;
	//cin >> UserLatitude;

	/*If either of the data is wrong(Latitude or Longitude) both are reset to avoid confusion in erroneous output
	 * In this case, if a wrong entry for Latitude is made, entry info for longitude is not requested for at all.
	 * This method also ensures that an entry is made. Avoids no entries.
	 * */
	while(LatitudeSet == false)
	{
		LatitudeSet = true;
		cin >> UserLatitude;

		if(cin.fail() || (UserLatitude < -90) || (UserLatitude > 90))
		{
			cout << "Wrong data entered. Please enter again(Latitude should be between -90 and 90)." << endl;
			cin.clear();
			cin.ignore(256,'\n');
			LatitudeSet = false;
		}
	}
	cout << "Enter Longitude of Current Position : " << endl;
	while(LongitudeSet == false)
	{
		LongitudeSet = true;
		cin >> UserLongitude;
		if(cin.fail() || (UserLongitude < -180) || (UserLongitude > 180))
		{
			cout << "Wrong data entered. Please enter again(Longitude should be between -180 and 180)." << endl;
			cin.clear();
			cin.ignore(256,'\n');
			LongitudeSet = false;
		}
	}

	CWayPoint Coordinates1("User Coordinates",UserLatitude,UserLongitude,WAYPOINT);

	return Coordinates1;
}
