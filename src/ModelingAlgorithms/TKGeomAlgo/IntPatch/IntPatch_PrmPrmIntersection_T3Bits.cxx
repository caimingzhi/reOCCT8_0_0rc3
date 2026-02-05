#include <IntPatch_PrmPrmIntersection_T3Bits.hpp>

IntPatch_PrmPrmIntersection_T3Bits::IntPatch_PrmPrmIntersection_T3Bits(const int size)
{
  //-- ex: size=4  -> 4**3 = 64 bits -> 2 mots 32bits
  int nb = (size * size * size) >> 5;
  Isize  = nb;
  p      = new int[nb];
  do
  {
    p[--nb] = 0;
  } while (nb);
}

IntPatch_PrmPrmIntersection_T3Bits::~IntPatch_PrmPrmIntersection_T3Bits()
{
  if (p)
  {
    delete[] p;
    p = nullptr;
  }
}

void IntPatch_PrmPrmIntersection_T3Bits::ResetAnd()
{
  // ind = 0;
}

int IntPatch_PrmPrmIntersection_T3Bits::And(IntPatch_PrmPrmIntersection_T3Bits& Oth, int& indice)
{
  int k = indice >> 5;
  while (k < Isize)
  {
    int r = p[k] & Oth.p[k];
    if (r)
    {
      unsigned int c = 0;
      do
      {
        if (r & 1)
        {
          const int op = (k << 5) | (c);
          Raz(op);
          Oth.Raz(op);
          indice = op;
          return (1);
        }
        c++;
        r >>= 1;
      } while (c < 32);
    }
    k++;
  }
  return (0);
}
