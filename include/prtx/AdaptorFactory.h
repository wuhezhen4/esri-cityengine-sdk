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

#ifndef PRTX_ADAPTORFACTORY_H_
#define PRTX_ADAPTORFACTORY_H_

#include <string>

#include "prtx.h"
#include "prtx/Extension.h"
#include "prtx/ExtensionFactory.h"


namespace prtx {


/**
 * This is the base class for all adaptor factories.
 */

class PRTX_EXPORTS_API AdaptorFactory : public ExtensionFactory {
protected:
	AdaptorFactory() { }

public:
	virtual ~AdaptorFactory() { }

	/**
	 * Fixates the extension type to prtx::Extension::ET_ADAPTOR.
	 *
	 * @return Always returns prtx::Extension::ET_ADAPTOR.
	 */
	virtual prtx::Extension::ExtensionType getExtensionType() const;

	/**
	 * An adaptor is content type agnostic.
	 *
	 * @return Always returns prt::CT_UNDEFINED.
	 */
	virtual prt::ContentType getContentType() const;
};


} /* namespace prtx */


#endif /* PRTX_ADAPTORFACTORY_H_ */

