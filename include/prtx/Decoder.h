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

#ifndef PRTX_DECODER_H_
#define PRTX_DECODER_H_

#include <istream>

#include "prt/ContentType.h"
#include "prt/InitialShape.h"
#include "prt/Callbacks.h"

#include "prtx/prtx.h"
#include "prtx/Content.h"
#include "prtx/Texture.h"
#include "prtx/Geometry.h"
#include "prtx/CGB.h"
#include "prtx/Extension.h"
#include "prtx/ResolveMap.h"


namespace prtx {


class Decoder;
typedef boost::shared_ptr<Decoder> DecoderPtr;

/**
 * Base class for all decoders. A decoder accepts a byte stream and constructs one or more Content subclass objects from it.
 * Typically the byte stream is created by a StreamAdaptor from an URI (e.g. a file). A decoder then parses the stream
 * (e.g. a text stream from a Wavefront OBJ file) and creates the corresponding prtx::Geometry objects.
 *
 * For a list of built-in decoders, consult the <a href="../esri_prt_codecs.html">Built-In Codecs Reference</a>.
 */
class PRTX_EXPORTS_API Decoder : public Extension {
public:
	Decoder() { }
	virtual ~Decoder() { }

public:
	/**
	 * Accepts a byte stream and creates corresponding objects from Content derived classes.
	 * It is legal to defer parts of the stream to nested decoders or calling the DataBackend on dependent URIs.
	 *
	 * \sa Content
	 * \sa StreamAdaptor
	 * \sa ResolveMap
	 */
	virtual void decode(
			ContentPtrVector&		results,	///< [in,out] Receives the created content objects.
			std::istream&			stream,		///< [in] The input byte stream, typically created by a StreamAdaptor.
			prt::Cache*				cache,		///< [in] Cache object potentially necessary for nested calls to the DataBackend.
			const std::wstring&		key,		///< [in] Keys into resolveMap to retrieve the URI on which the stream is based.
			prtx::ResolveMap const*	resolveMap,	///< [in] See key.
			std::wstring&			warnings	///< [in,out] Decoders may append any warnings encountered during decoding to this string.
												///< The warnings will be collected and forwarded to the DataBackend.
	) = 0;

	/**
	 * Fixates the extension types of all subclasses to prtx::Extension::ET_DECODER.
	 *
	 * @returns Always returns prtx::Extension::ET_DECODER;
	 */
	virtual ExtensionType getExtensionType() const { return ET_DECODER; }
};


/**
 * Helper base class for all decoders which return prtx::Geometry as main decode result.
 * Note that such decoders typically also create dependent content objects such as
 * Mesh, Material, Texture.
 *
 * \sa prtx::Geometry
 */
class PRTX_EXPORTS_API GeometryDecoder : public Decoder {
public:
	GeometryDecoder() { }
	virtual ~GeometryDecoder() { }

	/**
	 * Fixates the content type to prt::CT_GEOMETRY.
	 *
	 * @return Always returns prt::CT_GEOMETRY.
	 */
	virtual prt::ContentType getContentType() const { return prt::CT_GEOMETRY; }
};


/**
 * Helper base class for all decoders which return prtx::Material as main decode result.
 * Note that such decoders typically also create dependent content objects such as Texture.
 *
 * \sa prtx::Material
 */
class PRTX_EXPORTS_API MaterialDecoder : public Decoder {
public:
	MaterialDecoder() { }
	virtual ~MaterialDecoder() { }

	/**
	 * Fixates the content type to prt::CT_MATERIAL.
	 *
	 * @return Always returns prt::CT_MATERIAL.
	 */
	virtual prt::ContentType getContentType() const { return prt::CT_MATERIAL; }
};


/**
 * Helper base class for all decoders which return prtx::Shader as main decode result.
 * Note that such decoders typically also create related content objects such as Material or Texture.
 *
 * \sa prtx::Shader
 */
class PRTX_EXPORTS_API ShaderDecoder : public Decoder {
public:
	ShaderDecoder() { }
	virtual ~ShaderDecoder() { }

	/**
	 * Fixates the content type to prt::CT_SHADER.
	 *
	 * @return Always returns prt::CT_SHADER.
	 */
	virtual prt::ContentType getContentType() const { return prt::CT_SHADER; }
};


/**
 * Helper base class for all decoders which return prtx::Texture as main decode result.
 *
 * \sa prtx::Texture
 */
class PRTX_EXPORTS_API TextureDecoder : public Decoder {
public:
	TextureDecoder() { }
	virtual ~TextureDecoder() { }

	/**
	 * Fixates the content type to prt::CT_TEXTURE.
	 *
	 * @return Always returns prt::CT_TEXTURE.
	 */
	virtual prt::ContentType getContentType() const { return prt::CT_TEXTURE; }
};


/**
 * Helper base class for all decoders which return prtx::CGB as main decode result.
 *
 * \sa prtx::CGB
 */
class PRTX_EXPORTS_API CGBDecoder : public Decoder {
public:
	CGBDecoder() { }
	virtual ~CGBDecoder() { }

	/**
	 * Fixates the content type to prt::CT_CGB.
	 *
	 * @return Always returns prt::CT_CGB.
	 */
	virtual prt::ContentType getContentType() const { return prt::CT_CGB; }
};


} // namespace prtx


#endif /* PRTX_DECODER_H_ */

