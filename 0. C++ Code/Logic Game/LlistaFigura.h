#pragma once

#include "NodeFigura.h"

class LlistaFigura
{
public:
	LlistaFigura() { m_first = nullptr; m_last = nullptr; }
	~LlistaFigura();

	LlistaFigura(const LlistaFigura& l);
	LlistaFigura& operator=(const LlistaFigura& l);

	NodeFigura* insert(const Figura& pt);
	void popFirst();

	int size() const;
	bool empty() const { return m_first == nullptr; }
    Figura getFirst() const { return m_first->getValue(); }
    NodeFigura* getFirstNode() const { return m_first; }

 private:
	NodeFigura* m_first;
	NodeFigura* m_last;
};
