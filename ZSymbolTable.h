#ifndef _ZSYMTAB_H_
#define _ZSYMTAB_H_

#include "hash_table.h"

template <class ZHVar>
class ZSymbolTable
{
public:
	typedef ZScope<ZHVar> ZTpScope;

	dense_hash_map < int , ZTpScope*  > Scopes;
	ZTpScope* currentScope;
	int cid;

	ZSymbolTable():cid(0)
	{
		Scopes.set_empty_key(cid++);
		currentScope=NULL;
		InitScope();
	}

	void InitScope()
	{
		ZTpScope* zs=new ZTpScope();
		Scopes[cid++]=zs;
		zs->id=cid;
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

	ZHVar* getSymbol(ZChar * key,bool rec)
	{
		ZTpScope* tmp=ZAlloc(ZTpScope,1);
		tmp=currentScope;
		ZHVar* ret=0;
		do
		{
			if((ret=tmp->lookup(key))!=0)
				return ret;
			tmp=tmp->Parent;
		}while(rec && tmp!=NULL);

		return ret;
	}

	void InsertSymbol(ZChar * key,ZHVar* var)
	{
		currentScope->VarTable.Insert(var,key);
	}
};

#endif