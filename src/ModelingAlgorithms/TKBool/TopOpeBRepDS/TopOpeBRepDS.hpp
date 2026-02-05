#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TopAbs_State.hpp>
#include <TopOpeBRepDS_Kind.hpp>
#include <TCollection_AsciiString.hpp>
#include <TopAbs_ShapeEnum.hpp>
#include <TopAbs_Orientation.hpp>
#include <TopOpeBRepDS_Config.hpp>
class TCollection_AsciiString;

//! This package provides services used by the TopOpeBRepBuild
//! package performing topological operations on the BRep
//! data structure.
class TopOpeBRepDS
{
public:
  DEFINE_STANDARD_ALLOC

  //! IN OU ON UN
  Standard_EXPORT static TCollection_AsciiString SPrint(const TopAbs_State S);

  Standard_EXPORT static Standard_OStream& Print(const TopAbs_State S, Standard_OStream& OS);

  //! <K>
  Standard_EXPORT static TCollection_AsciiString SPrint(const TopOpeBRepDS_Kind K);

  //! S1(<K>,<I>)S2
  Standard_EXPORT static TCollection_AsciiString SPrint(const TopOpeBRepDS_Kind        K,
                                                        const int                      I,
                                                        const TCollection_AsciiString& B = "",
                                                        const TCollection_AsciiString& A = "");

  Standard_EXPORT static Standard_OStream& Print(const TopOpeBRepDS_Kind K, Standard_OStream& S);

  Standard_EXPORT static Standard_OStream& Print(const TopOpeBRepDS_Kind        K,
                                                 const int                      I,
                                                 Standard_OStream&              S,
                                                 const TCollection_AsciiString& B = "",
                                                 const TCollection_AsciiString& A = "");

  Standard_EXPORT static TCollection_AsciiString SPrint(const TopAbs_ShapeEnum T);

  //! (<T>,<I>)
  Standard_EXPORT static TCollection_AsciiString SPrint(const TopAbs_ShapeEnum T, const int I);

  Standard_EXPORT static Standard_OStream& Print(const TopAbs_ShapeEnum T,
                                                 const int              I,
                                                 Standard_OStream&      S);

  Standard_EXPORT static TCollection_AsciiString SPrint(const TopAbs_Orientation O);

  Standard_EXPORT static TCollection_AsciiString SPrint(const TopOpeBRepDS_Config C);

  Standard_EXPORT static Standard_OStream& Print(const TopOpeBRepDS_Config C, Standard_OStream& S);

  Standard_EXPORT static bool IsGeometry(const TopOpeBRepDS_Kind K);

  Standard_EXPORT static bool IsTopology(const TopOpeBRepDS_Kind K);

  Standard_EXPORT static TopAbs_ShapeEnum KindToShape(const TopOpeBRepDS_Kind K);

  Standard_EXPORT static TopOpeBRepDS_Kind ShapeToKind(const TopAbs_ShapeEnum S);
};
