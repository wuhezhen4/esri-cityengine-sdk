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

#ifndef PRT_RULEFILEINFO_H_
#define PRT_RULEFILEINFO_H_

#include "prt/prt.h"
#include "prt/Object.h"
#include "prt/Annotation.h"


class ClassFileReader;


namespace prt {

/**
 * The RuleFileInfo class allows for browsing through the rules and attributes contained within a rule file.
 * Both rules and attributes can be annotated. Following annotations are defined:
 @verbatim
    @StartRule: Mark a rule as a start rule.
                (CE:  for the start rule chooser)
    @Hidden: Mark an attribute or rule as hidden
             (CE: it will not appear in the inspector or start rule chooser)
    @Group("level_1-group", ..., "level_n-group"): Set the group of an attribute
                                                   (CE: the inspector will group attributes accordingly)
    @Range(min, max): Set the numeric range of an attribute to min, max (inclusvie)
    @Range(value1, value2, value3, ...): Set the range to specific values.
                                         Values can be numeric or string.
    @Range(item_1 = value, ..., item_n = value): Set the range of an attribute to the given enumeration.
                                                 Value can be numeric or string.
    @Color: Mark an attribute as a color attribute.
            (CE: which will present a color picker in the inspector)
    @File: Mark an attribute as a file name.
           (CE: The inspector will present a file chooser)
    @File("ext_1", ... , "ext_n"): Mark an attribute as a file name.
                                   (CE: The inspector will present a file chooser for the given file
                                        extensions ("ext_1", ... , "ext_n") )
    @Directory: Mark an attribute as a directory name.
                (CE: The inspector will present a directory chooser)
    @Location(x, y): (CE: Sets the 2D location of an attribute or rule for the visual CGA editor)
    @Order(order): Sets the sort order for an attribute.
                   (CE: in the inspector)
    @Description("description"): Adds a description to an attribute or rule.
                                 (CE: which will be displayed as tooltip in the inspector or
                                      as description in the start rule chooser or style manager)
 @endverbatim
 */
class PRT_EXPORTS_API RuleFileInfo : public Object {
public:
	class PRT_EXPORTS_API Parameter {
	public:
		virtual AnnotationArgumentType	getType()               const = 0;
		virtual const wchar_t*			getName()               const = 0;
		virtual size_t					getNumAnnotations()     const = 0;
		virtual const Annotation*		getAnnotation(size_t i) const = 0;

	protected:
		virtual ~Parameter() { }
	};


	class PRT_EXPORTS_API Entry {
	public:
		virtual AnnotationArgumentType	getReturnType()         const = 0;
		virtual const wchar_t*			getName()               const = 0;
		virtual size_t					getNumParameters()      const = 0;
		virtual const Parameter*		getParameter(size_t i)  const = 0;
		virtual size_t					getNumAnnotations()     const = 0;
		virtual const Annotation*		getAnnotation(size_t i) const = 0;

	protected:
		virtual ~Entry() { }
	};



	virtual size_t					getNumAttributes()      const = 0;
	virtual const Entry*			getAttribute(size_t i)  const = 0;
	virtual size_t					getNumRules()           const = 0;
	virtual const Entry*			getRule(size_t i)       const = 0;
	virtual size_t					getNumAnnotations()     const = 0;
	virtual const Annotation*		getAnnotation(size_t i) const = 0;

protected:
	virtual ~RuleFileInfo() { }
};


} /* namespace prt */


#endif /* PRT_RULEFILEINFO_H_ */

