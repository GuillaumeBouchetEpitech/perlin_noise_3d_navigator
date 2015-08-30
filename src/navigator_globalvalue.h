#ifndef NAVIGATOR_GLOBALVALUE_H
#define NAVIGATOR_GLOBALVALUE_H

struct  Navigator_GlobalValue
{
public :
    unsigned int    _octaves;
    float           _frequency;
    float           _amplitude;
    unsigned int    _seed;

    unsigned int    _chunkSize;
    unsigned int    _chunkRange;

    bool            _lightEnabled;
    bool            _perturbationEnabled;

    bool            _update_needed;

    bool            _polyEnabled;
    bool            _lineEnabled;


public:
    static Navigator_GlobalValue*   pTest;

public:
    Navigator_GlobalValue();

};

#endif // NAVIGATOR_GLOBALVALUE_H
