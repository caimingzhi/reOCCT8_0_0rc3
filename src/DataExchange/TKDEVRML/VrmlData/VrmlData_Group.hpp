#pragma once

#include <NCollection_List.hpp>
#include <VrmlData_Node.hpp>
#include <NCollection_DataMap.hpp>
#include <VrmlData_Appearance.hpp>
#include <TopoDS_TShape.hpp>
#include <Bnd_B3.hpp>
#include <gp_Trsf.hpp>

class TopoDS_Shape;

class VrmlData_Group : public VrmlData_Node
{
public:
  typedef NCollection_List<occ::handle<VrmlData_Node>>::Iterator Iterator;

  VrmlData_Group(const bool isTransform = false)
      : myIsTransform(isTransform)
  {
  }

  Standard_EXPORT VrmlData_Group(const VrmlData_Scene& theScene,
                                 const char*           theName,
                                 const bool            isTransform = false);

  inline occ::handle<VrmlData_Node>& AddNode(const occ::handle<VrmlData_Node>& theNode)
  {
    return myNodes.Append(theNode);
  }

  Standard_EXPORT bool RemoveNode(const occ::handle<VrmlData_Node>& theNode);

  inline Iterator NodeIterator() const { return Iterator(myNodes); }

  inline const Bnd_B3f& Box() const { return myBox; }

  inline void SetBox(const Bnd_B3f& theBox) { myBox = theBox; }

  Standard_EXPORT bool SetTransform(const gp_Trsf& theTrsf);

  inline const gp_Trsf& GetTransform() const { return myTrsf; }

  inline bool IsTransform() const { return myIsTransform; }

  Standard_EXPORT occ::handle<VrmlData_Node> Clone(
    const occ::handle<VrmlData_Node>& theOther) const override;

  Standard_EXPORT VrmlData_ErrorStatus Read(VrmlData_InBuffer& theBuffer) override;

  Standard_EXPORT VrmlData_ErrorStatus Write(const char* thePrefix) const override;

  Standard_EXPORT occ::handle<VrmlData_Node> FindNode(const char* theName,
                                                      gp_Trsf&    theLocation) const;

  Standard_EXPORT void Shape(
    TopoDS_Shape&                                                                      theShape,
    NCollection_DataMap<occ::handle<TopoDS_TShape>, occ::handle<VrmlData_Appearance>>* pMapApp);

protected:
  Standard_EXPORT VrmlData_ErrorStatus openFile(Standard_IStream&              theStream,
                                                const TCollection_AsciiString& theFilename);

private:
  bool                                         myIsTransform;
  NCollection_List<occ::handle<VrmlData_Node>> myNodes;
  Bnd_B3f                                      myBox;
  gp_Trsf                                      myTrsf;

public:
  DEFINE_STANDARD_RTTIEXT(VrmlData_Group, VrmlData_Node)
};
