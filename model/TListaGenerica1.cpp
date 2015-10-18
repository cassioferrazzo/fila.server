//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TListaGenerica1.h"
//---------------------------------------------------------------------------
template < class T >
__fastcall TListaGenerica < T > ::TListaGenerica(void)
{
	lista = new TList;
}
//---------------------------------------------------------------------------
template < class T >
__fastcall TListaGenerica < T > ::~ TListaGenerica(void)
{
	Clear();
	delete lista;
}
//---------------------------------------------------------------------------
template < class T >
T *__fastcall TListaGenerica < T > ::getItems(int Index)
{
	return (T *)lista->Items[Index];
}
//---------------------------------------------------------------------------
template < class T >
void __fastcall TListaGenerica < T > ::putItems(int Index, T *obj)
{
	lista->Items[Index] = obj;
}
//---------------------------------------------------------------------------
template < class T >
int __fastcall TListaGenerica < T > ::getCount(void)
{
	return lista->Count;
}
//---------------------------------------------------------------------------
template < class T >
void __fastcall TListaGenerica < T > ::setCount(int Count)
{
	lista->Count = Count;
}
//---------------------------------------------------------------------------
template < class T >
int __fastcall TListaGenerica < T > ::Add(T *Item)
{
	lista->Add(Item);
	return lista->Count - 1;
}
//---------------------------------------------------------------------------
template < class T >
void __fastcall TListaGenerica < T > ::Insert(int Index, T *Item)
{
	lista->Insert(Index, Item);
}
//---------------------------------------------------------------------------
template < class T >
void __fastcall TListaGenerica < T > ::Delete(int index)
{
	delete(T *) lista->Items[index];
	lista->Delete(index);
}
//---------------------------------------------------------------------------
template < class T >
void __fastcall TListaGenerica < T > ::Clear(void)
{
	while(lista->Count > 0)
	{
		Delete(0);
	}
	lista->Clear();
}
//---------------------------------------------------------------------------
