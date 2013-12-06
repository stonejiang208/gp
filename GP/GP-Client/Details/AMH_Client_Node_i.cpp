// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-03-14 16:17:47 by jiangtao> */

/* @file AMH_Client_Node_i.cpp
 * $Id: AMH_Client_Node_i.cpp 2013/03/14 08:17:45 jiangtao Exp $
 *
 * @author:Jiangtao<jiangtao@tao-studio.net>
 */
//===========================================================================


#include "AMH_Client_Node_i.h"
#include "../Chat_Listener.h"
 

#include <stdio.h>
  
void AMH_Client_Node_i::message(
  GP::AMH_Client_NodeResponseHandler_ptr _tao_rh,
 ::GP::User_Id sender,
  const char * a_message,
  const ::GP::Message_Info & info)
{
   _tao_rh->message();
   printf (" AMH_Client_Node_i::message(%s)\n",a_message);
   
    client_->on_message(0,sender,a_message);
    
}

AMH_Client_Node_i::AMH_Client_Node_i( Chat_Listener* client )
  :client_ (client)
{

}
