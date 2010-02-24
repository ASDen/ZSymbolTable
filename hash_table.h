#ifndef _ZHASH_H_
#define _ZHASH_H_

//#include "../ZTypes/ZTypes.h"
#include "../ZTypes/Zlang.h"
#include <google/dense_hash_map>
using google::dense_hash_map;
using stdext::hash_compare;

struct eqstr
{
	bool operator()(const ZChar* s1, const ZChar* s2) const
  {
    return (s1 == s2) || (s1 && s2 && zcstrcmp(s1, s2) == 0);
  }
};

template <class Data>
class ZHash
{
public:

	dense_hash_map < const ZChar * , Data* , hash_compare < const ZChar * > , eqstr > ZIHash;
	
	ZHash()
	{
		ZIHash.set_empty_key(NULL);
	}

	void Insert(Data* d , ZChar * key)
	{
		ZIHash[key]=d;
	}

	void Delete(ZChar * key)
	{
		ZIHash.set_deleted_key (_ZC(""));
		ZIHash.erase(key);
		ZIHash.clear_deleted_key();
	}

	void PrintAll()
	{
		for(
			dense_hash_map < const ZChar * , Data* , hash_compare < const ZChar * > , eqstr >::iterator i=ZIHash.begin();
			i!=ZIHash.end();i++)
			cout<<i->first<<" : "<< boost::apply_visitor(ToString(),*(i->second)) <<endl;
	}

};

template <class ZHVar>
class ZScope
{
public:
	int id;
	ZHash<ZHVar> VarTable;
	ZScope<ZHVar>* Parent;
	
	ZHVar* lookup(ZChar * key)
	{
		if(VarTable.ZIHash.find(key)==VarTable.ZIHash.end()) return NULL;
		else return VarTable.ZIHash.find(key)->second;
	}

};

#endif