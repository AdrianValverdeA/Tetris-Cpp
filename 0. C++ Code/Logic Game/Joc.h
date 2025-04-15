#pragma once
#include "Tauler.h"
#include "Figura.h"
#include <string>
using namespace std;

class Joc
{
public:
	Joc() { m_finalitzat = false; m_swap.setTipus(NO_FIGURA); }
	void inicialitza(const string& nomFitxer);
	bool giraFigura(DireccioGir direccio);
	bool mouFigura(int dirX);

	void escriuTauler(const string& nomFitxer);

    int getFiguraFila() const { return m_figura.getFila(); }
    int getFiguraColumna() const { return m_figura.getColumna(); }
    TipusFigura getTipusFigura() const { return m_figura.getTipus(); }
    Figura getFigura() const { return m_figura; }
    Tauler getTauler() const { return m_tauler; }
    bool potMoure() const { return m_tauler.potMoure(m_figura); }

    bool generaFigura();
    void novaFigura(const Figura& figura);
    void dibuixa() const;
    void dibuixaTest() const;
    void dibuixaHold() const { m_swap.dibuixaHold(); }
    void dibuixaSeguent() const { m_seguent.dibuixaSeguent(); }
    bool finalitzat() const { return m_finalitzat; }

    int baixaFigura();
	int baixarTotal();
    void swap();
    void sombra();
private:
	void invertirDireccioGir(DireccioGir& d);
	Tauler m_tauler;
	Figura m_figura;
    Figura m_seguent;
    Figura m_swap;
    Figura m_sombra;
    bool m_finalitzat;
    ModeJoc m_mode;
};
