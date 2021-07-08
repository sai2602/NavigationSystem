#include<sstream>
#include "CCSV.h"
using namespace std;

#define OutputfileDelimiter 0 //0 for comma; 1 for semi-colon

/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CCSV.CPP
* Author          :	Sai Parimi
* Description     :	A CSV handler class which reads data from a CSV
*					and writes it to the database and vice-versa.
****************************************************************************/

//Method Implementations

/*
 *This function sets the media name of the files which would be referred to for read and write operations.
 *@param : string name, which is the media name of the file.
 *@return : Void
 */
void CCSV::setMediaName(string name)
{
	MediaName = name;
}

/*
 *Parses through the WP and POI databases and writes all the information
 *available in it into the corresponding .csv files.
 *@param : const CWpDatabase& waypointDb,const CPOIDatabase& poiDb, references to both the databases.
 *@return : bool, to signify success
 */
bool CCSV::writeData(const CWpDatabase& waypointDb,
		const CPOIDatabase& poiDb)
{
	std::map<WpKeyType,WpValueType> WPMapCopy;
	std::map<POIKeyType,POIValueType> POIMapCopy;

	string WPFileName = MediaName + "-wp.csv";
	string POIFileName = MediaName + "-poi.csv";
	char delimiter;
	delimiter = (OutputfileDelimiter == 0) ? ',' : ';';

	ofstream WriteWPHandle;
	WriteWPHandle.open(WPFileName.c_str(),ios::out);
	ofstream WritePOIHandle;
	WritePOIHandle.open(POIFileName.c_str(),ios::out);

	WPMapCopy = waypointDb.GetWPMap();
	POIMapCopy = poiDb.GetPOIMap();

	for(std::map<WpKeyType,WpValueType>::iterator it = WPMapCopy.begin(); it != WPMapCopy.end(); ++it)
	{
		WriteWPHandle << it->first << delimiter;
		WriteWPHandle << it->second.GetLatitude() << delimiter;
		WriteWPHandle << it->second.GetLongitude() << delimiter;
		if(it->second.GetType() == 0)
			WriteWPHandle << "WAYPOINT" << endl;
	}
	WriteWPHandle.close();

	for(std::map<POIKeyType,POIValueType>::iterator it = POIMapCopy.begin(); it != POIMapCopy.end(); ++it)
	{
		switch(it->second.GetPOIType())
		{
			case RESTAURANT:
				WritePOIHandle << "RESTAURANT" << delimiter;
				break;
			case TOURISTIC:
				WritePOIHandle << "TOURISTIC" << delimiter;
				break;
			case GASSTATION:
				WritePOIHandle << "GASSTATION" << delimiter;
				break;
			case UNIVERSITY:
				WritePOIHandle << "UNIVERSITY" << delimiter;
				break;
			default:
				WritePOIHandle << delimiter;
		}
		WritePOIHandle << it->first << delimiter;
		WritePOIHandle << it->second.GetDescription() << delimiter;
		WritePOIHandle << it->second.GetLatitude()  << delimiter;
		WritePOIHandle << it->second.GetLongitude() << "\n";
	}
	WritePOIHandle.close();

	return true;
}

/*
 *This function checks for all possible errors that could occur in a line and handles them accordingly.
 *The possible errors that could occur are defined in the corresponding enum type.
 *@param : string line,DB_t DBType,string &Name,string &Description,float &Latitude,float &Longitude,Wp_t &WPType,Poi_t &POIType
 *@param : line in which the error is to be checked, corresponding DB and reference parameters like name etc to hold WP and POI info.
 *@return : Error code(Enum Type)
 */
ErrorCode_t CCSV::ValidityCheck(string line,DB_t DBType,string &Name,string &Description,float &Latitude,float &Longitude,Wp_t &WPType,Poi_t &POIType)
{
	ErrorCode_t Returnerror = NoError;
	bool CommaCSV = CheckCommaDelimiter(line);
	bool ColonCSV = CheckColonDelimiter(line);

	if(CommaCSV && ColonCSV)
	{
		Returnerror = MultipleDelimiters;
	}
	else if(CommaCSV)
	{
		unsigned int count = NumberOfEntries(line,',');
		if(((DBType == WayPoint) && count > 4) || ((DBType == POI) && count > 5))
		{
			Returnerror = TooManyParameters;
		}
		else if(((DBType == WayPoint) && count == 4) || ((DBType == POI) && count == 5))
		{
			if(line.at(line.size() - 1) != ',')
			{
				Returnerror = TooManyParameters;
			}
		}
		else if(((DBType == WayPoint) && count < 3) || ((DBType == POI) && count < 4))
		{
			Returnerror = TooLittleParameters;
		}
		else if(((DBType == WayPoint) && count == 3) || ((DBType == POI) && count == 4))
		{
			if(line.at(line.size() - 1) == ',')
				Returnerror = TooLittleParameters;
			else
				line.append(",");
		}

		if((Returnerror != TooManyParameters) && (Returnerror != TooLittleParameters))
		{
			if((line.at(line.size() - 1)) != ',')
			{
				line.append(",");
			}
			Delimiter_t Delimiter = comma;
			Returnerror = GetAllData(line,Name,Description,Latitude,Longitude,WPType,POIType,DBType,Delimiter);
		}
	}
	else if(ColonCSV)
	{
		unsigned int count = NumberOfEntries(line,';');
		if(((DBType == WayPoint) && count > 4) || ((DBType == POI) && count > 5))
		{
			Returnerror = TooManyParameters;
		}
		else if(((DBType == WayPoint) && count == 4) || ((DBType == POI) && count == 5))
		{
			if(line.at(line.size() - 1) != ';')
			{
				Returnerror = TooManyParameters;
			}
		}
		else if(((DBType == WayPoint) && count < 3) || ((DBType == POI) && count < 4))
		{
			Returnerror = TooLittleParameters;
		}
		else if(((DBType == WayPoint) && count == 3) || ((DBType == POI) && count == 4))
		{
			if(line.at(line.size() - 1) == ';')
				Returnerror = TooLittleParameters;
			else
				line.append(";");
		}

		if((Returnerror != TooManyParameters) && (Returnerror != TooLittleParameters))
		{
			Delimiter_t Delimiter = colon;
			Returnerror = GetAllData(line,Name,Description,Latitude,Longitude,WPType,POIType,DBType,Delimiter);
		}
	}
	else
	{
		Returnerror = InvalidDelimiter;
	}

	return Returnerror;
}

/*
 *This function checks if a comma delimiter is available in the given line
 *@param : std::string line, the line in which the delimiter should be checked
 *@return : bool, to signify success
 */
bool CCSV::CheckCommaDelimiter(std::string line)
{
	string delimiter = ",";
	size_t found = line.find(delimiter);

	return (found!=string::npos);
}

/*
 *This function checks if a semi-colon delimiter is available in the given line
 *@param : std::string line, the line in which the delimiter should be checked
 *@return : bool, to signify success
 */
bool CCSV::CheckColonDelimiter(std::string line)
{
	string delimiter = ";";
	size_t found = line.find(delimiter);

	return (found!=string::npos);
}

/*
 *This function checks the number of delimiters available in the given line
 *This gives a possible estimate of the number of parameters in the line
 *@param : std::string line,char delimiter: the line in which the delimiter should be checked
 *@return : bool, to signify success
 */
unsigned int CCSV::NumberOfEntries(std::string line,char delimiter)
{
	unsigned int count = 0;
	for(unsigned int i = 0; i < line.size(); i++)
	{
		if(line[i] == delimiter)
		{
			count++;
		}
	}
	return count;
}

/*
 *This function returns all the information available in a line with the reference parameters passed to it.
 *@param : std::string line, std::string& Name,
		std::string& Description, float& Latitude, float& Longitude,
		Wp_t& WPType, Poi_t& POIType, DB_t DBType, Delimiter_t Delimiter, all the parameters into which data is written
 *@return : errorcode enum, to signify success or error in dereferencing.
 */
ErrorCode_t CCSV::GetAllData(std::string line, std::string& Name,
		std::string& Description, float& Latitude, float& Longitude,
		Wp_t& WPType, Poi_t& POIType, DB_t DBType, Delimiter_t Delimiter)
{
	size_t position = 0;
	ErrorCode_t error = NoError;
	int index = 0;

	char delimiter = (Delimiter == comma) ? ',' : ';';

	if(DBType == WayPoint)
	{
		while((position = line.find(delimiter)) != std::string::npos)
		{
			stringstream data(line.substr(0,position));
			if(index == 0)
			{
				Name = data.str();
				index++;
			}
			else if(index == 1)
			{
				data >> Latitude;
				if(data.fail())
				{
					error = LatitudeNotNumber;
				}
				index++;
			}
			else if(index == 2)
			{
				data >> Longitude;
				if(data.fail())
				{
					error = LongitudeNotNumber;
				}
				index++;
			}
			else
			{
				string type;
				type = data.str();
				if(type.compare("WAYPOINT") == 0)
				{
					WPType = WAYPOINT;
				}
				else
				{
					error = TypeIncorrect;
					break;
				}

			}
			line.erase(0,position+1);
		}
	}
	else
	{
		while((position = line.find(delimiter)) != std::string::npos)
		{
			stringstream data(line.substr(0,position));
			if(index == 0)
			{
				string type;
				type = data.str();
				if(type == "TOURISTIC")
				{
					POIType = TOURISTIC;
				}
				else if(type == "UNIVERSITY")
				{
					POIType = UNIVERSITY;
				}
				else if(type == "RESTAURANT")
				{
					POIType = RESTAURANT;
				}
				else if(type == "GASSTATION")
				{
					POIType = GASSTATION;
				}
				else
				{
					error = TypeIncorrect;
					break;
				}
				index++;
			}
			else if(index == 1)
			{
				Name = data.str();
				index++;
			}
			else if(index == 2)
			{
				Description = data.str();
				index++;
			}
			else if(index == 3)
			{
				data >> Latitude;
				if(data.fail())
				{
					error = LatitudeNotNumber;
				}
				index++;
			}
			else
			{
				data >> Longitude;
				if(data.fail())
				{
					error = LongitudeNotNumber;
				}
			}
			line.erase(0,position+1);
		}
	}

	return error;

}

/*
 *This function handles the returned error codes set in the other methods and handles it accordingly.
 *@param : ErrorCode_t ErrorValues,unsigned int LineNumber,DB_t DBType, errorcode, line in which the error occured and its DB.
 *@return : Void
 */
void CCSV::ErrorHandler(ErrorCode_t ErrorValues,unsigned int LineNumber,DB_t DBType,std::string line)
{
	string errorfile;
	errorfile = (DBType == POI) ? (MediaName + "-poi.csv") : (MediaName + "-wp.csv");

	switch(ErrorValues)
	{
		case MultipleDelimiters:
			cout << errorfile << ":" << endl;
			cout << "Error: " << "Multiple delimiters found in line " << LineNumber <<
					": " << line << endl <<
					"(Probably due to German notion of number representation)." << endl << endl;
		break;

		case InvalidDelimiter:
			cout << errorfile << ":" << endl;
			cout << "Error: " << "Invalid delimiter found in line " << LineNumber <<
					": " << line << endl << endl;
		break;

		case TooManyParameters:
			cout << errorfile << ":" << endl;
			cout << "Error: " << "Too many parameters found in line " << LineNumber <<
					": " << line << endl <<
					"(Probably due to German notion of number representation)." << endl << endl;
		break;

		case TooLittleParameters:
			cout << errorfile << ":" << endl;
			cout << "Error: " << "Too few parameters found in line " << LineNumber <<
					": " << line << endl << endl;
		break;

		case LatitudeNotNumber:
			cout << errorfile << ":" << endl;
			cout << "Error: " << "Latitude not a number in line " << LineNumber <<
					": " << line << endl << endl;
		break;

		case LongitudeNotNumber:
			cout << errorfile << ":" << endl;
			cout << "Error: " << "Longitude not a number in line " << LineNumber <<
					": " << line << endl << endl;
		break;

		case TypeIncorrect:
			cout << errorfile << ":" << endl;
			cout << "Error: " << "Invalid Type found in line " << LineNumber <<
					": " << line << endl << endl;
		break;

		case NoError:
			//Handled in readData function itself
			break;
	}
}

/*
 *This function reads the data from text files and based on this, stores the available information in the corresponding DB.
 *@param : ErrorCode_t ErrorValues,unsigned int LineNumber,DB_t DBType, errorcode, line in which the error occurred and its DB.
 *@return : bool, to signify success
 */
bool CCSV::readData(CWpDatabase& waypointDb, CPOIDatabase& poiDb, MergeMode mode)
{
	unsigned int LineNumber = 0;
	string line;

	string Name,Description;
	float Latitude,Longitude;
	Wp_t WPType;
	Poi_t POIType;

	string WPFileName = MediaName + "-wp.csv";
	string POIFileName = MediaName + "-poi.csv";
	ifstream WPHandler;
	WPHandler.open(WPFileName.c_str(),ios::in);
	ifstream POIHandler;
	POIHandler.open(POIFileName.c_str(),ios::in);
	if(!WPHandler.is_open())
	{
		cout << "Couldn't find WayPoint file: " << WPFileName << endl << endl;
	}
	else
	{
		if(mode == REPLACE)
		{
			waypointDb.ClearWPMap();
		}
		while(getline(WPHandler,line))
		{
			LineNumber++;
			ErrorCode_t ReturnedError =  ValidityCheck(line,WayPoint,Name,Description,Latitude,Longitude,WPType,POIType);
			if(ReturnedError == NoError)
			{
				static int i = 1;
				CWayPoint WPObj(Name,Latitude,Longitude,WPType);
				waypointDb.AddWayPoint(WPObj,WPObj.GetName());
				i++;
			}
			else
			{
				ErrorHandler(ReturnedError,LineNumber,WayPoint,line);
			}

		}
	}
	if(!POIHandler.is_open())
	{
		cout << "Couldn't find POI file: " << POIFileName << endl << endl;
	}
	else
	{
		if(mode == REPLACE)
		{
			poiDb.ClearPOIMap();
		}
		LineNumber = 0;
		while(getline(POIHandler,line))
		{
			LineNumber++;
			ErrorCode_t ReturnedError =  ValidityCheck(line,POI,Name,Description,Latitude,Longitude,WPType,POIType);
			if(ReturnedError == NoError)
			{
				CPOI POIObj(POIType,Name,Description,Latitude,Longitude);
				poiDb.AddPOI(POIObj,POIObj.GetName());
			}
			else
			{
				ErrorHandler(ReturnedError,LineNumber,POI,line);
			}

		}
	}
	if(mode == REPLACE)
	{
		cout << "Since the old database has been cleared out, your existing route may no longer be valid. Please recreate the route.\n\n";
	}
	return true;
}

