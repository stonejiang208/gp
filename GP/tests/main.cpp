// $Id: MessengerClient.cpp 85583 2009-06-09 13:47:38Z calabrese_p $

#include "Game_PlatformC.h"
#include "User_NodeC.h"
#include "orbsvcs/CosNamingC.h"
#include "orbsvcs/Naming/Naming_Client.h"
#include "ace/OS_NS_unistd.h"
#include <iostream>
int
  ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  try {
    // Initialize orb
    CORBA::ORB_var orb = CORBA::ORB_init( argc, argv );

    // Find the Naming Service
    TAO_Naming_Client naming_client;

    if (naming_client.init (orb.in ()) != 0) {
      std::cerr << "Could not initialize naming client." << std::endl;
      return 1;
    }

    // Resolve the Messenger object
    CosNaming::Name name;
    name.length( 1 );
    name[0].id = CORBA::string_dup( "Game_Platform" );
   
    CORBA::Object_var obj = CORBA::Object::_nil();
    while (CORBA::is_nil(obj.in())) {
      try {
        obj = naming_client->resolve(name);
      } catch (const CosNaming::NamingContext::NotFound&) {
        // Sleep for a second and try again
        ACE_OS::sleep(1);
      }
    }

    // Narrow
    GP::Game_Platform_var platform = GP::Game_Platform::_narrow(obj.in());
    if (CORBA::is_nil(platform.in())) {
      std::cerr << "Not a Messenger reference" << std::endl;
      return 1;
    }
    CORBA::String_var uuid = CORBA::string_dup("uuid");
    GP::User_Node_var user_node =
      platform->create_user(uuid.in());
    CORBA::String_var msg = CORBA::string_dup("this is the message");

    for(int i = 0; i < 100; i++)
    {
      user_node->message(i,msg.in());
      ACE_OS::sleep(1);
    }
    std::cout << "Message was sent" << std::endl;
  }
  catch(const CORBA::Exception& ex) {
    std::cerr << "Caught a CORBA::Exception: " << ex << std::endl;
    return 1;
  }

  return 0;
}
