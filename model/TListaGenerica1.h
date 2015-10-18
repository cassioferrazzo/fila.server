//---------------------------------------------------------------------------

#ifndef TListaGenerica1H
#define TListaGenerica1H

//---------------------------------------------------------------------------
template < class T >
class TListaGenerica
{
private:
	TList *lista;

	T *__fastcall getItems(int Index);
	void __fastcall setCount(int Count);
	int __fastcall getCount(void);
	void __fastcall putItems(int Index, T *obj);

public:
	__fastcall TListaGenerica(void);
	__fastcall ~ TListaGenerica(void);
	int __fastcall Add(T *Item);
	void __fastcall Insert(int Index, T *Item);
	void __fastcall Delete(int index);
	void __fastcall Clear(void);

	__property T *Items[int Index] =
	{
		read = getItems,
		write = putItems
	};
	__property int Count =
	{
		read = getCount,
		write = setCount
	};
};
//---------------------------------------------------------------------------
#endif
