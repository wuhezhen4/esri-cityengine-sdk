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

	/**
	 * The absolute path to the activation library (e.g. flexnet_prt.dll on windows).
	 */
	const char* mActLibPath;

	/**
	 * For standard CE installations: The license feature string (char*),
	 * i.e. one of
	 * - CityEngBasFx
	 * - CityEngBas
	 * - CityEngAdvFx
	 * - CityEngAdv
	 */
	const char* mFeature;

	/**
	 * Host name of the license server (empty for node-locked licensing). For the
	 * default flexnet port 27000, the syntax is \code 27000@myserver.example.com \endcode
	 */
	const char* mHostName;
};


} // namespace prt


#endif /* PRT_FLEXLICPARAMS_H_ */

