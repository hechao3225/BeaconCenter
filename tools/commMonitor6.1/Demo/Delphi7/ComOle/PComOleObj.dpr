program PComOleObj;

uses
  Forms,
  uMainForm in 'uMainForm.pas' {fmOleObj},
  D7Com_TLB in 'D7Com_TLB.pas',
  uEventObj in 'uEventObj.pas' {EventObj: CoClass};

{$R *.TLB}

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TfmOleObj, fmOleObj);
  Application.Run;
end.
