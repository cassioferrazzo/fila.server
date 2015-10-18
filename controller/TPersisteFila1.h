// ---------------------------------------------------------------------------

#ifndef TPersisteFila1H
#define TPersisteFila1H

#include <Data.DB.hpp>
#include <FireDAC.Dapt.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.Comp.UI.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.PG.hpp>
#include <FireDAC.Phys.PGDef.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
#include <Data.DBXJSON.hpp>

// ---------------------------------------------------------------------------
class TPersisteFila {
private:
	TFDConnection *conexao;
	TFDQuery *qry;
	TFDTable *tabela;

	TJSONObject *__fastcall inserirSenha(void);
	UnicodeString __fastcall gerarCodigo(int id);
	int __fastcall calcularSenhasNaFrente(UnicodeString codigoSenha);

public:
	__fastcall TPersisteFila(void);
	__fastcall ~TPersisteFila(void);
	TJSONObject *__fastcall requisitarSenha(void);
	void __fastcall finalizarAtendimento(TJSONObject *jsSenha);
	TJSONArray *__fastcall getSenhasAtivas(void);
	void __fastcall cancelarAtendimento(TJSONObject *jsSenha);
	TJSONObject *__fastcall verificarStatusSenha(TJSONObject *jsSenha);
	TJSONObject *__fastcall chamarProximaSenha(void);
};
// ---------------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------------
