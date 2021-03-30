//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Unit_Logo.cpp", Form_Logo);
USEFORM("Unit_Login.cpp", Form_Login);
USEFORM("Unit_Bibliotheka.cpp", Form_Bibliotheka);
USEFORM("Unit_Book_Add.cpp", Form_Book_Add);
USEFORM("Unit_Reader_Add.cpp", Form_Reader_Add);
USEFORM("Unit_Book_Out.cpp", Form_Book_Out);
USEFORM("Unit_Book_In.cpp", Form_Book_In);
USEFORM("Unit_Admin.cpp", Form_Admin);
USEFORM("Unit_Stat.cpp", Form_Stat);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Автоматизированная система \"БИБЛИОТЕКА\"";
                 Application->CreateForm(__classid(TForm_Logo), &Form_Logo);
                 Application->CreateForm(__classid(TForm_Login), &Form_Login);
                 Application->CreateForm(__classid(TForm_Bibliotheka), &Form_Bibliotheka);
                 Application->CreateForm(__classid(TForm_Book_Add), &Form_Book_Add);
                 Application->CreateForm(__classid(TForm_Reader_Add), &Form_Reader_Add);
                 Application->CreateForm(__classid(TForm_Book_Out), &Form_Book_Out);
                 Application->CreateForm(__classid(TForm_Book_In), &Form_Book_In);
                 Application->CreateForm(__classid(TForm_Admin), &Form_Admin);
                 Application->CreateForm(__classid(TForm_Stat), &Form_Stat);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
