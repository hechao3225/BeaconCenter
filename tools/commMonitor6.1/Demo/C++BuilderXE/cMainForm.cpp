//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "cMainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CommMonitor6x_OCX"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
  redtData->Clear();
  redtCtl->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btn3Click(TObject *Sender)
{
  this->CommMonitor1->AboutBox();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn1Click(TObject *Sender)
{
  this->redtCtl->Clear();
  this->redtData->Clear();
}


DWORD   IRP_MJ_CREATE                   =  0x00;
DWORD   IRP_MJ_CLOSE                    =0x02;
DWORD   IRP_MJ_READ                     =0x03;
DWORD   IRP_MJ_WRITE                   = 0x04;
DWORD   IRP_MJ_DEVICE_CONTROL          =  0x0E;
DWORD   IRP_MJ_CLEANUP                 =  0x12;
DWORD   IRP_MJ_MAXIMUM_FUNCTION        = 0x1B;
DWORD   IRP_MJ_FLUSH_BUFFERS           = 0x09;


   DWORD fTotalWrite = 0;
   DWORD fTotalRead = 0;
   Boolean fActive = false ;
   Boolean fPause = false;
//---------------------------------------------------------------------------
void __fastcall TForm1::btnPauseClick(TObject *Sender)
{
  if (CommMonitor1->PauseMonitor(fPause))
     fPause = !fPause;

  if (fPause)
  {
	btnPause->Caption = "Continue";
	btnPause->Font->Color = clBlack;
  }
  else
  {
	btnPause->Caption = "Pause";
	btnPause->Font->Color = clBlue;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnOpenClick(TObject *Sender)
{
  WideString sComPort =   cbb1->Text.Trim().w_str();

  if (!fActive)
	fActive = CommMonitor1->StartMonitor((wchar_t*)sComPort);
  else
  {
	CommMonitor1->StopMonitor();
    fActive = False;
  }

   if (fActive)
   {
	 btnOpen->Caption = "Stop Monitor";
	 btnOpen->Font->Color = clBlue;

   }
   else
   {
	 btnOpen->Caption = "Start Monitor";
	 btnOpen->Font->Color = clBlack;
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CommMonitor1Monitor(TObject *Sender, BSTR sPortName, long dwCtrlCode,
          long dwPID, Variant *vtData, long dwSize)
{
  // DO Bin data
}
//---------------------------------------------------------------------------

void __fastcall TForm1::UpdateLog(TRichEdit *redt, String msg, TColor AColor)
{
    if (redt->Lines->Count >= 10000) redt->Clear();
	redt->SelAttributes->Color = AColor;

	if (redt->Lines->Count == 0)
	   redt->SelText = msg;
	else
		redt->SelText = msg;

}

void __fastcall TForm1::CommMonitor1Ascii(TObject *Sender, BSTR sPortName, long dwCtrlCode,
		  long dwPID, BSTR sData, long dwSize)
{

	if (dwCtrlCode == IRP_MJ_WRITE){
		 fTotalWrite += dwSize;
		 UpdateLog( redtData, Format("%s(%d): %s\r\n", ARRAYOFCONST((sPortName, dwSize, sData))), clGreen);

	}
	else if (dwCtrlCode == IRP_MJ_READ) {

        fTotalRead += dwSize;
		UpdateLog(redtData , Format("%s(%d): %s\r\n", ARRAYOFCONST((sPortName, dwSize, sData))), clBlue) ;
	}
	else if ( dwCtrlCode == IRP_MJ_CLOSE )
	  UpdateLog( redtData, Format("%s: Close\r\n", ARRAYOFCONST((sPortName))), clBlack);
	else if (dwCtrlCode==IRP_MJ_CREATE)
	  UpdateLog( redtData, Format("%s: Open\r\n", ARRAYOFCONST((sPortName))), clBlack);
	else if (dwCtrlCode > 0x400 )
	{
			redtCtl->Tag  = redtCtl->Tag + 1;
            if ((redtCtl->Tag % 2) == 0)
			   UpdateLog( redtCtl, Format("%s\r\n", ARRAYOFCONST((sData))), clGreen);
			else
			  UpdateLog( redtCtl, Format("%s\r\n", ARRAYOFCONST((sData))), clBlue);

	}
  if ((dwCtrlCode == IRP_MJ_WRITE) || (dwCtrlCode == IRP_MJ_READ))
  stat1->Panels->Items[0]->Text =
	 Format("Write: %u(Bytes)|Read: %u(Bytes)", ARRAYOFCONST((fTotalWrite, fTotalRead)));
}


//---------------------------------------------------------------------------
