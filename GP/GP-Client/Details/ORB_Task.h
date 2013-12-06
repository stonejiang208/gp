// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2012-10-17 14:06:45 by jiangtao> */

/* @file ORB_Task.h
 * $Id: ORB_Task.h 2012/10/17 06:04:33 jiangtao Exp $
 *
 * @author:Stone Jiang<jiangtao@tao-studio.net>
 */
//===========================================================================

#ifndef ORB_TASK_H
#define ORB_TASK_H

#include "ace/Task.h"
#include "tao/ORB.h"
#include "tao/PortableServer/POAC.h"

class ORB_Task : public ACE_Task_Base
{
public:
  ORB_Task( ACE_UINT32 num_threads = 1);
  void orb(CORBA::ORB_ptr orb);
  void poa(PortableServer::POA_ptr poa);
  virtual ~ORB_Task();
  virtual int open (void*);
  virtual int svc();
  virtual int close (u_long);
  void shutdown();
private:
  CORBA::ORB_var orb_;
  PortableServer::POA_var root_poa_;
  ACE_UINT32 num_threads_;
};

#endif /* ORB_TASK_H */
