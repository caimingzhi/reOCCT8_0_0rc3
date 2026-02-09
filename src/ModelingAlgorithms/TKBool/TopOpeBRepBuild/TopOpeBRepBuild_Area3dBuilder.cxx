#include <TopOpeBRepBuild_Area3dBuilder.hpp>
#include <TopOpeBRepBuild_Loop.hpp>
#include <TopOpeBRepBuild_LoopClassifier.hpp>
#include <TopOpeBRepBuild_LoopSet.hpp>

TopOpeBRepBuild_Area3dBuilder::TopOpeBRepBuild_Area3dBuilder() = default;

TopOpeBRepBuild_Area3dBuilder::TopOpeBRepBuild_Area3dBuilder(TopOpeBRepBuild_LoopSet&        LS,
                                                             TopOpeBRepBuild_LoopClassifier& LC,
                                                             const bool ForceClass)
{
  InitAreaBuilder(LS, LC, ForceClass);
}

void TopOpeBRepBuild_Area3dBuilder::InitAreaBuilder(TopOpeBRepBuild_LoopSet&        LS,
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
        NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& aArea = AreaIter.ChangeValue();
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
        NCollection_List<occ::handle<TopOpeBRepBuild_Loop>>& aArea = AreaIter.ChangeValue();
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
          const occ::handle<TopOpeBRepBuild_Loop>& LLI1 = LoopIter.Value();
          state                                         = LC.Compare(LLI1, L);
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
          ashapeinside = ablockinside                   = false;
          const occ::handle<TopOpeBRepBuild_Loop>& LLI2 = LoopIter.Value();
          state                                         = LC.Compare(LLI2, L);
          if (state == TopAbs_UNKNOWN)
            Atomize(state, TopAbs_IN);
          ashapeinside = (state == TopAbs_IN);
          if (ashapeinside)
          {
            const occ::handle<TopOpeBRepBuild_Loop>& LLI3 = LoopIter.Value();
            state                                         = LC.Compare(L, LLI3);
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
