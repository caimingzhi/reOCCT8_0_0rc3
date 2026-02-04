#pragma once


#include <Standard.hpp>

#include <TDF_Label.hpp>
#include <Draw_Drawable3D.hpp>
#include <Standard_OStream.hpp>
#include <Draw_Interpretor.hpp>
class Draw_Display;
class TCollection_AsciiString;
class TDataStd_TreeNode;

//! Browses a TreeNode from TDataStd.
//! =================================
class DDataStd_TreeBrowser : public Draw_Drawable3D
{

public:
  Standard_EXPORT DDataStd_TreeBrowser(const TDF_Label& root);

  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  //! Specific methods
  //! ================
  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

  Standard_EXPORT void Label(const TDF_Label& root);

  Standard_EXPORT TDF_Label Label() const;

  //! Returns a string composed with the TreeNode of
  //! <myLabel>.
  Standard_EXPORT TCollection_AsciiString OpenRoot() const;

  //! Returns a string composed with the sub-TreeNodes of
  //! <L>
  Standard_EXPORT TCollection_AsciiString OpenNode(const TDF_Label& L) const;

  DEFINE_STANDARD_RTTIEXT(DDataStd_TreeBrowser, Draw_Drawable3D)

private:
  //! Returns a string composed with the sub-TreeNodes
  //! of <aTreeNode>. Used to implement other methods.
  Standard_EXPORT void OpenNode(const occ::handle<TDataStd_TreeNode>& aTreeNode,
                                TCollection_AsciiString&              aList) const;

  TDF_Label myRoot;
};

