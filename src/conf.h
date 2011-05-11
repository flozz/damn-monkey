#ifndef CONF_H_INCLUDED
#define CONF_H_INCLUDED


/**
 * \file conf.h
 * \brief Contain the project configuration.
 *
 * In this file, the name and the version of the application can be
 * changed ; the build target can be selected (GNU/Linux, Windows or
 * Mac OS).
 */


/**
 * \def APP_PR_NAME
 * \brief Application printable name.
 */
#define APP_PR_NAME "Damn Monkey"

/**
 * \def APP_NAME
 * \brief Application name (lower case, no spaces or other special chars).
 */
#define APP_NAME "damn-monkey"

/**
 * \def VERSION
 * \brief The version of the game.
 */
#define VERSION "0.1"


/** \cond */

//Destination OS:
#define LINUX
//#define WINDOWS
//#define MAC_OS

/** \endcond */


#endif //CONF_H_INCLUDED

