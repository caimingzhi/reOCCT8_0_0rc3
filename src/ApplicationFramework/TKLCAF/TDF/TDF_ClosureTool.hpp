#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <TDF_Label.hpp>
#include <NCollection_Map.hpp>
#include <TDF_Attribute.hpp>
class TDF_DataSet;
class TDF_IDFilter;
class TDF_ClosureMode;
class TDF_Label;

//! This class provides services to build the closure
//! of an information set.
//! This class gives services around the transitive
//! enclosure of a set of information, starting from a
//! list of label.
//! You can set closure options by using IDFilter
//! (to select or exclude specific attribute IDs) and
//! CopyOption objects and by giving to Closure
//! method.
class TDF_ClosureTool
{
public:
  DEFINE_STANDARD_ALLOC

  //! Builds the transitive closure of label and
  //! attribute sets into <aDataSet>.
  Standard_EXPORT static void Closure(const occ::handle<TDF_DataSet>& aDataSet);

  //! Builds the transitive closure of label and
  //! attribute sets into <aDataSet>. Uses <aFilter> to
  //! determine if an attribute has to be taken in
  //! account or not. Uses <aMode> for various way of
  //! closing.
  Standard_EXPORT static void Closure(const occ::handle<TDF_DataSet>& aDataSet,
                                      const TDF_IDFilter&             aFilter,
                                      const TDF_ClosureMode&          aMode);

  //! Builds the transitive closure of <aLabel>.
  Standard_EXPORT static void Closure(const TDF_Label&                             aLabel,
                                      NCollection_Map<TDF_Label>&                  aLabMap,
                                      NCollection_Map<occ::handle<TDF_Attribute>>& anAttMap,
                                      const TDF_IDFilter&                          aFilter,
                                      const TDF_ClosureMode&                       aMode);

private:
  //! Adds label attributes and dependences.
  Standard_EXPORT static void LabelAttributes(const TDF_Label&                             aLabel,
                                              NCollection_Map<TDF_Label>&                  aLabMap,
                                              NCollection_Map<occ::handle<TDF_Attribute>>& anAttMap,
                                              const TDF_IDFilter&                          aFilter,
                                              const TDF_ClosureMode&                       aMode);
};
