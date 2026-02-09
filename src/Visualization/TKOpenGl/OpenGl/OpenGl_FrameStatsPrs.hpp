#pragma once

#include <OpenGl_Aspects.hpp>
#include <OpenGl_FrameStats.hpp>
#include <OpenGl_Text.hpp>

class Graphic3d_ArrayOfTriangles;
class Graphic3d_TransformPers;
class OpenGl_IndexBuffer;
class OpenGl_VertexBuffer;

class OpenGl_FrameStatsPrs : public OpenGl_Element
{
public:
  Standard_EXPORT OpenGl_FrameStatsPrs();

  Standard_EXPORT ~OpenGl_FrameStatsPrs() override;

  Standard_EXPORT void Render(const occ::handle<OpenGl_Workspace>& theWorkspace) const override;

  Standard_EXPORT void Release(OpenGl_Context* theCtx) override;

  Standard_EXPORT void Update(const occ::handle<OpenGl_Workspace>& theWorkspace);

  void SetTextAspect(const occ::handle<Graphic3d_AspectText3d>& theAspect)
  {
    myTextAspect.SetAspect(theAspect);
  }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

protected:
  Standard_EXPORT void updateChart(const occ::handle<OpenGl_Workspace>& theWorkspace);

protected:
  occ::handle<OpenGl_FrameStats> myStatsPrev;

  occ::handle<Graphic3d_TransformPers> myCountersTrsfPers;
  OpenGl_Text                          myCountersText;
  OpenGl_Aspects                       myTextAspect;
  occ::handle<Graphic3d_TransformPers> myChartTrsfPers;

  occ::handle<Graphic3d_ArrayOfTriangles> myChartArray;
  occ::handle<OpenGl_VertexBuffer>        myChartVertices;
  occ::handle<OpenGl_IndexBuffer>         myChartIndices;
  occ::handle<OpenGl_VertexBuffer>        myChartLines;
  OpenGl_Text                             myChartLabels[3];
};
