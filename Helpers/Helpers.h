#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <TlHelp32.h>
#include <thread>

#include "../External/winreg.h"

#define DEFAULT_ACCOUNT_FILE_NAME L"accounts.kak"

// no official for widestr output
struct Error : std::exception
{
    char text[ 1024 ] {};

    Error( char const* fmt, ... )
    {
        va_list ap;
        va_start( ap, fmt );
        vsnprintf( text, sizeof text, fmt, ap );
        va_end( ap );
    }

    char const* what( ) const throw( )
    {
        return text;
    }

    Error( ) = default;
};

struct CAccount
{
    std::wstring Username {};
    std::wstring Password {};

    CAccount( ) = default;

    CAccount( const std::wstring& Username, const std::wstring& Password )
        : Username( Username ), Password( Password )
    {
    }
};

#define LIGHT_GREEN 10
#define LIGHT_RED 12
#define YELLOW 14
#define WHITE 15

class CHelpers
{
private:
    int SelectedAccountIndex = -1;
public:
	__forceinline std::wstring GetPathToSteam( );
    void KillSteam( );

	void StartSteam( const std::wstring Args );
    void FormatArgs( std::wstring& Args, std::vector<std::wstring> Filler );
    void RefreshAccounts( );
    void LoginToAccount( );
    void PrintColor( std::wstring str, UINT8 clr );

    std::vector< CAccount > Accounts {};

    CHelpers( )
    {
        if ( !Accounts.empty( ) )
            Accounts.clear( );

        PrintColor( L"Currently found accounts: \n", YELLOW );
        RefreshAccounts( );
    }

    void SetSelectedAccountIndex( int Index )
    {
        SelectedAccountIndex = Index;
    }

    int GetSelectedAccountIndex( ) const
    {
        return SelectedAccountIndex;
    }
};