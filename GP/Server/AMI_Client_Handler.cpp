// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-03-14 17:36:33 by jiangtao> */

/* @file AMI_Client_Handler.cpp
 * $Id: AMI_Client_Handler.cpp 2013/03/14 09:36:31 jiangtao Exp $
 *
 * @author:Jiangtao<jiangtao@tao-studio.net>
 */
//===========================================================================


#include "AMI_Client_Handler.h"
#include "ace/Log_Msg.h"
 
#include "Lobby.h"

AMI_Client_Handler_i::AMI_Client_Handler_i(GP::User_Id id)
  :id_(id)
{
  ACE_DEBUG ((LM_DEBUG,
    ACE_TEXT ("(%t|%T) AMI_Client_Handler_i::AMI_Client_Handler_i (%d)\n"),id));
}

AMI_Client_Handler_i::~AMI_Client_Handler_i()
{
  ACE_DEBUG ((LM_DEBUG,
    ACE_TEXT ("(%t|%T) AMI_Client_Handler_i::~AMI_Client_Handler_i (%d)\n"),
    id_));
}




