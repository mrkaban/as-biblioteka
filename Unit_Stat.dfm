object Form_Stat: TForm_Stat
  Left = 284
  Top = 160
  Width = 321
  Height = 531
  Caption = #1057#1090#1072#1090#1080#1089#1090#1080#1082#1072
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnHide = FormHide
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object SpeedButton1: TSpeedButton
    Left = 8
    Top = 464
    Width = 297
    Height = 25
    Caption = #1054#1058#1052#1045#1053#1040
    Flat = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton1Click
  end
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 216
    Height = 16
    Caption = #1055#1077#1088#1080#1086#1076' '#1092#1086#1088#1084#1080#1088#1086#1074#1072#1085#1080#1103' '#1086#1090#1095#1077#1090#1072':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object SpeedButton2: TSpeedButton
    Left = 16
    Top = 424
    Width = 129
    Height = 25
    Caption = 'TXT'
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton2Click
  end
  object SpeedButton3: TSpeedButton
    Left = 168
    Top = 424
    Width = 129
    Height = 25
    Caption = 'XLS'
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton3Click
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 56
    Width = 297
    Height = 129
    Caption = #1057#1090#1072#1090#1080#1089#1090#1080#1082#1072' '#1087#1086' '#1082#1085#1080#1075#1072#1084
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 192
    Width = 297
    Height = 105
    Caption = #1057#1090#1072#1090#1080#1089#1090#1080#1082#1072' '#1087#1086' '#1095#1080#1090#1072#1090#1077#1083#1103#1084
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 304
    Width = 297
    Height = 105
    Caption = #1057#1090#1072#1090#1080#1089#1090#1080#1082#1072' '#1087#1086' '#1089#1086#1090#1088#1091#1076#1085#1080#1082#1072#1084
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
  end
  object DateTimePicker1: TDateTimePicker
    Left = 8
    Top = 24
    Width = 113
    Height = 24
    CalAlignment = dtaLeft
    Date = 40978.4342858333
    Time = 40978.4342858333
    DateFormat = dfShort
    DateMode = dmComboBox
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    Kind = dtkDate
    ParseInput = False
    ParentFont = False
    TabOrder = 3
  end
  object DateTimePicker2: TDateTimePicker
    Left = 136
    Top = 24
    Width = 113
    Height = 24
    CalAlignment = dtaLeft
    Date = 40978.4342858333
    Time = 40978.4342858333
    DateFormat = dfShort
    DateMode = dmComboBox
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    Kind = dtkDate
    ParseInput = False
    ParentFont = False
    TabOrder = 4
  end
  object RadioButton1: TRadioButton
    Left = 24
    Top = 80
    Width = 113
    Height = 17
    Caption = #1054#1073#1097#1072#1103
    Checked = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    TabStop = True
  end
  object RadioButton2: TRadioButton
    Left = 24
    Top = 104
    Width = 145
    Height = 17
    Caption = #1055#1086' '#1074#1099#1076#1072#1095#1072#1084' '#1082#1085#1080#1075
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
  end
  object RadioButton3: TRadioButton
    Left = 24
    Top = 128
    Width = 145
    Height = 17
    Caption = #1055#1086' '#1089#1076#1072#1095#1072#1084' '#1082#1085#1080#1075
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 7
  end
  object RadioButton4: TRadioButton
    Left = 24
    Top = 152
    Width = 145
    Height = 17
    Caption = #1055#1086' '#1078#1072#1085#1088#1072#1084' '#1082#1085#1080#1075
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 8
  end
  object RadioButton5: TRadioButton
    Left = 24
    Top = 216
    Width = 113
    Height = 17
    Caption = #1054#1073#1097#1072#1103
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 9
  end
  object RadioButton6: TRadioButton
    Left = 24
    Top = 240
    Width = 145
    Height = 17
    Caption = #1055#1086' '#1074#1099#1076#1072#1095#1072#1084' '#1082#1085#1080#1075
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 10
  end
  object RadioButton7: TRadioButton
    Left = 24
    Top = 264
    Width = 145
    Height = 17
    Caption = #1055#1086' '#1089#1076#1072#1095#1072#1084' '#1082#1085#1080#1075
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 11
  end
  object RadioButton8: TRadioButton
    Left = 24
    Top = 328
    Width = 113
    Height = 17
    Caption = #1054#1073#1097#1072#1103
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 12
  end
  object RadioButton9: TRadioButton
    Left = 24
    Top = 352
    Width = 265
    Height = 17
    Caption = #1055#1086' '#1086#1087#1077#1088#1072#1094#1080#1103#1084' '#1089' '#1082#1085#1080#1075#1072#1084#1080
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 13
  end
  object RadioButton10: TRadioButton
    Left = 24
    Top = 376
    Width = 161
    Height = 17
    Caption = #1055#1086' '#1088#1072#1073#1086#1095#1080#1084' '#1089#1084#1077#1085#1072#1084
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 14
  end
  object Query1: TQuery
    Left = 8
    Top = 384
  end
  object Table1: TTable
    Left = 40
    Top = 384
  end
  object Query2: TQuery
    Left = 72
    Top = 384
  end
end
