//----------------------------------------------------------------------------
#ifndef SDIMainH
#define SDIMainH
//----------------------------------------------------------------------------
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <StdActns.hpp>
#include <ToolWin.hpp>

#include "scenario.h"

//----------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:
    TOpenDialog *OpenDialog;
    TSaveDialog *SaveDialog;
    TToolBar *ToolBar1;
    TToolButton *ToolButton1;
    TActionList *ActionList1;
    TAction *FileOpen1;
        TAction *FileSave1;
    TAction *FileExit1;
    TEditCut *EditCut1;
    TEditCopy *EditCopy1;
    TEditPaste *EditPaste1;
    TAction *HelpAbout1;
    TStatusBar *StatusBar;
    TImageList *ImageList1;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *FileOpenItem;
    TMenuItem *N1;
    TMenuItem *FileExitItem;
    TMenuItem *Help1;
    TMenuItem *HelpAboutItem;
        TButton *Button2;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TEdit *Edit1;
        TLabel *Label7;
        TTabSheet *TabSheet2;
        TGroupBox *GroupBox1;
        TEdit *EditMaxShips;
        TGroupBox *GroupBox2;
        TLabel *Label1;
        TLabel *Label2;
        TComboBox *ComboBox1;
        TEdit *Edit2;
        TGroupBox *GroupBox3;
        TLabel *Label4;
        TLabel *Label5;
        TComboBox *ComboBox2;
        TEdit *Edit3;
        TRadioGroup *RadioGroup1;
        TTabSheet *TabSheet3;
        TGroupBox *GroupBox4;
        TEdit *Edit4;
        TLabel *Label8;
        TEdit *Edit5;
        TLabel *Label9;
        TComboBox *ComboBox3;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox4;
        TGroupBox *GroupBox5;
        TLabel *Label3;
        TLabel *Label6;
        TEdit *Edit6;
        TEdit *Edit7;
        TComboBox *ComboBox4;
        TCheckBox *CheckBox5;
        TGroupBox *GroupBox6;
        TLabel *Label10;
        TLabel *Label11;
        TEdit *Edit8;
        TEdit *Edit9;
        TComboBox *ComboBox5;
        TTabSheet *TabSheet4;
        TMemo *Memo1;
        TButton *Button1;
        TTabSheet *TabSheet5;
        TTabSheet *TabSheet7;
        TTabSheet *TabSheet8;
        TGroupBox *GroupBox7;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TEdit *Edit10;
        TEdit *Edit11;
        TGroupBox *GroupBox8;
        TCheckBox *CheckBox8;
        TCheckBox *CheckBox9;
        TComboBox *ComboBox6;
        TComboBox *ComboBox7;
        TGroupBox *GroupBox9;
        TCheckBox *CheckBox10;
        TCheckBox *CheckBox11;
        TCheckBox *CheckBox12;
        TCheckBox *CheckBox13;
        TCheckBox *CheckBox14;
        TCheckBox *CheckBox15;
        TGroupBox *GroupBox11;
        TLabel *Label12;
        TLabel *Label13;
        TRadioGroup *RadioGroup2;
        TEdit *Edit12;
        TEdit *Edit13;
        TComboBox *ComboBox8;
        TTabSheet *TabSheet6;
        TGroupBox *GroupBox12;
        TCheckBox *CheckBox16;
        TCheckBox *CheckBox17;
        TGroupBox *GroupBox10;
        TCheckBox *CheckBox18;
        TLabel *Label14;
        TEdit *Edit14;
        TLabel *Label15;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TAction *ListAction;
        TMenuItem *Edit15;
        TMenuItem *List1;
        TAction *FileReopen;
        TMenuItem *Save1;
        TMenuItem *Reopen1;
        TToolButton *ToolButton2;
        TAction *FileSaveAs1;
        TMenuItem *SaveAs1;
        TAction *FileSaveExit;
        TAction *FileDelete1;
        TMenuItem *Delete1;
    TGroupBox *GroupBox13;
    TImage *Image1;
    TComboBox *ComboBox9;
        void __fastcall FileNew1Execute(TObject *Sender);
        void __fastcall FileOpen1Execute(TObject *Sender);
        void __fastcall FileSave1Execute(TObject *Sender);
        void __fastcall FileExit1Execute(TObject *Sender);
        void __fastcall HelpAbout1Execute(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox3Click(TObject *Sender);
        void __fastcall CheckBox4Click(TObject *Sender);
        void __fastcall CheckBox5Click(TObject *Sender);
        void __fastcall RadioGroup1Click(TObject *Sender);
        void __fastcall EditMaxShipsChange(TObject *Sender);
        void __fastcall Memo1Change(TObject *Sender);
        void __fastcall City1Change(TObject *Sender);
        void __fastcall City2Change(TObject *Sender);
        void __fastcall City3Change(TObject *Sender);
        void __fastcall Goods1Change(TObject *Sender);
        void __fastcall Goods2Change(TObject *Sender);
        void __fastcall CheckBox10Click(TObject *Sender);
        void __fastcall CheckBox11Click(TObject *Sender);
        void __fastcall CheckBox12Click(TObject *Sender);
        void __fastcall CheckBox13Click(TObject *Sender);
        void __fastcall CheckBox14Click(TObject *Sender);
        void __fastcall CheckBox15Click(TObject *Sender);
        void __fastcall RadioGroup2Click(TObject *Sender);
        void __fastcall CheckBox6Click(TObject *Sender);
        void __fastcall CheckBox7Click(TObject *Sender);
        void __fastcall CheckBox8Click(TObject *Sender);
        void __fastcall CheckBox9Click(TObject *Sender);
        void __fastcall Edit10Change(TObject *Sender);
        void __fastcall ComboBox7Change(TObject *Sender);
        void __fastcall ComboBox6Change(TObject *Sender);
        void __fastcall Edit11Change(TObject *Sender);
        void __fastcall Edit12Change(TObject *Sender);
        void __fastcall Edit13Change(TObject *Sender);
        void __fastcall ComboBox8Change(TObject *Sender);
        void __fastcall Edit14Change(TObject *Sender);
        void __fastcall CheckBox16Click(TObject *Sender);
        void __fastcall CheckBox17Click(TObject *Sender);
        void __fastcall CheckBox18Click(TObject *Sender);
        void __fastcall ListActionExecute(TObject *Sender);
        void __fastcall FileReopenExecute(TObject *Sender);
        void __fastcall FileReopenUpdate(TObject *Sender);
        void __fastcall FileSave1Update(TObject *Sender);
        void __fastcall FileSaveAs1Execute(TObject *Sender);
        void __fastcall FileSaveAs1Update(TObject *Sender);
        void __fastcall FileSaveExitExecute(TObject *Sender);
        void __fastcall FileSaveExitUpdate(TObject *Sender);
        void __fastcall FileDelete1Update(TObject *Sender);
        void __fastcall FileDelete1Execute(TObject *Sender);
private:
        Scenario* scen;
        TStrings* Klassen;
        TStrings* Goods;
        TStrings* Monopoly;
        static Scenario::MonopolyGood monopolyMap[];
        void readScenario();
        void citiesEnableDisable( TCheckBox* cb,
                TEdit* einwohner, TEdit* davon,
                TComboBox* davontyp,
                TLabel* l1, TLabel* l2 );
        void goodsEnableDisable(TCheckBox* cb,
                TEdit* store, TComboBox* good,
                TLabel* l1, TLabel* l2, TLabel* l3);
        void setEinwohner( int index,
                TCheckBox* cb, TEdit* total,
                TEdit* davon, TComboBox* davontyp );
        void setGoods(int index,
                TCheckBox* cb, TEdit* amount,
                TComboBox* type);
        void goodsChanged( int index,
                TCheckBox* cb, TEdit* amount,
                TComboBox* typ );
        void citiesChanged( int index,
                TCheckBox* cb, TEdit* einwohner,
                TEdit* davon, TComboBox* davontyp );
        void setDefeatPlayers();
        void setSupportPlayer();
        void setBalance( int index,
                TCheckBox* cb, TEdit* value );
        void setMonopoly( int index,
                TCheckBox* cb, TComboBox* typ );
        void suppCityChanged( TEdit* einwohner,
                TEdit* davon, TComboBox* davontyp );
        void getDirectories();
        void saveDirectories();

public:
    virtual __fastcall TMainForm(TComponent *AOwner);
};
//----------------------------------------------------------------------------
extern TMainForm *MainForm;
//----------------------------------------------------------------------------
#endif
