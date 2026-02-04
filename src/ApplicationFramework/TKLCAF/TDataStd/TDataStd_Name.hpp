#pragma once


#include <TDataStd_GenericExtString.hpp>
#include <Standard_OStream.hpp>

class TDF_Label;
class TCollection_ExtendedString;

//! Used to define a name attribute containing a string which specifies the name.
class TDataStd_Name : public TDataStd_GenericExtString
{

public:
  //! class methods working on the name itself
  //! ========================================
  //! Returns the GUID for name attributes.
  Standard_EXPORT static const Standard_GUID& GetID();

  //! Creates (if does not exist) and sets the name in the name attribute.
  //! from any label <L> search in father labels (L is not
  //! concerned) the first name attribute. if found set it in
  //! <father>.
  //! class methods working on the name tree
  //! ======================================
  //! Search in the whole TDF_Data the Name attribute which
  //! fit with <fullPath>. Returns True if found.
  //! Search under <currentLabel> a label which fit with
  //! <name>. Returns True if found. Shortcut which avoids
  //! building a ListOfExtendedStrin.
  //! Search in the whole TDF_Data the label which fit with name
  //! Returns True if found.
  //! tools methods to translate path <-> pathlist
  //! ===========================================
  //! move to draw For Draw test we may provide this tool method which convert a path in a
  //! sequence of string to call after the FindLabel methods.
  //! Example: if it's given "Assembly:Part_1:Sketch_5" it will return in <pathlist>
  //! the list of 3 strings: "Assembly","Part_1","Sketch_5".
  //! move to draw from <pathlist> build the string path
  //! Name methods
  //! ============
  Standard_EXPORT static occ::handle<TDataStd_Name> Set(const TDF_Label&                  label,
                                                        const TCollection_ExtendedString& string);

  //! Finds, or creates, a Name attribute with explicit user defined <guid> and sets <string>.
  //! The Name attribute is returned.
  Standard_EXPORT static occ::handle<TDataStd_Name> Set(const TDF_Label&                  label,
                                                        const Standard_GUID&              guid,
                                                        const TCollection_ExtendedString& string);

  Standard_EXPORT TDataStd_Name();

  //! Sets <S> as name. Raises if <S> is not a valid name.
  Standard_EXPORT void Set(const TCollection_ExtendedString& S) override;

  //! Sets the explicit user defined GUID to the attribute.
  Standard_EXPORT void SetID(const Standard_GUID& guid) override;

  //! Sets default GUID for the attribute.
  Standard_EXPORT void SetID() override;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& anOS) const override;

  DEFINE_DERIVED_ATTRIBUTE(TDataStd_Name, TDataStd_GenericExtString)
};

