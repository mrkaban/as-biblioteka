//---------------------------------------------------------------------------

#ifndef Unit_Book_InH
#define Unit_Book_InH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm_Book_In : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label3;
        TLabel *Label5;
        TEdit *Edit2;
        TLabel *Label6;
        TEdit *Edit3;
        TLabel *Label1;
        TEdit *Edit1;
        TLabel *Label2;
        TDBGrid *DBGrid_Hist;
        TTable *Table_Hist;
        TDataSource *DataSource_Hist;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TTable *Table_Book;
        TQuery *Query_Info;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall DBGrid_HistDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
        void __fastcall DBGrid_HistMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall FormHide(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall DBGrid_HistDblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm_Book_In(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Book_In *Form_Book_In;
//---------------------------------------------------------------------------
#endif
