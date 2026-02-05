#pragma once

#include <Standard.hpp>

#include <gp_Pnt.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_OStream.hpp>
class Standard_GUID;
class TDF_Label;
class TDF_RelocationTable;

//! attribute to store centroid
class XCAFDoc_Centroid : public TDF_Attribute
{

public:
  //! class methods
  //! =============
  Standard_EXPORT XCAFDoc_Centroid();

  Standard_EXPORT static const Standard_GUID& GetID();

  //! Find, or create, a Location attribute and set it's value
  //! the Location attribute is returned.
  //! Location methods
  //! ===============
  Standard_EXPORT static occ::handle<XCAFDoc_Centroid> Set(const TDF_Label& label,
                                                           const gp_Pnt&    pnt);

  Standard_EXPORT void Set(const gp_Pnt& pnt);

  Standard_EXPORT gp_Pnt Get() const;

  //! Returns point as argument
  //! returns false if no such attribute at the <label>
  Standard_EXPORT static bool Get(const TDF_Label& label, gp_Pnt& pnt);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& With) override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       Into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(XCAFDoc_Centroid, TDF_Attribute)

private:
  gp_Pnt myCentroid;
};
