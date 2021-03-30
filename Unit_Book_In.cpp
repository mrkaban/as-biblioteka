//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "IniFiles.hpp"
#include "Unit_Bibliotheka.h"
#include "Unit_Book_In.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_Book_In *Form_Book_In;
//---------------------------------------------------------------------------
__fastcall TForm_Book_In::TForm_Book_In(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_In::FormShow(TObject *Sender)
{
  AnsiString Patch;           // ���������� ��� ���� � ���������
  TIniFile *Ini;              // ���������� ��� ������ � INI ������
  AnsiString UserLogin;       // ������� ��� ���������

  // �������� ������
  Form_Book_In->Icon->LoadFromFile("Books-OGY.ico");
  // ����� ���� � ������ �������� �����
  Form_Book_In->Top = Form_Bibliotheka->Top + (Form_Bibliotheka->Height - Form_Book_In->Height) / 2;
  Form_Book_In->Left = Form_Bibliotheka->Left + (Form_Bibliotheka->Width - Form_Book_In->Width) / 2;
  // ����������� ���� � ���������
  Patch = ExtractFilePath(ParamStr(0));
  // ����������� ���� ������ �������
  DBGrid_Hist->DataSource = DataSource_Hist;
  DataSource_Hist->DataSet = Table_Hist;
  Table_Hist->DatabaseName = Patch + "Base\\";
  Table_Hist->TableName = "HIST.db";
  Table_Hist->Open();
  Table_Hist->Active = true;
  // ����������� ���� ������ ����
  Table_Book->DatabaseName = Patch + "Base\\";
  Table_Book->TableName = "BOOK.db";
  Table_Book->Open();
  Table_Book->Active = true;
  // ����������� ����, ��������� � �������
  Table_Hist->Filter = "HIST_DATE_IN IS NULL";
  Table_Hist->Filtered = true;
  // ������� �������� � ��������� ������
  Ini = new TIniFile(Patch+"Settings.ini");
  for (int i=0; i<9; i++)
    {
      AnsiString str;
      int k;
      k = Ini->ReadInteger("Grid_Hist_In","col_size_"+IntToStr(i+1),50);
      DBGrid_Hist->Columns->operator [](i)->Title->Caption = Ini->ReadString("Grid_Hist_In","col_name_"+IntToStr(i+1),"Title");
      DBGrid_Hist->Columns->operator [](i)->Width = k;
    }
  // ������� �������� ��������
  DBGrid_Hist->Columns->operator [](3)->Visible = false;
  DBGrid_Hist->Columns->operator [](5)->Visible = false;
  DBGrid_Hist->Columns->operator [](7)->Visible = false;
  DBGrid_Hist->Columns->operator [](8)->Visible = false;
  // ���������� ���� c����
  if (Table_Hist->RecordCount != 0)
    {
      Edit2->Text = DateToStr(Date());
    }
  else
    {
      Edit2->Text = "";
    }
  // ���������� ���������
  UserLogin = Ini->ReadString("CURRENT","User","not found");
  Edit3->Text = UserLogin;
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_In::DBGrid_HistDrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State)
{
  // ��������� ������ �������� ������
  if(State.Contains(gdSelected))
    {
      ((TDBGrid *)Sender)->Canvas->Font->Color = clRed;
      ((TDBGrid *)Sender)->Canvas->Brush->Color = TColor(0x00C6FFFF);
    }
  // ��� ������� ������ ����������
  else
    {
      ((TDBGrid *)Sender)->Canvas->Font->Color = clBlack;
      ((TDBGrid *)Sender)->Canvas->Brush->Color = clWhite;
    }
  // ��������� ������������ ����
  if (Column->Field->DataSet->FieldByName("HIST_DAY_IN_PLAN")->AsDateTime < Date())
    {
      ((TDBGrid *)Sender)->Canvas->Brush->Color = clRed;
      ((TDBGrid *)Sender)->Canvas->Font->Color = clBlack;
      if (State.Contains(gdSelected))
        {
          ((TDBGrid *)Sender)->Canvas->Font->Style = TFontStyles() << fsBold;
        }
    }
  // ���������� ���������� ���� ���������
  if (Table_Hist->FieldByName("HIST_DAY_IN_PLAN")->AsDateTime < Date() && State.Contains(gdSelected))
    {
      Edit1->Font->Color = clRed;
      Edit1->Text = IntToStr(Date()-Table_Hist->FieldByName("HIST_DAY_IN_PLAN")->AsDateTime);
      Label1->Caption = "���������:";
    }
  if (Table_Hist->FieldByName("HIST_DAY_IN_PLAN")->AsDateTime >= Date() && State.Contains(gdSelected))
    {
      Edit1->Font->Color = clBlack;
      Edit1->Text = IntToStr(Table_Hist->FieldByName("HIST_DAY_IN_PLAN")->AsDateTime-Date());
      Label1->Caption = "���� �� �����:";
    }
  if (Table_Hist->RecordCount == 0)
    {
      Edit1->Text = "";
    }
  // ��������� ������
  DBGrid_Hist->DefaultDrawColumnCell(Rect, DataCol, Column, State);
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_In::DBGrid_HistMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
  AnsiString Patch;           // ���������� ��� ���� � ���������
  TIniFile *Ini;              // ���������� ��� ������ � INI ������

  // ����������� ���� � ���������
  Patch = ExtractFilePath(ParamStr(0));
  // ���������� ������
  Ini = new TIniFile(Patch+"Settings.ini");
  for (int i=0; i<9; i++)
    {
      Ini->WriteInteger("Grid_Hist_In","col_size_"+IntToStr(i+1),DBGrid_Hist->Columns->operator [](i)->Width);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_In::FormResize(TObject *Sender)
{
  // ������������ �������� ����
  Form_Book_In->Height = 379;
  Form_Book_In->Width = 569;
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_In::SpeedButton1Click(TObject *Sender)
{
  AnsiString Patch;           // ���������� ��� ���� � ���������
  TIniFile *Ini;              // ���������� ��� ������ � INI ������
  AnsiString UserLogin;       // ������� ��� ���������
  TBookmark SavePlace;        // ��������

  // �������� ������� ���� ��� c����
  if (Table_Hist->RecordCount == 0)
    {
      ShowMessage ("��� ���� ��� c����!!!");
      return;
    }
  // ����������� ���� � ���������
  Patch = ExtractFilePath(ParamStr(0));
  // ���������� ���������
  Ini = new TIniFile(Patch+"Settings.ini");
  UserLogin = Ini->ReadString("CURRENT","User","not found");
  // ����������� ������������ �����
  Table_Book->Filter = "BOOK_ID = "+IntToStr(Table_Hist->FieldByName("HIST_BOOK_ID")->AsInteger);
  Table_Book->Filtered = true;
  // ������� ����� ��� ������������
  Table_Book->Edit();
  Table_Book->FieldByName("BOOK_STATUS")->AsBoolean = true;
  Table_Book->UpdateRecord();
  Table_Book->Post();
  // ������������� ������ � ����
  Table_Hist->Edit();
  Table_Hist->FieldByName("HIST_DATE_IN")->AsDateTime = Date();
  Table_Hist->FieldByName("HIST_USER_IN")->AsString = UserLogin;
  Table_Hist->UpdateRecord();
  Table_Hist->Post();
  // �������� �������
  Table_Book->Filtered = false;
  Table_Book->Close();
  Table_Hist->Close();
  // ���������� ������ �� �������� �����
  SavePlace = Form_Bibliotheka->Query_Hist->GetBookmark();
  Form_Bibliotheka->Query_Hist->Filtered = false;
  Form_Bibliotheka->Query_Hist->Close();
  Form_Bibliotheka->Query_Hist->Active = false;
  Form_Bibliotheka->Query_Hist->ExecSQL();
  Form_Bibliotheka->Query_Hist->Open();
  Form_Bibliotheka->Query_Hist->Active = true;
  Form_Bibliotheka->Query_Hist->Filtered = true;
  Form_Bibliotheka->Query_Hist->GotoBookmark(SavePlace);
  // ������� �������� � ��������� ������
  for (int i=0; i<7; i++)
    {
      Form_Bibliotheka->DBGrid_Hist->Columns->operator [](i)->Title->Caption = Ini->ReadString("Grid_Hist","col_name_"+IntToStr(i+1),"Title");
      Form_Bibliotheka->DBGrid_Hist->Columns->operator [](i)->Width = Ini->ReadInteger("Grid_Hist","col_size_"+IntToStr(i+1),50);
    }
  // ���������� �������� ������ �����
  Form_Bibliotheka->Enabled = true;
  Form_Book_In->Hide();
  // �������� ������ �������� �������
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_In::FormHide(TObject *Sender)
{
  // �������� �������
  Table_Book->Filtered = false;
  Table_Book->Close();
  Table_Hist->Close();
  // ���������� �������� ������ �����
  Form_Bibliotheka->Enabled = true;
  Form_Book_In->Hide();
  // �������� ������ �������� �������
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_In::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  // �������� �������
  Table_Book->Filtered = false;
  Table_Book->Close();
  Table_Hist->Close();
  // ���������� �������� ������ �����
  Form_Bibliotheka->Enabled = true;
  Form_Book_In->Hide();
  // �������� ������ �������� �������
  Form_Bibliotheka->DBGrid_Hist->SetFocus();        
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_In::SpeedButton2Click(TObject *Sender)
{
  // �������� �������
  Table_Book->Filtered = false;
  Table_Book->Close();
  Table_Hist->Close();
  // ���������� �������� ������ �����
  Form_Bibliotheka->Enabled = true;
  Form_Book_In->Hide();
  // �������� ������ �������� �������
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_In::DBGrid_HistDblClick(TObject *Sender)
{
  AnsiString Patch;           // ���������� ��� ���� � ���������
  AnsiString Str1;            // ������ 1 ����� �����
  AnsiString Str2;            // ������ 2 �������� �����
  AnsiString Str3;            // ������ 3 ��� ��������
  AnsiString Str4;            // ������ 4 ���� ������
  AnsiString Str5;            // ������ 5 �� ������� ���� ������
  AnsiString Str6;            // ������ 6 ����������� ���� ��������

  // �������� ������� �������� ����
  if (Table_Hist->RecordCount == 0)
    {
      ShowMessage ("��� ���� ��� c����!!!");
      return;
    }
  // ����������� ���� � ���������
  Patch = ExtractFilePath(ParamStr(0));
  // ����� ���������� ���������� � ���������� �����
  Query_Info->DatabaseName = Patch + "Base\\";
  Query_Info->SQL->Clear();
  Query_Info->SQL->Add("SELECT Book.BOOK_AUTHOR, Book.BOOK_NAME, Reader.READER_FIO, Hist.HIST_MAX_DAY, Hist.HIST_DATE_OUT, Hist.HIST_DAY_IN_PLAN");
  Query_Info->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book, \"READER.db\" Reader");
  Query_Info->SQL->Add("WHERE (Book.BOOK_ID = Hist.HIST_BOOK_ID) AND (Reader.READER_ID = Hist.HIST_REDER_ID) AND (Hist.HIST_ID ="+Table_Hist->FieldByName("HIST_ID")->AsString+")");
  Query_Info->ExecSQL();
  Query_Info->Open();
  Query_Info->Active = true;
  // ����������� ���������� � �������� �����
  Str1 = Query_Info->FieldByName("BOOK_AUTHOR")->AsString;
  Str2 = Query_Info->FieldByName("BOOK_NAME")->AsString;
  Str3 = Query_Info->FieldByName("READER_FIO")->AsString;
  Str4 = Query_Info->FieldByName("HIST_MAX_DAY")->AsString;
  Str5 = Query_Info->FieldByName("HIST_DATE_OUT")->AsString;
  Str6 = Query_Info->FieldByName("HIST_DAY_IN_PLAN")->AsString;
  // ����� ���������
  Application->MessageBoxA(("�����: "+Str1+"\n��������: "+Str2+"\n��������: "+Str3+"\n�� ������� ���� ������: "+Str4+"\n���� ������: "+Str5+"\n����������� ���� ��������: "+Str6).c_str(), "���������� � �������� �����", MB_OK|MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

