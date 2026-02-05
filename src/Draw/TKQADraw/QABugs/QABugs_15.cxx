#include <QABugs.hpp>

#include <Draw.hpp>
#include <Draw_Interpretor.hpp>
#include <AIS_InteractiveContext.hpp>
#include <ViewerTest.hpp>

#include <QABugs_PresentableObject.hpp>

occ::handle<QABugs_PresentableObject> theObject1 = nullptr;
occ::handle<QABugs_PresentableObject> theObject2 = nullptr;

static int BUC60720(Draw_Interpretor& di, int argc, const char** argv)
{
  occ::handle<AIS_InteractiveContext> myAISContext = ViewerTest::GetAISContext();
  if (myAISContext.IsNull())
  {
    di << "use 'vinit' command before " << argv[0] << "\n";
    return -1;
  }

  if (argc != 2)
  {
    di << "Usage : " << argv[0] << " 0/1\n";
  }

  if (Draw::Atoi(argv[1]) == 0)
  {
    if (theObject1.IsNull())
    {
      theObject1 = new QABugs_PresentableObject();
      theObject1->SetDisplayMode(0);
      myAISContext->Display(theObject1, true);
    }
  }
  else if (Draw::Atoi(argv[1]) == 1)
  {
    if (theObject2.IsNull())
    {
      theObject2 = new QABugs_PresentableObject();
      theObject2->SetDisplayMode(1);
      myAISContext->Display(theObject2, true);
    }
  }
  else
  {
    di << "Usage : " << argv[0] << " 0/1\n";
    return -1;
  }
  return 0;
}

void QABugs::Commands_15(Draw_Interpretor& theCommands)
{
  const char* group = "QABugs";
  theCommands.Add("BUC60720", "BUC60720 0/1", __FILE__, BUC60720, group);
}
