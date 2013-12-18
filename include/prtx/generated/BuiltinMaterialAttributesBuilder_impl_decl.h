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

public:
	virtual void ambient_b(double val);
	virtual void ambient_g(double val);
	virtual void ambient_r(double val);
	virtual void bumpValue(double val);
	virtual void bumpmap_rw(double val);
	virtual void bumpmap_su(double val);
	virtual void bumpmap_sv(double val);
	virtual void bumpmap_tu(double val);
	virtual void bumpmap_tv(double val);
	virtual void color_a(double val);
	virtual void color_b(double val);
	virtual void color_g(double val);
	virtual void color_r(double val);
	virtual void colormap_rw(double val);
	virtual void colormap_su(double val);
	virtual void colormap_sv(double val);
	virtual void colormap_tu(double val);
	virtual void colormap_tv(double val);
	virtual void dirtmap_rw(double val);
	virtual void dirtmap_su(double val);
	virtual void dirtmap_sv(double val);
	virtual void dirtmap_tu(double val);
	virtual void dirtmap_tv(double val);
	virtual void normalmap_rw(double val);
	virtual void normalmap_su(double val);
	virtual void normalmap_sv(double val);
	virtual void normalmap_tu(double val);
	virtual void normalmap_tv(double val);
	virtual void opacity(double val);
	virtual void opacitymap_rw(double val);
	virtual void opacitymap_su(double val);
	virtual void opacitymap_sv(double val);
	virtual void opacitymap_tu(double val);
	virtual void opacitymap_tv(double val);
	virtual void reflectivity(double val);
	virtual void shininess(double val);
	virtual void specular_b(double val);
	virtual void specular_g(double val);
	virtual void specular_r(double val);
	virtual void specularmap_rw(double val);
	virtual void specularmap_su(double val);
	virtual void specularmap_sv(double val);
	virtual void specularmap_tu(double val);
	virtual void specularmap_tv(double val);
	virtual void name(const std::wstring& val);
	virtual void shader(const std::wstring& val);

// default Material keys
	virtual void ambientColor(const std::vector<double>& val);
	virtual void diffuseColor(const std::vector<double>& val);
	virtual void specularColor(const std::vector<double>& val);
	virtual void bumpMap(const prtx::TexturePtrVector& val, const prtx::WStringVector& resolveMapKeys);
	virtual void diffuseMap(const prtx::TexturePtrVector& val, const prtx::WStringVector& resolveMapKeys);
	virtual void normalMap(const prtx::TexturePtrVector& val, const prtx::WStringVector& resolveMapKeys);
	virtual void opacityMap(const prtx::TexturePtrVector& val, const prtx::WStringVector& resolveMapKeys);
	virtual void specularMap(const prtx::TexturePtrVector& val, const prtx::WStringVector& resolveMapKeys);


