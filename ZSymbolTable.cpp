// ZSymbolTable.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <hash_map>
#include "data.h"
#include "ZSymbolTable.h"


int main()
{
	ZVar zv1=1,zv2=2,zv3=3;
	ZFun zf1=10,zf2=20,zf3=30;
	ZSymbolTable<ZVar> zx;
	zx.InitScope();
	zx.InitScope();
	zx.InsertSymbol("zv1",&zv1);
	zx.InsertSymbol("zv2",&zv2);
	zx.InitScope();
	zx.InitScope();
	/*zx.FinScope();
	zx.FinScope();
	zx.FinScope();*/
	//zx.Jump(2);
	ZVar* zv4=zx.getSymbol("zv1",true);
	if(zv4==NULL)
		std::cout<<"Not Found\n";
	else
		std::cout<<"zv4="<<*zv4<<std::endl;

	zv4=zx.getSymbol("zv1",false);
	if(zv4==NULL)
		std::cout<<"Not Found\n";
	else
		std::cout<<"zv4="<<*zv4<<std::endl;
	zx.FinScope();

	return 0;
}

