#include <google/dense_hash_map>

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

template <class ZHVar,class ZHFun>
class ZScope
{
public:
	ZHash<ZHVar> VarTable;
	ZHash<ZHFun> FunTable;
	int id;
	ZScope* Parent;
	
	template<class T> T* lookup(ZChar * key){}

	template<>
	ZHVar* lookup<ZHVar>(ZChar * key)
	{
		return VarTable.ZIHash[key];
	}

	template<>
	ZHFun* lookup<ZHFun>(ZChar * key)
	{
		return FunTable.ZIHash[key];
	}
};