#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <TopoDS_Solid.hpp>
#include <TopOpeBRepBuild_ShapeSet.hpp>
#include <TCollection_AsciiString.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopoDS_Shape;
class TCollection_AsciiString;

//! a bound is a shell, a boundelement is a face.
//! The ShapeSet stores :
//! - a list of shell (bounds),
//! - a list of face (boundelements) to start reconstructions,
//! - a map of edge giving the list of face incident to an edge.
class TopOpeBRepBuild_ShellFaceSet : public TopOpeBRepBuild_ShapeSet
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a ShellFaceSet to build blocks of faces
  //! connected by edges.
  Standard_EXPORT TopOpeBRepBuild_ShellFaceSet();

  //! Creates a ShellFaceSet to build blocks of faces
  //! connected by edges.
  Standard_EXPORT TopOpeBRepBuild_ShellFaceSet(const TopoDS_Shape& S, void* const Addr = nullptr);

  Standard_EXPORT const TopoDS_Solid& Solid() const;

  Standard_EXPORT void AddShape(const TopoDS_Shape& S) override;

  Standard_EXPORT void AddStartElement(const TopoDS_Shape& S) override;

  Standard_EXPORT void AddElement(const TopoDS_Shape& S) override;

  Standard_EXPORT void DumpSS() override;

  Standard_EXPORT TCollection_AsciiString
    SName(const TopoDS_Shape&            S,
          const TCollection_AsciiString& sb = "",
          const TCollection_AsciiString& sa = "") const override;

  Standard_EXPORT TCollection_AsciiString
    SName(const NCollection_List<TopoDS_Shape>& S,
          const TCollection_AsciiString&        sb = "",
          const TCollection_AsciiString&        sa = "") const override;

  Standard_EXPORT TCollection_AsciiString
    SNameori(const TopoDS_Shape&            S,
             const TCollection_AsciiString& sb = "",
             const TCollection_AsciiString& sa = "") const override;

  Standard_EXPORT TCollection_AsciiString
    SNameori(const NCollection_List<TopoDS_Shape>& S,
             const TCollection_AsciiString&        sb = "",
             const TCollection_AsciiString&        sa = "") const override;

private:
  TopoDS_Solid mySolid;
};

