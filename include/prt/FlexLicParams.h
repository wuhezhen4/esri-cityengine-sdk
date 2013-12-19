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

#ifndef PRT_FLEXLICPARAMS_H_
#define PRT_FLEXLICPARAMS_H_

#include "API.h"

namespace prt {

// --- MAIN PRT API CALLS

/**
 * Structure for licensing information for the flexnet loader.
 *
 */
struct FlexLicParams : LicParams {
	const char* mActLibPath;	//!< the absolute path to the activation library (e.g. flexnet_prt.dll on windows)
	const char* mFeature;		//!< for standard CE installations: The license feature string (char*), i.e. one of "CityEngBasFx;CityEngBas;CityEngAdvFx;CityEngAdv;"
	const char* mHostName;      //!< host name of the license server
};

}

#endif /* PRT_FLEXLICPARAMS_H_ */

