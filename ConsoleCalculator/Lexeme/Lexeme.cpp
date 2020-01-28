#include "Lexeme.h"
#include "StateMachine/StateMachine.h"

#include <cwctype>

std::wistream& clc::lxr::operator>>(std::wistream& stream, Lexeme& lexeme)
{
    CharType bufferChar;
    while (stream.get(bufferChar) )
    {
        if (!std::iswspace(bufferChar) && 
            bufferChar != L'\n' &&
            bufferChar != L'\;')
        {
            stream.putback(bufferChar);
            break;
        }
    }

    StateMachine stateMachine;
    lexeme.Clear();

    while (stream.get(bufferChar) )
    {
        lexeme.value.push_back(bufferChar);
        lexeme.type = stateMachine.SetChar(bufferChar);

        if (lexeme.type != StateType::Empty)
        {

            stream.putback(bufferChar);
            lexeme.value.erase(lexeme.value.end() - 1);

            break;
        }
    }

    return stream;
}

std::wostream& clc::lxr::operator<<(std::wostream& stream, const Lexeme& lexeme)
{

    switch(lexeme.type)
    {
    case Type::Number:
        stream << L"Number";
        break;

    case Type::Name:
        stream << L"Name";
        break;

    case Type::Function:
        stream << L"Function";
        break;

    case Type::Operation:
        stream << L"Operation";
        break;

    case Type::Bad:
        stream << L"Bad";
        break;

    case Type::Empty:
        stream << L"Empty";
        break;

    default:
        stream << L"Unknown lexeme type";
    }

    stream << L' ' << lexeme.value;

    return stream;
}