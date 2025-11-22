#include "SDIMain.h"
#include "scenario.h"

Scenario::Scenario( const AnsiString& filename )
 : _filename(filename), _buffer(0)
{
    init();
}

__fastcall Scenario::~Scenario()
{
    delete _buffer;
    _size = 0;
}

void Scenario::init()
{
    // open file
    int fh = FileOpen( _filename, fmOpenRead );
    if( fh < 0 )
    {
        AnsiString msg = "Can't open scenario file: "
            + _filename;
        ShowMessage( msg );
        return;
    }

    // read file
    delete [] _buffer;
    _size = FileSeek( fh, 0, 2 );
    FileSeek( fh, 0, 0 );
    _buffer = new char[_size];
    int n = FileRead( fh, _buffer, _size );
    if( n != _size )
    {
        AnsiString msg = "Error reading scenario file: "
            + _filename;
        Application->MessageBoxA( msg.c_str(), "Error", MB_OK );
        return;
    }

    // close file
    FileClose( fh );

    analyse();
}

void Scenario::analyse()
{
    int i = 0;
    while( i<_size && !CompareMem( _buffer+i, "AUFTRAG4", 8 ) )
        i++;
    if( i == _size )
        return;
    _auftrag = (Auftrag*)(_buffer + i);

    // Check for zero length Auftrag
    if( _auftrag->length == 0 )
    {
        // Insert AUFTRAG
        char* old_buffer = _buffer;
        _size += 0x8c4;
        _buffer = new char[_size];
        _auftrag = (Auftrag*)(_buffer + i );
        char* auftragbody = ((char*)_auftrag) + 0x14;
        int length1 = auftragbody - _buffer;
        int length2 = 0x08c4;
        int length3 = _size - length1;
        memcpy( _buffer, old_buffer, length1 + 0x14 );
        memset( auftragbody, 0, length2 );
        memcpy( auftragbody+length2, old_buffer+length1, length3 );
        _auftrag->length = length2;
        delete [] old_buffer;
    }

    while( i<_size && !CompareMem( _buffer+i, "TIMERS", 6 ) )
        i++;
    if( i == _size )
        return;
    _timers = _buffer + i;
}

void Scenario::save()
{
    // open or create file
    int fh;
    if( FileExists( _filename ) )
       fh = FileOpen( _filename, fmOpenReadWrite );
    else
       fh = FileCreate( _filename );
    if( fh < 0 )
    {
        AnsiString msg = "Can't open or create file:\n"
            + _filename;
        ShowMessage( msg );
        return;
    }

    // write file
    FileSeek( fh, 0, 0 );
    int n = FileWrite( fh, _buffer, _size );
    if( n != _size )
    {
        AnsiString msg = "Error writing scenario file: "
            + _filename;
        Application->MessageBoxA( msg.c_str(), "Error", MB_OK );
        return;
    }

    // close file
    FileClose( fh );
}

void Scenario::saveAs( AnsiString newName )
{
   _filename = newName;
   save();
}

AnsiString Scenario::getAssignment()
{
    return AnsiString(_auftrag->text);
}

void Scenario::setAssignment( AnsiString txt )
{
   StrLCopy( _auftrag->text, txt.c_str(), 0x7ff );
}

Scenario::Einwohner* Scenario::getEinwohner( int index )
{
    return &_auftrag->einwohner[index];
}

void Scenario::setEinwohner( int index, const Einwohner& einw )
{
    _auftrag->einwohner[index].total = einw.total;
    _auftrag->einwohner[index].davon = einw.davon;
    _auftrag->einwohner[index].davontyp = einw.davontyp;
}

Scenario::Goods* Scenario::getGoods( int index )
{
    return &_auftrag->wareMin[index];
}

void Scenario::setGoods( int index, const Goods& goods )
{
    _auftrag->wareMin[index].typ = goods.typ;
    _auftrag->wareMin[index].amount = goods.amount;
}

int Scenario::getShipMax()
{
    return (int)_timers[0xd4];
}

void Scenario::setShipMax( int max )
{
   _timers[0xd4] = (char)max;
}

bool Scenario::getNoKampf()
{
    return ( (_timers[0xbd] & 0x02) != 0 );
}

void Scenario::setNoKampf( bool setting )
{
   if( setting )
      _timers[0xbd] |= 0x02;
   else
      _timers[0xbd] &= ~0x02;
}

void Scenario::getDefeatPlayers( DefeatPlayers& players )
{
    if( (_auftrag->flags & 0x02) != 0 )  // beliebigen
    {
        if( _auftrag->defeatPlayers[0] == 1 )
            players.any = 1;
    }

    if( (_auftrag->flags & 0x04) != 0 )  // bestimmte
    {
        players.red     = _auftrag->defeatPlayers[1];
        players.blue    = _auftrag->defeatPlayers[2];
        players.yellow  = _auftrag->defeatPlayers[3];
        players.white   = _auftrag->defeatPlayers[4];
        players.pirates = _auftrag->defeatPlayers[6];
    }
}

void Scenario::setDefeatPlayers( const DefeatPlayers& players )
{
    _auftrag->defeatPlayers[0] = players.any;
    _auftrag->defeatPlayers[1] = players.red;
    _auftrag->defeatPlayers[2] = players.blue;
    _auftrag->defeatPlayers[3] = players.yellow;
    _auftrag->defeatPlayers[4] = players.white;
    _auftrag->defeatPlayers[6] = players.pirates;

    if( players.any )
    {
       _auftrag->flags |= 0x02;    // set bit 0x02
    }
    else
    {
       _auftrag->flags &= ~0x02;   // clear bit 0x02
    }

    if( players.red | players.blue | players.yellow |
        players.white | players.pirates )
    {
        _auftrag->flags |= 0x04;    // set bit 0x04
    }
    else
    {
       _auftrag->flags &= ~0x04;   // clear bit 0x04
    }
}

Scenario::SupportPlayer Scenario::getSupportPlayer()
{
    if( _auftrag->support & 0x10 )
    {
        return (SupportPlayer)_auftrag->supportColor;
    }
    else
    {
        return none;
    }
}

void Scenario::setSupportPlayer( SupportPlayer player )
{
    if( player == none )
    {
        _auftrag->support &= ~0x10;   // clear bit 0x10
        _auftrag->supportColor = 0;
    }
    else
    {
        _auftrag->support |= 0x10;
        _auftrag->supportColor = (char)player;
    }
}

Scenario::Einwohner* Scenario::getSupportEinw()
{
    return &_auftrag->einwSupport;
}

void Scenario::setSupportEinw( const Einwohner& einw )
{
    _auftrag->einwSupport.total = einw.total;
    _auftrag->einwSupport.davon = einw.davon;
    _auftrag->einwSupport.davontyp = einw.davontyp;
}

int Scenario::getBalance( int index )
{
    switch( index )
    {
    case 0: return _auftrag->totalBalance;
    case 1: return _auftrag->tradeBalance;
    default: break;
    }
    return 0;
}

void Scenario::setBalance( int index, int balance )
{
    switch( index )
    {
    case 0: _auftrag->totalBalance = balance; break;
    case 1: _auftrag->tradeBalance = balance; break;
    default: break;
    }
}

Scenario::MonopolyGood Scenario::getMonopoly( int index )
{
    return (MonopolyGood)_auftrag->monopoly[index];
}

void Scenario::setMonopoly( int index,
                        Scenario::MonopolyGood good )
{
    _auftrag->monopoly[index] = (short)good;
}

char Scenario::getBuildings()
{
    return _auftrag->buildings;
}

void Scenario::setBuildings( char buildings )
{
    _auftrag->buildings = buildings;
}

int Scenario::getKontore()
{
    return _auftrag->numKontor;
}

void Scenario::setKontore( int kontore )
{
    _auftrag->numKontor = kontore;
}

