#ifndef INFO_JOC_H
#define INFO_JOC_H

typedef enum
{
    TECLA_ESQUERRA,
    TECLA_DRETA,
    TECLA_AMUNT,
    TECLA_ABAIX,
    TECLA_ESPAI,
    TECLA_ESCAPE,
    NO_TECLA
} TipusTecla;

typedef enum
{
    MOVIMENT_ESQUERRA = 0,
    MOVIMENT_DRETA,
    MOVIMENT_GIR_HORARI,
    MOVIMENT_GIR_ANTI_HORARI,
    MOVIMENT_BAIXA_FINAL,
    MOVIMENT_BAIXA,
} TipusMoviment;

const int N_TIPUS_FIGURES = 7;

typedef enum
{
    COLOR_NEGRE = 0,
    COLOR_GROC,
    COLOR_BLAUCEL,
    COLOR_MAGENTA,
    COLOR_TARONJA,
    COLOR_BLAUFOSC,
    COLOR_VERMELL,
    COLOR_VERD,
    NO_COLOR,
    COLOR_INV
} ColorFigura;

typedef enum
{
    NO_FIGURA = 0,
    FIGURA_O,
    FIGURA_I,
    FIGURA_T,
    FIGURA_L,
    FIGURA_J,
    FIGURA_Z,
    FIGURA_S
} TipusFigura;

typedef enum
{
	MODEJOC_NORMAL,
	MODEJOC_TEST
} ModeJoc;

// Tamany de la pantalla gràfica
const int SCREEN_SIZE_X = 800;
const int SCREEN_SIZE_Y = 635;

// Mida dels quadrats que formen el tauler
const int MIDA_QUADRAT = 26;

// Tamany del tauler
const int N_FILES_TAULER = 21;
const int N_COL_TAULER = 11;

// Posició del tauler a la pantalla
const int POS_X_TAULER = (SCREEN_SIZE_X / 2) - N_FILES_TAULER;
const int POS_Y_TAULER = 50;

#endif
