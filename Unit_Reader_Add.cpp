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
  AnsiString Patch;                   // переменная для пути к программе

  // загрузка иконки
  Form_Reader_Add->Icon->LoadFromFile("Books-OGY.ico");
  // вывод окна в центре основной формы
  Form_Reader_Add->Top = Form_Bibliotheka->Top + (Form_Bibliotheka->Height - Form_Reader_Add->Height) / 2;
  Form_Reader_Add->Left = Form_Bibliotheka->Left + (Form_Bibliotheka->Width - Form_Reader_Add->Width) / 2;
  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // подключение базы данных книг
  Table1->DatabaseName = Patch + "Base\\";
  Table1->TableName = "READER.db";
  Table1->Open();
  Table1->Active = true;
  // определение порядкового номера для добавления
  Table1->Last();
  Edit1->Text = IntToStr(Table1->FieldByName("READER_ID")->AsInteger + 1);
  // очистка полей
  Edit2->Text = "";
  Edit3->Text = "";
  Edit4->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm_Reader_Add::FormHide(TObject *Sender)
{
  // закрытие таблицы
  Table1->Close();
  // завершение операции добавления книги
  Form_Bibliotheka->Enabled = true;
  Form_Reader_Add->Hide();
  // передача фокуса основной таблице
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Reader_Add::FormClose(TObject *Sender,TCloseAction &Action)
{
  // закрытие таблицы
  Table1->Close();
  // завершение операции добавления книги
  Form_Bibliotheka->Enabled = true;
  Form_Reader_Add->Hide();
  // передача фокуса основной таблице
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Reader_Add::SpeedButton2Click(TObject *Sender)
{
  // закрытие таблицы
  Table1->Close();
  // завершение операции добавления книги
  Form_Bibliotheka->Enabled = true;
  Form_Reader_Add->Hide();
  // передача фокуса основной таблице
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Reader_Add::SpeedButton1Click(TObject *Sender)
{
  // добавление читателя в базу
  Table1->Append();
  Table1->FieldByName("READER_FIO")->AsString = Edit2->Text;
  Table1->FieldByName("READER_ADRESS")->AsString = Edit3->Text;
  Table1->FieldByName("READER_PASSPORT")->AsString = Edit4->Text;
  Table1->UpdateRecord();
  Table1->Post();
  // закрытие таблицы
  Table1->Close();
  // завершение операции добавления читателя
  Form_Bibliotheka->Enabled = true;
  Form_Reader_Add->Hide();
  // передача фокуса основной таблице
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------

