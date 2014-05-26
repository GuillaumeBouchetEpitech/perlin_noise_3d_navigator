
#include "abstract_geometry.h"


Abstract_Geometry::Abstract_Geometry( t_Shader_Perlin3D& shader )
    : _shader(shader),
      _isInitialized(false),
      _VBO_and_VAO_initialized(false)
{
}

