#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class MAT_Edge;
class MAT_ListOfEdge;

class MAT_TListNodeOfListOfEdge : public Standard_Transient
{

public:
  MAT_TListNodeOfListOfEdge();

  MAT_TListNodeOfListOfEdge(const occ::handle<MAT_Edge>& anitem);

  occ::handle<MAT_Edge> GetItem() const;

  occ::handle<MAT_TListNodeOfListOfEdge> Next() const;

  occ::handle<MAT_TListNodeOfListOfEdge> Previous() const;

  void SetItem(const occ::handle<MAT_Edge>& anitem);

  void Next(const occ::handle<MAT_TListNodeOfListOfEdge>& atlistnode);

  void Previous(const occ::handle<MAT_TListNodeOfListOfEdge>& atlistnode);

  Standard_EXPORT void Dummy() const;

  DEFINE_STANDARD_RTTI_INLINE(MAT_TListNodeOfListOfEdge, Standard_Transient)

private:
  occ::handle<MAT_TListNodeOfListOfEdge> thenext;
  occ::handle<MAT_TListNodeOfListOfEdge> theprevious;
  occ::handle<MAT_Edge>                  theitem;
};

//=================================================================================================
// Inline implementations
//=================================================================================================

inline MAT_TListNodeOfListOfEdge::MAT_TListNodeOfListOfEdge() = default;

//=================================================================================================

inline MAT_TListNodeOfListOfEdge::MAT_TListNodeOfListOfEdge(const occ::handle<MAT_Edge>& anitem)
{
  theitem = anitem;
}

//=================================================================================================

inline occ::handle<MAT_Edge> MAT_TListNodeOfListOfEdge::GetItem() const
{
  return theitem;
}

//=================================================================================================

inline occ::handle<MAT_TListNodeOfListOfEdge> MAT_TListNodeOfListOfEdge::Next() const
{
  return thenext;
}

//=================================================================================================

inline occ::handle<MAT_TListNodeOfListOfEdge> MAT_TListNodeOfListOfEdge::Previous() const
{
  return theprevious;
}

//=================================================================================================

inline void MAT_TListNodeOfListOfEdge::SetItem(const occ::handle<MAT_Edge>& anitem)
{
  theitem = anitem;
}

//=================================================================================================

inline void MAT_TListNodeOfListOfEdge::Next(
  const occ::handle<MAT_TListNodeOfListOfEdge>& atlistnode)
{
  thenext = atlistnode;
}

//=================================================================================================

inline void MAT_TListNodeOfListOfEdge::Previous(
  const occ::handle<MAT_TListNodeOfListOfEdge>& atlistnode)
{
  theprevious = atlistnode;
}
