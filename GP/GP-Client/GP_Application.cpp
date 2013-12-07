// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-12-06 08:16:27 by jiangtao> */

/* @file GP_Application.cpp
 * $Id: GP_Application.cpp 2013/12/06 00:16:24 jiangtao Exp $
 *
 * @author:Stone Jiang<jiangtao@tao-studio.net>
 */
//===========================================================================


#include "GP_Application.h"
#include "Details/Application.h"

GP_Application::GP_Application()
{
  this->impl_ = new Details::Application(this);
}

GP_Application::~GP_Application()
{
  delete this->impl_;
}

int GP_Application::init( int argc, ACE_TCHAR* argv[] )
{
  return this->impl_->init(argc,argv);
}

int GP_Application::run()
{
  return this->impl_->run();
}

int GP_Application::quit()
{
  return this->impl_->quit ();
}

void GP_Application::shutdown()
{
  this->impl_->shutdown();
}

void GP_Application::on_message( int x, int sender, const char* message )
{
   ACE_DEBUG ((LM_INFO,
     ACE_TEXT ("(%t|%T)  GP_Application::on_message(%d,%d,%s)\n"),
     x,sender,message));
}

void GP_Application::on_data( int, int sender, const void* data, size_t length )
{

}

void GP_Application::online()
{
  ACE_DEBUG ((LM_INFO,ACE_TEXT ("(%t|%T)  GP_Application::online()\n")));
}

void GP_Application::offline()
{
   ACE_DEBUG ((LM_INFO,ACE_TEXT ("(%t|%T)  GP_Application::offline()\n")));
}

void GP_Application::on_system_message( int error_code, const char* desc )
{
  if (error_code == 0)
  {
    ACE_DEBUG ((LM_INFO,ACE_TEXT ("(%t|%T) INFO: %s\n"),desc));
  }
  else
  {
    ACE_DEBUG ((LM_ERROR,
      ACE_TEXT ("(%t|%T) ERROR: code=%d, desc=%s\n"),error_code,desc));
  }
}

int GP_Application::send_message( int x, const char* msg )
{
  return this->impl_->send_message(x,msg);  
}



