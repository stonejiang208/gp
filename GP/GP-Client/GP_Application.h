// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-12-06 08:16:13 by jiangtao> */

/* @file GP_Application.h
 * $Id: GP_Application.h 2013/12/06 00:16:07 jiangtao jiangtao$
 *
 * @author:Stone Jiang<jiangtao@tao-studio.net>
 */
//===========================================================================

#ifndef GP_APPLICATION_H
#define GP_APPLICATION_H

#include "GP_Client_export.h"
#include "Chat_Listener.h"
namespace Details
{
  class Application;
};

class GP_Client_Export GP_Application : public Chat_Listener
{
public:
  GP_Application();
  virtual ~GP_Application();
  int init (int argc,  ACE_TCHAR* argv[]);
  int run ();
  int quit();
  void shutdown ();
public:
  int send_message(int x, const char* msg);
  virtual void on_message(int, int sender, const char* message);
  virtual void on_system_message(int error_code, const char* desc);
  virtual void on_data (int, int sender, const void* data, size_t length);
  virtual void online();
  virtual void offline();

private:
  Details::Application*  impl_;
};
 #endif /* GP_APPLICATION_H */
