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


#include "CWayPoint.h"
#include "CDatabaseHandler.h"
#include<map>

#ifndef CWPDATABASE_H_
#define CWPDATABASE_H_

typedef std::string WpKeyType;
typedef CWayPoint WpValueType;

class CWpDatabase: public CDatabaseHandler<WpKeyType,WpValueType> {

public:

	void AddWayPoint(WpValueType const& WP, WpKeyType const& Key);

	CWpDatabase();

	WpValueType* GetPointerToWayPoint(WpKeyType Name);

	std::map<WpKeyType, WpValueType> GetWPMap() const;

	bool ClearWPMap();

	void Print();

	bool CopytoMap(std::map<WpKeyType, WpValueType> RHSMap);
};


#endif /* CWPDATABASE_H_ */
