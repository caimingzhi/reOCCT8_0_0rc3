#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <TDF_Label.hpp>
#include <NCollection_DoubleMap.hpp>
#include <TFunction_Logbook.hpp>
#include <TDF_Attribute.hpp>
#include <Standard_OStream.hpp>
class TDF_Label;
class Standard_GUID;
class TFunction_Logbook;
class TDF_RelocationTable;

//! Keeps a scope of functions.
class TFunction_Scope : public TDF_Attribute
{

public:
  //! Static methods
  //! ==============
  //! Finds or Creates a TFunction_Scope attribute at the root label accessed by <Access>.
  //! Returns the attribute.
  Standard_EXPORT static occ::handle<TFunction_Scope> Set(const TDF_Label& Access);

  //! Returns the GUID for Scope attribute.
  //! Instant methods
  //! ===============
  //! Constructor (empty).
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT TFunction_Scope();

  //! Adds a function to the scope of functions.
  Standard_EXPORT bool AddFunction(const TDF_Label& L);

  //! Removes a function from the scope of functions.
  Standard_EXPORT bool RemoveFunction(const TDF_Label& L);

  //! Removes a function from the scope of functions.
  Standard_EXPORT bool RemoveFunction(const int ID);

  //! Removes all functions from the scope of functions.
  Standard_EXPORT void RemoveAllFunctions();

  //! Returns true if the function exists with such an ID.
  Standard_EXPORT bool HasFunction(const int ID) const;

  //! Returns true if the label contains a function of this scope.
  Standard_EXPORT bool HasFunction(const TDF_Label& L) const;

  //! Returns an ID of the function.
  Standard_EXPORT int GetFunction(const TDF_Label& L) const;

  //! Returns the label of the function with this ID.
  Standard_EXPORT const TDF_Label& GetFunction(const int ID) const;

  //! Returns the Logbook used in TFunction_Driver methods.
  //! Implementation of Attribute methods
  //! ===================================
  Standard_EXPORT occ::handle<TFunction_Logbook> GetLogbook() const;

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT void Restore(const occ::handle<TDF_Attribute>& with) override;

  Standard_EXPORT void Paste(const occ::handle<TDF_Attribute>&       into,
                             const occ::handle<TDF_RelocationTable>& RT) const override;

  Standard_EXPORT occ::handle<TDF_Attribute> NewEmpty() const override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  //! Returns the scope of functions.
  Standard_EXPORT const NCollection_DoubleMap<int, TDF_Label>& GetFunctions() const;

  //! Returns the scope of functions for modification.
  //! Warning: Don't use this method if You are not sure what You do!
  Standard_EXPORT NCollection_DoubleMap<int, TDF_Label>& ChangeFunctions();

  Standard_EXPORT void SetFreeID(const int ID);

  Standard_EXPORT int GetFreeID() const;

  DEFINE_STANDARD_RTTIEXT(TFunction_Scope, TDF_Attribute)

private:
  NCollection_DoubleMap<int, TDF_Label> myFunctions;
  int                                   myFreeID;
};

