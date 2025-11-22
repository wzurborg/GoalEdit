//---------------------------------------------------------------------------

#ifndef GoalViewH
#define GoalViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TGoalForm : public TForm
{
__published:	// IDE-managed Components
        TButton *PrintButton;
        TButton *CloseButton;
        TRichEdit *Goals;
        void __fastcall CloseButtonClick(TObject *Sender);
        void __fastcall PrintButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TGoalForm(TComponent* Owner);
        void InitText( AnsiString heading );
};
//---------------------------------------------------------------------------
extern PACKAGE TGoalForm *GoalForm;
//---------------------------------------------------------------------------
#endif

