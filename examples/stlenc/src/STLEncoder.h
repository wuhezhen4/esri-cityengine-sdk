#ifndef PRT_EXAMPLE_STLENCODER_H_
#define PRT_EXAMPLE_STLENCODER_H_

#include <string>

#include "prt/AttributeMap.h"
#include "prt/Callbacks.h"

#include "prtx/prtx.h"
#include "prtx/GenerateContext.h"
#include "prtx/Encoder.h"
#include "prtx/EncoderFactory.h"
#include "prtx/EncodePreparator.h"
#include "prtx/Singleton.h"
#include "prtx/EncoderInfoBuilder.h"
#include "prtx/Geometry.h"
#include "prtx/Shape.h"
#include "prtx/ShapeIterator.h"


class STLEncoder : public prtx::GeometryEncoder {
public:
	static const std::wstring ID;
	static const std::wstring NAME;
	static const std::wstring DESCRIPTION;

	STLEncoder(const std::wstring& id, const prt::AttributeMap* defaultOptions, prt::Callbacks* callbacks);
	virtual ~STLEncoder();

	virtual void init(prtx::GenerateContext& context);
	virtual void encode(prtx::GenerateContext& context, size_t initialShapeIndex);
	virtual void finish(prtx::GenerateContext& context);

private:
	prtx::DefaultNamePreparator	mNamePreparator;
	prtx::EncodePreparatorPtr	mEncodePreparator;
};


class STLEncoderFactory : public prtx::EncoderFactory, public prtx::Singleton<STLEncoderFactory> {
public:
	static STLEncoderFactory* createInstance();

	STLEncoderFactory(const prt::EncoderInfo* info) : prtx::EncoderFactory(info) { }
	virtual ~STLEncoderFactory() { }
	virtual STLEncoder* create(const prt::AttributeMap* defaultOptions, prt::Callbacks* callbacks) const {
		return new STLEncoder(getID(), defaultOptions, callbacks);
	}

};


#endif /* PRT_EXAMPLE_STLENCODER_H_ */
