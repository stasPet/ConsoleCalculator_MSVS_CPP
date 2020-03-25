#include "CharacterHandler.h"
#include <iostream>

void clc::lxr::CharacterHandler::Handle(wchar_t message)
{
    std::wcout << "Handle2 :" << message << std::endl;;
}