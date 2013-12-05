/* -*- C++ -*- */

// Time-stamp: <2012-11-02 22:56:16 by jiangtao>

/**
* @file main.cpp
* @author jiangtao
*/

#include "ace/Log_Msg.h"
#include "ace/OS_main.h"
#include <iostream>
#include "tao/Strategies/advanced_resource.h"

#include "The_Server.h"

int ACE_TMAIN(int argc, ACE_TCHAR * argv[])
{
  ACE_DEBUG((LM_DEBUG,
    ACE_TEXT ("(%t|%T) Server start here.\n")));

  try
  {
    The_Server server (argc, argv);;
    My_Service_Shutdown killer (server);
    Service_Shutdown kill_contractor (killer);
    server.run();

  }
  catch (The_Server::InitError& ex)
  {
    std::cerr << "Unexpected initialization Error: "
      << ex.msg_ << std::endl;
    return -1;

  } 
  catch (const CORBA::Exception & e)
  {
    e._tao_print_exception ("CORBA exception in main");
    return 1;
  }
  ACE_DEBUG((LM_DEBUG,
    ACE_TEXT ("(%t|%T) Server shutdown gracefully.\n")));

  return 0;
}

