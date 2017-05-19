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

#include <vcl.h>
#pragma hdrstop

#include <olectrls.hpp>
#include <oleserver.hpp>
#if defined(USING_ATL)
#include <atl\atlvcl.h>
#endif

#pragma option -w-8122
#include "CommMonitor6x_OCX.h"

#if !defined(__PRAGMA_PACKAGE_SMART_INIT)
#define      __PRAGMA_PACKAGE_SMART_INIT
#pragma package(smart_init)
#endif

namespace Commmonitor6x_tlb
{



// *********************************************************************//
// OCX PROXY CLASS IMPLEMENTATION
// (The following variables/methods implement the class TCommMonitor which
// allows "CommMonitor6x Control" to be hosted in CBuilder IDE/apps).
// *********************************************************************//
int   TCommMonitor::EventDispIDs[7] = {
    0x000000C9, 0x000000CA, 0x000000CB, 0x000000CC, 0x000000CD, 0x000000CE,
    0x000000CF};

int TCommMonitor::TFontIDs[1] = {
    0xFFFFFE00
};

Vcl::Olectrls::TControlData2 TCommMonitor::CControlData =
{
  // GUID of CoClass and Event Interface of Control
  {0x2F89A1E6, 0x2C00, 0x4882,{ 0xA3, 0xD4, 0xAC,0xDA, 0x95, 0xFC,0x7F, 0x6B} }, // CoClass
  {0x2E50E334, 0x3D45, 0x4743,{ 0xA0, 0x90, 0x59,0xCF, 0x4C, 0x04,0xD8, 0xF3} }, // Events

  // Count of Events and array of their DISPIDs
  7, &EventDispIDs,

  // Pointer to Runtime License string
  NULL,  // HRESULT(0x00000000)

  // Flags for OnChanged PropertyNotification
  0x0000001D,
  401,// (IDE Version)

  // Count of Font Prop and array of their DISPIDs
  1, Winapi::Activex::PDispIDList(TFontIDs),

  // Count of Pict Prop and array of their DISPIDs
  0, Winapi::Activex::PDispIDList(NULL),
  0, // Reserved
  0, // Instance count (used internally)
  0, // List of Enum descriptions (internal)
};

GUID     TCommMonitor::DEF_CTL_INTF = {0x4C2D6F22, 0xACFF, 0x47D3,{ 0xB3, 0xE8, 0xE2,0x71, 0xE5, 0x38,0xF0, 0x44} };
TNoParam TCommMonitor::OptParam;

static inline void ValidCtrCheck(TCommMonitor *)
{
   delete new TCommMonitor((System::Classes::TComponent*)(0));
};

void __fastcall TCommMonitor::InitControlData()
{
  ControlData = (Vcl::Olectrls::TControlData*)&CControlData;
  CControlData.FirstEventOfs = System::PByte(&FOnCanResize) - System::PByte(this);
};

void __fastcall TCommMonitor::CreateControl()
{
  if (!m_OCXIntf)
  {
    _ASSERTE(DefaultDispatch);
    DefaultDispatch->QueryInterface(DEF_CTL_INTF, (LPVOID*)&m_OCXIntf);
  }
};

TCOMICommMonitor6x __fastcall TCommMonitor::GetDefaultInterface()
{
  CreateControl();
  return m_OCXIntf;
};

long __fastcall TCommMonitor::DrawTextBiDiModeFlagsReadingOnly(void)
{
  long Value;
  OLECHECK(GetDefaultInterface()->DrawTextBiDiModeFlagsReadingOnly((long*)&Value));
  return Value;
}

void __fastcall TCommMonitor::InitiateAction(void)
{
  GetDefaultInterface()->InitiateAction();
}

VARIANT_BOOL __fastcall TCommMonitor::IsRightToLeft(void)
{
  VARIANT_BOOL Value;
  OLECHECK(GetDefaultInterface()->IsRightToLeft((VARIANT_BOOL*)&Value));
  return Value;
}

VARIANT_BOOL __fastcall TCommMonitor::UseRightToLeftReading(void)
{
  VARIANT_BOOL Value;
  OLECHECK(GetDefaultInterface()->UseRightToLeftReading((VARIANT_BOOL*)&Value));
  return Value;
}

VARIANT_BOOL __fastcall TCommMonitor::UseRightToLeftScrollBar(void)
{
  VARIANT_BOOL Value;
  OLECHECK(GetDefaultInterface()->UseRightToLeftScrollBar((VARIANT_BOOL*)&Value));
  return Value;
}

void __fastcall TCommMonitor::SetSubComponent(VARIANT_BOOL IsSubComponent/*[in]*/)
{
  GetDefaultInterface()->SetSubComponent(IsSubComponent/*[in]*/);
}

void __fastcall TCommMonitor::AboutBox(void)
{
  GetDefaultInterface()->AboutBox();
}

VARIANT_BOOL __fastcall TCommMonitor::StartMonitor(BSTR sPortName/*[in]*/)
{
  VARIANT_BOOL Value;
  OLECHECK(GetDefaultInterface()->StartMonitor(sPortName, (VARIANT_BOOL*)&Value));
  return Value;
}

VARIANT_BOOL __fastcall TCommMonitor::StopMonitor(void)
{
  VARIANT_BOOL Value;
  OLECHECK(GetDefaultInterface()->StopMonitor((VARIANT_BOOL*)&Value));
  return Value;
}

VARIANT_BOOL __fastcall TCommMonitor::PauseMonitor(VARIANT_BOOL bPause/*[in]*/)
{
  VARIANT_BOOL Value;
  OLECHECK(GetDefaultInterface()->PauseMonitor(bPause, (VARIANT_BOOL*)&Value));
  return Value;
}

unsigned_long __fastcall TCommMonitor::SerialCtrlCode(unsigned_long ctlCode/*[in]*/)
{
  unsigned_long Value;
  OLECHECK(GetDefaultInterface()->SerialCtrlCode(ctlCode, (unsigned_long*)&Value));
  return Value;
}

BSTR __fastcall TCommMonitor::GetPIDImagerName(unsigned_long dwPID/*[in]*/)
{
  BSTR Value = 0;
  OLECHECK(GetDefaultInterface()->GetPIDImagerName(dwPID, (BSTR*)&Value));
  return Value;
}


};     // namespace Commmonitor6x_tlb


// *********************************************************************//
// The Register function is invoked by the IDE when this module is 
// installed in a Package. It provides the list of Components (including
// OCXes) implemented by this module. The following implementation
// informs the IDE of the OCX proxy classes implemented here.
// *********************************************************************//
namespace Commmonitor6x_ocx
{

void __fastcall PACKAGE Register()
{
  // [1]
  System::Classes::TComponentClass cls_ocx[] = {
                              __classid(Commmonitor6x_tlb::TCommMonitor)
                           };
  System::Classes::RegisterComponents("ActiveX", cls_ocx,
                     sizeof(cls_ocx)/sizeof(cls_ocx[0])-1);
}

};     // namespace Commmonitor6x_ocx
