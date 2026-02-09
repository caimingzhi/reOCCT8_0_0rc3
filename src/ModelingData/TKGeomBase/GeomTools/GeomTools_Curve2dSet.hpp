#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
#include <Standard_IStream.hpp>
#include <Message_ProgressRange.hpp>

class Geom2d_Curve;

class GeomTools_Curve2dSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomTools_Curve2dSet();

  Standard_EXPORT void Clear();

  Standard_EXPORT int Add(const occ::handle<Geom2d_Curve>& C);

  Standard_EXPORT occ::handle<Geom2d_Curve> Curve2d(const int I) const;

  Standard_EXPORT int Index(const occ::handle<Geom2d_Curve>& C) const;

  Standard_EXPORT void Dump(Standard_OStream& OS) const;

  Standard_EXPORT void Write(
    Standard_OStream&            OS,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) const;

  Standard_EXPORT void Read(Standard_IStream&            IS,
                            const Message_ProgressRange& theProgress = Message_ProgressRange());

  Standard_EXPORT static void PrintCurve2d(const occ::handle<Geom2d_Curve>& C,
                                           Standard_OStream&                OS,
                                           const bool                       compact = false);

  Standard_EXPORT static occ::handle<Geom2d_Curve> ReadCurve2d(Standard_IStream& IS);

private:
  NCollection_IndexedMap<occ::handle<Standard_Transient>> myMap;
};
