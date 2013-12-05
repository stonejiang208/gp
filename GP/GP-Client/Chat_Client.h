// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-11-24 14:36:46 by jiangtao> */

/* @file Chat_Client.h
 * $Id: Chat_Client.h 2013/03/13 06:23:43 jiangtao Exp $
 *
 * @author:Jiangtao<jiangtao@tao-studio.net>
 */
//===========================================================================

#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

#include "Chat_Listener.h"

class GP_Client_Export Chat_Client
{
public:
  Chat_Client();
  virtual ~Chat_Client();
  int init (int argc, ACE_TCHAR* argv[]);
  void run();
  void shutdown();
public:
  int join(const char* nick_name);
  int quit();
  int send_message(int, const char* msg);
  int send_data(int, const void* data, size_t length);
  int enter_room(int new_room);
  void listener(Chat_Listener* l);
  Chat_Listener* listener(void);
  Room_List get_room_list(int parent_id);
private:
  Chat_Client_Impl* impl_;
};

#endif /* CHAT_CLIENT_H */
