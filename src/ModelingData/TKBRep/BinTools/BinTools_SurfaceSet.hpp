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

//! Stores a set of Surfaces from Geom in binary format.
class BinTools_SurfaceSet
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns an empty set of Surfaces.
  Standard_EXPORT BinTools_SurfaceSet();

  //! Clears the content of the set.
  Standard_EXPORT void Clear();

  //! Incorporate a new Surface in the set and returns
  //! its index.
  Standard_EXPORT int Add(const occ::handle<Geom_Surface>& S);

  //! Returns the Surface of index <I>.
  Standard_EXPORT occ::handle<Geom_Surface> Surface(const int I) const;

  //! Returns the index of <L>.
  Standard_EXPORT int Index(const occ::handle<Geom_Surface>& S) const;

  //! Writes the content of me on the stream <OS> in
  //! binary format that can be read back by Read.
  Standard_EXPORT void Write(Standard_OStream&            OS,
                             const Message_ProgressRange& theRange = Message_ProgressRange()) const;

  //! Reads the content of me from the stream <IS>. me
  //! is first cleared.
  Standard_EXPORT void Read(Standard_IStream&            IS,
                            const Message_ProgressRange& therange = Message_ProgressRange());

  //! Dumps the surface on the stream in binary
  //! format that can be read back.
  Standard_EXPORT static void WriteSurface(const occ::handle<Geom_Surface>& S,
                                           BinTools_OStream&                OS);

  //! Reads the surface from the stream. The surface is
  //! assumed to have been written with the Write method.
  Standard_EXPORT static Standard_IStream& ReadSurface(Standard_IStream&          IS,
                                                       occ::handle<Geom_Surface>& S);

private:
  NCollection_IndexedMap<occ::handle<Standard_Transient>> myMap;
};

