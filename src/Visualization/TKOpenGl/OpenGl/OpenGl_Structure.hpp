#pragma once

#include <Graphic3d_CStructure.hpp>

#include <OpenGl_GraphicDriver.hpp>
#include <OpenGl_Group.hpp>
#include <OpenGl_Workspace.hpp>

#include <NCollection_List.hpp>

class OpenGl_Structure : public Graphic3d_CStructure
{
  friend class OpenGl_Group;
  DEFINE_STANDARD_RTTIEXT(OpenGl_Structure, Graphic3d_CStructure)
public:
  typedef SubclassStructIterator<OpenGl_Structure> StructIterator;

  typedef SubclassGroupIterator<OpenGl_Group> GroupIterator;

public:
  Standard_EXPORT OpenGl_Structure(const occ::handle<Graphic3d_StructureManager>& theManager);

  Standard_EXPORT void OnVisibilityChanged() override;

  Standard_EXPORT void Clear() override;

  Standard_EXPORT void Connect(Graphic3d_CStructure& theStructure) override;

  Standard_EXPORT void Disconnect(Graphic3d_CStructure& theStructure) override;

  Standard_EXPORT void SetTransformation(const occ::handle<TopLoc_Datum3D>& theTrsf) override;

  Standard_EXPORT void SetTransformPersistence(
    const occ::handle<Graphic3d_TransformPers>& theTrsfPers) override;

  Standard_EXPORT void SetZLayer(const Graphic3d_ZLayerId theLayerIndex) override;

  Standard_EXPORT void GraphicHighlight(
    const occ::handle<Graphic3d_PresentationAttributes>& theStyle) override;

  Standard_EXPORT void GraphicUnhighlight() override;

  Standard_EXPORT occ::handle<Graphic3d_CStructure> ShadowLink(
    const occ::handle<Graphic3d_StructureManager>& theManager) const override;

  Standard_EXPORT occ::handle<Graphic3d_Group> NewGroup(
    const occ::handle<Graphic3d_Structure>& theStruct) override;

  Standard_EXPORT void RemoveGroup(const occ::handle<Graphic3d_Group>& theGroup) override;

public:
  OpenGl_GraphicDriver* GlDriver() const
  {
    return (OpenGl_GraphicDriver*)myGraphicDriver.operator->();
  }

  Standard_EXPORT void Clear(const occ::handle<OpenGl_Context>& theGlCtx);

  Standard_EXPORT virtual void Render(const occ::handle<OpenGl_Workspace>& theWorkspace) const;

  Standard_EXPORT virtual void Release(const occ::handle<OpenGl_Context>& theGlCtx);

  Standard_EXPORT void ReleaseGlResources(const occ::handle<OpenGl_Context>& theGlCtx);

  const OpenGl_Structure* InstancedStructure() const { return myInstancedStructure; }

  size_t ModificationState() const { return myModificationState; }

  void ResetModificationState() const { myModificationState = 0; }

  bool IsRaytracable() const;

  Standard_EXPORT void updateLayerTransformation() override;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT ~OpenGl_Structure() override;

  void UpdateStateIfRaytracable(const bool toCheck = true) const;

  Standard_EXPORT void renderGeometry(const occ::handle<OpenGl_Workspace>& theWorkspace,
                                      bool&                                theHasClosed) const;

  Standard_EXPORT void renderBoundingBox(const occ::handle<OpenGl_Workspace>& theWorkspace) const;

  Standard_EXPORT void applyTransformation(const occ::handle<OpenGl_Context>& theContext,
                                           const gp_Trsf&                     theTrsf,
                                           const bool                         toEnable) const;

  Standard_EXPORT void applyPersistence(
    const occ::handle<OpenGl_Context>&          theCtx,
    const occ::handle<Graphic3d_TransformPers>& theTrsfPersistence,
    const bool                                  theIsLocal,
    bool&                                       theOldCastShadows) const;

  Standard_EXPORT void revertPersistence(
    const occ::handle<OpenGl_Context>&          theCtx,
    const occ::handle<Graphic3d_TransformPers>& theTrsfPersistence,
    const bool                                  theIsLocal,
    const bool                                  theOldCastShadows) const;

protected:
  OpenGl_Structure* myInstancedStructure;

  NCollection_Mat4<float> myRenderTrsf;

  mutable bool   myIsRaytracable;
  mutable size_t myModificationState;

  bool myIsMirrored;
};
