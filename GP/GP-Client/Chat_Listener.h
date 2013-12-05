// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-11-24 14:39:16 by jiangtao> */

/* @file Chat_Listener.h
 * $Id: Chat_Listener.h 2013/03/13 06:24:01 jiangtao Exp $
 *
 * @author:Jiangtao<jiangtao@tao-studio.net>
 */
//===========================================================================

#ifndef CHAT_LISTENER_H
#define CHAT_LISTENER_H
#include "GP_Client_export.h"

#include <string>
#include <vector>
class Chat_Client_Impl;
typedef std::vector<int> Room_List;

class GP_Client_Export Chat_Listener
{
public:
  Chat_Listener();
  virtual ~Chat_Listener();
  virtual void on_message(int, int sender, const char* message) = 0;
  virtual void on_data (int, int sender, const void* data, size_t length) = 0;
  virtual void online() = 0;
  virtual void offline() = 0;
};

#endif /* CHAT_LISTENER_H */
