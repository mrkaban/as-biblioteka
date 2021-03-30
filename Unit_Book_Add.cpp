//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit_Book_Add.h"
#include "Unit_Bibliotheka.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_Book_Add *Form_Book_Add;
//---------------------------------------------------------------------------
__fastcall TForm_Book_Add::TForm_Book_Add(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_Add::FormShow(TObject *Sender)
{
  AnsiString Patch;                   // переменная для пути к программе

  // загрузка иконки
  Form_Book_Add->Icon->LoadFromFile("Books-OGY.ico");
  // вывод окна в центре основной формы
  Form_Book_Add->Top = Form_Bibliotheka->Top + (Form_Bibliotheka->Height - Form_Book_Add->Height) / 2;
  Form_Book_Add->Left = Form_Bibliotheka->Left + (Form_Bibliotheka->Width - Form_Book_Add->Width) / 2;
  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // подключение базы данных книг
  Table1->DatabaseName = Patch + "Base\\";
  Table1->TableName = "BOOK.db";
  Table1->Open();
  Table1->Active = true;
  // определение порядкового номера для добавления
  Table1->Last();
  Edit1->Text = IntToStr(Table1->FieldByName("BOOK_ID")->AsInteger + 1);
  // очистка полей
  Edit2->Text = "";
  Edit3->Text = "";
  Edit4->Text = "";
  Edit5->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_Add::FormHide(TObject *Sender)
{
  // закрытие таблицы
  Table1->Close();
  // завершение операции добавления книги
  Form_Bibliotheka->Enabled = true;
  Form_Book_Add->Hide();
  // передача фокуса основной таблице
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_Add::FormClose(TObject *Sender, TCloseAction &Action)
{
  // закрытие таблицы
  Table1->Close();
  // завершение операции добавления книги
  Form_Bibliotheka->Enabled = true;
  Form_Book_Add->Hide();
  // передача фокуса основной таблице
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_Add::SpeedButton2Click(TObject *Sender)
{
  // закрытие таблицы
  Table1->Close();
  // завершение операции добавления книги
  Form_Bibliotheka->Enabled = true;
  Form_Book_Add->Hide();
  // передача фокуса основной таблице
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_Add::SpeedButton1Click(TObject *Sender)
{
  // добавление книги в базу
  Table1->Append();
  Table1->FieldByName("BOOK_AUTHOR")->AsString = Edit2->Text;
  Table1->FieldByName("BOOK_NAME")->AsString = Edit3->Text;
  Table1->FieldByName("BOOK_YEAR")->AsDateTime = DateTimePicker1->Date;
  Table1->FieldByName("BOOK_SECTION")->AsString = Edit4->Text;
  Table1->FieldByName("BOOK_DESCRIPTION")->AsString = Edit5->Text;
  Table1->FieldByName("BOOK_STATUS")->AsBoolean = true;
  Table1->UpdateRecord();
  Table1->Post();
  // закрытие таблицы
  Table1->Close();
  // завершение операции добавления книги
  Form_Bibliotheka->Enabled = true;
  Form_Book_Add->Hide();
  // передача фокуса основной таблице
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
