#pragma once

#include <Graphic3d_ClipPlane.hpp>

class Graphic3d_SequenceOfHClipPlane : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_SequenceOfHClipPlane, Standard_Transient)
public:
  class Iterator : public NCollection_Sequence<occ::handle<Graphic3d_ClipPlane>>::Iterator
  {
  public:
    Iterator() = default;

    Iterator(const Graphic3d_SequenceOfHClipPlane& thePlanes)
        : NCollection_Sequence<occ::handle<Graphic3d_ClipPlane>>::Iterator(thePlanes.myItems)
    {
    }

    Iterator(const occ::handle<Graphic3d_SequenceOfHClipPlane>& thePlanes) { Init(thePlanes); }

    void Init(const Graphic3d_SequenceOfHClipPlane& thePlanes)
    {
      NCollection_Sequence<occ::handle<Graphic3d_ClipPlane>>::Iterator::Init(thePlanes.myItems);
    }

    void Init(const occ::handle<Graphic3d_SequenceOfHClipPlane>& thePlanes)
    {
      if (!thePlanes.IsNull())
      {
        NCollection_Sequence<occ::handle<Graphic3d_ClipPlane>>::Iterator::Init(thePlanes->myItems);
      }
      else
      {
        *this = Iterator();
      }
    }
  };

public:
  Standard_EXPORT Graphic3d_SequenceOfHClipPlane();

  bool ToOverrideGlobal() const { return myToOverrideGlobal; }

  void SetOverrideGlobal(const bool theToOverride) { myToOverrideGlobal = theToOverride; }

  bool IsEmpty() const { return myItems.IsEmpty(); }

  int Size() const { return myItems.Size(); }

  Standard_EXPORT bool Append(const occ::handle<Graphic3d_ClipPlane>& theItem);

  Standard_EXPORT bool Remove(const occ::handle<Graphic3d_ClipPlane>& theItem);

  void Remove(Iterator& theItem) { myItems.Remove(theItem); }

  void Clear() { myItems.Clear(); }

  const occ::handle<Graphic3d_ClipPlane>& First() const { return myItems.First(); }

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  NCollection_Sequence<occ::handle<Graphic3d_ClipPlane>> myItems;
  bool                                                   myToOverrideGlobal;
};
