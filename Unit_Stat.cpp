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
  AnsiString Patch;                   // ���������� ��� ���� � ���������

  // �������� ������
  Form_Stat->Icon->LoadFromFile("Books-OGY.ico");
  // ����� ���� � ������ �������� �����
  Form_Stat->Top = Form_Bibliotheka->Top + (Form_Bibliotheka->Height - Form_Stat->Height) / 2;
  Form_Stat->Left = Form_Bibliotheka->Left + (Form_Bibliotheka->Width - Form_Stat->Width) / 2;
  // ����������� ���� � ���������
  Patch = ExtractFilePath(ParamStr(0));
  //
  DateTimePicker2->DateTime = Date();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Stat::SpeedButton1Click(TObject *Sender)
{
  // ���������� �������� �������� ����������
  Form_Bibliotheka->Enabled = true;
  Form_Stat->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Stat::FormHide(TObject *Sender)
{
  // ���������� �������� �������� ����������
  Form_Bibliotheka->Enabled = true;
  Form_Stat->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Stat::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  // ���������� �������� �������� ����������
  Form_Bibliotheka->Enabled = true;
  Form_Stat->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Stat::SpeedButton2Click(TObject *Sender)
{
  AnsiString Patch;                   // ���������� ��� ���� � ���������
  struct date d;                      // ���������� ��� �������� ����
  struct time t;                      // ���������� ��� �������� �������
  AnsiString FileName;                // ���������� ��� ����� �����
  char buf[100];                      // �������� ������
  FILE *out;                          // ���������� ��� �������� ������
  STARTUPINFO si;                     // ���������� ���������� ������������ ��������
  PROCESS_INFORMATION pi;             // ���������� ��������� ����������� ��������
  int res;                            // ��������� ����������� ��������
  int count1, count2;                 // ���������� ��� �������� ���������� �������
  TDateTime DT1, DT2, DT3;            // ���������� ��� �������� ����-�������

  // ����������� ������� ���� � �������
  getdate(&d);
  gettime(&t);
  // ������������ ����� �����
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
  // ����������� ���� � ���������
  Patch = ExtractFilePath(ParamStr(0));
  // �������� � �������� ����� ��� �������� ������
  out = fopen ((Patch+"STAT\\"+FileName).c_str(),"w");
  if (RadioButton1->Checked)
    {
      // ����� ���������� - ����������� � ���� ����
      Table1->DatabaseName = Patch + "Base\\";
      Table1->TableName = "BOOK.db";
      Table1->Open();
      Table1->Active = true;
      // ����� ������ � ����
      fprintf (out,"���� � ����������: %d\n", Table1->RecordCount);
      Table1->First();
      for (int i=0; i<Table1->RecordCount; i++)
        {
          fprintf (out,"%s, %s, %s �. ���.\n", Table1->FieldByName("BOOK_AUTHOR")->AsString,Table1->FieldByName("BOOK_NAME")->AsString, Table1->FieldByName("BOOK_YEAR")->AsString);
          Table1->Next();
        }
      // �������� �������
      Table1->Close();
      Table1->Active = false;
    }
  if (RadioButton2->Checked)
    {
      // ���������� �� ������ ���� - ����������� � ���� ���� � ������� �������� � �������
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
      // ����� ������ � ����
      fprintf (out,"����� �� ������: %d\n", Query1->RecordCount);
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          fprintf (out,"%s, %s, %s �. ���., ������ %s\n", Query1->FieldByName("BOOK_AUTHOR")->AsString,Query1->FieldByName("BOOK_NAME")->AsString, Query1->FieldByName("BOOK_YEAR")->AsString, Query1->FieldByName("HIST_DATE_OUT")->AsString);
          Query1->Next();
        }
      // �������� �������
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton3->Checked)
    {
      // ���������� �� c���� ���� - ����������� � ���� ���� � ������� �������� � �������
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
      // ����� ������ � ����
      fprintf (out,"����� �� ������: %d\n", Query1->RecordCount);
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          fprintf (out,"%s, %s, %s �. ���., c���� %s\n", Query1->FieldByName("BOOK_AUTHOR")->AsString,Query1->FieldByName("BOOK_NAME")->AsString, Query1->FieldByName("BOOK_YEAR")->AsString, Query1->FieldByName("HIST_DATE_IN")->AsString);
          Query1->Next();
        }
      // �������� �������
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton4->Checked)
    {
      // ���������� �� ������ ���� - ����������� � ���� ����
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Book.BOOK_SECTION");
      Query1->SQL->Add("FROM \"BOOK.db\" Book");
      Query1->SQL->Add("GROUP BY Book.BOOK_SECTION");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;

      // ����� ������ � ����
      fprintf (out,"�������� ����: %d\n", Query1->RecordCount);
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          // ��������� ��������� ���������� �� �������� � ���������� �������� ����
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
          // ��������� ��������� ���������� �� �������� � ���������� c������ ����
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
          // ��������� ��������� ���������� �� �������� �������� �� ������
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
          // ����� ������������� ���������� � �������
          fprintf (out,"������ \'%s\': ����� %d, ���� %d\n", Query1->FieldByName("BOOK_SECTION")->AsString, count1, count2);
          // ������������ ������ ��� ������ � �����
          Query2->First();
          for (int i=0; i<Query2->RecordCount; i++)
            {
              if ((int)Query2->FieldByName("HIST_DATE_IN")->AsDateTime < 10)
                {
                  fprintf (out,"\t%s, %s, %s �. ���., ������ %s\n", Query2->FieldByName("BOOK_AUTHOR")->AsString,Query2->FieldByName("BOOK_NAME")->AsString, Query2->FieldByName("BOOK_YEAR")->AsString, Query2->FieldByName("HIST_DATE_OUT")->AsString);
                }
              else
                {
                  fprintf (out,"\t%s, %s, %s �. ���., ������ %s, c���� %s\n", Query2->FieldByName("BOOK_AUTHOR")->AsString,Query2->FieldByName("BOOK_NAME")->AsString, Query2->FieldByName("BOOK_YEAR")->AsString, Query2->FieldByName("HIST_DATE_OUT")->AsString, Query2->FieldByName("HIST_DATE_IN")->AsString);
                }
              Query2->Next();
            }
          Query1->Next();
        }
      // �������� �������
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
      Query2->Close();
      Query2->Active = false;
      Query2->SQL->Clear();
    }
  if (RadioButton5->Checked)
    {
      // ����� ���������� - ����������� � ���� ����
      Table1->DatabaseName = Patch + "Base\\";
      Table1->TableName = "READER.db";
      Table1->Open();
      Table1->Active = true;
      // ����� ������ � ����
      fprintf (out,"��������� � ����������: %d\n", Table1->RecordCount);
      Table1->First();
      for (int i=0; i<Table1->RecordCount; i++)
        {
          fprintf (out,"%s, %s, �������� %s\n", Table1->FieldByName("READER_FIO")->AsString,Table1->FieldByName("READER_ADRESS")->AsString, Table1->FieldByName("READER_PASSPORT")->AsString);
          Table1->Next();
        }
      // �������� �������
      Table1->Close();
      Table1->Active = false;
    }
  if (RadioButton6->Checked)
    {
      // ���������� �� ������ ���� - ����������� � ���� ���� � ������� �������� � �������
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
      // ����� ������ � ����
      fprintf (out,"����� �� ������: %d\n", Query1->RecordCount);
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          fprintf (out,"%s, %s, �������� %s, %s, ������ %s\n", Query1->FieldByName("READER_FIO")->AsString,Query1->FieldByName("READER_ADRESS")->AsString, Query1->FieldByName("READER_PASSPORT")->AsString, Query1->FieldByName("BOOK_INFO")->AsString, Query1->FieldByName("HIST_DATE_OUT")->AsString);
          Query1->Next();
        }
      // �������� �������
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton7->Checked)
    {
      // ���������� �� ������ ���� - ����������� � ���� ���� � ������� �������� � �������
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
      // ����� ������ � ����
      fprintf (out,"C��� �� ������: %d\n", Query1->RecordCount);
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          fprintf (out,"%s, %s, �������� %s, %s, ������ %s\n", Query1->FieldByName("READER_FIO")->AsString,Query1->FieldByName("READER_ADRESS")->AsString, Query1->FieldByName("READER_PASSPORT")->AsString, Query1->FieldByName("BOOK_INFO")->AsString, Query1->FieldByName("HIST_DATE_IN")->AsString);
          Query1->Next();
        }
      // �������� �������
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton8->Checked)
    {
      // ����� ���������� - ����������� � ���� ����
      Table1->DatabaseName = Patch + "Base\\";
      Table1->TableName = "USERS.db";
      Table1->Open();
      Table1->Active = true;
      // ����� ������ � ����
      fprintf (out,"����������� � ����������: %d\n", Table1->RecordCount);
      Table1->First();
      for (int i=0; i<Table1->RecordCount; i++)
        {
          fprintf (out,"%s - %s, %s, �������� %s\n", Table1->FieldByName("USER_S_NAME")->AsString, Table1->FieldByName("USER_F_NAME")->AsString, Table1->FieldByName("USER_ADRESS")->AsString, Table1->FieldByName("USER_PASSPORT")->AsString);
          Table1->Next();
        }
      // �������� �������
      Table1->Close();
      Table1->Active = false;
    }
  if (RadioButton9->Checked)
    {
      // ���������� �� ������ ���� - ����������� � ���� ����
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Userr.USER_F_NAME,Userr.USER_S_NAME");
      Query1->SQL->Add("FROM \"USERS.db\" Userr");
      Query1->SQL->Add("ORDER BY Userr.USER_F_NAME,Userr.USER_S_NAME");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;

      // ����� ������ � ����
      fprintf (out,"�����������: %d\n", Query1->RecordCount);
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          // ��������� ��������� ���������� �� �����������
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
          // ��������� ��������� ���������� �� �������� � ���������� c������ ����
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
          // ��������� ��������� ���������� �� �������� �������� �� ������
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
          // ����� ������������� ���������� � �������
          fprintf (out,"��������� \'%s (%s)\': ����� %d, ���� %d\n", Query1->FieldByName("USER_F_NAME")->AsString,Query1->FieldByName("USER_S_NAME")->AsString, count1, count2);
          // ������������ ������ ��� ������ � �����
          Query2->First();
          for (int i=0; i<Query2->RecordCount; i++)
            { // Userr.USER_S_NAME = Hist.HIST_USER_IN OR Userr.USER_S_NAME = Hist.HIST_USER_OUT

              if (
                  Query2->FieldByName("HIST_USER_OUT")->AsString == Query1->FieldByName("USER_S_NAME")->AsString &&
                  Query2->FieldByName("HIST_USER_IN")->AsString == Query1->FieldByName("USER_S_NAME")->AsString
                 )
                {
                  fprintf (out,"\t%s, %s, %s �. ���., ������ %s, c���� %s\n", Query2->FieldByName("BOOK_AUTHOR")->AsString,Query2->FieldByName("BOOK_NAME")->AsString, Query2->FieldByName("BOOK_YEAR")->AsString, Query2->FieldByName("HIST_DATE_OUT")->AsString, Query2->FieldByName("HIST_DATE_IN")->AsString);
                }
              if (Query2->FieldByName("HIST_USER_OUT")->AsString == Query1->FieldByName("USER_S_NAME")->AsString)
                {
                  fprintf (out,"\t%s, %s, %s �. ���., ������ %s\n", Query2->FieldByName("BOOK_AUTHOR")->AsString,Query2->FieldByName("BOOK_NAME")->AsString, Query2->FieldByName("BOOK_YEAR")->AsString, Query2->FieldByName("HIST_DATE_OUT")->AsString);
                }
              else
                {
                  fprintf (out,"\t%s, %s, %s �. ���., c���� %s\n", Query2->FieldByName("BOOK_AUTHOR")->AsString,Query2->FieldByName("BOOK_NAME")->AsString, Query2->FieldByName("BOOK_YEAR")->AsString, Query2->FieldByName("HIST_DATE_IN")->AsString);
                }
              Query2->Next();
            }
          Query1->Next();
        }
      // �������� �������
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
      Query2->Close();
      Query2->Active = false;
      Query2->SQL->Clear();
    }
  if (RadioButton10->Checked)
    {
      // ���������� �� ������ ���� - ����������� � ���� ����
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

      // ����� ������ � ����
      fprintf (out,"�����������: %d\n", Query1->RecordCount);
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          // ��������� ��������� ���������� �� ������������ ������
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
          // ����� ������������� ���������� � �������
          fprintf (out,"��������� \'%s\' (%s): %d ������ � �������\n", Query1->FieldByName("USER_F_NAME")->AsString,Query1->FieldByName("USER_S_NAME")->AsString, Query2->RecordCount);
          // ������������ ������ ��� ������ � �����
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
      // �������� �������
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
      Query2->Close();
      Query2->Active = false;
      Query2->SQL->Clear();
    }

  // �������� �����
  fclose(out);
  // �������� ���������� ����� ��� ���������
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
  AnsiString Patch;                   // ���������� ��� ���� � ���������
  struct date d;                      // ���������� ��� �������� ����
  struct time t;                      // ���������� ��� �������� �������
  AnsiString FileName;                // ���������� ��� ����� �����
  char buf[100];                      // �������� ������
  int count1, count2;                 // ���������� ��� �������� ���������� �������
  int rownum;                         // ���������� ��� ������ ������ � Excel
  Variant vApp;                       // ���������� Excel
  Variant vBooks;                     // ����� Excel
  Variant vBook;                      // ������� (��������) ����� Excel
  Variant vSheets;                    // �������� ����� Excel
  Variant vSheet;                     // ������� (��������) �������� Excel
  Variant vCells;                     // ������ �������� Excel
  Variant vCell;                      // ������� (��������) ������ Excel
  Variant vPage;                      // �������� Excel (��������)
  AnsiString Value;                   // ��������� ������
  TDateTime DT1, DT2, DT3;            // ���������� ��� �������� ����-�������

  // ����������� ������� ���� � �������
  getdate(&d);
  gettime(&t);
  // ������������ ����� �����
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
  // ����������� ���� � ���������
  Patch = ExtractFilePath(ParamStr(0));
  // ������� ������� Microsoft Excel
  try
    {
      vApp=CreateOleObject("Excel.Application");
    }
  catch(...)
    {
      MessageBox(0, "������ ��� ������� ������� Excel", "������", MB_OK);
      return;
    }
  // �������� ����� Excel � ������������ ������
  vBooks = vApp.OlePropertyGet("Workbooks");
  vApp.OlePropertySet("SheetsInNewWorkbook", 1);
  vBooks.OleProcedure("Add");
  vBook  = vBooks.OlePropertyGet("Item",1);
  vBook.OleProcedure("SaveAs", (Patch+"STAT\\"+FileName).c_str());
  vSheets= vBook.OlePropertyGet("Worksheets") ;
  vSheet = vSheets.OlePropertyGet("Item",1);
  // ���������� ���������
  vApp.OlePropertySet("DisplayAlerts", false);
  // ����� ������
  if (RadioButton1->Checked)
    {
      // ����� ���������� - ����������� � ���� ����
      Table1->DatabaseName = Patch + "Base\\";
      Table1->TableName = "BOOK.db";
      Table1->Open();
      Table1->Active = true;
      // ����� ����� ������ � ����
      Value = "���� � ����������: "+IntToStr(Table1->RecordCount);
      // ����� ����� ������� � ������ �������
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","�����");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","��������");
      vCell.OlePropertySet("ColumnWidth", 75);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","��� �������");
      vCell.OlePropertySet("ColumnWidth", 12);
      // ������� ������� �����
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:C3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // ����� �������
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
      // ������� ������� �������
      vCell = vSheet.OlePropertyGet("Range", ("A4:A"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("B4:B"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("C4:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      // ��������� ������ �������
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
      // �������� �������
      Table1->Close();
      Table1->Active = false;
    }
  if (RadioButton2->Checked)
    {
      // ���������� �� ������ ���� - ����������� � ���� ���� � ������� �������� � �������
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
      // ����� ����� ������ � ����
      Value = "����� �� ������: "+IntToStr(Query1->RecordCount);
      // ����� ����� ������� � ������ �������
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","�����");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","��������");
      vCell.OlePropertySet("ColumnWidth", 75);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","��� �������");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","���� ������");
      vCell.OlePropertySet("ColumnWidth", 12);
      // ������� ������� �����
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:D3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // ����� �������
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
      // ������� ������� �������
      vCell = vSheet.OlePropertyGet("Range", ("A4:A"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("B4:B"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("C4:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      vCell = vSheet.OlePropertyGet("Range", ("D4:D"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      // ��������� ������ �������
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
      // �������� �������
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton3->Checked)
    {
      // ���������� �� ������ ���� - ����������� � ���� ���� � ������� �������� � �������
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
      // ����� ����� ������ � ����
      Value = "����� �� ������: "+IntToStr(Query1->RecordCount);
      // ����� ����� ������� � ������ �������
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","�����");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","��������");
      vCell.OlePropertySet("ColumnWidth", 75);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","��� �������");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","���� c����");
      vCell.OlePropertySet("ColumnWidth", 12);
      // ������� ������� �����
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:D3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // ����� �������
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
      // ������� ������� �������
      vCell = vSheet.OlePropertyGet("Range", ("A4:A"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("B4:B"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("C4:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      vCell = vSheet.OlePropertyGet("Range", ("D4:D"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      // ��������� ������ �������
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
      // �������� �������
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton4->Checked)
    {
      // ���������� �� ������ ���� - ����������� � ���� ����
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Book.BOOK_SECTION");
      Query1->SQL->Add("FROM \"BOOK.db\" Book");
      Query1->SQL->Add("GROUP BY Book.BOOK_SECTION");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;

      // ����� ����� ������ � ����
      Value = "�������� ����: "+IntToStr(Query1->RecordCount);
      // ����� ����� ������� � ������ �������
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","�����");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","��������");
      vCell.OlePropertySet("ColumnWidth", 75);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","��� �������");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","���� ������");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "E3");
      vCell.OlePropertySet("Value","���� c����");
      vCell.OlePropertySet("ColumnWidth", 12);
      // ������� ������� �����
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:E3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // ����� �������
      rownum = 4;
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          // ��������� ��������� ���������� �� �������� � ���������� �������� ����
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
          // ��������� ��������� ���������� �� �������� � ���������� c������ ����
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
          // ��������� ��������� ���������� �� �������� �������� �� ������
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
          // ����� ������������� ���������� � �������
          Value = "          ������ \'"+Query1->FieldByName("BOOK_SECTION")->AsString+"\': ����� "+IntToStr(count1)+", ���� "+IntToStr(count2);
          vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          rownum++;
          // ������������ ������ ��� ������ � �����
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
      // ������� ������� �������
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
      // ��������� ������ �������
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
      // �������� �������
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
      Query2->Close();
      Query2->Active = false;
      Query2->SQL->Clear();
    }
  if (RadioButton5->Checked)
    {
      // ����� ���������� - ����������� � ���� ����
      Table1->DatabaseName = Patch + "Base\\";
      Table1->TableName = "READER.db";
      Table1->Open();
      Table1->Active = true;
      // ����� ����� ������ � ����
      Value = "��������� � ����������: "+IntToStr(Table1->RecordCount);
      // ����� ����� ������� � ������ �������
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","������� ��� ��������");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","�����");
      vCell.OlePropertySet("ColumnWidth", 50);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","�������");
      vCell.OlePropertySet("ColumnWidth", 12);
      // ������� ������� �����
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:C3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // ����� �������
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
      // ������� ������� �������
      vCell = vSheet.OlePropertyGet("Range", ("A4:A"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("B4:B"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("C4:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      // ��������� ������ �������
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
      // �������� �������
      Table1->Close();
      Table1->Active = false;
    }
  if (RadioButton6->Checked)
    {
      // ���������� �� ������ ���� - ����������� � ���� ���� � ������� �������� � �������
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
      // ����� ����� ������ � ����
      Value = "����� �� ������: "+IntToStr(Query1->RecordCount);
      // ����� ����� ������� � ������ �������
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","��������");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","�����");
      vCell.OlePropertySet("ColumnWidth", 50);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","�������");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","���������� � �����");
      vCell.OlePropertySet("ColumnWidth", 75);
      vCell = vSheet.OlePropertyGet("Range", "E3");
      vCell.OlePropertySet("Value","���� ������");
      vCell.OlePropertySet("ColumnWidth", 12);
      // ������� ������� �����
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:E3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // ����� �������
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
      // ������� ������� �������
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
      // ��������� ������ �������
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
      // �������� �������
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton7->Checked)
    {
      // ���������� �� c���� ���� - ����������� � ���� ���� � ������� �������� � �������
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
      // ����� ����� ������ � ����
      Value = "����� �� ������: "+IntToStr(Query1->RecordCount);
      // ����� ����� ������� � ������ �������
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","��������");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","�����");
      vCell.OlePropertySet("ColumnWidth", 50);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","�������");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","���������� � �����");
      vCell.OlePropertySet("ColumnWidth", 75);
      vCell = vSheet.OlePropertyGet("Range", "E3");
      vCell.OlePropertySet("Value","���� c����");
      vCell.OlePropertySet("ColumnWidth", 12);
      // ������� ������� �����
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:E3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // ����� �������
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
      // ������� ������� �������
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
      // ��������� ������ �������
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
      // �������� �������
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
    }
  if (RadioButton8->Checked)
    {
      // ����� ���������� - ����������� � ���� ����
      Table1->DatabaseName = Patch + "Base\\";
      Table1->TableName = "USERS.db";
      Table1->Open();
      Table1->Active = true;
      // ����� ����� ������ � ����
      Value = "����������� � ����������: "+IntToStr(Table1->RecordCount);
      // ����� ����� ������� � ������ �������
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","������� ���");
      vCell.OlePropertySet("ColumnWidth", 13);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","������ ���");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","�����");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","�������");
      vCell.OlePropertySet("ColumnWidth", 12);
      // ������� ������� �����
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:D3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // ����� �������
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
      // ������� ������� �������
      vCell = vSheet.OlePropertyGet("Range", ("A4:A"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("B4:B"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4131);
      vCell = vSheet.OlePropertyGet("Range", ("C4:C"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      vCell = vSheet.OlePropertyGet("Range", ("D4:D"+IntToStr(rownum-1)).c_str());
      vCell.OlePropertySet("HorizontalAlignment",-4108);
      // ��������� ������ �������
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
      // �������� �������
      Table1->Close();
      Table1->Active = false;
    }
  if (RadioButton9->Checked)
    {
      // ���������� �� ������ ���� - ����������� � ���� ����
      Query1->DatabaseName = Patch + "Base\\";
      Query1->SQL->Clear();
      Query1->SQL->Add("SELECT Userr.USER_F_NAME,Userr.USER_S_NAME");
      Query1->SQL->Add("FROM \"USERS.db\" Userr");
      Query1->SQL->Add("ORDER BY Userr.USER_F_NAME,Userr.USER_S_NAME");
      Query1->ExecSQL();
      Query1->Open();
      Query1->Active = true;

      // ����� ����� ������ � ����
      Value = "�����������: "+IntToStr(Query1->RecordCount);
      // ����� ����� ������� � ������ �������
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","�����");
      vCell.OlePropertySet("ColumnWidth", 30);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","��������");
      vCell.OlePropertySet("ColumnWidth", 75);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","��� �������");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","���� ������");
      vCell.OlePropertySet("ColumnWidth", 12);
      vCell = vSheet.OlePropertyGet("Range", "E3");
      vCell.OlePropertySet("Value","���� �����");
      vCell.OlePropertySet("ColumnWidth", 12);
      // ������� ������� �����
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:E3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // ����� �������
      rownum = 4;
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          // ��������� ��������� ���������� �� �����������
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
          // ��������� ��������� ���������� �� �������� � ���������� c������ ����
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
          // ��������� ��������� ���������� �� �������� �������� �� ������
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
          // ����� ������������� ���������� � ����������
          Value = "          ��������� \'"+Query1->FieldByName("USER_F_NAME")->AsString+"\' ("+Query1->FieldByName("USER_S_NAME")->AsString+"): ����� "+IntToStr(count1)+", ���� "+IntToStr(count2);
          vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          rownum++;
          // ������������ ������ ��� ������ � �����
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
      // ������� ������� �������
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
      // ��������� ������ �������
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
      // �������� �������
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
      Query2->Close();
      Query2->Active = false;
      Query2->SQL->Clear();
    }
  if (RadioButton10->Checked)
    {
      // ���������� �� ������ ���� - ����������� � ���� ����
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
      // ����� ����� ������ � ����
      Value = "�����������: "+IntToStr(Query1->RecordCount);
      // ����� ����� ������� � ������ �������
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertySet("Value",Value.c_str());
      vCell = vSheet.OlePropertyGet("Range", "A3");
      vCell.OlePropertySet("Value","���� �����");
      vCell.OlePropertySet("ColumnWidth", 13);
      vCell = vSheet.OlePropertyGet("Range", "B3");
      vCell.OlePropertySet("Value","����� �����");
      vCell.OlePropertySet("ColumnWidth", 13);
      vCell = vSheet.OlePropertyGet("Range", "C3");
      vCell.OlePropertySet("Value","���� ������");
      vCell.OlePropertySet("ColumnWidth", 13);
      vCell = vSheet.OlePropertyGet("Range", "D3");
      vCell.OlePropertySet("Value","����� ������");
      vCell.OlePropertySet("ColumnWidth", 13);
      vCell = vSheet.OlePropertyGet("Range", "E3");
      vCell.OlePropertySet("Value","������������");
      vCell.OlePropertySet("ColumnWidth", 13);
      // ������� ������� �����
      vCell = vSheet.OlePropertyGet("Range", "A1");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertyGet("Font").OlePropertySet("Underline", 2);
      vCell = vSheet.OlePropertyGet("Range", "A3:E3");
      vCell.OlePropertyGet("Font").OlePropertySet("Bold",true);
      vCell.OlePropertySet("HorizontalAlignment",xlCenter);
      // ����� �������
      rownum = 4;
      Query1->First();
      for (int i=0; i<Query1->RecordCount; i++)
        {
          // ��������� ��������� ���������� �� ������������ ������
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
          // ����� ������������� ���������� � �������
          //fprintf (out,"��������� \'%s\' (%s): %d ������ � �������\n", Query1->FieldByName("USER_F_NAME")->AsString,Query1->FieldByName("USER_S_NAME")->AsString, Query2->RecordCount);
          Value = "          ��������� \'"+Query1->FieldByName("USER_F_NAME")->AsString+"\' ("+Query1->FieldByName("USER_S_NAME")->AsString+"): ������ � ������� "+IntToStr(Query2->RecordCount);
          vCell = vSheet.OlePropertyGet("Range", ("A"+IntToStr(rownum)).c_str());
          vCell.OlePropertySet("Value",Value.c_str());
          rownum++;
          // ������������ ������ ��� ������ � �����
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
      // �������� �������
      Query1->Close();
      Query1->Active = false;
      Query1->SQL->Clear();
      Query2->Close();
      Query2->Active = false;
      Query2->SQL->Clear();
    }
  // ��������� ���������
  vBook.OleProcedure("Save");
  // ��������� ���������
  vApp.OlePropertySet("DisplayAlerts", true);
  // ������ ���� �������
  vApp.OlePropertySet("Visible",true);
}
//---------------------------------------------------------------------------
