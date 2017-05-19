//---------------------------------------------------------------------------

#ifndef cMainFormH
#define cMainFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "CommMonitor6x_OCX.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.OleCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TSplitter *spl1;
	TCommMonitor *CommMonitor1;
	TBitBtn *btn1;
	TBitBtn *btn2;
	TBitBtn *btnOpen;
	TBitBtn *btnPause;
	TButton *btn3;
	TComboBox *cbb1;
	TRichEdit *redtData;
	TStatusBar *stat1;
	TRichEdit *redtCtl;
	void __fastcall btn3Click(TObject *Sender);
	void __fastcall btn1Click(TObject *Sender);
	void __fastcall btnPauseClick(TObject *Sender);
	void __fastcall btnOpenClick(TObject *Sender);
	void __fastcall CommMonitor1Monitor(TObject *Sender, BSTR sPortName, long dwCtrlCode,
          long dwPID, Variant *vtData, long dwSize);
	void __fastcall CommMonitor1Ascii(TObject *Sender, BSTR sPortName, long dwCtrlCode,
          long dwPID, BSTR sData, long dwSize);
private:	// User declarations
   void __fastcall UpdateLog(TRichEdit *redt, String msg, TColor AColor);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
