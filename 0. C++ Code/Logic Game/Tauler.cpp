#include "Tauler.h"
#include "Figura.h"

#include "GraphicManager.h"

#include <iostream>
using namespace std;
Tauler::Tauler()
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        m_tauler[i][0] = NO_COLOR;
        m_tauler[i][MAX_COL + 1] = NO_COLOR;
        for (int j = 0; j < MAX_COL; j++)
        {
            m_tauler[i][j+1] = COLOR_NEGRE;
        }
    }
    for (int j = 0; j < MAX_COL+2; j++)
    {
        m_tauler[MAX_FILA][j] = NO_COLOR;
    }
    for (int i = 0; i < MAX_FILA; i++)
        m_pecesLliures[i] = MAX_COL;
}

void Tauler::inicialitza(ColorFigura taulerTests[MAX_FILA][MAX_COL])
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        m_pecesLliures[i] = MAX_COL;
    }

    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            m_tauler[i][j + 1] = taulerTests[i][j];

            if (taulerTests[i][j] != COLOR_NEGRE)
            {
                m_pecesLliures[i]--;
            }
        }
    }
}

bool Tauler::potMoure(const Figura& figura) const
{
    ColorFigura figuraInsertada[MAX_DIM][MAX_DIM];

    bool xoca = false; // si xoca la figura xoca sera true i per tant no es podra moure

    int filaFigura = 0;
    figura.getFigura(figuraInsertada);
    int dim = figura.getDim();

    int filaTauler = figura.getFila() - 1;
    while (!xoca && filaFigura < dim)
    {
        int columnaTauler = figura.getColumna();
        int columnaFigura = 0;
        while (!xoca && columnaFigura < dim)
        {
            if ((figuraInsertada[filaFigura][columnaFigura] * m_tauler[filaTauler][columnaTauler]) != COLOR_NEGRE)
            {
                xoca = true;
            }
            columnaFigura++;
            columnaTauler++;
        }

        filaFigura++;
        filaTauler++;
    }

    if (m_tauler[1][7] != COLOR_NEGRE || m_tauler[2][7] != COLOR_NEGRE || m_tauler[1][6] != COLOR_NEGRE || m_tauler[1][8] != COLOR_NEGRE)
    {
        xoca = true;
    }

    return !xoca; // invertim per a que la logica sigui positiva en base si es pot moure o no
}

void Tauler::eliminarFila(int fila)
{
    for (fila; fila > 0; fila--)
    {
        for (int j = 1; j <= MAX_COL; j++)
        {
            m_tauler[fila][j] = m_tauler[fila - 1][j];
        }
    }


    for (int j = 1; j <= MAX_COL; j++)
    {
        m_tauler[0][j] = COLOR_NEGRE;
    }
}

int Tauler::posarFigura(const Figura& figura)
{
    ColorFigura figuraInsertada[MAX_DIM][MAX_DIM];
    int nFilesCompletades = -1;

    ColorFigura color = figura.getColor();
    figura.getFigura(figuraInsertada);
    int filaTauler = figura.getFila() - 1;
    for (int filaFigura = 0; filaFigura < figura.getAltura(); filaFigura++)
    {
        int colTauler = figura.getColumna();
        for (int columnaFigura = 0; columnaFigura < figura.getAmplada(); columnaFigura++)
        {
            if (figuraInsertada[filaFigura][columnaFigura] != 0)
            {
                m_tauler[filaTauler][colTauler] = color;
                m_pecesLliures[filaTauler]--;
                if (m_pecesLliures[filaTauler] == 0)
                {
                    nFilesCompletades == -1 ? nFilesCompletades = 1 : nFilesCompletades++;
                    eliminarFila(filaTauler);
                }
            }
            colTauler++;
        }
        filaTauler++;
    }

    for (int i = 0; i < MAX_FILA; i++)
    {
        m_pecesLliures[i] = 0;
        for (int j = 0; j < MAX_COL; j++)
        {
            if (m_tauler[i][j+1] == COLOR_NEGRE)
                m_pecesLliures[i]++;
        }
    }
    return nFilesCompletades;
}


void Tauler::getTauler(ColorFigura tauler[MAX_FILA][MAX_COL]) const
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
            tauler[i][j] = m_tauler[i][j + 1];
    }
}

void Tauler::getLliures(int pecesLliures[MAX_COL]) const
{
    for (int i = 0; i < MAX_COL; i++)
    {
        pecesLliures[i] = m_pecesLliures[i];
    }
}

void Tauler::dibuixa() const
{
    GraphicManager::getInstance()
        ->drawSprite(GRAFIC_TAULER,
                     POS_X_TAULER,
                     POS_Y_TAULER,
                     false);

    for (int i = 0; i < N_FILES_TAULER; i++)
    {
        for (int j = 0; j < N_COL_TAULER; j++)
        {
            if (m_tauler[i][j + 1] != COLOR_NEGRE)
            {

                GraphicManager::getInstance()
                    ->drawSprite(IMAGE_NAME(m_tauler[i][j + 1] + 1),
                                 POS_X_TAULER + ((j + 1) * MIDA_QUADRAT),
                                 POS_Y_TAULER + ((i) * MIDA_QUADRAT),
                                 false);
            }
        }
    }

}
