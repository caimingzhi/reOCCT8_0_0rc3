#pragma once

#include <TObj_LabelIterator.hpp>

/**
 * This class provides an iterator by objects in a partition.
 * (implements TObj_ObjectIterator interface)
 */

class TObj_OcafObjectIterator : public TObj_LabelIterator
{
public:
  //! Creates the iterator on TObj objects on the sub-labels of theLabel.
  //! @param theLabel start label for searching
  //! @param theType type of the found objects, or all types if Null
  //! @param theRecursive search children recursively, not only on sub-labels of theLabel
  //! @param theAllSubChildren do not stop at the first level of children, but search for
  //! sub-children too
  Standard_EXPORT TObj_OcafObjectIterator(const TDF_Label&                  theLabel,
                                          const occ::handle<Standard_Type>& theType      = nullptr,
                                          const bool                        theRecursive = false,
                                          const bool theAllSubChildren                   = false);

protected:
  //! Shift iterator to the next object
  Standard_EXPORT void MakeStep() override;

protected:
  occ::handle<Standard_Type> myType; //!< type of objects to iterate on
  // clang-format off
  bool myAllSubChildren; //!< to iterate all sub-children, do not stop on the first level
  // clang-format on

public:
  //! CASCADE RTTI
  DEFINE_STANDARD_RTTIEXT(TObj_OcafObjectIterator, TObj_LabelIterator)
};

//! Define handle class for TObj_OcafObjectIterator

#ifdef _MSC_VER
  #pragma once
#endif
