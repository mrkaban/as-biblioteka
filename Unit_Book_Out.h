//---------------------------------------------------------------------------

#ifndef Unit_Book_OutH
#define Unit_Book_OutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TForm_Book_Out : public TForm
{
__published:	// IDE-managed Components
        TTable *Table_Book_Out;
        TDBGrid *DBGrid_Book_Out;
        TDataSource *DataSource_Book_Out;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TLabel *Label1;
        TEdit *Edit1;
        TLabel *Label3;
        TLabel *Label2;
        TLabel *Label4;
        TDBGrid *DBGrid_Reader_Out;
        TTable *Table_Reader_Out;
        TDataSource *DataSource_Reader_Out;
        TLabel *Label5;
        TEdit *Edit2;
        TLabel *Label6;
        TEdit *Edit3;
        TTable *Table_Hist;
        TCSpinEdit *CSpinEdit1;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        void __fastcall FormHide(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall DBGrid_Book_OutMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall DBGrid_Reader_OutMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall DBGrid_Book_OutDrawDataCell(TObject *Sender,
          const TRect &Rect, TField *Field, TGridDrawState State);
        void __fastcall DBGrid_Reader_OutDrawDataCell(TObject *Sender,
          const TRect &Rect, TField *Field, TGridDrawState State);
        void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm_Book_Out(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Book_Out *Form_Book_Out;
//---------------------------------------------------------------------------
#endif
