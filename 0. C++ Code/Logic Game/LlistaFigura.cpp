#include "LlistaFigura.h"

LlistaFigura::LlistaFigura(const LlistaFigura& l)
{
	m_first = nullptr;
	m_last = nullptr;
	NodeFigura* aux = l.getFirstNode();
	NodeFigura* aux_nova = m_first;
	while (aux != nullptr)
	{
		aux_nova = LlistaFigura::insert(aux->getValue());
		aux = aux->getNext();
	}
}

LlistaFigura::~LlistaFigura()
{
	while (m_first != nullptr)
    {
        LlistaFigura::popFirst();
    }
}

LlistaFigura& LlistaFigura::operator=(const LlistaFigura& l)
{
	if (this != &l)
	{
		while (m_first != nullptr)
        {
            LlistaFigura::popFirst();
        }
		NodeFigura* aux = l.getFirstNode();
		NodeFigura* aux_nova = m_first;
		while (aux != nullptr)
		{
			aux_nova = LlistaFigura::insert(aux->getValue());
			aux = aux->getNext();
		}
	}
	return *this;
}

NodeFigura *LlistaFigura::insert(const Figura& value)
{
	NodeFigura* aux = new NodeFigura;
	if (aux != nullptr)
	{
		aux->setValue(value);
		aux->setNext(nullptr);
		if (m_first == nullptr)
		{
			m_first = aux;
		}
		else
		{
			m_last->setNext(aux);
		}
		m_last = aux;
	}
	return aux;
}

void LlistaFigura::popFirst()
{
 	NodeFigura* aux;
	if (m_first == m_last)
	{
		delete m_first;
		m_first = nullptr;
		m_last = nullptr;
	}
	else
	{
		aux = m_first->getNext();
		delete m_first;
		m_first = aux;
	}
}

int LlistaFigura::size() const
{
	int size = 0;
	NodeFigura *aux = m_first;
	while (aux != nullptr)
	{
		size++;
		aux = aux->getNext();
	}
	return size;
}
