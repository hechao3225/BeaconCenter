object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 502
  ClientWidth = 773
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object spl1: TSplitter
    Left = 0
    Top = 344
    Width = 773
    Height = 5
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = -34
    ExplicitTop = 304
    ExplicitWidth = 807
  end
  object CommMonitor1: TCommMonitor
    Left = 0
    Top = 0
    Width = 773
    Height = 37
    ParentFont = False
    Align = alTop
    TabOrder = 0
    OnMonitor = CommMonitor1Monitor
    OnAscii = CommMonitor1Ascii
    ExplicitLeft = -34
    ExplicitWidth = 807
    DesignSize = (
      773
      37)
    ControlData = {
      54504630065450616E656C00044C656674020003546F70020005576964746803
      050306486569676874022509416C69676E6D656E74070D74614C6566744A7573
      746966790A426576656C4F75746572070662764E6F6E650743617074696F6E06
      1D436F6D6D4D6F6E69746F7220666F722044656C70686920372044656D6F0C46
      6F6E742E43686172736574070C414E53495F434841525345540A466F6E742E43
      6F6C6F72070C636C57696E646F77546578740B466F6E742E48656967687402F5
      09466F6E742E4E616D65060D4D532053616E732053657269660A466F6E742E53
      74796C650B066673426F6C64000A506172656E74466F6E74080000}
    object btn1: TBitBtn
      Left = 526
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Clear '
      TabOrder = 0
      OnClick = btn1Click
    end
    object btn2: TBitBtn
      Left = 689
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akRight, akBottom]
      Kind = bkClose
      NumGlyphs = 2
      TabOrder = 1
    end
    object btnOpen: TBitBtn
      Left = 292
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
      Left = 396
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
      Left = 606
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'ABout'
      TabOrder = 4
      OnClick = btn3Click
    end
    object cbb1: TComboBox
      Left = 219
      Top = 11
      Width = 68
      Height = 21
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
    Width = 773
    Height = 307
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
    Top = 483
    Width = 773
    Height = 19
    Panels = <
      item
        Width = 50
      end>
  end
  object redtCtl: TRichEdit
    Left = 0
    Top = 349
    Width = 773
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
