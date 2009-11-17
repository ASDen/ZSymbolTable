#ifndef _ZSYMTAB_H_
#define _ZSYMTAB_H_

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
	Data* getSymbol(ZChar * key,bool rec)
	{
		ZTpScope* tmp=ZAlloc(ZTpScope,1);
		tmp=currentScope;
		Data* ret=0;
		do
		{
			if((ret=tmp->lookup<Data>(key))!=0)
				return ret;
			tmp=tmp->Parent;
		}while(rec && tmp!=NULL);

		return ret;
	}
};

#endif