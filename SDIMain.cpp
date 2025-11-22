//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SDIMain.h"
#include "About.h"
#include "GoalView.h"

#include "registry.hpp"

static AnsiString C_DirKey( "Software\\SirHenry\\ScenEdit" );
static AnsiString C_OpenDir( "OpenDir" );
static AnsiString C_SaveDir( "SaveDir" );

//---------------------------------------------------------------------
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------

Scenario::MonopolyGood TMainForm::monopolyMap[9] = {
       Scenario::kakao, Scenario::baumwolle,
       Scenario::gewuerze, Scenario::tabak, Scenario::wein,
       Scenario::zuckerrohr, Scenario::erz, Scenario::gold
    };


__fastcall TMainForm::TMainForm(TComponent *AOwner)
	: TForm(AOwner),scen(0)
{
    int i;
    char* sKlassen[] = { "Pioneers", "Settlers", "Citizens",
           "Merchants", "Aristocrats" };
    Klassen = new TStringList;
    for( i=0; i<5; i++ )
       Klassen->Insert( i, sKlassen[i] );

    ComboBox3->Items = Klassen;
    ComboBox4->Items = Klassen;
    ComboBox5->Items = Klassen;
    ComboBox8->Items = Klassen;

    char* sGoods[] = {
        "Iron Ore", "Gold", "Wool/Cotton", "Sugar Cane",
        "Tobacco", "Cattle", "Grain", "Flour",
        "Iron", "Swords", "Muskets", "Cannons",
        "Food", "Cigars", "Spices", "Cocoa",
        "Alcohol", "Cloth", "Clothes", "Jewelry",
        "Tools", "Wood", "Bricks" };
    Goods = new TStringList;
    for( i=0; i<23; i++ )
        Goods->Insert( i, sGoods[i] );
    ComboBox1->Items = Goods;
    ComboBox2->Items = Goods;

    char* sMonopoly[] = {
        "Cocoa", "Cotton", "Spices", "Tobacco",
        "Vines", "Sugar Cane", "Iron Ore", "Gold" };
    Monopoly = new TStringList;
    for( i=0; i<8; i++ )
        Monopoly->Insert( i, sMonopoly[i] );
    ComboBox6->Items = Monopoly;
    ComboBox7->Items = Monopoly;

    getDirectories();
}
//---------------------------------------------------------------------

void TMainForm::readScenario()
{
    Memo1->Text = scen->getAssignment();
    EditMaxShips->Text = AnsiString(scen->getShipMax());
    RadioGroup1->ItemIndex = scen->getNoKampf() ? 0 : 1;

    setEinwohner( 0, CheckBox3, Edit4, Edit5, ComboBox3 );
    setEinwohner( 1, CheckBox4, Edit6, Edit7, ComboBox4 );
    setEinwohner( 2, CheckBox5, Edit8, Edit9, ComboBox5 );

    CheckBox16->State = (scen->getBuildings() & 0x02) ? cbChecked : cbUnchecked;
    CheckBox17->State = (scen->getBuildings() & 0x04) ? cbChecked : cbUnchecked;

    setGoods( 0, CheckBox1, Edit2, ComboBox1 );
    setGoods( 1, CheckBox2, Edit3, ComboBox2 );

    setDefeatPlayers();
    setSupportPlayer();
    setBalance( 0, CheckBox6, Edit10 );
    setBalance( 1, CheckBox7, Edit11 );

    setMonopoly( 0, CheckBox8, ComboBox6 );
    setMonopoly( 1, CheckBox9, ComboBox7 );

    int numKontor = scen->getKontore();
    if( numKontor != 0 )
    {
       CheckBox18->State = cbChecked;
       Edit14->Text = AnsiString( numKontor );
    }
    else
    {
        CheckBox18->State = cbUnchecked;
    }
}

void __fastcall TMainForm::FileNew1Execute(TObject *Sender)
{
  // Do nothing        
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileOpen1Execute(TObject *Sender)
{
  OpenDialog->Options >> ofReadOnly;
  if( OpenDialog->Execute() )
  {
        delete scen;
        scen = new Scenario( OpenDialog->FileName );
        readScenario();
        PageControl1->Enabled = true;
        Edit1->Text = OpenDialog->FileName;
        ListAction->Enabled = true;

        saveDirectories();
  }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileSave1Execute(TObject *Sender)
{
    scen->save();
    saveDirectories();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FileExit1Execute(TObject *Sender)
{
  Close();        
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::HelpAbout1Execute(TObject *Sender)
{
  AboutBox->ShowModal();        
}
//---------------------------------------------------------------------------




void __fastcall TMainForm::CheckBox2Click(TObject *Sender)
{
   TCheckBox* cb = (TCheckBox*)Sender;
   goodsEnableDisable( cb, Edit3, ComboBox2,
        Label4, Label5, Label6 );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox1Click(TObject *Sender)
{
   TCheckBox* cb = (TCheckBox*)Sender;
   goodsEnableDisable( cb, Edit2, ComboBox1,
        Label1, Label2, Label3 );
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::CheckBox3Click(TObject *Sender)
{
   TCheckBox* cb = (TCheckBox*)Sender;
   citiesEnableDisable( cb, Edit4, Edit5,
        ComboBox3, Label8, Label9 );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox4Click(TObject *Sender)
{
   TCheckBox* cb = (TCheckBox*)Sender;
   citiesEnableDisable( cb, Edit6, Edit7,
        ComboBox4, Label3, Label6 );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox5Click(TObject *Sender)
{
   TCheckBox* cb = (TCheckBox*)Sender;
   citiesEnableDisable( cb, Edit8, Edit9,
        ComboBox5, Label10, Label11 );
}
//---------------------------------------------------------------------------

void TMainForm::goodsEnableDisable( TCheckBox* cb,
        TEdit* store, TComboBox* good,
        TLabel* l1, TLabel* l2, TLabel* l3 )
{
   if( cb->Checked )
   {
        good->Enabled = true;
        good->Color = clWindow;
        store->Enabled = true;
        store->Color = clWindow;
        l1->Enabled = true;
        l2->Enabled = true;
        l3->Enabled = true;
    }
   else
   {
        good->Enabled = false;
        good->Color = clBtnFace;
        good->ItemIndex = -1;
        store->Enabled = false;
        store->Color = clBtnFace;
        store->Clear();
        l1->Enabled = false;
        l2->Enabled = false;
        l3->Enabled = false;
   }
}

void TMainForm::citiesEnableDisable( TCheckBox* cb,
        TEdit* einwohner, TEdit* davon,
        TComboBox* davontyp,
        TLabel* l1, TLabel* l2 )
{
   if( cb->Checked )
   {
        davontyp->Enabled = true;
        davontyp->Color = clWindow;
        einwohner->Enabled = true;
        einwohner->Color = clWindow;
        davon->Enabled = true;
        davon->Color = clWindow;
        l1->Enabled = true;
        l2->Enabled = true;
   }
   else
   {
        davontyp->Enabled = false;
        davontyp->Color = clBtnFace;
        davontyp->ItemIndex = -1;
        einwohner->Enabled = false;
        einwohner->Color = clBtnFace;
        einwohner->Clear();
        davon->Enabled = false;
        davon->Color = clBtnFace;
        davon->Clear();
        l1->Enabled = false;
        l2->Enabled = false;
   }
}

void __fastcall TMainForm::RadioGroup1Click(TObject *Sender)
{
   TRadioGroup* rg = (TRadioGroup*)Sender;
   scen->setNoKampf( rg->ItemIndex == 0 ? true : false );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::EditMaxShipsChange(TObject *Sender)
{
   TEdit* ed = (TEdit*)Sender;
   if( ed->Text.Length() > 0 )
      scen->setShipMax( ed->Text.ToInt() );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Memo1Change(TObject *Sender)
{
   TMemo* memo = (TMemo*)Sender;
   scen->setAssignment( memo->Text );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::City1Change(TObject *Sender)
{
    citiesChanged( 0, CheckBox3, Edit4, Edit5, ComboBox3 );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::City2Change(TObject *Sender)
{
    citiesChanged( 1, CheckBox4, Edit6, Edit7, ComboBox4 );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::City3Change(TObject *Sender)
{
    citiesChanged( 2, CheckBox5, Edit8, Edit9, ComboBox5 );
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Goods1Change(TObject *Sender)
{
    goodsChanged( 0, CheckBox1, Edit2, ComboBox1 );
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Goods2Change(TObject *Sender)
{
    goodsChanged( 1, CheckBox2, Edit3, ComboBox2 );
}
//---------------------------------------------------------------------------

void TMainForm::setEinwohner( int index,
        TCheckBox* cb, TEdit* total,
        TEdit* davon, TComboBox* davontyp )
{
    Scenario::Einwohner* ew = scen->getEinwohner( index );
    if( ew->total > 0 )
    {
        cb->State = cbChecked;
        // disable OnChange events
        TNotifyEvent ev1 = total->OnChange;
        TNotifyEvent ev2 = davon->OnChange;
        total->OnChange = 0;
        davon->OnChange = 0;
        total->Text = AnsiString(ew->total);
        davon->Text = AnsiString(ew->davon);
        total->OnChange = ev1;
        davon->OnChange = ev2;
        davontyp->ItemIndex = ew->davontyp;
    }
    else
    {
        cb->State = cbUnchecked;
    }
 }

void TMainForm::setGoods( int index,
        TCheckBox* cb, TEdit* amount, TComboBox* type )
{
    Scenario::Goods* goods = scen->getGoods( index );
    if( goods->amount > 0 && goods->typ > 0 )
    {
        cb->State = cbChecked;
        // disable OnChange event
        TNotifyEvent ev = amount->OnChange;
        amount->OnChange = 0;
        amount->Text = AnsiString( goods->amount );
        // restore OnChange event
        amount->OnChange = ev;
        type->ItemIndex = goods->typ - 2;
    }
    else
    {
        cb->State = cbUnchecked;
    }
}

void TMainForm::goodsChanged( int index,
        TCheckBox* cb, TEdit* amount, TComboBox* typ )
{
    Scenario::Goods goods;
    if( cb->Enabled &&
        amount->Text.Length() > 0 &&
        typ->ItemIndex >= 0 )
    {
        goods.amount = amount->Text.ToInt();
        goods.typ = typ->ItemIndex + 2;
    }
    else
    {
        goods.amount = 0;
        goods.typ = 0;
    }
    scen->setGoods( index, goods );
}

void TMainForm::citiesChanged( int index,
                TCheckBox* cb, TEdit* einwohner,
                TEdit* davon, TComboBox* davontyp )
{
    Scenario::Einwohner einw;
    if( cb->Enabled &&
        einwohner->Text.Length() > 0 &&
        davon->Text.Length() > 0 &&
        davontyp->ItemIndex >= 0 )
    {
        einw.total = einwohner->Text.ToInt();
        einw.davon = davon->Text.ToInt();
        einw.davontyp = davontyp->ItemIndex;
    }
    else
    {
        einw.total = 0;
        einw.davon = 0;
        einw.davontyp = 0;
    }
    scen->setEinwohner( index, einw );
}

void TMainForm::setDefeatPlayers()
{
    Scenario::DefeatPlayers players;
    scen->getDefeatPlayers( players );
    CheckBox10->State = players.red     ? cbChecked : cbUnchecked;
    CheckBox11->State = players.blue    ? cbChecked : cbUnchecked;
    CheckBox12->State = players.yellow  ? cbChecked : cbUnchecked;
    CheckBox13->State = players.white   ? cbChecked : cbUnchecked;
    CheckBox14->State = players.any     ? cbChecked : cbUnchecked;
    CheckBox15->State = players.pirates ? cbChecked : cbUnchecked;
}

void TMainForm::setSupportPlayer()
{
    Scenario::SupportPlayer player = scen->getSupportPlayer();

    switch( player )
    {
    case Scenario::any:
        RadioGroup2->ItemIndex = 5;
        break;

    default:
        RadioGroup2->ItemIndex = ((int)player) + 1;
    }

    if( player != Scenario::none )
    {
        Scenario::Einwohner* ew = scen->getSupportEinw();

        // disable events
        TNotifyEvent ev1 = Edit12->OnChange;
        TNotifyEvent ev2 = Edit13->OnChange;
        Edit12->OnChange = 0;
        Edit13->OnChange = 0;

        Edit12->Text = AnsiString( ew->total );
        Edit13->Text = AnsiString( ew->davon );

        // restore events
        Edit12->OnChange = ev1;
        Edit13->OnChange = ev2;

        ComboBox8->ItemIndex = ew->davontyp;
    }
    else
    {
        Edit12->Clear();
        Edit13->Clear();
        ComboBox8->ItemIndex = -1;
    }
}

void TMainForm::setBalance( int index,
        TCheckBox* cb, TEdit* value )
{
    int bal = scen->getBalance( index );

    if( bal > 0 )
    {
        cb->State = cbChecked;
        value->Text = AnsiString( bal );
    }
    else
    {
        cb->State = cbUnchecked;
        value->Clear();
    }
}

void TMainForm::setMonopoly( int index,
        TCheckBox* cb, TComboBox* typ )
{
    Scenario::MonopolyGood good = scen->getMonopoly( index );

    cb->State = (good == Scenario::nomop) ? cbUnchecked : cbChecked;
    switch( good )
    {
    case Scenario::kakao:      typ->ItemIndex = 0; break;
    case Scenario::baumwolle:  typ->ItemIndex = 1; break;
    case Scenario::gewuerze:   typ->ItemIndex = 2; break;
    case Scenario::tabak:      typ->ItemIndex = 3; break;
    case Scenario::wein:       typ->ItemIndex = 4; break;
    case Scenario::zuckerrohr: typ->ItemIndex = 5; break;
    case Scenario::erz:        typ->ItemIndex = 6; break;
    case Scenario::gold:       typ->ItemIndex = 7; break;
    default:                   typ->ItemIndex = -1; break;
    }
}
void __fastcall TMainForm::CheckBox10Click(TObject *Sender)
{
   TCheckBox* cb = (TCheckBox*)Sender;
   Scenario::DefeatPlayers players;
   scen->getDefeatPlayers( players );
   players.red = (cb->State == cbChecked) ? 1 : 0;
   if( cb->State == cbChecked )
   {
      CheckBox14->State = cbUnchecked;
      players.any = 0;
   }
   scen->setDefeatPlayers( players );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox11Click(TObject *Sender)
{
   TCheckBox* cb = (TCheckBox*)Sender;
   Scenario::DefeatPlayers players;
   scen->getDefeatPlayers( players );
   players.blue = (cb->State == cbChecked) ? 1 : 0;
   if( cb->State == cbChecked )
   {
      CheckBox14->State = cbUnchecked;
      players.any = 0;
   }
   scen->setDefeatPlayers( players );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox12Click(TObject *Sender)
{
   TCheckBox* cb = (TCheckBox*)Sender;
   Scenario::DefeatPlayers players;
   scen->getDefeatPlayers( players );
   players.yellow = (cb->State == cbChecked) ? 1 : 0;
   if( cb->State == cbChecked )
   {
      CheckBox14->State = cbUnchecked;
      players.any = 0;
   }
   scen->setDefeatPlayers( players );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox13Click(TObject *Sender)
{
   TCheckBox* cb = (TCheckBox*)Sender;
   Scenario::DefeatPlayers players;
   scen->getDefeatPlayers( players );
   players.white = (cb->State == cbChecked) ? 1 : 0;
   if( cb->State == cbChecked )
   {
      CheckBox14->State = cbUnchecked;
      players.any = 0;
   }
   scen->setDefeatPlayers( players );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox14Click(TObject *Sender)
{
   TCheckBox* cb = (TCheckBox*)Sender;

   // reset other boxes
   Scenario::DefeatPlayers players;
   scen->getDefeatPlayers( players );
   players.any = (cb->State == cbChecked) ? 1 : 0;
   if( cb->State == cbChecked )
   {
      CheckBox10->State = cbUnchecked;
      CheckBox11->State = cbUnchecked;
      CheckBox12->State = cbUnchecked;
      CheckBox13->State = cbUnchecked;
      players.red = players.blue =
        players.yellow = players.white = 0;
   }
   scen->setDefeatPlayers( players );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox15Click(TObject *Sender)
{
   TCheckBox* cb = (TCheckBox*)Sender;
   Scenario::DefeatPlayers players;
   scen->getDefeatPlayers( players );
   players.pirates = (cb->State == cbChecked) ? 1 : 0;
   scen->setDefeatPlayers( players );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioGroup2Click(TObject *Sender)
{
    TRadioGroup* rg = (TRadioGroup*)Sender;
    Scenario::SupportPlayer player;

    switch( rg->ItemIndex )
    {
    case 5:
        player = Scenario::any;
        break;
    default:
        player = (Scenario::SupportPlayer)(rg->ItemIndex - 1);
        break;
    }

    if( rg->ItemIndex == 0 )
    {
        Edit12->Clear();
        Edit12->Enabled = false;
        Edit12->Color = clBtnFace;
        Edit13->Clear();
        Edit13->Enabled = false;
        Edit13->Color = clBtnFace;
        ComboBox8->ItemIndex = -1;
        ComboBox8->Enabled = false;
        ComboBox8->Color= clBtnFace;
        Label12->Enabled = false;
        Label13->Enabled = false;
    }
    else
    {
        Edit12->Enabled = true;
        Edit12->Color = clWindow;
        Edit13->Enabled = true;
        Edit13->Color = clWindow;
        ComboBox8->Enabled = true;
        ComboBox8->Color = clWindow;
        Label12->Enabled = true;
        Label13->Enabled = true;
    }
    scen->setSupportPlayer( player );
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::CheckBox6Click(TObject *Sender)
{
    TCheckBox* cb = (TCheckBox*)Sender;

    if( cb->State == cbChecked )
    {
       Edit10->Color = clWindow;
       Edit10->Enabled = true;
    }
    else
    {
       Edit10->Color = clBtnFace;
       Edit10->Clear();
       Edit10->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox7Click(TObject *Sender)
{
    TCheckBox* cb = (TCheckBox*)Sender;

    if( cb->State == cbChecked )
    {
       Edit11->Color = clWindow;
       Edit11->Enabled = true;
    }
    else
    {
       Edit11->Color = clBtnFace;
       Edit11->Clear();
       Edit11->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox8Click(TObject *Sender)
{
    TCheckBox* cb = (TCheckBox*)Sender;

    if( cb->State == cbChecked )
    {
       ComboBox6->Color = clWindow;
       ComboBox6->Enabled = true;
    }
    else
    {
       ComboBox6->Color = clBtnFace;
       ComboBox6->ItemIndex = -1;
       ComboBox6->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox9Click(TObject *Sender)
{
    TCheckBox* cb = (TCheckBox*)Sender;

    if( cb->State == cbChecked )
    {
       ComboBox7->Color = clWindow;
       ComboBox7->Enabled = true;
    }
    else
    {
       ComboBox7->Color = clBtnFace;
       ComboBox7->ItemIndex = -1;
       ComboBox7->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit10Change(TObject *Sender)
{
    if( CheckBox6->State == cbChecked &&
        Edit10->Text.Length() > 0 )
    {
        int bal = Edit10->Text.ToInt();
        scen->setBalance( 0, bal );
    }
    else
    {
        scen->setBalance( 0, 0 );
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ComboBox7Change(TObject *Sender)
{
    Scenario::MonopolyGood good;
    if( CheckBox9->Enabled &&
        ComboBox7->ItemIndex >= 0 )
    {
        good = monopolyMap[ ComboBox7->ItemIndex ];
    }
    else
    {
       good = Scenario::nomop;
    }
    scen->setMonopoly( 1, good );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ComboBox6Change(TObject *Sender)
{
    Scenario::MonopolyGood good;
    if( CheckBox8->Enabled &&
        ComboBox6->ItemIndex >= 0 )
    {
        good = monopolyMap[ ComboBox6->ItemIndex ];
    }
    else
    {
       good = Scenario::nomop;
    }
    scen->setMonopoly( 0, good );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit11Change(TObject *Sender)
{
    if( CheckBox7->State == cbChecked &&
        Edit11->Text.Length() > 0 )
    {
        int bal = Edit11->Text.ToInt();
        scen->setBalance( 1, bal );
    }
    else
    {
        scen->setBalance( 1, 0 );
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit12Change(TObject *Sender)
{
    suppCityChanged( Edit12, Edit13, ComboBox8 );
}
//---------------------------------------------------------------------------

void TMainForm::suppCityChanged( TEdit* einwohner,
                TEdit* davon, TComboBox* davontyp )
{
    Scenario::Einwohner einw;
    if( einwohner->Text.Length() > 0 &&
        davon->Text.Length() > 0 &&
        davontyp->ItemIndex >= 0 )
    {
        einw.total = einwohner->Text.ToInt();
        einw.davon = davon->Text.ToInt();
        einw.davontyp = davontyp->ItemIndex;
    }
    else
    {
        einw.total = 0;
        einw.davon = 0;
        einw.davontyp = 0;
    }
    scen->setSupportEinw( einw );
}

void __fastcall TMainForm::Edit13Change(TObject *Sender)
{
    suppCityChanged( Edit12, Edit13, ComboBox8 );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ComboBox8Change(TObject *Sender)
{
    suppCityChanged( Edit12, Edit13, ComboBox8 );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit14Change(TObject *Sender)
{
    TEdit* ed = (TEdit*)Sender;
    if( ed->Text.Length() > 0 )
    {
        int kontore = ed->Text.ToInt();
        scen->setKontore( kontore );
    }
}
//---------------------------------------------------------------------------





void __fastcall TMainForm::CheckBox16Click(TObject *Sender)
{
    TCheckBox* cb = (TCheckBox*)Sender;
    char buildings = scen->getBuildings();

    if( cb->State == cbChecked )
       buildings |= 0x02;
    else
       buildings &= ~0x02;

    scen->setBuildings( buildings );
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox17Click(TObject *Sender)
{
    TCheckBox* cb = (TCheckBox*)Sender;
    char buildings = scen->getBuildings();

    if( cb->State == cbChecked )
       buildings |= 0x04;
    else
       buildings &= ~0x04;

    scen->setBuildings( buildings );
}
//---------------------------------------------------------------------------

void TMainForm::getDirectories()
{
    TRegistry* registry = new TRegistry;
    if( registry->OpenKey( C_DirKey, true ))
    {
        OpenDialog->InitialDir = registry->ReadString( C_OpenDir );
        SaveDialog->InitialDir = registry->ReadString( C_SaveDir );
    }
    delete registry;
}

void TMainForm::saveDirectories()
{
    TRegistry* registry = new TRegistry;
    if( registry->OpenKey( C_DirKey, true ))
    {
        AnsiString openDir = ExtractFileDir(OpenDialog->FileName);
        AnsiString saveDir = ExtractFileDir(SaveDialog->FileName);
        registry->WriteString( C_OpenDir, openDir );
        registry->WriteString( C_SaveDir, saveDir );
    }
    delete registry;
}

void __fastcall TMainForm::CheckBox18Click(TObject *Sender)
{
    TCheckBox* cb = (TCheckBox*)Sender;
    if( cb->State == cbChecked )
    {
       Edit14->Enabled = true;
       Edit14->Color = clWindow;
       Label14->Enabled = true;
       Label15->Enabled = true;
    }
    else
    {
       Edit14->Clear();
       Edit14->Enabled = false;
       Edit14->Color = clBtnFace;
       Label14->Enabled = false;
       Label15->Enabled = false;
    }
}
//---------------------------------------------------------------------------







void __fastcall TMainForm::ListActionExecute(TObject *Sender)
{
    GoalForm->Visible = true;
    GoalForm->InitText( OpenDialog->FileName );
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FileReopenExecute(TObject *Sender)
{
    if( scen )
    {
        scen->init();
        readScenario();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileReopenUpdate(TObject *Sender)
{
    TAction* action = (TAction*)Sender;
    action->Enabled = (scen != 0);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileSave1Update(TObject *Sender)
{
    TAction* action = (TAction*)Sender;
    action->Enabled = (scen != 0 &&
                !OpenDialog->Options.Contains( ofReadOnly ));
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileSaveAs1Execute(TObject *Sender)
{
     if( SaveDialog->Execute() )
     {
        scen->saveAs( SaveDialog->FileName );
        Edit1->Text = SaveDialog->FileName;
        saveDirectories();
     }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileSaveAs1Update(TObject *Sender)
{
    TAction* action = (TAction*)Sender;
    action->Enabled = (scen != 0);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileSaveExitExecute(TObject *Sender)
{
    scen->save();
    Close();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FileSaveExitUpdate(TObject *Sender)
{
    TAction* action = (TAction*)Sender;
    action->Enabled = (scen != 0 &&
                !OpenDialog->Options.Contains( ofReadOnly ));
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileDelete1Update(TObject *Sender)
{
    TAction* action = (TAction*)Sender;
    action->Enabled = (scen != 0 &&
                !OpenDialog->Options.Contains( ofReadOnly ));
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FileDelete1Execute(TObject *Sender)
{
    AnsiString msg =
    "Are you really sure to delete this scenario?";
    TMsgDlgButtons buttons;
    buttons << mbYes << mbNo;
    int answer = MessageDlg(msg, mtConfirmation, buttons, -1);
    if( answer == mrYes )
    {
        if( !DeleteFile( Edit1->Text ) )
        {
            ShowMessage( "The file could not be deleted" );
        }
    }
}
//---------------------------------------------------------------------------

