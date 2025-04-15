#pragma once


class Puntuacio
{
public:
    Puntuacio(const std::string& nom, const int puntuacio) { m_nom = nom; m_highScore = puntuacio; }

    void setNom(const std::string& nom) { m_nom = nom; }
    void setHighScore(const int score) { m_highScore = score; }

    std::string getNom() const { return m_nom; }
    int getHighScore() const { return m_highScore; }

private:
    std::string m_nom;
    int m_highScore;
};
