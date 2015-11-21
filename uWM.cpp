
//---------------------------------------------------------------------------
#include "uWM.h"
#include "uSM.h"
#include <Web.WebReq.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TComponentClass WebModuleClass = __classid(TWM);
//---------------------------------------------------------------------------
__fastcall TWM::TWM(TComponent* Owner)
	: TWebModule(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TWM::DSServerClass1GetClass(TDSServerClass *DSServerClass,
          TPersistentClass &PersistentClass)
{
	PersistentClass =  __classid(TSM);
}
//----------------------------------------------------------------------------
void __fastcall TWM::ServerFunctionInvokerHTMLTag(TObject *Sender, TTag Tag,
          const UnicodeString TagString, TStrings *TagParams, UnicodeString &ReplaceText)

{
	if (SameText(TagString, "urlpath"))
		ReplaceText = (Request->InternalScriptName);
	else if (SameText(TagString, "port"))
		ReplaceText = IntToStr(Request->ServerPort);
	else if (SameText(TagString, "host"))
		ReplaceText = (Request->Host);
	else if (SameText(TagString, "classname"))
		ReplaceText = __classid(TSM)->ClassName();
	else if (SameText(TagString, "loginrequired"))
	{
		if (DSHTTPWebDispatcher1->AuthenticationManager != NULL)
			ReplaceText = "true";
		else
			ReplaceText = "false";
	}
	else if (SameText(TagString, "serverfunctionsjs"))
		ReplaceText = Request->InternalScriptName + "/js/serverfunctions.js";
	else if (SameText(TagString, "servertime"))
		ReplaceText = DateTimeToStr(Now());
	else if  (SameText(TagString, "serverfunctioninvoker"))
	{
		if (AllowServerFunctionInvoker())
			ReplaceText =
			"<div><a href='" + Request->InternalScriptName +
			"/ServerFunctionInvoker' target='_blank'>Server Functions</a></div>";
	}
	else
		ReplaceText = "";
}
//---------------------------------------------------------------------------
void __fastcall TWM::WebModuleDefaultAction(TObject *Sender, TWebRequest *Request,
		  TWebResponse *Response, bool &Handled)
{
  if (Request->InternalPathInfo == "" || Request->InternalPathInfo == "/")
	Response->Content = ServerFunctionInvoker->Content();
  else
	Response->SendRedirect(Request->InternalScriptName + "/");
}
//---------------------------------------------------------------------------
void __fastcall TWM::WebModuleBeforeDispatch(TObject *Sender, TWebRequest *Request,
          TWebResponse *Response, bool &Handled)
{
	if (FServerFunctionInvokerAction != NULL)
	{
		FServerFunctionInvokerAction->Enabled = AllowServerFunctionInvoker();
	}
}
//---------------------------------------------------------------------------
bool __fastcall TWM::AllowServerFunctionInvoker(void)
{
	return Request->RemoteAddr == "127.0.0.1" ||
		Request->RemoteAddr == "0:0:0:0:0:0:0:1" || Request->RemoteAddr == "::1";
}
//---------------------------------------------------------------------------
void __fastcall TWM::WebFileDispatcher1BeforeDispatch(TObject *Sender, const UnicodeString AFileName,
          TWebRequest *Request, TWebResponse *Response, bool &Handled)

{
	Handled = False;
	if (SameFileName(ExtractFileName(AFileName), "serverfunctions.js"))
	{
		TDateTime D1, D2;
		if (FileAge(AFileName, D1) && FileAge(WebApplicationFileName(), D2) && (D1 < D2))
		{
			DSProxyGenerator1->TargetDirectory = ExtractFilePath(AFileName);
			DSProxyGenerator1->TargetUnitName = ExtractFileName(AFileName);
			DSProxyGenerator1->Write();
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TWM::WebModuleCreate(TObject *Sender)
{
	FServerFunctionInvokerAction = ActionByName("ServerFunctionInvokerAction");
}

//---------------------------------------------------------------------------
static void freeWebModules()
{
	FreeWebModules();
}
#pragma exit freeWebModules 33

