object fmOleObj: TfmOleObj
  Left = 244
  Top = 242
  Width = 845
  Height = 563
  Caption = 'fmOleObj'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object spl1: TSplitter
    Left = 0
    Top = 367
    Width = 829
    Height = 5
    Cursor = crVSplit
    Align = alBottom
  end
  object pnl1: TPanel
    Left = 0
    Top = 0
    Width = 829
    Height = 41
    Align = alTop
    Alignment = taLeftJustify
    Caption = 'CommMonitor for Delphi7 ComOleObj Demo'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    DesignSize = (
      829
      41)
    object cbb1: TComboBox
      Left = 275
      Top = 11
      Width = 68
      Height = 21
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 0
      Text = 'COM1'
      Items.Strings = (
        'COM1'
        'COM2'
        'COM3'
        'COM4'
        'COM5'
        'COM6')
    end
    object btnOpen: TBitBtn
      Left = 348
      Top = 7
      Width = 97
      Height = 25
      Caption = 'Start Monitor'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = btnOpenClick
    end
    object btnPause: TBitBtn
      Left = 452
      Top = 7
      Width = 97
      Height = 25
      Caption = 'Pause'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = btnPauseClick
    end
    object btn1: TBitBtn
      Left = 578
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Clear '
      TabOrder = 3
      OnClick = btn1Click
    end
    object btn3: TButton
      Left = 658
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'ABout'
      TabOrder = 4
      OnClick = btn3Click
    end
    object btn2: TBitBtn
      Left = 741
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akRight, akBottom]
      TabOrder = 5
      Kind = bkClose
    end
  end
  object stat1: TStatusBar
    Left = 0
    Top = 506
    Width = 829
    Height = 19
    Panels = <
      item
        Width = 50
      end>
  end
  object redtData: TRichEdit
    Left = 0
    Top = 41
    Width = 829
    Height = 326
    Align = alClient
    BevelInner = bvNone
    BevelOuter = bvRaised
    BevelKind = bkFlat
    BorderStyle = bsNone
    Ctl3D = True
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    HideScrollBars = False
    Lines.Strings = (
      'redt1')
    ParentCtl3D = False
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 2
  end
  object redtCtl: TRichEdit
    Left = 0
    Top = 372
    Width = 829
    Height = 134
    Align = alBottom
    BevelInner = bvNone
    BevelOuter = bvRaised
    BevelKind = bkFlat
    BorderStyle = bsNone
    Ctl3D = True
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    HideScrollBars = False
    Constraints.MinHeight = 30
    Lines.Strings = (
      'redt1')
    ParentCtl3D = False
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 3
  end
end
