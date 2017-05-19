program CommMointorD7;

uses
  Forms,
  uMainForm in 'uMainForm.pas' {frmMainForm};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TfrmMainForm, frmMainForm);
  Application.Run;
end.
