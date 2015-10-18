//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TClasseBase1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TClasseBase::TClasseBase(void)
{

}
	//---------------------------------------------------------------------------
__fastcall TClasseBase::~ TClasseBase(void)
{

}
//---------------------------------------------------------------------------
TJSONObject *__fastcall TClasseBase::toJSON(void)
{
	TRttiContext *ctxRtti;
	TRttiType *typRtti;
	TJSONObject *retorno;
	TRttiProperty *propriedade;
	System::DynamicArray < TRttiProperty * > Propriedades;
	TipoJSON tipo;
	TObject *Obj;
	try
	{
		retorno = new TJSONObject;

		ctxRtti = new TRttiContext;
		typRtti = ctxRtti->GetType(this->ClassType());
		Propriedades = typRtti->GetProperties();
		for(int i = 0; i < Propriedades.get_length(); i++)
		{
			propriedade = Propriedades[i];
			tipo = getJSONValueByType(propriedade->PropertyType->TypeKind);

			if(tipo == tjInteger)
			{
				retorno->AddPair(getNumberPair(propriedade->Name,
						propriedade->GetValue(this).ToString()));
			}
			else if(tipo == tjFloat)
			{
				retorno->AddPair(getFloatNumberPair(propriedade->Name,
						propriedade->GetValue(this).ToString()));
			}
			else if(tipo == tjString)
			{
				retorno->AddPair(getStringPair(propriedade->Name,
						propriedade->GetValue(this).ToString()));
			}
			else if(tipo == tjBool)
			{
				retorno->AddPair(getBoolPair(propriedade->Name,
						propriedade->GetValue(this).AsType < bool > ()));
			}
			else if(tipo == tjObject)
			{
				Obj = propriedade->GetValue(this).AsObject();
				if(Obj != NULL)
				{
					if(Obj->InheritsFrom(__classid(TClasseBase)))
					{
						retorno->AddPair(getObjectPair(propriedade->Name,
								(TClasseBase *)Obj));
					}
				}
			}
		}
	}
	__finally
	{
		delete ctxRtti;
	}
	return (retorno);
}
//---------------------------------------------------------------------------
void __fastcall TClasseBase::fromJSON(TJSONObject *Value)
{
	TipoJSON tipo;
	TRttiType *typRtti;
	TRttiContext *ctxRtti;
	TRttiProperty *propriedade;
	System::DynamicArray < TRttiProperty * > Propriedades;
	TValue valor;
	TJSONUnMarshal *Conversor;
	UnicodeString valorStr;
	TJSONValue *jsPropriedade;
	try
	{
		ctxRtti = new TRttiContext;
		Conversor = new TJSONUnMarshal();

		typRtti = ctxRtti->GetType(this->ClassType());
		Propriedades = typRtti->GetProperties();
		for(int i = 0; i < Propriedades.get_length(); i++)
		{
			propriedade = Propriedades[i];
			tipo = getJSONValueByType(propriedade->PropertyType->TypeKind);
			jsPropriedade = Value->GetValue(propriedade->Name);
			if(tipo != tjObject)
			{
				if(tipo == tjInteger)
				{
					valor = TValue::From < int > (StrToIntDef(jsPropriedade->Value(), 0));
					propriedade->SetValue(this, valor);
				}
				if(tipo == tjFloat)
				{
					valor = TValue::From < double >
						(StrToFloatDef(jsPropriedade->Value(), 0));
					propriedade->SetValue(this, valor);
				}
				if(tipo == tjString)
				{
					valor = TValue::From < UnicodeString > (jsPropriedade->Value());
					propriedade->SetValue(this, valor);
				}
				if(tipo == tjBool)
				{
					propriedade->SetValue(this, valor);
				}

			}

		}

	}
	__finally
	{
		delete ctxRtti;
		delete Conversor;
	}

}
//---------------------------------------------------------------------------
TJSONPair *__fastcall TClasseBase::getFloatNumberPair(UnicodeString Nome,
	UnicodeString Valor)
{
	double val = StrToFloatDef(Valor.SubString(1, 5), 0);
	return new TJSONPair(Nome, new System::Json::TJSONNumber(val));
}
//---------------------------------------------------------------------------
TJSONPair *__fastcall TClasseBase::getNumberPair(UnicodeString Nome,
	UnicodeString Valor)
{
	return new TJSONPair(Nome, new TJSONNumber(StrToIntDef(Valor, 0)));
}
//---------------------------------------------------------------------------
TJSONPair *__fastcall TClasseBase::getStringPair(UnicodeString Nome,
	UnicodeString Valor)
{
	return new TJSONPair(Nome, Valor);
}
//---------------------------------------------------------------------------
TJSONPair *__fastcall TClasseBase::getObjectPair(UnicodeString Nome,
	TClasseBase *Valor)
{
	TJSONObject *jsObj = Valor->toJSON();
	return new TJSONPair(Nome, jsObj);
}
//---------------------------------------------------------------------------
TJSONPair *__fastcall TClasseBase::getBoolPair(UnicodeString Nome, bool Valor)
{
	if(Valor)
	{
		return new TJSONPair(Nome, new TJSONTrue());
	}
	return new TJSONPair(Nome, new TJSONFalse());
}
//---------------------------------------------------------------------------
TipoJSON __fastcall TClasseBase::getJSONValueByType
	(System::Typinfo::TTypeKind TypeKind)
{
	if(TypeKind == tkInteger || TypeKind == tkInt64)
	{
		return (tjInteger);
	}
	else if(TypeKind == tkFloat)
	{
		return (tjFloat);
	}
	else if(TypeKind == tkWChar || TypeKind == tkString ||
		TypeKind == tkWString || TypeKind == tkLString || TypeKind == tkUString)
	{
		return (tjString);
	}
	else if(TypeKind == tkDynArray || TypeKind == tkArray || TypeKind == tkRecord)
	{
		return (tjArray);
	}
	else if(TypeKind == tkClass || TypeKind == tkPointer)
	{
		return (tjObject);
	}
	else if(TypeKind == tkChar)
	{
		return (tjBool);
	}
	else if(TypeKind == tkEnumeration)
	{
		return (tjEnum);
	}

	return (tjNULL);
}
//---------------------------------------------------------------------------
void __fastcall TClasseBase::clonar(TClasseBase *clone)
{
	clone->fromJSON(this->toJSON());
}
//---------------------------------------------------------------------------
