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

#ifndef PRTX_CGB_H_
#define PRTX_CGB_H_

#include <vector>

#include "boost/shared_ptr.hpp"

#include "prt/Object.h"

#include "prtx/prtx.h"
#include "prtx/Content.h"


namespace prtx {


class CGB;
typedef boost::shared_ptr<CGB> CGBPtr;
typedef std::vector<CGBPtr> CGBPtrVector;

class PRTX_EXPORTS_API CGB : public Content {
public:
	CGB();
	virtual ~CGB();

	static CGB* create();
};


} /* namespace prtx */


#endif /* PRTX_CGB_H_ */

