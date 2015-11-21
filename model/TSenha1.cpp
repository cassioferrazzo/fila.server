// ---------------------------------------------------------------------------

#pragma hdrstop

#include "TSenha1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
// ---------------------------------------------------------------------------
void __fastcall TSenha::fromJSON(TJSONObject *Value) {

	TClasseBase::fromJSON(Value);
	TRttiType *typRtti;
	TRttiContext *ctxRtti = new TRttiContext;
	TRttiProperty *propriedade;
	System::DynamicArray<TRttiProperty*>Propriedades;
	TJSONArray *jsArray;
	TJSONObject *objTmp;
	TJSONValue *jsPropriedade;
	try {
		typRtti = ctxRtti->GetType(this->ClassType());
		Propriedades = typRtti->GetProperties();

		for (int i = 0; i < Propriedades.get_length(); i++) {
			propriedade = Propriedades[i];

			if (propriedade->Name == "data") {
				data = StrToDate(Value->GetValue("data")->Value());
			}
			if (propriedade->Name == "hora") {
				hora = StrToTime(Value->GetValue("hora")->Value());
			}
			if (propriedade->Name == "ativo") {
				if (Value->GetValue(propriedade->Name) == "true") {
					ativo = true;
				}
				else {
					ativo = false;
				}
			}
		}
	}
	__finally {
		delete ctxRtti;
	}
}
// ---------------------------------------------------------------------------
TJSONObject *__fastcall TSenha::toJSON(void) {

	TRttiContext *ctxRtti;
	TRttiType *typRtti;
	TJSONObject *retorno = (TJSONObject*)TClasseBase::toJSON();
	TRttiProperty *propriedade;

	try {
		ctxRtti = new TRttiContext;
		typRtti = ctxRtti->GetType(this->ClassType());
		System::DynamicArray<TRttiProperty*>Propriedades =
			typRtti->GetProperties();
		for (int i = 0; i < Propriedades.get_length(); i++) {
			propriedade = Propriedades[i];
			if (propriedade->Name == "data") {
				retorno->RemovePair(propriedade->Name);
				retorno->AddPair(getStringPair(propriedade->Name,
					data.DateString()));
			}
			if (propriedade->Name == "hora") {
				retorno->RemovePair(propriedade->Name);
				retorno->AddPair(getStringPair(propriedade->Name,
					hora.TimeString()));
			}
			if (propriedade->Name == "ativo") {
				retorno->AddPair(getBoolPair(propriedade->Name, ativo));
			}
		}
	}
	__finally {
		delete ctxRtti;
	}
	return (retorno);
}
// ---------------------------------------------------------------------------
