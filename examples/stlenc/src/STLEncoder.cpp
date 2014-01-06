#include "boost/foreach.hpp"

#include "STLEncoder.h"


const std::wstring STLEncoder::ID = L"com.esri.prt.examples.STLEncoder";
const std::wstring STLEncoder::NAME = L"STL Encoder";
const std::wstring STLEncoder::DESCRIPTION = L"Example encoder for the STL format";


STLEncoder::STLEncoder(const std::wstring& id, const prt::AttributeMap* defaultOptions, prt::Callbacks* callbacks)
: prtx::GeometryEncoder(id, defaultOptions, callbacks)
{
}


STLEncoder::~STLEncoder() {
}


void STLEncoder::init(prtx::GenerateContext& /*context*/) {
	prtx::NamePreparator::NamespacePtr nsMaterials = mNamePreparator.newNamespace();
	prtx::NamePreparator::NamespacePtr nsMeshes = mNamePreparator.newNamespace();
	mEncodePreparator = prtx::EncodePreparator::create(true, mNamePreparator, nsMeshes, nsMaterials);
}


void STLEncoder::encode(prtx::GenerateContext& context, size_t initialShapeIndex) {
	prt::SimpleOutputCallbacks* soh = dynamic_cast<prt::SimpleOutputCallbacks*>(getCallbacks());
	const prtx::InitialShape* is = context.getInitialShape(initialShapeIndex);

	try {
		prtx::LeafIteratorPtr li = prtx::LeafIterator::create(context, initialShapeIndex);
		for (prtx::ShapePtr shape = li->getNext(); shape.get() != 0; shape = li->getNext()) {
			mEncodePreparator->add(context.getCache(), shape, is->getAttributeMap());
		}
	} catch(...) {
		mEncodePreparator->add(context.getCache(), *is, initialShapeIndex);
	}

	prtx::GeometryPtrVector geos;
	std::vector<prtx::DoubleVector> trafos;
	std::vector<prtx::MaterialPtrVector> materials;

	prtx::EncodePreparator::PreparationFlags prepFlags;
	prepFlags.instancing(true);
	prepFlags.mergeByMaterial(true);
	prepFlags.triangulate(false);
	prepFlags.mergeVertices(true);
	prepFlags.cleanupVertexNormals(true);
	prepFlags.cleanupUVs(true);
	prepFlags.processVertexNormals(prtx::VertexNormalProcessor::SET_MISSING_TO_FACE_NORMALS);

	std::vector<prtx::EncodePreparator::FinalizedInstance> finalizedInstances;
	mEncodePreparator->fetchFinalizedInstances(finalizedInstances, prepFlags);
	BOOST_FOREACH(prtx::EncodePreparator::FinalizedInstance& instance, finalizedInstances) {
		geos.push_back(instance.getGeometry());
		trafos.push_back(instance.getTransformation());
		materials.push_back(instance.getMaterials());
	}

	// TODO: the stl stuff
}


void STLEncoder::finish(prtx::GenerateContext& /*context*/) {
}


STLEncoderFactory* STLEncoderFactory::createInstance() {
	prtx::EncoderInfoBuilder encoderInfoBuilder;

	encoderInfoBuilder.setID(STLEncoder::ID);
	encoderInfoBuilder.setName(STLEncoder::NAME);
	encoderInfoBuilder.setDescription(STLEncoder::DESCRIPTION);
	encoderInfoBuilder.setType(prt::CT_GEOMETRY);

	//encoderInfoBuilder.setValidator(prtx::EncodeOptionsValidatorPtr(new TestOptionsValidator()));

	return new STLEncoderFactory(encoderInfoBuilder.create());
}
