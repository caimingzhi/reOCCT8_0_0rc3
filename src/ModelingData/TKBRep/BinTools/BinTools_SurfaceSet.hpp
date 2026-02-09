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
#include <BinTools_OStream.hpp>

class Geom_Surface;

class BinTools_SurfaceSet
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BinTools_SurfaceSet();

  Standard_EXPORT void Clear();

  Standard_EXPORT int Add(const occ::handle<Geom_Surface>& S);

  Standard_EXPORT occ::handle<Geom_Surface> Surface(const int I) const;

  Standard_EXPORT int Index(const occ::handle<Geom_Surface>& S) const;

  Standard_EXPORT void Write(Standard_OStream&            OS,
                             const Message_ProgressRange& theRange = Message_ProgressRange()) const;

  Standard_EXPORT void Read(Standard_IStream&            IS,
                            const Message_ProgressRange& therange = Message_ProgressRange());

  Standard_EXPORT static void WriteSurface(const occ::handle<Geom_Surface>& S,
                                           BinTools_OStream&                OS);

  Standard_EXPORT static Standard_IStream& ReadSurface(Standard_IStream&          IS,
                                                       occ::handle<Geom_Surface>& S);

private:
  NCollection_IndexedMap<occ::handle<Standard_Transient>> myMap;
};
