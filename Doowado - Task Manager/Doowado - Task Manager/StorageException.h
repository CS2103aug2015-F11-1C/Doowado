#pragma once

#include <exception>
#include <string>

class StorageException {
private:
	std::string _message;
public:
	StorageException (std::string message);
	std::string getMessage();
	~StorageException();
};