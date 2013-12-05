// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-03-14 16:46:53 by jiangtao> */

/* @file Lobby.h
 * $Id: Lobby.h 2013/03/14 08:46:50 jiangtao Exp $
 *
 * @author:Jiangtao<jiangtao@tao-studio.net>
 */
//===========================================================================

#ifndef LOBBY_H
#define LOBBY_H
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"

#include "tao/PortableServer/POAC.h"
#include "CommonC.h"
#include "Server_NodeC.h"

#include <map>
#include <list>

class AMH_Game_Platform_i;
class AMH_User_Node_i;
class AMH_Platform_Node_i;


typedef std::map<GP::User_Id, AMH_User_Node_i*> Player_Map;
typedef std::map<GP::Room_Id, Player_Map*> Room_Map;
typedef std::list<int > My_List;
typedef std::map<GP::Location_Id, ::GP::Server_Node_ptr> Bomb_Server_Map; 
typedef std::map<GP::Room_Id, ::GP::Server_Node_ptr> Room_Server_Map; 

class Lobby
{
  friend class ACE_Singleton<Lobby, ACE_Null_Mutex>; 
public:
  Lobby();
  virtual ~Lobby();
 

private:
  AMH_Game_Platform_i*   platform_;
};

typedef ACE_Singleton<Lobby, ACE_Null_Mutex> LOBBY;
TimeBase::TimeT get_timestamp();
#endif /* LOBBY_H */