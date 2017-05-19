unit D7Com_TLB;

// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// PASTLWTR : 1.2
// File generated on 2011-12-24 16:47:44 from Type Library described below.

// ************************************************************************  //
// Type Lib: G:\jfyes\KD\CommMonitor6.1\·¢²¼\Demo\Delphi7\ComOle\PComOleObj.tlb (1)
// LIBID: {1683AFC6-848B-43DD-A226-247D69F32988}
// LCID: 0
// Helpfile: 
// HelpString: D7Com Library
// DepndLst: 
//   (1) v2.0 stdole, (C:\Windows\system32\stdole2.tlb)
// ************************************************************************ //
{$TYPEDADDRESS OFF} // Unit must be compiled without type-checked pointers. 
{$WARN SYMBOL_PLATFORM OFF}
{$WRITEABLECONST ON}
{$VARPROPSETTER ON}
interface

uses Windows, ActiveX, Classes, Graphics, StdVCL, Variants;
  

// *********************************************************************//
// GUIDS declared in the TypeLibrary. Following prefixes are used:        
//   Type Libraries     : LIBID_xxxx                                      
//   CoClasses          : CLASS_xxxx                                      
//   DISPInterfaces     : DIID_xxxx                                       
//   Non-DISP interfaces: IID_xxxx                                        
// *********************************************************************//
const
  // TypeLibrary Major and minor versions
  D7ComMajorVersion = 1;
  D7ComMinorVersion = 0;

  LIBID_D7Com: TGUID = '{1683AFC6-848B-43DD-A226-247D69F32988}';

  IID_IEventObj: TGUID = '{DE12CC05-3E35-40A1-9809-CF6D86284CF9}';
  DIID_IEventObjEvents: TGUID = '{06381D5B-9F52-46D9-AA0C-7A4731BD535F}';
  CLASS_EventObj: TGUID = '{C60BA9D4-7523-4ABC-926F-06C6E6539863}';
type

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
  IEventObj = interface;
  IEventObjDisp = dispinterface;
  IEventObjEvents = dispinterface;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
// *********************************************************************//
  EventObj = IEventObj;


// *********************************************************************//
// Interface: IEventObj
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {DE12CC05-3E35-40A1-9809-CF6D86284CF9}
// *********************************************************************//
  IEventObj = interface(IDispatch)
    ['{DE12CC05-3E35-40A1-9809-CF6D86284CF9}']
    procedure OnAscii(const sPortName: WideString; dwCtrlCode: Integer; dwPID: Integer; 
                      const sData: WideString; dwSize: Integer); safecall;
  end;

// *********************************************************************//
// DispIntf:  IEventObjDisp
// Flags:     (4416) Dual OleAutomation Dispatchable
// GUID:      {DE12CC05-3E35-40A1-9809-CF6D86284CF9}
// *********************************************************************//
  IEventObjDisp = dispinterface
    ['{DE12CC05-3E35-40A1-9809-CF6D86284CF9}']
    procedure OnAscii(const sPortName: WideString; dwCtrlCode: Integer; dwPID: Integer; 
                      const sData: WideString; dwSize: Integer); dispid 207;
  end;

// *********************************************************************//
// DispIntf:  IEventObjEvents
// Flags:     (4096) Dispatchable
// GUID:      {06381D5B-9F52-46D9-AA0C-7A4731BD535F}
// *********************************************************************//
  IEventObjEvents = dispinterface
    ['{06381D5B-9F52-46D9-AA0C-7A4731BD535F}']
  end;

// *********************************************************************//
// The Class CoEventObj provides a Create and CreateRemote method to          
// create instances of the default interface IEventObj exposed by              
// the CoClass EventObj. The functions are intended to be used by             
// clients wishing to automate the CoClass objects exposed by the         
// server of this typelibrary.                                            
// *********************************************************************//
  CoEventObj = class
    class function Create: IEventObj;
    class function CreateRemote(const MachineName: string): IEventObj;
  end;

implementation

uses ComObj;

class function CoEventObj.Create: IEventObj;
begin
  Result := CreateComObject(CLASS_EventObj) as IEventObj;
end;

class function CoEventObj.CreateRemote(const MachineName: string): IEventObj;
begin
  Result := CreateRemoteComObject(MachineName, CLASS_EventObj) as IEventObj;
end;

end.
