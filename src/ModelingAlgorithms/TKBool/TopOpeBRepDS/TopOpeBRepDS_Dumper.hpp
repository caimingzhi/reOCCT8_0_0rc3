#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopOpeBRepDS_Kind.hpp>
#include <Standard_Integer.hpp>
#include <TCollection_AsciiString.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_List.hpp>
class TopOpeBRepDS_HDataStructure;
class TCollection_AsciiString;
class TopoDS_Shape;

class TopOpeBRepDS_Dumper
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TopOpeBRepDS_Dumper(const occ::handle<TopOpeBRepDS_HDataStructure>& HDS);

  Standard_EXPORT TCollection_AsciiString SDumpRefOri(const TopOpeBRepDS_Kind K, const int I) const;

  Standard_EXPORT TCollection_AsciiString SDumpRefOri(const TopoDS_Shape& S) const;

  Standard_EXPORT TCollection_AsciiString SPrintShape(const int I) const;

  Standard_EXPORT TCollection_AsciiString SPrintShape(const TopoDS_Shape& S) const;

  Standard_EXPORT TCollection_AsciiString
    SPrintShapeRefOri(const TopoDS_Shape& S, const TCollection_AsciiString& B = "") const;

  Standard_EXPORT TCollection_AsciiString
    SPrintShapeRefOri(const NCollection_List<TopoDS_Shape>& L,
                      const TCollection_AsciiString&        B = "") const;

private:
  occ::handle<TopOpeBRepDS_HDataStructure> myHDS;
};
