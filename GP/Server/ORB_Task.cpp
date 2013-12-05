// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2012-10-17 14:09:28 by jiangtao> */

/* @file ORB_Task.cpp
 * $Id: ORB_Task.cpp 2012/10/17 06:06:54 jiangtao Exp $
 *
 * @author:Stone Jiang<jiangtao@tao-studio.net>
 */
//===========================================================================


#include "ORB_Task.h"

namespace
{
  enum
  {
    MAX_ORB_TASK_WORKER_THREADS = 20  
  };
}



ORB_Task::ORB_Task(CORBA::ORB_ptr orb, unsigned num_threads)
  : orb_(CORBA::ORB::_duplicate(orb)),
    num_threads_(num_threads)
{
}


ORB_Task::~ORB_Task()
{
}


int
ORB_Task::open(void*)
{
  if (this->num_threads_ < 1)
    {
      ACE_ERROR_RETURN((LM_ERROR,
                        "(%t|%T) ORB_Task failed to open.  "
                        "num_threads_ (%d) is less-than 1.\n",
                        this->num_threads_),
                       -1);
    }

  if (this->num_threads_ > MAX_ORB_TASK_WORKER_THREADS)
    {
      ACE_ERROR_RETURN((LM_ERROR,
                        "(%t|%T) ORB_Task failed to open.  "
                        "num_threads_ (%d) is too large.  Max is %d.\n",
                        this->num_threads_, MAX_ORB_TASK_WORKER_THREADS),
                       -1);
    }

  if (CORBA::is_nil(this->orb_.in()))
    {
      ACE_ERROR_RETURN((LM_ERROR,
                        "(%t|%T) ORB_Task failed to open.  "
                        "ORB object reference is nil.\n"),
                        -1);
    }

  if (this->activate(THR_NEW_LWP | THR_JOINABLE, this->num_threads_) != 0)
    {
      // Assumes that when activate returns non-zero return code that
      // no threads were activated.
      ACE_ERROR_RETURN((LM_ERROR,
                        "(%t|%T) ORB_Task failed to activate "
                        "(%d) worker threads.\n",
                        this->num_threads_),
                       -1);
    }

  return 0;
}


int
ORB_Task::svc()
{
  try
  {
    this->orb_->run();
  }
  catch (...)
  {
    ACE_ERROR((LM_ERROR,
      "(%t|%T) Exception raised by ORB::run() method. "
      "ORB_Task is stopping.\n"));
  }

  return 0;
}


int
ORB_Task::close(u_long)
{
  return 0;
}

void ORB_Task::shutdown()
{
   this->orb_->destroy();
}


