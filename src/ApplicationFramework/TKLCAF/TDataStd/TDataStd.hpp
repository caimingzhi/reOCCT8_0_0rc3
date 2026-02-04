#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_GUID.hpp>
#include <NCollection_List.hpp>
#include <Standard_OStream.hpp>
#include <TDataStd_RealEnum.hpp>

//! This package defines standard attributes for
//! modelling.
//! These allow you to create and modify labels
//! and attributes for many basic data types.
//! Standard topological and visualization
//! attributes have also been created.
//! To find an attribute attached to a specific label,
//! you use the GUID of the type of attribute you
//! are looking for. To do this, first find this
//! information using the method GetID as follows: Standard_GUID anID =
//! MyAttributeClass::GetID();
//! Then, use the method Find for the label as follows:
//! bool HasAttribute
//! =
//! aLabel.Find(anID,anAttribute);
//! Note
//! For information on the relations between this
//! component of OCAF and the others, refer to the OCAF User's Guide.
class TDataStd
{
public:
  DEFINE_STANDARD_ALLOC

  //! Appends to <anIDList> the list of the attributes
  //! IDs of this package. CAUTION: <anIDList> is NOT
  //! cleared before use.
  Standard_EXPORT static void IDList(NCollection_List<Standard_GUID>& anIDList);

  //! Prints the name of the real dimension <DIM> as a String on
  //! the Stream <S> and returns <S>.
  Standard_EXPORT static Standard_OStream& Print(const TDataStd_RealEnum DIM, Standard_OStream& S);
};

