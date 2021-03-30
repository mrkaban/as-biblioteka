//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit_Logo.h"
#include "Unit_Login.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_Logo *Form_Logo;
//---------------------------------------------------------------------------
__fastcall TForm_Logo::TForm_Logo(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_Logo::FormShow(TObject *Sender)
{
  // �������� ������ � ��������
  Form_Logo->Icon->LoadFromFile("Books-OGY.ico");
  Image1->Picture->LoadFromFile("image_gallery.bmp");
  // ����� ����� �� ������ ������
  Form_Logo->Top = (Screen->DesktopHeight - Form_Logo->Height) / 2;
  Form_Logo->Left = (Screen->DesktopWidth - Form_Logo->Width) / 2;
  // ������ �������
  Timer1->Interval = 3000;
  Timer1->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm_Logo::Timer1Timer(TObject *Sender)
{
  // �������� ����� ����� 3 ���.
  Timer1->Enabled = false;
  Form_Logo->Hide();
  Form_Login->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Logo::FormResize(TObject *Sender)
{
  // ������������ �������� �����
  Form_Logo->Height = 219;
  Form_Logo->Width = 505;
}
//---------------------------------------------------------------------------

