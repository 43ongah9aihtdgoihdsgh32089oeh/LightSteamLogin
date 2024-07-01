#include "InputHandler.h"
#include "Helpers.h"

std::string CInputHandler::GetInput( std::wstring Prompt )
{
	auto Helper = GetHelper( );
	if ( !Helper )
		throw new Error( "failed to get helper func in getinput" );

	std::string out;
	Helper->PrintColor( Prompt.append( L": " ), WHITE );
	std::cin >> out;
	return out;
}

void CInputHandler::Handle( std::string In, std::vector<std::function<void()>> Functions, const int MaxArgs )
{
	auto Helper = GetHelper( );
	if ( !Helper )
		throw new Error( "failed to get helper func in input handle" );

	int Option = std::atoi( In.data( ) );
	if ( Option > MaxArgs )
	{
		Helper->PrintColor( L"Invalid option\n", LIGHT_RED );
		return;
	}

	auto& Function = Functions[ Option ];
	Function( );
}
