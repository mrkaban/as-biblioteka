object Form_Bibliotheka: TForm_Bibliotheka
  Left = 277
  Top = 80
  Width = 873
  Height = 640
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
  object StatusBar: TStatusBar
    Left = 0
    Top = 587
    Width = 865
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 865
    Height = 41
    ButtonHeight = 36
    Caption = 'ToolBar1'
    TabOrder = 1
    object Image2: TImage
      Left = 0
      Top = 2
      Width = 10
      Height = 36
    end
    object SpeedButton1: TSpeedButton
      Left = 10
      Top = 2
      Width = 36
      Height = 36
      Hint = #1044#1086#1073#1072#1074#1080#1090#1100' '#1095#1080#1090#1072#1090#1077#1083#1103
      Flat = True
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton1Click
    end
    object Image1: TImage
      Left = 46
      Top = 2
      Width = 10
      Height = 36
    end
    object SpeedButton2: TSpeedButton
      Left = 56
      Top = 2
      Width = 36
      Height = 36
      Hint = #1044#1086#1073#1072#1074#1080#1090#1100' '#1082#1085#1080#1075#1091
      Flat = True
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton2Click
    end
    object Image3: TImage
      Left = 92
      Top = 2
      Width = 10
      Height = 36
    end
    object SpeedButton3: TSpeedButton
      Left = 102
      Top = 2
      Width = 36
      Height = 36
      Hint = #1042#1099#1076#1072#1090#1100' '#1082#1085#1080#1075#1091
      Flat = True
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton3Click
    end
    object Image4: TImage
      Left = 138
      Top = 2
      Width = 10
      Height = 36
    end
    object SpeedButton4: TSpeedButton
      Left = 148
      Top = 2
      Width = 36
      Height = 36
      Hint = #1057#1076#1072#1090#1100' '#1082#1085#1080#1075#1091
      Flat = True
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton4Click
    end
    object Image5: TImage
      Left = 184
      Top = 2
      Width = 10
      Height = 36
    end
    object SpeedButton5: TSpeedButton
      Left = 194
      Top = 2
      Width = 36
      Height = 36
      Hint = #1040#1076#1084#1080#1085#1080#1089#1090#1088#1080#1088#1086#1074#1072#1085#1080#1077
      Flat = True
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton5Click
    end
    object Image6: TImage
      Left = 230
      Top = 2
      Width = 10
      Height = 36
    end
    object SpeedButton6: TSpeedButton
      Left = 240
      Top = 2
      Width = 36
      Height = 36
      Hint = #1057#1090#1072#1090#1080#1089#1090#1080#1082#1072
      Flat = True
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton6Click
    end
    object Image8: TImage
      Left = 276
      Top = 2
      Width = 10
      Height = 36
    end
    object SpeedButton_About: TSpeedButton
      Left = 286
      Top = 2
      Width = 36
      Height = 36
      Hint = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
      Flat = True
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton_AboutClick
    end
    object Image7: TImage
      Left = 322
      Top = 2
      Width = 10
      Height = 36
    end
    object SpeedButton_Exit: TSpeedButton
      Left = 332
      Top = 2
      Width = 36
      Height = 36
      Hint = #1042#1099#1093#1086#1076
      Flat = True
      ParentShowHint = False
      ShowHint = True
      OnClick = SpeedButton_ExitClick
    end
  end
  object DBGrid_Hist: TDBGrid
    Left = 8
    Top = 48
    Width = 849
    Height = 497
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Options = [dgTitles, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentFont = False
    ReadOnly = True
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = [fsBold]
    OnDrawDataCell = DBGrid_HistDrawDataCell
    OnDrawColumnCell = DBGrid_HistDrawColumnCell
    OnMouseUp = DBGrid_HistMouseUp
  end
  object CheckBox_Norm: TCheckBox
    Left = 8
    Top = 560
    Width = 97
    Height = 17
    Caption = #1042#1099#1076#1072#1085#1085#1099#1077
    Checked = True
    State = cbChecked
    TabOrder = 3
    OnClick = CheckBox_NormClick
  end
  object CheckBox_Debt: TCheckBox
    Left = 288
    Top = 560
    Width = 145
    Height = 17
    Caption = #1042#1099#1076#1077#1083#1080#1090#1100' '#1087#1088#1086#1089#1088#1086#1095#1077#1085#1085#1099#1077
    Checked = True
    State = cbChecked
    TabOrder = 4
    OnClick = CheckBox_DebtClick
  end
  object CheckBox_Return: TCheckBox
    Left = 120
    Top = 560
    Width = 97
    Height = 17
    Caption = #1042#1086#1079#1074#1088#1072#1097#1077#1085#1085#1099#1077
    TabOrder = 5
    OnClick = CheckBox_ReturnClick
  end
  object Table_Stat: TTable
    Left = 824
    Top = 8
  end
  object DataSource_Stat: TDataSource
    Left = 792
    Top = 8
  end
  object Query_Hist: TQuery
    Left = 824
    Top = 64
  end
  object DataSource_Hist: TDataSource
    Left = 792
    Top = 64
  end
end
