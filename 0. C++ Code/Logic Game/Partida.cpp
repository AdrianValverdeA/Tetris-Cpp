#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"
#include "Figura.h"

#include <windows.h>

#include <iostream>
#include <fstream>

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

Partida::Partida()
{
    m_temps = 0;
    m_joc.generaFigura();
    m_puntuacio = 0;
    m_finalitzat = false;
}

void Partida::actualitzaNormal(const double& dt)
{
    Partida::drawFons();
    if (m_joc.finalitzat())
    {
        Partida::drawJoc();
        Partida::drawGameOver();
    }
    else
    {
        Partida::moviment();
        Partida::drawJoc();
        Partida::baixa(dt);
    }
}

bool Partida::actualitzaTest(const double& deltaTime)
{
    m_temps += deltaTime;
    if (m_temps > m_period)
    {
        m_temps = 0.0;
        TipusMoviment moviment;
        if (m_moviments.empty())
        {
            Partida::drawFons();
            Partida::drawGameOver();
            std::cerr << "FINAL" << std::endl;
            m_finalitzat = true;
            return m_finalitzat;
        }
        else
        {
            moviment = m_moviments.getFirst();
            m_moviments.popFirst();
            int nFilesEliminades;
            switch (moviment)
            {
            case MOVIMENT_DRETA:
                m_joc.mouFigura(1);
                break;
            case MOVIMENT_ESQUERRA:
                m_joc.mouFigura(-1);
                break;
            case MOVIMENT_GIR_HORARI:
                m_joc.giraFigura(GIR_HORARI);
                break;
            case MOVIMENT_GIR_ANTI_HORARI:
                m_joc.giraFigura(GIR_ANTI_HORARI);
                break;
            case MOVIMENT_BAIXA_FINAL:
                nFilesEliminades = m_joc.baixarTotal();
                Partida::actualitzaPunts(nFilesEliminades);
                if (!m_figures.empty())
                {
                    Figura figura = m_figures.getFirst();
                    m_figures.popFirst();
                    m_joc.novaFigura(figura);
                }
                else
                {
                    m_finalitzat = true;
                    return m_finalitzat;
                }
                break;
            case MOVIMENT_BAIXA:
                nFilesEliminades = m_joc.baixaFigura();
                if (nFilesEliminades != -1)
                {
                    Partida::actualitzaPunts(nFilesEliminades);
                    if (!m_figures.empty())
                    {
                        Figura figura = m_figures.getFirst();
                        m_figures.popFirst();
                        m_joc.novaFigura(figura);
                    }
                    else
                    {
                        m_finalitzat = true;
                        return m_finalitzat;
                    }
                }
                break;
            }
            Partida::drawFons();
            m_joc.dibuixaTest();
        }
    }
    Sleep(750);
    return m_finalitzat;
}

void Partida::inicialitza(const std::string& fitxerInicial,
                          const std::string& fitxerFigures,
                          const std::string& fitxerMoviments,
                          const std::string& fitxerPuntuacions)
{
    if (fitxerInicial == "" || fitxerFigures == "" || fitxerMoviments == "")
    {
        m_finalitzat = m_joc.generaFigura();
        Partida::llegeixPuntuacions(fitxerPuntuacions);
    }
    else
    {
        m_joc.inicialitza(fitxerInicial);
        ifstream figures;
        figures.open(fitxerFigures);
        if (figures.is_open())
        {
            int tipus;
            int fila;
            int columna;
            int gir;
            while (figures >> tipus >> fila >> columna >> gir)
            {
                Figura figura;
                figura.inicialitza(TipusFigura(tipus), fila, columna);
                for (int i = 0; i < gir; i++)
                {
                    figura.gira(GIR_HORARI);
                }
                m_figures.insert(figura);
            }
            figures.close();
        }

        ifstream moviments;
        moviments.open(fitxerMoviments);
        if (moviments.is_open())
        {
            int tipus;
            while (moviments >> tipus)
            {
                m_moviments.insert(TipusMoviment(tipus));
            }
            moviments.close();
        }
    }
}

void Partida::drawFons() const
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS,
                                              0,
                                              0,
                                              false);
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS,
                                              300,
                                              0,
                                              false);
}

void Partida::baixa(const double& dt)
{
    m_freq = 1.0 + (0.75 * (m_puntuacio / 1000));
    m_period = 1.0 / m_freq;

    m_temps += dt;
    int n = -2;
    if (m_temps > m_period || Keyboard_GetKeyTrg(KEYBOARD_RCTRL))
    {
        n = m_joc.baixaFigura();
        m_temps = 0.0;
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
    {
        n = m_joc.baixarTotal();
    }

    if (n > -2)
    {
        if (n > 0)
        {
            m_puntuacio += PUNTUACIONS[min(n, 4) - 1];
            if (n == 4)
            {
                PlaySound(TEXT("./data/Audio/NES_Tetris_Sound_Effect_Tetris_Clear.wav"), NULL, SND_FILENAME | SND_SYNC);
                PlaySound(TEXT("./data/Audio/Old_RuneScape_Soundtrack_Newbie_Melody.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
            }
        }
        else
        {
            m_puntuacio += 10;
        }
    }
}

void Partida::moviment()
{
    if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT)
        || Keyboard_GetKeyTrg(KEYBOARD_D))
    {
        m_joc.mouFigura(1);
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_LEFT)
             || Keyboard_GetKeyTrg(KEYBOARD_A))
    {
        m_joc.mouFigura(-1);
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_Z) || Keyboard_GetKeyTrg(KEYBOARD_DOWN))
    {
        m_joc.giraFigura(GIR_ANTI_HORARI);
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_X) || Keyboard_GetKeyTrg(KEYBOARD_UP))
    {
        m_joc.giraFigura(GIR_HORARI);
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_C))
    {
        m_joc.swap();
    }
}

void Partida::drawGameOver() const
{
    std::string game_over = "GAME OVER";

    GraphicManager::getInstance()
        ->drawFont(FONT_WHITE_30,
                   SCREEN_SIZE_X / 2 / 1.5,
                   SCREEN_SIZE_Y / 2 / 1.5,
                   1.5,
                   game_over);
    PlaySound(0, 0, 0);
    PlaySound(TEXT("./data/Audio/Game_Over.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void Partida::drawJoc() const
{
    std::string puntuacio = "Puntuacio: " + std::to_string(m_puntuacio) + ", Nivell: " + std::to_string((m_puntuacio / 1000) + 1);
    GraphicManager::getInstance()
        ->drawFont(FONT_WHITE_30,
                   10,
                   10,
                   1.0,
                   puntuacio);

    std::string leaderboard = "Leaderboard: ";
    GraphicManager::getInstance()
        ->drawFont(FONT_WHITE_30,
                   10,
                   400,
                   1.0,
                   leaderboard);

    int x = 0;
    int n = 20;
    for (auto it = m_puntuacions.begin();
         it != m_puntuacions.end() && (x/n) < 5;
         it++)
    {
        if (0 == x)
        {
            std::string record = std::to_string(x/n + 1) + ". " + it->getNom() + "    " + std::to_string(it->getHighScore()) + " pts.";
            GraphicManager::getInstance()
                ->drawFont(FONT_RED_30,
                           10,
                           450 + x,
                           0.5,
                           record);
        }
        else
        {
            std::string record = std::to_string(x/n + 1) + ". " + it->getNom() + "    " + std::to_string(it->getHighScore()) + " pts.";
            GraphicManager::getInstance()
                ->drawFont(FONT_WHITE_30,
                           10,
                           450 + x,
                           0.5,
                           record);
        }
        x += n;
    }
    m_joc.dibuixa();
}

int Partida::getPuntuacio() const
{
    return m_puntuacio;
}

void Partida::actualitzaPunts(int n)
{
    if (n == 0)
    {
        m_puntuacio += 10;
    }
    else
    {
        m_puntuacio += PUNTUACIONS[min(n, 4) - 1];
    }
    m_nivell = (m_puntuacio / 100) + 1;
    m_period *= 0.75;
}

void Partida::llegeixPuntuacions(const std::string& nomFitxer)
{
    std::ifstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
    {
        std::string nom;
        int punts;
        while (fitxer >> nom >> punts)
        {
            Puntuacio p(nom, punts);
            m_puntuacions.push_back(p);
        }
        fitxer.close();
    }
}
