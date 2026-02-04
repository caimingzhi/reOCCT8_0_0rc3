#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
class TDF_DataSet;
class TDF_RelocationTable;
class TDF_Label;

//! This tool class is used to copy the content of
//! source label under target label. Only child
//! labels and attributes of source are copied.
//! attributes located out of source scope are not
//! copied by this algorithm.
//! Depending of the called method an external
//! reference is set in the target document to
//! registered the externallink.
//! Provide services to set, update and perform
//! external references.
//! Warning1: Nothing is provided in this class about the
//! opportunity to copy, set a link or update it.
//! Such decisions must be under application control.
//! Warning2: If the document manages shapes, use after copy
//! TNaming::ChangeShapes(target,M) to make copy of
//! shapes.
class TDocStd_XLinkTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT TDocStd_XLinkTool();

  //! Copies the content of the label <fromsource> to the label <intarget>.
  //! The link is registered with an XLink attribute by <intarget>
  //! label. if the content of <fromsource> is not
  //! self-contained, and/or <intarget> has already an XLink
  //! attribute, an exception is raised.
  Standard_EXPORT void CopyWithLink(const TDF_Label& intarget, const TDF_Label& fromsource);

  //! Update the external reference set at <L>.
  //! Example
  //! occ::handle<TDocStd_Document> aDoc;
  //! if
  //! (!OCAFTest::GetDocument(1,aDoc)) return 1;
  //! occ::handle<TDataStd_Reference> aRef;
  //! TDocStd_XLinkTool xlinktool;
  //! if
  //! (!OCAFTest::Find(aDoc,2),TDataStd_Reference::GetID(),aRef) return 1;
  //! xlinktool.UpdateLink(aRef->Label());
  //! Exceptions
  //! Standard_DomainError if <L> has no XLink attribute.
  Standard_EXPORT void UpdateLink(const TDF_Label& L);

  //! Copy the content of <fromsource> under
  //! <intarget>. No link is registered. No check is done.
  //! Example
  //! occ::handle<TDocStd_Document> DOC, XDOC;
  //! TDF_Label L, XL;
  //! TDocStd_XLinkTool xlinktool;
  //! xlinktool.Copy(L,XL);
  //! Exceptions:
  //! Standard_DomainError if the contents of
  //! fromsource are not entirely in the scope of this
  //! label, in other words, are not self-contained.
  //! !!! ==> Warning:
  //! If the document manages shapes use the next way:
  //! TDocStd_XLinkTool xlinktool;
  //! xlinktool.Copy(L,XL);
  //! NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> M;
  //! TNaming::ChangeShapes(target,M);
  Standard_EXPORT virtual void Copy(const TDF_Label& intarget, const TDF_Label& fromsource);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT occ::handle<TDF_DataSet> DataSet() const;

  Standard_EXPORT occ::handle<TDF_RelocationTable> RelocationTable() const;

protected:
  bool isDone;

private:
  occ::handle<TDF_DataSet>         myDS;
  occ::handle<TDF_RelocationTable> myRT;
};

