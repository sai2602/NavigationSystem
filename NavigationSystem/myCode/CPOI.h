/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOI.H
* Author          :	Sai Parimi
* Description     :	This class defines a POI(Point of Interest) which
*					defines the name, location and a description for
*					the POI.
****************************************************************************/
#include<string>
#include<iostream>
#include <stdlib.h>
#include "CWayPoint.h"

#ifndef CPOI_H
#define CPOI_H

typedef enum Points
{
	RESTAURANT,
	TOURISTIC,
	GASSTATION,
	UNIVERSITY
}Poi_t;



class CPOI: public CWayPoint{
private:

Poi_t m_Type;
std::string m_Description;


public:

	friend std::ostream& operator<<(std::ostream & poiprint,CPOI& POI);

	void Print(int format);

	void GetAllDataByReference(std::string &name,double &latitude,double &longitude,Poi_t &type,std::string &description);

	CPOI(Poi_t type,std::string name,std::string description,double latitude,double longitude);

	CPOI();

	Poi_t GetPOIType() const;

	std::string GetDescription() const;

};


/********************
**  CLASS END
*********************/
#endif /* CPOI_H */
