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

#ifndef PRTX_FILEEXTENSIONS_H_
#define PRTX_FILEEXTENSIONS_H_

#include <string>
#include <vector>

#include "prtx/prtx.h"
#include "prtx/Types.h"


#ifdef _MSC_VER
#	ifdef PRT_CC_DBG
#		pragma message(__FILE__": disabled MSVC warnings 4251" )
#	endif
#	pragma warning(push)
#	pragma warning (disable : 4251)
#endif


namespace prtx {


/**
 * Helper class representing a list of file extensions.
 * Instances of this class are immutable.
 */
class PRTX_EXPORTS_API FileExtensions {
public:
	FileExtensions();
	virtual ~FileExtensions();

	/**
	 * Initializes the instance with exactly one extension.
	 * e must begin with a dot.
	 */
	FileExtensions(const std::wstring& e);

	/**
	 * Initializes the instance with an arbitrary number of extensions.
	 * All extensions must begin with a dot.
	 */
	FileExtensions(const WStringVector& v);

	/**
	 * Returns a string representation of the extension list.
	 * Each extension is delimited with a semi-colon, also if there is only one extension.
	 */
	const std::wstring& toString() const;

	/**
	 * Returns true if e is found in the list of known extensions.
	 * e must begin with a dot.
	 */
	bool contains(const std::wstring& e) const;

	/**
	 * Returns a reference to the extension list.
	 */
	const WStringVector& items() const;

	/**
	 * Helper to get reference to one extension item.
	 */
	const std::wstring& item(size_t i) const;

private:
	WStringVector mExts;
	mutable std::wstring* mStrCache;
};


} // namespace prtx


#endif /* PRTX_FILEEXTENSIONS_H_ */

