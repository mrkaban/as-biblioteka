//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit_Admin.h"
#include "Unit_Bibliotheka.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_Admin *Form_Admin;
//---------------------------------------------------------------------------
__fastcall TForm_Admin::TForm_Admin(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_Admin::FormShow(TObject *Sender)
{
  AnsiString Patch;                   // переменная для пути к программе

  // загрузка иконки
  Form_Admin->Icon->LoadFromFile("Books-OGY.ico");
  // вывод окна в центре основной формы
  Form_Admin->Top = Form_Bibliotheka->Top + (Form_Bibliotheka->Height - Form_Admin->Height) / 2;
  Form_Admin->Left = Form_Bibliotheka->Left + (Form_Bibliotheka->Width - Form_Admin->Width) / 2;
  // определение пути к программе
  Patch = ExtractFilePath(ParamStr(0));
  // подключение базы данных книг
  Table1->DatabaseName = Patch + "Base\\";
  Table1->TableName = "USERS.db";
  Table1->Open();
  Table1->Active = true;
  // заполнение списка работников
  Table1->First();
  ListBox1->Items->Clear();
  for (int i=0; i<Table1->RecordCount; i++)
    {
      ListBox1->Items->Add(Table1->FieldByName("USER_S_NAME")->AsString);
      Table1->Next();
    }
  ListBox1->ItemIndex = 0;
  // заполнение полей данными первой записи
  Table1->First();
  Edit1->Text = Table1->FieldByName("USER_S_NAME")->AsString;
  Edit2->Text = Table1->FieldByName("USER_ADRESS")->AsString;
  Edit3->Text = Table1->FieldByName("USER_PASSPORT")->AsString;
  Edit4->Text = Table1->FieldByName("USER_PASSWORD")->AsString;
  DateTimePicker1->Date = Table1->FieldByName("USER_DATE_OF_BIRTH")->AsDateTime;
  if (Table1->FieldByName("USER_PRIVILEGE")->AsInteger == 0)
    {
      RadioButton1->Checked = true;
    }
  if (Table1->FieldByName("USER_PRIVILEGE")->AsInteger == 1)
    {
      RadioButton2->Checked = true;
    }
  if (Table1->FieldByName("USER_PRIVILEGE")->AsInteger == 2)
    {
      RadioButton3->Checked = true;
    }
  // блокирование изменений
  Edit1->Enabled = false;
  Edit2->Enabled = false;
  Edit3->Enabled = false;
  Edit4->Enabled = false;
  DateTimePicker1->Enabled = false;
  RadioButton1->Enabled = false;
  RadioButton2->Enabled = false;
  RadioButton3->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_Admin::ListBox1Click(TObject *Sender)
{
  // поиск требуемой записи
  Table1->Filtered = false;
  Table1->Filter = "USER_S_NAME = \'"+ListBox1->Items->operator [](ListBox1->ItemIndex)+"\'";
  Table1->Filtered = true;
  // заполнение полей данными
  Table1->First();
  Edit1->Text = Table1->FieldByName("USER_F_NAME")->AsString;
  Edit2->Text = Table1->FieldByName("USER_ADRESS")->AsString;
  Edit3->Text = Table1->FieldByName("USER_PASSPORT")->AsString;
  Edit4->Text = Table1->FieldByName("USER_PASSWORD")->AsString;
  DateTimePicker1->Date = Table1->FieldByName("USER_DATE_OF_BIRTH")->AsDateTime;
  if (Table1->FieldByName("USER_PRIVILEGE")->AsInteger == 0)
    {
      RadioButton1->Checked = true;
    }
  if (Table1->FieldByName("USER_PRIVILEGE")->AsInteger == 1)
    {
      RadioButton2->Checked = true;
    }
  if (Table1->FieldByName("USER_PRIVILEGE")->AsInteger == 2)
    {
      RadioButton3->Checked = true;
    }
  // блокирование изменений если запись стандартная
  if (ListBox1->ItemIndex < 2)
    {
      Edit1->Enabled = false;
      Edit2->Enabled = false;
      Edit3->Enabled = false;
      Edit4->Enabled = false;
      DateTimePicker1->Enabled = false;
      RadioButton1->Enabled = false;
      RadioButton2->Enabled = false;
      RadioButton3->Enabled = false;
    }
  // или разрешение измененний в противном случае
  else
    {
      Edit1->Enabled = true;
      Edit2->Enabled = true;
      Edit3->Enabled = true;
      Edit4->Enabled = true;
      DateTimePicker1->Enabled = true;
      RadioButton1->Enabled = true;
      RadioButton2->Enabled = true;
      RadioButton3->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm_Admin::SpeedButton_NewClick(TObject *Sender)
{
  // запуск операции добавления пользователей
  ListBox1->Enabled = false;
  SpeedButton_New->Visible = false;
  SpeedButton_Add->Visible = true;
  SpeedButton_Cancel->Visible = true;
  Label7->Visible = true;
  Edit5->Visible = true;
  Edit1->Text = "";
  Edit2->Text = "";
  Edit3->Text = "";
  Edit4->Text = "";
  Edit5->Text = "";
  Edit1->Enabled = true;
  Edit2->Enabled = true;
  Edit3->Enabled = true;
  Edit4->Enabled = true;
  DateTimePicker1->Enabled = true;
  RadioButton1->Enabled = true;
  RadioButton2->Enabled = true;
  RadioButton3->Enabled = true;
  RadioButton2->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm_Admin::SpeedButton_CancelClick(TObject *Sender)
{
  // отмена операции добавления пользователей
  ListBox1->Enabled = true;
  SpeedButton_New->Visible = true;
  SpeedButton_Add->Visible = false;
  SpeedButton_Cancel->Visible = false;
  Label7->Visible = false;
  Edit5->Visible = false;
  ListBox1Click(ListBox1);
}
//---------------------------------------------------------------------------
void __fastcall TForm_Admin::SpeedButton2Click(TObject *Sender)
{
  // закрытие таблицы
  Table1->Close();
  // завершение операции добавления книги
  Form_Bibliotheka->Enabled = true;
  Form_Admin->Hide();
  // передача фокуса основной таблице
  Form_Bibliotheka->DBGrid_Hist->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm_Admin::SpeedButton_AddClick(TObject *Sender)
{
  // снятие блокировки
  ListBox1->Enabled = true;
  Table1->Filtered = false;
  // добавление пользователя
  Table1->Append();
  Table1->FieldByName("USER_F_NAME")->AsString = Edit1->Text;
  Table1->FieldByName("USER_ADRESS")->AsString = Edit2->Text;
  Table1->FieldByName("USER_PASSPORT")->AsString = Edit3->Text;
  Table1->FieldByName("USER_PASSWORD")->AsString = Edit4->Text;
  Table1->FieldByName("USER_S_NAME")->AsString = Edit5->Text;
  Table1->FieldByName("USER_DATE_OF_BIRTH")->AsDateTime = DateTimePicker1->Date;
  if (RadioButton1->Checked)
    {
      Table1->FieldByName("USER_PRIVILEGE")->AsInteger = 0;;
    }
  if (RadioButton2->Checked)
    {
      Table1->FieldByName("USER_PRIVILEGE")->AsInteger = 1;
    }
  if (RadioButton3->Checked)
    {
      Table1->FieldByName("USER_PRIVILEGE")->AsInteger = 2;
    }
  Table1->UpdateRecord();
  Table1->Post();
  // обновление данных
  int i= ListBox1->ItemIndex;
  Form_Admin->Hide();
  Form_Admin->Show();
  ListBox1->ItemIndex = i;
  ListBox1Click(ListBox1);
  // завершение операции добавления пользователей
  SpeedButton_New->Visible = true;
  SpeedButton_Add->Visible = false;
  SpeedButton_Cancel->Visible = false;
  Label7->Visible = false;
  Edit5->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm_Admin::SpeedButton1Click(TObject *Sender)
{
  // сохранение пользователя
  Table1->Edit();
  Table1->FieldByName("USER_F_NAME")->AsString = Edit1->Text;
  Table1->FieldByName("USER_ADRESS")->AsString = Edit2->Text;
  Table1->FieldByName("USER_PASSPORT")->AsString = Edit3->Text;
  Table1->FieldByName("USER_PASSWORD")->AsString = Edit4->Text;
  Table1->FieldByName("USER_DATE_OF_BIRTH")->AsDateTime = DateTimePicker1->Date;
  if (RadioButton1->Checked)
    {
      Table1->FieldByName("USER_PRIVILEGE")->AsInteger = 0;;
    }
  if (RadioButton2->Checked)
    {
      Table1->FieldByName("USER_PRIVILEGE")->AsInteger = 1;
    }
  if (RadioButton3->Checked)
    {
      Table1->FieldByName("USER_PRIVILEGE")->AsInteger = 2;
    }
  Table1->UpdateRecord();
  Table1->Post();
}
//---------------------------------------------------------------------------

