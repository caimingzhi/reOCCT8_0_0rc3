#pragma once

#include <Graphic3d_GraduatedTrihedron.hpp>
#include <NCollection_Array1.hpp>
#include <OpenGl_Aspects.hpp>
#include <OpenGl_Element.hpp>
#include <OpenGl_PrimitiveArray.hpp>
#include <OpenGl_Text.hpp>

class OpenGl_GraduatedTrihedron : public OpenGl_Element
{
public:
  DEFINE_STANDARD_ALLOC

public:
  Standard_EXPORT OpenGl_GraduatedTrihedron();

  Standard_EXPORT ~OpenGl_GraduatedTrihedron() override;

  Standard_EXPORT void Render(const occ::handle<OpenGl_Workspace>& theWorkspace) const override;

  Standard_EXPORT void Release(OpenGl_Context* theCtx) override;

  Standard_EXPORT void SetValues(const Graphic3d_GraduatedTrihedron& theData);

  Standard_EXPORT void SetMinMax(const NCollection_Vec3<float>& theMin,
                                 const NCollection_Vec3<float>& theMax);

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

private:
  class Axis
  {
  public:
    NCollection_Vec3<float>       Direction;
    Quantity_Color                NameColor;
    OpenGl_Aspects                LineAspect;
    mutable OpenGl_Text           Label;
    mutable OpenGl_PrimitiveArray Tickmark;
    mutable OpenGl_PrimitiveArray Line;
    mutable OpenGl_PrimitiveArray Arrow;

  public:
    Axis(const Graphic3d_GraduatedTrihedron::AxisAspect& theAspect =
           Graphic3d_GraduatedTrihedron::AxisAspect(),
         const NCollection_Vec3<float>& theDirection = NCollection_Vec3<float>(1.0f, 0.0f, 0.0f));

    ~Axis();

    Axis& operator=(const Axis& theOther);

    void InitArrow(const occ::handle<OpenGl_Context>& theContext,
                   const float                        theLength,
                   const NCollection_Vec3<float>&     theNormal) const;

    void InitTickmark(const occ::handle<OpenGl_Context>& theContext,
                      const NCollection_Vec3<float>&     theDir) const;

    void InitLine(const occ::handle<OpenGl_Context>& theContext,
                  const NCollection_Vec3<float>&     theDir) const;

    void Release(OpenGl_Context* theCtx);
  };

private:
  struct GridAxes
  {
  public:
    GridAxes()
        : Origin(0, 0, 0)
    {
      Axes[0] = NCollection_Vec3<float>(1.0f, 0.0f, 0.0f);
      Axes[1] = NCollection_Vec3<float>(0.0f, 1.0f, 0.0f);
      Axes[2] = NCollection_Vec3<float>(0.0f, 0.0f, 1.0f);

      Ticks[0] = NCollection_Vec3<float>(0.0f, 0.0f, 0.0f);
      Ticks[1] = NCollection_Vec3<float>(0.0f, 0.0f, 0.0f);
      Ticks[2] = NCollection_Vec3<float>(0.0f, 0.0f, 0.0f);
    }

  public:
    NCollection_Vec3<float> Origin;
    NCollection_Vec3<float> Axes[3];

  public:
    NCollection_Vec3<float> Ticks[3];
  };

private:
  void initGlResources(const occ::handle<OpenGl_Context>& theContext) const;

  float getNormal(const occ::handle<OpenGl_Context>& theContext,
                  NCollection_Vec3<float>&           theNormal) const;

  float getDistanceToCorner(const NCollection_Vec3<float>& theNormal,
                            const NCollection_Vec3<float>& theCenter,
                            const float                    theX,
                            const float                    theY,
                            const float                    theZ) const;

  char16_t getGridAxes(const float theCorners[8], GridAxes& theGridAxes) const;

  void renderLine(const OpenGl_PrimitiveArray&         theLine,
                  const occ::handle<OpenGl_Workspace>& theWorkspace,
                  const NCollection_Mat4<float>&       theMat,
                  const float                          theXt,
                  const float                          theYt,
                  const float                          theZt) const;

  void renderGridPlane(const occ::handle<OpenGl_Workspace>& theWorkspace,
                       const int&                           theIndex,
                       const GridAxes&                      theGridAxes,
                       NCollection_Mat4<float>&             theMat) const;

  void renderAxis(const occ::handle<OpenGl_Workspace>& theWorkspace,
                  const int&                           theIndex,
                  const NCollection_Mat4<float>&       theMat) const;

  void renderTickmarkLabels(const occ::handle<OpenGl_Workspace>& theWorkspace,
                            const NCollection_Mat4<float>&       theMat,
                            const int                            theIndex,
                            const GridAxes&                      theGridAxes,
                            const float                          theDpix) const;

protected:
  NCollection_Vec3<float> myMin;
  NCollection_Vec3<float> myMax;

protected:
  mutable Axis                         myAxes[3];
  mutable Graphic3d_GraduatedTrihedron myData;
  mutable OpenGl_Aspects               myGridLineAspect;

protected:
  mutable OpenGl_Text    myLabelValues;
  mutable OpenGl_Aspects myAspectLabels;
  mutable OpenGl_Aspects myAspectValues;

private:
  mutable bool myIsInitialized;

  enum AxisFlags
  {
    XOO_XYO = 1 << 1,
    XOO_XOZ = 1 << 2,
    OYO_OYZ = 1 << 3,
    OYO_XYO = 1 << 4,
    OOZ_XOZ = 1 << 5,
    OOZ_OYZ = 1 << 6,
    OYZ_XYZ = 1 << 7,
    XOZ_XYZ = 1 << 8,
    XYO_XYZ = 1 << 9
  };
};
