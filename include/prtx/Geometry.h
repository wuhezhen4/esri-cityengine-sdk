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

#ifndef PRTX_GEOMETRY_H_
#define PRTX_GEOMETRY_H_

#include <vector>

#include "boost/shared_ptr.hpp"

#include "prtx/prtx.h"
#include "prtx/Builder.h"
#include "prtx/URI.h"
#include "prtx/Content.h"
#include "prtx/Mesh.h"


#ifdef _MSC_VER
#	ifdef PRT_CC_DBG
#		pragma message(__FILE__": disabling MSVC warnings 4231 4251 4275 4660" )
#	endif
#	pragma warning(push)
#	pragma warning (disable : 4231 4251 4275 4660)
#endif


namespace prtx {


class BoundingBox;
class Geometry;
typedef boost::shared_ptr<Geometry> GeometryPtr;		///< shared Geometry pointer
typedef std::vector<GeometryPtr> GeometryPtrVector;		///< vector of shared Geometry pointers

/**
 * Read-only container for polygon meshes. A Geometry has an URI which is either:
 *  * empty / invalid: the Geometry is a transient result of the generate() process
 *  * valid:           the URI uniquely identifies this geometry which originates from an external asset (file).
 *
 *  The coordinate system of the Geometry is arbitrary.
 *
 *  @sa DataBackend, GeometryBuilder, Mesh
 */
class PRTX_EXPORTS_API Geometry: public Content {

public:
	virtual ~Geometry() {}

	/**
	 * @returns the URI which is either empty or uniquely identifies the external asset (file).
	 */
	URIPtr getURI() const {
		return mURI;
	}

	/**
	 * @returns a vector with all meshes.
	 */
	const MeshPtrVector& getMeshes() const {
		return mMeshes;
	}

	/**
	 * @returns axis-aligned BoundingBox.
	 */
	virtual const BoundingBox& getBoundingBox() const = 0;

protected:
	// @cond
	Geometry() : mURI(URI::create()) {}
	Geometry(const prtx::URIPtr& uri, const MeshPtrVector& meshes);

	URIPtr			mURI;
	MeshPtrVector	mMeshes;
	// @endcond
};


/**
 * Builder to create (immutable) Geometry instances.
 */
class PRTX_EXPORTS_API GeometryBuilder : public PRTXBuilder<Geometry> {
public:
	/**
	 * Constructs an empty GeometryBuilder.
	 */
	GeometryBuilder();

	/**
	 * Constructs a GeometryBuilder initialized to the passed geometry.
	 * @param geometry Geometry to initialize builder with.
	 */
	GeometryBuilder(const Geometry& geometry);

	virtual ~GeometryBuilder();

	/**
	 * Creates a geometry instance. Throws an exception if requirements are not met.
	 * @param[out] warnings Optional pointer to return warnings.
	 * @return shared pointer to new Geometry instance.
	 */
	Geometry* create(std::wstring* warnings = 0) const;

	/**
	 * Creates a geometry instance and resets the builder's state.
	 * Throws an exception if requirements are not met.
	 * @param[out] warnings Optional pointer to return warnings.
	 * @return shared pointer to new Geometry instance.
	 */
	Geometry* createAndReset(std::wstring* warnings = 0);

	/**
	 * Resets the builder's state.
	 */
	void reset();

	/**
	 * Sets the URI for the Geometry.
	 * @param uri URI for the geometry.
	 */
	void setURI(const URIPtr& uri);

	/**
	 * Adds a mesh to the builder.
	 * @param mesh Mesh to add.
	 * @returns index of newly inserted mesh in internal vector.
	 */
	uint32_t addMesh(const MeshPtr& mesh);

	/**
	 * Adds a vector of meshes to the builder.
	 * @param meshes Meshes to add.
	 */
	void addMeshes(const MeshPtrVector& meshes);

private:
	URIPtr        mURI;
	MeshPtrVector mMeshes;
};


} /* namespace prtx */



#ifdef _MSC_VER
#	pragma warning(pop)
#endif

#endif /* PRTX_GEOMETRY_H_ */

