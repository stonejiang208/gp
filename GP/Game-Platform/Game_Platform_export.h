
// -*- C++ -*-
// $Id$
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl Game_Platform
// ------------------------------
#ifndef GAME_PLATFORM_EXPORT_H
#define GAME_PLATFORM_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (GAME_PLATFORM_HAS_DLL)
#  define GAME_PLATFORM_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && GAME_PLATFORM_HAS_DLL */

#if !defined (GAME_PLATFORM_HAS_DLL)
#  define GAME_PLATFORM_HAS_DLL 1
#endif /* ! GAME_PLATFORM_HAS_DLL */

#if defined (GAME_PLATFORM_HAS_DLL) && (GAME_PLATFORM_HAS_DLL == 1)
#  if defined (GAME_PLATFORM_BUILD_DLL)
#    define Game_Platform_Export ACE_Proper_Export_Flag
#    define GAME_PLATFORM_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define GAME_PLATFORM_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* GAME_PLATFORM_BUILD_DLL */
#    define Game_Platform_Export ACE_Proper_Import_Flag
#    define GAME_PLATFORM_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define GAME_PLATFORM_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* GAME_PLATFORM_BUILD_DLL */
#else /* GAME_PLATFORM_HAS_DLL == 1 */
#  define Game_Platform_Export
#  define GAME_PLATFORM_SINGLETON_DECLARATION(T)
#  define GAME_PLATFORM_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* GAME_PLATFORM_HAS_DLL == 1 */

// Set GAME_PLATFORM_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (GAME_PLATFORM_NTRACE)
#  if (ACE_NTRACE == 1)
#    define GAME_PLATFORM_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define GAME_PLATFORM_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !GAME_PLATFORM_NTRACE */

#if (GAME_PLATFORM_NTRACE == 1)
#  define GAME_PLATFORM_TRACE(X)
#else /* (GAME_PLATFORM_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define GAME_PLATFORM_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (GAME_PLATFORM_NTRACE == 1) */

#endif /* GAME_PLATFORM_EXPORT_H */

// End of auto generated file.
