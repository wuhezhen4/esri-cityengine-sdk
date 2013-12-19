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

#ifndef PRTX_SHAPEUTILS_H_
#define PRTX_SHAPEUTILS_H_

#include "prt/Callbacks.h"

#include "prtx/prtx.h"
#include "prtx/Shape.h"
#include "prtx/InitialShape.h"


namespace prtx {


/** @namespace prtx::ShapeUtils
 * Utility functions for working with shapes.
 */
namespace ShapeUtils {


/**
 * Extracts the transformation matrix which transforms a shape's geometry to world coordinates.
 * This matrix depends on the actual geometry, the shape's attributes (scope, pivot) and the intialShape's
 * origin.
 *
 * @param shape
 * @param trafoMatrix [output parameter] 4x4 harmonic transformation matrix, column major (OpenGL)
 */
PRTX_EXPORTS_API void getGeometryToWorldTrafo(const Shape& shape, DoubleVector& trafoMatrix);




//PRTX_EXPORTS_API void getScopeToWorldTrafo(const Shape& shape, DoubleVector& trafoMatrix);

PRTX_EXPORTS_API void getPivotToWorldTrafo(const Shape& shape, DoubleVector& trafoMatrix);

/**
 * Extracts the transformation matrix which transforms from object coordinates to world coordinates.
 * This matrix depends on the intialShape's origin.
 *
 * @param shape
 * @param trafoMatrix [output parameter] 4x4 harmonic transformation matrix, column major (OpenGL)
 */
PRTX_EXPORTS_API void getObjectToWorldTrafo(const Shape& shape, DoubleVector& trafoMatrix);


/**
 * Transforms vIn (3 components) with the transformation matrix trafo (column first).
 */
PRTX_EXPORTS_API inline void transformPoint(const prtx::DoubleVector& trafo, const double* vIn, double* vOut) {
	assert(trafo.size() == 16);
	vOut[0] = trafo[0]*vIn[0] + trafo[4]*vIn[1] + trafo[ 8]*vIn[2] + trafo[12];
	vOut[1] = trafo[1]*vIn[0] + trafo[5]*vIn[1] + trafo[ 9]*vIn[2] + trafo[13];
	vOut[2] = trafo[2]*vIn[0] + trafo[6]*vIn[1] + trafo[10]*vIn[2] + trafo[14];
}


PRTX_EXPORTS_API void getBoundingBoxWorld(const prtx::Shape& shape, prtx::DoubleVector& bbMinMaxExtent);


/*
 * Combine a shape's material with the material of the shape's geometry.
 * The shape's material is written during cga generation. It defaults to "CityEngineMaterial".
 * As long as it isn't changed, it is overridden by it's geometrys material (e.g. if you inseert [i()]
 * a textured asset, material.colormap is set to that texture).
 * As soon as it is changed (via set(material.colormap, "meinefresse.jpg")), the shape material "wins".
 * It is not trivial, use this function.
 */
PRTX_EXPORTS_API MaterialPtr combineMaterials(const Material& shapeMat, const Material& meshMat);


// style$import.rule({t})
PRTX_EXPORTS_API std::wstring getStyledRuleSignature(const Shape& shape);

// style$import.rule
PRTX_EXPORTS_API std::wstring getStyledRuleName(const Shape& shape);

// import.rule
PRTX_EXPORTS_API std::wstring getRuleName(const Shape& shape);

// ({t})
PRTX_EXPORTS_API std::wstring getRuleArguments(const Shape& shape);

// ({evaluated parameters})
PRTX_EXPORTS_API std::wstring getRuleParameters(const Shape& shape);



} // namespace ShapeUtils


} // namespace prtx


#endif /* PRTX_SHAPEUTILS_H_ */

