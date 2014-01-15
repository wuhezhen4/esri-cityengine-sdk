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

#ifndef PRT_INITIALSHAPE_H_
#define PRT_INITIALSHAPE_H_

#include "prt/prt.h"
#include "prt/prt_stdint.h"
#include "prt/Object.h"
#include "prt/AttributeMap.h"
#include "prt/ResolveMap.h"
#include "prt/Cache.h"


namespace prt {


/**
 * An InitialShape is the fundamental input for the generation of a procedural model. It contains
 *  - a geometry (1D (e.g. a point), 2D (e.g. a building footrint) or 3D (e.g. a building mass model)
 *  - a rule file (a cgb file compiled from a cga rule)
 *  - a start rule (which must be defined in the rule file)
 *  - a random seed
 *  - a number of values for named (rule) attributes
 *  - a resolve map, used for resolving symbolic asset names ("keys") to real URIs
 *  all the above members are mandatory, i.e. must be set, and directly control the generation of
 *  the procedural model.
 *
 *
 * @sa generate(), InitialShapeBuilder
 */
class PRT_EXPORTS_API InitialShape : public Object {
public:
	/**
	 * @returns URI to the rule file.
	 */
	virtual wchar_t const*		getRuleFile()		const = 0;
	/**
	 * @returns Name of the start rule.
	 */
	virtual wchar_t const*		getStartRule()		const = 0;
	/**
	 * The name can be any string, i.e. must not be unique!
	 * @returns Name of the initial shape.
	 */
	virtual wchar_t const*		getName()			const = 0;
	/**
	 * @returns Random seed of the initial shape.
	 */
	virtual int32_t				getRandomSeed()		const = 0;
	/**
	 * @returns AttributeMap with the initial shape's (rule) attributes.
	 */
	virtual AttributeMap const*	getAttributeMap()	const = 0;
	/**
	 * @returns ResolveMap of the initial shape.
	 */
	virtual ResolveMap   const* getResolveMap()		const = 0;
	/**
	 * Returns a unique string which can be used for caching purposes.
	 * By default returns a memory URI of the InitialShape instance.
	 * Can be user-defined by setting the string attribute "/cache/key".
	 * Is used as cache key for shapetree caching.
	 *
	 * @returns Cache key of the initial shape.
	 */
	virtual const wchar_t*		getCacheKey()		const = 0;

protected:
	InitialShape();
	virtual ~InitialShape();
};


class PRT_EXPORTS_API InitialShapeBuilder : public Object {
protected:
	InitialShapeBuilder();
	virtual ~InitialShapeBuilder();

public:

	/**
	 * Creates an initial shape builder.
	 *
	 * @param stat Pointer to a Status object which will receive a status code.
	 * @return Pointer to InitalShape instance, must be destroy()-ed by the client.
	 */
	static InitialShapeBuilder* create(Status* status = 0);

	/**
	 * Creates an initial shape instance and resets the builder state to the default values.
	 */
	virtual InitialShape const* createInitialShapeAndReset(Status* status = 0) = 0;


	/**
	 * Sets the initial shape's geometry.
	 *
	 * @param vertexCoords       The vertex coordinates as (x,y,z) tuples: { x0, y0, z0, x1, y1, z1, ... }.
	 * @param vcCount            The size of vertexCoords == 3 * number of vertices.
	 * @param indices            The vertex indices per face: { f0i0, f0i1, f0i2, f0if0Count-1, ..., f1i0, ... }
	 * @param indicesCount       The size of indices.
	 * @param faceCounts         The number of vertices per face: { f0Count, f1Count, ... }
	 * @param faceCountsCount    The number of faces.
	 * @param holes              List which assigns hole-faces to faces.
	 * 							 Holes must have the same vertex-ordering as the encircling face.
	 *                           The Structure is: { face-with-holes1-idx, hole-face-idx1, hole-face-idx2, ..., MAX_UINT32_T, ..., face-with-holesn-idx, hole-face-idx1, hole-face-idx2, ..., MAX_UINT32_T }
	 * @param holesCount         The number of uint32_t entries in the array above.
	 * @return STATUS_OK on success or other detailed value in cause of failure.
	 */
	virtual Status setGeometry(double const*         vertexCoords,
			                   size_t                vcCount,
			                   uint32_t const*       indices,
			                   size_t                indicesCount,
			                   uint32_t const*       faceCounts,
			                   size_t                faceCountsCount,
			                   const uint32_t*       holes = 0,
			                   size_t                holesCount = 0) = 0;


	/**
	 * Sets the initial shape's uv coordinates (texture coordinates). The uvs must match the geometry set with  {@link #setGeometry()}.
	 * The sequence of {@link #setGeometry()}, {@link #setUvs()} and {@link #resolveTextures()} calls does not matter, but some parameters mus be consistent.
	 *
	 * @param uvCoords           The uv coords as (u,v) tuples: { u0, v0, u1, v1, ... }.
	 * @param uvCount            The number of texture coords = 2 * number of (u,v) tuples.
	 * @param indices            The uv indices per face.
	 * @param indicesCount       The uv indices per face (analogous to indices in {@link #setGeometry()}).
	 * @param faceCounts         The number of vertices per face: { f0Count, f1Count, ... } (== faceCounts in {@link #setGeometry()}).
	 * @param faceCountsCount    The number of faces (== faceCountsCount in {@link #setGeometry()})
	 * @return STATUS_OK on success or other detailed value in cause of failure.
	 */
	virtual Status setUVs(double const*         uvCoords,
                  		  size_t                uvcCount,
                   		  uint32_t const*       uvIndices,
			              size_t                uvIndicesCount,
                   		  uint32_t const*       faceCounts,
                          size_t                faceCountsCount) = 0;


	/**
	 * Sets up the initial shape''s material by resolving, loading and decoding the given textures. The @ref faceTextureIndices must match the geometry set with
	 * {@link #setGeometry()}.
	 * If a texture can not be resolved, STATUS_UNABLE_TO_RESOLVE is returned and builtin:unknowntexture.png is used for that texture.
	 *
	 * The sequence of {@link #setGeometry()}, {@link #setUvs()} and {@link #resolveTextures()} calls does not matter, but some parameters mus be consistent.
	 * @param textureKeys        The textures (keys into texturesResolveMap / uris if resolveMap is 0).
	 *                           0 or an empty string means 'no texture'.
	 * @param textureCount       The number of textures.
	 * @param faceTextureIndices Array with texture index for each face.
	 * @param facesCount         The number of faces (== faceCountsCount in {@link #setGeometry()}). This is the number of elements in @ref faceTextureIndices.
	 * @param resolveMap         ResolveMap to use for texture lookups
	 * @param cache              Cache to use for texture lookups. 0 for no caching.
	 * @return STATUS_OK on success or other detailed value in cause of failure.
	 */
	virtual Status resolveTextures(wchar_t const* const* textureKeys,
			                       size_t                textureCount,
			                       uint32_t const*       faceTextureIndices,
			                       uint32_t              facesCount,
			                       const ResolveMap*     resolveMap = 0,
			                       Cache*               cache      = 0) = 0;


	/**
	 * Sets an initial shape's geometry (plus uv coordinates and texturing if available) from an external resource.
	 * If an initial shape's geometry is loaded with @ref resolveGeometry, calls to setGeometry(), setUVs() and resolveTextures() are ignored.
	 *
	 * @param key             The key (into resolveMap) of the geometry asset to load.
	 *                        If resolveMap is 0, key is treated as a an uri.
	 * @param resolveMap      The resolveMap which contains key/uri entries for the key plus nested resources (such as a mtl file referenced by an obj file etc.).
	 * @param cache           Cache to use for texture lookups. 0 for no caching.
	 * @return STATUS_OK on success or other detailed value in cause of failure.
	 */
	virtual Status resolveGeometry(wchar_t const*      key,
			                       ResolveMap const*   resolveMap = 0,
			                       Cache*             cache      = 0) = 0;


	/**
	 * Sets the initial shape's attributes.
	 * The major purpose is to override rule attributes with concrete values in order to control the procedural model generation.
	 * However, any attribute name can be used; this allows for passing initial shape specific attributes to the encoder.
	 * There is a number of reserved attribute names for special purposes; if present they influence the model generation:
	 * @verbatim
	  L"streetWidth"                   - (float array) A semantic attribute to transport information about
	                                     streets adjacent to the initial shape.
	                                     If present it is used to evaluate the stret.xxx selectors in cga
	                                     (for instance in the comp() operation). The index into the array
	                                     corresponds to the edge-index, and the value corresponds to the
	                                     width of the street on that side. 0 means no street, a value > 0
	                                     means street.

	  L"/cgaenv/"                      - Reserved namespace for controlling the cga generation.
      L"/cgaenv/occlDisableIntra"      - Disable intra-model occlusion queries (i.e. they all return false);
                                         bool; default: false
	  L"/cgaenv/occlDisableInter"      - Disable inter-model occlusion queries (i.e. they all return false);
	                                     bool; default: false
	  L"/cgaenv/maxDerivationDepth"    - Maximum recursion level for cga operations;
	                                     int; default: 99
	  L"/cgaenv/maxDerivationWidth"    - Maximum shapetree width (for cga);
	                                     int; default: 50000
	  L"/cgaenv/maxFuncCallDepth"      - Maximum recursion level for cga functions;
	                                     int; default: 256
	  L"/cgaenv/floatCheck"            - Controls checking of float parameters of operation/built-in functions
	                                     for inf/nan values:
	                                      0 = ignore(don't check)
	                                      1 = check and abort if inf/nan detected,
	                                      2 = check and replace with 0  if inf/nan detected;
	                                     int; default: 2
	  L"/cgaenv/trimPlanesComputeSize" - The size of the computed trimplanes in meters;
	                                     float; default: 100.0
	  L"/cgaenv/touchesMaxDist",       - The maximum distance to distinct between touches and intersects;
	                                     float; default: 1e-3f

	  L"/cache/key"                    - Set the cache key associated to this initial shape. This allows e.g.
	                                     for re-using an initial shape's cache key with a different instance.
	                                     See also the generateOptions parameter of generate().
	 @endverbatim
	 *
	 *
	 * @param ruleFile           The cgb file (as a key into the resolveMap).
	 * @param startRule          The start rule, with style prefix (e.g. "Default$Init").  This will be the initialShape.startRule cga attribute.
	 * @param randomSeed         The random seed; this will be the seedian cga attribute of the initial shape.
	 * @param name               The name of the initial shape. This will be the initialShape.name cga attribute.
	 * @param attributes         The rule attributes.
	 * @param resolveMap         The resolve map to use in generate().
	 * @return STATUS_OK on success or other detailed value in cause of failure.
	 */
	virtual Status setAttributes(wchar_t const*        ruleFile,
			                     wchar_t const*        startRule,
			                     int32_t               randomSeed,
			                     wchar_t const*        name,
			                     AttributeMap const*   attributes,
			                     ResolveMap const*	   resolveMap) = 0;

	/**
	 * Compute a random seed from the initial shape geometry.
	 *
	 * @return A random seed computed from the initial shape geometry.
	 */
	virtual int32_t computeSeed() = 0;
};


} /* namespace prt */


#endif /* PRT_INITIALSHAPE_H_ */

