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

#ifndef PRTX_TYPES_H_
#define PRTX_TYPES_H_

#include <string>
#include <vector>

#include "boost/shared_ptr.hpp"

#include "prt/prt_stdint.h"


namespace prtx {


typedef uint8_t							Bool;				///< uint8_t based Bool type
typedef std::vector<prtx::Bool>			BoolVector;			///< vector of uint8_t based Bool type
typedef std::vector<double>				DoubleVector;		///< vector of double

typedef std::vector<std::string>		StringVector;		///< vector of std::string
typedef std::vector<std::wstring>		WStringVector;		///< vector of std::wstring
typedef boost::shared_ptr<std::wstring>	StringPtr;			///< shared std::string

const Bool PRTX_FALSE	= (Bool)0u;
const Bool PRTX_TRUE	= (Bool)1u;
const Bool PRTX_NO		= (Bool)0u;
const Bool PRTX_YES		= (Bool)1u;

inline bool toPrimitive(Bool b) { return (b == PRTX_TRUE); }


} // namespace prtx


#endif /* PRTX_TYPES_H_ */

