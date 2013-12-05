// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-11-24 18:39:46 by jiangtao> */

/* @file AMH_Game_Platform_i.cpp
* $Id: AMH_Game_Platform_i.cpp 2012/10/21 06:21:24 jiangtao Exp $
*
* @author:Stone Jiang<jiangtao@tao-studio.net>
*/
//===========================================================================


#include "ace/ACE.h"
#include "ace/Log_Msg.h"
#include "ace/OS_NS_stdlib.h"
#include "ace/OS_NS_time.h"
#include "tao/TransportCurrent/TC_IIOPC.h"
#include "tao/TransportCurrent/TCC.h"
#include "ace/OS_NS_sys_time.h"
#include "AMH_Game_Platform_i.h"
#include "AMH_User_Node_i.h"
#include "AMH_Platform_Node_i.h"

#include "AMI_Client_Handler.h"
#include "Lobby.h"
 

AMH_Game_Platform_i::AMH_Game_Platform_i()
{
  ACE_DEBUG ((LM_DEBUG,
    ACE_TEXT ("(%t|%T) AMH_Game_Platform_i::AMH_Game_Platform_i()\n")));
  ACE_OS::srand((u_int) ACE_OS::time (0));
  LOBBY::instance()->set_platform(this);
}

AMH_Game_Platform_i::~AMH_Game_Platform_i()
{
  ACE_DEBUG ((LM_DEBUG,
    ACE_TEXT ("(%t|%T) AMH_Game_Platform_i::~AMH_Game_Platform_i()\n")));
}

void AMH_Game_Platform_i::orb(CORBA :: ORB_ptr o)
{
  this->orb_ = CORBA::ORB::_duplicate (o);
}

CORBA::ORB_ptr AMH_Game_Platform_i::orb()
{
  return CORBA::ORB::_duplicate (this->orb_.in());
}

void AMH_Game_Platform_i::poa(PortableServer :: POA_ptr p)
{
  this->poa_ = PortableServer::POA::_duplicate (p);
}

PortableServer::POA_ptr AMH_Game_Platform_i::poa()
{
  return PortableServer::POA::_duplicate (poa_.in());
}

void AMH_Game_Platform_i::create_user(
  GP::AMH_Game_PlatformResponseHandler_ptr _tao_rh,
  ::GP::Client_Node_ptr a_client_node )
{
  ACE_DEBUG ((LM_DEBUG,
      ACE_TEXT ("(%t|%T) AMH_Game_Platform_i::create_user ()\n")));
  CORBA::ULong user_id  = ACE::hash_pjw("user_uuid");

  AMH_User_Node_i* user_node_impl = new AMH_User_Node_i (user_id);
  PortableServer::ServantBase_var servant(user_node_impl);

  PortableServer::ObjectId_var id =
    this->poa_->activate_object ( user_node_impl);
  CORBA::Object_var object = this->poa_->id_to_reference (id.in());
  GP::User_Node_var user_node = GP::User_Node::_narrow (object.in());
  _tao_rh->create_user (user_node.in());

  LOBBY::instance()->bind_user_node (user_id,user_node_impl);

}

void AMH_Game_Platform_i::finalize()
{
}



void AMH_Game_Platform_i::deactive_user_node( AMH_User_Node_i* user_node )
{
  PortableServer::ObjectId_var oid =
    this->poa_->servant_to_id(user_node);
  this->poa_->deactivate_object(oid);
}
