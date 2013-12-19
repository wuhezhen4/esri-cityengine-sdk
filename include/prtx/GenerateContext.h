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

#ifndef PRTX_GENERATECONTEXT_H_
#define PRTX_GENERATECONTEXT_H_

#include "boost/noncopyable.hpp"

#include "prt/InitialShape.h"
#include "prt/Callbacks.h"
#include "prt/Cache.h"
#include "prt/OcclusionSet.h"
#include "prtx/InitialShape.h"


#ifdef _MSC_VER
#	ifdef PRT_CC_DBG
#		pragma message(__FILE__": disabled MSVC warnings 4251 4231 4275 4660")
#	endif
#	pragma warning(push)
#	pragma warning (disable : 4251 4231 4275 4660)
#endif


namespace prtx {


/**
 * A GenerateContext is created for each prt::generate() call. It basically contains the parameters of the prt::generate() call.
 */
class PRTX_EXPORTS_API GenerateContext : boost::noncopyable {
public:
	virtual ~GenerateContext() {};

	/**
	 * @returns the number of initial shapes.
	 */
	size_t                    getInitialShapeCount() const       { return mInitialShapes.size(); }
	/**
	 * @param  i Index of InitialShape to return.
	 * @returns InitialShape with index i.
	 */
	const prtx::InitialShape* getInitialShape(size_t i) const    { return mInitialShapes[i]; }
	/**
	 * Optionally, there is a occlusion handle for every initial shape.
	 * @param  i Index of occlusion handle to return.
	 * @returns occlusion handle with index i if set,  0 (= no handle) otherwise.
	 */
	prt::OcclusionSet::Handle getOcclusionHandle(size_t i) const { return mOcclusionHandles[i]; }
	/**
	 * @returns pointer to the prt::Callbacks implementation.
	 */
	prt::Callbacks*           getCallbacks()                     { return mCallbacks; }
	/**
	 * @returns pointer to the (optional) prt::Cache implementation. Might be NULL.
	 */
	prt::Cache*               getCache()                         { return mCache; }
	/**
	 * @returns pointer to the (optional) read-only prt::OcclusionSet which contains the occluders
	 * identified by the occlusion handles. Might be NULL.
	 */
	const prt::OcclusionSet*  getOcclusionSet()                  { return mOcclusionSet; }

protected:
	GenerateContext() {};

	/**
	 * Constructor for read-only access to occlusionSet (i.e. to use occlusion set to resolve occlusion queries).
	 */
	GenerateContext(const prt::InitialShape** const initialShapes, const prt::OcclusionSet::Handle* occlusionHandles, size_t initialShapeCount,
			prt::Callbacks* callbacks, prt::Cache* cache, const prt::OcclusionSet* occlusionSet);

	/**
	 * Constructor for write access to occlusionSet (i.e. for generateOccluders() call)
	 */
	GenerateContext(const prt::InitialShape** const initialShapes, size_t initialShapeCount,
			prt::Callbacks* callbacks, prt::Cache* cache, prt::OcclusionSet* writableOcclusionSet);

	// @cond
	std::vector<const prtx::InitialShape*> mInitialShapes;
	std::vector<prt::OcclusionSet::Handle> mOcclusionHandles;
	prt::Callbacks*                        mCallbacks;
	prt::Cache*                            mCache;
	const prt::OcclusionSet*               mOcclusionSet;
	prt::OcclusionSet*                     mWritableOcclusionSet;
	// @endcond
};


} //namespace prtx


#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif /* PRTX_GENERATECONTEXT_H_ */

