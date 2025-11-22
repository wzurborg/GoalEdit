#ifndef _scenario_h_
#define _scenario_h_

#include <system.hpp>

class Scenario : public TObject
{
public:
    struct Einwohner
    {
        int total;
        int davontyp;
        int davon;
    };

    struct Goods
    {
        short typ;
        short unknown : 5;
        short amount : 11;
    };

    struct DefeatPlayers
    {
        char red;
        char blue;
        char yellow;
        char white;
        char any;
        char pirates;
        DefeatPlayers() { red=blue=yellow=white=any=pirates=0; }
    };

    enum SupportPlayer
    {
        none = -1,
        red = 0,
        blue = 1,
        yellow = 2,
        white = 3,
        any = 7
    };

    enum MonopolyGood
    {
       nomop = 0x00,
       erz = 0x02,
       gold = 0x03,
       kakao = 0x33,
       baumwolle = 0x31,
       gewuerze = 0x2f,
       tabak = 0x2e,
       wein = 0x32,
       zuckerrohr = 0x30
    };

    Scenario( const AnsiString& filename );
    virtual __fastcall ~Scenario();
    void init();
    AnsiString getAssignment();
    void setAssignment( AnsiString txt );
    void save();
    void saveAs( AnsiString newName );
    void analyse();
    Einwohner* getEinwohner(int index);
    void setEinwohner( int index, const Einwohner& einw );
    Goods* getGoods( int index );
    void setGoods( int index, const Goods& goods );
    int getShipMax();
    void setShipMax( int max );
    bool getNoKampf();
    void setNoKampf( bool setting );
    void getDefeatPlayers( DefeatPlayers& players );
    void setDefeatPlayers( const DefeatPlayers& players );
    SupportPlayer getSupportPlayer();
    void setSupportPlayer( SupportPlayer player );
    Einwohner* getSupportEinw();
    void setSupportEinw( const Einwohner& einw );
    int getBalance( int index);
    void setBalance( int index, int balance );
    MonopolyGood Scenario::getMonopoly( int index );
    void setMonopoly( int index, MonopolyGood good );
    char getBuildings();
    void setBuildings( char buildings );
    int getKontore();
    void setKontore( int kontore );

private:
    AnsiString _filename;
    char* _buffer;
    int _size;

    struct Auftrag
    {
        char header[0x10];
        int length;
        int unknown;
        char support;   // Bit 0x10 = Spieler unterstützen
        char flags;  // Spieler besiegen:
                     // Bit 0x02 = beliebigen, Bit 0x04 = bestimmten
                     // Bit 0x40 = 1. Monopol, Bit 0x80 = 2. Monopol
        char buildings;
        char unknown2[0x19];
        short monopoly[2];
        char supportColor; // rot=0 blau=1 gelb=2 weiß=3 beliebig=7
        char unknown3a[6];
        char defeatPlayers[7]; // 0=beliebig, 1=rot, 2=blau, 3=gelb
                                // 4=weiß, 6=Piraten - Byte ist 0 oder 1
        char unknown3b[0x0d];
        int numKontor;  // Min. Anzahl Kontore
        int unknown3c[2];
        int totalBalance;
        int unknown4;
        int tradeBalance;
        char unknown5[0x10];
        char text[0x800];
        Goods wareMin[2];
        Einwohner einwohner[3];
        int unknown6[9];
        Einwohner einwSupport;
    };

    Auftrag* _auftrag;
    char* _timers;
};

#endif


