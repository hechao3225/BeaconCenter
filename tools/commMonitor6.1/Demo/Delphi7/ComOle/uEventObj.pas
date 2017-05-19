unit uEventObj;

{$WARN SYMBOL_PLATFORM OFF}

interface

uses
  ComObj, ActiveX, AxCtrls, Classes, D7Com_TLB, StdVcl;

type
  TEventObj = class(TAutoObject, IConnectionPointContainer, IEventObj)
  private
    { Private declarations }
    FConnectionPoints: TConnectionPoints;
    FConnectionPoint: TConnectionPoint;
    FEvents: IEventObjEvents;
    { note: FEvents maintains a *single* event sink. For access to more
      than one event sink, use FConnectionPoint.SinkList, and iterate
      through the list of sinks. }
  public
    procedure Initialize; override;

    function   ObjQueryInterface(const   IID:   TGUID;   out   Obj):   HResult;   override;   
  protected
    { Protected declarations }
    property ConnectionPoints: TConnectionPoints read FConnectionPoints
      implements IConnectionPointContainer;
    procedure EventSinkChanged(const EventSink: IUnknown); override;
    procedure OnAscii(const sPortName: WideString; dwCtrlCode, dwPID: Integer;
      const sData: WideString; dwSize: Integer); safecall;
  end;

implementation

uses ComServ, uMainForm;

procedure TEventObj.EventSinkChanged(const EventSink: IUnknown);
begin
  FEvents := EventSink as IEventObjEvents;
end;

procedure TEventObj.Initialize;
begin
  inherited Initialize;
  FConnectionPoints := TConnectionPoints.Create(Self);
  if AutoFactory.EventTypeInfo <> nil then
    FConnectionPoint := FConnectionPoints.CreateConnectionPoint(
      AutoFactory.EventIID, ckSingle, EventConnect)
  else FConnectionPoint := nil;
end;


function TEventObj.ObjQueryInterface(const IID: TGUID; out Obj): HResult;
begin
  if  IsEqualGUID(IID, FEventIID)   and   GetInterface(IDispatch,   Obj)   then
    Result   :=   S_OK
    else
        Result   :=   inherited   ObjQueryInterface(IID,   Obj); 
end;

procedure TEventObj.OnAscii(const sPortName: WideString; dwCtrlCode,
  dwPID: Integer; const sData: WideString; dwSize: Integer);
begin
  fmOleObj.OnAscii(sPortName, dwCtrlCode, dwPID, sData, dwSize)
end;

initialization
  TAutoObjectFactory.Create(ComServer, TEventObj, Class_EventObj,
    ciSingleInstance, tmApartment);
end.
