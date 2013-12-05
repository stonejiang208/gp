// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-11-24 15:33:36 by jiangtao> */

/* @file Lobby.cpp
 * $Id: Lobby.cpp 2013/03/14 08:46:57 jiangtao Exp $
 *
 * @author:Jiangtao<jiangtao@tao-studio.net>
 */
//===========================================================================


#include "Lobby.h"
#include "Options.h"
#include "AMH_Game_Platform_i.h"
#include "AMH_User_Node_i.h"
#include "AMH_Platform_Node_i.h"
#include "ace/Log_Msg.h"
#include "ace/OS_NS_stdio.h"
#include "orbsvcs/Time_Utilities.h"
#include "ace/streams.h"
 


TimeBase::TimeT get_timestamp()
{
  TimeBase::TimeT retval;
  ACE_hrtime_t t = ACE_OS::gethrtime ();
  ORBSVCS_Time::hrtime_to_TimeT (retval, t );
  return retval;
}


Lobby::Lobby()
  :platform_ (0)
{
  ACE_DEBUG ((LM_DEBUG,
    ACE_TEXT ("(%t|%T) Lobby::Lobby()\n")));
 
}

Lobby::~Lobby()
{
  ACE_DEBUG ((LM_DEBUG,
    ACE_TEXT ("(%t|%T) Lobby::~Lobby()\n")));
   
}

void Lobby::set_platform( AMH_Game_Platform_i* p )
{
  this->platform_ = p;
}

void Lobby::bind_user_node( GP::User_Id id, AMH_User_Node_i* user_node )
{
  ACE_DEBUG ((LM_DEBUG,
    ACE_TEXT ("(%t|%T) Lobby::bind_user_node (%d)\n"),id));
  this->user_node_map_[id] =user_node;
}

void Lobby::unbind_user_node( GP::User_Id id )
{
  ACE_DEBUG ((LM_DEBUG,
    ACE_TEXT ("(%t|%T) Lobby::unbind_user_node (%d)\n"),id));
  AMH_User_Node_i* user_node =  this->user_node_map_[id];
  this->platform_->deactive_user_node(user_node);
}










