#pragma once
#include "Figura.h"

class Tauler
{
public:
    Tauler();

    void inicialitza(ColorFigura taulerTests[N_FILES_TAULER][N_COL_TAULER]);
    bool potMoure(const Figura& figura) const;

    int posarFigura(const Figura& figura);
    void eliminarFila(int fila);

    void getTauler(ColorFigura tauler[N_FILES_TAULER][N_COL_TAULER]) const;
    void getLliures(int pecesLliures[N_COL_TAULER]) const;

    void dibuixa() const;

private:
    ColorFigura m_tauler[N_FILES_TAULER + 1][N_COL_TAULER + 2];
    int m_pecesLliures[N_FILES_TAULER];
};
