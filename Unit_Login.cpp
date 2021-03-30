//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit_Logo.h"
#include "Unit_Login.h"
#include "Unit_Bibliotheka.h"
#include "IniFiles.hpp"
#include "Unit_Book_In.h"
#include "Unit_Book_Out.h"
#include "Unit_Book_Add.h"
#include "Unit_Reader_Add.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_Login *Form_Login;
//---------------------------------------------------------------------------
__fastcall TForm_Login::TForm_Login(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_Login::FormShow(TObject *Sender)
{
  AnsiString Patch;                   // переменная для пути к программе
  AnsiString OldUserName;             // переменная для имени работника
  AnsiString OldDate;                 // переменная для даты
  AnsiString OldTime;                 // переменная для времени
  TIniFile *Ini;                      // переменная для работы с INI файлом
  int user_number;                    // номер работника в списке

  // загрузка иконки
  Form_Login->Icon->LoadFromFile("Books-OGY.ico");
  // вывод формы по центру экрана
  Form_Login->Top = (Screen->DesktopHeight - Form_Login->Height) / 2;
  Form_Login->Left = (Screen->DesktopWidth - Form_Login->Width) / 2;
  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // подключение базы данных работников
  DataSource1->DataSet = Table1;
  Table1->DatabaseName = Patch + "Base\\";
  Table1->TableName = "USERS.db";
  Table1->Open();
  Table1->Active = true;
  // подключение базы данных статистики
  DataSource2->DataSet = Table2;
  Table2->DatabaseName = Patch + "Base\\";
  Table2->TableName = "STAT.db";
  Table2->Open();
  Table2->Active = true;
  // определение имени предыдущего вошедшего работника
  Ini = new TIniFile(Patch+"Settings.ini");
  OldUserName = Ini->ReadString("OLD","User","");
  // определение списка работников
  ComboBox1->Items->Clear();
  user_number = -1;
  for (int i=0; i<Table1->RecordCount; i++)
     {
       ComboBox1->Items->Add(Table1->FieldByName("USER_F_NAME")->AsString);
       if (Table1->FieldByName("USER_S_NAME")->AsString == OldUserName)
         {
           user_number = i;
         }
       Table1->Next();
     }
  // вывод предыдущего вошедшего работника
  if (user_number == -1)
    {
      ComboBox1->ItemIndex = -1;
      ComboBox1->Text = "Выберите работника...";
    }
  else
    {
      OldDate = Ini->ReadString("OLD","Date","");
      OldTime = Ini->ReadString("OLD","Time","");
      Label5->Caption = OldUserName + ", " + OldDate + " " + OldTime;
      ComboBox1->ItemIndex = user_number;
      Table1->RecNo = user_number+1;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Login::CheckBox1Click(TObject *Sender)
{
  // показание / скрытие пароля
  if (CheckBox1->Checked)
    {
      MaskEdit1->PasswordChar = '*';
    }
  else
    {
      MaskEdit1->PasswordChar = 0;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Login::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  // выход из программы
  exit(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm_Login::SpeedButton2Click(TObject *Sender)
{
  // выход из программы
  exit(0);
}
//---------------------------------------------------------------------------
void __fastcall TForm_Login::SpeedButton1Click(TObject *Sender)
{
  AnsiString Patch;                   // переменная для пути к программе
  TIniFile *Ini;                      // переменная для работы с INI файлом
  int Session_Id;                     // номер сессии работы с ПО

  // проверка пароля
  if (Table1->FieldByName("USER_PASSWORD")->AsString == MaskEdit1->Text)
    {
      // успешный вход
      // запись информации о входе
      Table2->Append();
      Table2->FieldByName("STAT_USER_S_NAME")->AsString = Table1->FieldByName("USER_S_NAME")->AsString;
      Table2->FieldByName("STAT_DATA_IN")->AsDateTime = Date();
      Table2->FieldByName("STAT_TIME_IN")->AsDateTime = Time();
      Table2->UpdateRecord();
      Table2->Post();
      // сохранение данных о входе в ПО
      Patch = ExtractFilePath(ParamStr(0));
      Ini = new TIniFile(Patch+"Settings.ini");
      Table2->Last();
      Ini->WriteString("OLD","User",Table1->FieldByName("USER_S_NAME")->AsString);
      Ini->WriteString("OLD","Date",DateToStr(Date()));
      Ini->WriteString("OLD","Time",TimeToStr(Time()));
      Ini->WriteString("CURRENT","User",Table1->FieldByName("USER_S_NAME")->AsString);
      Ini->WriteString("CURRENT","User_name",Table1->FieldByName("USER_F_NAME")->AsString);
      Ini->WriteString("CURRENT","Id_Num",Table2->FieldByName("STAT_ID")->AsInteger);
      // установка прав доступа гостя
      if (Table1->FieldByName("USER_PRIVILEGE")->AsInteger == 2)
        {
          Form_Book_In->SpeedButton1->Enabled = false;
          Form_Book_Out->SpeedButton1->Enabled = false;
          Form_Reader_Add->SpeedButton1->Enabled = false;
          Form_Book_Add->SpeedButton1->Enabled = false;
          
        }
      // установка прав доступа администратора
      if (Table1->FieldByName("USER_PRIVILEGE")->AsInteger != 0)
        {
          Form_Bibliotheka->SpeedButton5->Enabled = false;
        }
      // скрытие формы
      Form_Login->Hide();
      Form_Bibliotheka->Show();
      // закрытие таблиц БД
      Table1->Close();
      Table2->Close();
    }
  else
    {
      // неверный пароль
      ShowMessage("Неверный пароль !!!");
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Login::ComboBox1Change(TObject *Sender)
{
  // определение краткого имени работника
  Table1->First();
  for (int i=0; i<ComboBox1->ItemIndex; i++)
    {
      Table1->Next();
    }
  Label2->Caption = "Пароль сотрудника " + Table1->FieldByName("USER_S_NAME")->AsString;
}
//---------------------------------------------------------------------------
void __fastcall TForm_Login::FormResize(TObject *Sender)
{
  // фиксирование размеров формы
  Form_Login->Height = 315;
  Form_Login->Width = 409;
}
//---------------------------------------------------------------------------

