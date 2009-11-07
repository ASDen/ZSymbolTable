#include "hash_table.h"

template <class ZHVar,class ZHFun>
class ZSymbolTable
{
public:
	typedef ZScope<ZHVar,ZHFun> ZTpScope;

	dense_hash_map < int , ZTpScope*  > Scopes;
	ZTpScope* currentScope;
	int cid;

	ZSymbolTable():cid(0)
	{
		Scopes.set_empty_key(cid++);
		currentScope=NULL;
	}

	void InitScope()
	{
		ZTpScope* zs=new ZTpScope();
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
		ZTpScope*js;
		if((js = Scopes[id])!=NULL)
			currentScope=js;
	}

	template <class Data>
	Data* getSymbol(ZChar * key)
	{
		ZTpScope* tmp=currentScope;
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