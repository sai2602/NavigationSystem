/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CCSV.CPP
* Author          :	Sai Parimi
* Description     :	A CSV handler class which reads data from a CSV
*					and writes it to the database and vice-versa.
****************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include "CPersistanceStorage.h"

#ifndef CCSVREADER_H_
#define CCSVREADER_H_

typedef enum ErrorCodes{
	NoError,
	MultipleDelimiters,
	InvalidDelimiter,
	TooManyParameters,
	TooLittleParameters,
	LatitudeNotNumber,
	LongitudeNotNumber,
	TypeIncorrect
}ErrorCode_t;

typedef enum DatabaseType{
	WayPoint,
	POI
}DB_t;

typedef enum Delimiter{
	comma,
	colon
}Delimiter_t;

class CCSV: public CPersistentStorage{

private:

	std::string MediaName;
	ErrorCode_t ValidityCheck(std::string line,DB_t DBType,std::string &Name,std::string &Description,float &Latitude,float &Longitude,Wp_t &WPType,Poi_t &POIType);
	bool CheckCommaDelimiter(std::string line);
	bool CheckColonDelimiter(std::string line);
	unsigned int NumberOfEntries(std::string line,char delimiter);
	ErrorCode_t GetAllData(std::string line,std::string &Name,std::string &Description,float &Latitude,float &Longitude,Wp_t &WPType,Poi_t &POIType,DB_t DBType,Delimiter_t Delimiter);
	void ErrorHandler(ErrorCode_t ErrorValues,unsigned int LineNumber,DB_t DBType,std::string line);

public:
/**
* Set the name of the media to be used for persistent storage.
* The exact interpretation of the name depends on the implementation
* of the component.
*
* @param name the media to be used
*/
void setMediaName(std::string name);
/**
* Write the data to the persistent storage.
*
* @param waypointDb the data base with way points
* @param poiDb the database with points of interest
* @return true if the data could be saved successfully
*/
bool writeData(const CWpDatabase& waypointDb, const CPOIDatabase& poiDb);

/**
* Fill the databases with the data from persistent storage. If
* merge mode is MERGE, the content in the persistent storage
* will be merged with any content already existing in the data
* bases. If merge mode is REPLACE, already existing content
* will be removed before inserting the content from the persistent
* storage.
*
* @param waypointDb the the data base with way points
* @param poiDb the database with points of interest
* @param mode the merge mode
* @return true if the data could be read successfully
*/
bool readData (CWpDatabase& waypointDb, CPOIDatabase& poiDb, MergeMode mode);

};



#endif /* CCSVREADER_H_ */
