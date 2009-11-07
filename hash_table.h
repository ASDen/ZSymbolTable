#include <google/dense_hash_map>
#include "data.h"
using google::dense_hash_map;
using stdext::hash_compare;

struct eqstr
{
	bool operator()(const ZChar* s1, const ZChar* s2) const
  {
    return (s1 == s2) || (s1 && s2 && strcmp(s1, s2) == 0);
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
		ZIHash.set_deleted_key ("");
		ZIHash.erase(key);
		ZIHash.clear_deleted_key();
	}

};

class ZScope
{
public:
	ZHash<ZVar> VarTable;
	ZHash<ZFun> FunTable;
	int id;
	ZScope* Parent;
	
	template<class T> T* lookup(ZChar * key){}

	template<>
	ZVar* lookup<ZVar>(ZChar * key)
	{
		return VarTable.ZIHash[key];
	}

	template<>
	ZFun* lookup<ZFun>(ZChar * key)
	{
		return FunTable.ZIHash[key];
	}
};