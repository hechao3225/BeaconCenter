object frmMainForm: TfrmMainForm
  Left = 388
  Top = 185
  Width = 823
  Height = 500
  Caption = 'frmMainForm'
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
    Top = 304
    Width = 807
    Height = 5
    Cursor = crVSplit
    Align = alBottom
  end
  object CommMonitor1: TCommMonitor
    Left = 0
    Top = 0
    Width = 807
    Height = 37
    ParentFont = False
    Align = alTop
    TabOrder = 0
    OnMonitor = CommMonitor1Monitor
    OnAscii = CommMonitor1Ascii
    DesignSize = (
      807
      37)
    ControlData = {
      54504630065450616E656C00044C656674020003546F70020005576964746803
      270306486569676874022509416C69676E6D656E74070D74614C6566744A7573
      746966790A426576656C4F75746572070662764E6F6E650743617074696F6E06
      22436F6D6D4D6F6E69746F7220666F722044656C7068693720204F4358202044
      656D6F0C466F6E742E43686172736574070C414E53495F434841525345540A46
      6F6E742E436F6C6F72070C636C57696E646F77546578740B466F6E742E486569
      67687402F509466F6E742E4E616D65060D4D532053616E732053657269660A46
      6F6E742E5374796C650B066673426F6C64000A506172656E74466F6E74080000}
    object btn1: TBitBtn
      Left = 560
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Clear '
      TabOrder = 0
      OnClick = btn1Click
    end
    object btn2: TBitBtn
      Left = 723
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akRight, akBottom]
      TabOrder = 1
      Kind = bkClose
    end
    object btnOpen: TBitBtn
      Left = 332
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
      TabOrder = 2
      OnClick = btnOpenClick
    end
    object btnPause: TBitBtn
      Left = 436
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
      TabOrder = 3
      OnClick = btnPauseClick
    end
    object btn3: TButton
      Left = 640
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'ABout'
      TabOrder = 4
      OnClick = btn3Click
    end
    object cbb1: TComboBox
      Left = 259
      Top = 11
      Width = 68
      Height = 21
      ItemHeight = 13
      ItemIndex = 0
      TabOrder = 5
      Text = 'COM1'
      Items.Strings = (
        'COM1'
        'COM2'
        'COM3'
        'COM4'
        'COM5'
        'COM6')
    end
  end
  object redtData: TRichEdit
    Left = 0
    Top = 37
    Width = 807
    Height = 267
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
    TabOrder = 1
  end
  object stat1: TStatusBar
    Left = 0
    Top = 443
    Width = 807
    Height = 19
    Panels = <
      item
        Width = 50
      end>
  end
  object redtCtl: TRichEdit
    Left = 0
    Top = 309
    Width = 807
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
