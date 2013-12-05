// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2012-11-02 22:58:34 by jiangtao> */

/* @file The_Server.h
 * $Id: The_Server.h 2012/10/15 14:44:38 jiangtao Exp $
 *
 * @author:Stone Jiang<jiangtao@tao-studio.net>
 */
//===========================================================================

#ifndef THE_SERVER_H
#define THE_SERVER_H
#include <string>
#include "AMH_Game_Platform_i.h"
#include "ace/Event_Handler.h"
#include "ace/Condition_Thread_Mutex.h"
#include "ace/Argv_Type_Converter.h"

#include "tao/ORB_Core.h"
#include "orbsvcs/Naming/Naming_Client.h"
#include "ShutdownInterface.h"

class The_Server
  : public ShutdownInterface, public ACE_Event_Handler
{
  typedef AMH_Game_Platform_i Servant;

public:
  struct InitError {
    InitError(const char* msg)
      : msg_(msg) {};
    std::string msg_;
  };
public:
  The_Server(int argc, ACE_TCHAR *argv[]);
  void shutdown();
  void run();
  virtual int handle_exception(ACE_HANDLE fd = ACE_INVALID_HANDLE);
private:
  void init();
  void finalize();
  ACE_Argv_Type_Converter argv_converter_;
  bool finalized_;
  ACE_Thread_Mutex lock_;
  ACE_Condition_Thread_Mutex cond_;
  bool shutdown_complete_;

  CORBA::ORB_var orb_;
  Servant* servant_;
  TAO_Naming_Client naming_client_;


};


class My_Service_Shutdown : public Shutdown_Functor
{
public:
  My_Service_Shutdown(The_Server& svc);
  void operator() (int which_signal);
private:
  The_Server& svc_;
};


#endif /* THE_SERVER_H */
