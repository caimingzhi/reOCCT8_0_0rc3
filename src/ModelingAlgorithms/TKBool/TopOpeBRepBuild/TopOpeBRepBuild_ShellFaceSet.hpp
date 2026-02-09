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

class TopOpeBRepBuild_ShellFaceSet : public TopOpeBRepBuild_ShapeSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepBuild_ShellFaceSet();

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
