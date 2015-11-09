#include "StorageException.h"

StorageException::StorageException(std::string message){
	_message = message;
}

std::string StorageException::getMessage(){
	return _message;
}

StorageException::~StorageException(){
	
}
