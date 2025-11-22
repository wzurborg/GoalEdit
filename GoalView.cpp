//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GoalView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGoalForm *GoalForm;
//---------------------------------------------------------------------------
__fastcall TGoalForm::TGoalForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGoalForm::CloseButtonClick(TObject *Sender)
{
    Goals->Clear();
    this->Visible = false;        
}
//---------------------------------------------------------------------------

void __fastcall TGoalForm::PrintButtonClick(TObject *Sender)
{
    Goals->Print( this->Caption );
}
//---------------------------------------------------------------------------


void TGoalForm::InitText( AnsiString heading )
{
    Goals->SelAttributes->Color = clBlue;
    Goals->SelAttributes->Size = 10;
    TFontStyles styles;
    styles << fsBold;
    Goals->SelAttributes->Style = styles;
    Goals->Paragraph->LeftIndent = 20;
    Goals->Lines->Add("");
    Goals->Lines->Add( heading );

    Goals->SelAttributes->Color = clBlack;
    Goals->Paragraph->Numbering = nsBullet;
    Goals->Lines->Add( "Text1" );
    Goals->Lines->Add( "Text2" );

}
