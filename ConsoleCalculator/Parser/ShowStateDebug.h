#pragma once

#include <cstddef>
#include <iostream>
#include <string>

namespace clc::prs
{
    enum DebugState : std::size_t // (used in action table)
    {
        Start,
        A1, A2, A3, B1, B2, B3, C1, C2, C3,
        D1, D2, E1, F1, G1, G2, G3, G4
    };

    std::string stateName;

    void ShowState(DebugState s)
    {
        switch(s)
        {
            case Start:
                stateName = "Start";
                break;

            case A1:
                stateName = "A1";
                break;

            case A2:
                stateName = "A2";
                break;

            case A3:
                stateName = "A3";
                break;

            case B1:
                stateName = "B1";
                break;

            case B2:
                stateName = "B2";
                break;

            case B3:
                stateName = "B3";
                break;

            case C1:
                stateName = "C1";
                break;

            case C2:
                stateName = "C2";
                break;

            case C3:
                stateName = "C3";
                break;

            case D1:
                stateName = "D1";
                break;

            case D2:
                stateName = "D2";
                break;

            case E1:
                stateName = "E1";
                break;

            case F1:
                stateName = "F1";
                break;

            case G1:
                stateName = "G1";
                break;

            case G2:
                stateName = "G2";
                break;

            case G3:
                stateName = "G3";
                break;

            case G4:
                stateName = "G4";
                break;

            default:
                stateName = "Unknown state";
        }

        std::cout << stateName << std::endl;
    }
}