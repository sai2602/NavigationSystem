/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CROUTE.H
* Author          :	Sai Parimi
* Description     :	This class creates a route by connecting multiple waypoins
*					and adds POIs to the route whose data is fetched from
*					POI Database.
****************************************************************************/
#include<string>
#include<iostream>
#include <stdlib.h>
#include<vector>
#include "CPOIDatabase.h"
#include "CWpDatabase.h"


#ifndef CROUTE_H
#define CROUTE_H


class CRoute {
private:
CPOIDatabase *m_pPoiDatabase;
CWpDatabase *m_pWpDatabase;
std::vector<WpValueType*> Route;


public:

CRoute(CRoute& Origin);

CRoute();

~CRoute();

void ConnectToPOIDatabase(CPOIDatabase *pPOIDB);

void AddWayPoint(WpKeyType NameWp);

void AddPOI(POIKeyType NamePoi, std::string AfterWp);

void ConnectToWPDatabase(CWpDatabase *pWpDB);

CRoute& operator+=(const WpKeyType Name);

CRoute& operator+(CRoute& Route2);

CRoute& operator=(CRoute& Robject);

void ClearRoute();

void Print();

const std::vector<const WpValueType*> getRoute();

/*
 * Unused in this exercise
double GetDistanceNextPOI(const CWayPoint &wp,CPOI &POI);
*/
};
/********************
**  CLASS END
*********************/
#endif /* CROUTE_H */
