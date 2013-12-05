// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2012-11-16 15:08:32 by jiangtao> */

/* @file Options.cpp
 * $Id: Options.cpp 2012/11/16 06:22:57 jiangtao Exp $
 *
 * @author:Stone Jiang<jiangtao@tao-studio.net>
 */
//===========================================================================
#include "ace/OS_NS_unistd.h"
#include "ace/Log_Msg.h"
#include "ace/streams.h"
#include "Options.h"
#include <fstream>
 
Options::Options()
{
  if (load () !=0)
  {
    throw;
  }
}

Options::~Options()
{

}
int Options::load()
{
  if (ACE_OS::access(MAP_OPT_FILE,F_OK) != 0)
  {
    //write default 
    big_map_root_["header"]["version"]=1;
    big_map_root_["header"]["type"]=1;

    Json::Value payload;
    Json::Value room;
    room["name"]="chat_room0";
    room["gates"][0u]="1";
    room["gates"][1u]="2";
    payload["0"] = room;


    room["name"]="chat_room1";
    room["gates"][0u]="0";
    room["gates"][1u]="2";
    payload["1"] = room;


    room["name"]="chat_room2";
    room["gates"][0u]="0";
    room["gates"][1u]="1";
    payload["2"] = room;


    big_map_root_["payload"] = payload;
    ofstream f_out (MAP_OPT_FILE);
    f_out << big_map_root_.toStyledString()<<endl;
    f_out.close();
  }
  if (load_options(MAP_OPT_FILE,this->big_map_root_) != 0)
  {
    return -1;
  }  

  
  return 0;
}


int Options::load_options( const char* filename, Json::Value& root )
{
  Json::Reader reader;   
  //const char* full_path = 
  //  cocos2d::CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(filename);

  ifstream  input (filename);

  if (!reader.parse(input,root))
  {
    input.close();
    ACE_ERROR_RETURN ((LM_ERROR,
       ACE_TEXT ("(%t|%T) ERROR: read %s error\n"),filename),-1);
  }
  else
  {
     ACE_DEBUG ((LM_INFO,
       ACE_TEXT ("(%t|%T) load options file %s ok\n"),filename));
  }
  input.close();  
  return 0;
}

Json::Value Options::get_map_options( const char* id )
{
  return this->big_map_root_;
}
