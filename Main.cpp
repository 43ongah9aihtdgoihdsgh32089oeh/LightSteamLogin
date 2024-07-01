#include <iostream>
#include <Windows.h>
#include "Helpers\Helpers.h"
#include "Helpers\InputHandler.h"

#define REMOTE_FUNC(s) [ = ]( ) { s }

static void RenderOptions( CHelpers* Helper );
static void HandleAccountSelection( CInputHandler* Input );

int main( )
{
	CHelpers* Helper = new CHelpers( );
	CInputHandler* Input = new CInputHandler( );

	Input->SetHelper( Helper );

	static bool Startup = true;

	while ( true )
	{
		if ( !Startup )
			printf( "\n" );

		if ( Startup )
			Startup = false;

		RenderOptions( Helper );

		std::string UserInput;
		UserInput = Input->GetInput( L"Hello, select an option from the ones above" );

		Input->Handle( UserInput, {
			REMOTE_FUNC( Helper->PrintColor( L"\n\n\n", WHITE ); Helper->RefreshAccounts( ); ),
			REMOTE_FUNC( Helper->PrintColor( L"\n\n\n", WHITE ); HandleAccountSelection( Input ); ),
			REMOTE_FUNC( exit( 0 ); )
			}, 2 );

		std::this_thread::sleep_for( std::chrono::milliseconds( 5 ) );
	}

	delete Helper;

#ifdef _DEBUG
	// wait
	int c = getchar( );
#endif

	return 0;
}

static void HandleAccountSelection( CInputHandler* Input )
{
	auto Helper = Input->GetHelper( );
	auto& LoadedAccounts = Helper->Accounts;
	for ( size_t i = 0; i < LoadedAccounts.size( ); i++ )
	{
		wchar_t Buffer[ 512 ] {};
		swprintf_s( Buffer, L"%u -> %ws\n", static_cast< unsigned int >( i ), LoadedAccounts.at( i ).Username.data( ) );
		Helper->PrintColor( Buffer, LIGHT_GREEN );
	}

	std::string UserInput;
	UserInput = Input->GetInput( L"Please select an account from the ones above" );

	int Option = std::atoi( UserInput.data( ) );
	if ( Option >= LoadedAccounts.size( ) || Option < 0 )
	{
		Helper->PrintColor( L"Invalid option\n", LIGHT_RED );
		HandleAccountSelection( Input );
		return;
	}

	wchar_t Buffer[ 512 ] {};
	swprintf_s( Buffer, L"Selected %ws\n", LoadedAccounts.at( Option ).Username.data( ) );

	Helper->SetSelectedAccountIndex( Option );
	Helper->PrintColor( Buffer, LIGHT_GREEN );

	Helper->LoginToAccount( );
	Helper->SetSelectedAccountIndex( -1 );
}

static void RenderOptions( CHelpers* Helper )
{
	Helper->PrintColor( L"0 -> Refresh accounts\n", WHITE );
	Helper->PrintColor( L"1 -> Login\n", WHITE );
	Helper->PrintColor( L"2 -> Exit\n", WHITE );
	Helper->PrintColor( L"\n", WHITE );
}