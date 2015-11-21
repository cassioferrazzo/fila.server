// ---------------------------------------------------------------------------

#ifndef uSMH
#define uSMH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <DataSnap.DSServer.hpp>
#include <Datasnap.DSProviderDataModuleAdapter.hpp>

// ---------------------------------------------------------------------------
class DECLSPEC_DRTTI TSM : public TDataModule {
__published: // IDE-managed Components
		private : // User declarations
	public : // User declarations
		__fastcall TSM(TComponent* Owner);
	TJSONObject * __fastcall requisitarSenha(void);
	TJSONObject * __fastcall chamarProximaSenha(void);
	TJSONObject * __fastcall finalizarAtendimento(TJSONObject *senha);
	void __fastcall finalizarAtendimentoById(int id);
	TJSONObject * __fastcall verificarStatusSenha(TJSONObject *senha);
	TJSONArray * __fastcall getSenhasAtivas(void);
	TJSONObject * __fastcall verificarStatusSenhaById(int id);
};

// ---------------------------------------------------------------------------
extern PACKAGE TSM *SM;
// ---------------------------------------------------------------------------
#endif
