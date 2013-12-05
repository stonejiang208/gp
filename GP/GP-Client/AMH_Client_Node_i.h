// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-11-24 14:32:19 by jiangtao> */

/* @file AMH_Client_Node_i.h
 * $Id: AMH_Client_Node_i.h 2013/03/14 08:17:35 jiangtao Exp $
 *
 * @author:Jiangtao<jiangtao@tao-studio.net>
 */
//===========================================================================

#ifndef AMH_CLIENT_NODE_I_H
#define AMH_CLIENT_NODE_I_H

#include "Client_NodeS.h"

class Chat_Client_Impl;

class AMH_Client_Node_i : virtual public POA_GP::AMH_Client_Node
{
public:
  AMH_Client_Node_i(Chat_Client_Impl* client);

  virtual void message (
    GP::AMH_Client_NodeResponseHandler_ptr _tao_rh,
    ::GP::User_Id sender,
    const char * a_message,
    const ::GP::Message_Info & info
    );

private:
  Chat_Client_Impl* client_;
};

#endif /* AMH_CLIENT_NODE_I_H */
