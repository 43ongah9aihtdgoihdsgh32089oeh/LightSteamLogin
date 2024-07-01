#pragma once
#include <iostream>
#include <string>
#include <functional>

class CHelpers;

class CInputHandler
{
private:
	CHelpers* Helper = nullptr;

public:
	std::string GetInput( std::wstring Prompt );
	void Handle( std::string In, std::vector<std::function<void()>> Functions, const int MaxArgs );
	CInputHandler( ) = default;

	void SetHelper( CHelpers* Help )
	{
		Helper = Help;
	}

	CHelpers* GetHelper( )
	{
		return Helper;
	}
};