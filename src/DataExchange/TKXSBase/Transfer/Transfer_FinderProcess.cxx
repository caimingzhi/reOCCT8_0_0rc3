

#include <Interface_Check.hpp>
#include <Interface_MSG.hpp>
#include <Transfer_FinderProcess.hpp>
#include <Transfer_TransientMapper.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Transfer_FinderProcess, Transfer_ProcessForFinder)

Transfer_FinderProcess::Transfer_FinderProcess(const int nb)
    : Transfer_ProcessForFinder(nb)
{
}

void Transfer_FinderProcess::SetModel(const occ::handle<Interface_InterfaceModel>& model)
{
  themodel = model;
}

occ::handle<Interface_InterfaceModel> Transfer_FinderProcess::Model() const
{
  return themodel;
}

int Transfer_FinderProcess::NextMappedWithAttribute(const char* name, const int num0) const
{
  int num, nb = NbMapped();
  for (num = num0 + 1; num <= nb; num++)
  {
    occ::handle<Transfer_Finder> fnd = Mapped(num);
    if (fnd.IsNull())
      continue;
    if (!fnd->Attribute(name).IsNull())
      return num;
  }
  return 0;
}

occ::handle<Transfer_TransientMapper> Transfer_FinderProcess::TransientMapper(
  const occ::handle<Standard_Transient>& obj) const
{
  occ::handle<Transfer_TransientMapper> mapper = new Transfer_TransientMapper(obj);
  int                                   index  = MapIndex(mapper);
  if (index == 0)
    return mapper;
  return occ::down_cast<Transfer_TransientMapper>(Mapped(index));
}

void Transfer_FinderProcess::PrintTrace(const occ::handle<Transfer_Finder>& start,
                                        Standard_OStream&                   S) const
{
  if (!start.IsNull())
    S << " Type:" << start->ValueTypeName();
}

void Transfer_FinderProcess::PrintStats(const int mode, Standard_OStream& S) const
{
  S << "\n*******************************************************************\n";
  if (mode == 1)
  {
    S << "********                 Basic Statistics                  ********" << std::endl;

    int nbr = 0, nbe = 0, nbw = 0;
    int i, max = NbMapped(), nbroots = NbRoots();
    S << "****        Nb Final Results    : " << nbroots << std::endl;

    for (i = 1; i <= max; i++)
    {
      const occ::handle<Transfer_Binder>& binder = MapItem(i);
      if (binder.IsNull())
        continue;
      const occ::handle<Interface_Check> ach  = binder->Check();
      Transfer_StatusExec                stat = binder->StatusExec();
      if (stat != Transfer_StatusInitial && stat != Transfer_StatusDone)
        nbe++;
      else
      {
        if (ach->NbWarnings() > 0)
          nbw++;
        if (binder->HasResult())
          nbr++;
      }
    }
    if (nbr > nbroots)
      S << "****      ( Itermediate Results : " << nbr - nbroots << " )\n";
    if (nbe > 0)
      S << "****                  Errors on :" << Interface_MSG::Blanks(nbe, 4) << nbe
        << " Entities\n";
    if (nbw > 0)
      S << "****                Warnings on : " << Interface_MSG::Blanks(nbw, 4) << nbw
        << " Entities\n";
    S << "*******************************************************************";
  }
  S << std::endl;
}
