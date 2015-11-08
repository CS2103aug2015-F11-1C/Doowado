#pragma once
#include <string>

class CmdBuilderException
{
private:
	std::string _message;
public:
	CmdBuilderException(std::string message);
	inline std::string getMessage();
	~CmdBuilderException();
};

