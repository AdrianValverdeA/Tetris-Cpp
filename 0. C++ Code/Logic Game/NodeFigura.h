#include "InfoJoc.h"
#include "Figura.h"

class NodeFigura
{
public:
    NodeFigura() { m_next = nullptr; };
    NodeFigura(const Figura& value) { m_value = value; m_next = nullptr; }
    ~NodeFigura() {};

    NodeFigura* getNext() const { return m_next; }
    Figura getValue() const { return m_value; }

    void setNext(NodeFigura* next) { m_next = next; }
    void setValue(const Figura& value) { m_value = value; }
private:
    Figura m_value;
    NodeFigura* m_next;
};
