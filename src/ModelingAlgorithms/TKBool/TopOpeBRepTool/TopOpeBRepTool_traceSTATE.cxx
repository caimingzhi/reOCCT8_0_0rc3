#ifdef OCCT_DEBUG

  #include <Standard_Type.hpp>
  #include <TopOpeBRepTool_STATE.hpp>

static TopOpeBRepTool_STATE TopOpeBRepTool_CL3DDR("draw 3d classification states");
static TopOpeBRepTool_STATE TopOpeBRepTool_CL3DPR("print 3d classification states");
static TopOpeBRepTool_STATE TopOpeBRepTool_CL2DDR("draw 2d classification states");
static TopOpeBRepTool_STATE TopOpeBRepTool_CL2DPR("print 2d classification states");

Standard_EXPORT void TopOpeBRepTool_SettraceCL3DDR(const bool b, int narg, char** a)
{
  TopOpeBRepTool_CL3DDR.Set(b, narg, a);
}

Standard_EXPORT bool TopOpeBRepTool_GettraceCL3DDR(const TopAbs_State S)
{
  return TopOpeBRepTool_CL3DDR.Get(S);
}

Standard_EXPORT bool TopOpeBRepTool_GettraceCL3DDR()
{
  return TopOpeBRepTool_CL3DDR.Get();
}

Standard_EXPORT void TopOpeBRepTool_SettraceCL3DPR(const bool b, int narg, char** a)
{
  TopOpeBRepTool_CL3DPR.Set(b, narg, a);
}

Standard_EXPORT bool TopOpeBRepTool_GettraceCL3DPR(const TopAbs_State S)
{
  return TopOpeBRepTool_CL3DPR.Get(S);
}

Standard_EXPORT bool TopOpeBRepTool_GettraceCL3DPR()
{
  return TopOpeBRepTool_CL3DPR.Get();
}

Standard_EXPORT void TopOpeBRepTool_SettraceCL2DDR(const bool b, int narg, char** a)
{
  TopOpeBRepTool_CL2DDR.Set(b, narg, a);
}

Standard_EXPORT bool TopOpeBRepTool_GettraceCL2DDR(const TopAbs_State S)
{
  return TopOpeBRepTool_CL2DDR.Get(S);
}

Standard_EXPORT bool TopOpeBRepTool_GettraceCL2DDR()
{
  return TopOpeBRepTool_CL2DDR.Get();
}

Standard_EXPORT void TopOpeBRepTool_SettraceCL2DPR(const bool b, int narg, char** a)
{
  TopOpeBRepTool_CL2DPR.Set(b, narg, a);
}

Standard_EXPORT bool TopOpeBRepTool_GettraceCL2DPR(const TopAbs_State S)
{
  return TopOpeBRepTool_CL2DPR.Get(S);
}

Standard_EXPORT bool TopOpeBRepTool_GettraceCL2DPR()
{
  return TopOpeBRepTool_CL2DPR.Get();
}

#endif
