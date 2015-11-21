// ---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TPersisteFila1.h"
#include "TSenha1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

// ---------------------------------------------------------------------------
__fastcall TPersisteFila::TPersisteFila(void) {

	conexao = new TFDConnection(NULL);
	conexao->LoginPrompt = false;
	conexao->Params->Add("User_Name=postgres");
	conexao->Params->Add("Password=root");
	conexao->Params->Add("Server=127.0.0.1");
	conexao->Params->Add("DriverID=PG");
	conexao->Params->Add("Database=fila");

	qry = new TFDQuery(NULL);
	qry->CachedUpdates = false;
	qry->Connection = conexao;

	tabela = new TFDTable(NULL);
	tabela->CachedUpdates = false;
	tabela->Connection = conexao;
	tabela->TableName = "tb_fila";
}

// ---------------------------------------------------------------------------
__fastcall TPersisteFila::~TPersisteFila(void) {
	delete conexao;
	delete qry;
	delete tabela;
}

// ---------------------------------------------------------------------------
TJSONObject *__fastcall TPersisteFila::requisitarSenha(void) {

	return inserirSenha();
}

// ---------------------------------------------------------------------------
TJSONObject * __fastcall TPersisteFila::inserirSenha(void) {

	TSenha *senha = new TSenha;
	try {
		senha->data = Now().CurrentDate();
		senha->hora = Now().CurrentTime();
		senha->ativo = true;

		tabela->Open();
		try {
			tabela->Insert();

			tabela->FieldByName("hora")->AsDateTime = senha->hora;
			tabela->FieldByName("data")->AsDateTime = senha->data;
			tabela->FieldByName("ativo")->AsBoolean = senha->ativo;

			tabela->Post();
			tabela->Last();
			senha->id = tabela->FieldByName("id_fila")->AsInteger;
			senha->codigo = gerarCodigo(senha->id);
			senha->senhasNaFrente = calcularSenhasNaFrente(senha->codigo);
		}
		__finally {
			tabela->Unprepare();
			tabela->Close();
		}

		return senha->toJSON();
	}

	__finally {
		delete senha;
	}
}

// ---------------------------------------------------------------------------
UnicodeString __fastcall TPersisteFila::gerarCodigo(int id) {

	UnicodeString codigo = "A" + FormatFloat("0000", id);

	tabela->Edit();
	try {
		tabela->FieldByName("codigo")->AsString = codigo;
	}
	__finally {
		tabela->Post();
	}
	return codigo;
}

// ---------------------------------------------------------------------------
void __fastcall TPersisteFila::cancelarAtendimento(TJSONObject *jsSenha) {

	TSenha *senha = new TSenha;
	try {
		senha->fromJSON(jsSenha);

		tabela->Open();
		try {
			if (tabela->Locate("id_fila", senha->id)) {
				tabela->Edit();
				tabela->FieldByName("ativo")->AsBoolean = false;
				tabela->Post();
			}
		}
		__finally {
			tabela->Unprepare();
			tabela->Close();
		}
	}
	__finally {
		delete senha;
	}

}

// ---------------------------------------------------------------------------
void __fastcall TPersisteFila::finalizarAtendimentoById(int id) {

	tabela->Open();
	try {
		if (tabela->Locate("id_fila", id)) {
			tabela->Edit();
			tabela->FieldByName("ativo")->AsBoolean = false;
			tabela->Post();
		}
	}
	__finally {
		tabela->Unprepare();
		tabela->Close();
	}
}

// ---------------------------------------------------------------------------
void __fastcall TPersisteFila::finalizarAtendimento(TJSONObject *jsSenha) {

	TSenha *senha = new TSenha;
	try {
		senha->fromJSON(jsSenha);

		tabela->Open();
		try {
			if (tabela->Locate("id_fila", senha->id)) {
				tabela->Edit();
				tabela->FieldByName("ativo")->AsBoolean = false;
				tabela->Post();
			}
		}
		__finally {
			tabela->Unprepare();
			tabela->Close();
		}
	}
	__finally {
		delete senha;
	}

}

// ---------------------------------------------------------------------------
TJSONArray *__fastcall TPersisteFila::getSenhasAtivas(void) {

	TJSONArray *jsArraySenhas = new TJSONArray;
	tabela->Open();
	try {
		TSenha *senha;
		tabela->First();
		while (!tabela->Eof) {

			senha = new TSenha;
			senha->id = tabela->FieldByName("id_fila")->AsInteger;
			senha->hora = tabela->FieldByName("hora")->AsDateTime;
			senha->data = tabela->FieldByName("data")->AsDateTime;
			senha->ativo = tabela->FieldByName("ativo")->AsBoolean;
			senha->codigo = tabela->FieldByName("codigo")->AsString;
			tabela->Next();
			if (senha->ativo) {
				jsArraySenhas->AddElement(senha->toJSON());
				continue;
			}
			delete senha;
		}
	}
	__finally {
		tabela->Unprepare();
		tabela->Close();
	}

	return jsArraySenhas;
}

// ---------------------------------------------------------------------------
int __fastcall TPersisteFila::calcularSenhasNaFrente(UnicodeString codigoSenha)
{
	int senhasNaFrente = 0;

	tabela->Open();
	try {
		if (!tabela->Locate("codigo", codigoSenha)) {
			throw Exception("Código de seha não existe.");
		}
	}
	__finally {
		tabela->Unprepare();
		tabela->Close();
	}

	qry->Open("SELECT * FROM tb_fila WHERE ativo = TRUE ORDER BY id_fila");
	try {
		TSenha *senha;
		qry->First();
		while (!qry->Eof) {
			if (qry->FieldByName("codigo")->AsString == codigoSenha) {
				break;
			}
			senhasNaFrente++;
			qry->Next();
		}
	}
	__finally {
		qry->Unprepare();
		qry->Close();
	}

	return senhasNaFrente;
}

// ---------------------------------------------------------------------------
TJSONObject *__fastcall TPersisteFila::verificarStatusSenhaById(int id) {

	TSenha *senha = new TSenha;
	tabela->Open();
	try {
		if (tabela->Locate("id_fila", id)) {
			senha->id = tabela->FieldByName("id_fila")->AsInteger;
			senha->hora = tabela->FieldByName("hora")->AsDateTime;
			senha->data = tabela->FieldByName("data")->AsDateTime;
			senha->ativo = tabela->FieldByName("ativo")->AsBoolean;
			senha->codigo = tabela->FieldByName("codigo")->AsString;
			senha->senhasNaFrente = calcularSenhasNaFrente(senha->codigo);
		}
	}
	__finally {
		tabela->Unprepare();
		tabela->Close();
	}

	return senha->toJSON();
}

// ---------------------------------------------------------------------------
TJSONObject *__fastcall TPersisteFila::verificarStatusSenha
	(TJSONObject *jsSenha) {

	TSenha *senha = new TSenha;
	try {
		senha->fromJSON(jsSenha);
		return verificarStatusSenhaById(senha->id);
	}
	__finally {
		delete senha;
	}
	return NULL;
}

// ---------------------------------------------------------------------------
TJSONObject *__fastcall TPersisteFila::chamarProximaSenha(void) {

	qry->Open("SELECT * FROM tb_fila WHERE ativo = TRUE ORDER BY id_fila");
	try {
		TSenha *senha = new TSenha;
		qry->First();
		senha->id = qry->FieldByName("id_fila")->AsInteger;
		senha->hora = qry->FieldByName("hora")->AsDateTime;
		senha->data = qry->FieldByName("data")->AsDateTime;
		senha->ativo = qry->FieldByName("ativo")->AsBoolean;
		senha->codigo = qry->FieldByName("codigo")->AsString;

		return senha->toJSON();
	}
	__finally {
		qry->Unprepare();
		qry->Close();
	}

	return new TJSONObject(new TJSONPair("status", "sem senhas"));
}
// ---------------------------------------------------------------------------
