inline double TopClass_Classifier2d::Parameter() const
{
  return myParam;
}

inline TheIntersector& TopClass_Classifier2d::Intersector()
{
  return myIntersector;
}

inline int TopClass_Classifier2d::ClosestIntersection() const
{
  return myClosest;
}

inline TopAbs_State TopClass_Classifier2d::State() const
{
  return myState;
}

inline bool TopClass_Classifier2d::IsHeadOrEnd() const
{
  return myIsHeadOrEnd;
}
