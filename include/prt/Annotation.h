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

#ifndef PRT_ANNOTATION_H_
#define PRT_ANNOTATION_H_

#include "prt/prt.h"
#include "prt/Object.h"

namespace prt {


enum AnnotationArgumentType {AAT_VOID, AAT_BOOL, AAT_FLOAT, AAT_STR, AAT_INT, AAT_UNKNOWN};


class PRT_EXPORTS_API AnnotationArgument : public Object {
public:
	virtual AnnotationArgumentType		getType()				const = 0;
	virtual const wchar_t*				getKey()				const = 0;
	virtual bool						getBool()				const = 0;
	virtual double						getFloat()				const = 0;
	virtual const wchar_t*				getStr()				const = 0;

protected:
	virtual ~AnnotationArgument() { }
};


class PRT_EXPORTS_API Annotation : public Object {
public:
	virtual const wchar_t*				getName()				const = 0;
	virtual size_t						getNumArguments()		const = 0;
	virtual const AnnotationArgument*	getArgument(size_t i)	const = 0;

protected:
	virtual ~Annotation() { }
};


} // namespace prt


#endif /* PRT_ANNOTATION_H_ */

