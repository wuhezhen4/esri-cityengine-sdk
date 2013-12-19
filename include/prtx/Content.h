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

#ifndef PRTX_CONTENT_H_
#define PRTX_CONTENT_H_

#include <vector>

#include "boost/shared_ptr.hpp"
#include "boost/noncopyable.hpp"

#include "prtx/prtx.h"

#ifdef _MSC_VER
#	ifdef PRT_CC_DBG
#		pragma message (__FILE__": disabled MSVC warnings 4251 4231 4275 4660" )
#	endif
#	pragma warning(push)
#	pragma warning (disable : 4251 4231 4275 4660)
#endif


namespace prtx {


/**
 * Base class for all content types.
 * Content classes are not copyable.
 */

class PRTX_EXPORTS_API Content : boost::noncopyable {
public:
	Content() : boost::noncopyable() { }
	virtual ~Content() { }
};


typedef boost::shared_ptr<Content> ContentPtr;
typedef std::vector<ContentPtr>    ContentPtrVector;


/**
 * Interface for comparable content classes.
 *
 * A word of caution: To compare content objects, do not directly compare pointer values (or shared pointers)!
 * Content objects are typically implemented as thin wrappers to internal storage classes and do not guarantee pointer equality.
 * Operate on the objects instead:
 * \code{.cpp}
 * MaterialBuilder mb;
 * MaterialPtr m1 = mb.createShared();
 * MaterialPtr m2 = mb.createShared();
 *
 * assert(m1 == m2); // WRONG!
 * assert(*m1 == *m2); // CORRECT!
 * assert(m1->compare(*m2)); // CORRECT!
 * \endcode
 *
 * To use shared pointers to content objects with STL containers like std::set or std::map, we recommend to use a
 * de-referencing comparator like this:
 * \code{.cpp}
template<typename T>
struct DeRefLess<boost::shared_ptr<T> > : public std::binary_function<boost::shared_ptr<T>, boost::shared_ptr<T>, bool> {
	bool operator()(const boost::shared_ptr<T>& a, const boost::shared_ptr<T>& b) const {
		T* pa = a.get();
		T* pb = b.get();

		if(pa == 0)
			return pb != 0;
		if(pb == 0)
			return false;
		return *pa < *pb;
	}
};
 * \endcode
 */

class PRTX_EXPORTS_API ComparableContent : public Content {
public:
	ComparableContent() { }
	virtual ~ComparableContent() { }

	virtual bool compare(const ComparableContent& rhs) const = 0;
	virtual bool operator==(const ComparableContent& rhs) const = 0;
	virtual bool operator!=(const ComparableContent& rhs) const = 0;
	virtual bool operator<(const ComparableContent& rhs) const = 0;
};


} // namespace prtx


#ifdef _MSC_VER
#	pragma warning(pop)
#endif


#endif /* PRTX_CONTENT_H_ */

