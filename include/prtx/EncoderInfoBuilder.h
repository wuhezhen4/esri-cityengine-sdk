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

#ifndef PRTX_ENCODERINFOBUILDER_H_
#define PRTX_ENCODERINFOBUILDER_H_

#include <string>

#include "prt/ContentType.h"
#include "prt/EncoderInfo.h"

#include "prtx/prtx.h"
#include "prtx/Builder.h"
#include "prtx/EncodeOptionsValidator.h"
#include "prtx/FileExtensions.h"


#ifdef _MSC_VER
#	ifdef PRT_CC_DBG
#		pragma message(__FILE__": disabled MSVC warnings 4275")
#	endif
#	pragma warning(push)
#	pragma warning(disable : 4275)
#endif


class EncoderInfoImpl;


namespace prtx {


/**
 * Builder class for EncoderInfo objects.
 */
class PRTX_EXPORTS_API EncoderInfoBuilder : public PRTBuilder<const prt::EncoderInfo> {
public:
	EncoderInfoBuilder();
	virtual ~EncoderInfoBuilder();

	/**
	 * Creates a prt::EncoderInfo instance from the current builder state.
	 *
	 * @return A new prt::EncoderInfo instance. Needs to be destroyed by the caller.
	 */
	const prt::EncoderInfo* create(std::wstring* warnings = 0) const;

	/**
	 * Creates a prt::EncoderInfo instance from the current builder state and resets the builder state.
	 *
	 * @return A new prt::EncoderInfo instance. Needs to be destroyed by the caller.
	 */
	const prt::EncoderInfo* createAndReset(std::wstring* warnings = 0);

	/**
	 * Specifies the content type of the corresponding encoder.
	 */
	void setType(prt::ContentType type);

	/**
	 * Specifies the ID of the corresponding encoder.
	 */
	void setID(const std::wstring& id);

	/**
	 * Specifies the human-readable name of the corresponding encoder.
	 */
	void setName(const std::wstring& name);

	/**
	 * Specifies the human-readable description of the corresponding encoder.
	 */
	void setDescription(const std::wstring& desc);

	/**
	 * Convenience member function to directly specifiy a single file extension for the corresponding encoder.
	 */
	void setExtensions(const std::wstring& exts);

	/**
	 * Specifies the supported file extensions by the corresponding encoder.
	 */
	void setExtensions(const prtx::FileExtensions& exts);

	/**
	 * Specifies the icon for the corresponding encoder. Useful for UI generation code.
	 */
	void setIcon(
			const char* icon	///< [in] An icon as Base64-encoded PNG byte array.
	);

	/**
	 * Specify the default options of the corresponding encoder class.
	 * Takes over the ownership of defaultOptions.
	 */
	void setDefaultOptions(prt::AttributeMap const* defaultOptions);

	/**
	 * Registers a encoder-specific validator instance for the corresponding encoder.
	 * If no validator is set, only option key validation will take place,
	 * i.e. no option value validation will happen.
	 */
	void setValidator(prtx::EncodeOptionsValidatorPtr validator);

	/**
	 * Adds an annotation to a specific option. Use the prtx::AnnotationBuilder to create annotations.
	 * There is also the prtx::EncodeOptionsAnnotator helper class for a more convenient way to set annotations.
	 *
	 * Note: To make an encoder option appear in the CityEngine UI (version 2013.1 and later),
	 * the following annotations are mandatory:
	 * LABEL, ORDER, GROUP and DESCRIPTION
	 *
	 * @param [in] key The encoder option attribute key to annotate.
	 * @param [in] a The annotation instance. The ownership will be transferred. All annotations will be destroyed
	 * when the encoder info instance is destroyed.
	 */
	void addAnnotation(const std::wstring& key, const prt::Annotation* a);

	/**
	 * Specifies the mandatory initial shape attributes (key names and types) the corresponding encoders needs to operate.
	 * See prt::EncoderInfo::getMandatoryAttributes() for details.
	 *
	 * @param [in] mandatoryAttributes The attribute map with mandatory attributes. The ownership is transferred
	 * to the EncoderInfo object under construction.
	 */
	void setMandatoryAttributes(prt::AttributeMap const* mandatoryAttributes);

private:
	EncoderInfoImpl* mInfo;
};


} /* namespace prtx */


#ifdef _MSC_VER
#	pragma warning(pop)
#endif


#endif /* PRTX_ENCODERINFOBUILDER_H_ */

