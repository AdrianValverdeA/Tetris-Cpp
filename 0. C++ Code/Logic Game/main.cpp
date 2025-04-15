#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)
    #include <iostream>
    #define SDL_MAIN_HANDLED
    #include <windows.h>
    #include "../Graphic Lib/libreria.h"
    #include "../Graphic Lib/NFont/NFont.h"
    #include <conio.h>
#elif __APPLE__
    #include "../Graphic Lib/libreria.h"
    #include "../Graphic Lib/NFont/NFont.h"
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdocumentation"
    #include <SDL2/SDL.h>
    #pragma clang diagnostic pop
#endif

#include "./Tetris.h"
#include "./InfoJoc.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void printOptions()
{
    std::cout << "==============    TETRIS     ==============" << std::endl;
    std::cout << "===========================================" << std::endl;
    std::cout << "Premi '1' per jugar en mode NORMAL" << std::endl;
    std::cout << "Premi '2' pel mode TEST" << std::endl;
    std::cout << "Premi '3' per veure les puntuacions" << std::endl;
    std::cout << "Premi qualsevol altre tecla per sortir" << std::endl;
}

int main(int argc, const char** argv)
{
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    std::cout << "Copyright (C) 2024 Adrian Valverde, Biel Sala" << std::endl;

    Tetris tetris("./data/Games/puntuacions.txt");
    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);
    char op;
    bool sortir = false;
    do
    {
        printOptions();
        op = _getch();
        switch (op)
            {
            case '1':
                {
                    system("CLS");
                    PlaySound(TEXT("./data/Audio/Old_RuneScape_Soundtrack_Newbie_Melody.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
                    int punts;
                    std::string jugador;
                    punts = tetris.juga(pantalla, MODEJOC_NORMAL, "", "", "");
                    PlaySound(0, 0, 0);
                    std::cout << "Nom del jugador: ";
                    std::getline(std::cin, jugador);
                    tetris.pushPuntuacio(jugador, punts);
                    system("CLS");
                }
                break;

            case '2':
                {
                    int punts;
                    std::string fitxerInicial;
                    std::string fitxerFigures;
                    std::string fitxerMoviments;
                    std::cout << "Fitxer estat inicial tauler: ";
                    getline(std::cin, fitxerInicial);
                    fitxerInicial = "./data/Games/" + fitxerInicial;
                    std::cout << "Fitxer sequencia figures: ";
                    getline(std::cin, fitxerFigures);
                    fitxerFigures = "./data/Games/" + fitxerFigures;
                    std::cout << "Fitxer sequencia moviments: ";
                    getline(std::cin, fitxerMoviments);
                    fitxerMoviments = "./data/Games/" + fitxerMoviments;
                    punts = tetris.juga(pantalla,
                                        MODEJOC_TEST,
                                        fitxerInicial,
                                        fitxerFigures,
                                        fitxerMoviments);
                }
                break;

            case '3':
                {
                    system("CLS");
                    tetris.printPuntuacions();
                }
                break;

            default:
                {
                    sortir = true;
                }
                break;
            }
        tetris.writePuntuacions("./data/Games/puntuacions.txt");
    } while(!sortir);

    SDL_Quit();
    return 0;
}
