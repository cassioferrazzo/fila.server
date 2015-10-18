// ---------------------------------------------------------------------------

#ifndef ServerMethodsUnit1H
#define ServerMethodsUnit1H
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <DataSnap.DSServer.hpp>
#include <Datasnap.DSProviderDataModuleAdapter.hpp>

// ---------------------------------------------------------------------------
class DECLSPEC_DRTTI TServerMethods1 : public TDataModule {
__published: // IDE-managed Components
		private : // User declarations
	public : // User declarations
		__fastcall TServerMethods1(TComponent* Owner);
	TJSONObject * __fastcall requisitarSenha(void);
	TJSONObject * __fastcall chamarProximaSenha(void);
	TJSONObject * __fastcall finalizarAtendimento(TJSONObject *senha);
	TJSONObject * __fastcall verificarStatusSenha(TJSONObject *senha);
	TJSONArray * __fastcall getSenhasAtivas(void);
};

// ---------------------------------------------------------------------------
extern PACKAGE TServerMethods1 *ServerMethods1;
// ---------------------------------------------------------------------------
#endif
