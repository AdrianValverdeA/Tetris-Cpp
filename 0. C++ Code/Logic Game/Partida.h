#pragma once

#include <stdio.h>
#include <string>
#include <vector>

#include "InfoJoc.h"
#include "Joc.h"

#include "LlistaFigura.h"
#include "LlistaMoviment.h"
#include "Puntuacio.h"

const size_t PUNTUACIONS[] = { 100, 150, 175, 200 };

class Partida
{
public:
    Partida();

    void inicialitza(const std::string& fitxerInicial,
                     const std::string& fitxerFigures,
                     const std::string& fitxerMoviments,
                     const std::string& fitxerPuntuacions);

    void actualitzaNormal(const double& deltaTime);
    bool actualitzaTest(const double& deltaTime);
    void actualitzaPunts(int n);
    void drawPuntuacioNivell() const;
    void drawGameOver() const;
    void baixa(const double& dt);
    void drawJoc() const;
    void drawFons() const;
    void moviment();
    void llegeixPuntuacions(const std::string& nomFitxer);
    bool finalitzat() const { return m_joc.finalitzat(); }
    int getPuntuacio() const;

private:
    double m_temps;
    Joc m_joc;
    bool m_finalitzat;
    int m_puntuacio;
    int m_nivell;
    double m_freq;
    double m_period;
    LlistaFigura m_figures;
	LlistaMoviment m_moviments;
    std::vector<Puntuacio> m_puntuacions;
};
