//---------------------------------------------------------------------------

#ifndef Unit_LoginH
#define Unit_LoginH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
class TForm_Login : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TMaskEdit *MaskEdit1;
        TCheckBox *CheckBox1;
        TSpeedButton *SpeedButton1;
        TLabel *Label3;
        TDataSource *DataSource1;
        TTable *Table1;
        TSpeedButton *SpeedButton2;
        TComboBox *ComboBox1;
        TDataSource *DataSource2;
        TTable *Table2;
        TLabel *Label4;
        TLabel *Label5;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm_Login(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Login *Form_Login;
//---------------------------------------------------------------------------
#endif
