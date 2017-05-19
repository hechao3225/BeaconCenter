//ComObj

unit uMainForm;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, OleCtrls, D7Com_TLB, uEventObj,
  ExtCtrls, ComCtrls, Buttons;

type

  TfmOleObj = class(TForm)
    pnl1: TPanel;
    stat1: TStatusBar;
    redtData: TRichEdit;
    spl1: TSplitter;
    redtCtl: TRichEdit;
    cbb1: TComboBox;
    btnOpen: TBitBtn;
    btnPause: TBitBtn;
    btn1: TBitBtn;
    btn3: TButton;
    btn2: TBitBtn;
    procedure btnOpenClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure btnPauseClick(Sender: TObject);
    procedure btn3Click(Sender: TObject);
    procedure btn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    FEvent: TEventObj;
    procedure AddLog(redt: TRichEdit;  AColor: TColor; const Msg: string);
    procedure OnAscii(const sPortName: WideString; dwCtrlCode, dwPID: Integer;
      const sData: WideString; dwSize: Integer); 
  end;

var
  fmOleObj: TfmOleObj;
  //DIID_ICommMonitor6Events: TGUID = '{2E50E334-3D45-4743-A090-59CF4C04D8F3}';
  FEventIID: TGUID = '{2E50E334-3D45-4743-A090-59CF4C04D8F3}';

  
implementation

uses
  ComObj;

{$R *.dfm}

const
  IRP_MJ_CREATE                   =$00;
  IRP_MJ_CLOSE                    =$02;
  IRP_MJ_READ                     =$03;
  IRP_MJ_WRITE                    =$04;
  IRP_MJ_DEVICE_CONTROL           =$0E;
  IRP_MJ_CLEANUP                  =$12;
 


  

var
  vCommMonitor: OleVariant;
  fActive: Boolean = false;
  fPause: Boolean = False;
  FConnection:Integer = 0;
  fTotalWrite: DWORD = 0;
  fTotalRead: DWORD = 0;


procedure TfmOleObj.btnOpenClick(Sender: TObject);
begin
  if not VarIsEmpty(vCommMonitor) then
  begin
     if not fActive then
        fActive := vCommMonitor.StartMonitor(self.cbb1.Text)
     else
     begin
        vCommMonitor.StopMonitor;
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
end;

procedure TfmOleObj.OnAscii(const sPortName: WideString; dwCtrlCode,
  dwPID: Integer; const sData: WideString; dwSize: Integer);
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

procedure TfmOleObj.FormCreate(Sender: TObject);
begin
  self.redtData.Clear;
  self.redtCtl.Clear;
  FEvent := TEventObj.Create;
  
  try
    vCommMonitor := CreateOleObject('CommMonitor6x.CommMonitor');
  except on E: Exception do
  begin
    ShowMessageFmt('CreateOleObject "CommMonitor6x" fail: %s', [E.Message]);
    Exit;
  end;
  end;

  if not VarIsEmpty(vCommMonitor) then
  begin
    InterfaceConnect(vCommMonitor, FEventIID, FEvent, FConnection);
    if FConnection = 0 then ShowMessage('Connect comobj event fail.');
  end else
  begin
    ShowMessage('Unregister CommMonitor6x.ocx');
    Exit;
  end;
  

end;

procedure TfmOleObj.FormDestroy(Sender: TObject);
begin
  if not VarIsEmpty(vCommMonitor) then
  begin
    if fActive then vCommMonitor.StopMonitor;
     vCommMonitor := Unassigned;
  end;
end;

procedure TfmOleObj.btnPauseClick(Sender: TObject);
begin
  if  VarIsEmpty(vCommMonitor) then Exit;
  
  if vCommMonitor.PauseMonitor(fPause) then
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

procedure TfmOleObj.btn3Click(Sender: TObject);
begin
  if not VarIsEmpty(vCommMonitor) then
    vCommMonitor.AboutBox;
end;

procedure TfmOleObj.btn1Click(Sender: TObject);
begin
  self.redtData.Clear;
  self.redtCtl.Clear;
end;

procedure TfmOleObj.AddLog(redt: TRichEdit; AColor: TColor;
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

end.
