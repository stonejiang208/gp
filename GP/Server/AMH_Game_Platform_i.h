// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2013-11-24 18:31:40 by jiangtao> */

/* @file AMH_Game_Platform_i.h
 * $Id: AMH_Game_Platform_i.h 2012/10/21 06:20:55 jiangtao Exp $
 *
 * @author:Stone Jiang<jiangtao@tao-studio.net>
 */
//===========================================================================

#ifndef AMH_GAME_PLATFORM_I_H
#define AMH_GAME_PLATFORM_I_H
#include "Game_PlatformS.h"
#include "orbsvcs/Shutdown_Utilities.h"
#include "Client_NodeC.h"
#include "Server_NodeC.h"

class AMH_User_Node_i;
class AMH_Platform_Node_i;

class Player;
class AMH_Game_Platform_i
  : public virtual POA_GP::AMH_Game_Platform
{
public:
  AMH_Game_Platform_i();
  virtual ~AMH_Game_Platform_i();

public:
  virtual void create_user (
    GP::AMH_Game_PlatformResponseHandler_ptr _tao_rh,
    const char * user_uuid
    );

public:
  void orb (CORBA::ORB_ptr o);
  void poa(PortableServer::POA_ptr p);

  CORBA::ORB_ptr orb();
  PortableServer::POA_ptr poa(); 

  /// Cleanup state for shutdown.
  void finalize();
  void deactivate_player(AMH_User_Node_i* p);
  void deactivete_platform(AMH_Platform_Node_i* p);
private:
  CORBA::ORB_var orb_;
  PortableServer::POA_var poa_;
  void  obtain_ip(void); 
};


#endif /* AMH_GAME_PLATFORM_I_H */
