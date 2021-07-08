
#ifndef CJSON_H_
#define CJSON_H_
#include "CJsonScanner.h"
#include "CPersistanceStorage.h"
#include<fstream>

typedef enum attribchoices {
	name,
	description,
	type,
	latitude,
	longitude,
	invalid,
	valid
}atrribtype_t;

typedef enum currentread {
	labelread,
	valueread
}currentstate_t;

typedef enum DBChoice {
	WPDB,
	POIDB,
	NoChoice
}DBChoice_t;

typedef enum States {
	WaitingforDB,
	WaitingforLabel,
	WaitingforStringValue,
	WaitingforNumberValue,
	WaitingforEndofArray,
	WaitingforEndofObject
}States_t;

typedef enum TokenStates {
	WaitingForString,
	WaitingForColon,
	WaitingForArrayStart,
	WaitingForStartObject,
	WaitingForComma,
	SkipValue
}TokenStates_t;

typedef enum ErrorStates {
	InvalidNumber,
	InvalidLabel,
	InvalidDBType,
	InvalidString,
	ToomanyParameters,
	ToofewParameters,
	InvalidType,
	InvalidToken,
	MissingStart,
	UnwantedToken,
	MissingLabel,
	MissingColon,
	MissingStartArray,
	MissingComma
}ErrorStates_t;

class CJSON: public CPersistentStorage{

private:

	std::string MediaName;
	void labelevaluator(DBChoice_t &DBSelected,currentstate_t &tokentype,atrribtype_t &attribvalue,APT::CJsonStringToken *strptr,States_t &currentstate);
	void valueevaluator(currentstate_t &tokentype,atrribtype_t &attribvalue,APT::CJsonToken *typeptr,std::string &locname,std::string &locdescription,std::string &loctype,double &loclatitude,double &loclongitude,unsigned int &valuecounter,States_t &currentstate,Poi_t &POIType);
	void linenumbercalculator(APT::CJsonToken *typeptr,unsigned int &linenumber,States_t State);
	void ValidatePOIType(std::string Type,Poi_t &POITYPE);
	void WpInfoPrinter(std::map<WpKeyType,WpValueType>::iterator itwp,std::ofstream &FileHandler);
	void POIInfoPrinter(std::map<POIKeyType,POIValueType>::iterator itpoi,std::ofstream &FileHandler);
	std::string TypetoStringConverter(Poi_t Type);
	void TokenStateHandler(TokenStates_t &TokenState,APT::CJsonToken::TokenType PrevToken,APT::CJsonToken::TokenType CurrToken);


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




#endif /* CJSON_H_ */
