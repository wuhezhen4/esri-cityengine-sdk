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

#ifndef PRT_CONTENTTYPE_H_
#define PRT_CONTENTTYPE_H_


namespace prt {


/**
 * Encodes the types handled by Decoders and Encoders.
 */
enum ContentType {
	CT_UNDEFINED,		///< extension does not make use of specific content type, e.g. adaptor extensions
	CT_GEOMETRY,		///< extension can handle geometries (and potentially also materials and textures)
	CT_MATERIAL,		///< extension can handle materials (and potentially also textures)
	CT_TEXTURE,			///< extension can handle textures
	CT_SHADER,			///< extension can handle shader resources
	CT_CGB,				///< extension can handle CGB resources
	CT_INITIALSHAPE,	///< (reserved) extension can handle initial shape
	CT_CGAERROR,		///< extension can handle CGA error events
	CT_CGAPRINT,		///< extension can handle CGA print events
	CT_CGAREPORT,		///< extension can handle CGA report events
	CT_ATTRIBUTE,		///< extension can handle CGA attributes
	CT_SHAPETREE,		///< extension can handle shape trees
	CT_COUNT			///< sentinel value
};


} // namespace prt


#endif /* PRT_CONTENTTYPE_H_ */

