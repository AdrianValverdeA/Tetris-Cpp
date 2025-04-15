#include "InfoJoc.h"

class NodeMoviment
{
public:
    NodeMoviment() { m_next = nullptr; }
    NodeMoviment(const TipusMoviment& value) { m_value = value; m_next = nullptr; }
	~NodeMoviment() {}

    NodeMoviment* getNext() const { return m_next; }
    TipusMoviment getValue() const { return m_value; }

    void setNext(NodeMoviment* next) { m_next = next; }
    void setValue(const TipusMoviment& value) { m_value = value; }
private:
    TipusMoviment m_value;
    NodeMoviment* m_next;
};
