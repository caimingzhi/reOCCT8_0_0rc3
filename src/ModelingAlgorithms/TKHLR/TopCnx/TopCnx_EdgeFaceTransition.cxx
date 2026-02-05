#include <TopCnx_EdgeFaceTransition.hpp>

//=================================================================================================

TopCnx_EdgeFaceTransition::TopCnx_EdgeFaceTransition()
    : nbBoundForward(0),
      nbBoundReversed(0)
{
}

//=================================================================================================

void TopCnx_EdgeFaceTransition::Reset(const gp_Dir& Tgt, const gp_Dir& Norm, const double Curv)
{
  myCurveTransition.Reset(Tgt, Norm, Curv);
  nbBoundForward = nbBoundReversed = 0;
}

//=================================================================================================

void TopCnx_EdgeFaceTransition::Reset(const gp_Dir& Tgt)
{
  myCurveTransition.Reset(Tgt);
  nbBoundForward = nbBoundReversed = 0;
}

//=================================================================================================

void TopCnx_EdgeFaceTransition::AddInterference(const double             Tole,
                                                const gp_Dir&            Tang,
                                                const gp_Dir&            Norm,
                                                const double             Curv,
                                                const TopAbs_Orientation Or,
                                                const TopAbs_Orientation Tr,
                                                const TopAbs_Orientation BTr)
{
  myCurveTransition.Compare(Tole, Tang, Norm, Curv, Tr, Or);
  switch (BTr)
  {

    case TopAbs_FORWARD:
      nbBoundForward++;
      break;

    case TopAbs_REVERSED:
      nbBoundReversed++;
      break;

    case TopAbs_INTERNAL:
    case TopAbs_EXTERNAL:
      break;
  }
}

//=================================================================================================

TopAbs_Orientation TopCnx_EdgeFaceTransition::Transition() const
{
  TopAbs_State Bef = myCurveTransition.StateBefore();
  TopAbs_State Aft = myCurveTransition.StateAfter();
  if (Bef == TopAbs_IN)
  {
    if (Aft == TopAbs_IN)
      return TopAbs_INTERNAL;
    else if (Aft == TopAbs_OUT)
      return TopAbs_REVERSED;
#ifdef OCCT_DEBUG
    else
      std::cout << "\n*** Complex Transition : unprocessed state" << std::endl;
#endif
  }
  else if (Bef == TopAbs_OUT)
  {
    if (Aft == TopAbs_IN)
      return TopAbs_FORWARD;
    else if (Aft == TopAbs_OUT)
      return TopAbs_EXTERNAL;
#ifdef OCCT_DEBUG
    else
      std::cout << "\n*** Complex Transition : unprocessed state" << std::endl;
#endif
  }
#ifdef OCCT_DEBUG
  else
    std::cout << "\n*** Complex Transition : unprocessed state" << std::endl;
#endif
  return TopAbs_INTERNAL;
}

//=================================================================================================

TopAbs_Orientation TopCnx_EdgeFaceTransition::BoundaryTransition() const
{
  if (nbBoundForward > nbBoundReversed)
    return TopAbs_FORWARD;
  else if (nbBoundForward < nbBoundReversed)
    return TopAbs_REVERSED;
  else if ((nbBoundReversed % 2) == 0)
    return TopAbs_EXTERNAL;
  else
    return TopAbs_EXTERNAL;
}
