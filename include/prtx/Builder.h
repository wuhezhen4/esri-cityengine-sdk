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

#ifndef BUILDER_H_
#define BUILDER_H_

#include <string>

#include "boost/noncopyable.hpp"
#include "boost/shared_ptr.hpp"

#include "prtx/PRTUtils.h"


#ifdef _MSC_VER
#	ifdef PRT_CC_DBG
#		pragma message(__FILE__": disabled MSVC warnings 4275")
#	endif
#	pragma warning(push)
#	pragma warning(disable : 4275)
#endif


namespace prtx {


/**
 * Interface template for the Builder Pattern.
 * A builder is useful to create (multiple) immutable objects with similar states.
 */
template<typename C> class Builder : boost::noncopyable {
protected:

	/**
	 * Creates an instance of type C based on the current builder state. Does not modify the builder state.
	 *
	 * @param [out] warnings If warnings != 0, a builder implementation may emit warnings about the creation process.
	 * @return New instance of type C. Must be destroyed by the caller.
	 */
	virtual C* create(std::wstring* warnings = 0) const = 0;

	/**
	 * Creates and instance of type C based on the current builder state. Resets the builder state at the end.
	 *
	 * @param [out] warnings If warnings != 0, a builder implementation may emit warnings about the creation process.
	 * @return New instance of type C. Must be destroyed by the caller.
	 */
	virtual C* createAndReset(std::wstring* warnings = 0) = 0;
};


/**
 * Builder with additional member functions to create managed objects of base type prt::Object
 */
template<typename C> class PRTBuilder : public Builder<C> {
public:
	/**
	 * Convenience member function to create a shared object pointer of a new instance of C. Does not modify the builder state.
	 */
	prtx::PRTUtils::ObjectPtr<C> createShared(std::wstring* warnings = 0) const {
		return prtx::PRTUtils::ObjectPtr<C>(this->create(warnings));
	}

	/**
	 * Convenience member function to create a shared pointer of a new instance of C. Resets the builder to its default values.
	 */
	prtx::PRTUtils::ObjectPtr<C> createSharedAndReset(std::wstring* warnings = 0) {
		return prtx::PRTUtils::ObjectPtr<C>(this->createAndReset(warnings));
	}
};


/**
 * Builder with additional member functions to create shared pointers for objects with base type prtx::Content
 */
template<typename C> class PRTXBuilder : public Builder<C> {
public:
	/**
	 * Convenience member function to create a shared pointer of a new instance of C. Does not modify the builder state.
	 */
	boost::shared_ptr<C> createShared(std::wstring* warnings = 0) const {
		return boost::shared_ptr<C>(this->create(warnings));
	}

	/**
	 * Convenience member function to create a shared pointer of a new instance of C. Resets the builder to its default values.
	 */
	boost::shared_ptr<C> createSharedAndReset(std::wstring* warnings = 0) {
		return boost::shared_ptr<C>(this->createAndReset(warnings));
	}
};


} // namespace prtx


#ifdef _MSC_VER
#	pragma warning(pop)
#endif


#endif /* BUILDER_H_ */

