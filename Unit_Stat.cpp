//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit_Bibliotheka.h"
#include "Unit_Stat.h"
#include <ComObj.hpp>
#include <stdio.h>
#include <dos.h>
#include <process.h>

#define xlCenter    -4108
#define xlLeft      -4131
#define xlRight     -4152
#define xlBottom    -4107
#define xlTop       -4160
#define xlNone      -4142
#define xlLandscape 2
#define xlPortrait  1
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_Stat *Form_Stat;
//---------------------------------------------------------------------------
__fastcall TForm_Stat::TForm_Stat(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_Stat::FormShow(TObject *Sender)
{
  AnsiString Patch;                   // переменная для пути к программе

  // загрузка иконки
  Form_Stat->Icon->LoadFromFile("Books-OGY.ico");
  // вывод окна в центре основной формы
  Form_Stat->Top = Form_Bibliotheka->Top + (Form_Bibliotheka->Height - Form_Stat->Height) / 2;
  Form_Stat->Left = Form_Bibliotheka->Left + (Form_Bibliotheka->Width - Form_Stat->Width) / 2;
  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  //
  DateTimePicker2->DateTime = Date();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Stat::SpeedButton1Click(TObject *Sender)
{
  // завершение операции создания статистики
  Form_Bibliotheka->Enabled = true;
  Form_Stat->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Stat::FormHide(TObject *Sender)
{
  // завершение операции создания статистики
  Form_Bibliotheka->Enabled = true;
  Form_Stat->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Stat::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  // завершение операции создания статистики
  Form_Bibliotheka->Enabled = true;
  Form_Stat->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Stat::SpeedButton2Click(TObject *Sender)
{
  AnsiString Patch;                   // переменная для пути к программе
  struct date d;                      // переменная для хранения даты
  struct time t;                      // переменная для хранения времени
  AnsiString FileName;                // переменная для имени файла
  char buf[100];                      // буферная строка
  FILE *out;                          // переменная для выгрузки данных
  STARTUPINFO si;                     // переменная параметров запускаемого процесса
  PROCESS_INFORMATION pi;             // переменная состояния запущенного процесса
  int res;                            // состояние запущенного процесса
  int count1, count2;                 // переменные для хранения количества записей
  TDateTime DT1, DT2, DT3;            // переменные для хранения даты-времени

  // определение текущей даты и времени
  getdate(&d);
  gettime(&t);
  // формирование имени файла
  sprintf (buf,"%4.0d.%2.0d.%2.0d",d.da_year,d.da_mon,d.da_day);
  for (int i=0; i<10; i++)
    {
      if (buf[i] == ' ')
        {
          buf[i] = '0';
        }
    }
  FileName = (AnsiString)buf;
  FileName += "_";
  sprintf (buf,"%2.0d.%2.0d.%2.0d",t.ti_hour,t.ti_min,t.ti_sec);
  for (int i=0; i<8; i++)
    {
      if (buf[i] == ' ')
        {
          buf[i] = '0';
        }
    }
  FileName += (AnsiString)buf;
  FileName += ".txt";
  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // создание и открытие файла для выгрузки данных
  out = fopen ((Patch+"STAT\\"+FileName).c_str(),"w");
  if (RadioButton1->Checked)
    {
      // общая статистика - подключение к базе книг
      Table1->DatabaseName = Patch + "Base\\";
      Table1->TableName = "BOOK.db";
      Table1->Open();
      Table1->Active = true;
      // вывод данных в файл
      fprintf (out,"Книг в библиотеке: %d\n", Table1->RecordCount);
      Table1->First();
      for (int i=0; i<Table1->RecordCount; i++)
        {
          fprintf (out,"%s, %s, %s г. изд.\n", Table1->FieldByName("BOOK_AUTHOR")->AsString,Table1->FieldByName("BOOK_NAME")->AsString, Table1->FieldByName("BOOK_YEAR")->AsString);
          Table1->Next();
        }
      // закрытие таблицы
      Table1->Close();
      Table1->Active = false;
    }
  if (RadioButton2->Checked)
    {
      // статистика по выдаче книг - подключение к базе книг и истории операций с книгами
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Book.BOOK_AUTHOR,Book.BOOK_NAME,Book.BOOK_YEAR,Hist.HIST_DATE_OUT");
      Query1->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book");
      Query1->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID");
      Query1->SQL->Add("AND Hist.HIST_DATE_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'");
      Query1->SQL->Add("ORDER BY Book.BOOK_AUTHOR,Book.BOOK_NAME,Book.BOOK_YEAR,Hist.HIST_DATE_OUT");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;
      // вывод данных в файл
      fprintf (out,"Выдач за период: %d\n", Query1->RecordCount);
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          fprintf (out,"%s, %s, %s г. изд., выдана %s\n", Query1->FieldByName("BOOK_AUTHOR")->AsString,Query1->FieldByName("BOOK_NAME")->AsString, Query1->FieldByName("BOOK_YEAR")->AsString, Query1->FieldByName("HIST_DATE_OUT")->AsString);
          Query1->Next();
        }
      // закрытие таблицы
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton3->Checked)
    {
      // статистика по cдаче книг - подключение к базе книг и истории операций с книгами
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Book.BOOK_AUTHOR,Book.BOOK_NAME,Book.BOOK_YEAR,Hist.HIST_DATE_IN");
      Query1->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book");
      Query1->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID");
      Query1->SQL->Add("AND Hist.HIST_DATE_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'");
      Query1->SQL->Add("ORDER BY Book.BOOK_AUTHOR,Book.BOOK_NAME,Book.BOOK_YEAR,Hist.HIST_DATE_IN");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;
      // вывод данных в файл
      fprintf (out,"Сдано за период: %d\n", Query1->RecordCount);
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          fprintf (out,"%s, %s, %s г. изд., cдана %s\n", Query1->FieldByName("BOOK_AUTHOR")->AsString,Query1->FieldByName("BOOK_NAME")->AsString, Query1->FieldByName("BOOK_YEAR")->AsString, Query1->FieldByName("HIST_DATE_IN")->AsString);
          Query1->Next();
        }
      // закрытие таблицы
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton4->Checked)
    {
      // статистика по жанрам книг - подключение к базе книг
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Book.BOOK_SECTION");
      Query1->SQL->Add("FROM \"BOOK.db\" Book");
      Query1->SQL->Add("GROUP BY Book.BOOK_SECTION");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;

      // вывод данных в файл
      fprintf (out,"Разделов книг: %d\n", Query1->RecordCount);
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          // получение подробной статистики по разделам о количестве выданных книг
          Query2->DatabaseName = Patch + "Base\\";
          Query2->SQL->Clear();
          Query2->SQL->Add("SELECT Book.BOOK_AUTHOR,Book.BOOK_NAME,Book.BOOK_SECTION,Hist.HIST_DATE_IN,Hist.HIST_DATE_OUT");
          Query2->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book");
          Query2->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID AND Book.BOOK_SECTION = \'"+Query1->FieldByName("BOOK_SECTION")->AsString+"\'");
          Query2->SQL->Add("AND (Hist.HIST_DATE_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
          Query2->SQL->Add("ORDER BY Book.BOOK_AUTHOR,Book.BOOK_NAME,Hist.HIST_DATE_OUT,Hist.HIST_DATE_IN");
          Query2->ExecSQL();
          Query2->Open();
          Query2->Active = true;
          count1 = Query2->RecordCount;
          Query2->Close();
          Query2->Active = false;
          // получение подробной статистики по разделам о количестве cданных книг
          Query2->DatabaseName = Patch + "Base\\";
          Query2->SQL->Clear();
          Query2->SQL->Add("SELECT Book.BOOK_AUTHOR,Book.BOOK_NAME,Book.BOOK_SECTION,Hist.HIST_DATE_IN,Hist.HIST_DATE_OUT");
          Query2->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book");
          Query2->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID AND Book.BOOK_SECTION = \'"+Query1->FieldByName("BOOK_SECTION")->AsString+"\'");
          Query2->SQL->Add("AND (Hist.HIST_DATE_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
          Query2->SQL->Add("ORDER BY Book.BOOK_AUTHOR,Book.BOOK_NAME,Hist.HIST_DATE_OUT,Hist.HIST_DATE_IN");
          Query2->ExecSQL();
          Query2->Open();
          Query2->Active = true;
          count2 = Query2->RecordCount;
          Query2->Close();
          Query2->Active = false;
          // получение подробной статистики по разделам подробно по книгам
          Query2->SQL->Clear();
          Query2->SQL->Add("SELECT Book.BOOK_AUTHOR,Book.BOOK_NAME,Book.BOOK_SECTION,Book.BOOK_YEAR,Hist.HIST_DATE_IN,Hist.HIST_DATE_OUT");
          Query2->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book");
          Query2->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID AND Book.BOOK_SECTION = \'"+Query1->FieldByName("BOOK_SECTION")->AsString+"\'");
          Query2->SQL->Add("AND ((Hist.HIST_DATE_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
          Query2->SQL->Add("OR (Hist.HIST_DATE_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'))");
          Query2->SQL->Add("ORDER BY Book.BOOK_AUTHOR,Book.BOOK_NAME,Hist.HIST_DATE_OUT,Hist.HIST_DATE_IN");
          Query2->ExecSQL();
          Query2->Open();
          Query2->Active = true;
          // вывод промежуточной информации о разделе
          fprintf (out,"Раздел \'%s\': выдач %d, сдач %d\n", Query1->FieldByName("BOOK_SECTION")->AsString, count1, count2);
          // формирование строки для вывода в отчет
          Query2->First();
          for (int i=0; i<Query2->RecordCount; i++)
            {
              if ((int)Query2->FieldByName("HIST_DATE_IN")->AsDateTime < 10)
                {
                  fprintf (out,"\t%s, %s, %s г. изд., выдана %s\n", Query2->FieldByName("BOOK_AUTHOR")->AsString,Query2->FieldByName("BOOK_NAME")->AsString, Query2->FieldByName("BOOK_YEAR")->AsString, Query2->FieldByName("HIST_DATE_OUT")->AsString);
                }
              else
                {
                  fprintf (out,"\t%s, %s, %s г. изд., выдана %s, cдана %s\n", Query2->FieldByName("BOOK_AUTHOR")->AsString,Query2->FieldByName("BOOK_NAME")->AsString, Query2->FieldByName("BOOK_YEAR")->AsString, Query2->FieldByName("HIST_DATE_OUT")->AsString, Query2->FieldByName("HIST_DATE_IN")->AsString);
                }
              Query2->Next();
            }
          Query1->Next();
        }
      // закрытие таблицы
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
      Query2->Close();
      Query2->Active = false;
      Query2->SQL->Clear();
    }
  if (RadioButton5->Checked)
    {
      // общая статистика - подключение к базе книг
      Table1->DatabaseName = Patch + "Base\\";
      Table1->TableName = "READER.db";
      Table1->Open();
      Table1->Active = true;
      // вывод данных в файл
      fprintf (out,"Читателей в библиотеке: %d\n", Table1->RecordCount);
      Table1->First();
      for (int i=0; i<Table1->RecordCount; i++)
        {
          fprintf (out,"%s, %s, пасспорт %s\n", Table1->FieldByName("READER_FIO")->AsString,Table1->FieldByName("READER_ADRESS")->AsString, Table1->FieldByName("READER_PASSPORT")->AsString);
          Table1->Next();
        }
      // закрытие таблицы
      Table1->Close();
      Table1->Active = false;
    }
  if (RadioButton6->Checked)
    {
      // статистика по выдаче книг - подключение к базе книг и истории операций с книгами
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Reader.READER_FIO,Reader.READER_ADRESS,Reader.READER_PASSPORT, Book.BOOK_AUTHOR||Book.BOOK_NAME AS BOOK_INFO,Hist.HIST_DATE_OUT");
      Query1->SQL->Add("FROM \"HIST.db\" Hist, \"READER.db\" Reader, \"BOOK.db\" Book");
      Query1->SQL->Add("WHERE Reader.READER_ID = Hist.HIST_REDER_ID AND Book.BOOK_ID = Hist.HIST_BOOK_ID");
      Query1->SQL->Add("AND Hist.HIST_DATE_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'");
      Query1->SQL->Add("ORDER BY Reader.READER_FIO,Reader.READER_ADRESS,Reader.READER_PASSPORT,BOOK_INFO,Hist.HIST_DATE_OUT");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;
      // вывод данных в файл
      fprintf (out,"Выдач за период: %d\n", Query1->RecordCount);
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          fprintf (out,"%s, %s, пасспорт %s, %s, выдана %s\n", Query1->FieldByName("READER_FIO")->AsString,Query1->FieldByName("READER_ADRESS")->AsString, Query1->FieldByName("READER_PASSPORT")->AsString, Query1->FieldByName("BOOK_INFO")->AsString, Query1->FieldByName("HIST_DATE_OUT")->AsString);
          Query1->Next();
        }
      // закрытие таблицы
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton7->Checked)
    {
      // статистика по выдаче книг - подключение к базе книг и истории операций с книгами
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Reader.READER_FIO,Reader.READER_ADRESS,Reader.READER_PASSPORT, Book.BOOK_AUTHOR||Book.BOOK_NAME AS BOOK_INFO,Hist.HIST_DATE_IN");
      Query1->SQL->Add("FROM \"HIST.db\" Hist, \"READER.db\" Reader, \"BOOK.db\" Book");
      Query1->SQL->Add("WHERE Reader.READER_ID = Hist.HIST_REDER_ID AND Book.BOOK_ID = Hist.HIST_BOOK_ID");
      Query1->SQL->Add("AND Hist.HIST_DATE_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'");
      Query1->SQL->Add("ORDER BY Reader.READER_FIO,Reader.READER_ADRESS,Reader.READER_PASSPORT,BOOK_INFO,Hist.HIST_DATE_IN");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;
      // вывод данных в файл
      fprintf (out,"Cдач за период: %d\n", Query1->RecordCount);
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          fprintf (out,"%s, %s, пасспорт %s, %s, выдана %s\n", Query1->FieldByName("READER_FIO")->AsString,Query1->FieldByName("READER_ADRESS")->AsString, Query1->FieldByName("READER_PASSPORT")->AsString, Query1->FieldByName("BOOK_INFO")->AsString, Query1->FieldByName("HIST_DATE_IN")->AsString);
          Query1->Next();
        }
      // закрытие таблицы
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton8->Checked)
    {
      // общая статистика - подключение к базе книг
      Table1->DatabaseName = Patch + "Base\\";
      Table1->TableName = "USERS.db";
      Table1->Open();
      Table1->Active = true;
      // вывод данных в файл
      fprintf (out,"Сотрудников в библиотеке: %d\n", Table1->RecordCount);
      Table1->First();
      for (int i=0; i<Table1->RecordCount; i++)
        {
          fprintf (out,"%s - %s, %s, пасспорт %s\n", Table1->FieldByName("USER_S_NAME")->AsString, Table1->FieldByName("USER_F_NAME")->AsString, Table1->FieldByName("USER_ADRESS")->AsString, Table1->FieldByName("USER_PASSPORT")->AsString);
          Table1->Next();
        }
      // закрытие таблицы
      Table1->Close();
      Table1->Active = false;
    }
  if (RadioButton9->Checked)
    {
      // статистика по жанрам книг - подключение к базе книг
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Userr.USER_F_NAME,Userr.USER_S_NAME");
      Query1->SQL->Add("FROM \"USERS.db\" Userr");
      Query1->SQL->Add("ORDER BY Userr.USER_F_NAME,Userr.USER_S_NAME");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;

      // вывод данных в файл
      fprintf (out,"Сотрудников: %d\n", Query1->RecordCount);
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          // получение подробной статистики по сотрудникам
          Query2->DatabaseName = Patch + "Base\\";
          Query2->SQL->Clear();
          Query2->SQL->Add("SELECT *");
          Query2->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book, \"USERS.db\" Userr");
          Query2->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID AND Userr.USER_S_NAME = Hist.HIST_USER_OUT");
          Query2->SQL->Add("AND Userr.USER_S_NAME = \'"+Query1->FieldByName("USER_S_NAME")->AsString+"\'");
          Query2->SQL->Add("AND (Hist.HIST_DATE_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
          Query2->SQL->Add("ORDER BY Hist.HIST_DATE_OUT,Hist.HIST_DATE_IN");
          Query2->ExecSQL();
          Query2->Open();
          Query2->Active = true;
          count1 = Query2->RecordCount;
          Query2->Close();
          Query2->Active = false;
          // получение подробной статистики по разделам о количестве cданных книг
          Query2->DatabaseName = Patch + "Base\\";
          Query2->SQL->Clear();
          Query2->SQL->Add("SELECT *");
          Query2->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book, \"USERS.db\" Userr");
          Query2->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID AND Userr.USER_S_NAME = Hist.HIST_USER_IN");
          Query2->SQL->Add("AND Userr.USER_S_NAME = \'"+Query1->FieldByName("USER_S_NAME")->AsString+"\'");
          Query2->SQL->Add("AND (Hist.HIST_DATE_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
          Query2->SQL->Add("ORDER BY Hist.HIST_DATE_OUT,Hist.HIST_DATE_IN");
          Query2->ExecSQL();
          Query2->Open();
          Query2->Active = true;
          count2 = Query2->RecordCount;
          Query2->Close();
          Query2->Active = false;
          // получение подробной статистики по разделам подробно по книгам
          Query2->SQL->Clear();
          Query2->SQL->Add("SELECT *");
          Query2->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book, \"USERS.db\" Userr");
          Query2->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID AND (Userr.USER_S_NAME = Hist.HIST_USER_IN OR Userr.USER_S_NAME = Hist.HIST_USER_OUT)");
          Query2->SQL->Add("AND Userr.USER_S_NAME = \'"+Query1->FieldByName("USER_S_NAME")->AsString+"\'");
          Query2->SQL->Add("AND ((Hist.HIST_DATE_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
          Query2->SQL->Add("OR (Hist.HIST_DATE_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'))");
          Query2->SQL->Add("ORDER BY Hist.HIST_DATE_OUT,Hist.HIST_DATE_IN");
          Query2->ExecSQL();
          Query2->Open();
          Query2->Active = true;
          // вывод промежуточной информации о разделе
          fprintf (out,"Сотрудник \'%s (%s)\': выдач %d, сдач %d\n", Query1->FieldByName("USER_F_NAME")->AsString,Query1->FieldByName("USER_S_NAME")->AsString, count1, count2);
          // формирование строки для вывода в отчет
          Query2->First();
          for (int i=0; i<Query2->RecordCount; i++)
            { // Userr.USER_S_NAME = Hist.HIST_USER_IN OR Userr.USER_S_NAME = Hist.HIST_USER_OUT

              if (
                  Query2->FieldByName("HIST_USER_OUT")->AsString == Query1->FieldByName("USER_S_NAME")->AsString &&
                  Query2->FieldByName("HIST_USER_IN")->AsString == Query1->FieldByName("USER_S_NAME")->AsString
                 )
                {
                  fprintf (out,"\t%s, %s, %s г. изд., выдана %s, cдана %s\n", Query2->FieldByName("BOOK_AUTHOR")->AsString,Query2->FieldByName("BOOK_NAME")->AsString, Query2->FieldByName("BOOK_YEAR")->AsString, Query2->FieldByName("HIST_DATE_OUT")->AsString, Query2->FieldByName("HIST_DATE_IN")->AsString);
                }
              if (Query2->FieldByName("HIST_USER_OUT")->AsString == Query1->FieldByName("USER_S_NAME")->AsString)
                {
                  fprintf (out,"\t%s, %s, %s г. изд., выдана %s\n", Query2->FieldByName("BOOK_AUTHOR")->AsString,Query2->FieldByName("BOOK_NAME")->AsString, Query2->FieldByName("BOOK_YEAR")->AsString, Query2->FieldByName("HIST_DATE_OUT")->AsString);
                }
              else
                {
                  fprintf (out,"\t%s, %s, %s г. изд., cдана %s\n", Query2->FieldByName("BOOK_AUTHOR")->AsString,Query2->FieldByName("BOOK_NAME")->AsString, Query2->FieldByName("BOOK_YEAR")->AsString, Query2->FieldByName("HIST_DATE_IN")->AsString);
                }
              Query2->Next();
            }
          Query1->Next();
        }
      // закрытие таблицы
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
      Query2->Close();
      Query2->Active = false;
      Query2->SQL->Clear();
    }
  if (RadioButton10->Checked)
    {
      // статистика по жанрам книг - подключение к базе книг
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();/*
      Query1->SQL->Add("SELECT Userr.USER_F_NAME,Userr.USER_S_NAME");
      Query1->SQL->Add("FROM \"USERS.db\" Userr");
      Query1->SQL->Add("ORDER BY Userr.USER_F_NAME,Userr.USER_S_NAME");*/
          Query1->SQL->Add("SELECT Userr.USER_F_NAME,Userr.USER_S_NAME");
          Query1->SQL->Add("FROM \"STAT.db\" Stat, \"USERS.db\" Userr");
          Query1->SQL->Add("WHERE Stat.STAT_USER_S_NAME = Userr.USER_S_NAME");
          Query1->SQL->Add("AND ((Stat.STAT_DATA_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
          Query1->SQL->Add("OR (Stat.STAT_DATA_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'))");
          Query1->SQL->Add("GROUP BY Userr.USER_F_NAME,Userr.USER_S_NAME");
          Query1->SQL->Add("ORDER BY Userr.USER_F_NAME,Userr.USER_S_NAME");

      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;

      // вывод данных в файл
      fprintf (out,"Сотрудников: %d\n", Query1->RecordCount);
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          // получение подробной статистики по отработанным сменам
          Query2->DatabaseName = Patch + "Base\\";
          Query2->SQL->Clear();
          Query2->SQL->Add("SELECT *");
          Query2->SQL->Add("FROM \"STAT.db\" Stat, \"USERS.db\" Userr");
          Query2->SQL->Add("WHERE Stat.STAT_USER_S_NAME = Userr.USER_S_NAME");
          Query2->SQL->Add("AND Userr.USER_S_NAME = \'"+Query1->FieldByName("USER_S_NAME")->AsString+"\'");
          Query2->SQL->Add("AND ((Stat.STAT_DATA_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
          Query2->SQL->Add("OR (Stat.STAT_DATA_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'))");
          Query2->SQL->Add("ORDER BY Stat.STAT_DATA_IN,Stat.STAT_TIME_IN,Stat.STAT_DATA_OUT,Stat.STAT_TIME_OUT");
          Query2->ExecSQL();
          Query2->Open();
          Query2->Active = true;
          // вывод промежуточной информации о разделе
          fprintf (out,"Сотрудник \'%s\' (%s): %d входов в систему\n", Query1->FieldByName("USER_F_NAME")->AsString,Query1->FieldByName("USER_S_NAME")->AsString, Query2->RecordCount);
          // формирование строки для вывода в отчет
          Query2->First();
          for (int i=0; i<Query2->RecordCount; i++)
            {
              DT1 = Query2->FieldByName("STAT_DATA_IN")->AsDateTime + Query2->FieldByName("STAT_TIME_IN")->AsDateTime;
              DT2 = Query2->FieldByName("STAT_DATA_OUT")->AsDateTime + Query2->FieldByName("STAT_TIME_OUT")->AsDateTime;
              DT3 = DT2 - DT1; 
              fprintf (out,"%s %s", Query2->FieldByName("STAT_DATA_IN")->AsString,Query2->FieldByName("STAT_TIME_IN")->AsString);
              if ((int)Query2->FieldByName("STAT_DATA_OUT")->AsDateTime > 10)
                {
                  fprintf (out,", %s %s, %s\n", Query2->FieldByName("STAT_DATA_OUT")->AsString,Query2->FieldByName("STAT_TIME_OUT")->AsString, TimeToStr(DT3));
                }
              else
                {
                  fprintf (out,"\n");
                }
              Query2->Next();
            }
          Query1->Next();
        }
      // закрытие таблицы
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
      Query2->Close();
      Query2->Active = false;
      Query2->SQL->Clear();
    }

  // закрытие файла
  fclose(out);
  // открытие текстового файла для просмотра
  memset(&pi, 0, sizeof(pi));
  memset(&si, 0, sizeof(si));
  si.cb = sizeof(si);
  res = CreateProcess("notepad.exe", ("notepad.exe STAT\\"+FileName).c_str(), 0, 0, 0, 0, 0, 0, &si, &pi);
  if (res)
    {
      WaitForSingleObject(pi.hThread, INFINITE);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Stat::SpeedButton3Click(TObject *Sender)
{
  AnsiString Patch;                   // переменная для пути к программе
  struct date d;                      // переменная для хранения даты
  struct time t;                      // переменная для хранения времени
  AnsiString FileName;                // переменная для имени файла
  char buf[100];                      // буферная строка
  int count1, count2;                 // переменные для хранения количества записей
  int rownum;                         // переменная для номера строки в Excel
  Variant vApp;                       // приложение Excel
  Variant vBooks;                     // книги Excel
  Variant vBook;                      // рабочая (активная) книга Excel
  Variant vSheets;                    // страницы книги Excel
  Variant vSheet;                     // рабочая (активная) страница Excel
  Variant vCells;                     // ячейки страницы Excel
  Variant vCell;                      // рабочая (активная) ячейка Excel
  Variant vPage;                      // страница Excel (печатная)
  AnsiString Value;                   // выводимые данные
  TDateTime DT1, DT2, DT3;            // переменные для хранения даты-времени

  // определение текущей даты и времени
  getdate(&d);
  gettime(&t);
  // формирование имени файла
  sprintf (buf,"%4.0d.%2.0d.%2.0d",d.da_year,d.da_mon,d.da_day);
  for (int i=0; i<10; i++)
    {
      if (buf[i] == ' ')
        {
          buf[i] = '0';
        }
    }
  FileName = (AnsiString)buf;
  FileName += "_";
  sprintf (buf,"%2.0d.%2.0d.%2.0d",t.ti_hour,t.ti_min,t.ti_sec);
  for (int i=0; i<8; i++)
    {
      if (buf[i] == ' ')
        {
          buf[i] = '0';
        }
    }
  FileName += (AnsiString)buf;
  FileName += ".xls";
  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // запуска сервера Microsoft Excel
  try
    {
      vApp=CreateOleObject("Excel.Application");
    }
  catch(...)
    {
      MessageBox(0, "Ошибка при запуске сервера Excel", "Ошибка", MB_OK);
      return;
    }
  // создание файла Excel с определенным именем
  vBooks = vApp.OlePropertyGet("Workbooks");
  vApp.OlePropertySet("SheetsInNewWorkbook", 1);
  vBooks.OleProcedure("Add");
  vBook  = vBooks.OlePropertyGet("Item",1);
  vBook.OleProcedure("SaveAs", (Patch+"STAT\\"+FileName).c_str());
  vSheets= vBook.OlePropertyGet("Worksheets") ;
  vSheet = vSheets.OlePropertyGet("Item",1);
  // отключение сообщений
  vApp.OlePropertySet("DisplayAlerts", false);
  // вывод данных
  if (RadioButton1->Checked)
    {
      // общая статистика - подключение к базе книг
      Table1->DatabaseName = Patch + "Base\\";
      Table1->TableName = "BOOK.db";
      Table1->Open();
      Table1->Active = true;
      // вывод общих данных в файл
      Value = "Книг в библиотеке: "+IntToStr(Table1->RecordCount);
      // вывод шапки таблицы и ширины колонок
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","Автор");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","Название");
      vCell.OlePropertySet("ColumnWidth", 75);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","Год издания");
      vCell.OlePropertySet("ColumnWidth", 12);
      // задание формата шапки
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:C3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // вывод таблицы
      rownum = 4;
      for (int i=0; i<Table1->RecordCount; i++)
        {
          Value = Table1->FieldByName("BOOK_AUTHOR")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());

          Value = Table1->FieldByName("BOOK_NAME")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("B"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());

          Value = Table1->FieldByName("BOOK_YEAR")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("C"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());

          Table1->Next();
          rownum++;
        }
      // задание формата колонок
      vCell = vSheet.OlePropertyGet("Range", ("A4:A"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("B4:B"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("C4:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      // рисование границ таблицы
      vCell = vSheet.OlePropertyGet("Range", ("A3:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertyGet("Borders",7).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("ColorIndex",1);
      // закрытие таблицы
      Table1->Close();
      Table1->Active = false;
    }
  if (RadioButton2->Checked)
    {
      // статистика по выдаче книг - подключение к базе книг и истории операций с книгами
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Book.BOOK_AUTHOR,Book.BOOK_NAME,Book.BOOK_YEAR,Hist.HIST_DATE_OUT");
      Query1->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book");
      Query1->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID");
      Query1->SQL->Add("AND Hist.HIST_DATE_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'");
      Query1->SQL->Add("ORDER BY Book.BOOK_AUTHOR,Book.BOOK_NAME,Book.BOOK_YEAR,Hist.HIST_DATE_OUT");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;
      // вывод общих данных в файл
      Value = "Выдач за период: "+IntToStr(Query1->RecordCount);
      // вывод шапки таблицы и ширины колонок
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","Автор");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","Название");
      vCell.OlePropertySet("ColumnWidth", 75);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","Год издания");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","Дата выдачи");
      vCell.OlePropertySet("ColumnWidth", 12);
      // задание формата шапки
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:D3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // вывод таблицы
      rownum = 4;
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          Value = Query1->FieldByName("BOOK_AUTHOR")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Query1->FieldByName("BOOK_NAME")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("B"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Query1->FieldByName("BOOK_YEAR")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("C"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Query1->FieldByName("HIST_DATE_OUT")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("D"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Query1->Next();
          rownum++;
        }
      // задание формата колонок
      vCell = vSheet.OlePropertyGet("Range", ("A4:A"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("B4:B"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("C4:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      vCell = vSheet.OlePropertyGet("Range", ("D4:D"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      // рисование границ таблицы
      vCell = vSheet.OlePropertyGet("Range", ("A3:D"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertyGet("Borders",7).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("ColorIndex",1);
      // закрытие таблицы
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton3->Checked)
    {
      // статистика по выдаче книг - подключение к базе книг и истории операций с книгами
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Book.BOOK_AUTHOR,Book.BOOK_NAME,Book.BOOK_YEAR,Hist.HIST_DATE_IN");
      Query1->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book");
      Query1->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID");
      Query1->SQL->Add("AND Hist.HIST_DATE_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'");
      Query1->SQL->Add("ORDER BY Book.BOOK_AUTHOR,Book.BOOK_NAME,Book.BOOK_YEAR,Hist.HIST_DATE_IN");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;
      // вывод общих данных в файл
      Value = "Выдач за период: "+IntToStr(Query1->RecordCount);
      // вывод шапки таблицы и ширины колонок
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","Автор");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","Название");
      vCell.OlePropertySet("ColumnWidth", 75);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","Год издания");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","Дата cдачи");
      vCell.OlePropertySet("ColumnWidth", 12);
      // задание формата шапки
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:D3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // вывод таблицы
      rownum = 4;
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          Value = Query1->FieldByName("BOOK_AUTHOR")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Query1->FieldByName("BOOK_NAME")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("B"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Query1->FieldByName("BOOK_YEAR")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("C"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Query1->FieldByName("HIST_DATE_IN")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("D"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Query1->Next();
          rownum++;
        }
      // задание формата колонок
      vCell = vSheet.OlePropertyGet("Range", ("A4:A"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("B4:B"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("C4:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      vCell = vSheet.OlePropertyGet("Range", ("D4:D"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      // рисование границ таблицы
      vCell = vSheet.OlePropertyGet("Range", ("A3:D"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertyGet("Borders",7).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("ColorIndex",1);
      // закрытие таблицы
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton4->Checked)
    {
      // статистика по жанрам книг - подключение к базе книг
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Book.BOOK_SECTION");
      Query1->SQL->Add("FROM \"BOOK.db\" Book");
      Query1->SQL->Add("GROUP BY Book.BOOK_SECTION");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;

      // вывод общих данных в файл
      Value = "Разделов книг: "+IntToStr(Query1->RecordCount);
      // вывод шапки таблицы и ширины колонок
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","Автор");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","Название");
      vCell.OlePropertySet("ColumnWidth", 75);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","Год издания");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","Дата выдачи");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "E3");
      vCell.OlePropertySet("Value","Дата cдачи");
      vCell.OlePropertySet("ColumnWidth", 12);
      // задание формата шапки
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:E3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // вывод таблицы
      rownum = 4;
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          // получение подробной статистики по разделам о количестве выданных книг
          Query2->DatabaseName = Patch + "Base\\";
          Query2->SQL->Clear();
          Query2->SQL->Add("SELECT Book.BOOK_AUTHOR,Book.BOOK_NAME,Book.BOOK_SECTION,Hist.HIST_DATE_IN,Hist.HIST_DATE_OUT");
          Query2->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book");
          Query2->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID AND Book.BOOK_SECTION = \'"+Query1->FieldByName("BOOK_SECTION")->AsString+"\'");
          Query2->SQL->Add("AND (Hist.HIST_DATE_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
          Query2->SQL->Add("ORDER BY Book.BOOK_AUTHOR,Book.BOOK_NAME,Hist.HIST_DATE_OUT,Hist.HIST_DATE_IN");
          Query2->ExecSQL();
          Query2->Open();
          Query2->Active = true;
          count1 = Query2->RecordCount;
          Query2->Close();
          Query2->Active = false;
          // получение подробной статистики по разделам о количестве cданных книг
          Query2->DatabaseName = Patch + "Base\\";
          Query2->SQL->Clear();
          Query2->SQL->Add("SELECT Book.BOOK_AUTHOR,Book.BOOK_NAME,Book.BOOK_SECTION,Hist.HIST_DATE_IN,Hist.HIST_DATE_OUT");
          Query2->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book");
          Query2->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID AND Book.BOOK_SECTION = \'"+Query1->FieldByName("BOOK_SECTION")->AsString+"\'");
          Query2->SQL->Add("AND (Hist.HIST_DATE_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
          Query2->SQL->Add("ORDER BY Book.BOOK_AUTHOR,Book.BOOK_NAME,Hist.HIST_DATE_OUT,Hist.HIST_DATE_IN");
          Query2->ExecSQL();
          Query2->Open();
          Query2->Active = true;
          count2 = Query2->RecordCount;
          Query2->Close();
          Query2->Active = false;
          // получение подробной статистики по разделам подробно по книгам
          Query2->SQL->Clear();
          Query2->SQL->Add("SELECT Book.BOOK_AUTHOR,Book.BOOK_NAME,Book.BOOK_SECTION,Book.BOOK_YEAR,Hist.HIST_DATE_IN,Hist.HIST_DATE_OUT");
          Query2->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book");
          Query2->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID AND Book.BOOK_SECTION = \'"+Query1->FieldByName("BOOK_SECTION")->AsString+"\'");
          Query2->SQL->Add("AND ((Hist.HIST_DATE_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
          Query2->SQL->Add("OR (Hist.HIST_DATE_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'))");
          Query2->SQL->Add("ORDER BY Book.BOOK_AUTHOR,Book.BOOK_NAME,Hist.HIST_DATE_OUT,Hist.HIST_DATE_IN");
          Query2->ExecSQL();
          Query2->Open();
          Query2->Active = true;
          // вывод промежуточной информации о разделе
          Value = "          Раздел \'"+Query1->FieldByName("BOOK_SECTION")->AsString+"\': выдач "+IntToStr(count1)+", сдач "+IntToStr(count2);
          vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          rownum++;
          // формирование строки для вывода в отчет
          Query2->First();
          for (int i=0; i<Query2->RecordCount; i++)
            {
              Value = Query2->FieldByName("BOOK_AUTHOR")->AsString;
              vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
              vCell.OlePropertySet("Value",Value.c_str());
              Value = Query2->FieldByName("BOOK_NAME")->AsString;
              vCell = vSheet.OlePropertyGet("Range", ("B"+IntToStr(rownum)).c_str());
              vCell.OlePropertySet("Value",Value.c_str());
              Value = Query2->FieldByName("BOOK_YEAR")->AsString;
              vCell = vSheet.OlePropertyGet("Range", ("C"+IntToStr(rownum)).c_str());
              vCell.OlePropertySet("Value",Value.c_str());
              Value = Query2->FieldByName("HIST_DATE_OUT")->AsString;
              vCell = vSheet.OlePropertyGet("Range", ("D"+IntToStr(rownum)).c_str());
              vCell.OlePropertySet("Value",Value.c_str());
              Value = Query2->FieldByName("HIST_DATE_IN")->AsString;
              vCell = vSheet.OlePropertyGet("Range", ("E"+IntToStr(rownum)).c_str());
              vCell.OlePropertySet("Value",Value.c_str());
              Query2->Next();
              rownum++;
            }
          Query1->Next();
        }
      // задание формата колонок
      vCell = vSheet.OlePropertyGet("Range", ("A4:A"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("B4:B"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("C4:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      vCell = vSheet.OlePropertyGet("Range", ("D4:D"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      vCell = vSheet.OlePropertyGet("Range", ("E4:E"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      // рисование границ таблицы
      vCell = vSheet.OlePropertyGet("Range", ("A3:E"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertyGet("Borders",7).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("ColorIndex",1);
      // закрытие таблицы
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
      Query2->Close();
      Query2->Active = false;
      Query2->SQL->Clear();
    }
  if (RadioButton5->Checked)
    {
      // общая статистика - подключение к базе книг
      Table1->DatabaseName = Patch + "Base\\";
      Table1->TableName = "READER.db";
      Table1->Open();
      Table1->Active = true;
      // вывод общих данных в файл
      Value = "Читателей в библиотеке: "+IntToStr(Table1->RecordCount);
      // вывод шапки таблицы и ширины колонок
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","Фамилия Имя Отчество");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","Адрес");
      vCell.OlePropertySet("ColumnWidth", 50);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","Паспорт");
      vCell.OlePropertySet("ColumnWidth", 12);
      // задание формата шапки
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:C3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // вывод таблицы
      rownum = 4;
      for (int i=0; i<Table1->RecordCount; i++)
        {
          Value = Table1->FieldByName("READER_FIO")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());

          Value = Table1->FieldByName("READER_ADRESS")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("B"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());

          Value = Table1->FieldByName("READER_PASSPORT")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("C"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());

          Table1->Next();
          rownum++;
        }
      // задание формата колонок
      vCell = vSheet.OlePropertyGet("Range", ("A4:A"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("B4:B"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("C4:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      // рисование границ таблицы
      vCell = vSheet.OlePropertyGet("Range", ("A3:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertyGet("Borders",7).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("ColorIndex",1);
      // закрытие таблицы
      Table1->Close();
      Table1->Active = false;
    }
  if (RadioButton6->Checked)
    {
      // статистика по выдаче книг - подключение к базе книг и истории операций с книгами
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Reader.READER_FIO,Reader.READER_ADRESS,Reader.READER_PASSPORT, Book.BOOK_AUTHOR||Book.BOOK_NAME AS BOOK_INFO,Hist.HIST_DATE_OUT");
      Query1->SQL->Add("FROM \"HIST.db\" Hist, \"READER.db\" Reader, \"BOOK.db\" Book");
      Query1->SQL->Add("WHERE Reader.READER_ID = Hist.HIST_REDER_ID AND Book.BOOK_ID = Hist.HIST_BOOK_ID");
      Query1->SQL->Add("AND Hist.HIST_DATE_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'");
      Query1->SQL->Add("ORDER BY Reader.READER_FIO,Reader.READER_ADRESS,Reader.READER_PASSPORT,BOOK_INFO,Hist.HIST_DATE_OUT");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;
      // вывод общих данных в файл
      Value = "Выдач за период: "+IntToStr(Query1->RecordCount);
      // вывод шапки таблицы и ширины колонок
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","Читатель");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","Адрес");
      vCell.OlePropertySet("ColumnWidth", 50);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","Паспорт");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","Информация о книге");
      vCell.OlePropertySet("ColumnWidth", 75);
      vCell = vSheet.OlePropertyGet("Range", "E3");
      vCell.OlePropertySet("Value","Дата выдачи");
      vCell.OlePropertySet("ColumnWidth", 12);
      // задание формата шапки
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:E3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // вывод таблицы
      rownum = 4;
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          Value = Query1->FieldByName("READER_FIO")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Query1->FieldByName("READER_ADRESS")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("B"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Query1->FieldByName("READER_PASSPORT")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("C"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Query1->FieldByName("BOOK_INFO")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("D"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Query1->FieldByName("HIST_DATE_OUT")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("E"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Query1->Next();
          rownum++;
        }
      // задание формата колонок
      vCell = vSheet.OlePropertyGet("Range", ("A4:A"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("B4:B"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("C4:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      vCell = vSheet.OlePropertyGet("Range", ("D4:D"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("D4:D"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      // рисование границ таблицы
      vCell = vSheet.OlePropertyGet("Range", ("A3:E"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertyGet("Borders",7).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("ColorIndex",1);
      // закрытие таблицы
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton7->Checked)
    {
      // статистика по cдаче книг - подключение к базе книг и истории операций с книгами
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Reader.READER_FIO,Reader.READER_ADRESS,Reader.READER_PASSPORT, Book.BOOK_AUTHOR||Book.BOOK_NAME AS BOOK_INFO,Hist.HIST_DATE_IN");
      Query1->SQL->Add("FROM \"HIST.db\" Hist, \"READER.db\" Reader, \"BOOK.db\" Book");
      Query1->SQL->Add("WHERE Reader.READER_ID = Hist.HIST_REDER_ID AND Book.BOOK_ID = Hist.HIST_BOOK_ID");
      Query1->SQL->Add("AND Hist.HIST_DATE_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'");
      Query1->SQL->Add("ORDER BY Reader.READER_FIO,Reader.READER_ADRESS,Reader.READER_PASSPORT,BOOK_INFO,Hist.HIST_DATE_IN");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;
      // вывод общих данных в файл
      Value = "Выдач за период: "+IntToStr(Query1->RecordCount);
      // вывод шапки таблицы и ширины колонок
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","Читатель");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","Адрес");
      vCell.OlePropertySet("ColumnWidth", 50);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","Паспорт");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","Информация о книге");
      vCell.OlePropertySet("ColumnWidth", 75);
      vCell = vSheet.OlePropertyGet("Range", "E3");
      vCell.OlePropertySet("Value","Дата cдачи");
      vCell.OlePropertySet("ColumnWidth", 12);
      // задание формата шапки
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:E3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // вывод таблицы
      rownum = 4;
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          Value = Query1->FieldByName("READER_FIO")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Query1->FieldByName("READER_ADRESS")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("B"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Query1->FieldByName("READER_PASSPORT")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("C"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Query1->FieldByName("BOOK_INFO")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("D"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Query1->FieldByName("HIST_DATE_IN")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("E"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Query1->Next();
          rownum++;
        }
      // задание формата колонок
      vCell = vSheet.OlePropertyGet("Range", ("A4:A"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("B4:B"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("C4:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      vCell = vSheet.OlePropertyGet("Range", ("D4:D"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("D4:D"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      // рисование границ таблицы
      vCell = vSheet.OlePropertyGet("Range", ("A3:E"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertyGet("Borders",7).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("ColorIndex",1);
      // закрытие таблицы
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton8->Checked)
    {
      // общая статистика - подключение к базе книг
      Table1->DatabaseName = Patch + "Base\\";
      Table1->TableName = "USERS.db";
      Table1->Open();
      Table1->Active = true;
      // вывод общих данных в файл
      Value = "Сотрудников в библиотеке: "+IntToStr(Table1->RecordCount);
      // вывод шапки таблицы и ширины колонок
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","Краткое имя");
      vCell.OlePropertySet("ColumnWidth", 13);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","Полное имя");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","Адрес");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","Паспорт");
      vCell.OlePropertySet("ColumnWidth", 12);
      // задание формата шапки
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:D3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // вывод таблицы
      rownum = 4;
      for (int i=0; i<Table1->RecordCount; i++)
        {
          Value = Table1->FieldByName("USER_S_NAME")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Table1->FieldByName("USER_F_NAME")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("B"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Table1->FieldByName("USER_ADRESS")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("C"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Value = Table1->FieldByName("USER_PASSPORT")->AsString;
          vCell = vSheet.OlePropertyGet("Range", ("D"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          Table1->Next();
          rownum++;
        }
      // задание формата колонок
      vCell = vSheet.OlePropertyGet("Range", ("A4:A"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("B4:B"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("C4:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      vCell = vSheet.OlePropertyGet("Range", ("D4:D"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      // рисование границ таблицы
      vCell = vSheet.OlePropertyGet("Range", ("A3:D"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertyGet("Borders",7).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("ColorIndex",1);
      // закрытие таблицы
      Table1->Close();
      Table1->Active = false;
    }
  if (RadioButton9->Checked)
    {
      // статистика по жанрам книг - подключение к базе книг
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Userr.USER_F_NAME,Userr.USER_S_NAME");
      Query1->SQL->Add("FROM \"USERS.db\" Userr");
      Query1->SQL->Add("ORDER BY Userr.USER_F_NAME,Userr.USER_S_NAME");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;

      // вывод общих данных в файл
      Value = "Сотрудников: "+IntToStr(Query1->RecordCount);
      // вывод шапки таблицы и ширины колонок
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","Автор");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","Название");
      vCell.OlePropertySet("ColumnWidth", 75);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","Год издания");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","Дата выдачи");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "E3");
      vCell.OlePropertySet("Value","Дата сдачи");
      vCell.OlePropertySet("ColumnWidth", 12);
      // задание формата шапки
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:E3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // вывод таблицы
      rownum = 4;
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          // получение подробной статистики по сотрудникам
          Query2->DatabaseName = Patch + "Base\\";
          Query2->SQL->Clear();
          Query2->SQL->Add("SELECT *");
          Query2->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book, \"USERS.db\" Userr");
          Query2->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID AND Userr.USER_S_NAME = Hist.HIST_USER_OUT");
          Query2->SQL->Add("AND Userr.USER_S_NAME = \'"+Query1->FieldByName("USER_S_NAME")->AsString+"\'");
          Query2->SQL->Add("AND (Hist.HIST_DATE_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
          Query2->SQL->Add("ORDER BY Hist.HIST_DATE_OUT,Hist.HIST_DATE_IN");
          Query2->ExecSQL();
          Query2->Open();
          Query2->Active = true;
          count1 = Query2->RecordCount;
          Query2->Close();
          Query2->Active = false;
          // получение подробной статистики по разделам о количестве cданных книг
          Query2->DatabaseName = Patch + "Base\\";
          Query2->SQL->Clear();
          Query2->SQL->Add("SELECT *");
          Query2->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book, \"USERS.db\" Userr");
          Query2->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID AND Userr.USER_S_NAME = Hist.HIST_USER_IN");
          Query2->SQL->Add("AND Userr.USER_S_NAME = \'"+Query1->FieldByName("USER_S_NAME")->AsString+"\'");
          Query2->SQL->Add("AND (Hist.HIST_DATE_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
          Query2->SQL->Add("ORDER BY Hist.HIST_DATE_OUT,Hist.HIST_DATE_IN");
          Query2->ExecSQL();
          Query2->Open();
          Query2->Active = true;
          count2 = Query2->RecordCount;
          Query2->Close();
          Query2->Active = false;
          // получение подробной статистики по разделам подробно по книгам
          Query2->SQL->Clear();
          Query2->SQL->Add("SELECT *");
          Query2->SQL->Add("FROM \"HIST.db\" Hist, \"BOOK.db\" Book, \"USERS.db\" Userr");
          Query2->SQL->Add("WHERE Book.BOOK_ID = Hist.HIST_BOOK_ID AND (Userr.USER_S_NAME = Hist.HIST_USER_IN OR Userr.USER_S_NAME = Hist.HIST_USER_OUT)");
          Query2->SQL->Add("AND Userr.USER_S_NAME = \'"+Query1->FieldByName("USER_S_NAME")->AsString+"\'");
          Query2->SQL->Add("AND ((Hist.HIST_DATE_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
          Query2->SQL->Add("OR (Hist.HIST_DATE_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'))");
          Query2->SQL->Add("ORDER BY Hist.HIST_DATE_OUT,Hist.HIST_DATE_IN");
          Query2->ExecSQL();
          Query2->Open();
          Query2->Active = true;
          // вывод промежуточной информации о сотруднике
          Value = "          Сотрудник \'"+Query1->FieldByName("USER_F_NAME")->AsString+"\' ("+Query1->FieldByName("USER_S_NAME")->AsString+"): выдач "+IntToStr(count1)+", сдач "+IntToStr(count2);
          vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          rownum++;
          // формирование строки для вывода в отчет
          Query2->First();
          for (int i=0; i<Query2->RecordCount; i++)
            {

              Value = Query2->FieldByName("BOOK_AUTHOR")->AsString;
              vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
              vCell.OlePropertySet("Value",Value.c_str());
              Value = Query2->FieldByName("BOOK_NAME")->AsString;
              vCell = vSheet.OlePropertyGet("Range", ("B"+IntToStr(rownum)).c_str());
              vCell.OlePropertySet("Value",Value.c_str());
              Value = Query2->FieldByName("BOOK_YEAR")->AsString;
              vCell = vSheet.OlePropertyGet("Range", ("C"+IntToStr(rownum)).c_str());
              vCell.OlePropertySet("Value",Value.c_str());
              if (Query2->FieldByName("HIST_USER_OUT")->AsString == Query1->FieldByName("USER_S_NAME")->AsString)
                {
                  Value = Query2->FieldByName("HIST_DATE_OUT")->AsString;
                  vCell = vSheet.OlePropertyGet("Range", ("D"+IntToStr(rownum)).c_str());
                  vCell.OlePropertySet("Value",Value.c_str());

                }
              if (Query2->FieldByName("HIST_USER_IN")->AsString == Query1->FieldByName("USER_S_NAME")->AsString)
                {
                  Value = Query2->FieldByName("HIST_DATE_IN")->AsString;
                  vCell = vSheet.OlePropertyGet("Range", ("E"+IntToStr(rownum)).c_str());
                  vCell.OlePropertySet("Value",Value.c_str());

                }
              Query2->Next();
              rownum++;
            }
          Query1->Next();
        }
      // задание формата колонок
      vCell = vSheet.OlePropertyGet("Range", ("A4:A"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("B4:B"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("C4:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      vCell = vSheet.OlePropertyGet("Range", ("D4:D"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      vCell = vSheet.OlePropertyGet("Range", ("E4:E"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      // рисование границ таблицы
      vCell = vSheet.OlePropertyGet("Range", ("A3:E"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertyGet("Borders",7).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",7).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",8).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",9).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",10).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",11).OlePropertySet("ColorIndex",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("LineStyle",1);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("Weight",2);
      vCell.OlePropertyGet("Borders",12).OlePropertySet("ColorIndex",1);
      // закрытие таблицы
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
      Query2->Close();
      Query2->Active = false;
      Query2->SQL->Clear();
    }
  if (RadioButton10->Checked)
    {
      // статистика по жанрам книг - подключение к базе книг
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Userr.USER_F_NAME,Userr.USER_S_NAME");
      Query1->SQL->Add("FROM \"STAT.db\" Stat, \"USERS.db\" Userr");
      Query1->SQL->Add("WHERE Stat.STAT_USER_S_NAME = Userr.USER_S_NAME");
      Query1->SQL->Add("AND ((Stat.STAT_DATA_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
      Query1->SQL->Add("OR (Stat.STAT_DATA_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'))");
      Query1->SQL->Add("GROUP BY Userr.USER_F_NAME,Userr.USER_S_NAME");
      Query1->SQL->Add("ORDER BY Userr.USER_F_NAME,Userr.USER_S_NAME");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;
      // вывод общих данных в файл
      Value = "Сотрудников: "+IntToStr(Query1->RecordCount);
      // вывод шапки таблицы и ширины колонок
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","Дата входа");
      vCell.OlePropertySet("ColumnWidth", 13);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","Время входа");
      vCell.OlePropertySet("ColumnWidth", 13);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","Дата выхода");
      vCell.OlePropertySet("ColumnWidth", 13);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","Время выхода");
      vCell.OlePropertySet("ColumnWidth", 13);
      vCell = vSheet.OlePropertyGet("Range", "E3");
      vCell.OlePropertySet("Value","Длительность");
      vCell.OlePropertySet("ColumnWidth", 13);
      // задание формата шапки
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:E3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // вывод таблицы
      rownum = 4;
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          // получение подробной статистики по отработанным сменам
          Query2->DatabaseName = Patch + "Base\\";
          Query2->SQL->Clear();
          Query2->SQL->Add("SELECT *");
          Query2->SQL->Add("FROM \"STAT.db\" Stat, \"USERS.db\" Userr");
          Query2->SQL->Add("WHERE Stat.STAT_USER_S_NAME = Userr.USER_S_NAME");
          Query2->SQL->Add("AND Userr.USER_S_NAME = \'"+Query1->FieldByName("USER_S_NAME")->AsString+"\'");
          Query2->SQL->Add("AND ((Stat.STAT_DATA_IN between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\')");
          Query2->SQL->Add("OR (Stat.STAT_DATA_OUT between \'"+DateToStr(DateTimePicker1->DateTime)+"\' AND \'"+DateToStr(DateTimePicker2->DateTime)+"\'))");
          Query2->SQL->Add("ORDER BY Stat.STAT_DATA_IN,Stat.STAT_TIME_IN,Stat.STAT_DATA_OUT,Stat.STAT_TIME_OUT");
          Query2->ExecSQL();
          Query2->Open();
          Query2->Active = true;
          // вывод промежуточной информации о разделе
          //fprintf (out,"Сотрудник \'%s\' (%s): %d входов в систему\n", Query1->FieldByName("USER_F_NAME")->AsString,Query1->FieldByName("USER_S_NAME")->AsString, Query2->RecordCount);
          Value = "          Сотрудник \'"+Query1->FieldByName("USER_F_NAME")->AsString+"\' ("+Query1->FieldByName("USER_S_NAME")->AsString+"): входов в систему "+IntToStr(Query2->RecordCount);
          vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          rownum++;
          // формирование строки для вывода в отчет
          Query2->First();
          for (int i=0; i<Query2->RecordCount; i++)
            {
              DT1 = Query2->FieldByName("STAT_DATA_IN")->AsDateTime + Query2->FieldByName("STAT_TIME_IN")->AsDateTime;
              DT2 = Query2->FieldByName("STAT_DATA_OUT")->AsDateTime + Query2->FieldByName("STAT_TIME_OUT")->AsDateTime;
              DT3 = DT2 - DT1; 

              Value = Query2->FieldByName("STAT_DATA_IN")->AsString;
              vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
              vCell.OlePropertySet("Value",Value.c_str());
              Value = Query2->FieldByName("STAT_TIME_IN")->AsString;
              vCell = vSheet.OlePropertyGet("Range", ("B"+IntToStr(rownum)).c_str());
              vCell.OlePropertySet("Value",Value.c_str());

              if ((int)Query2->FieldByName("STAT_DATA_OUT")->AsDateTime > 10)
                {
                  Value = Query2->FieldByName("STAT_DATA_OUT")->AsString;
                  vCell = vSheet.OlePropertyGet("Range", ("C"+IntToStr(rownum)).c_str());
                  vCell.OlePropertySet("Value",Value.c_str());
                  Value = Query2->FieldByName("STAT_TIME_OUT")->AsString;
                  vCell = vSheet.OlePropertyGet("Range", ("D"+IntToStr(rownum)).c_str());
                  vCell.OlePropertySet("Value",Value.c_str());
                  Value = TimeToStr(DT3);
                  vCell = vSheet.OlePropertyGet("Range", ("E"+IntToStr(rownum)).c_str());
                  vCell.OlePropertySet("Value",Value.c_str());
                }
              Query2->Next();
              rownum++;
            }
          Query1->Next();
        }
      // закрытие таблицы
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
      Query2->Close();
      Query2->Active = false;
      Query2->SQL->Clear();
    }
  // сохраняем изменения
  vBook.OleProcedure("Save");
  // включение сообщений
  vApp.OlePropertySet("DisplayAlerts", true);
  // делаем файл видимым
  vApp.OlePropertySet("Visible",true);
}
//---------------------------------------------------------------------------
