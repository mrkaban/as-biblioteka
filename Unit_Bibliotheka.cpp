//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit_Bibliotheka.h"
#include "IniFiles.hpp"
#include "Unit_Reader_Add.h"
#include "Unit_Book_Add.h"
#include "Unit_Book_Out.h"
#include "Unit_Book_In.h"
#include "Unit_Admin.h"
#include "Unit_Stat.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_Bibliotheka *Form_Bibliotheka;
//---------------------------------------------------------------------------
__fastcall TForm_Bibliotheka::TForm_Bibliotheka(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::FormShow(TObject *Sender)
{
  AnsiString Patch;           // переменная для пути к программе
  TIniFile *Ini;              // переменная для работы с INI файлом
  int Top;                    // положение окна от верха экрана
  int Left;                   // положение окна от левого края экрана
  int Height;                 // высота окна программы
  int Width;                  // ширина окна программы
  int TextLength;             // длина текста в пикселях
  int Session_Id;             // номер входа в ПО
  int WindowState;            // флаг максимизации окна
  AnsiString UserLogin;       // краткое имя работника
  AnsiString UserName;        // полное имя работника

  // загрузка иконки
  Form_Bibliotheka->Icon->LoadFromFile("Books-OGY.ico");
  // загрузка картинок кнопок
  SpeedButton1->Glyph->LoadFromFile("user_add.bmp");
  SpeedButton2->Glyph->LoadFromFile("book_add.bmp");
  SpeedButton3->Glyph->LoadFromFile("book_next.bmp");
  SpeedButton4->Glyph->LoadFromFile("book_previous.bmp");
  SpeedButton5->Glyph->LoadFromFile("users_preferences.bmp");
  SpeedButton6->Glyph->LoadFromFile("table.bmp");
  SpeedButton_About->Glyph->LoadFromFile("about.bmp");
  SpeedButton_Exit->Glyph->LoadFromFile("exit.bmp");
  // первоначальная инициализация - вывод формы по центру экрана
  Top = (Screen->DesktopHeight - Form_Bibliotheka->Height) / 2;
  Left = (Screen->DesktopWidth - Form_Bibliotheka->Width) / 2;
  Height = Form_Bibliotheka->Height;
  Width = Form_Bibliotheka->Width;
  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // чтение настроек
  Ini = new TIniFile(Patch+"Settings.ini");
  Top = Ini->ReadInteger("PROG","Top",Top);
  Left = Ini->ReadInteger("PROG","Left",Left);
  Height = Ini->ReadInteger("PROG","Height",Height);
  Width = Ini->ReadInteger("PROG","Width",Width);
  WindowState = Ini->ReadInteger("PROG","WindowState",0);
  Session_Id = Ini->ReadInteger("CURRENT","Id_Num",-1);
  UserLogin =Ini->ReadString("CURRENT","User","not found");
  UserName = Ini->ReadString("CURRENT","User_name","not found");
  // установка параметров окна
  Form_Bibliotheka->Height = Height;
  Form_Bibliotheka->Width = Width;
  if (WindowState == 1)
    {
      Form_Bibliotheka->WindowState = wsMaximized;
    }
  // вывод данных в строку статуса
  StatusBar->Panels->Add();
  StatusBar->Panels->Add();
  StatusBar->Panels->Add();
  StatusBar->Panels->Add();
  StatusBar->Panels->operator [](0)->Text = "Сессия №"+IntToStr(Session_Id);
  TextLength = this->Canvas->TextWidth(StatusBar->Panels->operator [](0)->Text);
  StatusBar->Panels->operator [](0)->Width = TextLength+10;
  StatusBar->Panels->operator [](1)->Text = UserLogin;
  TextLength = this->Canvas->TextWidth(StatusBar->Panels->operator [](1)->Text);
  StatusBar->Panels->operator [](1)->Width = TextLength+10;
  StatusBar->Panels->operator [](2)->Text = UserName;
  TextLength = this->Canvas->TextWidth(StatusBar->Panels->operator [](2)->Text);
  StatusBar->Panels->operator [](2)->Width = TextLength+10;
  // подключение базы данных статистики
  DataSource_Stat->DataSet = Table_Stat;
  Table_Stat->DatabaseName = Patch + "Base\\";
  Table_Stat->TableName = "STAT.db";
  Table_Stat->Open();
  Table_Stat->Active = true;
  // подключение базы истории взятия/сдачи книг
  DBGrid_Hist->DataSource = DataSource_Hist;
  DataSource_Hist->DataSet = Query_Hist;
  Query_Hist->DatabaseName = Patch + "Base\\";
  Query_Hist->SQL->Clear();
  Query_Hist->SQL->Add("SELECT Book.BOOK_AUTHOR, Book.BOOK_NAME, Reader.READER_FIO, Hist.HIST_MAX_DAY, Hist.HIST_DATE_OUT, Hist.HIST_DAY_IN_PLAN, Hist.HIST_DATE_IN");
  Query_Hist->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book, \"READER.db\" Reader");
  Query_Hist->SQL->Add("WHERE (Book.BOOK_ID = Hist.HIST_BOOK_ID) AND (Reader.READER_ID = Hist.HIST_REDER_ID)");
  Query_Hist->ExecSQL();
  Query_Hist->Open();
  Query_Hist->Active = true;
  // подпись столбцов и установка ширины
  for (int i=0; i<7; i++)
    {
      DBGrid_Hist->Columns->operator [](i)->Title->Caption = Ini->ReadString("Grid_Hist","col_name_"+IntToStr(i+1),"Title");
      DBGrid_Hist->Columns->operator [](i)->Width = Ini->ReadInteger("Grid_Hist","col_size_"+IntToStr(i+1),50);
    }
  // загрузка состояния чекбоксов
  CheckBox_Norm->Checked = Ini->ReadBool("CheckBox","CheckBox_Norm",true);
  CheckBox_Debt->Checked = Ini->ReadBool("CheckBox","CheckBox_Debt",true);
  CheckBox_Return->Checked = Ini->ReadBool("CheckBox","CheckBox_Return",true);
  // установка фильтра на выданные/возвращенные книги
  Query_Hist->Filtered = false;
  Query_Hist->Filter = "";
  if (CheckBox_Norm->Checked == true && CheckBox_Return->Checked == true)
    {
      Query_Hist->Filter = "";
    }
  if (CheckBox_Norm->Checked == false && CheckBox_Return->Checked == false)
    {
      Query_Hist->Filter = "HIST_DATE_IN IS NULL AND HIST_DATE_IN IS NOT NULL";
    }
  if (CheckBox_Norm->Checked == false && CheckBox_Return->Checked == true)
    {
      Query_Hist->Filter = "HIST_DATE_IN IS NOT NULL";
    }
  if (CheckBox_Norm->Checked == true && CheckBox_Return->Checked == false)
    {
      Query_Hist->Filter = "HIST_DATE_IN IS NULL";
    }
  Query_Hist->Filtered = true;
  // передача фокуса основной таблице
  DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::FormResize(TObject *Sender)
{
  AnsiString Patch;           // переменная для пути к программе
  TIniFile *Ini;              // переменная для работы с INI файлом
  int WindowState;            // флаг максимизации окна

  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // запись настроек
  Ini = new TIniFile(Patch+"Settings.ini");
  WindowState = Ini->ReadInteger("PROG","WindowState",0);
  if (Form_Bibliotheka->Top == -4 && Form_Bibliotheka->Left == -4 && WindowState == 0)
    {
      Ini->WriteInteger("PROG","WindowState",1);
    }
  else if ((Form_Bibliotheka->Top != -4 || Form_Bibliotheka->Left != -4) && WindowState == 1)
    {
      Ini->WriteInteger("PROG","WindowState",0);
    }
  else if ((Form_Bibliotheka->Top != -4 || Form_Bibliotheka->Left != -4) && WindowState == 0)
    {
      Ini->WriteInteger("PROG","Top",Form_Bibliotheka->Top);
      Ini->WriteInteger("PROG","Left",Form_Bibliotheka->Left);
      Ini->WriteInteger("PROG","Height",Form_Bibliotheka->Height);
      Ini->WriteInteger("PROG","Width",Form_Bibliotheka->Width);
    }
  // изменение размеров таблицы
  DBGrid_Hist->Width = Form_Bibliotheka->Width-24;
  DBGrid_Hist->Height = Form_Bibliotheka->Height-143;
  // изменение положения чекбоксов
  CheckBox_Norm->Top = DBGrid_Hist->Top+DBGrid_Hist->Height+15;
  CheckBox_Debt->Top = CheckBox_Norm->Top;
  CheckBox_Return->Top = CheckBox_Norm->Top;
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::FormClose(TObject *Sender, TCloseAction &Action)
{
  AnsiString Patch;           // переменная для пути к программе
  TIniFile *Ini;              // переменная для работы с INI файлом
  AnsiString UserLogin;       // краткое имя работника
  int Session_Id;             // номер входа в ПО

  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // чтение текущей сессии
  Ini = new TIniFile(Patch+"Settings.ini");
  Session_Id = Ini->ReadInteger("CURRENT","Id_Num",-1);
  // переход к записи о текущей сессии
  Table_Stat->Last();
  while (Table_Stat->FieldByName("STAT_ID")->AsInteger > Session_Id)
    {
      Table_Stat->Prior();
    }
  // запись информации о входе
  Table_Stat->Edit();
  Table_Stat->FieldByName("STAT_DATA_OUT")->AsDateTime = Date();
  Table_Stat->FieldByName("STAT_TIME_OUT")->AsDateTime = Time();
  Table_Stat->UpdateRecord();
  Table_Stat->Post();
  // закрытие таблицы
  Table_Stat->Close();
  // заверщение программы
  exit(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::SpeedButton1Click(TObject *Sender)
{
  // вызов операции добавления читателя
  Form_Bibliotheka->Enabled = false;
  Form_Reader_Add->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::SpeedButton2Click(TObject *Sender)
{
  // вызов операции добавления книги
  Form_Bibliotheka->Enabled = false;
  Form_Book_Add->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::DBGrid_HistMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
  AnsiString Patch;           // переменная для пути к программе
  TIniFile *Ini;              // переменная для работы с INI файлом

  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // сохранение ширины
  Ini = new TIniFile(Patch+"Settings.ini");
  for (int i=0; i<7; i++)
    {
      Ini->WriteInteger("Grid_Hist","col_size_"+IntToStr(i+1),DBGrid_Hist->Columns->operator [](i)->Width);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::SpeedButton3Click(TObject *Sender)
{
  // вызов операции выдачи книги
  Form_Bibliotheka->Enabled = false;
  Form_Book_Out->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::SpeedButton4Click(TObject *Sender)
{
  // вызов операции сдачи книги
  Form_Bibliotheka->Enabled = false;
  Form_Book_In->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::SpeedButton_ExitClick(TObject *Sender)
{
  AnsiString Patch;           // переменная для пути к программе
  TIniFile *Ini;              // переменная для работы с INI файлом
  AnsiString UserLogin;       // краткое имя работника
  int Session_Id;             // номер входа в ПО

  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // чтение текущей сессии
  Ini = new TIniFile(Patch+"Settings.ini");
  Session_Id = Ini->ReadInteger("CURRENT","Id_Num",-1);
  // переход к записи о текущей сессии
  Table_Stat->Last();
  while (Table_Stat->FieldByName("STAT_ID")->AsInteger > Session_Id)
    {
      Table_Stat->Prior();
    }
  // запись информации о входе
  Table_Stat->Edit();
  Table_Stat->FieldByName("STAT_DATA_OUT")->AsDateTime = Date();
  Table_Stat->FieldByName("STAT_TIME_OUT")->AsDateTime = Time();
  Table_Stat->UpdateRecord();
  Table_Stat->Post();
  // закрытие таблицы
  Table_Stat->Close();
  // заверщение программы
  exit(0);        
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::DBGrid_HistDrawDataCell(TObject *Sender, const TRect &Rect, TField *Field, TGridDrawState State)
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
  // рисование данных
  ((TDBGrid *)Sender)->Canvas->FillRect(Rect);
  ((TDBGrid *)Sender)->Canvas->TextOut(Rect.Left+10,Rect.Top+2,Field->Text);
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::DBGrid_HistDrawColumnCell(
      TObject *Sender, const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
  // выделение просроченных книг
  if (CheckBox_Debt->Checked)
    {
      if (Column->Field->DataSet->FieldByName("HIST_DAY_IN_PLAN")->AsDateTime < Date())
        {
          ((TDBGrid *)Sender)->Canvas->Brush->Color = clRed;
          ((TDBGrid *)Sender)->Canvas->Font->Color = clBlack;
          if (State.Contains(gdSelected))
            {
              ((TDBGrid *)Sender)->Canvas->Font->Style = TFontStyles() << fsBold;
            }
        }
    }
  DBGrid_Hist->DefaultDrawColumnCell(Rect, DataCol, Column, State);
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::CheckBox_DebtClick(TObject *Sender)
{
  AnsiString Patch;           // переменная для пути к программе
  TIniFile *Ini;              // переменная для работы с INI файлом

  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // сохранение состояния чекбокса
  Ini = new TIniFile(Patch+"Settings.ini");
  Ini->WriteBool("CheckBox","CheckBox_Debt",CheckBox_Debt->Checked);
  // иммитация вызова процедуры прорисовки
  if (Query_Hist->RecNo != 1)
    {
      Query_Hist->Prior();
      Query_Hist->Next();
    }
  else
   {
      Query_Hist->Next();
      Query_Hist->Prior();
   }
  // передача фокуса основной таблице
  DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::CheckBox_NormClick(TObject *Sender)
{
  AnsiString Patch;           // переменная для пути к программе
  TIniFile *Ini;              // переменная для работы с INI файлом

  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // сохранение состояния чекбокса
  Ini = new TIniFile(Patch+"Settings.ini");
  Ini->WriteBool("CheckBox","CheckBox_Norm",CheckBox_Norm->Checked);
  // установка фильтра на выданные/возвращенные книги
  Query_Hist->Filtered = false;
  Query_Hist->Filter = "";
  if (CheckBox_Norm->Checked == true && CheckBox_Return->Checked == true)
    {
      Query_Hist->Filter = "";
    }
  if (CheckBox_Norm->Checked == false && CheckBox_Return->Checked == false)
    {
      Query_Hist->Filter = "HIST_DATE_IN IS NULL AND HIST_DATE_IN IS NOT NULL";
    }
  if (CheckBox_Norm->Checked == false && CheckBox_Return->Checked == true)
    {
      Query_Hist->Filter = "HIST_DATE_IN IS NOT NULL";
    }
  if (CheckBox_Norm->Checked == true && CheckBox_Return->Checked == false)
    {
      Query_Hist->Filter = "HIST_DATE_IN IS NULL";
    }
  Query_Hist->Filtered = true;
  // передача фокуса основной таблице
  DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::CheckBox_ReturnClick(TObject *Sender)
{
  AnsiString Patch;           // переменная для пути к программе
  TIniFile *Ini;              // переменная для работы с INI файлом

  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // сохранение состояния чекбокса
  Ini = new TIniFile(Patch+"Settings.ini");
  Ini->WriteBool("CheckBox","CheckBox_Return",CheckBox_Return->Checked);
  // установка фильтра на выданные/возвращенные книги
  Query_Hist->Filtered = false;
  Query_Hist->Filter = "";
  if (CheckBox_Norm->Checked == true && CheckBox_Return->Checked == true)
    {
      Query_Hist->Filter = "";
    }
  if (CheckBox_Norm->Checked == false && CheckBox_Return->Checked == false)
    {
      Query_Hist->Filter = "HIST_DATE_IN IS NULL AND HIST_DATE_IN IS NOT NULL";
    }
  if (CheckBox_Norm->Checked == false && CheckBox_Return->Checked == true)
    {
      Query_Hist->Filter = "HIST_DATE_IN IS NOT NULL";
    }
  if (CheckBox_Norm->Checked == true && CheckBox_Return->Checked == false)
    {
      Query_Hist->Filter = "HIST_DATE_IN IS NULL";
    }
  Query_Hist->Filtered = true;
  // передача фокуса основной таблице
  DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm_Bibliotheka::SpeedButton_AboutClick(TObject *Sender)
{
  AnsiString Patch;           // переменная для пути к программе
  TIniFile *Ini;              // переменная для работы с INI файлом
  AnsiString Str1;            // строка 1 сообщения о программе
  AnsiString Str2;            // строка 2 сообщения о программе
  AnsiString Str3;            // строка 3 сообщения о программе
  AnsiString Str4;            // строка 4 сообщения о программе
  AnsiString Str5;            // строка 5 сообщения о программе

  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // чтение строк
  Ini = new TIniFile(Patch+"Settings.ini");
  Str1 = Ini->ReadString("About", "Str1", "Str1");
  Str2 = Ini->ReadString("About", "Str2", "Str2");
  Str3 = Ini->ReadString("About", "Str3", "Str3");
  Str4 = Ini->ReadString("About", "Str4", "Str4");
  Str5 = Ini->ReadString("About", "Str5", "Str5");
  // вывод сообщения
  Application->MessageBoxA(("\n"+Str1+"\n"+Str2+"\n"+Str3+"\n"+Str4+"\n"+Str5).c_str(), "О программе...", MB_OK|MB_ICONINFORMATION);

}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::SpeedButton5Click(TObject *Sender)
{
  // вызов операции администрирования
  Form_Bibliotheka->Enabled = false;
  Form_Admin->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Bibliotheka::SpeedButton6Click(TObject *Sender)
{
  // вызов операции подведения статистики
  Form_Bibliotheka->Enabled = false;
  Form_Stat->Show();          
}
//---------------------------------------------------------------------------

