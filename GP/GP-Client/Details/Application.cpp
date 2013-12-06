#include "Application.h"
#include "../Chat_Listener.h"
#include "ace/streams.h"
#include "tao/AnyTypeCode/Any.h"
#include "tao/BiDir_GIOP/BiDirGIOP.h"
#include "orbsvcs/CosNamingC.h"
#include "ace/CDR_Stream.h"
#include "ace/SString.h"
#include "ace/High_Res_Timer.h"
#include "ace/Thread_Manager.h"
#include "ace/Sched_Params.h"
#include "ace/Stats.h"
#include "ace/Throughput_Stats.h"
#include "ace/Sample_History.h"

namespace Details
{
  Application::Application( Chat_Listener* l)
    :listener_ (l)
  {
    //no-op
  }

  Application::~Application()
  {
    //no-op
  }

  int Application::init( int argc, ACE_TCHAR *argv[] )
  {   
    int retval = -1;
    retval = init_orb(argc,argv);
    system_message(retval,"init orb");
    if (retval != 0)
    {
      return -1;
    }
    retval = reslove_naming_service();
    system_message(retval,"reslove_naming_service");
    if (retval != 0)
    {
      return -1;
    }

    retval = init_client_node();
    system_message(retval,"init_client_node");
    if (retval != 0)
    {
      return -1;
    }
    return 0;
  }

  int Application::reslove_naming_service()
  {
    try 
    {
      CORBA::Object_var naming_context_object =
        orb_->resolve_initial_references ("NameService");
      CosNaming::NamingContext_var naming_context =
        CosNaming::NamingContext::_narrow (naming_context_object.in ());

      CosNaming::Name name (1);
      name.length (1);
      name[0].id = CORBA::string_dup ("Game_Platform");

      CORBA::Object_var object =
        naming_context->resolve (name);

      this->game_platform_ =
        GP::Game_Platform::_narrow (object.in());
      if (CORBA::is_nil(this->game_platform_.in()))
        ACE_ERROR_RETURN ((LM_ERROR,
        ACE_TEXT ("(%t|%T) Unable to get Game_Platform Object from Naming Service.\n")),
        1);      
    }
    catch (CORBA::Exception &ex)
    {
      ex._tao_print_exception("reslove_naming_service");
      return -1;
    }

    return 0;
  }

  int Application::run()
  {
    this->orb_task_.open(0);
    return 0;
  }

  void Application::system_message( int error_code, const char* desc )
  {
    this->listener_->on_system_message (error_code, desc);
  }

  int Application::init_orb(int argc, ACE_TCHAR *argv[])
  {
    try
    {
      this->orb_ = CORBA::ORB_init (argc, argv);
      CORBA::Object_var poa_object =
        this->orb_->resolve_initial_references("RootPOA");
      if (CORBA::is_nil(poa_object.in()))
        ACE_ERROR_RETURN ((LM_ERROR,
        ACE_TEXT ("(%t|%T) Unable to initialize the POA.\n")),
        1);
      PortableServer::POA_var root_poa =
        PortableServer::POA::_narrow (poa_object.in());
      PortableServer::POAManager_var poa_manager =
        root_poa->the_POAManager();

      CORBA::PolicyList policies (1);
      policies.length (1);

      CORBA::Any pol;
      pol <<= BiDirPolicy::BOTH;
      policies[0] =
        orb_->create_policy(BiDirPolicy::BIDIRECTIONAL_POLICY_TYPE,
        pol);

      child_poa_ =
        root_poa->create_POA ("childPOA",
        poa_manager.in(),
        policies);

      for (CORBA::ULong i = 0;
        i < policies.length ();
        ++i)
      {
        policies[i]->destroy ();
      }

      poa_manager->activate ();
      orb_task_.orb(this->orb_.in());
      orb_task_.poa (child_poa_.in());	  
    }
    catch (CORBA::Exception &ex)
    {
      ex._tao_print_exception("ORB init");
      return -1;
    }
   
    return 0;
  }

  int Application::init_client_node()
  {
    try
    {
      client_impl_ = new  AMH_Client_Node_i(this->listener_) ;
      PortableServer::ServantBase_var servant(client_impl_);

      PortableServer::ObjectId_var id =
        child_poa_->activate_object (client_impl_);
      CORBA::Object_var object_player =
        child_poa_->id_to_reference (id.in());
      GP::Client_Node_var client = 
        GP::Client_Node::_unchecked_narrow(object_player.in());

      user_node_ = this->game_platform_->create_user(client.in());
    }
    catch (CORBA::Exception &ex)
    {
      ex._tao_print_exception("init_client_node");
      return -1;
    }
    return 0;
  }

  int Application::quit()
  {
    try
    {
      this->user_node_->quit();
    }
    catch (CORBA::Exception& e)
    {
      e._tao_print_exception("quit()");
    }
    return 0;
  }
  void Application::shutdown()
  {
    this->orb_task_.shutdown();
  }

  int Application::send_message( int x, const char* msg )
  {
    try
    {		 
      this->user_node_->message(x,msg);
    }	
    catch (CORBA::Exception& e)
    {
      if (this->listener_)
      {
        this->listener_->offline();
      }
      e._tao_print_exception("send_message()");
      return -1;
    }
    return 0;
  }


};