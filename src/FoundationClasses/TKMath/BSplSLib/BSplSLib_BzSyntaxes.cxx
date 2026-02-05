#define No_Standard_RangeError
#define No_Standard_OutOfRange

#include <BSplSLib.hpp>
#include <BSplCLib.hpp>
#include <NCollection_Array1.hpp>

//=================================================================================================

void BSplSLib::PolesCoefficients(const NCollection_Array2<gp_Pnt>& Poles,
                                 const NCollection_Array2<double>* Weights,
                                 NCollection_Array2<gp_Pnt>&       CachePoles,
                                 NCollection_Array2<double>*       CacheWeights)
{
  int                        i;
  int                        uclas = Poles.ColLength();
  int                        vclas = Poles.RowLength();
  NCollection_Array1<double> biduflatknots(1, uclas << 1);
  NCollection_Array1<double> bidvflatknots(1, vclas << 1);

  for (i = 1; i <= uclas; i++)
  {
    biduflatknots(i)         = 0.;
    biduflatknots(i + uclas) = 1.;
  }

  for (i = 1; i <= vclas; i++)
  {
    bidvflatknots(i)         = 0.;
    bidvflatknots(i + vclas) = 1.;
  }
  if (uclas > vclas)
  {
    BSplSLib::BuildCache(0.,
                         0.,
                         1.,
                         1.,
                         false,
                         false,
                         uclas - 1,
                         vclas - 1,
                         0,
                         0,
                         biduflatknots,
                         bidvflatknots,
                         Poles,
                         Weights,
                         CachePoles,
                         CacheWeights);
  }
  else
  {
    // BuilCache exige que les resultats soient formates en [MaxCoeff,MinCoeff]
    NCollection_Array2<gp_Pnt> CPoles(1, vclas, 1, uclas);
    NCollection_Array2<double> CWeights(1, vclas, 1, uclas);
    int                        ii, jj;
    BSplSLib::BuildCache(0.,
                         0.,
                         1.,
                         1.,
                         false,
                         false,
                         uclas - 1,
                         vclas - 1,
                         0,
                         0,
                         biduflatknots,
                         bidvflatknots,
                         Poles,
                         Weights,
                         CPoles,
                         &CWeights);
    if (Weights == nullptr)
    {

      for (ii = 1; ii <= uclas; ii++)
      {

        for (jj = 1; jj <= vclas; jj++)
        {
          CachePoles(ii, jj) = CPoles(jj, ii);
        }
      }
    }
    else
    {

      for (ii = 1; ii <= uclas; ii++)
      {

        for (jj = 1; jj <= vclas; jj++)
        {
          CachePoles(ii, jj)      = CPoles(jj, ii);
          (*CacheWeights)(ii, jj) = CWeights(jj, ii);
        }
      }
    }
  }
}
