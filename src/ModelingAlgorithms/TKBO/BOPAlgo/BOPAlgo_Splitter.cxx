#include <BOPAlgo_Splitter.hpp>
#include <BOPAlgo_PaveFiller.hpp>
#include <BOPAlgo_Alerts.hpp>

#include <TopoDS_Iterator.hpp>

BOPAlgo_Splitter::BOPAlgo_Splitter()

  = default;

BOPAlgo_Splitter::BOPAlgo_Splitter(const occ::handle<NCollection_BaseAllocator>& theAllocator)
    : BOPAlgo_ToolsProvider(theAllocator)
{
}

BOPAlgo_Splitter::~BOPAlgo_Splitter() = default;

void BOPAlgo_Splitter::CheckData()
{
  if (myArguments.IsEmpty() || (myArguments.Extent() + myTools.Extent()) < 2)
  {

    AddError(new BOPAlgo_AlertTooFewArguments);
    return;
  }

  CheckFiller();
}

void BOPAlgo_Splitter::Perform(const Message_ProgressRange& theRange)
{
  GetReport()->Clear();

  if (myEntryPoint == 1)
  {
    if (myPaveFiller)
    {
      delete myPaveFiller;
      myPaveFiller = nullptr;
    }
  }

  NCollection_List<TopoDS_Shape> aLS;

  NCollection_List<TopoDS_Shape>::Iterator aItLS(myArguments);
  for (; aItLS.More(); aItLS.Next())
  {
    aLS.Append(aItLS.Value());
  }

  aItLS.Initialize(myTools);
  for (; aItLS.More(); aItLS.Next())
  {
    aLS.Append(aItLS.Value());
  }

  BOPAlgo_PaveFiller* pPF = new BOPAlgo_PaveFiller();
  pPF->SetArguments(aLS);
  pPF->SetRunParallel(myRunParallel);

  pPF->SetFuzzyValue(myFuzzyValue);
  pPF->SetNonDestructive(myNonDestructive);
  pPF->SetGlue(myGlue);
  pPF->SetUseOBB(myUseOBB);

  Message_ProgressScope aPS(theRange, "Performing Split operation", 10);
  pPF->Perform(aPS.Next(9));

  myEntryPoint = 1;
  PerformInternal(*pPF, aPS.Next(1));
}

void BOPAlgo_Splitter::BuildResult(const TopAbs_ShapeEnum theType)
{
  BOPAlgo_Builder::BuildResult(theType);

  if (theType == TopAbs_COMPOUND)
  {

    if (myArguments.Extent() == 1)
    {
      TopoDS_Iterator it(myShape);
      if (it.More())
      {
        const TopoDS_Shape& aSFirst = it.Value();
        it.Next();
        if (!it.More())
          myShape = aSFirst;
      }
    }
  }
}
