#pragma once

#include <Standard_TypeDef.hpp>
#include <AdvApp2Var_Data_f2c.hpp>

class AdvApp2Var_SysBase
{
public:
  Standard_EXPORT AdvApp2Var_SysBase();
  Standard_EXPORT ~AdvApp2Var_SysBase();

  Standard_EXPORT int mainial_();

  Standard_EXPORT static int macinit_(int*, int*);

  Standard_EXPORT int mcrdelt_(integer*  iunit,
                               integer*  isize,
                               void*     t,
                               intptr_t* iofset,
                               integer*  iercod);

  Standard_EXPORT static int mcrfill_(integer* size, void* tin, void* tout);

  Standard_EXPORT int            mcrrqst_(integer*  iunit,
                                          integer*  isize,
                                          void*     t,
                                          intptr_t* iofset,
                                          integer*  iercod);
  Standard_EXPORT static integer mnfndeb_();

  Standard_EXPORT static int do__fio();
  Standard_EXPORT static int do__lio();
  Standard_EXPORT int        macrai4_(integer*  nbelem,
                                      integer*  maxelm,
                                      integer*  itablo,
                                      intptr_t* iofset,
                                      integer*  iercod);
  Standard_EXPORT int        macrar8_(integer*    nbelem,
                                      integer*    maxelm,
                                      doublereal* xtablo,
                                      intptr_t*   iofset,
                                      integer*    iercod);
  Standard_EXPORT int        macrdi4_(integer*  nbelem,
                                      integer*  maxelm,
                                      integer*  itablo,
                                      intptr_t* iofset,
                                      integer*  iercod);

  Standard_EXPORT int        macrdr8_(integer*    nbelem,
                                      integer*    maxelm,
                                      doublereal* xtablo,
                                      intptr_t*   iofset,
                                      integer*    iercod);
  Standard_EXPORT static int maermsg_(const char* cnompg, integer* icoder, ftnlen cnompg_len);
  Standard_EXPORT static int maitbr8_(integer* itaill, doublereal* xtab, doublereal* xval);
  Standard_EXPORT static int maovsr8_(integer* ivalcs);
  Standard_EXPORT static int mgenmsg_(const char* nomprg, ftnlen nomprg_len);

  Standard_EXPORT static int  mgsomsg_(const char* nomprg, ftnlen nomprg_len);
  Standard_EXPORT static void miraz_(integer* taille, void* adt);
  Standard_EXPORT static int  msifill_(integer* nbintg, integer* ivecin, integer* ivecou);
  Standard_EXPORT static int  msrfill_(integer* nbreel, doublereal* vecent, doublereal* vecsor);
  Standard_EXPORT static int  mswrdbg_(const char* ctexte, ftnlen ctexte_len);
  Standard_EXPORT static void mvriraz_(integer* taille, void* adt);

private:
  int macrchk_();
  int mcrlist_(integer* ier) const;

  static const int MAX_ALLOC_NB = 32;

  enum
  {
    static_allocation = 0,
    heap_allocation   = 1
  };

  struct mitem
  {
    unsigned char prot;
    unsigned char unit;
    integer       reqsize;
    intptr_t      loc;
    intptr_t      offset;
    unsigned char alloctype;
    integer       size;
    intptr_t      addr;
    integer       userzone;
    intptr_t      startaddr;
    intptr_t      endaddr;
    integer       rank;
  };

  struct
  {
    mitem         icore[MAX_ALLOC_NB];
    integer       ncore;
    unsigned char lprot;
  } mcrgene_;

  struct
  {
    integer nrqst[2], ndelt[2], nbyte[2], mbyte[2];
  } mcrstac_;
};
