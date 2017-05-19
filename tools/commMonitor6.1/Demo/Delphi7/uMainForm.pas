unit uMainForm;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, OleCtrls, CommMonitor6x_TLB, StdCtrls, ComCtrls, ExtCtrls,
  Buttons;

type
  TfrmMainForm = class(TForm)
    CommMonitor1: TCommMonitor;
    redtData: TRichEdit;
    stat1: TStatusBar;
    redtCtl: TRichEdit;
    spl1: TSplitter;
    btn1: TBitBtn;
    btn2: TBitBtn;
    btnOpen: TBitBtn;
    btnPause: TBitBtn;
    btn3: TButton;
    cbb1: TComboBox;
    procedure CommMonitor1Monitor(ASender: TObject;
      const sPortName: WideString; dwCtrlCode, dwPID: Integer;
      var vtData: OleVariant; dwSize: Integer);
    procedure btnOpenClick(Sender: TObject);
    procedure btnPauseClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure btn1Click(Sender: TObject);
    procedure btn3Click(Sender: TObject);
    procedure CommMonitor1Ascii(ASender: TObject;
      const sPortName: WideString; dwCtrlCode, dwPID: Integer;
      const sData: WideString; dwSize: Integer);
    procedure FormDestroy(Sender: TObject);
  private
    { Private declarations }
 
    fTotalWrite: DWORD;
    fTotalRead: DWORD;
    fActive: Boolean;
    fPause: Boolean;
    procedure AddLog(redt: TRichEdit;  AColor: TColor; const Msg: string);
  public
    { Public declarations }
  end;

var
  frmMainForm: TfrmMainForm;

implementation

{$R *.dfm}
 

const
  IRP_MJ_CREATE                   =$00;
  IRP_MJ_CLOSE                    =$02;
  IRP_MJ_READ                     =$03;
  IRP_MJ_WRITE                    =$04;
  IRP_MJ_DEVICE_CONTROL           =$0E;
  IRP_MJ_CLEANUP                  =$12;
  IRP_MJ_MAXIMUM_FUNCTION         =$1B;
  IRP_MJ_FLUSH_BUFFERS            =$09;
  
 

procedure TfrmMainForm.CommMonitor1Monitor(ASender: TObject;
  const sPortName: WideString; dwCtrlCode, dwPID: Integer;
  var vtData: OleVariant; dwSize: Integer);
begin
   //vtData bin data
end;

procedure TfrmMainForm.btnOpenClick(Sender: TObject);
begin
  if not fActive then
    fActive := self.CommMonitor1.StartMonitor(self.cbb1.Text)
  else
  begin
    CommMonitor1.StopMonitor;
    fActive := False;
  end;

   if fActive then
   begin
     btnOpen.Caption := 'Stop Monitor';
     btnOpen.Font.Color := clBlue;
     
   end
   else
   begin
     btnOpen.Caption := 'Start Monitor';
     btnOpen.Font.Color := clBlack;
   end;
end;

procedure TfrmMainForm.btnPauseClick(Sender: TObject);
begin
  if CommMonitor1.PauseMonitor(fPause) then
     fPause := not fPause;
     
  if fPause then
  begin
    btnPause.Caption := 'Continue';
    btnPause.Font.Color := clBlack;
  end
  else
  begin
    btnPause.Caption := 'Pause';
    btnPause.Font.Color := clBlue;
  end;
end;

procedure TfrmMainForm.FormCreate(Sender: TObject);
begin
  Caption :='CommMonitor for Delphi 7 Demo';
  self.redtData.Clear;
  self.redtCtl.Clear;  
  fPause := False;
  fActive := False;
end;

procedure TfrmMainForm.AddLog(redt: TRichEdit; AColor: TColor;
  const Msg: string);
begin
  try
    if redt.Lines.Count >= 10000 then redt.Clear;
    redt.SelAttributes.Color := AColor;

    if redt.Lines.Count = 0 then
       redt.SelText := Msg
    else
    begin
      {if cbx_AutoReturn.Checked then
        redt.SelText := #13#10+Msg
      else
      }
        redt.SelText := #13#10+Msg;
    end;
  except
  end;
end;

procedure TfrmMainForm.btn1Click(Sender: TObject);
begin
  self.redtData.Clear;
  self.redtCtl.Clear;
end;

procedure TfrmMainForm.btn3Click(Sender: TObject);
begin
  self.CommMonitor1.AboutBox;
end;

procedure TfrmMainForm.CommMonitor1Ascii(ASender: TObject;
  const sPortName: WideString; dwCtrlCode, dwPID: Integer;
  const sData: WideString; dwSize: Integer);
begin
    case dwCtrlCode of
      IRP_MJ_WRITE: begin
         Inc(fTotalWrite, dwSize);
         AddLog( redtData, clGreen,  Format('%s(%d): %s', [sPortName, dwSize, sData]));
         end;
      IRP_MJ_READ:  begin
        Inc(fTotalRead, dwSize);
        AddLog( redtData, clBlue, Format('%s(%d): %s', [sPortName, dwSize, sData]));
      end;
      IRP_MJ_CLOSE:  AddLog( redtData, clBlue, Format('%s: Close', [sPortName]));
      IRP_MJ_CREATE: AddLog( redtData, clBlue, Format('%s: Open', [sPortName]));
      else if dwCtrlCode > $400 then
         begin
            redtCtl.Tag  := redtCtl.Tag + 1;
            if redtCtl.Tag mod 2 = 0 then
              AddLog( redtCtl, clBlue, sData)
            else  AddLog( redtCtl, clGreen, sData)
      end;
    end;

  if dwCtrlCode in [IRP_MJ_WRITE, IRP_MJ_READ] then
    self.stat1.Panels[0].Text := Format('Write: %u(Bytes)|Read: %u(Bytes)', [fTotalWrite, fTotalRead])
end;

procedure TfrmMainForm.FormDestroy(Sender: TObject);
begin
  if fActive then self.CommMonitor1.StopMonitor;
end;

end.
