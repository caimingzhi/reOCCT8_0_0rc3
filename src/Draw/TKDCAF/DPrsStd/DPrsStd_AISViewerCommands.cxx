#include <DPrsStd.hpp>

#include <Draw_Appli.hpp>
#include <Draw_Interpretor.hpp>
#include <TCollection_AsciiString.hpp>
#include <TDocStd_Document.hpp>
#include <TDF_Label.hpp>
#include <TDF_Data.hpp>
#include <DDF.hpp>
#include <DDocStd.hpp>
#include <ViewerTest.hpp>
#include <V3d_View.hpp>
#include <TPrsStd_AISPresentation.hpp>
#include <TPrsStd_AISViewer.hpp>
#include <AIS_InteractiveContext.hpp>

//=======================================================================
// function : DPrsStd_AISInitViewer
// purpose  : AISInitViewer (DOC)
//=======================================================================

static int DPrsStd_AISInitViewer(Draw_Interpretor& theDI, int theArgNb, const char** theArgVec)
{
  if (theArgNb != 2)
  {
    std::cout << "DPrsStd_AISInitViewer : Error\n";
    return 1;
  }

  occ::handle<TDocStd_Document> aDoc;
  if (!DDocStd::GetDocument(theArgVec[1], aDoc))
  {
    return 1;
  }

  TDF_Label                      aRoot = aDoc->GetData()->Root();
  occ::handle<TPrsStd_AISViewer> aDocViewer;
  TCollection_AsciiString        aViewName =
    TCollection_AsciiString("Driver1/Document_") + theArgVec[1] + "/View1";
  if (!TPrsStd_AISViewer::Find(aRoot, aDocViewer))
  {
    ViewerTest::ViewerInit(aViewName);
    aDocViewer = TPrsStd_AISViewer::New(aRoot, ViewerTest::GetAISContext());
  }

  DDF::ReturnLabel(theDI, aDocViewer->Label());
  return 0;
}

//=================================================================================================

static int DPrsStd_AISRepaint(Draw_Interpretor& di, int nb, const char** arg)
{
  if (nb == 2)
  {
    occ::handle<TDocStd_Document> D;
    if (!DDocStd::GetDocument(arg[1], D))
      return 1;
    TDF_Label acces = D->GetData()->Root();
    TPrsStd_AISViewer::Update(acces);
    return 0;
  }
  di << "DPrsStd_AISRepaint : Error\n";
  return 1;
}

//=================================================================================================

void DPrsStd::AISViewerCommands(Draw_Interpretor& theCommands)
{

  static bool done = false;
  if (done)
    return;
  done          = true;
  const char* g = "DPrsStd : standard presentation commands";

  // standard commands working on AISViewer

  theCommands.Add("AISInitViewer", "AISInitViewer (DOC)", __FILE__, DPrsStd_AISInitViewer, g);

  theCommands.Add("AISRepaint", "update the AIS viewer", __FILE__, DPrsStd_AISRepaint, g);
}
