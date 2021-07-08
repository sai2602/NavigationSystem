/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CWAYPOINT.H
* Author          :	Sai Parimi
* Description     :	This class creates a way point which describes the
*					Name of the location and its corresponding
*					co-ordinates(Latitude and Longitude).
****************************************************************************/
#include<string>
#include<iostream>
#include <stdlib.h>
#include<math.h>
#include<conio.h>


#ifndef CWAYPOINT_H
#define CWAYPOINT_H

enum Cities{Amsterdam = 1, Darmstadt, Berlin, Tokio};


#define DEGREE 1
#define MMSS 2

typedef enum WayPoints
{
	WAYPOINT
}Wp_t;

class CWayPoint {
protected:
	std::string m_LocationName;
	double m_Latitude;
    double m_Longitude;
    Wp_t m_Type;

public:

    void Set(std::string Name, double Latitude, double Longitude);

    std::string GetName() const;

    double GetLatitude() const;

    double GetLongitude() const;

    Wp_t GetType() const;

    void GetAllCoordinatedata(std::string &Name, double &Latitude, double &Longitude,Wp_t Type);

    virtual void Print(int format);

    virtual ~CWayPoint();

    CWayPoint(std::string Name, double Latitude, double Longitude, Wp_t Type);//Constructor

    /*This constructor can be avoided all together
     *by initializing the parameters in the above constructor to some default values*/
    CWayPoint();
	/*
	 * Un-used in this exercise
	double CalculateDistance(const CWayPoint &wp);
	*/
public:

    void LongitudeTodegmmss(int &deg, int &mm, double &ss);

    void LatitudeTodegmmss(int &deg, int &mm, double &ss);

    friend std::ostream& operator<<(std::ostream& wpprint, CWayPoint& WP);
};
/********************
**  CLASS END
*********************/
#endif /* CWAYPOINT_H */
