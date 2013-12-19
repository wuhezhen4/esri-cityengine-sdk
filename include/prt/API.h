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

#ifndef PRT_API_H_
#define PRT_API_H_

#include "prt/prt.h"
#include "prt/Status.h"
#include "prt/InitialShape.h"
#include "prt/RuleFileInfo.h"
#include "prt/EncoderInfo.h"
#include "prt/DecoderInfo.h"
#include "prt/LogLevel.h"
#include "prt/LogHandler.h"
#include "prt/Callbacks.h"
#include "prt/Version.h"
#include "prt/OcclusionSet.h"


/** @namespace prt
 * @brief The Procedural Runtime API namespace.
 * The prt namespace contains the top level entry points into the Procedural Runtime API.
 */

/**
 * Base struct for (loader)implementation-dependent licensing information.
 */
namespace prt {

// --- MAIN PRT API CALLS

/**
 * Base structure for (loader)implementation-dependent licensing information.
 */
struct LicParams {};

/**
 * Performs global Procedural Runtime initialization. Must only be called once, else will fail with STATUS_ALREADY_INITIALIZED.
 * Is thread-safe.
 * Blocks until initialization is done.
 * @sa FlexLicParams
 *
 * @param prtPlugins      List of paths to shared libraries or paths of directories to scan for shared libraries.
 * @param prtPluginsCount Number of plugin paths provided.
 * @param logLevel        Loglevel to use
 * @param lic             Licensing Information (loader dependent).
 * @param[out] stat       Optional pointer to return the status.
 * @return                A "license handle" object which must be destroyed to release the license.
 */
PRT_EXPORTS_API const Object* init(
		const wchar_t**	 prtPlugins,
		size_t			 prtPluginsCount,
		LogLevel		 logLevel,
		const LicParams* lic,
		Status*          stat = 0
);



/**
 * Generate and encode procedural models for a number of initial shapes.
 *
 * Must be called after init(), will return STATUS_NOT_INITIALIZED else.
 * Is thread-safe.
 *
 *
 * @sa Callbacks.
 *
 * @param initialShapes        The initial shapes for which the procedural models have to be generated.
 * @param initialShapeCount    The number of initial shapes in the array.
 * @param occlusionHandles One occlusion handle for each initial shape. Set to 0 for no inter-model occlusion tests.
 *                             Use generateOccluders() to obtain the occlusion handles.
 * @param encoders             A number (>= 1) of encoders to use to encode the generated model. The encoders are identified by their ID, see EncoderInfo::getID().
 * @param encodersCount        The number of encoder ids in the array.
 * @param encoderOptions       One AttributeMap with the enocder options for each encoder.
 * @param callbacks            Pointer to an instance of an implementation of the Callbacks interface.
 * @param cache                Pointer to an instance of an implementation of the Cache interface. See CacheObject.
 * @param occlSet              The OcclusionSet which contains the occlusionHandles. Set to 0 for no inter-model occlusion tests.
 * @param generateOptions      An optional AttributeMap to set advanced generate options.<br>
 *                              int  "numberWorkerThreads": number of worker threads to internally use for generation. 0 = no multithreading = default<br>
		                        bool "cacheShapeTree": cache the generated shapetrees. default = false.
 * @return a status code.
 */
PRT_EXPORTS_API Status generate(
		const InitialShape** const	initialShapes,
		size_t						initialShapeCount,
		const uint64_t*				occlusionHandles,		// IN, can be 0
		const wchar_t**				encoders,
		size_t						encodersCount,
		const AttributeMap**		encoderOptions,
		Callbacks*					callbacks,
		Cache*						cache,
		const OcclusionSet*			occlSet,				// read-only, can be 0
		const AttributeMap*			generateOptions = 0
);

/**
 * Populate an OcclusionSet with occluder geometries for each initial shape and return an occlusion handle for each one.
 * These handles (and the OcclusionSet) can then be used to generate() modles based on rules with inter-model
 * occlusion queries.
 *
 * Must be called after init(), will return STATUS_NOT_INITIALIZED else.
 * Is thread-safe.
 *
 * @sa Callbacks.
 *
 * @param initialShapes         The initial shapes for which the occluders have to be generated.
 * @param initialShapeCount     The number of initial shapes in the array.
 * @param[out] occlusionHandles Must be preallocated to hold initialShapeCount occlusion Handles, one for each initial shape.
 *                              occlusionHandles[i] will receive the occlusin handle for initialShapes[i].
 * @param encoders              Optional encoders to run on the generated shapetree. Set to 0 if no extra encoders
 *                              should be used.
 *                              Note that many encoders only consider leaf shapes and do not capture
 *                              the correct occluder geometry; these are typically the encoders from the
 *                              com.esri.prt.codecs plugin.
 *                              Encoders which traverse the whole shapetree (such as com.esri.prt.core.CGAPrintEncoder,
 *                              com.esri.prt.core.CGAErrorEncoder or com.esri.prt.core.CGAReportEncoder) can safely be used here.
 * @param encodersCount         The number of encoder ids in the array.
 * @param encoderOptions        Options for the additional encoders. Use 0 if no encoders are used.
 * @param callbacks             Pointer to an instance of an implementation of the Callbacks interface.
 * @param cache                 Pointer to an instance of an implementation of the Cache interface. See CacheObject.
 * @param occlSet               The OcclusionSet which will be filled with the generated the occlusionHandles.
 * @param generateOptions       An optional AttributeMap to set generate options.
 * @return a status code.
 */
PRT_EXPORTS_API Status generateOccluders(
		const InitialShape** const	initialShapes,
		size_t						initialShapeCount,
		prt::OcclusionSet::Handle*	occlusionHandles,
		const wchar_t**				encoders,
		size_t						encodersCount,
		const AttributeMap**		encoderOptions,
		Callbacks*					callbacks,
		Cache*						cache,
		OcclusionSet*				occlSet,
		const AttributeMap*			generateOptions = 0
);

/**
 * Creates a RuleFileInfo instance for a cgb file.
 *
 * Must be called after init(), will return STATUS_NOT_INITIALIZED else.
 * Is thread-safe.
 * The returned instance must be destroyed by the caller.
 *
 * @param ruleFileURI URI to the cgb file.
 * @param cache       Optional Cache instance.
 * @param[out] stat   Optional pointer to return the status.
 * @returns Pointer to a RuleFileInfo instance on success or 0 on failure.
 */
PRT_EXPORTS_API RuleFileInfo const* createRuleFileInfo(
		const wchar_t*	ruleFileURI,
		Cache*			cache = 0,
		Status*			stat = 0
);

/**
 * Create a ResolveMap for a rpk. The entries will point into the rpk.
 *
 * Must be called after init(), will return STATUS_NOT_INITIALIZED else.
 * Is thread-safe.
 * The returned instance must be destroyed by the caller.
 *
 * @param rpkURI             URI to the rpk.
 * @param unpackToFileSystem If true, the rpk gets unpacked to a temporary directory in the filesystem
 *                           and the ResolveMap entries will point to those files.
 * @param[out] stat       Optional pointer to return the status.
 * @returns Pointer to ResolveMap instance on success or 0 on failure.
 *
 */
PRT_EXPORTS_API ResolveMap const* createResolveMap(
		const wchar_t*	rpkURI,
		bool			unpackToFileSystem = false,
		Status*			stat = 0
);


// --- EXTENSIONS

/**
 * Lists all registered encoders.
 * If the result does not fit into the allocated buffer, the result is truncated. the INOUT parameter resultSize must be compared to
 * the original buffer size after the call to detect this situation.
 *
 * Must be called after init(), will return STATUS_NOT_INITIALIZED else.
 * Is thread-safe.
 *
 * @sa EncoderInfo, createEncoderInfo
 *
 * @param[in,out] result     Pointer to pre-allocated string to receive the semicolon-separated list of encoder ids.
 * @param[in,out] resultSize Pointer to size of reserved buffer; receives the size of the actual result (incl. terminating 0).
 * @returns status.
 */
PRT_EXPORTS_API Status   listEncoderIds(wchar_t* result, size_t* resultSize);

/**
 * Lists all registered decoders.
 * If the result does not fit into the allocated buffer, the result is truncated. the INOUT parameter resultSize must be compared to
 * the original buffer size after the call to detect this situation.
 *
 * Must be called after init(), will return STATUS_NOT_INITIALIZED else.
 * Is thread-safe.
 *
 * @sa DecoderInfo, createDecoderInfo
 *
 * @param[in,out] result     Pointer to pre-allocated string to receive the semicolon-separated list of decoder ids.
 * @param[in,out] resultSize Pointer to size of reserved buffer; receives the size of the actual result (incl. terminating 0).
 * @returns status.
 */
PRT_EXPORTS_API Status   listDecoderIds(wchar_t* result, size_t* resultSize);

/**
 * Creates an EncoderInfo instance for the given encoder id.
 *
 * Must be called after init(), will return STATUS_NOT_INITIALIZED else.
 * Is thread-safe.
 * The returned instance must be destroyed by the caller.
 *
 * @sa EncoderInfo, listEncoderIds
 *
 * @param encoderID  ID of encoder to get EncoderInfo for.
 * @param[out] stat  Optional pointer to return the status.
 * @returns Pointer to EncoderInfo instance on success or 0 on failure.
  */
PRT_EXPORTS_API EncoderInfo const* createEncoderInfo(const wchar_t* encoderId, Status* stat = 0);

/**
 * Creates an DecoderInfo instance for the given decoder id.
 *
 * Must be called after init(), will return STATUS_NOT_INITIALIZED else.
 * Is thread-safe.
 * The returned instance must be destroyed by the caller.
 *
 * @sa DecoderInfo, listDecoderIds
 *
 * @param encoderID  ID of encoder to get EncoderInfo for.
 * @param[out] stat  Optional pointer to return the status.
 * @returns Pointer to DecoderInfo instance on success or 0 on failure.
  */
PRT_EXPORTS_API DecoderInfo const* createDecoderInfo(const wchar_t* decoderId, Status* stat = 0);


// --- TEXTURE HANDLING

/**
 * Creates a AttributeMap with the metadata for a given texture URI.
 * See prtx::Texture for a list of supported metadata attributes.
 *
 * Must be called after init(), will return STATUS_NOT_INITIALIZED else.
 * Is thread-safe.
 * The returned instance must be destroyed by the caller.
 *
 * @sa getTexturePixeldata(), Attributable::PrimitiveType, prtx::Texture
 *
 * @param uri         URI of the texture.
 * @param cache       Optional Cache instance.
 * @param[out] stat   Optional pointer to return the status.
 * @returns Pointer to a AttributeMap instance on success or 0 on failure.
 *
 */
PRT_EXPORTS_API const AttributeMap* createTextureMetadata(
		const wchar_t*	uri,
		Cache*			cache = 0,
		Status*			stat = 0
);

/**
 * Reads and decodes a texture and copies the pixel data to the passed buffer.
 *
 * Must be called after init(), will return STATUS_NOT_INITIALIZED else.
 * Is thread-safe.
 *
 * @param uri         URI of the texture.
 * @param[out] buffer Pointer to pre-allocated buffer. The needed size can be calculated with createTextureMetadata() (width*height*depth).
 * @param bufferSize  Size of the pre-allocated buffer.
 * @param cache       Optional Cache instance.
 * @returns status.
 *
 */
PRT_EXPORTS_API Status getTexturePixeldata(
		const wchar_t*	uri,
		uint8_t*		buffer,
		size_t			bufferSize,
		Cache*			cache = 0
);

/**
 * Encodes the passed texture and writes the result to the passed SimpleOutputCallbacks instance.
 *
 * @param metadata       The textures metadata, must contain width/height/format attributes. Other attributes are currently ignored.
 * @param pixeldata      The pixeldata to encode
 * @param encoderId      Id of the encoder to use.
 * @param encoderOptions Options for the encoder. This includes the filename.
 * @param soc            The SimpleOutputCallbacks instance which will receive the encoded texture.
 * @returns status.
 */
PRT_EXPORTS_API Status encodeTexture(
		const AttributeMap*		metadata,
		const uint8_t*			pixeldata,
		const wchar_t*			encoderId,
		const AttributeMap*		encoderOptions,
		SimpleOutputCallbacks*	soc
);


// --- UTILS

/**
 * Returns a human readable description based on a status value.
 */
PRT_EXPORTS_API const char* getStatusDescription(Status stat);

/**
 * Returns the Version struct with information about the current Procedural Runtime.
 */
PRT_EXPORTS_API Version const* getVersion();


// --- LOGGING

/**
 * Register a log handler, can be called at any time
 * (also before init()).
 * Is thread-safe.
 *
 * @param logHandler LogHandler to register.
 * @returns status.
 */
PRT_EXPORTS_API Status	addLogHandler(LogHandler* logHandler);

/**
 * Remove a previously registered log handler, can be called
 * at any time (also before init()).
 * Is thread-safe.
 *
 * @param logHandler LogHandler to remove.
 * @returns status.
 */
PRT_EXPORTS_API Status	removeLogHandler(LogHandler* logHandler);

/**
 * Injects a log message into the PRT log dispatcher, can be called
 * at any time (also before init()).
 * Is thread-safe.
 *
 * @param msg   Message to log.
 * @param level LogLevel of the message.
 * @returns status.
 */
PRT_EXPORTS_API Status	log(const wchar_t* msg, LogLevel level);


} /* namespace prt */


#endif /* PRT_API_H_ */

