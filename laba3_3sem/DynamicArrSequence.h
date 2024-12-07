#pragma once

#include "MutableSequence.h"
#include "DynamicArr.h"

template<class ElmType>
class MutableSequence;

template<class ElmType>
class DynamicArrSequence : public MutableSequence<ElmType>
{
private:
    DynamicArray<ElmType> _inner;
public:
    DynamicArrSequence() {}

    DynamicArrSequence(int size) : _inner(size) {}

    DynamicArrSequence(ElmType* source, int size) : _inner(source ,size ) {}

    DynamicArrSequence(const DynamicArray<ElmType>& source) : _inner(source) {}

    void clearArr() override
    {
        _inner.clearArr();
    }

    ElmType& operator[](int index) override 
    {
        return _inner[index];
    }

    const ElmType& getFirst() const override
    {
        return _inner[0];
    };

    const ElmType& getLast() const override
    {
        return _inner[_inner.get_colElm() - 1];
    }

    void popLast() override
    {
        _inner.pop_back();
    }

    void pop_index(int idx) override
    {
        _inner.pop_index(idx);
    }

    const ElmType& get(int index) const override
    {
        return _inner[index];
    }
    int get_size() const override
    {
        return _inner.get_size();
    }

    int get_colElm() const override
    {
        return _inner.get_colElm();
    }

    void concat(const DynamicArray<ElmType> source) override
    {
        for (int i = 0; i < source.get_colElm(); i++)
            _inner.push_back(source[i]);
    }


    void push_back(ElmType value) override
    {
        _inner.push_back(value);
    }

    void set(int index, const ElmType& value) override
    {
        _inner.set(index, value);
    }
};
