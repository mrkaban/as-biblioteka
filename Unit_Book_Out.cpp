//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit_Bibliotheka.h"
#include "Unit_Book_Out.h"
#include "IniFiles.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm_Book_Out *Form_Book_Out;
//---------------------------------------------------------------------------
__fastcall TForm_Book_Out::TForm_Book_Out(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_Out::FormHide(TObject *Sender)
{
  // закрытие таблицы
  Table_Book_Out->Close();
  Table_Reader_Out->Close();
  Table_Hist->Close();
  // завершение операции выдачи книги
  Form_Bibliotheka->Enabled = true;
  Form_Book_Out->Hide();
  // передача фокуса основной таблице
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_Out::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  // закрытие таблицы
  Table_Book_Out->Close();
  Table_Reader_Out->Close();
  Table_Hist->Close();
  // завершение операции выдачи книги
  Form_Bibliotheka->Enabled = true;
  Form_Book_Out->Hide();
  // передача фокуса основной таблице
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_Out::SpeedButton2Click(TObject *Sender)
{
  // закрытие таблицы
  Table_Book_Out->Close();
  Table_Reader_Out->Close();
  Table_Hist->Close();
  // завершение операции выдачи книги
  Form_Bibliotheka->Enabled = true;
  Form_Book_Out->Hide();
  // передача фокуса основной таблице
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_Out::FormShow(TObject *Sender)
{
  AnsiString Patch;           // переменная для пути к программе
  TIniFile *Ini;              // переменная для работы с INI файлом
  AnsiString UserLogin;       // краткое имя работника

  // загрузка иконки
  Form_Book_Out->Icon->LoadFromFile("Books-OGY.ico");
  // вывод окна в центре основной формы
  Form_Book_Out->Top = Form_Bibliotheka->Top + (Form_Bibliotheka->Height - Form_Book_Out->Height) / 2;
  Form_Book_Out->Left = Form_Bibliotheka->Left + (Form_Bibliotheka->Width - Form_Book_Out->Width) / 2;
  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // подключение базы данных книг
  DBGrid_Book_Out->DataSource = DataSource_Book_Out;
  DataSource_Book_Out->DataSet = Table_Book_Out;
  Table_Book_Out->DatabaseName = Patch + "Base\\";
  Table_Book_Out->TableName = "BOOK.db";
  Table_Book_Out->Open();
  Table_Book_Out->Active = true;
  // отображение книг, имеющихся в наличии
  Table_Book_Out->Filter = "BOOK_STATUS = True";
  Table_Book_Out->Filtered = true;
  // подключение базы данных читателей
  DBGrid_Reader_Out->DataSource = DataSource_Reader_Out;
  DataSource_Reader_Out->DataSet = Table_Reader_Out;
  Table_Reader_Out->DatabaseName = Patch + "Base\\";
  Table_Reader_Out->TableName = "READER.db";
  Table_Reader_Out->Open();
  Table_Reader_Out->Active = true;
  // подключение базы данных читателей
  Table_Hist->DatabaseName = Patch + "Base\\";
  Table_Hist->TableName = "HIST.db";
  Table_Hist->Open();
  Table_Hist->Active = true;
  // определение порядкового номера для добавления
  Table_Hist->Last();
  Edit1->Text = IntToStr(Table_Hist->FieldByName("HIST_ID")->AsInteger + 1);
  // заполнение даты выдачи
  Edit2->Text = DateToStr(Date());
  // заполнение работника
  Ini = new TIniFile(Patch+"Settings.ini");
  UserLogin = Ini->ReadString("CURRENT","User","not found");
  Edit3->Text = UserLogin;
  // подпись столбцов и установка ширины
  for (int i=0; i<6; i++)
    {
      DBGrid_Book_Out->Columns->operator [](i)->Title->Caption = Ini->ReadString("Grid_Book_Out","col_name_"+IntToStr(i+1),"Title");
      DBGrid_Book_Out->Columns->operator [](i)->Width = Ini->ReadInteger("Grid_Book_Out","col_size_"+IntToStr(i+1),50);
    }
  for (int i=0; i<4; i++)
    {
      DBGrid_Reader_Out->Columns->operator [](i)->Title->Caption = Ini->ReadString("Grid_Reader_Out","col_name_"+IntToStr(i+1),"Title");
      DBGrid_Reader_Out->Columns->operator [](i)->Width = Ini->ReadInteger("Grid_Reader_Out","col_size_"+IntToStr(i+1),50);
    }
  // скрытие столбца статуса книги
  DBGrid_Book_Out->Columns->operator [](6)->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_Out::FormResize(TObject *Sender)
{
  // запрет изменения размеров
  Form_Book_Out->Width = 761;
  Form_Book_Out->Height = 459;
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_Out::DBGrid_Book_OutMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
  AnsiString Patch;           // переменная для пути к программе
  TIniFile *Ini;              // переменная для работы с INI файлом

  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // сохранение ширины
  Ini = new TIniFile(Patch+"Settings.ini");
  for (int i=0; i<6; i++)
    {
      Ini->WriteInteger("Grid_Book_Out","col_size_"+IntToStr(i+1),DBGrid_Book_Out->Columns->operator [](i)->Width);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_Out::DBGrid_Reader_OutMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
  AnsiString Patch;           // переменная для пути к программе
  TIniFile *Ini;              // переменная для работы с INI файлом

  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // сохранение ширины
  Ini = new TIniFile(Patch+"Settings.ini");
  for (int i=0; i<4; i++)
    {
      Ini->WriteInteger("Grid_Reader_Out","col_size_"+IntToStr(i+1),DBGrid_Reader_Out->Columns->operator [](i)->Width);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_Out::DBGrid_Book_OutDrawDataCell(TObject *Sender, const TRect &Rect, TField *Field, TGridDrawState State)
{
  // выделение цветом активной строки
  if(State.Contains(gdSelected))
    {
      ((TDBGrid *)Sender)->Canvas->Font->Color = clRed;
      ((TDBGrid *)Sender)->Canvas->Brush->Color = TColor(0x00C6FFFF);
    }
  // или обычным цветом неактивной
  else
    {
      ((TDBGrid *)Sender)->Canvas->Font->Color = clBlack;
      ((TDBGrid *)Sender)->Canvas->Brush->Color = clWhite;
    }
  ((TDBGrid *)Sender)->Canvas->FillRect(Rect);
  ((TDBGrid *)Sender)->Canvas->TextOut(Rect.Left+10,Rect.Top+2,Field->Text);
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_Out::DBGrid_Reader_OutDrawDataCell(TObject *Sender, const TRect &Rect, TField *Field, TGridDrawState State)
{
  // выделение цветом активной строки
  if(State.Contains(gdSelected))
    {
      ((TDBGrid *)Sender)->Canvas->Font->Color = clRed;
      ((TDBGrid *)Sender)->Canvas->Brush->Color = TColor(0x00C6FFFF);
    }
  // или обычным цветом неактивной
  else
    {
      ((TDBGrid *)Sender)->Canvas->Font->Color = clBlack;
      ((TDBGrid *)Sender)->Canvas->Brush->Color = clWhite;
    }
  ((TDBGrid *)Sender)->Canvas->FillRect(Rect);
  ((TDBGrid *)Sender)->Canvas->TextOut(Rect.Left+10,Rect.Top+2,Field->Text);
}
//---------------------------------------------------------------------------
void __fastcall TForm_Book_Out::SpeedButton1Click(TObject *Sender)
{
  AnsiString Patch;           // переменная для пути к программе
  TIniFile *Ini;              // переменная для работы с INI файлом
  AnsiString UserLogin;       // краткое имя работника
  TDateTime DayPlan;          // плановая дата сдачи книги
  TBookmark SavePlace;        // закладка

  // проверка наличия книг для выдачи
  if (Table_Book_Out->RecordCount == 0)
    {
      ShowMessage ("Нет книг для выдачи!!!");
      return;
    }
  // проверка наличия читателей
  if (Table_Reader_Out->RecordCount == 0)
    {
      ShowMessage ("Нет читателей!!!");
      return;
    }
  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // заполнение работника
  Ini = new TIniFile(Patch+"Settings.ini");
  UserLogin = Ini->ReadString("CURRENT","User","not found");
  // расчет даты сдачи книги
  DayPlan = Date();
  for (int i=0; i<CSpinEdit1->Value; i++)
    {
      DayPlan.operator ++();
    }
  // добавление записи в базу
  Table_Hist->Append();
  Table_Hist->FieldByName("HIST_BOOK_ID")->AsInteger = Table_Book_Out->FieldByName("BOOK_ID")->AsInteger;
  Table_Hist->FieldByName("HIST_REDER_ID")->AsInteger = Table_Reader_Out->FieldByName("READER_ID")->AsInteger;
  Table_Hist->FieldByName("HIST_MAX_DAY")->AsInteger = CSpinEdit1->Value;
  Table_Hist->FieldByName("HIST_DATE_OUT")->AsDateTime = Date();
  Table_Hist->FieldByName("HIST_USER_OUT")->AsString = UserLogin;
  Table_Hist->FieldByName("HIST_DAY_IN_PLAN")->AsDateTime = DayPlan;
  Table_Hist->UpdateRecord();
  Table_Hist->Post();
  // пометка книги как выданной
  Table_Book_Out->Edit();
  Table_Book_Out->FieldByName("BOOK_STATUS")->AsBoolean = false;
  Table_Book_Out->UpdateRecord();
  Table_Book_Out->Post();
  // закрытие таблицы
  Table_Book_Out->Filtered = false;
  Table_Book_Out->Close();
  Table_Reader_Out->Close();
  Table_Hist->Close();
  // обновление данных на основной форме
  SavePlace = Form_Bibliotheka->Query_Hist->GetBookmark();
  Form_Bibliotheka->Query_Hist->Filtered = false;
  Form_Bibliotheka->Query_Hist->Close();
  Form_Bibliotheka->Query_Hist->Active = false;
  Form_Bibliotheka->Query_Hist->ExecSQL();
  Form_Bibliotheka->Query_Hist->Open();
  Form_Bibliotheka->Query_Hist->Active = true;
  Form_Bibliotheka->Query_Hist->Filtered = true;
  Form_Bibliotheka->Query_Hist->GotoBookmark(SavePlace);
  // подпись столбцов и установка ширины
  for (int i=0; i<7; i++)
    {
      Form_Bibliotheka->DBGrid_Hist->Columns->operator [](i)->Title->Caption = Ini->ReadString("Grid_Hist","col_name_"+IntToStr(i+1),"Title1");
      Form_Bibliotheka->DBGrid_Hist->Columns->operator [](i)->Width = Ini->ReadInteger("Grid_Hist","col_size_"+IntToStr(i+1),500);
    }
  // завершение операции выдачи книги
  Form_Bibliotheka->Enabled = true;
  Form_Book_Out->Hide();
  // передача фокуса основной таблице
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------

