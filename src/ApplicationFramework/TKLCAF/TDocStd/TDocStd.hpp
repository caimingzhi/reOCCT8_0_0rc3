#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_GUID.hpp>
#include <NCollection_List.hpp>

//! This package define CAF main classes.
//!
//! * The standard application root class
//!
//! * The standard document which contains data
//!
//! * The external reference mechanism between documents
//!
//! * Attributes for Document management
//! Standard documents offer you a ready-to-use
//! document containing a TDF-based data
//! structure. The documents themselves are
//! contained in a class inheriting from
//! TDocStd_Application which manages creation,
//! storage and retrieval of documents.
//! You can implement undo and redo in your
//! document, and refer from the data framework of
//! one document to that of another one. This is
//! done by means of external link attributes, which
//! store the path and the entry of external links. To
//! sum up, standard documents alone provide
//! access to the data framework. They also allow
//! you to:
//! - Update external links
//! - Manage the saving and opening of data
//! - Manage undo/redo functionality.
//! Note
//! For information on the relations between this
//! component of OCAF and the others, refer to the
//! OCAF User's Guide.
class TDocStd
{
public:
  DEFINE_STANDARD_ALLOC

  //! specific GUID of this package
  //! =============================
  //! Appends to <anIDList> the list of the attributes
  //! IDs of this package. CAUTION: <anIDList> is NOT
  //! cleared before use.
  Standard_EXPORT static void IDList(NCollection_List<Standard_GUID>& anIDList);
};

