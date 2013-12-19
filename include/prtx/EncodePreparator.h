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

#ifndef PRTX_ENCODEPREPARATOR_H_
#define PRTX_ENCODEPREPARATOR_H_

#include "boost/shared_ptr.hpp"
#include "boost/noncopyable.hpp"

#include "prtx/prtx.h"
#include "prtx/Shape.h"
#include "prtx/InitialShape.h"
#include "prtx/NamePreparator.h"


#ifdef _MSC_VER
#	ifdef PRT_CC_DBG
#		pragma message(__FILE__": disabled MSVC warnings 4275")
#	endif
#	pragma warning(push)
#	pragma warning(disable : 4275)
#endif


namespace prtx {


struct VertexNormalProcessor {
enum Action {
	PASS,							///< The vertex normals are not modified.
	DELETE_NORMALS,					///< The vertex normals are deleted.
	SET_MISSING_TO_FACE_NORMALS,	///< Any missing vertex normals will be set to the corresponding face normal.
	SET_ALL_TO_FACE_NORMALS			///< All vertex normals will be replaced with the corresponding face normal.
};
};

struct HoleProcessor {
enum Action {
	PASS,							///< Faces with holes are not modified.
	TRIANGULATE_FACES_WITH_HOLES,	///< Faces with holes will be triangulated.
	DELETE_HOLES,					///< Any holes will be deleted.
	CONVERT_HOLES_TO_FACES			///< Holes will be converted to regular faces.
};
};


class EncodePreparator;
typedef boost::shared_ptr<EncodePreparator> EncodePreparatorPtr;


/**
 * The EncodePreparator is the most important tool for encoder authors. It implements common geometry encoding tasks.
 * Its main purpose is to gather prtx::Shape objects from the generated shape tree and create exportable groups of
 * prtx::Geometry objects with associated prtx::Mesh, prtx::Material and prtx::Texture objects. It identifies identical
 * geometry, material and texture instances and allows for their efficient sharing (e.g. to implement instancing).
 *
 * The preparation process is triggered by calling fetchFinalizedInstances and can be controlled by
 * setting the appropriate PreparationFlags.
 *
 * A simple usage example looks like this:
 * \code{.cpp}
	#include "prtx/EncodePreparator.h"

	prtx::DefaultNamePreparator namePrep;

	// create two namespaces for mesh and material names
	prtx::NamePreparator::NamespacePtr nsMesh = namePrep.newNamespace();
	prtx::NamePreparator::NamespacePtr nsMaterial = namePrep.newNamespace();

	// create the preparator
	prtx::EncodePreparatorPtr encPrep = prtx::EncodePreparator::create(true, namePrep, nsMesh, nsMaterial);

	// add any number of shapes
	encPrep->add(...);
	// ...

	// setup some simple preparation flags
	prtx::EncodePreparator::PreparationFlags flags;
	flags.instancing(false).mergeByMaterial(true).triangulate(true);

	// trigger the preparation of the shapes added so far
	prtx::EncodePreparator::InstanceVector instances;
	encPrep->fetchFinalizedInstances(instances, flags);

	// the instances are now ready for the actual encoding...
 * \endcode
 */

class PRTX_EXPORTS_API EncodePreparator  : boost::noncopyable {
public:
	static const prtx::DoubleVector IDENTITY;
	class FinalizedInstance;
	typedef std::vector<FinalizedInstance> InstanceVector;
	class PreparationFlags;

public:
	/**
	 * Factory member function to create an encode preparator instance. Typically, an encoder keeps one
	 * preparator instance during its life-time to perform multiple add and fetch operations.
	 *
	 * @param [in] enforceTextureConsistency Matches the materials to the corresponding meshes. If true, any textures
	 * without corresponding texture coordinates in the mesh(es) will be deleted from the corresponding materials.
	 * @param [in] namePreparator See NamePreparator
	 * @param [in] nsMeshes The namespace for mesh names.
	 * @param [in] nsMaterials The namespace for material names.
	 *
	 * @return Returns a shared pointer to the preparator instance.
	 */
	static EncodePreparatorPtr create(
			bool 								enforceTextureConsistency,
			NamePreparator&						namePreparator,
			const NamePreparator::NamespacePtr&	nsMeshes,
			const NamePreparator::NamespacePtr&	nsMaterials
	);

	/**
	 * Adds a shape to the preparator.
	 * @param callbacks Must point to a callback instance with a valid cache.
	 * @param shape Typically a shape created by a ShapeIterator subclass.
	 */
	virtual void add(prt::Cache* cache, ShapePtr shape, const prt::AttributeMap* encAttrs = 0) = 0;

	/**
	 * Adds an initial shape to the preparator. This can be used to directly encode the geometry
	 * of an initial shape.
	 */
	virtual void add(prt::Cache* cache, const prtx::InitialShape& initialShape, size_t initialShapeIndex) = 0;

	/**
	 * Adds an existing geometry to the preparator, no instancing or shape material overrides are performed.
	 */
	virtual void add(GeometryPtr g, const prtx::DoubleVector* offset = 0) = 0;

	/**
	 * Create geometry instances with corresponding transformations from the accumulated shapes and resets the preparator.
	 * Please note that a material and texture pool is kept during the whole lifetime of the preparator in order
	 * to detect identical materials and textures.
	 *
	 * Any unused vertex attribute data (e.g. unused vertex coordinates) are removed from the meshes regardless of the
	 * preparator flags.
	 *
	 * @param [out] instances Receives the instances.
	 * @param [in] flags Preparation flags to control the preparation process.
	 *
	 * \sa FinalizedInstance
	 */
	virtual void fetchFinalizedInstances(
			InstanceVector&			instances,
			const PreparationFlags&	flags
	) = 0;

	/**
	 * Returns the world-space bounding box of the accumulated geometry.
	 *
	 * \sa prtx::BoundingBox
	 */
	virtual void getBoundingBox(prtx::BoundingBox& bbox) = 0;

	/**
	 * Returns an estimate of how much memory (in bytes) is consumed by the content added so far.
	 */
	virtual uint64_t getUsedMem() const = 0;

	/**
	 * Resets the preparator
	 */
	virtual void clear() = 0;

	virtual ~EncodePreparator();

protected:
	struct FinalizedInstanceBase {
		GeometryPtr             mGeometry;
		prtx::DoubleVector      mTransformation;
		prtx::MaterialPtrVector mMaterials;
		StringPtr               mInitialShapeName;
		StringPtr               mShapeName;
		uint32_t                mInitialShapeIndex;
		uint32_t                mShapeId;
		std::vector<uint32_t>   mMeshProperties;
		int                     mPrototype;
	};

	EncodePreparator();

	static FinalizedInstanceBase& getBase(FinalizedInstance& instance);

public:
	enum MeshProperties {
		ALL_MESH_FACES_CONVEX = 1 << 0,
		ALL_MESH_FACES_PLANAR = 1 << 1
	};

	/**
	 * Container class for a finalized (= prepared) geometry instance.
	 */
	class PRTX_EXPORTS_API FinalizedInstance : private FinalizedInstanceBase {
	public:
		static const uint32_t NO_INITIAL_SHAPE_INDEX = uint32_t(-1);
		static const uint32_t NO_SHAPE_ID = uint32_t(-1);

	public:
		/**
		 * Returns the prepared geometry with associated meshes, materials and textures.
		 * Note that the geometry is potentially shared across multiple instances.
		 */
		const GeometryPtr& getGeometry() const;

		/**
		 * Returns the to world transformation of this instance in column-major format.
		 */
		const prtx::DoubleVector& getTransformation() const;

		/**
		 * Returns the referenced material instances in this geometry instance.
		 */
		const prtx::MaterialPtrVector& getMaterials() const;

		/**
		 * Returns the finalized initial shape name.
		 * \sa prt::InitialShape
		 */
		const std::wstring& getInitialShapeName() const;

		/**
		 * Returns the finalized name of the shape this geometry comes from.
		 */
		const std::wstring& getShapeName() const;

		/**
		 * Returns the initial shape index.
		 */
		uint32_t getInitialShapeIndex() const;

		/**
		 * Returns the id of the shape this geometry comes from.
		 */
		uint32_t getShapeId() const;

		/**
		 * Returns the prototype index. All instances which share the same cached geometry
		 * (= backed by an URI) have the same index. Returns -1 if the geometry is not cached.
		 *
		 * \sa prt::Cache
		 */
		int getPrototypeIndex() const;

		/**
		 * Returns true if all faces of mesh at index meshIndex are convex.
		 * Note: will always return false unless PreparatorFlags::determineMeshProperties() has been set to true.
		 *
		 * \sa prtx::Geometry::getMeshes()
		 */
		bool allMeshFacesConvex(size_t meshIndex) const;

		/**
		 * Returns true if all faces of mesh at index meshIndex are planar.
		 * Note: will always return false unless PreparatorFlags::determineMeshProperties() has been set to true.
		 *
		 * \sa prtx::Geometry::getMeshes()
		 */
		bool allMeshFacesPlanar(size_t meshIndex) const;

	private:
		FinalizedInstanceBase& getBase();
		friend class EncodePreparator;
	};

	/**
	 * Container class for the preparation flags. This class provides a number of chainable setters to control
	 * the preparation process.
	 *
	 * \sa prtx::EncodePreparator::fetchFinalizedInstances()
	 */
	class PRTX_EXPORTS_API PreparationFlags {
	public:
		enum IndexSharing {
			/**
			 * All vertex attributes have independent indexing (= the most compact representation).
			 */
			INDICES_SEPARATE_FOR_ALL_VERTEX_ATTRIBUTES				= 0,

			/**
			 * Vertex coordinates and vertex normals will use the same index. Data is replicated if needed.
			 */
			INDICES_SAME_FOR_VERTICES_AND_NORMALS					= (1 << 0),

			/**
			 * Vertex coordinates and the first texture coordinate set will use the same index. Data is replicated if needed.
			 */
			INDICES_SAME_FOR_VERTICES_AND_FIRST_UV_SET				= (1 << 1),

			/**
			 * Vertex coordinates and all texture coordinate sets will use the same index. Data is replicated if needed.
			 */
			INDICES_SAME_FOR_VERTICES_AND_ALL_UV_SETS				= (1 << 2) | INDICES_SAME_FOR_VERTICES_AND_FIRST_UV_SET,

			/**
			 * Vertex coordinates, vertex normals and the first texture coordinate set will use the same index. Data is replicated if needed.
			 */
			INDICES_SAME_FOR_VERTICES_AND_NORMALS_AND_FIRST_UV_SET	= INDICES_SAME_FOR_VERTICES_AND_NORMALS | INDICES_SAME_FOR_VERTICES_AND_FIRST_UV_SET,

			/**
			 * All vertex attributes will use the same index. Data is replicated if needed.
			 */
			INDICES_SAME_FOR_ALL_VERTEX_ATTRIBUTES					= INDICES_SAME_FOR_VERTICES_AND_NORMALS | INDICES_SAME_FOR_VERTICES_AND_ALL_UV_SETS
		};

	public:
		PreparationFlags();

		/**
		 * If true, the preparator shares/reuses cached/identical geometry objects over multiple instances.
		 */
		PreparationFlags& instancing(bool v);

		/**
		 * If true, meshes with the same material are combined per fetch call.
		 */
		PreparationFlags& mergeByMaterial(bool v);

		/**
		 * If true, all meshes are triangulated.
		 */
		PreparationFlags& triangulate(bool v);

		/**
		 * All meshes are offset by (x,y,z).
		 */
		PreparationFlags& offset(double x, double y, double z);

		/**
		 * All meshes are offset by xyz. xyz is expected contain three double values.
		 */
		PreparationFlags& offset(const double* xyz);

		/**
		 * The specified operation is applied to all vertex normals.
		 *
		 * \sa VertexNormalProcessor
		 */
		PreparationFlags& processVertexNormals(VertexNormalProcessor::Action v);

		/**
		 * The specified action is applied to faces with holes.
		 *
		 * \sa HoleProcessor
		 */
		PreparationFlags& processHoles(HoleProcessor::Action v);

		/**
		 * If true, vertices will be merged together if they are closer than the distance
		 * specified with mergeToleranceVertices(float v).
		 */
		PreparationFlags& mergeVertices(bool v);

		/**
		 * If true, vertex normals will be merged if they are within the tolerance set by mergeToleranceNormals().
		 */
		PreparationFlags& cleanupVertexNormals(bool v);

		/**
		 * If true, texture coordinates will be merged if they are within the tolerance set by mergeToleranceUVs().
		 */
		PreparationFlags& cleanupUVs(bool v);

		/**
		 * Merge tolerance for vertex coordinates. See mergeVertices().
		 */
		PreparationFlags& mergeToleranceVertices(float v);

		/**
		 * Merge tolerance for vertex normals. See cleanupVertexNormals().
		 */
		PreparationFlags& mergeToleranceNormals(float v);

		/**
		 * Merge tolerance for texture coordinates. See cleanupUVs().
		 */
		PreparationFlags& mergeToleranceUVs(float v);

		/**
		 * Specify the index setup of the finalized meshes.
		 *
		 * \sa IndexSharing
		 */
		PreparationFlags& indexSharing(IndexSharing v);

		/**
		 * If true, performs a mesh analysis. The results can be accessed in FinalizedInstance::allMeshFacesConvex()
		 * and FinalizedInstance::allMeshFacesPlanar().
		 */
		PreparationFlags& determineMeshProperties(bool v);

		bool instancing() const;
		bool mergeByMaterial() const;
		bool triangulate() const;
		const double* offset() const;
		VertexNormalProcessor::Action processVertexNormals() const;
		HoleProcessor::Action processHoles() const;
		bool mergeVertices() const;
		bool cleanupVertexNormals() const;
		bool cleanupUVs() const;
		float mergeToleranceVertices() const;
		float mergeToleranceNormals() const;
		float mergeToleranceUVs() const;
		IndexSharing indexSharing() const;
		bool determineMeshProperties() const;

	private:
		bool mInstancing;
		bool mMergeByMaterial;
		bool mTriangulate;
		bool mDetermineMeshProperties;
		bool mMergeVertices;
		bool mCleanupVertexNormals;
		bool mCleanupUVs;
		VertexNormalProcessor::Action mVertexNormalAction;
		HoleProcessor::Action mHoleAction;
		IndexSharing mIndexSharing;
		float mMergeToleranceVertices;
		float mMergeToleranceNormals;
		float mMergeToleranceUVs;
		double mOffset[3];
	};
};


} // namespace prtx


#ifdef _MSC_VER
#	pragma warning(pop)
#endif


#endif /* PRTX_ENCODEPREPARATOR_H_ */

