#include <ostream>
#include <sstream>

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
	const prtx::InitialShape* is = context.getInitialShape(initialShapeIndex);
	try {
		prtx::LeafIteratorPtr li = prtx::LeafIterator::create(context, initialShapeIndex);
		for (prtx::ShapePtr shape = li->getNext(); shape.get() != 0; shape = li->getNext()) {
			mEncodePreparator->add(context.getCache(), shape, is->getAttributeMap());
		}
	} catch(...) {
		mEncodePreparator->add(context.getCache(), *is, initialShapeIndex);
	}
}


void STLEncoder::finish(prtx::GenerateContext& /*context*/) {
	prt::SimpleOutputCallbacks* soh = dynamic_cast<prt::SimpleOutputCallbacks*>(getCallbacks());
	std::wstring name = std::wstring(getOptions()->getString(L"name")) + L".stl";

	prtx::GeometryPtrVector geos;
//	std::vector<prtx::DoubleVector> trafos;
//	std::vector<prtx::MaterialPtrVector> materials;

	prtx::EncodePreparator::PreparationFlags prepFlags;
	prepFlags.instancing(false);
	prepFlags.mergeByMaterial(true);
	prepFlags.triangulate(true);
	prepFlags.mergeVertices(true);
	prepFlags.cleanupVertexNormals(true);
	prepFlags.cleanupUVs(true);
	prepFlags.processVertexNormals(prtx::VertexNormalProcessor::SET_ALL_TO_FACE_NORMALS);

	std::vector<prtx::EncodePreparator::FinalizedInstance> finalizedInstances;
	mEncodePreparator->fetchFinalizedInstances(finalizedInstances, prepFlags);
	BOOST_FOREACH(prtx::EncodePreparator::FinalizedInstance& instance, finalizedInstances) {
		geos.push_back(instance.getGeometry());
//		trafos.push_back(instance.getTransformation());
//		materials.push_back(instance.getMaterials());
	}

	std::wostringstream out;
	out << std::scientific;
	out << L"solid " << name << L"\n";

	BOOST_FOREACH(const prtx::GeometryPtr& g, geos) {
		BOOST_FOREACH(const prtx::MeshPtr& m, g->getMeshes()) {
			for (uint32_t fi = 0, n = m->getFaceCount(); fi < n; fi++) {

				const uint32_t* fvni = m->getFaceVertexNormalIndices(fi);
				const double* fn = &m->getVertexNormalsCoords()[3 * fvni[0]];

				const uint32_t* fvi = m->getFaceVertexIndices(fi);
				const double* v0 = &m->getVertexCoords()[3 * fvi[0] + 0];
				const double* v1 = &m->getVertexCoords()[3 * fvi[1] + 1];
				const double* v2 = &m->getVertexCoords()[3 * fvi[2] + 2];

				out << L"facet normal " << fn[0] << L" " << fn[1] << L" " << fn[2] << L"\n";
				out << L"  outer loop\n";
				out << L"    vertex " << v0[0] << L" " << v0[1] << L" " << v0[2] << L"\n";
				out << L"    vertex " << v1[0] << L" " << v1[1] << L" " << v1[2] << L"\n";
				out << L"    vertex " << v2[0] << L" " << v2[1] << L" " << v2[2] << L"\n";
				out << L"  endloop\n";
				out << L"endfacet\n";
			}
		}
	}

	out << L"endsolid\n";

	uint64_t h = soh->open(ID.c_str(), prt::CT_GEOMETRY, name.c_str(), prt::SimpleOutputCallbacks::SE_UTF8);
	soh->write(h, out.str().c_str());
	soh->close(h, 0, 0);
}


STLEncoderFactory* STLEncoderFactory::createInstance() {
	prtx::EncoderInfoBuilder encoderInfoBuilder;

	encoderInfoBuilder.setID(STLEncoder::ID);
	encoderInfoBuilder.setName(STLEncoder::NAME);
	encoderInfoBuilder.setDescription(STLEncoder::DESCRIPTION);
	encoderInfoBuilder.setType(prt::CT_GEOMETRY);

	//encoderInfoBuilder.setValidator(prtx::EncodeOptionsValidatorPtr(new TestOptionsValidator()));

	prtx::PRTUtils::AttributeMapBuilderPtr amb(prt::AttributeMapBuilder::create());
	amb->setString(L"name", L"stl_default_name");
	encoderInfoBuilder.setDefaultOptions(amb->createAttributeMap());

	return new STLEncoderFactory(encoderInfoBuilder.create());
}
