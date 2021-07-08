/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOIDatabase.H
* Author          :	Sai Parimi
* Description     :	This class creates a database containing information
*					of all the POI's added by the user. This is referenced
*					by CRoute class to extract EnRoute POI's.
****************************************************************************/
#include<string>
#include<iostream>
#include <stdlib.h>
#include <map>
#include "CPOI.h"
#include "CDatabaseHandler.h"

#ifndef CPOIDatabase_H
#define CPOIDatabase_H

typedef std::string POIKeyType;
typedef CPOI POIValueType;

class CPOIDatabase:CDatabaseHandler<POIKeyType,POIValueType> {

public:

	void AddPOI(POIValueType const& POI, POIKeyType const& Key);

	CPOIDatabase();

	CPOI* GetPointerToPOI(POIKeyType Name);

	std::map<POIKeyType, POIValueType> GetPOIMap() const;

	bool ClearPOIMap();

	bool CopytoMap(std::map<POIKeyType, POIValueType> RHSPOIMap);

	void Print();
};
/********************
**  CLASS END
*********************/
#endif /* CPOIDatabase_H */
