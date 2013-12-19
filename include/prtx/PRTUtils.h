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

#ifndef PRTX_CLASSUTILS_H_
#define PRTX_CLASSUTILS_H_

#include <string>

#include "boost/shared_ptr.hpp"

#include "prt/Object.h"

#include "prtx/prtx.h"


namespace prt {


class AttributeMap;
class AttributeMapBuilder;
class ResolveMap;
class ResolveMapBuilder;
class InitialShape;
class RuleFileInfo;
class EncoderInfo;
class DecoderInfo;
class Annotation;


} // namespace prt


namespace prtx {


/** @namespace prtx::PRTUtils
 * Various class- and object- related utilities useful for prtx extension authors.
 */
namespace PRTUtils {


/**
 * Functor to destroy a PRT object instance.
 */
class ObjectDestroyer {
public:
	void operator()(prt::Object const* p) { p->destroy(); }
};


/**
 * Wrapper template which lets us automate the life-cycle of any PRTObject subclass instance.
 */
template<typename P> class ObjectPtr {
public:
	typedef P	type;
	typedef P*	ptrType;

	ObjectPtr() { }
	explicit ObjectPtr(P* p) : mPRT(p, ObjectDestroyer()) { assert(p != 0); }
	virtual ~ObjectPtr() { }

	P* get() const { return mPRT.get(); }
	P* operator->() const { return mPRT.get(); }
	P& operator*() const { return *mPRT; }
	bool operator<(const ObjectPtr<P>& rhs) const { return (mPRT.get() < rhs.mPRT.get()); }
	bool operator==(const ObjectPtr<P>& rhs) const { return (mPRT.get() == rhs.mPRT.get()); }
	bool operator()() const { return mPRT; }

protected:
	boost::shared_ptr<P> mPRT;
};


typedef ObjectPtr<const	prt::AttributeMap>			AttributeMapPtr;
typedef ObjectPtr<		prt::AttributeMapBuilder>	AttributeMapBuilderPtr;

typedef ObjectPtr<const	prt::ResolveMap>			ResolveMapPtr;
typedef ObjectPtr<		prt::ResolveMapBuilder>		ResolveMapBuilderPtr;

typedef ObjectPtr<const	prt::InitialShape>			InitialShapePtr;
typedef ObjectPtr<const	prt::RuleFileInfo>			RuleFileInfoPtr;
typedef ObjectPtr<const	prt::EncoderInfo>			EncoderInfoPtr;
typedef ObjectPtr<const	prt::DecoderInfo>			DecoderInfoPtr;
typedef ObjectPtr<const	prt::Annotation>			AnnotationPtr;


/**
 * Helper function to get the XML representation of object p
 */
PRTX_EXPORTS_API std::string objectToXML(prt::Object const* p);


} // namespace PRTUtils


} // namespace prtx


#endif /* PRTX_CLASSUTILS_H_ */

