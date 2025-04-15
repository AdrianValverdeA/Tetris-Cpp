#include "Joc.h"
#include "GraphicManager.h"
#include "InfoJoc.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
using namespace std;

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		int tipusFigura;
		int fila;
		int columna;
		int girFigura;

		fitxer >> tipusFigura >> fila >> columna >> girFigura;
		m_figura.inicialitza(TipusFigura(tipusFigura), fila, columna);

		ColorFigura taulerFitxer[MAX_FILA][MAX_COL];
		int colorFigura;

		for (int i = 0; i < MAX_FILA; i++)
		{
			for (int j = 0; j < MAX_COL; j++)
			{
				fitxer >> colorFigura;
				taulerFitxer[i][j] = ColorFigura(colorFigura);
			}
		}

		for (int i = 0; i < girFigura; i++)
		{
			m_figura.gira(GIR_HORARI);
		}

		m_tauler.inicialitza(taulerFitxer);
		fitxer.close();
	}
}

void Joc::escriuTauler(const string& nomFitxer)
{
	ofstream fitxer;
	fitxer.open(nomFitxer);

	if (fitxer.is_open())
	{
		if (m_figura.getTipus() != NO_FIGURA)
		{
			m_tauler.posarFigura(m_figura);
		}

		ColorFigura taulerActual[MAX_FILA][MAX_COL];
		m_tauler.getTauler(taulerActual);

		for (int i = 0; i < MAX_FILA; i++)
		{
			for (int j = 0; j < MAX_COL; j++)
			{
				fitxer << taulerActual[i][j] << " ";
			}
			fitxer << endl;
		}

		fitxer.close();
	}
}

void Joc::invertirDireccioGir(DireccioGir& d)
{
	switch (d)
	{
		case GIR_ANTI_HORARI:
			d = GIR_HORARI;
			break;
		case GIR_HORARI:
			d = GIR_ANTI_HORARI;
			break;
	}
}

bool Joc::giraFigura(DireccioGir direccio)
{
    bool resultat = false;
    m_figura.gira(direccio);
    m_sombra.gira(direccio);
    Joc::sombra();
    if (!m_tauler.potMoure(m_figura))
    {
        resultat = true;
        invertirDireccioGir(direccio);
        m_figura.gira(direccio);
        m_sombra.gira(direccio);
        Joc::sombra();
    }

    return resultat;
}

bool Joc::mouFigura(int dirX)
{
    bool resultat = true;
    m_figura.mou(dirX);
    m_sombra.mou(dirX);
    Joc::sombra();

    if (!m_tauler.potMoure(m_figura))
    {
        resultat = false;
        m_figura.mou(-dirX);
        m_sombra.mou(-dirX);
        Joc::sombra();
    }

    return resultat;
}

int Joc::baixaFigura()
{
    int nFilesCompletades = -2;
    m_figura.baixa();
    if (!m_tauler.potMoure(m_figura))
    {
        if (m_figura.getY() <= 0)
        {
            m_finalitzat = true;
        }
        else
        {
            m_figura.puja();
            nFilesCompletades = m_tauler.posarFigura(m_figura);
            m_figura.reset();
            m_finalitzat = Joc::generaFigura();
        }
    }

    return nFilesCompletades;
}

bool Joc::generaFigura()
{
    srand(rand() ^ time(NULL));
    TipusFigura tipus = TipusFigura(rand() % N_TIPUS_FIGURES + 1);
    int nGir = (rand() % 4);

    if (m_seguent.getTipus() == NO_FIGURA)
    {
        m_figura.inicialitza(tipus, 1, N_COL_TAULER / 2);
        for (int i = 0; i < nGir; i++)
        {
            m_figura.gira(GIR_HORARI);
        }
        m_sombra.inicialitza(tipus, 1, N_COL_TAULER / 2);
        for (int i = 0; i < nGir; i++)
        {
            m_sombra.gira(GIR_HORARI);
        }

        srand(rand() ^ time(NULL));
        TipusFigura tipus = TipusFigura(rand() % N_TIPUS_FIGURES + 1);
        int nGir = (rand() % 4);
        m_seguent.inicialitza(tipus, 1, N_COL_TAULER / 2);
        for (int i = 0; i < nGir; i++)
        {
            m_seguent.gira(GIR_HORARI);
        }

    }
    else
    {
        m_figura = m_seguent;
        m_sombra = m_seguent;
        m_seguent.inicialitza(tipus, 1, N_COL_TAULER / 2);
        for (int i = 0; i < nGir; i++)
        {
            m_seguent.gira(GIR_HORARI);
        }
    }

    bool colisiona = !m_tauler.potMoure(m_figura);

    Joc::sombra();
    if (colisiona)
    {
        m_figura.reset();
        m_sombra.reset();
        m_finalitzat = true;
        std::string game_over = "GAME OVER";

        GraphicManager::getInstance()
            ->drawFont(FONT_WHITE_30,
                       SCREEN_SIZE_X / 2 / 1.5,
                       SCREEN_SIZE_Y / 2 / 1.5,
                       1.5,
                       game_over);
    }
    return colisiona;
}

int Joc::baixarTotal()
{
    int nFiles = -1;
    bool potMoure = m_tauler.potMoure(m_figura);
    while (potMoure = m_tauler.potMoure(m_figura))
    {
        m_figura.baixa();
    }
    if (!potMoure)
    {
        m_figura.puja();
        nFiles = m_tauler.posarFigura(m_figura);
        Joc::generaFigura();
    }

    return nFiles;
}

void Joc::sombra()
{
    m_sombra.setY(m_figura.getY());
    bool potMoure = m_tauler.potMoure(m_sombra);
    while (potMoure = m_tauler.potMoure(m_sombra))
    {
        m_sombra.baixa();
    }
    if (m_sombra.getY()>0)
        m_sombra.puja();
}

void Joc::dibuixa() const
{
    m_tauler.dibuixa();
    m_sombra.dibuixaSombra();
    m_seguent.dibuixaSeguent();
    m_swap.dibuixaHold();
    m_figura.dibuixa();
}

void Joc::dibuixaTest() const
{
    m_tauler.dibuixa();
    m_figura.dibuixa();
}

void Joc::swap()
{
    Figura fig = m_figura;
    Figura swp = m_swap;
    if (m_swap.getTipus() == NO_FIGURA)
    {
        int x = m_figura.getX();
        int y = m_figura.getY();
        m_swap = m_figura;
        Joc::generaFigura();
        m_sombra = m_figura;
    }
    else
    {
        Figura aux = m_swap;
        aux.setX(m_figura.getX());
        aux.setY(m_figura.getY());
        m_swap = m_figura;
        m_figura = aux;
        m_sombra = m_figura;
    }

    if (!m_tauler.potMoure(m_figura))
    {
        m_figura = fig;
        m_swap = swp;
        m_sombra = m_figura;
    }
    Joc::sombra();
}

void Joc::novaFigura(const Figura& figura)
{
    m_figura = figura;
}
