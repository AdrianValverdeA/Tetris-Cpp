#include "Figura.h"

#include <iostream>
#include "GraphicManager.h"

using namespace std;

void Figura::reset()
{
	for (int i = 0; i < m_altura; i++)
	{
		for (int j = 0; j < m_amplada; j++)
		{
			m_matriu[i][j] = ColorFigura(0);

		}
	}
}

void Figura::inicialitzaMatriu(TipusFigura tip)
{
	switch (tip)
	{
	case FIGURA_I:

		m_amplada = 4;
		m_altura = 4;
		reset();
		m_dim = MAX_DIM;
		m_color = COLOR_BLAUCEL;
		for (int i = 0; i < m_dim; i++)
			for (int j = 0; j < m_dim; j++)
				m_matriu[i][j] = matFigI[i][j];
		break;

	case FIGURA_O:

		m_amplada = 2;
		m_altura = 2;
		reset();
		m_dim = 2;
		m_color = COLOR_GROC;
		for (int i = 0; i < m_dim; i++)
			for (int j = 0; j < m_dim; j++)
				m_matriu[i][j] = matFigO[i][j];
		break;

	case FIGURA_T:

		m_amplada = 3;
		m_altura = 3;
		reset();
		m_dim = 3;
		m_color = COLOR_MAGENTA;
		for (int i = 0; i < m_dim; i++)
			for (int j = 0; j < m_dim; j++)
				m_matriu[i][j] = matFigT[i][j];
		break;

	case FIGURA_L:

		m_amplada = 3;
		m_altura = 3;
		reset();
		m_dim = 3;
		m_color = COLOR_TARONJA;
		for (int i = 0; i < m_dim; i++)
			for (int j = 0; j < m_dim; j++)
				m_matriu[i][j] = matFigL[i][j];
		break;

	case FIGURA_J:

		m_amplada = 3;
		m_altura = 3;
		reset();
		m_dim = 3;
		m_color = COLOR_BLAUFOSC;
		for (int i = 0; i < m_dim; i++)
			for (int j = 0; j < m_dim; j++)
				m_matriu[i][j] = matFigJ[i][j];
		break;

	case FIGURA_Z:

		m_amplada = 3;
		m_altura = 3;
		reset();
		m_dim = 3;
		m_color = COLOR_VERMELL;
		for (int i = 0; i < m_dim; i++)
			for (int j = 0; j < m_dim; j++)
				m_matriu[i][j] = matFigZ[i][j];
		break;

	case FIGURA_S:

		m_amplada = 3;
		m_altura = 3;
		reset();
		m_dim = 3;
		m_color = COLOR_VERD;
		for (int i = 0; i < m_dim; i++)
			for (int j = 0; j < m_dim; j++)
				m_matriu[i][j] = matFigS[i][j];
		break;
	}
}

void Figura::mou(int dirX)
{
	m_x += dirX;
}

void Figura::baixa()
{
	m_y++;
}

void Figura::puja()
{
	m_y--;
}

void Figura::gira(DireccioGir direccio)
{

    Figura::transposaMatriu();
	switch (direccio)
	{
	case GIR_HORARI:
	{
        Figura::invertirColumnes();
		m_formaActual = (m_formaActual + 1) % 4;
	}
	break;

	case GIR_ANTI_HORARI:
	{
        Figura::invertirFiles();
		m_formaActual = (m_formaActual - 1) % 4;
	}
	break;
	}
}

void Figura::inicialitza(TipusFigura tip, int fila, int columna)
{
	m_tipus = tip;
	m_x = columna;
	m_y = fila;
	m_formaActual = 0;
    Figura::inicialitzaMatriu(tip);
}

void Figura::getFigura(ColorFigura figura[MAX_DIM][MAX_DIM]) const
{
	for (int i = 0; i < MAX_DIM; ++i)
	{
		for (int j = 0; j < MAX_DIM; ++j)
		{
			figura[i][j] = m_matriu[i][j];
		}
	}
}

void Figura::setFigura(const ColorFigura figura[MAX_DIM][MAX_DIM])
{
    for (int i = 0; i < MAX_DIM; ++i)
    {
		for (int j = 0; j < MAX_DIM; ++j)
		{
			m_matriu[i][j] = figura[i][j];
		}
	}
}


void Figura::transposaMatriu()
{
	ColorFigura out[MAX_DIM][MAX_DIM];
	for (int i = 0; i < m_dim; i++)
	{
		for (int j = 0; j < m_dim; j++)
		{
			out[i][j] = m_matriu[j][i];
		}
	}
	for (int i = 0; i < m_dim; i++)
	{
		for (int j = 0; j < m_dim; j++)
		{
			m_matriu[i][j] = out[i][j];
		}
	}
}

void Figura::invertirColumnes()
{
	int col, col2;
	if (m_dim != 2)
	{
		if (m_dim == 3)
		{
			col = 0;
			col2 = 2;
		}
		else
		{
			col = 1;
			col2 = 2;
		}
		ColorFigura out;
		for (int i = 0; i < m_dim; i++)
		{
			out = m_matriu[i][col];
			m_matriu[i][col] = m_matriu[i][col2];
			m_matriu[i][col2] = out;
		}
	}
}

void Figura::invertirFiles()
{
	int fila, fila2;
	if (m_dim != 2)
	{
		if (m_dim == 3)
		{
			fila = 0;
			fila2 = 2;
		}
		else
		{
			fila = 1;
			fila2 = 2;
		}
		ColorFigura out;
		for (int i = 0; i < m_dim; i++)
		{
			out = m_matriu[fila][i];
			m_matriu[fila][i] = m_matriu[fila2][i];
			m_matriu[fila2][i] = out;
		}
	}
}

void Figura::dibuixa() const
{
    for (int i = 0; i < m_dim; i++)
    {
        for (int j = 0; j < m_dim; j++)
        {
            if (m_matriu[i][j] != COLOR_NEGRE)
            {
                GraphicManager::getInstance()
                    ->drawSprite(IMAGE_NAME(m_color + 1),
                                 POS_X_TAULER + ((j + m_x) * MIDA_QUADRAT),
                                 POS_Y_TAULER + ((m_y + i - 1) * MIDA_QUADRAT),
                                 false);
            }
        }
    }
}

void Figura::dibuixaHold() const
{
    std::string hold = "Hold: ";
    GraphicManager::getInstance()
        ->drawFont(FONT_WHITE_30,
                   10,
                   80,
                   1.0,
                   hold);
    for (int i = 0; i < m_dim; i++)
    {
        for (int j = 0; j < m_dim; j++)
        {
            if (m_matriu[i][j] != COLOR_NEGRE)
            {
                GraphicManager::getInstance()
                    ->drawSprite(IMAGE_NAME(m_color + 1),
                                 100 + ((j) * MIDA_QUADRAT),
                                 30 + POS_Y_TAULER + ((i) * MIDA_QUADRAT),
                                 false);
            }
        }
    }
}

void Figura::dibuixaSombra() const
{
    for (int i = 0; i < m_dim; i++)
    {
        for (int j = 0; j < m_dim; j++)
        {
            if (m_matriu[i][j] != COLOR_NEGRE)
            {
                GraphicManager::getInstance()
                    ->drawSprite(IMAGE_NAME(COLOR_INV),
                        POS_X_TAULER + ((j + m_x) * MIDA_QUADRAT),
                        POS_Y_TAULER + ((m_y + i - 1) * MIDA_QUADRAT),
                        false);
            }
        }
    }
}

void Figura::dibuixaSeguent() const
{
    std::string seguent = "Seguent: ";
    GraphicManager::getInstance()
        ->drawFont(FONT_WHITE_30,
                   10,
                   200,
                   1.0,
                   seguent);
    for (int i = 0; i < m_dim; i++)
    {
        for (int j = 0; j < m_dim; j++)
        {
            if (m_matriu[i][j] != COLOR_NEGRE)
            {
                GraphicManager::getInstance()
                    ->drawSprite(IMAGE_NAME(m_color + 1),
                                 100 + ((j) * MIDA_QUADRAT),
                                 200 + POS_Y_TAULER + ((i) * MIDA_QUADRAT),
                                 false);
            }
        }
    }
}
