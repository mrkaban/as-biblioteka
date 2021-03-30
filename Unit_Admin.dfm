object Form_Admin: TForm_Admin
  Left = 271
  Top = 221
  Width = 665
  Height = 419
  Caption = #1040#1076#1084#1080#1085#1080#1089#1090#1088#1080#1088#1086#1074#1072#1085#1080#1077
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 104
    Height = 16
    Caption = #1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1080':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 232
    Top = 16
    Width = 168
    Height = 16
    Caption = #1060#1072#1084#1080#1083#1080#1103' '#1048#1084#1103' '#1054#1090#1095#1077#1089#1090#1074#1086':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 232
    Top = 64
    Width = 48
    Height = 16
    Caption = #1040#1076#1088#1077#1089':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 232
    Top = 112
    Width = 72
    Height = 16
    Caption = #1055#1072#1089#1089#1087#1086#1088#1090':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 456
    Top = 112
    Width = 56
    Height = 16
    Caption = #1055#1072#1088#1086#1083#1100':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Label6: TLabel
    Left = 536
    Top = 16
    Width = 112
    Height = 16
    Caption = #1044#1072#1090#1072' '#1088#1086#1078#1076#1077#1085#1080#1103':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object SpeedButton1: TSpeedButton
    Left = 232
    Top = 344
    Width = 201
    Height = 25
    Caption = #1057#1054#1061#1056#1040#1053#1048#1058#1068
    Flat = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton1Click
  end
  object SpeedButton2: TSpeedButton
    Left = 448
    Top = 344
    Width = 201
    Height = 25
    Caption = #1042#1067#1061#1054#1044
    Flat = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton2Click
  end
  object SpeedButton_New: TSpeedButton
    Left = 232
    Top = 272
    Width = 201
    Height = 25
    Caption = #1057#1054#1047#1044#1040#1058#1068
    Flat = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton_NewClick
  end
  object SpeedButton_Add: TSpeedButton
    Left = 232
    Top = 272
    Width = 201
    Height = 25
    Caption = #1044#1054#1041#1040#1042#1048#1058#1068
    Flat = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    Visible = False
    OnClick = SpeedButton_AddClick
  end
  object Label7: TLabel
    Left = 448
    Top = 256
    Width = 96
    Height = 16
    Caption = #1050#1088#1072#1090#1082#1086#1077' '#1080#1084#1103':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object SpeedButton_Cancel: TSpeedButton
    Left = 232
    Top = 304
    Width = 201
    Height = 25
    Caption = #1054#1058#1052#1045#1053#1040
    Flat = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    Visible = False
    OnClick = SpeedButton_CancelClick
  end
  object ListBox1: TListBox
    Left = 8
    Top = 32
    Width = 209
    Height = 337
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ItemHeight = 16
    ParentFont = False
    TabOrder = 0
    OnClick = ListBox1Click
  end
  object Edit1: TEdit
    Left = 232
    Top = 32
    Width = 281
    Height = 24
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    Text = 'Edit1'
  end
  object Edit2: TEdit
    Left = 232
    Top = 80
    Width = 417
    Height = 24
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    Text = 'Edit1'
  end
  object Edit3: TEdit
    Left = 232
    Top = 128
    Width = 201
    Height = 24
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    Text = 'Edit1'
  end
  object Edit4: TEdit
    Left = 456
    Top = 128
    Width = 193
    Height = 24
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    Text = 'Edit1'
  end
  object DateTimePicker1: TDateTimePicker
    Left = 536
    Top = 32
    Width = 114
    Height = 24
    CalAlignment = dtaLeft
    Date = 40975.0385772917
    Time = 40975.0385772917
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
    TabOrder = 5
  end
  object GroupBox1: TGroupBox
    Left = 232
    Top = 168
    Width = 417
    Height = 73
    Caption = #1055#1088#1080#1074#1080#1083#1077#1075#1080#1080
    TabOrder = 6
    object RadioButton1: TRadioButton
      Left = 8
      Top = 16
      Width = 297
      Height = 17
      Caption = #1040#1076#1084#1080#1085#1080#1089#1090#1088#1072#1090#1086#1088' ('#1087#1086#1083#1085#1099#1081' '#1076#1086#1089#1090#1091#1087' '#1082#1086' '#1074#1089#1077#1084' '#1086#1087#1077#1088#1072#1094#1080#1103#1084')'
      TabOrder = 0
    end
    object RadioButton2: TRadioButton
      Left = 8
      Top = 32
      Width = 305
      Height = 17
      Caption = #1056#1072#1073#1086#1090#1085#1080#1082' ('#1086#1089#1085#1086#1074#1085#1099#1077' '#1086#1087#1077#1088#1072#1094#1080#1080' '#1089' '#1082#1085#1080#1075#1072#1084#1080', '#1095#1080#1090#1072#1090#1077#1083#1103#1084#1080')'
      Checked = True
      TabOrder = 1
      TabStop = True
    end
    object RadioButton3: TRadioButton
      Left = 8
      Top = 48
      Width = 297
      Height = 17
      Caption = #1043#1086#1089#1090#1100' ('#1090#1086#1083#1100#1082#1086' '#1086#1079#1085#1072#1082#1086#1084#1080#1090#1077#1083#1100#1085#1099#1081' '#1087#1088#1086#1089#1084#1086#1090#1088')'
      TabOrder = 2
    end
  end
  object Edit5: TEdit
    Left = 448
    Top = 272
    Width = 193
    Height = 21
    TabOrder = 7
    Text = 'Edit5'
    Visible = False
  end
  object Table1: TTable
    Left = 8
    Top = 8
  end
end
