#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_CString.hpp>
#include <Standard_Type.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TCollection_HExtendedString.hpp>
#include <TopoDS_Shape.hpp>
#include <TopAbs_ShapeEnum.hpp>
class Standard_Transient;
class TCollection_HAsciiString;
class TCollection_AsciiString;
class TCollection_HExtendedString;
class TCollection_ExtendedString;
class TopoDS_Shape;

class XSControl_Utils
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT XSControl_Utils();

  Standard_EXPORT void TraceLine(const char* line) const;

  Standard_EXPORT void TraceLines(const occ::handle<Standard_Transient>& lines) const;

  Standard_EXPORT bool IsKind(const occ::handle<Standard_Transient>& item,
                              const occ::handle<Standard_Type>&      what) const;

  Standard_EXPORT const char* TypeName(const occ::handle<Standard_Transient>& item,
                                       const bool                             nopk = false) const;

  Standard_EXPORT occ::handle<Standard_Transient> TraValue(
    const occ::handle<Standard_Transient>& list,
    const int                              num) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>> NewSeqTra()
    const;

  Standard_EXPORT void AppendTra(
    const occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>& seqval,
    const occ::handle<Standard_Transient>&                                     traval) const;

  Standard_EXPORT const char* DateString(const int yy,
                                         const int mm,
                                         const int dd,
                                         const int hh,
                                         const int mn,
                                         const int ss) const;

  Standard_EXPORT void DateValues(const char* text,
                                  int&        yy,
                                  int&        mm,
                                  int&        dd,
                                  int&        hh,
                                  int&        mn,
                                  int&        ss) const;

  Standard_EXPORT const char* ToCString(const occ::handle<TCollection_HAsciiString>& strval) const;

  Standard_EXPORT const char* ToCString(const TCollection_AsciiString& strval) const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ToHString(const char* strcon) const;

  Standard_EXPORT TCollection_AsciiString ToAString(const char* strcon) const;

  Standard_EXPORT const char16_t* ToEString(
    const occ::handle<TCollection_HExtendedString>& strval) const;

  Standard_EXPORT const char16_t* ToEString(const TCollection_ExtendedString& strval) const;

  Standard_EXPORT occ::handle<TCollection_HExtendedString> ToHString(const char16_t* strcon) const;

  Standard_EXPORT TCollection_ExtendedString ToXString(const char16_t* strcon) const;

  Standard_EXPORT const char16_t* AsciiToExtended(const char* str) const;

  Standard_EXPORT bool IsAscii(const char16_t* str) const;

  Standard_EXPORT const char* ExtendedToAscii(const char16_t* str) const;

  Standard_EXPORT const char* CStrValue(const occ::handle<Standard_Transient>& list,
                                        const int                              num) const;

  Standard_EXPORT const char16_t* EStrValue(const occ::handle<Standard_Transient>& list,
                                            const int                              num) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>
                  NewSeqCStr() const;

  Standard_EXPORT void AppendCStr(
    const occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>& seqval,
    const char*                                                                      strval) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HExtendedString>>>
                  NewSeqEStr() const;

  Standard_EXPORT void AppendEStr(
    const occ::handle<NCollection_HSequence<occ::handle<TCollection_HExtendedString>>>& seqval,
    const char16_t* strval) const;

  Standard_EXPORT TopoDS_Shape
    CompoundFromSeq(const occ::handle<NCollection_HSequence<TopoDS_Shape>>& seqval) const;

  Standard_EXPORT TopAbs_ShapeEnum ShapeType(const TopoDS_Shape& shape, const bool compound) const;

  Standard_EXPORT TopoDS_Shape SortedCompound(const TopoDS_Shape&    shape,
                                              const TopAbs_ShapeEnum type,
                                              const bool             explore,
                                              const bool             compound) const;

  Standard_EXPORT TopoDS_Shape
    ShapeValue(const occ::handle<NCollection_HSequence<TopoDS_Shape>>& seqv, const int num) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<TopoDS_Shape>> NewSeqShape() const;

  Standard_EXPORT void AppendShape(const occ::handle<NCollection_HSequence<TopoDS_Shape>>& seqv,
                                   const TopoDS_Shape& shape) const;

  Standard_EXPORT occ::handle<Standard_Transient> ShapeBinder(const TopoDS_Shape& shape,
                                                              const bool          hs = true) const;

  Standard_EXPORT TopoDS_Shape BinderShape(const occ::handle<Standard_Transient>& tr) const;

  Standard_EXPORT int SeqLength(const occ::handle<Standard_Transient>& list) const;

  Standard_EXPORT occ::handle<Standard_Transient> SeqToArr(
    const occ::handle<Standard_Transient>& seq,
    const int                              first = 1) const;

  Standard_EXPORT occ::handle<Standard_Transient> ArrToSeq(
    const occ::handle<Standard_Transient>& arr) const;

  Standard_EXPORT int SeqIntValue(const occ::handle<NCollection_HSequence<int>>& list,
                                  const int                                      num) const;
};
