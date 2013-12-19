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

#ifndef PRT_ATTRIBUTEMAP_H_
#define PRT_ATTRIBUTEMAP_H_

#include "prt/prt.h"
#include "prt/Attributable.h"
#include "prt/Object.h"


namespace prt {


/**
 * A map implementing the Attributable interface. Use an AttributeMapBuilder to create an AttributeMap instance.
 */
class PRT_EXPORTS_API AttributeMap : public Attributable, public Object {
protected:
	AttributeMap();
	virtual ~AttributeMap();
};


/**
 * A builder to create AttributeMap instances.
 */
class PRT_EXPORTS_API AttributeMapBuilder : public Object {
public:
	/**
	 * Creates a new AttributeMapBuilder instance.
	 *
	 * @param[out] stat       Optional pointer to return the status.
	 * @returns Pointer to a new instance of an AttributeMapBuilder on success or 0 on failure.
	 */
	static	AttributeMapBuilder*	create(Status* status = 0);

	/**
	 * Creates a new AttributeMapBuilder instance initialized to the content of a AttributeMap.
	 *
	 * @param      src        Source AttributeMap. The new instance wil be initialized to the values of src.
	 * @param[out] stat       Optional pointer to return the status.
	 * @returns Pointer to a new instance of an AttributeMapBuilder on success or 0 on failure.
	 */
	static	AttributeMapBuilder*	createFromAttributeMap(const AttributeMap* src, Status* status = 0);

	/**
	 * Creates a new AttributeInstance which contains all currently set key-value pairs. The AttributeBuilder is reset to
	 * its initial state.
	 *
	 * @param[out] stat       Optional pointer to return the status.
	 * @returns Pointer to a new instance of an AttributeMap on success or 0 on failure.
	 */
	virtual AttributeMap const*		createAttributeMapAndReset(Status* status = 0) = 0;

	/**
	 * Creates a new AttributeInstance which contains all currently set key-value pairs. The AttributeBuilder's state is preserved.
	 *
	 * @param[out] stat       Optional pointer to return the status.
	 * @returns Pointer to a new instance of an AttributeMap on success or 0 on failure.
	 */
	virtual AttributeMap const*		createAttributeMap(Status* status = 0) const = 0;

	/**
	 * Resets the AttributeMapBiulder to the content of the passed AttributeMap.
	 *
	 * @param      src        Source AttributeMap. The new instance wil be initialized to the values of src.
	 * @param[out] stat       Optional pointer to return the status.
	 */
	virtual void resetToAttributeMap(const AttributeMap* src, Status* status = 0) = 0;

	/**
	 * Sets a boolean.
	 *
	 * @param key     Key to set.
	 * @param value   Value to copy.
	 * @returns STATUS_OK on success, STATUS_KEY_ALREADY_TAKEN or other status on failure.
	 */
	virtual Status				setBool			(const wchar_t* key, bool				value) = 0;
	/**
	 * Sets an integer.
	 *
	 * @param key     Key to set.
	 * @param value   Value to copy.
	 * @returns STATUS_OK on success, STATUS_KEY_ALREADY_TAKEN or other status on failure.
	 */
	virtual Status				setInt			(const wchar_t* key, int32_t			value) = 0;
	/**
	 * Sets a float value.
	 *
	 * @param key     Key to set.
	 * @param value   Value to copy.
	 * @returns STATUS_OK on success, STATUS_KEY_ALREADY_TAKEN or other status on failure.
	 */
	virtual Status				setFloat		(const wchar_t* key, double			    value) = 0;
	/**
	 * Sets a string.
	 *
	 * @param key     Key to set.
	 * @param value   Pointer to string to copy.
	 * @returns STATUS_OK on success, STATUS_KEY_ALREADY_TAKEN or other status on failure.
	 */
	virtual Status				setString		(const wchar_t* key, const wchar_t*	    value) = 0;

	/**
	 * Sets an array of booleans.
	 *
	 * @param key     Key to set.
	 * @param value   Pointer to the array to copy.
	 * @param count   Number of elements to copy.
	 * @returns STATUS_OK on success, STATUS_KEY_ALREADY_TAKEN or other status on failure.
	 */
	virtual Status				setBoolArray	(const wchar_t* key, const bool*		value, size_t count) = 0;
	/**
	 * Sets an array of integers.
	 *
	 * @param key     Key to set.
	 * @param value   Pointer to the array to copy.
	 * @param count   Number of elements to copy.
	 * @returns STATUS_OK on success, STATUS_KEY_ALREADY_TAKEN or other status on failure.
	 */
	virtual Status				setIntArray		(const wchar_t* key, const int32_t*	    value, size_t count) = 0;
	/**
	 * Sets an array of floats.
	 *
	 * @param key     Key to set.
	 * @param value   Pointer to the array to copy.
	 * @param count   Number of elements to copy.
	 * @returns STATUS_OK on success, STATUS_KEY_ALREADY_TAKEN or other status on failure.
	 */
	virtual Status				setFloatArray	(const wchar_t* key, const double*	    value, size_t count) = 0;
	/**
	 * Sets an array of strings.
	 *
	 * @param key     Key to set.
	 * @param value   Pointer to the array to copy.
	 * @param count   Number of elements to copy.
	 * @returns STATUS_OK on success, STATUS_KEY_ALREADY_TAKEN or other status on failure.
	 */
	virtual Status				setStringArray	(const wchar_t* key, const wchar_t**	value, size_t count) = 0;

protected:
	AttributeMapBuilder();
	virtual ~AttributeMapBuilder();
};


} // namespace prt


#endif /* PRT_ATTRIBUTEMAP_H_ */

