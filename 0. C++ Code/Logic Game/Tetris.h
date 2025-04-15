#pragma once

#include "Partida.h"
#include <vector>
#include <iostream>
#include <string>

#define SDL_MAIN_HANDLED
#include <windows.h>
#include "../Graphic Lib/libreria.h"

#include "Puntuacio.h"

class Tetris
{
public:
    Tetris(const std::string& nomFitxer);

    int juga(Screen& pantalla,
             ModeJoc mode,
             const std::string& fitxerInicial,
             const std::string& fitxerFigures,
             const std::string& fitxerMoviments);

    void pushPuntuacio(const string& nom, const int punts);
    void printPuntuacions();
    void writePuntuacions(const std::string& nomFitxer);

private:
    Partida m_partida;
    std::vector<Puntuacio> m_puntuacions;
    std::string m_fitxerPuntuacions;
};
