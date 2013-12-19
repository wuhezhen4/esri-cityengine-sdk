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

#ifndef PRT_FILEOUTPUTCALLBACKS_H_
#define PRT_FILEOUTPUTCALLBACKS_H_

#include "prt/prt.h"
#include "prt/Object.h"
#include "prt/Callbacks.h"
#include "prt/ContentType.h"

namespace prt {

/**
 * File-based implementation of the SimpleOutputCallbacks interface.
 */
class PRT_EXPORTS_API FileOutputCallbacks: public SimpleOutputCallbacks, public Object {
public:
	/**
	 * Creates a FileOutputCallbacks instance. The returned instance must be destroyed by the caller.
	 *
	 * @param dir             Absolute filesystem path to the base directory.
	 *                        The name parameter of the open calls will be a file relative to this directory.
	 * @param cgaOutputEnc    Optional encoding for cgaPrint, cgaReport and cgaError (string) calls.
	 * @param[out] stat       Optional pointer to return the status.
 	 * @returns a pointer to the instance or 0 in case of error.
	 */
	static FileOutputCallbacks* create(const wchar_t* dir, StringEncoding cgaOutputEnc = SE_NATIVE, Status* status = 0);

protected:
	FileOutputCallbacks();
	virtual ~FileOutputCallbacks();
};


}


#endif /* PRT_FILEOUTPUTCALLBACKS_H_ */

