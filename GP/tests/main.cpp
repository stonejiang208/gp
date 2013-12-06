// $Id: MessengerClient.cpp 85583 2009-06-09 13:47:38Z calabrese_p $

#include "Game_PlatformC.h"
#include "User_NodeC.h"
#include "orbsvcs/CosNamingC.h"
#include "orbsvcs/Naming/Naming_Client.h"
#include "ace/OS_NS_unistd.h"
#include <iostream>

#include "My_Application.h"

#include "My_Listener.h"
 
int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  ACE_DEBUG ((LM_DEBUG,ACE_TEXT ("(%t|%T) test start here.\n")));

  My_Appliation* app = new My_Appliation();
#if 0
  Chat_Client *client = new Chat_Client();
  My_Listener l;
  int retval = client->init(argc,argv);
  if (retval != 0)
  {
    ACE_ERROR_RETURN ((LM_ERROR,
      ACE_TEXT ("(%t|%T) init error\n")),-1);
  }
  client->listener(&l);
  client->join("name");
  client->run();

  for(int i = 0; i < 10; i++)
  {
    client->send_message(i,"hello world.");
    ACE_OS::sleep(1);

  }
  ACE_OS::sleep(5);
  client->quit();
  client->shutdown();

  delete client;
#endif
  try
  {
    int retval = app->init (argc, argv);
    if (retval != 0)
    {
      ACE_ERROR_RETURN ((LM_ERROR,
        ACE_TEXT ("(%t|%T) init error\n")),-1);
    }
    app->run();
  }  
  catch (...)
  {
  }
  for(int i = 0; i < 10; i++)
  {
    app->send_message(i,"hello world.");
    ACE_OS::sleep(1);

  }
  ACE_OS::sleep(2);
  app->quit();
  app->shutdown();
  delete app;
  ACE_DEBUG ((LM_DEBUG,ACE_TEXT ("(%t|%T) test end here.\n")));

  return 0;
}
