#include "Helpers.h"

std::wstring CHelpers::GetPathToSteam( )
{
	winreg::RegKey SteamPathRegKey { HKEY_CURRENT_USER, L"SOFTWARE\\Valve\\Steam" };
	std::wstring SteamPath = SteamPathRegKey.GetStringValue( L"SteamExe" );
	return SteamPath;
}

void CHelpers::KillSteam( )
{
	const auto Handle = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );

	PROCESSENTRY32W Entry {};
	Entry.dwSize = sizeof( Entry );

	try
	{
		if ( !Process32FirstW( Handle, ( LPPROCESSENTRY32W ) &Entry ) )
			throw new Error( "failed process32firstw : %u", GetLastError( ) );

		while ( Process32NextW( Handle, ( LPPROCESSENTRY32W ) &Entry ) )
		{
			std::wstring Name = Entry.szExeFile;
			if ( Name == L"steam.exe" )
			{
				const auto HandleProc = OpenProcess( PROCESS_TERMINATE, false, Entry.th32ProcessID );
				if ( HandleProc != nullptr )
				{
					TerminateProcess( HandleProc, 9 );
					CloseHandle( HandleProc );
				}
				else
					throw new Error( "failed openprocess : %u", GetLastError( ) );
			}
			std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
		}
	}
	catch ( Error Err )
	{
		MessageBoxA( 0, Err.what( ), "error occured", MB_OK | MB_ICONERROR );
	}

	CloseHandle( Handle );
}

void CHelpers::StartSteam( const std::wstring Args )
{
	_STARTUPINFOW StartupInfo {};
	PROCESS_INFORMATION ProcInfo {};
	ZeroMemory( &StartupInfo, sizeof( StartupInfo ) );
	ZeroMemory( &ProcInfo, sizeof( ProcInfo ) );
	StartupInfo.cb = sizeof( StartupInfo );

	try
	{
		std::wstring ExecPath = GetPathToSteam( );
		if ( ExecPath.empty( ) )
			throw new Error( "failed to get steam path : %u", GetLastError( ) );

		ExecPath.push_back( ' ' );
		ExecPath.append( Args );

		if ( !CreateProcessW( nullptr, ExecPath.data( ), 0, 0, false, 0, 0, 0,
			( LPSTARTUPINFOW ) &StartupInfo, &ProcInfo ) )
		{
			throw new Error( "failed to start steam : %u", GetLastError( ) );
		}
	}
	catch ( Error Err )
	{
		MessageBoxA( 0, Err.what( ), "error occured", MB_OK | MB_ICONERROR );
	}
}

// todo: use CAccount
void CHelpers::FormatArgs( std::wstring& Args, std::vector<std::wstring> Filler )
{
	Args.append( L"-login" );
	Args.append( L" " );

	for ( size_t i = 0; i < Filler.size( ); i++ )
	{
		Args.append( L" " );
		Args.append( Filler[ i ].data( ) );
	}
}

void CHelpers::RefreshAccounts( )
{
	wchar_t PathBuffer[ MAX_PATH ] = { 0 };
	GetModuleFileNameW( NULL, PathBuffer, MAX_PATH );

	size_t Position = std::wstring( PathBuffer ).find_last_of( L"\\/" );
	std::wstring Path = std::wstring( PathBuffer ).substr( 0, Position );

	wchar_t FormattedPath[ MAX_PATH + 100 ] {};
	swprintf_s( FormattedPath, L"%ws\\%ws", Path.data( ), DEFAULT_ACCOUNT_FILE_NAME );

	std::wifstream InputFile( FormattedPath );
	if ( InputFile.is_open( ) )
	{
		std::wstring Line;
		while ( std::getline( InputFile, Line ) )
		{
			std::wstringstream LineStream( Line );

			std::wstring Username = {};
			std::wstring Password = {};
			std::getline( LineStream, Username, L':' );
			std::getline( LineStream, Password );

			Accounts.emplace_back( Username, Password );

			PrintColor( L"Found account -> ", LIGHT_GREEN );
			PrintColor( Username.data( ), WHITE );
			PrintColor( L"\n", WHITE );
		}
		InputFile.close( );
	}
}

void CHelpers::LoginToAccount( )
{
	if ( GetSelectedAccountIndex( ) == -1 )
		return;

	PrintColor( L"Killing steam process...\n", LIGHT_RED );
	KillSteam( );
	
	std::wstring Args;

	CAccount Acc = Accounts[ GetSelectedAccountIndex( ) ];
	FormatArgs( Args, { Acc.Username, Acc.Password } );
	PrintColor( L"Formatting arguments...\n", YELLOW );
	StartSteam( { Args } );
	PrintColor( L"Starting steam...\n", LIGHT_GREEN );

}

void CHelpers::PrintColor( std::wstring str, UINT8 clr )
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

	SetConsoleTextAttribute( hConsole, clr );
	printf( "%ws", str.data( ) );

	// reset
	SetConsoleTextAttribute( hConsole, WHITE );
}