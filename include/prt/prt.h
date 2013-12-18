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

#ifndef PRT_H_
#define PRT_H_


#ifdef _WIN32
#	ifdef PRT_EXPORTS
#		define PRT_EXPORTS_API __declspec(dllexport)
#	else
#		define PRT_EXPORTS_API __declspec(dllimport)
#	endif
#else
#	ifndef SWIG
#		define PRT_EXPORTS_API __attribute__ ((visibility ("default")))
#	else
#		define PRT_EXPORTS_API
#	endif
#endif


/**
 * \mainpage Esri Procedural Runtime
 *
 * The CityEngine SDK enables you as a 3rd party developer to extend CityEngine with additional import and export formats and storage backends beyond simple files. Moreover, you can integrate the procedural runtime in your own client applications taking full advantage of the procedural core without running CityEngine or ArcGIS.
 *
 * The main documentation resources are:
 * - PRT Documentation
 *   - <a href="../esri_prt_whitepaper.pdf">PRT white paper</a>
 *   - <a href="../esri_prt_architecture.pdf">PRT architecture with examples</a>
 * - PRT API Reference
 *   - <a href="namespaceprt.html#func-members">PRT Functions </a>
 *   - <a href="namespaceprt.html#nested-classes">PRT Classes </a>
 * - PRT SPI (PRTX) Reference
 *   - <a href="namespaceprtx.html#nested-classes">PRTX Classes </a>
 * - Built-In Codecs Reference
 *   - <a href="../esri_prt_codecs.html">esri_prt_codecs.html</a>
 */


#endif /* PRT_H_ */

