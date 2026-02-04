#include TheFaceExplorer_hxx

//=================================================================================================

inline bool TopClass_FaceClassifier::Rejected() const
{
  return rejected;
}

//=================================================================================================

inline bool TopClass_FaceClassifier::NoWires() const
{
  return nowires;
}

//=================================================================================================

inline IntRes2d_Position TopClass_FaceClassifier::Position() const
{
  return myPosition;
}
