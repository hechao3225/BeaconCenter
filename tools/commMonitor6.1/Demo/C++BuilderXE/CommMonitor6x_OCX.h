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

// $Rev: 39763 $
// File generated on 2011/12/21 17:11:08 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\Windows\Downloaded Program Files\CONFLICT.4\CommMonitor6x.ocx (1)
// LIBID: {E33195D5-E29C-4295-8552-DDFA24001F02}
// LCID: 0
// Helpfile: 
// HelpString: CommMonitor6x Library
// DepndLst: 
//   (1) v2.0 stdole, (C:\Windows\system32\stdole2.tlb)
// ************************************************************************ //
#ifndef   CommMonitor6x_OCXH
#define   CommMonitor6x_OCXH

#pragma option push -b -a4 -w-inl -w-8118

#include <olectrls.hpp>
#include <oleserver.hpp>
#if !defined(__UTILCLS_H)
#include <utilcls.h>
#endif
#if !defined(__UTILCLS_H_VERSION) || (__UTILCLS_H_VERSION < 0x0700)
//
// The code generated by the TLIBIMP utility or the Import|TypeLibrary 
// and Import|ActiveX feature of C++Builder rely on specific versions of
// the header file UTILCLS.H found in the INCLUDE\VCL directory. If an 
// older version of the file is detected, you probably need an update/patch.
//
#error "This file requires a newer version of the header UTILCLS.H" \
       "You need to apply an update/patch to your copy of C++Builder"
#endif
#include <olectl.h>
#include <ocidl.h>
#if !defined(_NO_VCL)
#include <StdVCL.hpp>
#endif  //   _NO_VCL
#include <ocxproxy.h>

#include "CommMonitor6x_TLB.h"
namespace Commmonitor6x_tlb
{

// *********************************************************************//
// HelpString: CommMonitor6x Library
// Version:    1.0
// *********************************************************************//


// *********************************************************************//
// COM Component Proxy Class Declaration
// Component Name   : TCommMonitor
// Help String      : CommMonitor6x Control
// Default Interface: ICommMonitor6x
// Def. Intf. Object: TCOMICommMonitor6x
// Def. Intf. DISP? : No
// Event   Interface: ICommMonitor6Events
// TypeFlags        : (34) CanCreate Control
// *********************************************************************//

// *********************************************************************//
// Definition of closures to allow VCL handlers to catch OCX events.      
// *********************************************************************//
typedef void __fastcall (__closure * TCommMonitorOnCanResize)(System::TObject * Sender, 
                                                              long* NewWidth/*[in,out]*/, 
                                                              long* NewHeight/*[in,out]*/, 
                                                              VARIANT_BOOL* Resize/*[in,out]*/);
typedef void __fastcall (__closure * TCommMonitorOnConstrainedResize)(System::TObject * Sender, 
                                                                      long* MinWidth/*[in,out]*/, 
                                                                      long* MinHeight/*[in,out]*/, 
                                                                      long* MaxWidth/*[in,out]*/, 
                                                                      long* MaxHeight/*[in,out]*/);
typedef void __fastcall (__closure * TCommMonitorOnMonitor)(System::TObject * Sender, 
                                                            BSTR sPortName/*[in]*/, 
                                                            long dwCtrlCode/*[in]*/, 
                                                            long dwPID/*[in]*/, 
                                                            VARIANT* vtData/*[in]*/, 
                                                            long dwSize/*[in]*/);
typedef void __fastcall (__closure * TCommMonitorOnAscii)(System::TObject * Sender, 
                                                          BSTR sPortName/*[in]*/, 
                                                          long dwCtrlCode/*[in]*/, 
                                                          long dwPID/*[in]*/, BSTR sData/*[in]*/, 
                                                          long dwSize/*[in]*/);
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// Proxy class to host CommMonitor6x Control in CBuilder IDE/Applications.
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class PACKAGE TCommMonitor : public Vcl::Olectrls::TOleControl
{
  OVERLOADED_PROP_METHODS;
  static TNoParam  OptParam;
  static GUID      DEF_CTL_INTF;

  // Instance of Closures to expose OCX Events as VCL ones
  //
  TCommMonitorOnCanResize        FOnCanResize;
  System::Classes::TNotifyEvent  FOnClick;
  TCommMonitorOnConstrainedResize FOnConstrainedResize;
  System::Classes::TNotifyEvent  FOnDblClick;
  System::Classes::TNotifyEvent  FOnResize;
  TCommMonitorOnMonitor          FOnMonitor;
  TCommMonitorOnAscii            FOnAscii;

  // Default Interace of OCX
  //
  TCOMICommMonitor6x m_OCXIntf;

  // VCL Property Getters/Setters which delegate to OCX
  //

  // Static variables used by all instances of OCX proxy
  //
  static int          EventDispIDs[7];
  static int          TFontIDs[1];
  static Vcl::Olectrls::TControlData2 CControlData;
  static GUID          CTL_DEF_INTF;

  // Method providing access to interface as __property 
  //
  TCOMICommMonitor6x __fastcall GetDefaultInterface();
  TCOMICommMonitor6x __fastcall GetControlInterface()
  { return GetDefaultInterface(); }

protected:
  void     __fastcall CreateControl  ();
  void     __fastcall InitControlData();

public:
  virtual  __fastcall TCommMonitor(System::Classes::TComponent* AOwner) : Vcl::Olectrls::TOleControl(AOwner)
  {};
  virtual  __fastcall TCommMonitor(HWND        Parent) : Vcl::Olectrls::TOleControl(Parent)
  {};

  // OCX methods
  //
  long            __fastcall DrawTextBiDiModeFlagsReadingOnly(void);
  void            __fastcall InitiateAction(void);
  VARIANT_BOOL    __fastcall IsRightToLeft(void);
  VARIANT_BOOL    __fastcall UseRightToLeftReading(void);
  VARIANT_BOOL    __fastcall UseRightToLeftScrollBar(void);
  void            __fastcall SetSubComponent(VARIANT_BOOL IsSubComponent/*[in]*/);
  void            __fastcall AboutBox(void);
  VARIANT_BOOL    __fastcall StartMonitor(BSTR sPortName/*[in]*/);
  VARIANT_BOOL    __fastcall StopMonitor(void);
  VARIANT_BOOL    __fastcall PauseMonitor(VARIANT_BOOL bPause/*[in]*/);
  unsigned_long   __fastcall SerialCtrlCode(unsigned_long ctlCode/*[in]*/);
  BSTR            __fastcall GetPIDImagerName(unsigned_long dwPID/*[in]*/);

  // OCX properties
  //
  __property bool DoubleBuffered={ read=GetWordBoolProp, write=SetWordBoolProp, index=217 };
  __property bool AlignDisabled={ read=GetWordBoolProp, index=218 };
  __property int VisibleDockClientCount={ read=GetIntegerProp, index=219 };
  __property TCOMICommMonitor6x ControlInterface={ read=GetDefaultInterface };

  // Published properties
  //
__published:

  // Standard/Extended properties
  //
  __property ParentFont;
  __property Align;
  __property ParentShowHint;
  __property PopupMenu;
  __property ShowHint;
  __property TabOrder;
  __property OnDragDrop;
  __property OnDragOver;
  __property OnEndDrag;
  __property OnEnter;
  __property OnExit;
  __property OnStartDrag;

  // OCX properties
  //
  __property Winapi::Activex::TOleEnum Alignment={ read=GetTOleEnumProp, write=SetTOleEnumProp, stored=false, index=201 };
  __property bool AutoSize={ read=GetWordBoolProp, write=SetWordBoolProp, stored=false, index=202 };
  __property Winapi::Activex::TOleEnum BevelInner={ read=GetTOleEnumProp, write=SetTOleEnumProp, stored=false, index=203 };
  __property Winapi::Activex::TOleEnum BevelOuter={ read=GetTOleEnumProp, write=SetTOleEnumProp, stored=false, index=204 };
  __property Winapi::Activex::TOleEnum BorderStyle={ read=GetTOleEnumProp, write=SetTOleEnumProp, stored=false, index=205 };
  __property System::WideString Caption={ read=GetWideStringProp, write=SetWideStringProp, stored=false, index=-518 };
  __property Vcl::Graphics::TColor Color={ read=GetTColorProp, write=SetTColorProp, stored=false, index=-501 };
  __property bool Ctl3D={ read=GetWordBoolProp, write=SetWordBoolProp, stored=false, index=206 };
  __property bool UseDockManager={ read=GetWordBoolProp, write=SetWordBoolProp, stored=false, index=207 };
  __property bool DockSite={ read=GetWordBoolProp, write=SetWordBoolProp, stored=false, index=208 };
  __property short DragCursor={ read=GetSmallintProp, write=SetSmallintProp, stored=false, index=209 };
  __property Winapi::Activex::TOleEnum DragMode={ read=GetTOleEnumProp, write=SetTOleEnumProp, stored=false, index=210 };
  __property bool Enabled={ read=GetWordBoolProp, write=SetWordBoolProp, stored=false, index=-514 };
  __property bool FullRepaint={ read=GetWordBoolProp, write=SetWordBoolProp, stored=false, index=211 };
  __property Vcl::Graphics::TFont * Font={ read=GetTFontProp, write=_SetTFontProp, stored=false, index=-512 };
  __property bool Locked={ read=GetWordBoolProp, write=SetWordBoolProp, stored=false, index=212 };
  __property bool ParentBackground={ read=GetWordBoolProp, write=SetWordBoolProp, stored=false, index=213 };
  __property bool ParentColor={ read=GetWordBoolProp, write=SetWordBoolProp, stored=false, index=214 };
  __property bool ParentCtl3D={ read=GetWordBoolProp, write=SetWordBoolProp, stored=false, index=215 };
  __property bool Visible={ read=GetWordBoolProp, write=SetWordBoolProp, stored=false, index=216 };

  // OCX Events
  //
  __property TCommMonitorOnCanResize OnCanResize={ read=FOnCanResize, write=FOnCanResize };
  __property System::Classes::TNotifyEvent OnClick={ read=FOnClick, write=FOnClick };
  __property TCommMonitorOnConstrainedResize OnConstrainedResize={ read=FOnConstrainedResize, write=FOnConstrainedResize };
  __property System::Classes::TNotifyEvent OnDblClick={ read=FOnDblClick, write=FOnDblClick };
  __property System::Classes::TNotifyEvent OnResize={ read=FOnResize, write=FOnResize };
  __property TCommMonitorOnMonitor OnMonitor={ read=FOnMonitor, write=FOnMonitor };
  __property TCommMonitorOnAscii OnAscii={ read=FOnAscii, write=FOnAscii };
};
typedef TCommMonitor  TCommMonitorProxy;

};     // namespace Commmonitor6x_tlb

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using  namespace Commmonitor6x_tlb;
#endif

#pragma option pop

#endif // CommMonitor6x_OCXH
