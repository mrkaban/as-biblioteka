//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit_Reader_Add.h"
#include "Unit_Bibliotheka.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_Reader_Add *Form_Reader_Add;
//---------------------------------------------------------------------------
__fastcall TForm_Reader_Add::TForm_Reader_Add(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_Reader_Add::FormShow(TObject *Sender)
{
  AnsiString Patch;                   // ���������� ��� ���� � ���������

  // �������� ������
  Form_Reader_Add->Icon->LoadFromFile("Books-OGY.ico");
  // ����� ���� � ������ �������� �����
  Form_Reader_Add->Top = Form_Bibliotheka->Top + (Form_Bibliotheka->Height - Form_Reader_Add->Height) / 2;
  Form_Reader_Add->Left = Form_Bibliotheka->Left + (Form_Bibliotheka->Width - Form_Reader_Add->Width) / 2;
  // ����������� ���� � ���������
  Patch = ExtractFilePath(ParamStr(0));
  // ����������� ���� ������ ����
  Table1->DatabaseName = Patch + "Base\\";
  Table1->TableName = "READER.db";
  Table1->Open();
  Table1->Active = true;
  // ����������� ����������� ������ ��� ����������
  Table1->Last();
  Edit1->Text = IntToStr(Table1->FieldByName("READER_ID")->AsInteger + 1);
  // ������� �����
  Edit2->Text = "";
  Edit3->Text = "";
  Edit4->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm_Reader_Add::FormHide(TObject *Sender)
{
  // �������� �������
  Table1->Close();
  // ���������� �������� ���������� �����
  Form_Bibliotheka->Enabled = true;
  Form_Reader_Add->Hide();
  // �������� ������ �������� �������
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Reader_Add::FormClose(TObject *Sender,TCloseAction &Action)
{
  // �������� �������
  Table1->Close();
  // ���������� �������� ���������� �����
  Form_Bibliotheka->Enabled = true;
  Form_Reader_Add->Hide();
  // �������� ������ �������� �������
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Reader_Add::SpeedButton2Click(TObject *Sender)
{
  // �������� �������
  Table1->Close();
  // ���������� �������� ���������� �����
  Form_Bibliotheka->Enabled = true;
  Form_Reader_Add->Hide();
  // �������� ������ �������� �������
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Reader_Add::SpeedButton1Click(TObject *Sender)
{
  // ���������� �������� � ����
  Table1->Append();
  Table1->FieldByName("READER_FIO")->AsString = Edit2->Text;
  Table1->FieldByName("READER_ADRESS")->AsString = Edit3->Text;
  Table1->FieldByName("READER_PASSPORT")->AsString = Edit4->Text;
  Table1->UpdateRecord();
  Table1->Post();
  // �������� �������
  Table1->Close();
  // ���������� �������� ���������� ��������
  Form_Bibliotheka->Enabled = true;
  Form_Reader_Add->Hide();
  // �������� ������ �������� �������
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------

