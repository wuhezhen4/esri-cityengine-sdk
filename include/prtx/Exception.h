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

#ifndef PRTX_EXCEPTION_H_
#define PRTX_EXCEPTION_H_

#include <exception>

#include "prtx/prtx.h"
#include "prt/Status.h"
#include "prt/API.h"


namespace prtx {


/**
 * Specialization of std::exception to transport a prt::Status code. If a StatusException is thrown
 * within prtx, the prt function which is the entry point will report the associated prt:::Status.
 */
class PRTX_EXPORTS_API StatusException : public std::exception {
public:
	explicit StatusException(prt::Status stat) : mStatus(stat) {}
	virtual ~StatusException() throw() {}

	virtual const char* what() const throw() { return prt::getStatusDescription(mStatus); }
	prt::Status getStatus() const { return mStatus; }

private:
	prt::Status  mStatus;
};


} // namespace prtx


#endif /* PRTX_EXCEPTION_H_ */

