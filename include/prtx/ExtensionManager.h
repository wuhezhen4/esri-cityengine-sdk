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

#ifndef PRTX_EXTENSIONMANAGER_H_
#define PRTX_EXTENSIONMANAGER_H_

#include "prt/AttributeMap.h"
#include "prt/EncoderInfo.h"
#include "prt/DecoderInfo.h"
#include "prt/API.h"

#include "prtx/prtx.h"
#include "prtx/URI.h"
#include "prtx/ExtensionFactory.h"
#include "prtx/Adaptor.h"
#include "prtx/Decoder.h"
#include "prtx/Encoder.h"


#ifdef _MSC_VER
#	ifdef PRT_CC_DBG
#		pragma message(__FILE__": disabled MSVC warning 4275")
#	endif
#	pragma warning(push)
#	pragma warning (disable : 4275)
#endif


namespace prtx {


/**
 * The PRT plugin (extension) manager. This class is used as a singleton, see instance().
 * Its main use case is the creation of Adaptors, Decoders and Encoders based on their extension IDs and URIs.
 *
 * \sa prtx::Extension
 * \sa prtx::Encoder
 * \sa prtx::Decoder
 * \sa prtx::Adaptor
 */
class PRTX_EXPORTS_API ExtensionManager {
public:
	virtual ~ExtensionManager();

	/**
	 * Access to the ExtensionManager singleton
	 */
	static ExtensionManager& instance();

	/**
	 * Registers an extension factory class. Use this member function to register any custom
	 * extensions.
	 */
	virtual void addFactory(prtx::ExtensionFactory* factory) = 0;

	/**
	 * List all registered extensions of type prtx::Extension::ET_ENCODER.
	 *
	 * @param [out] result A string buffer with space for resultSize characters.
	 * @param [in,out] resultSize Specifies the size of result and receives the
	 * actually needed size of the result.
	 */
	virtual void listEncoderIds(wchar_t* result, size_t *resultSize) const = 0;

	/**
	 * List all registered extensions of type prtx::Extension::ET_DECODER.
	 *
	 * @param [out] result A string buffer with space for resultSize characters.
	 * @param [in,out] resultSize Specifies the size of result and receives the
	 * actually needed size of the result.
	 */
	virtual void listDecoderIds(wchar_t* result, size_t *resultSize) const = 0;

	/**
	 * Creates an encoder info object based on an encoder ID.
	 *
	 * @param [in] id The ID of the new info instance.
	 * @return A new EncoderInfo instance. Must be destroyed by the caller.
	 */
	virtual prt::EncoderInfo const* createEncoderInfo(const std::wstring& id) const = 0;

	/**
	 * Creates a decoder info object based on an decoder ID.
	 *
	 * @param [in] id The ID of the new decoder info instance.
	 * @return A new DecoderInfo instance. Must be destroyed by the caller.
	 */
	virtual prt::DecoderInfo const* createDecoderInfo(const std::wstring& id) const = 0;

	/**
	 * Creates an encoder instance based on its identifier. See listEncoderIds().
	 *
	 * @return A shared pointer to the new encoder instance.
	 */
	virtual EncoderPtr createEncoder(
			const std::wstring&			id,			///< [in] The ID of the encoder to be instantiated.
			const prt::AttributeMap*	options,	///< [in] Encoder options for the new instance.
			prt::Callbacks* const		callbacks	///< [in] Callbacks to be used by the new encoder instance.
	) const = 0;

	/**
	 * Creates a decoder instance which matches the content type and can handle a specific URI.
	 * If multiple compatible decoders are available the one with the highest merit is returned.
	 *
	 * @param [in] ct The content type of the desired decoder instance.
	 * @param [in] uri The URI which the decoder must be able to handle.
	 * @return A shared pointer to a new decoder instance.
	 *
	 * \sa prtx::Extension::getMerit()
	 */
	virtual DecoderPtr createDecoder(prt::ContentType ct, const prtx::URIPtr& uri) const = 0;

	/**
	 * Create a decoder directly by its identifier. See listDecoderIds().
	 *
	 * @return A shared pointer to the new decoder instance.
	 */
	virtual DecoderPtr createDecoder(const std::wstring& id) const = 0;

	/**
	 * Create a stream adaptor which matches the URI. If multiple adaptors can handle the URI
	 * the one with the highest merit is returned.
	 *
	 * @param [in] uri The uri which the adaptor must be able to handle.
	 * @return A shared pointer to the new adaptor instance.
	 */
	virtual StreamAdaptorPtr createStreamAdaptor(const prtx::URIPtr& uri) const = 0;

public:
	static void setInstance(ExtensionManager* theInstance);
	virtual void init(const wchar_t** prtPlugins, size_t prtPluginsCount) = 0;

protected:
	ExtensionManager();
};


} // namespace prtx


#ifdef _MSC_VER
#pragma warning(pop)
#endif


#endif /* PRTX_EXTENSIONMANAGER_H_ */

