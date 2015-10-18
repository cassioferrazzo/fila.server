// ---------------------------------------------------------------------------

#ifndef TSenha1H
#define TSenha1H

#include "TClasseBase1.h"

// ---------------------------------------------------------------------------
class TSenha : public TClasseBase {
public:
	TJSONObject *__fastcall toJSON(void);
	void __fastcall TSenha::fromJSON(TJSONObject *Value);

	__property TDate data = {read = fData, write = fData};
	__property TDate hora = {read = fHora, write = fHora};
	__property UnicodeString codigo = {read = fCodigo, write = fCodigo};
	__property bool ativo = {read = fAtivo, write = fAtivo, default = false};
	__property int id = {read = fId, write = fId};
	__property int senhasNaFrente = {
		read = fSenhasNaFrente, write = fSenhasNaFrente, default = 0};

private:
	int fId;
	int fSenhasNaFrente;
	TDate fData;
	TTime fHora;
	UnicodeString fCodigo;
	bool fAtivo;
};
// ---------------------------------------------------------------------------
#endif
// ---------------------------------------------------------------------------
