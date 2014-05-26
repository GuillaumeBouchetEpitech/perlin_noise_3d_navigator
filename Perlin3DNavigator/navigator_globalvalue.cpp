#include "navigator_globalvalue.h"


#include <cstdlib>


Navigator_GlobalValue*  Navigator_GlobalValue::pTest = NULL;


Navigator_GlobalValue::Navigator_GlobalValue()
    : _octaves(1),
      _frequency(1.0f),
      _amplitude(1.0f),
      _seed(0),

      _chunkSize(20),
      _chunkRange(1),

      _lightEnabled(false),
      _perturbationEnabled(false),

      _update_needed(false),

      _polyEnabled(true),
      _lineEnabled(true)
{
}

