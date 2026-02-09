#include <BOPAlgo_BOP.hpp>
#include <BOPAlgo_Builder.hpp>
#include <BOPAlgo_PaveFiller.hpp>
#include <BOPAlgo_Section.hpp>
#include <BOPTest_Objects.hpp>
#include <BOPAlgo_CellsBuilder.hpp>
#include <BOPAlgo_Splitter.hpp>
#include <NCollection_BaseAllocator.hpp>
#include <Precision.hpp>

static occ::handle<NCollection_BaseAllocator>& Allocator1();

class BOPTest_Session
{
public:
  BOPTest_Session() { Init(); };

  ~BOPTest_Session() { Clear(); };

  void Init()
  {
    occ::handle<NCollection_BaseAllocator> pA1, pA2;

    pA1 = NCollection_BaseAllocator::CommonBaseAllocator();
    pA2 = NCollection_BaseAllocator::CommonBaseAllocator();

    myPaveFiller     = new BOPAlgo_PaveFiller(pA1);
    myBuilderDefault = new BOPAlgo_Builder(pA2);

    myBuilder = myBuilderDefault;
    SetDefaultOptions();
  };

  void Clear()
  {
    if (myPaveFiller)
    {
      delete myPaveFiller;
      myPaveFiller = nullptr;
    }

    if (myBuilderDefault)
    {
      delete myBuilderDefault;
      myBuilderDefault = nullptr;
    }
  };

  bool IsValid() const { return (myPaveFiller != nullptr); }

  BOPAlgo_PaveFiller& PaveFiller() { return *myPaveFiller; };

  BOPAlgo_Builder& Builder() { return *myBuilder; };

  void SetBuilder(BOPAlgo_Builder* pBuilder) { myBuilder = pBuilder; };

  void SetBuilderDefault() { myBuilder = myBuilderDefault; };

  NCollection_List<TopoDS_Shape>& Shapes() { return myShapes; }

  NCollection_List<TopoDS_Shape>& Tools() { return myTools; }

  void SetDefaultOptions()
  {
    myRunParallel    = false;
    myNonDestructive = false;
    myFuzzyValue     = Precision::Confusion();
    myGlue           = BOPAlgo_GlueOff;
    myDrawWarnShapes = false;
    myCheckInverted  = true;
    myUseOBB         = false;
    myUnifyEdges     = false;
    myUnifyFaces     = false;
    myAngTol         = Precision::Angular();
  }

  void SetRunParallel(const bool bFlag) { myRunParallel = bFlag; };

  bool RunParallel() const { return myRunParallel; };

  void SetFuzzyValue(const double aValue) { myFuzzyValue = aValue; };

  double FuzzyValue() const { return myFuzzyValue; };

  void SetNonDestructive(const bool theFlag) { myNonDestructive = theFlag; };

  bool NonDestructive() const { return myNonDestructive; };

  void SetGlue(const BOPAlgo_GlueEnum theGlue) { myGlue = theGlue; };

  BOPAlgo_GlueEnum Glue() const { return myGlue; };

  void SetDrawWarnShapes(const bool bDraw) { myDrawWarnShapes = bDraw; };

  bool DrawWarnShapes() const { return myDrawWarnShapes; };

  void SetCheckInverted(const bool bCheck) { myCheckInverted = bCheck; };

  bool CheckInverted() const { return myCheckInverted; };

  void SetUseOBB(const bool bUse) { myUseOBB = bUse; };

  bool UseOBB() const { return myUseOBB; };

  void SetUnifyEdges(const bool bUE) { myUnifyEdges = bUE; }

  bool UnifyEdges() const { return myUnifyEdges; }

  void SetUnifyFaces(const bool bUF) { myUnifyFaces = bUF; }

  bool UnifyFaces() const { return myUnifyFaces; }

  void SetAngular(const double theAngTol) { myAngTol = theAngTol; }

  double Angular() const { return myAngTol; }

protected:
  BOPTest_Session(const BOPTest_Session&);
  BOPTest_Session& operator=(const BOPTest_Session&);

protected:
  BOPAlgo_PaveFiller* myPaveFiller;
  BOPAlgo_Builder*    myBuilder;
  BOPAlgo_Builder*    myBuilderDefault;

  NCollection_List<TopoDS_Shape> myShapes;
  NCollection_List<TopoDS_Shape> myTools;
  bool                           myRunParallel;
  bool                           myNonDestructive;
  double                         myFuzzyValue;
  BOPAlgo_GlueEnum               myGlue;
  bool                           myDrawWarnShapes;
  bool                           myCheckInverted;
  bool                           myUseOBB;
  bool                           myUnifyEdges;
  bool                           myUnifyFaces;
  double                         myAngTol;
};

static BOPTest_Session& GetSession()
{
  static BOPTest_Session* pSession = new BOPTest_Session;

  if (!pSession->IsValid())
  {
    pSession->Init();
  }
  return *pSession;
}

void BOPTest_Objects::Init()
{
  GetSession().Init();
}

void BOPTest_Objects::Clear()
{
  GetSession().Clear();
  Shapes().Clear();
  Tools().Clear();
}

BOPAlgo_PaveFiller& BOPTest_Objects::PaveFiller()
{
  return GetSession().PaveFiller();
}

BOPDS_PDS BOPTest_Objects::PDS()
{
  return BOPTest_Objects::PaveFiller().PDS();
}

BOPAlgo_Builder& BOPTest_Objects::Builder()
{
  return GetSession().Builder();
}

void BOPTest_Objects::SetBuilder(const BOPAlgo_PBuilder& theBuilder)
{
  BOPAlgo_Builder* pB;

  pB = (BOPAlgo_Builder*)theBuilder;
  GetSession().SetBuilder(pB);
}

void BOPTest_Objects::SetBuilderDefault()
{
  GetSession().SetBuilderDefault();
}

BOPAlgo_BOP& BOPTest_Objects::BOP()
{
  static BOPAlgo_BOP sBOP(Allocator1());
  return sBOP;
}

BOPAlgo_Section& BOPTest_Objects::Section()
{
  static BOPAlgo_Section sSection(Allocator1());
  return sSection;
}

BOPAlgo_CellsBuilder& BOPTest_Objects::CellsBuilder()
{
  static BOPAlgo_CellsBuilder sCBuilder(Allocator1());
  return sCBuilder;
}

BOPAlgo_Splitter& BOPTest_Objects::Splitter()
{
  static BOPAlgo_Splitter aSplitter(Allocator1());
  return aSplitter;
}

NCollection_List<TopoDS_Shape>& BOPTest_Objects::Shapes()
{
  return GetSession().Shapes();
}

NCollection_List<TopoDS_Shape>& BOPTest_Objects::Tools()
{
  return GetSession().Tools();
}

void BOPTest_Objects::SetDefaultOptions()
{
  GetSession().SetDefaultOptions();
}

void BOPTest_Objects::SetRunParallel(const bool bFlag)
{
  GetSession().SetRunParallel(bFlag);
}

bool BOPTest_Objects::RunParallel()
{
  return GetSession().RunParallel();
}

void BOPTest_Objects::SetFuzzyValue(const double aValue)
{
  GetSession().SetFuzzyValue(aValue);
}

double BOPTest_Objects::FuzzyValue()
{
  return GetSession().FuzzyValue();
}

void BOPTest_Objects::SetNonDestructive(const bool theFlag)
{
  GetSession().SetNonDestructive(theFlag);
}

bool BOPTest_Objects::NonDestructive()
{
  return GetSession().NonDestructive();
}

void BOPTest_Objects::SetGlue(const BOPAlgo_GlueEnum theGlue)
{
  GetSession().SetGlue(theGlue);
}

BOPAlgo_GlueEnum BOPTest_Objects::Glue()
{
  return GetSession().Glue();
}

void BOPTest_Objects::SetDrawWarnShapes(const bool bDraw)
{
  GetSession().SetDrawWarnShapes(bDraw);
}

bool BOPTest_Objects::DrawWarnShapes()
{
  return GetSession().DrawWarnShapes();
}

void BOPTest_Objects::SetCheckInverted(const bool bCheck)
{
  GetSession().SetCheckInverted(bCheck);
}

bool BOPTest_Objects::CheckInverted()
{
  return GetSession().CheckInverted();
}

void BOPTest_Objects::SetUseOBB(const bool bUseOBB)
{
  GetSession().SetUseOBB(bUseOBB);
}

bool BOPTest_Objects::UseOBB()
{
  return GetSession().UseOBB();
}

void BOPTest_Objects::SetUnifyEdges(const bool bUE)
{
  GetSession().SetUnifyEdges(bUE);
}

bool BOPTest_Objects::UnifyEdges()
{
  return GetSession().UnifyEdges();
}

void BOPTest_Objects::SetUnifyFaces(const bool bUF)
{
  GetSession().SetUnifyFaces(bUF);
}

bool BOPTest_Objects::UnifyFaces()
{
  return GetSession().UnifyFaces();
}

void BOPTest_Objects::SetAngular(const double theAngTol)
{
  GetSession().SetAngular(theAngTol);
}

double BOPTest_Objects::Angular()
{
  return GetSession().Angular();
}

occ::handle<NCollection_BaseAllocator>& Allocator1()
{
  static occ::handle<NCollection_BaseAllocator> sAL1 =
    NCollection_BaseAllocator::CommonBaseAllocator();
  return sAL1;
}
