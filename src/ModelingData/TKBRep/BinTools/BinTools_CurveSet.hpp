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

class Geom_Curve;

//! Stores a set of Curves from Geom in binary format.
class BinTools_CurveSet
{
public:
  DEFINE_STANDARD_ALLOC

  //! Returns an empty set of Curves.
  Standard_EXPORT BinTools_CurveSet();

  //! Clears the content of the set.
  Standard_EXPORT void Clear();

  //! Incorporate a new Curve in the set and returns
  //! its index.
  Standard_EXPORT int Add(const occ::handle<Geom_Curve>& C);

  //! Returns the Curve of index <I>.
  Standard_EXPORT occ::handle<Geom_Curve> Curve(const int I) const;

  //! Returns the index of <L>.
  Standard_EXPORT int Index(const occ::handle<Geom_Curve>& C) const;

  //! Writes the content of me on the stream <OS> in a
  //! format that can be read back by Read.
  Standard_EXPORT void Write(Standard_OStream&            OS,
                             const Message_ProgressRange& theRange = Message_ProgressRange()) const;

  //! Reads the content of me from the stream <IS>. me
  //! is first cleared.
  Standard_EXPORT void Read(Standard_IStream&            IS,
                            const Message_ProgressRange& theRange = Message_ProgressRange());

  //! Dumps the curve on the stream in binary format
  //! that can be read back.
  Standard_EXPORT static void WriteCurve(const occ::handle<Geom_Curve>& C, BinTools_OStream& OS);

  //! Reads the curve from the stream. The curve is
  //! assumed to have been written with the Write
  //! method
  Standard_EXPORT static Standard_IStream& ReadCurve(Standard_IStream&        IS,
                                                     occ::handle<Geom_Curve>& C);

private:
  NCollection_IndexedMap<occ::handle<Standard_Transient>> myMap;
};

