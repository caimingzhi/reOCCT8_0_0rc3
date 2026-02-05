#ifndef No_Exception
  #define No_Exception
#endif

#include <HLRBRep_EdgeIList.hpp>
#include <HLRBRep_EdgeInterferenceTool.hpp>
#include <TopCnx_EdgeFaceTransition.hpp>

//=======================================================================
// function : AddInterference
// purpose  : insert an interference in a sorted list
//=======================================================================
void HLRBRep_EdgeIList::AddInterference(NCollection_List<HLRAlgo_Interference>& IL,
                                        const HLRAlgo_Interference&             I,
                                        const HLRBRep_EdgeInterferenceTool&     T)
{
  NCollection_List<HLRAlgo_Interference>::Iterator It(IL);
  double                                           p = T.ParameterOfInterference(I);
  while (It.More())
  {
    if (p < T.ParameterOfInterference(It.Value()))
    {
      IL.InsertBefore(I, It);
      return;
    }
    It.Next();
  }
  IL.Append(I);
}

//=================================================================================================

#ifdef OCCT_DEBUG_SI
static bool SimilarInterference(const HLRAlgo_Interference& I1, const HLRAlgo_Interference& I2)
{
  double             p1, p2;
  double             eps = 1.e-7;
  TopAbs_Orientation or1, or2;
  // int l1, l2; //levels

  p1 = I1.Intersection().Parameter();
  // l1 = I1.Intersection().Level();
  or1 = I1.Transition();

  p2 = I2.Intersection().Parameter();
  // l2 = I2.Intersection().Level();
  or2 = I2.Transition();

  bool IsSimilar = std::abs(p1 - p2) <= eps && or1 == or2;
  return IsSimilar;
}
#endif
void HLRBRep_EdgeIList::ProcessComplex(NCollection_List<HLRAlgo_Interference>& IL,
                                       const HLRBRep_EdgeInterferenceTool&     T)
{
  TopCnx_EdgeFaceTransition                        transTool;
  gp_Dir                                           TgtE, NormE, TgtI, NormI;
  const double                                     TolAng = 0.0001;
  double                                           CurvE, CurvI;
  NCollection_List<HLRAlgo_Interference>::Iterator It1(IL);

  while (It1.More())
  {
    NCollection_List<HLRAlgo_Interference>::Iterator It2(It1);
    It2.Next();
    if (It2.More())
    {
      if (T.SameInterferences(It1.Value(), It2.Value())
#ifdef OCCT_DEBUG_SI
          || SimilarInterference(It1.Value(), It2.Value())
#endif
      )
      {
        T.EdgeGeometry(T.ParameterOfInterference(It1.Value()), TgtE, NormE, CurvE);
        transTool.Reset(TgtE, NormE, CurvE);
        T.InterferenceBoundaryGeometry(It1.Value(), TgtI, NormI, CurvI);
        transTool.AddInterference(TolAng,
                                  TgtI,
                                  NormI,
                                  CurvI,
                                  It1.Value().Orientation(),
                                  It1.Value().Transition(),
                                  It1.Value().BoundaryTransition());

        while (It2.More())
        {
          if (!(T.SameInterferences(It1.Value(), It2.Value())
#ifdef OCCT_DEBUG_SI
                || SimilarInterference(It1.Value(), It2.Value())
#endif
                  ))
            break;

          T.InterferenceBoundaryGeometry(It2.Value(), TgtI, NormI, CurvI);
          transTool.AddInterference(TolAng,
                                    TgtI,
                                    NormI,
                                    CurvI,
                                    It2.Value().Orientation(),
                                    It2.Value().Transition(),
                                    It2.Value().BoundaryTransition());
          IL.Remove(It2);
        }
        // get the cumulated results
        It1.ChangeValue().Transition(transTool.Transition());
        It1.ChangeValue().BoundaryTransition(transTool.BoundaryTransition());
      }
    }
    It1.Next();
  }

  /*
    //Removing "coinciding" interference

    double p1, p2;
    double eps = 1.e-7;
    NCollection_List<HLRAlgo_Interference> ILNew;
    HLRAlgo_Interference I1, I2;
    TopAbs_Orientation or1, or2;
    int l1, l2; //levels
    It1.Initialize(IL);

    if(It1.More()) {
      I1 = It1.Value();
      p1 = I1.Intersection().Parameter();
      l1 = I1.Intersection().Level();
      or1 = I1.Transition();

      ILNew.Append(I1);
      NCollection_List<HLRAlgo_Interference>::Iterator It2(ILNew);

      It1.Next();

      while(It1.More()) {
        I2 = It1.Value();
        p2 = I2.Intersection().Parameter();
        l2 = I2.Intersection().Level();
        or2 = I2.Transition();

        if(p2 - p1 <= eps && or1 == or2) {
      ILNew.Remove(It2);
      if(l2 < l1) {
        ILNew.Append(I2);
      }
      else {
        ILNew.Append(I1);
      }
        }
        else {
      ILNew.Append(I2);
        }
        It1.Next();
        if(It2.More()) It2.Next();
        p1 = p2;
        l1 = l2;
        or1 = or2;
        I1 = I2;
      }

      IL = ILNew;

    }
  */
}
