

#ifndef	GL_FRUSTUMCULLING_HPP
#define	GL_FRUSTUMCULLING_HPP


#include "GL_Matrix.hpp"
#include "GL_Vec3.hpp"

#include <cmath>


// class	BoundingBox;

namespace	myGL
{

  class	GL_FrustumCulling
  {
  private :

    enum e_FrustumSide {eRight, eLeft, eBottom, eTop, eBack, eFront};
    enum e_PlaneData {eA, eB, eC, eD};

  private :

    float	_Frustum[6][4];

  private :

    void	normalizePlane(e_FrustumSide side);

  public :

    void        calculateFrustum( const float* proj, const float* modl );
    inline void calculateFrustum( const GL_Matrix& proj, const GL_Matrix& modl )
    {
        calculateFrustum( proj.Ptr(), modl.Ptr() );
    }

  public :

    bool        pointInFrustum( float x, float y, float z ) const;
    inline bool pointInFrustum( const Vec3f& pos ) const
    {
      return (pointInFrustum(pos.x, pos.y, pos.z));
    }

    bool        sphereInFrustum( float x, float y, float z, float radius ) const;
    inline bool sphereInFrustum( const Vec3f& pos, float radius ) const
    {
      return (sphereInFrustum(pos.x, pos.y, pos.z, radius));
    }

    bool        cubeInFrustum( float x, float y, float z, float size ) const;
    inline bool cubeInFrustum( const Vec3f& pos, float size ) const
    {
      return ( cubeInFrustum(pos.x, pos.y, pos.z, size) );
    }

    bool	cubeInFrustum( const Vec3f& v, const Vec3f& s) const;


//  public :

//    void	CalcOrtho( Vec3f eye, Vec3f target,
//			   float left, float right,
//			   float bottom, float top,
//			   float nearval, float farval );

//    void	CalcPerspective( Vec3f eye, Vec3f target,
//				 float angle, float aspect_ratio,
//				 float nearval, float farval );

//  public :

//    void	DrawOrtho( Vec3f eye, Vec3f target,
//			   float left, float right,
//			   float bottom, float top,
//			   float nearval, float farval );

//    void	DrawPerspective( Vec3f eye, Vec3f target,
//				 float angle, float aspect_ratio,
//				 float nearval, float farval );

  };

}; // namespace	myGL


#endif // GL_FRUSTUMCULLING_HPP

