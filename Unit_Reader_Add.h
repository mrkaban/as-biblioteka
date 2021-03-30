//---------------------------------------------------------------------------

#ifndef Unit_Reader_AddH
#define Unit_Reader_AddH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TForm_Reader_Add : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label3;
        TEdit *Edit1;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *Edit2;
        TLabel *Label4;
        TEdit *Edit3;
        TLabel *Label5;
        TEdit *Edit4;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TTable *Table1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm_Reader_Add(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Reader_Add *Form_Reader_Add;
//---------------------------------------------------------------------------
#endif
