

#ifndef CDATABASEHANDLER_H_
#define CDATABASEHANDLER_H_
#include<map>
#include<iostream>
#include<stdlib.h>
#include"CPOI.h"

template<class Key,class Value>
class CDatabaseHandler{
protected:
	std::map<Key,Value> MapOfLocations;
public:
	bool AddLocationToMap(Value const LocationObject, Key const KeyInfo);
	Value* GetPointerToLocation(Key LocationName);
	std::map<Key,Value> GetDBMap() const;
	void ClearMap();
	void CopyToMap(std::map<Key,Value> OldMap);
	void PrintDB();
};
/*Adds the requested object to the map
 *@param: key and value information
 *@return: bool to signify success
 */
template<class Key, class Value>
inline bool CDatabaseHandler<Key, Value>::AddLocationToMap(
		const Value LocationObject, const Key KeyInfo)
{
	bool validentry = true;
	if(MapOfLocations.count(KeyInfo))
	{
		validentry = false;
	}
	else
	{
		MapOfLocations[KeyInfo] = LocationObject;
	}
	return validentry;
}
/*returns a reference to the requested object based on the key info
 * @param: key value
 * @return: pointer to the object info
 */
template<class Key, class Value>
inline Value* CDatabaseHandler<Key, Value>::GetPointerToLocation(
		Key LocationName)
{
	Value *ObjectPointer = NULL;
	typename std::map<Key,Value>::iterator it_finder;
	it_finder = MapOfLocations.find(LocationName);
	if(!(it_finder == MapOfLocations.end()))
	{
		ObjectPointer = (&(it_finder->second));
	}
	return ObjectPointer;
}
/* returns the database map
 * @param: void
 * @return: Map
 */
template<class Key, class Value>
inline std::map<Key, Value> CDatabaseHandler<Key, Value>::GetDBMap() const
{
	return MapOfLocations;
}
/* Clear the map in the current instance
 * @param: void
 * @retun: void
 */
template<class Key, class Value>
inline void CDatabaseHandler<Key, Value>::ClearMap()
{
	MapOfLocations.clear();
}

/* Copy requested map to the local map(member)
 * @param: new map info
 * @return: void
 */
template<class Key, class Value>
inline void CDatabaseHandler<Key, Value>::CopyToMap(std::map<Key, Value> OldMap)
{
	MapOfLocations = OldMap;
}
/* Prints DB information(map contents)
 * @param: void
 * @return: void
 */
template<class Key, class Value>
inline void CDatabaseHandler<Key, Value>::PrintDB()
{
	typename std::map<Key,Value>::iterator it;
	for(it = MapOfLocations.begin(); it != MapOfLocations.end(); ++it)
	{
		std::cout << it->first << std::endl;
		std::cout << it->second << std::endl;
	}
	std::cout << std::endl;
}

#endif /* CDATABASEHANDLER_H_ */
