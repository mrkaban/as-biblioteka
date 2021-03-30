object Form_Logo: TForm_Logo
  Left = 333
  Top = 234
  Width = 505
  Height = 219
  Caption = #1040#1074#1090#1086#1084#1072#1090#1080#1079#1080#1088#1086#1074#1072#1085#1085#1072#1103' '#1089#1080#1089#1090#1077#1084#1072' "'#1041#1080#1073#1083#1080#1086#1090#1077#1082#1072'"'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 144
    Top = 16
    Width = 350
    Height = 29
    Alignment = taCenter
    AutoSize = False
    Caption = #1040#1074#1090#1086#1084#1072#1090#1080#1079#1080#1088#1086#1074#1072#1085#1085#1072#1103
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 144
    Top = 56
    Width = 350
    Height = 29
    Alignment = taCenter
    AutoSize = False
    Caption = #1089#1080#1089#1090#1077#1084#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 144
    Top = 96
    Width = 350
    Height = 29
    Alignment = taCenter
    AutoSize = False
    Caption = '"'#1041#1080#1073#1083#1080#1086#1090#1077#1082#1072'"'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -24
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 139
    Top = 160
    Width = 350
    Height = 17
    Alignment = taCenter
    AutoSize = False
    Caption = '2012 '#1075#1086#1076
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Image1: TImage
    Left = 0
    Top = 24
    Width = 200
    Height = 156
    Stretch = True
    Transparent = True
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 384
    Top = 136
  end
end
