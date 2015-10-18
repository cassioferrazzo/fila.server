// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ServerMethodsUnit1.h"
#include "TPersisteFila1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
__fastcall TServerMethods1::TServerMethods1(TComponent* Owner)
	: TDataModule(Owner) {
}

// ----------------------------------------------------------------------------
TJSONObject * __fastcall TServerMethods1::requisitarSenha(void) {

	TPersisteFila *pFila = new TPersisteFila;
	try {
		return pFila->requisitarSenha();
	}
	__finally {
		delete pFila;
	}
	return new TJSONObject(new TJSONPair("status", new TJSONNull));
}

// ----------------------------------------------------------------------------
TJSONObject * __fastcall TServerMethods1::chamarProximaSenha(void) {
	TPersisteFila *pFila = new TPersisteFila;
	try {
		return pFila->chamarProximaSenha();
	}
	__finally {
		delete pFila;
	}
	return new TJSONObject(new TJSONPair("status", new TJSONNull));
}

// ----------------------------------------------------------------------------
TJSONObject * __fastcall TServerMethods1::finalizarAtendimento
	(TJSONObject *senha) {

	TPersisteFila *pFila = new TPersisteFila;
	try {
		pFila->finalizarAtendimento(senha);
	}
	__finally {
		delete pFila;
	}
	return new TJSONObject(new TJSONPair("status", new TJSONNull));
}

// ----------------------------------------------------------------------------
TJSONObject * __fastcall TServerMethods1::verificarStatusSenha
	(TJSONObject *senha) {

	TPersisteFila *pFila = new TPersisteFila;
	try {
		return pFila->verificarStatusSenha(senha);
	}
	__finally {
		delete pFila;
	}
	return new TJSONObject(new TJSONPair("status", new TJSONNull));
}

// ----------------------------------------------------------------------------
TJSONArray * __fastcall TServerMethods1::getSenhasAtivas(void) {
	TPersisteFila *pFila = new TPersisteFila;
	try {
		return pFila->getSenhasAtivas();
	}
	__finally {
		delete pFila;
	}
	return new TJSONArray(new TJSONNull);
}
// ----------------------------------------------------------------------------
