#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <Arduino.h>

class FileHandlerClass
{
public:
	void init();
	void loadConnectionHandlerSettings();
};

extern FileHandlerClass FileHandler;

#endif
