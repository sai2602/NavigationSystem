/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSensor.H
* Author          :	Sai Parimi
* Description     :	This class returns the current position of the user
*
*
****************************************************************************/

#include<iostream>
#include <stdlib.h>
#include "CWayPoint.h"

#ifndef CGPSSENSOR_H
#define CGPSSENSOR_H

class CGPSSensor {

public:

	CWayPoint GetCurrentPosition();

	CGPSSensor();


};
/********************
**  CLASS END
*********************/
#endif /* CGPSSENSOR_H */
