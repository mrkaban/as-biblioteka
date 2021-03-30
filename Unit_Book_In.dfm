object Form_Book_In: TForm_Book_In
  Left = 429
  Top = 188
  Width = 569
  Height = 379
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
  object Label3: TLabel
    Left = 0
    Top = 8
    Width = 561
    Height = 20
    Alignment = taCenter
    AutoSize = False
    Caption = 'C'#1044#1040#1063#1040' '#1050#1053#1048#1043#1048
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label5: TLabel
    Left = 192
    Top = 40
    Width = 88
    Height = 16
    Caption = #1044#1072#1090#1072' c'#1076#1072#1095#1080':'
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
  object Label1: TLabel
    Left = 8
    Top = 40
    Width = 80
    Height = 16
    Caption = #1055#1088#1086#1089#1088#1086#1095#1082#1072':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = []
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
  object SpeedButton1: TSpeedButton
    Left = 8
    Top = 304
    Width = 265
    Height = 25
    Caption = 'C'#1044#1040#1058#1068' '#1050#1053#1048#1043#1059
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
    Left = 288
    Top = 304
    Width = 265
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
    TabOrder = 0
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
    TabOrder = 1
  end
  object Edit1: TEdit
    Left = 8
    Top = 56
    Width = 137
    Height = 24
    Color = clBtnFace
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 2
  end
  object DBGrid_Hist: TDBGrid
    Left = 8
    Top = 104
    Width = 545
    Height = 185
    Color = clWhite
    Options = [dgTitles, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    TabOrder = 3
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnDrawColumnCell = DBGrid_HistDrawColumnCell
    OnDblClick = DBGrid_HistDblClick
    OnMouseUp = DBGrid_HistMouseUp
  end
  object Table_Hist: TTable
    Left = 16
    Top = 168
  end
  object DataSource_Hist: TDataSource
    Left = 48
    Top = 168
  end
  object Table_Book: TTable
    Left = 16
    Top = 200
  end
  object Query_Info: TQuery
    Left = 48
    Top = 200
  end
end
