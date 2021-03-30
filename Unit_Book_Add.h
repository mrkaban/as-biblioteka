//---------------------------------------------------------------------------

#ifndef Unit_Book_AddH
#define Unit_Book_AddH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_Book_Add : public TForm
{
__published:	// IDE-managed Components
        TTable *Table1;
        TLabel *Label3;
        TLabel *Label1;
        TEdit *Edit1;
        TEdit *Edit2;
        TLabel *Label2;
        TEdit *Edit3;
        TLabel *Label4;
        TDateTimePicker *DateTimePicker1;
        TLabel *Label5;
        TEdit *Edit4;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *Edit5;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TTable *Table2;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm_Book_Add(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Book_Add *Form_Book_Add;
//---------------------------------------------------------------------------
#endif
