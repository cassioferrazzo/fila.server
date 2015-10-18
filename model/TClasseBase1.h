// ---------------------------------------------------------------------------

#ifndef TClasseBase1H
#define TClasseBase1H

#include <Data.DBXJSON.hpp>
#include <Data.DBXJSONReflect.hpp>
#include <System.Rtti.hpp>
#include "TListaGenerica1.h"
#include "TListaGenerica1.cpp"
#pragma explicit_rtti

// ---------------------------------------------------------------------------
enum TipoJSON {
	tjInteger, tjFloat, tjString, tjArray, tjObject, tjBool, tjEnum, tjNULL
};

class __declspec(delphiclass) TClasseBase : public TObject {
private:
	TJSONPair *__fastcall getFloatNumberPair(UnicodeString Nome,
		UnicodeString Valor);
	TJSONPair *__fastcall getNumberPair(UnicodeString Nome,
		UnicodeString Valor);
	TJSONPair *__fastcall getObjectPair(UnicodeString Nome, TClasseBase *Valor);

protected:
	TJSONPair *__fastcall getBoolPair(UnicodeString Nome, bool Valor);
	TJSONPair *__fastcall getStringPair(UnicodeString Nome,
		UnicodeString Valor);

	virtual void __fastcall fromJSON(TJSONObject *Value);

public:
	__fastcall TClasseBase(void);
	__fastcall virtual ~TClasseBase(void);
	virtual TJSONObject *__fastcall toJSON(void);
	TipoJSON __fastcall getJSONValueByType(System::Typinfo::TTypeKind TypeKind);

	void __fastcall virtual clonar(TClasseBase *clone);
};
// ---------------------------------------------------------------------------
#endif
