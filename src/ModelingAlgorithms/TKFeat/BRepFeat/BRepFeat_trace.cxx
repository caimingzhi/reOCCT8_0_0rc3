#ifdef OCCT_DEBUG

  #include <Standard_Type.hpp>

static bool BRepFeat_traceFEAT = true;

Standard_EXPORT void BRepFeat_SettraceFEAT(const bool b)
{
  BRepFeat_traceFEAT = b;
}

Standard_EXPORT bool BRepFeat_GettraceFEAT()
{
  return BRepFeat_traceFEAT;
}

static bool BRepFeat_traceFEATFORM = false;

Standard_EXPORT void BRepFeat_SettraceFEATFORM(const bool b)
{
  BRepFeat_traceFEATFORM = b;
}

Standard_EXPORT bool BRepFeat_GettraceFEATFORM()
{
  return BRepFeat_traceFEATFORM;
}

static bool BRepFeat_traceFEATPRISM = false;

Standard_EXPORT void BRepFeat_SettraceFEATPRISM(const bool b)
{
  BRepFeat_traceFEATPRISM = b;
}

Standard_EXPORT bool BRepFeat_GettraceFEATPRISM()
{
  return BRepFeat_traceFEATPRISM;
}

static bool BRepFeat_traceFEATRIB = false;

Standard_EXPORT void BRepFeat_SettraceFEATRIB(const bool b)
{
  BRepFeat_traceFEATRIB = b;
}

Standard_EXPORT bool BRepFeat_GettraceFEATRIB()
{
  return BRepFeat_traceFEATRIB;
}

static bool BRepFeat_traceFEATDRAFT = false;

Standard_EXPORT void BRepFeat_SettraceFEATDRAFT(const bool b)
{
  BRepFeat_traceFEATDRAFT = b;
}

Standard_EXPORT bool BRepFeat_GettraceFEATDRAFT()
{
  return BRepFeat_traceFEATDRAFT;
}

static bool BRepFeat_contextCHRONO = false;

Standard_EXPORT void BRepFeat_SetcontextCHRONO(const bool b)
{
  BRepFeat_contextCHRONO = b;
}

Standard_EXPORT bool BRepFeat_GetcontextCHRONO()
{
  bool b = BRepFeat_contextCHRONO;
  if (b)
    std::cout << "context (BRepFeat) CHRONO actif" << std::endl;
  return b;
}

#endif
