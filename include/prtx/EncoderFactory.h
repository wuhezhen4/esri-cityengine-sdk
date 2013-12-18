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

#ifndef PRTX_ENCODERFACTORY_H_
#define PRTX_ENCODERFACTORY_H_

#include <string>
#include <vector>

#include "prt/Annotation.h"
#include "prt/AttributeMap.h"
#include "prt/Callbacks.h"
#include "prt/EncoderInfo.h"

#include "prtx.h"
#include "prtx/ExtensionFactory.h"
#include "prtx/Encoder.h"


#ifdef _MSC_VER
#	ifdef PRT_CC_DBG
#		pragma message(__FILE__": disabled MSVC warnings 4251 4231 4660")
#	endif
#	pragma warning(push)
#	pragma warning (disable : 4251 4231 4660)
#endif


class EncoderInfoImpl;


namespace prtx {


/**
 * Base class for all encoder factories.
 *
 * A typical example to create a custom EncoderFactory with the Singleton helper template:
 *
 * \code{.cpp}
 *
 * class MyEncoder {
 *     // ...
 * };
 *
 * class MyEncoderFactory : public prtx::EncoderFactory, public prtx::ClassUtils::Singleton<MyEncoderFactory> {
 * public:
 *     MyEncoderFactory(const prt::EncoderInfo* info) : prtx::EncoderFactory(info) { }
 *     virtual ~MyEncoderFactory() { }
 *
 *     virtual MyEncoder* create(const prt::AttributeMap* defaultOptions, prt::Callbacks* callbacks) const {
 *         return new MyEncoder(getID(), defaultOptions, callbacks);
 *     }
 *
 *     static MyEncoderFactory* createInstance() {
 *         // ...
 *         return new MyEncoderFactory(info);
 *     }
 * };
 *
 * \endcode
 *
 * The factory can then be conveniently registered like this:
 * \code{.cpp}
 * prtx::ExtensionManager* manager ...
 * manager->addFactory(MyEncoderFactory::instance());
 * \endcode
 *
 *
 */
class PRTX_EXPORTS_API EncoderFactory : public ExtensionFactory {
protected:
	EncoderFactory();

	/**
	 * Constructs an EncoderFactory with the appropriate info. EncoderFactory subclasses must
	 * be used with singleton
	 *
	 * It is recommended to also protected the constructors of subclasses
	 * and use a static member function to create the singleton.
	 *
	 * @param info ownership is transferred to EncoderFactory
	 *
	 * \sa EncoderInfo
	 */

	EncoderFactory(const prt::EncoderInfo* info);

public:
	virtual ~EncoderFactory();

	/**
	 * Subclasses must override this member function to create an instance of the corresponding encoder.
	 *
	 * @param defaultOptions Optional default options needed to create an instance of the extension.
	 * @param callbacks Optional callbacks needed to create an instance of the extension.
	 *
	 * @return A new Encoder instance, must be destroyed by the caller.
	 */
	virtual Encoder* create(const prt::AttributeMap* defaultOptions, prt::Callbacks* callbacks) const = 0;

	/**
	 * Convenience member function forwarded from EncoderInfo.
	 */
	virtual const std::wstring& getID() const;

	/**
	 * Convenience member function forwarded from EncoderInfo.
	 */
	virtual const std::wstring& getName() const;

	/**
	 * Convenience member function forwarded from EncoderInfo.
	 */
	virtual const std::wstring& getDescription() const;

	/**
	 * Convenience member function forwarded from EncoderInfo.
	 */
	virtual prt::ContentType getContentType() const;

	/**
	 * Returns true if opts has the same key set as the default options
	 */
	bool checkOptionKeys(prt::AttributeMap const* opts) const;

	/**
	 * Returns a copy of the encoder info describing this encoder.
	 *
	 * @return A new instance of EncoderInfo, must be destroyed by the caller.
	 */
	prt::EncoderInfo* createEncoderInfo() const;

	/**
	 * Fixate the extension type to prtx::Extension::ET_ENCODER.
	 *
	 * @return Always returns Extension::ET_ENCODER.
	 */
	virtual prtx::Extension::ExtensionType getExtensionType() const;

	/**
	 * Encoders can handle any URI.
	 *
	 * @return Always returns true.
	 */
	virtual bool canHandleURI(prtx::URIPtr uri) const;

private:
	virtual Extension* create() const;

protected:
	const EncoderInfoImpl* mInfo;
};


} /* namespace prtx */


#ifdef _MSC_VER
#pragma warning(pop)
#endif


#endif /* PRTX_ENCODERFACTORY_H_ */

