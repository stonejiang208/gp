// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-03-13 14:23:51 by jiangtao> */

/* @file Chat_Client.cpp
 * $Id: Chat_Client.cpp 2013/03/13 06:23:50 jiangtao Exp $
 *
 * @author:Jiangtao<jiangtao@tao-studio.net>
 */
//===========================================================================


#include "Chat_Client.h"
#include "Chat_Client_Impl.h"
#include <stdio.h>


Chat_Client::Chat_Client()	
{
	this->impl_ = new Chat_Client_Impl();
}

Chat_Client::~Chat_Client()
{
	delete this->impl_;
}

int Chat_Client::init( int argc, ACE_TCHAR* argv[] )
{
	return this->impl_->init(argc, argv);
}

void Chat_Client::run()
{
 this->impl_->run();
}

void Chat_Client::shutdown()
{
	this->impl_->shutdown();
}

int Chat_Client::join( const char* nick_name )
{
	return this->impl_->join(nick_name);
}

int Chat_Client::quit()
{
	return this->impl_->quit();
}

int Chat_Client::send_message( int x, const char* msg )
{
 
	return this->impl_->send_message(x,msg);; 
}

int Chat_Client::send_data( int x, const void* data, size_t length )
{
	return this->impl_->send_data(x,data,length);; 
}

void Chat_Client::listener( Chat_Listener* l )
{
  this->impl_->listener(l);
}

Chat_Listener* Chat_Client::listener( void )
{
  return this->impl_->listener();
}

 

 

 
