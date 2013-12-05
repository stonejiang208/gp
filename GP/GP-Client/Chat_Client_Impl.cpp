// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-03-13 15:49:41 by jiangtao> */

/* @file Chat_Client_Impl.cpp
 * $Id: Chat_Client_Impl.cpp 2013/03/13 07:49:40 jiangtao Exp $
 *
 * @author:Jiangtao<jiangtao@tao-studio.net>
 */
//===========================================================================

#include "ace/OS_NS_stdio.h"
#include "Chat_Client_Impl.h"
 


Chat_Client_Impl::Chat_Client_Impl()
	:listener_(0)
{

}

Chat_Client_Impl::~Chat_Client_Impl()
{

}

int Chat_Client_Impl::init( int argc, ACE_TCHAR* argv[] )
{
	try 
	{
	  orb_ = CORBA::ORB_init(argc, argv);
	  CORBA::Object_var poa_object =
		  orb_->resolve_initial_references ("RootPOA");
	  if (CORBA::is_nil(poa_object.in()))
		  ACE_ERROR_RETURN ((LM_ERROR,
		  ACE_TEXT ("(%t|%T) Unable to initialize the POA.\n")),
		  1);

	  PortableServer::POA_var root_poa =
		  PortableServer::POA::_narrow (poa_object.in());

	  PortableServer::POAManager_var poa_manager =
		  root_poa->the_POAManager();

	  // Policies for the childPOA to be created.
	  CORBA::PolicyList policies (1);
	  policies.length (1);

	  CORBA::Any pol;
	  pol <<= BiDirPolicy::BOTH;
	  policies[0] =
		  orb_->create_policy(BiDirPolicy::BIDIRECTIONAL_POLICY_TYPE,
		  pol);

	  // Creae POA as child of RootPOA with the above policies. This POA
	  // will receive request in the same connection in which it sent
	  // the request

	  child_poa_ =
		  root_poa->create_POA ("childPOA",
		  poa_manager.in(),
		  policies);
	  // Creation of childPOA is over. Destroy the Policy objects.
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

void Chat_Client_Impl::run()
{
  this->orb_task_.open(0);

}

void Chat_Client_Impl::shutdown()
{
 this->orb_task_.shutdown();
}

int Chat_Client_Impl::join( const char* nick_name )
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

    GP::Game_Platform_var game =
      GP::Game_Platform::_narrow (object.in());

    client_impl = new  AMH_Client_Node_i(this) ;
    PortableServer::ServantBase_var servant(client_impl);

    PortableServer::ObjectId_var id =
      child_poa_->activate_object (client_impl);
    CORBA::Object_var object_player =
      child_poa_->id_to_reference (id.in());
    GP::Client_Node_var client = GP::Client_Node::_unchecked_narrow(object_player.in());

    
  }
  catch (CORBA::Exception &ex)
  {
    ex._tao_print_exception("ORB init");
    return -1;
  }
  if (this->listener_)
  {
    this->listener_->online();
  }
	return 0;
}

int Chat_Client_Impl::quit()
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

int Chat_Client_Impl::send_message( int room_id, const char* msg )
{	 
	try
	{		 
		this->user_node_->message(room_id,msg);
	}	
	catch (CORBA::Exception& e)
	{
    if (this->listener_)
    {
      this->listener_->offline();
    }
		e._tao_print_exception("send_message()");
	}
	
	return 0;
}

int Chat_Client_Impl::send_data( int, const void* data, size_t length )
{
	return 0;
}

void Chat_Client_Impl::listener( Chat_Listener* l )
{
   
   this->listener_ = l;
}

Chat_Listener* Chat_Client_Impl::listener( void )
{
  return this->listener_;
}

