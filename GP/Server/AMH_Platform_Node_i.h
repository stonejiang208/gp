// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-07-16 07:42:06 by jiangtao> */

/* @file AMH_Platform_Node_i.h
 * $Id: AMH_Platform_Node_i.h 2013/07/15 23:42:02 jiangtao Exp $
 *
 * @author:Jiangtao<jiangtao@tao-studio.net>
 */
//===========================================================================

#ifndef AMH_PLATFORM_NODE_I_H
#define AMH_PLATFORM_NODE_I_H

#include "Platform_NodeS.h"
#include "Server_NodeC.h"

class AMH_Platform_Node_i 
  : virtual public POA_GP::AMH_Platform_Node

{
public:
  AMH_Platform_Node_i(::GP::Server_Node_ptr inner);
  virtual ~AMH_Platform_Node_i();
public:
   
};


#endif /* AMH_PLATFORM_NODE_I_H */
