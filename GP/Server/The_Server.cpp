// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2012-11-02 22:59:06 by jiangtao> */

/* @file The_Server.cpp
 * $Id: The_Server.cpp 2012/10/15 14:45:07 jiangtao Exp $
 *
 * @author:Stone Jiang<jiangtao@tao-studio.net>
 */
//===========================================================================


#include "The_Server.h"

#include "ace/Get_Opt.h"
#include "ace/Arg_Shifter.h"
#include "ace/Service_Config.h"
#include "ace/Reactor.h"
#include "tao/ORB_Core.h"
#include "tao/BiDir_GIOP/BiDirGIOP.h"
#include "tao/AnyTypeCode/Any.h"
#include "tao/Messaging/Messaging.h"

#include "tao/IORTable/IORTable.h"
#include <orbsvcs/Shutdown_Utilities.h>
#include <string>
#include "ORB_Task.h"
#include "Options.h"

The_Server::The_Server( int argc, ACE_TCHAR *argv[] )
  :argv_converter_ (argc, argv) 
  ,finalized_(false)
  , lock_()
  , cond_(lock_)
  , shutdown_complete_(false)
{
  try 
  {
    OPTIONS::instance();
    this->init();
  } catch (...) 
  {
    this->finalize();
    throw;
  }
}


void The_Server::init()
{
  ACE_Argv_Type_Converter cvt (this->argv_converter_.get_argc(),
                               this->argv_converter_.get_ASCII_argv());
  this->orb_ = CORBA::ORB_init(cvt.get_argc(), cvt.get_ASCII_argv(), "");

  this->servant_ = new The_Server::Servant();
  this->servant_->orb(this->orb_.in());
  PortableServer::ServantBase_var servant(this->servant_);
  CORBA::Object_var obj =
    this->orb_->resolve_initial_references("RootPOA");
  PortableServer::POA_var root_poa = PortableServer::POA::_narrow(obj);
  this->servant_->poa(root_poa.in());

  PortableServer::POAManager_var poa_manager = root_poa->the_POAManager();

  // Use persistent and user id POA policies so the Info Repo's
  // object references are consistent.
  
  CORBA::PolicyList policies(3);
  policies.length(3);
  policies[0] = root_poa->create_id_assignment_policy(PortableServer::USER_ID);
  policies[1] = root_poa->create_lifespan_policy(PortableServer::PERSISTENT);
  CORBA::Any pol;
  pol <<= BiDirPolicy::BOTH;
  policies[2] =
    this->orb_->create_policy (BiDirPolicy::BIDIRECTIONAL_POLICY_TYPE,
                               pol);


  PortableServer::POA_var info_poa = root_poa->create_POA("Game_Platform",
    poa_manager,
    policies);

  poa_manager->activate();

  // Creation of the new POAs over, so destroy the Policy_ptr's.
  for (CORBA::ULong i = 0; i < policies.length(); ++i) 
  {
    policies[i]->destroy();
  }


  PortableServer::ObjectId_var oid =
    PortableServer::string_to_ObjectId("Game_Platform");
  info_poa->activate_object_with_id(oid, this->servant_);
  obj = info_poa->id_to_reference(oid);
  GP::Game_Platform_var game_platform =
    GP::Game_Platform::_unchecked_narrow(obj.in());

  if (this->naming_client_.init (this->orb_.in ()) == -1)
  {
    throw InitError("Unable to find the naming service.");
  }
  CosNaming::Name bindName;
  bindName.length (1);
  bindName[0].id = CORBA::string_dup ("Game_Platform");
  try
  {
    naming_client_->rebind (bindName,
                            game_platform.in());
  }
  catch (const CosNaming::NamingContext::AlreadyBound&)
  {

    throw InitError("Unable to bind naming service.");
  }
#if 0
  int return_code = 0;
  return_code = ACE_Service_Config::process_directive(
    ACE_DYNAMIC_SERVICE_DIRECTIVE("TAO_Transport_IIOP_Current_Loader",
    "TAO_TC_IIOP",
    "_make_TAO_Transport_IIOP_Current_Loader",
    ""
    )
    );
  if (return_code != 0)
  {
    ACE_DEBUG((LM_DEBUG,ACE_TEXT("(%T|%t) Load Transport IIOP_Current Error\n")));
    return ;
  }
#endif
  ACE_DEBUG((LM_DEBUG,
             ACE_TEXT ("(%t|%T) Server is ready....\n")));
}



void The_Server::run()
{
  this->shutdown_complete_ = false;
  ORB_Task orb_task (this->orb_.in(),4);
  orb_task.open(0);
  orb_task.wait();
  this->finalize();
  ACE_GUARD(ACE_Thread_Mutex, g, this->lock_);
  this->shutdown_complete_ = true;
  this->cond_.signal();
}

void The_Server::finalize()
{
  if (this->finalized_) 
  {
    return;
  }

  if (!CORBA::is_nil(this->orb_)) 
  {
    this->orb_->destroy();
  }

  this->finalized_ = true;
}

void The_Server::shutdown()
{
  this->orb_->orb_core()->reactor()->notify(this);
}

int The_Server::handle_exception( ACE_HANDLE /*fd = ACE_INVALID_HANDLE*/ )
{
  this->servant_->finalize();
  this->orb_->shutdown(true);
  return 0;
}


My_Service_Shutdown::My_Service_Shutdown (The_Server & svc)
  :svc_ (svc)
{}

void My_Service_Shutdown::operator() (int which_signal)
{
  ACE_DEBUG ((LM_DEBUG,
              ACE_TEXT ("(%t|%T) The Server: shutting down on signal %d\n"),
              which_signal));
  (void) this->svc_.shutdown();
}

