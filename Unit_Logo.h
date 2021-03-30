//---------------------------------------------------------------------------

#ifndef Unit_LogoH
#define Unit_LogoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm_Logo : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TImage *Image1;
        TLabel *Label4;
        TTimer *Timer1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm_Logo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Logo *Form_Logo;
//---------------------------------------------------------------------------
#endif
