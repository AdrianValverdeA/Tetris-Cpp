#pragma once
#include "InfoJoc.h"

const int MAX_COL = N_COL_TAULER;
const int MAX_FILA = N_FILES_TAULER;
const int TAULER_WIDTH = MAX_COL / 2;
const int MAX_DIM = 4;

const int MAX_ALCADA = 4;
const int MAX_AMPLADA = 4;

typedef enum
{
    GIR_HORARI = 0,
    GIR_ANTI_HORARI
} DireccioGir;

const ColorFigura matFigO[MAX_DIM][MAX_DIM] = { {COLOR_GROC, COLOR_GROC, COLOR_NEGRE, COLOR_NEGRE},
                                       {COLOR_GROC, COLOR_GROC, COLOR_NEGRE, COLOR_NEGRE},
                                       {COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE},
                                       {COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE} };

const ColorFigura matFigI[MAX_DIM][MAX_DIM] = { {COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE},
                                       {COLOR_BLAUCEL, COLOR_BLAUCEL, COLOR_BLAUCEL, COLOR_BLAUCEL},
                                       {COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE},
                                       {COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE} };

const ColorFigura matFigT[MAX_DIM][MAX_DIM] = { {COLOR_NEGRE, COLOR_MAGENTA, COLOR_NEGRE, COLOR_NEGRE},
                                       {COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA, COLOR_NEGRE},
                                       {COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE},
                                       {COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE} };

const ColorFigura matFigL[MAX_DIM][MAX_DIM] = { {COLOR_NEGRE, COLOR_NEGRE, COLOR_TARONJA, COLOR_NEGRE},
                                       {COLOR_TARONJA, COLOR_TARONJA, COLOR_TARONJA, COLOR_NEGRE},
                                       {COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE},
                                       {COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE} };

const ColorFigura matFigJ[MAX_DIM][MAX_DIM] = { {COLOR_BLAUFOSC, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE},
                                       {COLOR_BLAUFOSC, COLOR_BLAUFOSC, COLOR_BLAUFOSC, COLOR_NEGRE},
                                       {COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE},
                                       {COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE} };

const ColorFigura matFigZ[MAX_DIM][MAX_DIM] = { {COLOR_VERMELL, COLOR_VERMELL, COLOR_NEGRE, COLOR_NEGRE},
                                       {COLOR_NEGRE, COLOR_VERMELL, COLOR_VERMELL, COLOR_NEGRE},
                                       {COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE},
                                       {COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE} };

const ColorFigura matFigS[MAX_DIM][MAX_DIM] = { {COLOR_NEGRE, COLOR_VERD, COLOR_VERD, COLOR_NEGRE},
                                       {COLOR_VERD, COLOR_VERD, COLOR_NEGRE, COLOR_NEGRE},
                                       {COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE},
                                       {COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE, COLOR_NEGRE} };

class Figura
{
public:
    /* Constructors */
    // Figura();

    /* Setters */
    void setTipus(TipusFigura tipus) { m_tipus = tipus; }
    void setColor(ColorFigura color) { m_color = color; }
    void setX(int x) { m_x = x; }
    void setY(int y) { m_y = y; }
    void setColumna(int x) { m_x = x; }
    void setFila(int y) { m_y = y; }
    void setFormaActual(int forma) { m_formaActual = forma; }
    void setAmplada(int n) { m_amplada = n; }
    void setAltura(int n) { m_altura = n; }
    void setFigura(const ColorFigura figura[MAX_DIM][MAX_DIM]);

    /* Getters */
    TipusFigura getTipus() const { return m_tipus; }
    ColorFigura getColor() const { return m_color; }
    int getX() const { return m_x; }
    int getY() const { return m_y; }
    int getColumna() const { return m_x; }
    int getFila() const { return m_y; }
    int getFormaActual() const { return m_formaActual; }
    int getDim() const { return m_dim; }
    void getFigura(ColorFigura figura[MAX_DIM][MAX_DIM]) const;
    int getAmplada() const { return m_amplada; }
    int getAltura() const { return m_altura; }

    /* Metodes */
    void mou(int dirX);
    void baixa();
    void puja();
    void gira(DireccioGir direccio);
    void inicialitza(TipusFigura tip, int fila, int columna);
    void dibuixa() const;
    void dibuixaHold() const;
    void dibuixaSombra() const;
    void dibuixaSeguent() const;
    void reset();

    Figura operator=(const Figura& figura)
    {
        Figura::inicialitza(figura.getTipus(), figura.getY(), figura.getX());
        Figura::setFormaActual(figura.getFormaActual());
        ColorFigura matriuFigura[MAX_DIM][MAX_DIM];
        figura.getFigura(matriuFigura);
        Figura::setFigura(matriuFigura);
        return *this;
    }

private:
    void transposaMatriu();
    void invertirColumnes();
    void invertirFiles();
    void inicialitzaMatriu(TipusFigura tip);
    TipusFigura m_tipus;
    ColorFigura m_color;
    int m_x;
    int m_y;
    int m_formaActual;
    ColorFigura m_matriu[MAX_DIM][MAX_DIM];
    int m_dim;
    int m_amplada;
    int m_altura;
};
