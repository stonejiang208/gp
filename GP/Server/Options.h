// -*- C++ -*-
//===========================================================================
/* Time-stamp: <2012-11-16 14:23:28 by jiangtao> */

/* @file Options.h
* $Id: Options.h 2012/11/16 06:22:27 jiangtao Exp $
*
* @author:Stone Jiang<jiangtao@tao-studio.net>
*/
//===========================================================================

#ifndef OPTIONS_H
#define OPTIONS_H
#include "ace/Singleton.h"
#include "ace/Null_Mutex.h"
#include "ace/streams.h"
#include "json/json.h"

#define MAP_OPT_FILE  "maps.json"


class Options
{

public:
  friend class ACE_Singleton<Options, ACE_Null_Mutex>;
public:
  Json::Value get_map_options(const char* id);
  int load_options(const char* filename, Json::Value& root);

private:
  int load();

  Options();
  ~Options();
  Json::Value big_map_root_;

};

typedef ACE_Singleton<Options, ACE_Null_Mutex> OPTIONS;

#endif /* OPTIONS_H */
