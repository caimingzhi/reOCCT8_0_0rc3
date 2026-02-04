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

//! Stores a set of Curves from Geom2d.
class GeomTools_Curve2dSet
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns an empty set of Curves.
  Standard_EXPORT GeomTools_Curve2dSet();

  //! Clears the content of the set.
  Standard_EXPORT void Clear();

  //! Incorporate a new Curve in the set and returns
  //! its index.
  Standard_EXPORT int Add(const occ::handle<Geom2d_Curve>& C);

  //! Returns the Curve of index <I>.
  Standard_EXPORT occ::handle<Geom2d_Curve> Curve2d(const int I) const;

  //! Returns the index of <L>.
  Standard_EXPORT int Index(const occ::handle<Geom2d_Curve>& C) const;

  //! Dumps the content of me on the stream <OS>.
  Standard_EXPORT void Dump(Standard_OStream& OS) const;

  //! Writes the content of me on the stream <OS> in a
  //! format that can be read back by Read.
  Standard_EXPORT void Write(
    Standard_OStream&            OS,
    const Message_ProgressRange& theProgress = Message_ProgressRange()) const;

  //! Reads the content of me from the stream <IS>.
  //! me is first cleared.
  Standard_EXPORT void Read(Standard_IStream&            IS,
                            const Message_ProgressRange& theProgress = Message_ProgressRange());

  //! Dumps the curve on the stream, if compact is True
  //! use the compact format that can be read back.
  Standard_EXPORT static void PrintCurve2d(const occ::handle<Geom2d_Curve>& C,
                                           Standard_OStream&                OS,
                                           const bool                       compact = false);

  //! Reads the curve from the stream. The curve is
  //! assumed to have been written with the Print
  //! method (compact = True).
  Standard_EXPORT static occ::handle<Geom2d_Curve> ReadCurve2d(Standard_IStream& IS);

private:
  NCollection_IndexedMap<occ::handle<Standard_Transient>> myMap;
};

