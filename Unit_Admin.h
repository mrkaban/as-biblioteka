//---------------------------------------------------------------------------

#ifndef Unit_AdminH
#define Unit_AdminH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm_Admin : public TForm
{
__published:	// IDE-managed Components
        TListBox *ListBox1;
        TLabel *Label1;
        TTable *Table1;
        TLabel *Label2;
        TEdit *Edit1;
        TLabel *Label3;
        TEdit *Edit2;
        TEdit *Edit3;
        TLabel *Label4;
        TEdit *Edit4;
        TLabel *Label5;
        TDateTimePicker *DateTimePicker1;
        TLabel *Label6;
        TGroupBox *GroupBox1;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton_New;
        TEdit *Edit5;
        TSpeedButton *SpeedButton_Add;
        TLabel *Label7;
        TSpeedButton *SpeedButton_Cancel;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall SpeedButton_NewClick(TObject *Sender);
        void __fastcall SpeedButton_CancelClick(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton_AddClick(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm_Admin(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Admin *Form_Admin;
//---------------------------------------------------------------------------
#endif
