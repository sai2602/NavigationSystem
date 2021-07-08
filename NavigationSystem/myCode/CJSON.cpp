#include "CJSON.h"
#include<map>
using namespace APT;
using namespace std;

/*
 *This function sets the media name of the files which would be referred to for read and write operations.
 *@param : string name, which is the media name of the file.
 *@return : Void
 */
void CJSON::setMediaName(string name)
{
	MediaName = name;
}

/**
* Write the data to the persistent storage.
*
* @param waypointDb the data base with way points
* @param poiDb the database with points of interest
* @return true if the data could be saved successfully
*/
bool CJSON::writeData(const CWpDatabase& waypointDb, const CPOIDatabase& poiDb)
{
	ofstream FileHandler;
	string filename = MediaName + "-output.txt";
	FileHandler.open(filename.c_str(),ios::out);
	bool Success = true;
	if(!FileHandler.is_open())
	{
		Success = false;
	}

	map<WpKeyType,WpValueType>WpMap;
	map<POIKeyType,POIValueType>PoiMap;
	map<WpKeyType,WpValueType>::iterator itwp;
	map<POIKeyType,POIValueType>::iterator itpoi;

	WpMap = waypointDb.GetWPMap();
	PoiMap = poiDb.GetPOIMap();

	FileHandler << "{" << endl << "\t" << "\"waypoints\": [" << endl;
	if(!WpMap.empty())
	{
		for(itwp = WpMap.begin(); itwp != WpMap.end(); ++itwp)
		{
			WpInfoPrinter(itwp,FileHandler);
		}
		FileHandler << "],";
	}
	else
	{
		FileHandler << "],";
	}
	FileHandler << "\n\t" << "\"pois\": [" << endl;
	if(!PoiMap.empty())
	{
		for(itpoi = PoiMap.begin(); itpoi != PoiMap.end(); ++itpoi)
		{
			POIInfoPrinter(itpoi,FileHandler);
		}
		FileHandler << "]" << endl << "}";
	}
	else
	{
		FileHandler << "]" << endl << "}";

	}
	FileHandler.close();
	return (Success);
}

/* Evaluate the line number based on the current token state and update the status
 * @param: APT::CJsonToken* typeptr,unsigned int &linenumber,States_t State: Token info and status of state machine
 * @return void
 *
 */
void CJSON::linenumbercalculator(APT::CJsonToken* typeptr,unsigned int &linenumber,States_t State)
{
	switch(typeptr->getType())
	{
		case CJsonToken::STRING:
			if(State != WaitingforStringValue)
			linenumber++;
		break;
		case CJsonToken::BEGIN_OBJECT:
			linenumber++;
		break;
		case CJsonToken::END_ARRAY:
			linenumber++;
		break;
		case CJsonToken::END_OBJECT:
			linenumber++;
		break;
	}
}
/*Checks the string value of the POI type and evaluates the equivalent Enum value of POI type
 * @param: std::string Type, Poi_t &POITYPE: String info and Enum info
 * @return: Void
 */
void CJSON::ValidatePOIType(std::string Type, Poi_t &POITYPE)
{
	if(Type.compare("Restaurant") == 0)
	{
		POITYPE = RESTAURANT;
	}
	else if(Type.compare("Touristic") == 0)
	{
		POITYPE = TOURISTIC;
	}
	else if(Type.compare("Gasstation") == 0)
	{
		POITYPE = GASSTATION;
	}
	else if(Type.compare("University") == 0)
	{
		POITYPE = UNIVERSITY;
	}
	else
	{
		throw InvalidType;
	}
}
/*Print Waypoint info into JSON file after reading it from DB
 * @param: std::map<WpKeyType,WpValueType>::iterator itwp,std::ofstream &FileHandler: iterator to map and a handler to output file
 * @return: void
 */
void CJSON::WpInfoPrinter(std::map<WpKeyType,WpValueType>::iterator itwp,std::ofstream &FileHandler)
{
	FileHandler << "\t{" << endl << "\t\t" << "\"name\": \"" << itwp->second.GetName() << "\"," << endl;
	FileHandler << "\t\t\"" << "latitude\": " << itwp->second.GetLatitude() << "," << endl;
	FileHandler << "\t\t\"" << "longitude\": " << itwp->second.GetLongitude() << endl;
	FileHandler << "\t" << "}," << endl;
}
/*Print POI info into JSON file after reading it from DB
 * @param: std::map<POIKeyType, POIValueType>::iterator itpoi,std::ofstream& FileHandler: iterator to map and a handler to output file
 * @return: void
 */
void CJSON::POIInfoPrinter(std::map<POIKeyType, POIValueType>::iterator itpoi,
		std::ofstream& FileHandler)
{
	FileHandler << "\t{" << endl << "\t\t" << "\"name\": \"" << itpoi->second.GetName() << "\"," << endl;
	FileHandler << "\t\t\"" << "latitude\": " << itpoi->second.GetLatitude() << "," << endl;
	FileHandler << "\t\t\"" << "longitude\": " << itpoi->second.GetLongitude() << "," << endl;
	FileHandler << "\t\t\"" << "type\": " << "\"" << TypetoStringConverter(itpoi->second.GetPOIType()) << "\"," << endl;
	FileHandler << "\t\t\"" << "description\": " << "\"" << itpoi->second.GetDescription() << "\"" << endl;
	FileHandler << "\t" << "}," << endl;
}
/*Convert the POI Enum type to equivalent string type
 * @param: Poi_t Type: enum type
 * @return: String: string info
 */
std::string CJSON::TypetoStringConverter(Poi_t Type)
{
	string data;
	switch(Type)
	{
		case RESTAURANT:
			data = "Restaurant";
		break;
		case UNIVERSITY:
			data = "University";
		break;
		case GASSTATION:
			data = "Gasstation";
		break;
		case TOURISTIC:
			data = "Touristic";
		break;
	}
	return data;
}
/*Handles the state machine for the read operation
 * @param:TokenStates_t &TokenState: Current state
 * @param: APT::CJsonToken::TokenType PrevToken: Previous token information
 */
void CJSON::TokenStateHandler(TokenStates_t &TokenState,
		APT::CJsonToken::TokenType PrevToken, APT::CJsonToken::TokenType CurrToken)
{
	static int ColonCounter = 0;
	if(CurrToken != CJsonToken::END_ARRAY && CurrToken != CJsonToken::END_OBJECT)
	{
		switch(TokenState)
		{
			case WaitingForStartObject:
				if(!(CurrToken == CJsonToken::BEGIN_OBJECT))
					throw MissingStart;
				else TokenState = WaitingForString;
			break;
			case WaitingForString:
				if(!(CurrToken == CJsonToken::STRING))
					throw MissingLabel;
				else TokenState = WaitingForColon;
			break;
			case WaitingForColon:
				ColonCounter++;
				if(!(CurrToken == CJsonToken::NAME_SEPARATOR))
					throw MissingColon;
				else
				{
					if(ColonCounter == 1)
						TokenState = WaitingForArrayStart;
					else
						TokenState = SkipValue;
				}
			break;
			case WaitingForArrayStart:
				if(!(CurrToken == CJsonToken::BEGIN_ARRAY))
					throw MissingStartArray;
				else
					TokenState = WaitingForStartObject;
			break;
			case SkipValue:
				TokenState = WaitingForComma;
			break;
			case WaitingForComma:
				if(!(CurrToken == CJsonToken::VALUE_SEPARATOR))
				{
					throw MissingComma;
				}
				else
				{
					if(PrevToken == CJsonToken::END_OBJECT)
						TokenState = WaitingForStartObject;
					else
						TokenState = WaitingForString;
				}

			break;
		}
	}
	else
	{
		if(CurrToken == CJsonToken::END_ARRAY)
			ColonCounter = 0;
		TokenState = WaitingForComma;
	}
}
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
bool CJSON::readData(CWpDatabase& waypointDb, CPOIDatabase& poiDb,
		MergeMode mode)
{
	ifstream WPHandler;
	string filename = MediaName + ".txt";
	WPHandler.open(filename.c_str(),ios::in);
	CJsonScanner obj(WPHandler);
	CJsonToken *typeptr;
	CJsonStringToken *strptr;
	currentstate_t tokentype = labelread;
	atrribtype_t attribvalue = valid;
	States_t CurrentState = WaitingforDB;
	TokenStates_t TokenState = WaitingForStartObject;
	unsigned int linenumber = 0;
	string locname,locdescription,loctype;
	double loclatitude,loclongitude;
	DBChoice_t DBSelected = NoChoice;
	unsigned int valuecounter = 0;
	bool eofreached = false,enteredcatch = false,Success = true;
	CJsonToken::TokenType PrevToken = CJsonToken::VALUE_SEPARATOR;

	Wp_t WayPointType = WAYPOINT;
	Poi_t POIType;

if(WPHandler.is_open())
{
	map<WpKeyType,WpValueType>WpMapCopy = waypointDb.GetWPMap();
	map<POIKeyType,POIValueType>PoiMapCopy = poiDb.GetPOIMap();
	if(mode == CPersistentStorage::REPLACE)
	{
		waypointDb.ClearWPMap();
		poiDb.ClearPOIMap();
	}
	try
	{
		enteredcatch = false;
		while(!eofreached)
		{
			typeptr = obj.nextToken();
			linenumbercalculator(typeptr,linenumber,CurrentState);
			strptr = dynamic_cast<CJsonStringToken*>(typeptr);
			TokenStateHandler(TokenState,PrevToken,typeptr->getType());

			if((typeptr->getType() == CJsonToken::STRING) || (typeptr->getType() == CJsonToken::NUMBER) || (typeptr->getType() == CJsonToken::BOOL))
			{
				if(TokenState == WaitingForStartObject) throw MissingStart;
				if(tokentype == labelread && attribvalue != invalid)
				{
					labelevaluator(DBSelected,tokentype,attribvalue,strptr,CurrentState);
				}
				else if(tokentype == valueread && attribvalue != invalid)
				{
					valueevaluator(tokentype, attribvalue,typeptr,locname,locdescription,loctype,loclatitude,loclongitude,valuecounter,CurrentState,POIType);

				}
				else
				{
					/*Do Nothing*/
				}
			}
			else
			{
				if((typeptr->getType() == CJsonToken::END_ARRAY))
				{
					attribvalue = valid;
					CurrentState = WaitingforDB;

				}
				else if((typeptr->getType() == CJsonToken::END_OBJECT))
				{
					if(PrevToken == CJsonToken::VALUE_SEPARATOR) throw UnwantedToken;
					attribvalue = valid;
					if(PrevToken == CJsonToken::END_ARRAY)
					{
						eofreached = true;
					}
					else
					{
						if(CurrentState == WaitingforNumberValue) throw InvalidNumber;
						if(CurrentState == WaitingforStringValue) throw InvalidString;
						if(DBSelected == WPDB && CurrentState != WaitingforEndofObject)
						{
							if(valuecounter < 3)
							{
								valuecounter = 0;
								throw ToofewParameters;
							}
							else if(valuecounter > 3)
							{
								valuecounter = 0;
								throw ToomanyParameters;
							}
							else
							{
								CWayPoint WP(locname,loclatitude,loclongitude,WayPointType);
								waypointDb.AddWayPoint(WP,WP.GetName());
							}
						}
						if(DBSelected == POIDB && CurrentState != WaitingforEndofObject)
						{
							if(valuecounter < 5)
							{
								valuecounter = 0;
								throw ToofewParameters;
							}
							else if(valuecounter > 5)
							{
								valuecounter = 0;
								throw ToomanyParameters;
							}
							else
							{
								CPOI POI(POIType,locname,locdescription,loclatitude,loclongitude);
								poiDb.AddPOI(POI,POI.GetName());
							}
						}
					}
					valuecounter = 0;
					CurrentState = WaitingforLabel;
				}
				else
				{
					eofreached = false;
					if(typeptr->getType() == CJsonToken::BEGIN_ARRAY)
					{
						if(CurrentState == WaitingforDB)
						{
							CurrentState = WaitingforEndofArray;
							throw InvalidDBType;
						}
					}
				}
			}
			PrevToken = typeptr->getType();
		}
	}

	catch(ErrorStates_t &Errorcode){
		enteredcatch = true;
		switch(Errorcode)
		{
			case InvalidDBType:
				cout << "Error in line: " << linenumber << ": ";
				cout << "Invalid database type entered" << endl;
			break;
			case InvalidLabel:
				cout << "Error in line: " << linenumber << ": ";
				cout << "Invalid Label choice" << endl;
			break;
			case InvalidNumber:
				if(CurrentState == WaitingforNumberValue)
				{
					cout << "Error in line: " << linenumber-1 << ": ";
				}
				else
				{
					cout << "Error in line: " << linenumber << ": ";
				}
				cout << "Invalid number detected" << endl;
			break;
			case InvalidString:
				cout << "Error in line: " << linenumber << ": ";
				cout << "No string provided in value" << endl;
			break;
			case ToofewParameters:
				cout << "Error in line: " << linenumber << ": ";
				cout << "Too few parameters" << endl;
			break;
			case ToomanyParameters:
				cout << "Error in line: " << linenumber << ": ";
				cout << "Too many parameters" << endl;
			break;
			case InvalidType:
				cout << "Error in line: " << linenumber << ": ";
				cout << "Invalid Poi type entered" << endl;
			break;
			case InvalidToken:
				cout << "Error in line: " << linenumber << ": ";
				cout << "Invalid token entered" << endl;
			break;
			case MissingStart:
				cout << "Error in line: " << linenumber << ": ";
				cout << "Expecting { token" << endl;
			break;
			case UnwantedToken:
				cout << "Error in line: " << linenumber - 1 << ": ";
				cout << "Unwanted \",\" entered" << endl;
			break;
			case MissingLabel:
				cout << "Error in line: " << linenumber << ": ";
				cout << "String label missing" << endl;
			break;
			case MissingStartArray:
				cout << "Error in line: " << linenumber - 1 << ": ";
				cout << "Expecting [ token" << endl;
			break;
			case MissingComma:
				cout << ", token expected after every end object,end array and end line in object values." << endl;
			break;
		}
	}
	if(enteredcatch)
	{
		waypointDb.ClearWPMap();
		waypointDb.CopytoMap(WpMapCopy);
		poiDb.ClearPOIMap();
		poiDb.CopytoMap(PoiMapCopy);
		Success = false;
	}
}
else
{
	Success = false;
	cout << "couldn't find " << filename << endl;
}
	return Success;
}
/* JSON file labels are interpreted here as the corresponding waypoint or poi info is updated
 * @param: DBChoice_t& DBSelected: DB choice (WP or POI)
 * @param: currentstate_t& tokentype: current Token state
 * @param: atrribtype_t& attribvalue: label type, name or latitude or so on
 * @param: APT::CJsonStringToken *strptr, dereferenced string info
 * @param: States_t &currentstate, Current state
 * @return: void
 */
void CJSON::labelevaluator(DBChoice_t& DBSelected, currentstate_t& tokentype,
		atrribtype_t& attribvalue,APT::CJsonStringToken *strptr,States_t &currentstate)
{

	if(strptr != 0)
	{
		if(strptr->getValue().compare("waypoints") == 0 && currentstate == WaitingforDB)
		{
			DBSelected = WPDB;
			currentstate = WaitingforLabel;
		}
		else if(strptr->getValue().compare("pois") == 0 && currentstate == WaitingforDB)
		{
			DBSelected = POIDB;
			currentstate = WaitingforLabel;
		}
		else if(strptr->getValue().compare("name") == 0 && (currentstate != WaitingforEndofArray && currentstate != WaitingforEndofObject))
		{
			tokentype = valueread;
			attribvalue = name;
			currentstate = WaitingforStringValue;
		}
		else if(strptr->getValue().compare("latitude") == 0 && (currentstate != WaitingforEndofArray && currentstate != WaitingforEndofObject))
		{
			tokentype = valueread;
			attribvalue = latitude;
			currentstate = WaitingforNumberValue;
		}
		else if(strptr->getValue().compare("longitude") == 0 && (currentstate != WaitingforEndofArray && currentstate != WaitingforEndofObject))
		{
			tokentype = valueread;
			attribvalue = longitude;
			currentstate = WaitingforNumberValue;
		}
		else if(strptr->getValue().compare("type") == 0 && (currentstate != WaitingforEndofArray && currentstate != WaitingforEndofObject))
		{
			tokentype = valueread;
			attribvalue = type;
			currentstate = WaitingforStringValue;
		}
		else if(strptr->getValue().compare("description") == 0 && (currentstate != WaitingforEndofArray && currentstate != WaitingforEndofObject))
		{
			tokentype = valueread;
			attribvalue = description;
			currentstate = WaitingforStringValue;
		}
		else
		{
			tokentype = labelread;
			attribvalue = invalid;
			if(currentstate != WaitingforEndofArray && currentstate != WaitingforEndofObject && currentstate != WaitingforDB)
			{
				currentstate = WaitingforEndofObject;
				throw InvalidLabel;
			}
		}
	}
	else
	{
		attribvalue = invalid;
		throw InvalidNumber;

	}
}
/*interpret the value corresponding to a specific label and accumulate that info for the corresponding object
 * @param: currentstate_t& tokentype, current token state
 * @param: atrribtype_t& attribvalue, label value
   @param: APT::CJsonToken* typeptr, string equivalent label
   @param: std::string& locname, object param
   @param: std::string& locdescription, object param
   @param: std::string& loctype, object param
   @param: double &loclatitude, object param
   @param: double &loclongitude, object param
   @param: unsigned int &valuecounter, number of values for the object
   @param: States_t &currentstate, current state machine state
   @param: Poi_t &POIType, POI enum value
 * @return: void
 */
void CJSON::valueevaluator(currentstate_t& tokentype, atrribtype_t& attribvalue,
		APT::CJsonToken* typeptr, std::string& locname,
		std::string& locdescription, std::string& loctype, double &loclatitude,
		double &loclongitude,unsigned int &valuecounter,States_t &currentstate,Poi_t &POIType)
{
	CJsonStringToken *strptr;
	CJsonNumberToken *numptr;

	switch(attribvalue)
	{
		case name:
			strptr = dynamic_cast<CJsonStringToken*>(typeptr);
			if(strptr && currentstate == WaitingforStringValue)
			{
				locname = strptr->getValue();
				if(locname.compare("") == 0) throw InvalidString;
				attribvalue = valid;
				valuecounter++;
				currentstate = WaitingforLabel;
			}
			else
				currentstate = WaitingforEndofObject;

			tokentype = labelread;

		break;
		case description:
			strptr = dynamic_cast<CJsonStringToken*>(typeptr);
			if(strptr && currentstate == WaitingforStringValue)
			{
				locdescription = strptr->getValue();
				attribvalue = valid;
				valuecounter++;
				currentstate = WaitingforLabel;
			}
			else
				currentstate = WaitingforEndofObject;

			tokentype = labelread;

		break;
		case type:
			strptr = dynamic_cast<CJsonStringToken*>(typeptr);
			if(strptr && currentstate == WaitingforStringValue)
			{
				loctype = strptr->getValue();
				ValidatePOIType(loctype,POIType);
				attribvalue = valid;
				valuecounter++;
				currentstate = WaitingforLabel;
			}
			else
				currentstate = WaitingforEndofObject;

			tokentype = labelread;

		break;
		case latitude:
			numptr = dynamic_cast<CJsonNumberToken*>(typeptr);
			if(numptr == NULL) throw InvalidNumber;
			else
			{
				if(numptr && currentstate == WaitingforNumberValue)
				{
					loclatitude = numptr->getValue();
					attribvalue = valid;
					valuecounter++;
					currentstate = WaitingforLabel;
				}
				else
					currentstate = WaitingforEndofObject;
			}

			tokentype = labelread;

		break;
		case longitude:
			numptr = dynamic_cast<CJsonNumberToken*>(typeptr);
			if(numptr == NULL) throw InvalidNumber;
			else
			{
				if(numptr && currentstate == WaitingforNumberValue)
				{
					loclongitude = numptr->getValue();
					attribvalue = valid;
					valuecounter++;
					currentstate = WaitingforLabel;
				}
				else
					currentstate = WaitingforEndofObject;
			}

			tokentype = labelread;

		break;
		default:
			attribvalue = invalid;
			valuecounter = 0;
			currentstate = WaitingforEndofObject;
	}
}

