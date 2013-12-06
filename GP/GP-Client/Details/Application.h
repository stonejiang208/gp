#ifndef Application_h__
#define Application_h__

#include "ORB_Task.h"
#include "Game_PlatformC.h"
#include "AMH_Client_Node_i.h"
#include "Game_PlatformC.h"
#include "User_NodeC.h"

class Chat_Listener;
namespace Details
{
  class Application
  {
  public:
    Application(Chat_Listener* );
    virtual ~Application();
  public:
    int init (int argc, ACE_TCHAR *argv[]);
    int run ();
    int quit ();
    void shutdown ();
    int send_message(int x, const char* msg);
  protected:
    int init_orb(int argc, ACE_TCHAR *argv[]);
    int reslove_naming_service();
    int init_client_node();
    void system_message (int error_code, const char* desc);
  private:
    Chat_Listener* listener_;
    CORBA::ORB_var orb_;
    PortableServer::POA_var child_poa_;
    ORB_Task       orb_task_;
    GP::User_Node_var  user_node_;
    AMH_Client_Node_i *client_impl_;
    GP::Game_Platform_var game_platform_;
  };
};
#endif // Application_h__
