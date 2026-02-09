#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class MAT_Bisector;
class MAT_ListOfBisector;

class MAT_TListNodeOfListOfBisector : public Standard_Transient
{

public:
  MAT_TListNodeOfListOfBisector();

  MAT_TListNodeOfListOfBisector(const occ::handle<MAT_Bisector>& anitem);

  occ::handle<MAT_Bisector> GetItem() const;

  occ::handle<MAT_TListNodeOfListOfBisector> Next() const;

  occ::handle<MAT_TListNodeOfListOfBisector> Previous() const;

  void SetItem(const occ::handle<MAT_Bisector>& anitem);

  void Next(const occ::handle<MAT_TListNodeOfListOfBisector>& atlistnode);

  void Previous(const occ::handle<MAT_TListNodeOfListOfBisector>& atlistnode);

  Standard_EXPORT void Dummy() const;

  DEFINE_STANDARD_RTTI_INLINE(MAT_TListNodeOfListOfBisector, Standard_Transient)

private:
  occ::handle<MAT_TListNodeOfListOfBisector> thenext;
  occ::handle<MAT_TListNodeOfListOfBisector> theprevious;
  occ::handle<MAT_Bisector>                  theitem;
};

inline MAT_TListNodeOfListOfBisector::MAT_TListNodeOfListOfBisector() = default;

inline MAT_TListNodeOfListOfBisector::MAT_TListNodeOfListOfBisector(
  const occ::handle<MAT_Bisector>& anitem)
{
  theitem = anitem;
}

inline occ::handle<MAT_Bisector> MAT_TListNodeOfListOfBisector::GetItem() const
{
  return theitem;
}

inline occ::handle<MAT_TListNodeOfListOfBisector> MAT_TListNodeOfListOfBisector::Next() const
{
  return thenext;
}

inline occ::handle<MAT_TListNodeOfListOfBisector> MAT_TListNodeOfListOfBisector::Previous() const
{
  return theprevious;
}

inline void MAT_TListNodeOfListOfBisector::SetItem(const occ::handle<MAT_Bisector>& anitem)
{
  theitem = anitem;
}

inline void MAT_TListNodeOfListOfBisector::Next(
  const occ::handle<MAT_TListNodeOfListOfBisector>& atlistnode)
{
  thenext = atlistnode;
}

inline void MAT_TListNodeOfListOfBisector::Previous(
  const occ::handle<MAT_TListNodeOfListOfBisector>& atlistnode)
{
  theprevious = atlistnode;
}
