// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-03-13 15:49:29 by jiangtao> */

/* @file Chat_Client_Impl.h
 * $Id: Chat_Client_Impl.h 2013/03/13 07:49:27 jiangtao Exp $
 *
 * @author:Jiangtao<jiangtao@tao-studio.net>
 */
//===========================================================================

#ifndef CHAT_CLIENT_IMPL_H
#define CHAT_CLIENT_IMPL_H
#include "Chat_Listener.h"
#include "Game_PlatformC.h"

#include "User_NodeC.h"
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
#include "ORB_Task.h"
#include "AMH_Client_Node_i.h"

class Chat_Client_Impl
{
public:
	Chat_Client_Impl();
	virtual ~Chat_Client_Impl();
	int init (int argc, ACE_TCHAR* argv[]);
	void run();
	void shutdown();
public:
	int join(const char* nick_name);
	int quit();
	int send_message(int, const char* msg);
	int send_data(int, const void* data, size_t length);
	void listener(Chat_Listener* l);
	Chat_Listener* listener(void);
  
private:
	Chat_Listener* listener_;
	CORBA::ORB_var orb_;
  PortableServer::POA_var child_poa_;
	ORB_Task       orb_task_;
  GP::User_Node_var  user_node_;
  AMH_Client_Node_i *client_impl;
  std::string id_;
};


#endif /* CHAT_CLIENT_IMPL_H */
