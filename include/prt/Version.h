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

#ifndef PRT_VERSIONINFO_H_
#define PRT_VERSIONINFO_H_

#include "prt/prt.h"


namespace prt {


/**
 * Provides static/build-time version information about the API as narrow and wide strings.
 */
struct PRT_EXPORTS_API Version {
	Version();

	const char* mName;
	const char* mFullName;
	const char* mVersion;
	const char* mVersionMajor;
	const char* mVersionMinor;
	const char* mVersionBuild;
	const char* mBuildConfig;
	const char* mBuildDate;

	const wchar_t* mwName;
	const wchar_t* mwFullName;
	const wchar_t* mwVersion;
	const wchar_t* mwVersionMajor;
	const wchar_t* mwVersionMinor;
	const wchar_t* mwVersionBuild;
	const wchar_t* mwBuildConfig;
	const wchar_t* mwBuildDate;
};


} // namespace prt


#endif /* PRT_VERSIONINFO_H_ */

