// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-03-14 17:36:23 by jiangtao> */

/* @file AMI_Client_Handler.h
 * $Id: AMI_Client_Handler.h 2013/03/14 09:35:28 jiangtao Exp $
 *
 * @author:Jiangtao<jiangtao@tao-studio.net>
 */
//===========================================================================

#ifndef AMI_CLIENT_HANDLER_H
#define AMI_CLIENT_HANDLER_H

#include "Client_NodeS.h"
#include <string>

class AMI_Client_Handler_i : virtual public POA_GP::AMI_Client_NodeHandler
{
public:
  AMI_Client_Handler_i(GP::User_Id id);
  virtual ~AMI_Client_Handler_i();

private:
   GP::User_Id  id_;
};

#endif /* AMI_CLIENT_HANDLER_H */
