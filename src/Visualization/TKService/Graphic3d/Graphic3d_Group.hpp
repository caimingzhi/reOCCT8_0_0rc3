#pragma once

#include <BVH_Box.hpp>

typedef BVH_Box<float, 4> Graphic3d_BndBox4f;

#include <Graphic3d_AspectFillArea3d.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_CString.hpp>
#include <Graphic3d_Vertex.hpp>
#include <Graphic3d_TextPath.hpp>
#include <Graphic3d_HorizontalTextAlignment.hpp>
#include <Graphic3d_VerticalTextAlignment.hpp>
#include <Graphic3d_TypeOfPrimitiveArray.hpp>
#include <Graphic3d_IndexBuffer.hpp>
#include <Graphic3d_Buffer.hpp>
#include <Graphic3d_BoundBuffer.hpp>
#include <gp_Ax2.hpp>
#include <TCollection_ExtendedString.hpp>
class Graphic3d_Aspects;

class Graphic3d_Structure;
class Graphic3d_ArrayOfPrimitives;
class Graphic3d_Text;
class Graphic3d_TransformPers;

class Graphic3d_Group : public Standard_Transient
{
  friend class Graphic3d_Structure;
  DEFINE_STANDARD_RTTIEXT(Graphic3d_Group, Standard_Transient)

public:
  Standard_EXPORT virtual void Clear(const bool theUpdateStructureMgr = true);

  Standard_EXPORT ~Graphic3d_Group() override;

  Standard_EXPORT void Remove();

public:
  virtual occ::handle<Graphic3d_Aspects> Aspects() const = 0;

  virtual void SetGroupPrimitivesAspect(const occ::handle<Graphic3d_Aspects>& theAspect) = 0;

  virtual void SetPrimitivesAspect(const occ::handle<Graphic3d_Aspects>& theAspect) = 0;

  virtual void SynchronizeAspects() = 0;

  virtual void ReplaceAspects(
    const NCollection_DataMap<occ::handle<Graphic3d_Aspects>, occ::handle<Graphic3d_Aspects>>&
      theMap) = 0;

  Standard_EXPORT virtual void AddText(const occ::handle<Graphic3d_Text>& theTextParams,
                                       const bool                         theToEvalMinMax = true);

  Standard_EXPORT virtual void AddPrimitiveArray(
    const Graphic3d_TypeOfPrimitiveArray      theType,
    const occ::handle<Graphic3d_IndexBuffer>& theIndices,
    const occ::handle<Graphic3d_Buffer>&      theAttribs,
    const occ::handle<Graphic3d_BoundBuffer>& theBounds,
    const bool                                theToEvalMinMax = true);

  Standard_EXPORT void AddPrimitiveArray(const occ::handle<Graphic3d_ArrayOfPrimitives>& thePrim,
                                         const bool theToEvalMinMax = true);

public:
  Standard_EXPORT virtual void SetStencilTestOptions(const bool theIsEnabled) = 0;

  Standard_EXPORT virtual void SetFlippingOptions(const bool    theIsEnabled,
                                                  const gp_Ax2& theRefPlane) = 0;

  const gp_Trsf& Transformation() const { return myTrsf; }

  virtual void SetTransformation(const gp_Trsf& theTrsf) { myTrsf = theTrsf; }

  const occ::handle<Graphic3d_TransformPers>& TransformPersistence() const { return myTrsfPers; }

  Standard_EXPORT virtual void SetTransformPersistence(
    const occ::handle<Graphic3d_TransformPers>& theTrsfPers);

  Standard_EXPORT bool IsDeleted() const;

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT void MinMaxValues(double& theXMin,
                                    double& theYMin,
                                    double& theZMin,
                                    double& theXMax,
                                    double& theYMax,
                                    double& theZMax) const;

  Standard_EXPORT void SetMinMaxValues(const double theXMin,
                                       const double theYMin,
                                       const double theZMin,
                                       const double theXMax,
                                       const double theYMax,
                                       const double theZMax);

  const Graphic3d_BndBox4f& BoundingBox() const { return myBounds; }

  Graphic3d_BndBox4f& ChangeBoundingBox() { return myBounds; }

  Standard_EXPORT occ::handle<Graphic3d_Structure> Structure() const;

  void SetClosed(const bool theIsClosed) { myIsClosed = theIsClosed; }

  bool IsClosed() const { return myIsClosed; }

public:
  Standard_DEPRECATED(
    "Deprecated method Marker(), pass Graphic3d_ArrayOfPoints to AddPrimitiveArray() instead")
  Standard_EXPORT void Marker(const Graphic3d_Vertex& thePoint, const bool theToEvalMinMax = true);

  Standard_DEPRECATED(
    "Deprecated method Text() with obsolete arguments, use AddText() instead of it")
  Standard_EXPORT virtual void Text(const char*                             AText,
                                    const Graphic3d_Vertex&                 APoint,
                                    const double                            AHeight,
                                    const double                            AAngle,
                                    const Graphic3d_TextPath                ATp,
                                    const Graphic3d_HorizontalTextAlignment AHta,
                                    const Graphic3d_VerticalTextAlignment   AVta,
                                    const bool                              EvalMinMax = true);

  Standard_DEPRECATED(
    "Deprecated method Text() with obsolete arguments, use AddText() instead of it")
  Standard_EXPORT void Text(const char*             AText,
                            const Graphic3d_Vertex& APoint,
                            const double            AHeight,
                            const bool              EvalMinMax = true);

  Standard_DEPRECATED(
    "Deprecated method Text() with obsolete arguments, use AddText() instead of it")
  Standard_EXPORT void Text(const TCollection_ExtendedString&       AText,
                            const Graphic3d_Vertex&                 APoint,
                            const double                            AHeight,
                            const double                            AAngle,
                            const Graphic3d_TextPath                ATp,
                            const Graphic3d_HorizontalTextAlignment AHta,
                            const Graphic3d_VerticalTextAlignment   AVta,
                            const bool                              EvalMinMax = true);

  Standard_DEPRECATED(
    "Deprecated method Text() with obsolete arguments, use AddText() instead of it")
  Standard_EXPORT void Text(const TCollection_ExtendedString& AText,
                            const Graphic3d_Vertex&           APoint,
                            const double                      AHeight,
                            const bool                        EvalMinMax = true);

  Standard_DEPRECATED(
    "Deprecated method Text() with obsolete arguments, use AddText() instead of it")
  Standard_EXPORT virtual void Text(const char*                             theTextUtf,
                                    const gp_Ax2&                           theOrientation,
                                    const double                            theHeight,
                                    const double                            theAngle,
                                    const Graphic3d_TextPath                theTp,
                                    const Graphic3d_HorizontalTextAlignment theHTA,
                                    const Graphic3d_VerticalTextAlignment   theVTA,
                                    const bool                              theToEvalMinMax = true,
                                    const bool                              theHasOwnAnchor = true);

  Standard_DEPRECATED(
    "Deprecated method Text() with obsolete arguments, use AddText() instead of it")
  Standard_EXPORT virtual void Text(const TCollection_ExtendedString&       theText,
                                    const gp_Ax2&                           theOrientation,
                                    const double                            theHeight,
                                    const double                            theAngle,
                                    const Graphic3d_TextPath                theTp,
                                    const Graphic3d_HorizontalTextAlignment theHTA,
                                    const Graphic3d_VerticalTextAlignment   theVTA,
                                    const bool                              theToEvalMinMax = true,
                                    const bool                              theHasOwnAnchor = true);

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  Standard_EXPORT Graphic3d_Group(const occ::handle<Graphic3d_Structure>& theStructure);

  Standard_EXPORT void Update() const;

protected:
  occ::handle<Graphic3d_TransformPers> myTrsfPers;
  Graphic3d_Structure*                 myStructure;
  Graphic3d_BndBox4f                   myBounds;
  gp_Trsf                              myTrsf;
  bool                                 myIsClosed;
};
