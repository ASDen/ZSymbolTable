#include "hash_table.h"
class ZSymbolTable
{
public:
	dense_hash_map < int , ZScope*  > Scopes;
	ZScope* currentScope;
	int cid;

	ZSymbolTable():cid(0)
	{
		Scopes.set_empty_key(cid++);
		currentScope=NULL;
	}

	void InitScope()
	{
		ZScope* zs=new ZScope();
		Scopes[cid++]=zs;
		zs->id;
		zs->Parent=currentScope;
		currentScope=zs;
	}

	void FinScope()
	{
		currentScope=currentScope->Parent;
	}

	void Jump(int id)
	{
		ZScope*js;
		if((js = Scopes[id])!=NULL)
			currentScope=js;
	}

	template <class Data>
	Data* getSymbol(ZChar * key)
	{
		ZScope* tmp=currentScope;
		//Data def=Data();
		Data* ret;
		while(tmp!=NULL)
		{
			if((ret=tmp->lookup<Data>(key))!=NULL)
				return ret;
			tmp=tmp->Parent;
		}
		return ret;
	}
};