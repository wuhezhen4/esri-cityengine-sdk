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

#ifndef PRTX_ENCODER_H_
#define PRTX_ENCODER_H_

#include <vector>

#include "boost/shared_ptr.hpp"

#include "prt/AttributeMap.h"
#include "prt/InitialShape.h"
#include "prt/Callbacks.h"
#include "prt/ContentType.h"
#include "prt/Status.h"
#include "prt/CGAErrorLevel.h"

#include "prtx/prtx.h"
#include "prtx/Log.h"
#include "prtx/Extension.h"
#include "prtx/GenerateContext.h"


#ifdef _MSC_VER
#	ifdef PRT_CC_DBG
#		pragma message(__FILE__": disabled MSVC warnings 4251")
#	endif
#	pragma warning(push)
#	pragma warning (disable : 4251) // 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#endif


namespace prtx {


class Encoder;
typedef boost::shared_ptr<Encoder> EncoderPtr;
typedef std::vector<EncoderPtr> EncoderPtrVector;

/**
 * Base class for encoders. Subclasses typically want to implement Encoder::init, Encoder::encode and Encoder::finish.
 *
 * \sa prt::Callbacks
 */
class PRTX_EXPORTS_API Encoder : public Extension {
protected:
	Encoder();

public:
	/**
	 * Constructs an encoder instance. It is discouraged to call this directly, i.e. the corresponding
	 * EncoderFactory should be the only site which calls this constructor.
	 *
	 * \sa prt::AttributeMap
	 * \sa prt::Callbacks
	 */
	Encoder(
			const std::wstring&			id,				///< [in] The encoder ID (supplied by corresponding factory class).
			const prt::AttributeMap*	defaultOptions,	///< [in] The default encoder options (supplied by corresponding factory class).
			prt::Callbacks*				callbacks		///< [in] Client callbacks valid during the encoder life-time.
	);

	virtual ~Encoder();

	/**
	 * Implement this member function to setup data structures needed by your encoder before the first call to encode happens.
	 * This default implementation does nothing. It is legal to throw exceptions.
	 */
	virtual void init(
			GenerateContext& context					///< [in] The current generate context.
	);

	/**
	 * This member function can be implemented to check if an initial shape is valid for encoding, e.g. if the necessary
	 * initial shape attributes are present for the specific encoder to work properly.
	 * PRT only calls encode if the return value is true.
	 *
	 * @return Must return true if the initial shape is valid for encoding with this encoder.
	 * The default implementation always returns true. It is legal to throw exceptions.
	 */
	virtual bool validate(
			GenerateContext& context,					///< [in] The current generate context.
			size_t initialShapeIndex					///< [in] The active initial shape index,
														///< typically used it with GenerateContext::getInitialShape(size_t)
	) const;

	/**
	 * This encode member function is called once for each initial shape. This is where you can iterate over
	 * the shape tree to fetch any data necessary for your encoder. The default implementation does nothing.
	 * It is legal to throw exceptions.
	 */
	virtual void encode(
			GenerateContext& context,					///< [in] The current generate context.
			size_t initialShapeIndex					///< [in] The active initial shape index,
														///< typically used it with GenerateContext::getInitialShape(size_t)
	);

	/**
	 * This alternate encode member function is called from other encoders to defer encoding of other content objects.
	 * It is legal to throw exceptions.
	 */
	virtual void encode(
			const prtx::ContentPtrVector& content		///< [in] Content objects whose encoding has
														///< been deferred from a upstream encoder.
	);

	/**
	 * Implement this member function to free resources allocated by this encoder or to complete output handler operations.
	 * This member function is called once after the last initial shape has been encoded. It is called regardless of any
	 * encode or generation errors. It is legal to throw exceptions.
	 */
	virtual void finish(
			prtx::GenerateContext& context				///< [in] The current generate context.
	);

	/**
	 * Returns the extension type, i.e. ET_ENCODER.
	 */
	virtual ExtensionType getExtensionType() const;

	/**
	 * Returns the ID of this extension.
	 */
	const std::wstring& getID() const;

protected:
	/**
	 * Accessor to default options for subclasses.
	 */
	const prt::AttributeMap* getOptions() const;

	/**
	 * Accessor for callbacks for subclasses.
	 */
	prt::Callbacks* getCallbacks() const;

private:
	std::wstring				mID;
	const prt::AttributeMap*	mOptions;
	prt::Callbacks*				mCallbacks;
};


/**
 * Helper base class for all encoders which support the encoding of Geometry objects.
 * Note that such encoders typically also know how to encode (or defer) dependent
 * content objects such as Material and Texture.
 */
class PRTX_EXPORTS_API GeometryEncoder : public Encoder {
protected:
	GeometryEncoder();

public:
	GeometryEncoder(const std::wstring& id, const prt::AttributeMap* defaultOptions, prt::Callbacks* callbacks);
	virtual ~GeometryEncoder();

	/**
	 * Fixates the content type to prt::CT_GEOMETRY.
	 *
	 * @return Always returns prt::CT_GEOMETRY.
	 */
	virtual prt::ContentType getContentType() const;
};


/**
 * Helper base class for all encoders which support the encoding of Material objects.
 * Note that such encoders typically also know how to encode (or defer) dependent
 * content objects such as Texture.
 */
class PRTX_EXPORTS_API MaterialEncoder : public Encoder {
protected:
	MaterialEncoder();

public:
	MaterialEncoder(const std::wstring& id, const prt::AttributeMap* defaultOptions, prt::Callbacks* callbacks);
	virtual ~MaterialEncoder();

	/**
	 * Fixates the content type to prt::CT_MATERIAL.
	 *
	 * @return Always returns prt::CT_MATERIAL.
	 */
	virtual prt::ContentType getContentType() const;
};


/**
 * Helper base class for all encoders which support the encoding of Texture objects.
 */
class PRTX_EXPORTS_API TextureEncoder : public Encoder {
protected:
	TextureEncoder();

public:
	TextureEncoder(const std::wstring& id, const prt::AttributeMap* defaultOptions, prt::Callbacks* callbacks);
	virtual ~TextureEncoder();

	/**
	 * Fixates the content type to prt::CT_TEXTURE.
	 *
	 * @return Always returns prt::CT_TEXTURE.
	 */
	virtual prt::ContentType getContentType() const;
};


} // namespace prtx


#ifdef _MSC_VER
#	pragma warning(pop)
#endif


#endif /* PRTX_ENCODER_H_ */

