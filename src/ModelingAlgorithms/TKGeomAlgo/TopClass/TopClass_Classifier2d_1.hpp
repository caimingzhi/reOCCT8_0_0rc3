inline double TopClass_Classifier2d::Parameter() const
{
  return myParam;
}

//=================================================================================================

inline TheIntersector& TopClass_Classifier2d::Intersector()
{
  return myIntersector;
}

//=================================================================================================

inline int TopClass_Classifier2d::ClosestIntersection() const
{
  return myClosest;
}

//=================================================================================================

inline TopAbs_State TopClass_Classifier2d::State() const
{
  return myState;
}

//  Modified by skv - Wed Jul 12 15:20:58 2006 OCC12627 Begin

//=================================================================================================

inline bool TopClass_Classifier2d::IsHeadOrEnd() const
{
  return myIsHeadOrEnd;
}

//  Modified by skv - Wed Jul 12 15:20:58 2006 OCC12627 End
