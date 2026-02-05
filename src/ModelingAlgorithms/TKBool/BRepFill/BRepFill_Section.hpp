#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Wire.hpp>
#include <TopoDS_Vertex.hpp>

//! To store section definition
class BRepFill_Section
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepFill_Section();

  Standard_EXPORT BRepFill_Section(const TopoDS_Shape&  Profile,
                                   const TopoDS_Vertex& V,
                                   const bool           WithContact,
                                   const bool           WithCorrection);

  Standard_EXPORT void Set(const bool IsLaw);

  const TopoDS_Shape& OriginalShape() const;

  const TopoDS_Wire& Wire() const;

  const TopoDS_Vertex& Vertex() const;

  Standard_EXPORT TopoDS_Shape ModifiedShape(const TopoDS_Shape& theShape) const;

  bool IsLaw() const;

  bool IsPunctual() const;

  bool WithContact() const;

  bool WithCorrection() const;

private:
  TopoDS_Shape  myOriginalShape;
  TopoDS_Wire   wire;
  TopoDS_Vertex vertex;
  bool          islaw;
  bool          ispunctual;
  bool          contact;
  bool          correction;
};

inline const TopoDS_Shape& BRepFill_Section::OriginalShape() const
{
  return myOriginalShape;
}

inline const TopoDS_Wire& BRepFill_Section::Wire() const
{
  return wire;
}

inline const TopoDS_Vertex& BRepFill_Section::Vertex() const
{
  return vertex;
}

inline bool BRepFill_Section::IsLaw() const
{
  return islaw;
}

inline bool BRepFill_Section::IsPunctual() const
{
  return ispunctual;
}

inline bool BRepFill_Section::WithContact() const
{
  return contact;
}

inline bool BRepFill_Section::WithCorrection() const
{
  return correction;
}
