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

#ifndef PRT_CACHE_H_
#define PRT_CACHE_H_

#include "prt/Object.h"
#include "prt/ContentType.h"


namespace prt {


/**
 * The Cache interface is a callback interface which can be implemented by the client.
 *
 * Procedural Runtime's internal databackend, which resolves URIs to texture/geometry/cgb/material resources,
 * uses this interface to insert and lookup resolved resources.
 *
 * A cache entry is identified with a unique string (key), typically an URI.
 * There are two major types of cache entries:
 *   * transient:  these are non-serializable, prt-internal resources; the data contains
 *                 a reference to an internal refcount pointer, size is sizeof(void*)
 *   * persistent: these are typed, serializable data blocks; some transient resources are
 *                 an aggregation of datablocks. This allows for
 *                 * redundacy removal
 *                 * direct insertion of datablocks into the cache from some other source
 *                   to bypass the resolve step
 *                 * lazy-loading of datablocks
 *
 * Currently, persistent blobs are only implemented for textures. Persistent blobs can be locked and reserved:
 * Locked means the Cache knows the content (and it's guaranteed that a call to getPersistentBlob() succeeds).
 * Reserved means the Cache has the content in memory (and a pointer associatd to it).
 *
 *
 * A number of cache implementations is provided in CacheObject.
 *
 * @sa CacheObject, prtx::DataBackend
 */
class PRT_EXPORTS_API Cache {
public:
	/**
	 * Types of persistent blobs.
	 *
	 *@verbatim
	  IMAGE_METADATA V3:
	    uint32_t  Version              // 3
	    uint32_t  MD5Hash[4]           // md5 hash of associated pixeldata
	    uint32_t  Width                // width of associated pixeldata
	    uint32_t  Height               // height of associated pixedata
	    uint32_t  Format               // GREY8 = 1, GREY16 = 2, RGB8 = 3, RGBA8 = 4, FLOAT32 = 5
 	    double    Offset[3]            // georef: offset per channel (default: 0)
 	    double    Scale[3]             // georef: scale per channel  (default: 1)
 	    double    NoDataValue[3]       // georef: no data value markers per channel (default: MAX_DOUBLE)
 	    char      Unit[32]             // georef: semicolon separated strings per channel (default: empty)
 	    double    GeoTransform[6]      // georef: see GDALDataset::GetGeoTransform() function of GDAL (default: [0 1 0 0 0 1])
 	    char      ProjectionRef[1024]  // georef: "Well-known text" string describing the spacial reference system (default: empty)
 	  PIXELDATA:
 	    the decoded pixeldata, size = width*height*channels
 	 @endverbatim
	 */
	enum PersistentBlobType { CACHE_TYPE_IMAGE_METADATA, CACHE_TYPE_PIXELDATA };

	/**
	 * @param type Type of the resource.
	 * @param key  Unique string to identify the resource.
	 * @return The transient resource if known, 0 otherwise.
	 */
	virtual const void* getTransientBlob(ContentType type, const wchar_t* key) = 0;

	/**
	 * @param type Type of the resource.
	 * @param key  Unique string to identify the resource.
	 * @param ptr   Pointer to a transient resource,
	 * @return ptr or another, previously inserted pointer to a transient resource with identical permanent blob layout.
	 */
	virtual const void* insertTransientBlob(ContentType type, const wchar_t* key, const void* ptr) = 0;

	/**
	 * Tries to lock all persistent blobs associated with a (transient) key. \
	 * If the layout + the permanent blobs are known to the cache, they are locked
	 * (i.e. prevented from being deleted from permanent storage).
	 *
	 * @param type Type of the resource.
	 * @param key  Unique string to identify the resource.
	 * @return true if the permanent blobs are known, else false.
	 */
	virtual bool tryLockPersistentBlobs(ContentType type, const wchar_t* key) = 0;

	/**
	 * Inserts a persistent data blob connected to a key and locks it.
	 *
	 * @param type Type of the resource.
	 * @param key  Unique string to identify the resource.
	 * @param data Pointer to data to insert.
	 * @param size Size of data to insert in bytes.
	 */
	virtual void insertPersistentBlobAndLock(PersistentBlobType type, const wchar_t* key, const void* data, size_t size) = 0;

	/**
	 * Gets the pointer to a (locked) persistent blob plus it's size. The pointer is guaranteed to stay valid ("reserved") until
	 * releasePersistentBlob() is called.
	 *
	 * If (type, key) does not refer to a previously locked blob the behaviour is undefined.
	 *
	 * @param      type Type of the resource.
	 * @param      key  Unique string to identify the resource.
	 * @param[out] size Pointer to return the blob size in bytes.
	 * @returns Pointer to the persistent blob.
	 *
	 */
	virtual const void* getPersistentBlob(PersistentBlobType type, const wchar_t* key, size_t* size) = 0;

	/**
	 * Releases the pointer assigned to a persistent blob.
	 *
	 * @param      type Type of the resource.
	 * @param      key  Unique string to identify the resource.
	 *
	 */
	virtual void releasePersistentBlob(PersistentBlobType type, const wchar_t* key) = 0;

	/**
	 * Unlocks a persistent blob. Unlocked blobs can be deleted from persistent storage, reserved pointers stay
	 * valid however.
	 *
	 * @param      type Type of the resource.
	 * @param      key  Unique string to identify the resource.
	 */
	virtual void unlockPersistentBlob(PersistentBlobType type, const wchar_t* key) = 0;


      /**
       * Releases all transient blobs stored in the cache. If a transient blob is not still referenced anywhere
       * else in the Procedural Runtime and references
       * permanent blobs in the cache, the permanent blobs are released from the cache.
       * Is typically called from the client and must be thread-safe.
       *
       * @sa flushContentType(), flushEntry()
       */
      virtual void flushAll() = 0;
      /**
       * Releases all transient blobs of a certain ContentType.
       * If a transient blob is not still referenced anywhere else in the Procedural Runtime and references
       * permanent blobs in the cache, the permanent blobs are released from the cache.
       * Is typically called from the client and must be thread-safe.
       *
       * @sa flushAll(), flushEntry()
       *
       * @param      type Type of the resource.
       *
       */
      virtual void flushContentType(ContentType type) = 0;
      /**
       * Releases one specific transient blob from the cache.
       * If a transient blob is not still referenced anywhere else in the Procedural Runtime and references
       * permanent blobs in the cache, the permanent blobs are released from the cache.
       * Is typically called from the client and must be thread-safe.
       *
       * @sa flushAll(), flushContentType()
       *
       * @param      type Type of the resource.
       * @param      key  Unique string to identify the resource.
       */
      virtual void flushEntry(ContentType type, const wchar_t* key) = 0;


protected:
	/**
	 * Call this to tell Procedural Runtime that the Cache's reference to a transient resource was released (i.e. it was internally deleted
	 * from the cache). This is typically called in the Cache's destructor.
	 * @param ptr the transient blob to release.
	 */
	static void releaseTransientBlob(const void *ptr);

protected:
	Cache();
	virtual ~Cache();
};


/**
 * Base class for Cache implementations provided by Procedural Runtime.
 */

class PRT_EXPORTS_API CacheObject : public Object, public Cache {
public:
	/**
	 * The built-in cache implementations:
	 *
	 @verbatim
	 CACHE_TYPE_DEFAULT:
	   A straight-forward cache implementation.
	 CACHE_TYPE_NONREDUNDAND:
	   Detects identical permanent blobs (i.e. textures) and removes that redundancy.
	 @endverbatim
	 */
	enum CacheType { CACHE_TYPE_DEFAULT, CACHE_TYPE_NONREDUNDANT, CACHE_TYPE_COUNT };
	static CacheObject* create(CacheType type);
};


} // namespace prt


#endif /* PRT_CACHE_H_ */

