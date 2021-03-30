//---------------------------------------------------------------------------

#ifndef Unit_BibliothekaH
#define Unit_BibliothekaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm_Bibliotheka : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar;
        TTable *Table_Stat;
        TDataSource *DataSource_Stat;
        TToolBar *ToolBar1;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TImage *Image1;
        TImage *Image2;
        TImage *Image3;
        TSpeedButton *SpeedButton3;
        TDBGrid *DBGrid_Hist;
        TQuery *Query_Hist;
        TDataSource *DataSource_Hist;
        TImage *Image4;
        TSpeedButton *SpeedButton4;
        TSpeedButton *SpeedButton_Exit;
        TImage *Image5;
        TCheckBox *CheckBox_Norm;
        TCheckBox *CheckBox_Debt;
        TCheckBox *CheckBox_Return;
        TImage *Image6;
        TImage *Image7;
        TSpeedButton *SpeedButton5;
        TSpeedButton *SpeedButton_About;
        TSpeedButton *SpeedButton6;
        TImage *Image8;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall DBGrid_HistMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall SpeedButton_ExitClick(TObject *Sender);
        void __fastcall DBGrid_HistDrawDataCell(TObject *Sender,
          const TRect &Rect, TField *Field, TGridDrawState State);
        void __fastcall CheckBox_NormClick(TObject *Sender);
        void __fastcall DBGrid_HistDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
        void __fastcall CheckBox_DebtClick(TObject *Sender);
        void __fastcall CheckBox_ReturnClick(TObject *Sender);
        void __fastcall SpeedButton_AboutClick(TObject *Sender);
        void __fastcall SpeedButton5Click(TObject *Sender);
        void __fastcall SpeedButton6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm_Bibliotheka(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Bibliotheka *Form_Bibliotheka;
//---------------------------------------------------------------------------
#endif
