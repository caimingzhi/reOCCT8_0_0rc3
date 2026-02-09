#include <TopOpeBRepBuild_AreaBuilder.hpp>
#include <TopOpeBRepBuild_Loop.hpp>
#include <TopOpeBRepBuild_LoopClassifier.hpp>
#include <TopOpeBRepBuild_LoopSet.hpp>

TopOpeBRepBuild_AreaBuilder::TopOpeBRepBuild_AreaBuilder()
    : myUNKNOWNRaise(false)
{
}

TopOpeBRepBuild_AreaBuilder::TopOpeBRepBuild_AreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                                         TopOpeBRepBuild_LoopClassifier& LC,
                                                         const bool                      ForceClass)
    : myUNKNOWNRaise(false)
{
  InitAreaBuilder(LS, LC, ForceClass);
}

TopOpeBRepBuild_AreaBuilder::~TopOpeBRepBuild_AreaBuilder() = default;

TopAbs_State TopOpeBRepBuild_AreaBuilder::CompareLoopWithListOfLoop(
  TopOpeBRepBuild_LoopClassifier&                            LC,
  const occ::handle<TopOpeBRepBuild_Loop>&                   L,
  const NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& LOL,
  const TopOpeBRepBuild_LoopEnum                             what) const
{
  TopAbs_State                                                  state = TopAbs_UNKNOWN;
  bool                                                          totest;
  NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>::Iterator LoopIter;

  if (LOL.IsEmpty())
    return TopAbs_OUT;

  for (LoopIter.Initialize(LOL); LoopIter.More(); LoopIter.Next())
  {
    const occ::handle<TopOpeBRepBuild_Loop>& curL = LoopIter.Value();
    switch (what)
    {
      case TopOpeBRepBuild_ANYLOOP:
        totest = true;
        break;
      case TopOpeBRepBuild_BOUNDARY:
        totest = curL->IsShape();
        break;
      case TopOpeBRepBuild_BLOCK:
        totest = !curL->IsShape();
        break;
      default:
        totest = false;
    }
    if (totest)
    {
      state = LC.Compare(L, curL);
      if (state == TopAbs_OUT)

        break;
    }
  }

  return state;
}

void TopOpeBRepBuild_AreaBuilder::Atomize(TopAbs_State& state, const TopAbs_State newstate) const
{
  if (myUNKNOWNRaise)
  {
    Standard_DomainError_Raise_if((state == TopAbs_UNKNOWN), "AreaBuilder : Position Unknown");
  }
  else
  {
    state = newstate;
  }
}

void TopOpeBRepBuild_AreaBuilder::InitAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                                  TopOpeBRepBuild_LoopClassifier& LC,
                                                  const bool                      ForceClass)
{
  TopAbs_State state;
  bool         Loopinside;
  bool         loopoutside;

  NCollection_List<NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>>::Iterator AreaIter;
  NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>::Iterator                   LoopIter;

  NCollection_List<occ::handle<TopOpeBRepBuild_Loop>> boundaryloops;

  myArea.Clear();

  for (LS.InitLoop(); LS.MoreLoop(); LS.NextLoop())
  {

    const occ::handle<TopOpeBRepBuild_Loop>& L         = LS.Loop();
    bool                                     boundaryL = L->IsShape();

    bool traitercommeblock = (!boundaryL) || ForceClass;
    if (!traitercommeblock)
    {

      Loopinside = false;
      for (AreaIter.Initialize(myArea); AreaIter.More(); AreaIter.Next())
      {
        const NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& aArea = AreaIter.Value();
        if (aArea.IsEmpty())
          continue;
        state = CompareLoopWithListOfLoop(LC, L, aArea, TopOpeBRepBuild_BLOCK);
        if (state == TopAbs_UNKNOWN)
          Atomize(state, TopAbs_IN);
        Loopinside = (state == TopAbs_IN);
        if (Loopinside)
          break;
      }

      if (Loopinside)
      {
        NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& aArea = AreaIter.ChangeValue();
        ADD_Loop_TO_LISTOFLoop(L, aArea, (void*)("IN, to current area"));
      }
      else if (!Loopinside)
      {
        ADD_Loop_TO_LISTOFLoop(L, boundaryloops, (void*)("! IN, to boundaryloops"));
      }
    }

    else
    {

      Loopinside = false;
      for (AreaIter.Initialize(myArea); AreaIter.More(); AreaIter.Next())
      {
        const NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& aArea = AreaIter.Value();
        if (aArea.IsEmpty())
          continue;
        state = CompareLoopWithListOfLoop(LC, L, aArea, TopOpeBRepBuild_ANYLOOP);
        if (state == TopAbs_UNKNOWN)
          Atomize(state, TopAbs_IN);
        Loopinside = (state == TopAbs_IN);
        if (Loopinside)
          break;
      }

      if (Loopinside)
      {
        NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& aArea    = AreaIter.ChangeValue();
        bool                                                 allShape = true;
        NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>  removedLoops;
        LoopIter.Initialize(aArea);
        while (LoopIter.More())
        {
          state = LC.Compare(LoopIter.Value(), L);
          if (state == TopAbs_UNKNOWN)
            Atomize(state, TopAbs_IN);
          loopoutside = (state == TopAbs_OUT);
          if (loopoutside)
          {
            const occ::handle<TopOpeBRepBuild_Loop>& curL = LoopIter.Value();

            ADD_Loop_TO_LISTOFLoop(curL,
                                   removedLoops,
                                   (void*)("loopoutside = 1, area = removedLoops"));

            allShape = allShape && curL->IsShape();
            REM_Loop_FROM_LISTOFLoop(LoopIter,
                                     AreaIter.ChangeValue(),
                                     (void*)("loop of cur. area, cur. area"));
          }
          else
          {
            LoopIter.Next();
          }
        }

        ADD_Loop_TO_LISTOFLoop(L, aArea, (void*)("area = current"));
        if (!removedLoops.IsEmpty())
        {
          if (allShape)
          {
            ADD_LISTOFLoop_TO_LISTOFLoop(removedLoops,
                                         boundaryloops,
                                         (void*)("allShape = 1"),
                                         (void*)("removedLoops"),
                                         (void*)("boundaryloops"));
          }
          else
          {

            NCollection_List<occ::handle<TopOpeBRepBuild_Loop>> thelist;
            myArea.Append(thelist);
            ADD_LISTOFLoop_TO_LISTOFLoop(removedLoops,
                                         myArea.Last(),
                                         (void*)("allShape = 0"),
                                         (void*)("removedLoops"),
                                         (void*)("new area"));
          }
        }
      }

      else
      {
        int                                                 ashapeinside, ablockinside;
        NCollection_List<occ::handle<TopOpeBRepBuild_Loop>> thelist1;
        myArea.Append(thelist1);
        NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& newArea0 = myArea.Last();
        ADD_Loop_TO_LISTOFLoop(L, newArea0, (void*)("new area"));

        LoopIter.Initialize(boundaryloops);
        while (LoopIter.More())
        {
          ashapeinside = ablockinside = false;
          state                       = LC.Compare(LoopIter.Value(), L);
          if (state == TopAbs_UNKNOWN)
            Atomize(state, TopAbs_IN);
          ashapeinside = (state == TopAbs_IN);
          if (ashapeinside)
          {
            state = LC.Compare(L, LoopIter.Value());
            if (state == TopAbs_UNKNOWN)
              Atomize(state, TopAbs_IN);
            ablockinside = (state == TopAbs_IN);
          }
          if (ashapeinside && ablockinside)
          {
            const occ::handle<TopOpeBRepBuild_Loop>& curL = LoopIter.Value();
            ADD_Loop_TO_LISTOFLoop(curL,
                                   newArea0,
                                   (void*)("ashapeinside && ablockinside, new area"));

            REM_Loop_FROM_LISTOFLoop(LoopIter,
                                     boundaryloops,
                                     (void*)("loop of boundaryloops, boundaryloops"));
          }
          else
          {
            LoopIter.Next();
          }
        }
      }
    }
  }

  InitArea();
}

int TopOpeBRepBuild_AreaBuilder::InitArea()
{
  myAreaIterator.Initialize(myArea);
  InitLoop();
  int n = myArea.Extent();
  return n;
}

bool TopOpeBRepBuild_AreaBuilder::MoreArea() const
{
  bool b = myAreaIterator.More();
  return b;
}

void TopOpeBRepBuild_AreaBuilder::NextArea()
{
  myAreaIterator.Next();
  InitLoop();
}

int TopOpeBRepBuild_AreaBuilder::InitLoop()
{
  int n = 0;
  if (myAreaIterator.More())
  {
    const NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& LAL = myAreaIterator.Value();
    myLoopIterator.Initialize(LAL);
    n = LAL.Extent();
  }
  else
  {
    myLoopIterator = NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>::Iterator();
  }
  return n;
}

bool TopOpeBRepBuild_AreaBuilder::MoreLoop() const
{
  bool b = myLoopIterator.More();
  return b;
}

void TopOpeBRepBuild_AreaBuilder::NextLoop()
{
  myLoopIterator.Next();
}

const occ::handle<TopOpeBRepBuild_Loop>& TopOpeBRepBuild_AreaBuilder::Loop() const
{
  const occ::handle<TopOpeBRepBuild_Loop>& L = myLoopIterator.Value();
  return L;
}

void TopOpeBRepBuild_AreaBuilder::ADD_Loop_TO_LISTOFLoop(
  const occ::handle<TopOpeBRepBuild_Loop>&             L,
  NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& LOL,
  void* const) const
{
  LOL.Append(L);
}

void TopOpeBRepBuild_AreaBuilder::REM_Loop_FROM_LISTOFLoop(
  NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>::Iterator& ITA,
  NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>&           A,
  void* const) const
{
  A.Remove(ITA);
}

void TopOpeBRepBuild_AreaBuilder::ADD_LISTOFLoop_TO_LISTOFLoop(
  NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& A1,
  NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& A2,
  void* const,
  void* const,
  void* const) const
{
  A2.Append(A1);
}
