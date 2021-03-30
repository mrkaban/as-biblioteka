object Form_Login: TForm_Login
  Left = 132
  Top = 213
  Width = 409
  Height = 315
  Caption = #1040#1074#1090#1086#1084#1072#1090#1080#1079#1080#1088#1086#1074#1072#1085#1085#1072#1103' '#1089#1080#1089#1090#1077#1084#1072' "'#1041#1080#1073#1083#1080#1086#1090#1077#1082#1072'"'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 96
    Width = 128
    Height = 16
    Caption = #1048#1084#1103' '#1087#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1103
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 160
    Width = 144
    Height = 16
    Caption = #1055#1072#1088#1086#1083#1100' '#1089#1086#1090#1088#1091#1076#1085#1080#1082#1072' '
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object SpeedButton1: TSpeedButton
    Left = 16
    Top = 232
    Width = 169
    Height = 25
    Caption = #1042#1054#1049#1058#1048
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    OnClick = SpeedButton1Click
  end
  object Label3: TLabel
    Left = 16
    Top = 24
    Width = 369
    Height = 20
    Alignment = taCenter
    AutoSize = False
    Caption = #1042#1061#1054#1044' '#1042' '#1057#1048#1057#1058#1045#1052#1059
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object SpeedButton2: TSpeedButton
    Left = 216
    Top = 232
    Width = 169
    Height = 25
    Caption = #1054#1058#1052#1045#1053#1040
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    OnClick = SpeedButton2Click
  end
  object Label4: TLabel
    Left = 16
    Top = 56
    Width = 128
    Height = 16
    Caption = #1055#1088#1077#1076#1099#1076#1091#1097#1080#1081' '#1074#1093#1086#1076':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 16
    Top = 72
    Width = 8
    Height = 16
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object MaskEdit1: TMaskEdit
    Left = 16
    Top = 193
    Width = 369
    Height = 24
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    PasswordChar = '*'
    TabOrder = 0
    Text = #1087#1072#1088#1086#1083#1100
  end
  object CheckBox1: TCheckBox
    Left = 16
    Top = 176
    Width = 129
    Height = 17
    Caption = #1057#1082#1088#1099#1090#1100' '#1087#1072#1088#1086#1083#1100
    Checked = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    State = cbChecked
    TabOrder = 1
    OnClick = CheckBox1Click
  end
  object ComboBox1: TComboBox
    Left = 16
    Top = 120
    Width = 369
    Height = 24
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ItemHeight = 16
    ParentFont = False
    TabOrder = 2
    Text = 'ComboBox1'
    OnChange = ComboBox1Change
  end
  object DataSource1: TDataSource
    DataSet = Table1
    Left = 8
    Top = 8
  end
  object Table1: TTable
    DatabaseName = 'T:\!!! Free-Lance\!!!\4000\Project\BASE\'
    TableName = 'USERS.DB'
    Left = 40
    Top = 8
  end
  object DataSource2: TDataSource
    Left = 8
    Top = 40
  end
  object Table2: TTable
    Left = 40
    Top = 40
  end
end
