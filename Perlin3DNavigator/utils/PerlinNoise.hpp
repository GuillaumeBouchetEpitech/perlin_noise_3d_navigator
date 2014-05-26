

#ifndef	PERLINNOISE_HPP
#define PERLINNOISE_HPP


#include <cstdlib>


//#define SAMPLE_SIZE 1024
#define SAMPLE_SIZE 512


class PerlinNoise
{
public :

  PerlinNoise();
  PerlinNoise(int octaves, float freq, float amp, int seed);

public :

  void Set(int octaves, float freq, float amp, int seed);

public :

  float get(float x, float y);
  float get(float x, float y, float z);


  /////////////////////////////////////////////////////////////////////////


private :

  void init();
  // void init_perlin(int n,float p);

  float perlin_noise_2D(float vec[2]);
  float perlin_noise_3D(float vec[3]);

  float noise1(float arg);
  float noise2(float vec[2]);
  float noise3(float vec[3]);

  void normalize2(float v[2]);
  void normalize3(float v[3]);

private :

  int	_octaves;
  float	_frequency;
  float	_amplitude;
  int	_seed;

  int	p[SAMPLE_SIZE + SAMPLE_SIZE + 2];
  float	g3[SAMPLE_SIZE + SAMPLE_SIZE + 2][3];
  float	g2[SAMPLE_SIZE + SAMPLE_SIZE + 2][2];
  float	g1[SAMPLE_SIZE + SAMPLE_SIZE + 2];
  bool	_start;

};

#endif

