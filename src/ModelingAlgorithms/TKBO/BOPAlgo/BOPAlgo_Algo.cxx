#include <BOPAlgo_Algo.hpp>

#include <Standard_Integer.hpp>
#include <NCollection_Map.hpp>

//=================================================================================================

BOPAlgo_Algo::BOPAlgo_Algo()
    : BOPAlgo_Options(NCollection_BaseAllocator::CommonBaseAllocator())
{
}

//=================================================================================================

BOPAlgo_Algo::BOPAlgo_Algo(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : BOPAlgo_Options(theAllocator)
{
}

//=================================================================================================

BOPAlgo_Algo::~BOPAlgo_Algo() = default;

//=================================================================================================

void BOPAlgo_Algo::CheckData()
{
  GetReport()->Clear(Message_Fail);
}

//=================================================================================================

void BOPAlgo_Algo::CheckResult()
{
  GetReport()->Clear(Message_Fail);
}

//=================================================================================================

void BOPAlgo_Algo::analyzeProgress(const double theWhole, BOPAlgo_PISteps& theSteps) const
{
  double aWhole = theWhole;

  // Fill progress steps for constant operations
  fillPIConstants(theWhole, theSteps);

  NCollection_Array1<double>& aSteps = theSteps.ChangeSteps();
  NCollection_Map<int>        aMIConst;
  for (int i = aSteps.Lower(); i <= aSteps.Upper(); ++i)
  {
    if (aSteps(i) > 0.)
    {
      aMIConst.Add(i);
      aWhole -= aSteps(i);
    }
  }

  // Fill progress steps for other operations
  fillPISteps(theSteps);

  double aSum = 0.;
  for (int i = aSteps.Lower(); i <= aSteps.Upper(); ++i)
  {
    if (!aMIConst.Contains(i))
    {
      aSum += aSteps(i);
    }
  }

  // Normalize steps
  if (aSum > 0.)
  {
    for (int i = aSteps.Lower(); i <= aSteps.Upper(); ++i)
    {
      if (!aMIConst.Contains(i))
      {
        aSteps(i) = aWhole * aSteps(i) / aSum;
      }
    }
  }
}

//=================================================================================================

void BOPAlgo_Algo::fillPIConstants(const double, BOPAlgo_PISteps&) const {}

//=================================================================================================

void BOPAlgo_Algo::fillPISteps(BOPAlgo_PISteps&) const {}
