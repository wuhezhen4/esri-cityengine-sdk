/*
  COPYRIGHT (c) 2013 ESRI
  TRADE SECRETS: ESRI PROPRIETARY AND CONFIDENTIAL
  Unpublished material - all rights reserved under the
  Copyright Laws of the United States and applicable international
  laws, treaties, and conventions.

  For additional information, contact:
  Environmental Systems Research Institute, Inc.
  Attn: Contracts and Legal Services Department
  380 New York Street
  Redlands, California, 92373
  USA

  email: contracts@esri.com
*/

#ifndef PRT_LOGLEVEL_H_
#define PRT_LOGLEVEL_H_

#include "prt/prt.h"


namespace prt {

/**
 * Loglevels for the the logger.
 */
enum PRT_EXPORTS_API LogLevel {
	LOG_TRACE = 0, LOG_DEBUG = 1, LOG_INFO = 2, LOG_WARNING = 3, LOG_ERROR = 4, LOG_FATAL = 5, LOG_NO = 1000,
};


}

#endif /* PRT_LOGLEVEL_H_ */

