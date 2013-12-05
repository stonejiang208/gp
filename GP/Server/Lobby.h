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
#include "User_NodeC.h"
#include <map>
#include <list>

class AMH_Game_Platform_i;
class AMH_User_Node_i;
class AMH_Platform_Node_i;

typedef std::map<GP::User_Id, AMH_User_Node_i*> User_Node_Map;

typedef std::map<GP::Room_Id, User_Node_Map*> Room_Map;
typedef std::list<int > My_List;
typedef std::map<GP::Location_Id, ::GP::Server_Node_ptr> Bomb_Server_Map; 
typedef std::map<GP::Room_Id, ::GP::Server_Node_ptr> Room_Server_Map; 

class Lobby
{
  friend class ACE_Singleton<Lobby, ACE_Null_Mutex>; 
public:
  Lobby();
  virtual ~Lobby();
 
public:
  static TimeBase::TimeT get_timestamp();
  void set_platform (AMH_Game_Platform_i* p);
  void bind_user_node (GP::User_Id id, AMH_User_Node_i* user_node);
  void unbind_user_node (GP::User_Id id);

public:
  void send_message_to_room (GP::Room_Id room_id, const char* msg);
private:
  AMH_Game_Platform_i*   platform_;
  User_Node_Map          user_node_map_;

 
};

typedef ACE_Singleton<Lobby, ACE_Null_Mutex> LOBBY;

#endif /* LOBBY_H */
