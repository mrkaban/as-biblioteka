object Form_Book_Out: TForm_Book_Out
  Left = 231
  Top = 104
  Width = 761
  Height = 459
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnHide = FormHide
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object SpeedButton1: TSpeedButton
    Left = 8
    Top = 384
    Width = 361
    Height = 25
    Caption = #1042#1067#1044#1040#1058#1068' '#1050#1053#1048#1043#1059
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
    Left = 384
    Top = 384
    Width = 361
    Height = 25
    Caption = #1054#1058#1052#1045#1053#1040
    Flat = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    OnClick = SpeedButton2Click
  end
  object Label1: TLabel
    Left = 8
    Top = 40
    Width = 136
    Height = 16
    Caption = #1055#1086#1088#1103#1076#1082#1086#1074#1099#1081' '#1085#1086#1084#1077#1088':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 0
    Top = 8
    Width = 753
    Height = 20
    Alignment = taCenter
    AutoSize = False
    Caption = #1042#1067#1044#1040#1063#1040' '#1050#1053#1048#1043#1048
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 88
    Width = 120
    Height = 16
    Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1082#1085#1080#1075#1091':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 8
    Top = 232
    Width = 144
    Height = 16
    Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1095#1080#1090#1072#1090#1077#1083#1103':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 192
    Top = 40
    Width = 96
    Height = 16
    Caption = #1044#1072#1090#1072' '#1074#1099#1076#1072#1095#1080':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Label6: TLabel
    Left = 360
    Top = 40
    Width = 72
    Height = 16
    Caption = #1056#1072#1073#1086#1090#1085#1080#1082':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Label7: TLabel
    Left = 592
    Top = 32
    Width = 120
    Height = 16
    Caption = #1053#1072' '#1089#1082#1086#1083#1100#1082#1086' '#1076#1085#1077#1081
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Label8: TLabel
    Left = 592
    Top = 48
    Width = 48
    Height = 16
    Caption = #1074#1099#1076#1072#1090#1100
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object Label9: TLabel
    Left = 592
    Top = 64
    Width = 48
    Height = 16
    Caption = #1082#1085#1080#1075#1091':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
  end
  object DBGrid_Book_Out: TDBGrid
    Left = 8
    Top = 104
    Width = 737
    Height = 120
    Color = clWhite
    Options = [dgTitles, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnDrawDataCell = DBGrid_Book_OutDrawDataCell
    OnMouseUp = DBGrid_Book_OutMouseUp
  end
  object Edit1: TEdit
    Left = 8
    Top = 56
    Width = 137
    Height = 24
    Color = clBtnFace
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 1
  end
  object DBGrid_Reader_Out: TDBGrid
    Left = 8
    Top = 248
    Width = 737
    Height = 120
    Options = [dgTitles, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnDrawDataCell = DBGrid_Reader_OutDrawDataCell
    OnMouseUp = DBGrid_Reader_OutMouseUp
  end
  object Edit2: TEdit
    Left = 192
    Top = 56
    Width = 121
    Height = 24
    Color = clBtnFace
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 3
  end
  object Edit3: TEdit
    Left = 360
    Top = 56
    Width = 193
    Height = 24
    Color = clBtnFace
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 4
  end
  object CSpinEdit1: TCSpinEdit
    Left = 656
    Top = 56
    Width = 73
    Height = 26
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
    MaxValue = 31
    MinValue = 1
    ParentFont = False
    TabOrder = 5
    Value = 14
  end
  object Table_Book_Out: TTable
    Left = 16
    Top = 168
  end
  object DataSource_Book_Out: TDataSource
    Left = 48
    Top = 168
  end
  object Table_Reader_Out: TTable
    Left = 8
    Top = 304
  end
  object DataSource_Reader_Out: TDataSource
    Left = 40
    Top = 304
  end
  object Table_Hist: TTable
    Left = 720
    Top = 8
  end
end
