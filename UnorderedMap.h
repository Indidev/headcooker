#ifndef UNORDEREDMAP_H
#define UNORDEREDMAP_H

#include <vector>

template<typename KEY, typename VALUE> class UnorderedMap
{
public:

    struct Pair{
        KEY key;
        VALUE value;
    };

    VALUE &operator[] (const KEY key)
    {
        for(Pair elem : elements) {
            if (key == elem.key)
                return elem.value;
        }
        Pair newP;
        newP.key = key;
        elements.push_back(newP);
        return elements.back().value;
    }

    bool hasKey(const KEY key)
    {
        for (Pair elem : elements) {
            if (key == elem.key)
                return true;
        }
        return false;
    }
    void erase(const KEY key)
    {
        for (int i = 0; i < elements.size(); i++) {
            if (elements[i].first == key) {
                elements.erase(i);
                break;
            }
        }
    }
    int size() { return elements.size(); }
    VALUE &at(int index) { return elements[index].second;  }
    VALUE &at(const KEY key) { return &this[key]; }
    bool empty() { return elements.empty(); }
    void clear() { elements.clear(); }


    typedef typename std::vector<Pair>::iterator iter;
    typedef typename std::vector<Pair>::const_iterator const_iter;
    iter begin() { return elements.begin(); }
    iter end() { return elements.end(); }
    const_iter cbegin() { return elements.cbegin(); }
    const_iter cend() { return elements.cend(); }
    const_iter begin() const {return elements.begin(); }
    const_iter end() const {return elements.end(); }

protected:
    std::vector<Pair> elements;
};

#endif // UNORDEREDMAP_H
