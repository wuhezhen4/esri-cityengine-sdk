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

#ifndef PRTX_RESOLVEMAP_H_
#define PRTX_RESOLVEMAP_H_

#include <string>

#include "boost/shared_ptr.hpp"

#include "prtx/prtx.h"
#include "prtx/URI.h"
#include "prt/ResolveMap.h"


namespace prtx {


/**
 * The prtx specialization of the prt::ResolveMap adds convenience functions to directly support
 * stl strings and URIs.
 */
class PRTX_EXPORTS_API ResolveMap : public prt::ResolveMap {
public:
	ResolveMap() {}

	/**
	 * returns 0-ptr if key could not be resolved
	 */
	virtual prtx::URIPtr resolveKey(const std::wstring& key) const = 0;


	/**
	 * Searches the keys in the ResolveMap for the expression defined in query.
	 * Supported search queries include wildcards, regular expressions and file properties.
	 *
	 * This implements the CGA fileSearch() function.
	 * This function is thread-safe.
	 *
	 * @param         project     The name of the current project ("projects" are "subfolders" in the resolve map starting with a '/').
	 * @param         query       The search query. From the CGA reference:
	 *							  <br>Wildcards: The common wildcards characters '*' (asterisk character) and '?' (question mark) are supported.
	 *							  The asterisk substitutes for any zero or more characters, and the question mark substitutes for any one character.
	 *							  <br>Regular Expressions: Regular expressions start with '$'. Always put the '$' as the FIRST character if your searchQuery is
	 *							  a regular expression! Note that with regular expressions, the semantics of the wildcards "*" and "?" changes.
	 *							  "*" matches the preceding element zero or more times, therefore use ".*" to emulate the "match anything" behaviour.
	 *							  <br>File Properties: Following file properties can be queried:<br>
	 *							     Name: Filename<br>
	 *							     Ext: File extension<br>
	 *							     Project: Project name<br>
	 *							     Path: Filepath<br>
	 * @returns result.
	 */
	virtual std::wstring searchKey(const std::wstring& project, const std::wstring& query) const = 0;



	/**
	 * Helper function to resolve a key with fall back to URI = key if key not found in ResolveMap.
	 * @param resolveMap The resolveMap to use.
	 * @param key        The key to resolve.
	 * @returns the resolved URI if key can be resolved or a URI with the key else.
	 */
	static prtx::URIPtr resolveKeyWithURIFallback(ResolveMap const* resolveMap, const std::wstring& key) {
		if(resolveMap == 0) return URI::create(key);
		prtx::URIPtr uri = resolveMap->resolveKey(key);
		if(uri) return uri;
		else    return URI::create(key);
	}

	/**
	 * Helper function to replace the last segment in a key. Keys are often separated by '/' characters,
	 * for instance 'assets/elements/window.obj', and relative keys need to be constructed, e.g.
	 * 'assets/elements/glass.jpg'.
	 * @param key        The key whose last '/' separated segment needs to be replaced.
	 * @param newSegment The new segment.
	 * @returns key with the last segment replaced.
	 */
	static std::wstring replaceLastKeySegment(const std::wstring& key, const std::wstring& newSegment);


protected:
	virtual ~ResolveMap() {}

};


} // namespace prtx


#endif /* PRTX_RESOLVEMAP_H_ */

