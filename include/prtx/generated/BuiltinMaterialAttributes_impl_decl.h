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
// cga attributes
	virtual double ambient_b() const;
	virtual double ambient_g() const;
	virtual double ambient_r() const;
	virtual double bumpValue() const;
	virtual double bumpmap_rw() const;
	virtual double bumpmap_su() const;
	virtual double bumpmap_sv() const;
	virtual double bumpmap_tu() const;
	virtual double bumpmap_tv() const;
	virtual double color_a() const;
	virtual double color_b() const;
	virtual double color_g() const;
	virtual double color_r() const;
	virtual double colormap_rw() const;
	virtual double colormap_su() const;
	virtual double colormap_sv() const;
	virtual double colormap_tu() const;
	virtual double colormap_tv() const;
	virtual double dirtmap_rw() const;
	virtual double dirtmap_su() const;
	virtual double dirtmap_sv() const;
	virtual double dirtmap_tu() const;
	virtual double dirtmap_tv() const;
	virtual double normalmap_rw() const;
	virtual double normalmap_su() const;
	virtual double normalmap_sv() const;
	virtual double normalmap_tu() const;
	virtual double normalmap_tv() const;
	virtual double opacity() const;
	virtual double opacitymap_rw() const;
	virtual double opacitymap_su() const;
	virtual double opacitymap_sv() const;
	virtual double opacitymap_tu() const;
	virtual double opacitymap_tv() const;
	virtual double reflectivity() const;
	virtual double shininess() const;
	virtual double specular_b() const;
	virtual double specular_g() const;
	virtual double specular_r() const;
	virtual double specularmap_rw() const;
	virtual double specularmap_su() const;
	virtual double specularmap_sv() const;
	virtual double specularmap_tu() const;
	virtual double specularmap_tv() const;
	virtual const std::wstring& bumpmap() const;
	virtual const std::wstring& colormap() const;
	virtual const std::wstring& dirtmap() const;
	virtual const std::wstring& name() const;
	virtual const std::wstring& normalmap() const;
	virtual const std::wstring& opacitymap() const;
	virtual const std::wstring& shader() const;
	virtual const std::wstring& specularmap() const;

// default Material keys
	virtual const std::vector<double>& ambientColor() const;
	virtual const std::vector<double>& diffuseColor() const;
	virtual const std::vector<double>& specularColor() const;
	virtual const std::vector<prtx::TexturePtr>& bumpMap() const;
	virtual const std::vector<prtx::TexturePtr>& diffuseMap() const;
	virtual const std::vector<prtx::TexturePtr>& normalMap() const;
	virtual const std::vector<prtx::TexturePtr>& opacityMap() const;
	virtual const std::vector<prtx::TexturePtr>& specularMap() const;


