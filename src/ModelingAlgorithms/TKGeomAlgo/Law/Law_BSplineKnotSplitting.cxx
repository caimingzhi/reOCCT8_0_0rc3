#include <BSplCLib.hpp>
#include <Law_BSpline.hpp>
#include <Law_BSplineKnotSplitting.hpp>
#include <Standard_RangeError.hpp>

typedef NCollection_Array1<int>  Array1OfInteger;
typedef NCollection_HArray1<int> HArray1OfInteger;

Law_BSplineKnotSplitting::Law_BSplineKnotSplitting(const occ::handle<Law_BSpline>& BasisCurve,
                                                   const int                       ContinuityRange)
{
  if (ContinuityRange < 0)
    throw Standard_RangeError();

  int FirstIndex = BasisCurve->FirstUKnotIndex();
  int LastIndex  = BasisCurve->LastUKnotIndex();

  int Degree = BasisCurve->Degree();

  if (ContinuityRange == 0)
  {
    splitIndexes = new HArray1OfInteger(1, 2);
    splitIndexes->SetValue(1, FirstIndex);
    splitIndexes->SetValue(2, LastIndex);
  }
  else
  {
    int             NbKnots = BasisCurve->NbKnots();
    Array1OfInteger Mults(1, NbKnots);
    BasisCurve->Multiplicities(Mults);
    int Mmax = BSplCLib::MaxKnotMult(Mults, FirstIndex, LastIndex);
    if (Degree - Mmax >= ContinuityRange)
    {
      splitIndexes = new HArray1OfInteger(1, 2);
      splitIndexes->SetValue(1, FirstIndex);
      splitIndexes->SetValue(2, LastIndex);
    }
    else
    {
      Array1OfInteger Split(1, LastIndex - FirstIndex + 1);
      int             NbSplit = 1;
      int             Index   = FirstIndex;
      Split(NbSplit)          = Index;
      Index++;
      NbSplit++;
      while (Index < LastIndex)
      {
        if (Degree - Mults(Index) < ContinuityRange)
        {
          Split(NbSplit) = Index;
          NbSplit++;
        }
        Index++;
      }
      Split(NbSplit) = Index;
      splitIndexes   = new HArray1OfInteger(1, NbSplit);
      for (int i = 1; i <= NbSplit; i++)
      {
        splitIndexes->SetValue(i, Split(i));
      }
    }
  }
}

int Law_BSplineKnotSplitting::NbSplits() const
{

  return splitIndexes->Length();
}

int Law_BSplineKnotSplitting::SplitValue(

  const int Index

) const
{

  Standard_RangeError_Raise_if(Index < 1 || Index > splitIndexes->Length(), " ");
  return splitIndexes->Value(Index);
}

void Law_BSplineKnotSplitting::Splitting(

  Array1OfInteger& SplitValues

) const
{

  for (int i = 1; i <= splitIndexes->Length(); i++)
  {
    SplitValues(i) = splitIndexes->Value(i);
  }
}
