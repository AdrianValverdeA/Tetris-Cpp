#include "LlistaMoviment.h"

LlistaMoviment::LlistaMoviment(const LlistaMoviment& l)
{
	m_first = nullptr;
	m_last = nullptr;
	NodeMoviment* aux = l.getFirstNode();
	NodeMoviment* aux_nova = m_first;
	while (aux != nullptr)
	{
		aux_nova = LlistaMoviment::insert(aux->getValue());
		aux = aux->getNext();
	}
}

LlistaMoviment::~LlistaMoviment()
{
	while (m_first != nullptr)
    {
        LlistaMoviment::popFirst();
    }
}

LlistaMoviment& LlistaMoviment::operator=(const LlistaMoviment& l)
{
	if (this != &l)
	{
		while (m_first != nullptr)
        {
            popFirst();
        }
		NodeMoviment* aux = l.getFirstNode();
		NodeMoviment* aux_nova = m_first;
		while (aux != nullptr)
		{
			aux_nova = LlistaMoviment::insert(aux->getValue());
			aux = aux->getNext();
		}
	}
	return *this;
}

NodeMoviment *LlistaMoviment::insert(const TipusMoviment& value)
{
	NodeMoviment* aux = new NodeMoviment;
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

void LlistaMoviment::popFirst()
{
 	NodeMoviment* aux;
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

int LlistaMoviment::size() const
{
	int size = 0;
	NodeMoviment *aux = m_first;
	while (aux != nullptr)
	{
		size++;
		aux = aux->getNext();
	}
	return size;
}
