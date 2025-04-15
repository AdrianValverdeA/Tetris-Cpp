#include "Tetris.h"
#include <fstream>
#include <algorithm>

#include <windows.h>
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"

#include "GraphicManager.h"

Tetris::Tetris(const std::string& nomFitxer)
{
    std::ifstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
    {
        std::string nom;
        int punts;
        while (fitxer >> nom >> punts)
        {
            Tetris::pushPuntuacio(nom, punts);
        }
        fitxer.close();
    }
    m_fitxerPuntuacions = nomFitxer;
}

int Tetris::juga(Screen& pantalla,
                 ModeJoc mode,
                 const std::string& fitxerInicial,
                 const std::string& fitxerFigures,
                 const std::string& fitxerMoviments)
{
    pantalla.show();

    Partida partida;

    if (mode == MODEJOC_NORMAL)
    {
        partida.inicialitza(fitxerInicial, fitxerFigures, fitxerMoviments, m_fitxerPuntuacions);

        Uint64 NOW = SDL_GetPerformanceCounter();
        Uint64 LAST = 0;
        double deltaTime = 0;

        bool exit = false;

        do
        {
            LAST = NOW;
            NOW = SDL_GetPerformanceCounter();
            deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

            pantalla.processEvents();
            partida.actualitzaNormal(deltaTime);

            pantalla.update();

            if (partida.finalitzat())
            {
                exit = true;
            }

        } while (!exit
                 && !Keyboard_GetKeyTrg(KEYBOARD_Q)
                 && !Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)
                 && !((SDL_GetModState() == KMOD_LALT
                       || SDL_GetModState() == KMOD_RALT)
                      && Keyboard_GetKeyTrg(KEYBOARD_F4)));
    }
    else if (mode == MODEJOC_TEST)
    {
        partida.inicialitza(fitxerInicial, fitxerFigures, fitxerMoviments, m_fitxerPuntuacions);

        Uint64 NOW = SDL_GetPerformanceCounter();
        Uint64 LAST = 0;
        double deltaTime = 0;

        bool exit = false;
        do
        {
            LAST = NOW;
            NOW = SDL_GetPerformanceCounter();
            deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

            pantalla.processEvents();

            exit = partida.actualitzaTest(deltaTime);

            pantalla.update();

        } while (!Keyboard_GetKeyTrg(KEYBOARD_Q)
                 && !Keyboard_GetKeyTrg(KEYBOARD_ESCAPE)
                 && !((SDL_GetModState() == KMOD_LALT
                       || SDL_GetModState() == KMOD_RALT)
                      && Keyboard_GetKeyTrg(KEYBOARD_F4))
                 && !exit);

    }

    return partida.getPuntuacio();
}

void Tetris::pushPuntuacio(const string& nom, const int punts)
{
    std::vector<Puntuacio>::iterator it = m_puntuacions.begin();
    bool trobat = false;
    while (it != m_puntuacions.end() && !trobat)
    {
        if (it->getHighScore() < punts)
        {
            trobat = true;
        }
        else
        {
            it++;
        }
    }
    Puntuacio p(nom, punts);
    m_puntuacions.insert(it, p);
}

void Tetris::printPuntuacions()
{
    std::vector<Puntuacio>::iterator it = m_puntuacions.begin();
    std::cout << "=============== LEADERBOARD ===============" << std::endl;
    int n = 1;
    while (it != m_puntuacions.end())
    {
        printf("%d. %-10s %10d pts.\n", n, it->getNom().c_str(), it->getHighScore());
        //std::cout << n << ". " << it->getNom() << "\t-> " << it->getHighScore() << " pts." << std::endl;
        n++;
        it++;
    }
}

void Tetris::writePuntuacions(const std::string& nomFitxer)
{
    std::ofstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
    {
        for (std::vector<Puntuacio>::iterator it = m_puntuacions.begin();
             it != m_puntuacions.end();
             it++)
        {
            fitxer << it->getNom() << " " << it->getHighScore() << std::endl;
        }

        fitxer.close();
    }
}
