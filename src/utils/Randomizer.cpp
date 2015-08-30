

#include "Randomizer.hpp"


// #define	RAND_MAX	2147483647 // int max positive value : 2,147,483,647
#define	RAND_MAX	2147483648


namespace
{
    unsigned long	s_seed = 1;
}


int	my_rand()
{
  long	hi, lo, x;

  if (s_seed == 0)
    s_seed = 123459876;

  hi = s_seed / 127773;
  lo = s_seed % 127773;
  x = 16807 * lo - 2836 * hi;

  if (x < 0)
    x += 0x7fffffff;

  return ( (s_seed = x) % ((unsigned long)RAND_MAX + 1));
}

void	my_srand(int seed)
{
  s_seed = seed;
}

int	my_rangeRand(int min, int max)
{
  return  ( min + ( my_rand() / RAND_MAX * (max - min) ) );
}

float	my_rangeRand(float min, float max)
{
  return  ( min + ( (float)my_rand() / RAND_MAX * (max - min) ) );
}
