// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uSM.h"
#include "TPersisteFila1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

// ---------------------------------------------------------------------------
__fastcall TSM::TSM(TComponent* Owner) : TDataModule(Owner) {
}

// ----------------------------------------------------------------------------
TJSONObject * __fastcall TSM::requisitarSenha(void) {

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
TJSONObject * __fastcall TSM::chamarProximaSenha(void) {
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
TJSONObject * __fastcall TSM::finalizarAtendimento(TJSONObject *senha) {

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
void __fastcall TSM::finalizarAtendimentoById(int id)
{
	TPersisteFila *pFila = new TPersisteFila;
	try {
		pFila->finalizarAtendimentoById(id);
	}
	__finally {
		delete pFila;
	}
}
// ----------------------------------------------------------------------------
TJSONObject * __fastcall TSM::verificarStatusSenhaById(int id) {

	TPersisteFila *pFila = new TPersisteFila;
	try {
		return pFila->verificarStatusSenhaById(id);
	}
	__finally {
		delete pFila;
	}
	return new TJSONObject(new TJSONPair("status", new TJSONNull));
}

// ----------------------------------------------------------------------------
TJSONObject * __fastcall TSM::verificarStatusSenha(TJSONObject *senha) {

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
TJSONArray * __fastcall TSM::getSenhasAtivas(void) {
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
