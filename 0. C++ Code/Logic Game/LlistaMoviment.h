#include "NodeMoviment.h"

class LlistaMoviment
{
public:
	LlistaMoviment() { m_first = nullptr; }
	LlistaMoviment(const LlistaMoviment& l);
    ~LlistaMoviment();

	LlistaMoviment& operator=(const LlistaMoviment& l);

	NodeMoviment* insert(const TipusMoviment& pt);
	void popFirst();

	int size() const;
    bool empty() const { return m_first == nullptr; }
	TipusMoviment getFirst() const { return m_first->getValue(); }
    NodeMoviment* getFirstNode() const { return m_first; }

 private:
	NodeMoviment* m_first;
	NodeMoviment* m_last;
};
