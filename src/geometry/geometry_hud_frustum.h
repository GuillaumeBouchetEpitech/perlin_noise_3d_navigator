#ifndef GEOMETRY_HUD_FRUSTUM_H
#define GEOMETRY_HUD_FRUSTUM_H


#include "../myGL/GL_FreeFlyController.hpp"
#include "t_vertex.h"

#include "abstract_geometry.h"


class   Geometry_HUD_Frustum : public Abstract_Geometry
{
public :
    Geometry_HUD_Frustum( t_Shader_Perlin3D& shader );

public :
    void    generate( double aspect_ratio );
    void    render( const myGL::GL_Matrix& modelviewMatrix,
                    const myGL::GL_FreeFlyController& FreeFly,
                    double aspect_ratio );

public :
    inline void regenerate()    { _isInitialized = false; }

};



#endif // GEOMETRY_HUD_FRUSTUM_H
