inline int MAT_TList::Number() const
{
  return thenumberofitems;
}

//=================================================================================================

inline int MAT_TList::Index() const
{
  return thecurrentindex;
}

//=================================================================================================

inline bool MAT_TList::IsEmpty() const
{
  return thenumberofitems == 0;
}
