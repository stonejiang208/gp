// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-03-14 15:57:22 by jiangtao> */

/* @file AMH_User_Node_i.h
 * $Id: AMH_User_Node_i.h 2013/03/14 07:57:18 jiangtao Exp $
 *
 * @author:Jiangtao<jiangtao@tao-studio.net>
 */
//===========================================================================

#ifndef AMH_USER_NODE_I_H
#define AMH_USER_NODE_I_H

#include "User_NodeS.h"
#include <string>

class AMH_User_Node_i 
  : virtual public POA_GP::AMH_User_Node
{
public:
  AMH_User_Node_i( ::GP::User_Id a_id);
  virtual ~AMH_User_Node_i();
  virtual void message (
    GP::AMH_User_NodeResponseHandler_ptr _tao_rh,
    ::GP::Room_Id a_id,
    const char * a_message
    );

  virtual void enter_room (
    GP::AMH_User_NodeResponseHandler_ptr _tao_rh,
    ::GP::Room_Id new_room_id
    );
  virtual void leave_room (
    GP::AMH_User_NodeResponseHandler_ptr _tao_rh
    );
  virtual void quit (
    GP::AMH_User_NodeResponseHandler_ptr _tao_rh
    );
  
private:
  GP::User_Id  id_;
};


#endif /* AMH_USER_NODE_I_H */
