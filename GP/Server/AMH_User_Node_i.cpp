// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-03-14 15:57:33 by jiangtao> */

/* @file AMH_User_Node_i.cpp
 * $Id: AMH_User_Node_i.cpp 2013/03/14 07:57:32 jiangtao Exp $
 *
 * @author:Jiangtao<jiangtao@tao-studio.net>
 */
//===========================================================================

#include "ace/Log_Msg.h"
#include "ace/streams.h"
#include "AMI_Client_Handler.h"
#include "AMH_User_Node_i.h"
#include "Lobby.h"
#include "AMH_Game_Platform_i.h"
#include "Options.h"
 

AMH_User_Node_i::AMH_User_Node_i(::GP::User_Id a_id)
  :id_ (a_id)
{
  ACE_DEBUG ((LM_DEBUG,
    ACE_TEXT ("(%t|%T) AMH_User_Node_i::AMH_User_Node_i(%d)\n"),id_));
}

AMH_User_Node_i::~AMH_User_Node_i()
{
  ACE_DEBUG ((LM_DEBUG,
    ACE_TEXT ("(%t|%T) AMH_User_Node_i::~AMH_User_Node_i(%d)\n"),id_));
}


void AMH_User_Node_i::message(
  GP::AMH_User_NodeResponseHandler_ptr _tao_rh, 
  ::GP::Room_Id a_id, 
  const char * a_message )
{
  ACE_DEBUG ((LM_DEBUG,
    ACE_TEXT ("(%t|%T) AMH_User_Node_i::message(%d,%s)\n"),
    a_id,a_message));

 _tao_rh->message();  

}


void AMH_User_Node_i::quit( GP::AMH_User_NodeResponseHandler_ptr _tao_rh )
{
  ACE_DEBUG ((LM_DEBUG,
    ACE_TEXT ("(%t|%T) AMH_User_Node_i::quit ()\n")));
  _tao_rh->quit();
  LOBBY::instance()->unbind_user_node(this->id_);
}


void AMH_User_Node_i::enter_room(
  GP::AMH_User_NodeResponseHandler_ptr _tao_rh, 
  ::GP::Room_Id new_room_id )
{

  ACE_DEBUG ((LM_DEBUG,
    ACE_TEXT ("(%t|%T) AMH_User_Node_i::enter_room (%d)\n"),new_room_id));
    

  _tao_rh->enter_room();
 
}

void AMH_User_Node_i::leave_room( 
  GP::AMH_User_NodeResponseHandler_ptr _tao_rh)
{
  
  _tao_rh->leave_room();
 
}


