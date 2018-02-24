#include "libInclude.h"
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/AutoTransform>
#include <osg/ShapeDrawable>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgText\Text>
#include <osgUtil/Optimizer>

#include <iostream>

osg::ref_ptr<osg::Node> createQuad()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	geom->setVertexArray(v.get());

	osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();
	vt->push_back(osg::Vec2(0.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 1.0f));
	vt->push_back(osg::Vec2(0.0f, 1.0f));
	geom->setTexCoordArray(0, vt.get());

	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	vc->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	vc->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
	geom->setColorArray(vc.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	nc->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	geom->setNormalArray(nc.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	geode->addDrawable(geom.get());
	return geode.get();
}

osg::ref_ptr<osg::Geode> createQuad(bool b)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	v->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	geom->setVertexArray(v.get());

	osg::ref_ptr<osg::DrawElementsUShort> quad = new osg::DrawElementsUShort(osg::PrimitiveSet::QUADS, 0);
	quad->push_back(0);
	quad->push_back(1);
	quad->push_back(2);
	quad->push_back(3);
	geom->addPrimitiveSet(quad.get());

	osg::ref_ptr<osg::DrawElementsUShort> tria = new osg::DrawElementsUShort(osg::PrimitiveSet::TRIANGLES, 0);
	tria->push_back(4);
	tria->push_back(0);
	tria->push_back(3);
	geom->addPrimitiveSet(tria.get());

	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	vc->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	vc->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
	osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType, 4, 4> *colorindex = new osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType, 4, 4>();
	colorindex->push_back(0);
	colorindex->push_back(1);
	colorindex->push_back(2);
	colorindex->push_back(3);
	colorindex->push_back(2);
	geom->setColorArray(vc);
	geom->setColorIndices(colorindex);
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	nc->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	geom->setNormalArray(nc.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	geode->addDrawable(geom.get());
	return geode.get();
}

osg::ref_ptr<osg::Geode> createShape()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	float fRadius = 0.8f;
	float fHeight = 1.0f;

	osg::ref_ptr<osg::TessellationHints> hint = new osg::TessellationHints();
	hint->setDetailRatio(0.8f);

	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), fRadius), hint.get()));
	geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(2.0f, 0.0f, 0.0f), fRadius*2), hint.get()));
	geode->addDrawable(new osg::ShapeDrawable(new osg::Cone(osg::Vec3(4.0f, 0.0f, 0.0f), fRadius, fHeight), hint.get()));
	geode->addDrawable(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(6.0f, 0.0f, 0.0f), fRadius, fHeight), hint.get()));
	geode->addDrawable(new osg::ShapeDrawable(new osg::Capsule(osg::Vec3(8.0f, 0.0f, 0.0f), fRadius, fHeight), hint.get()));

		
	return geode.get();
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	osg::ref_ptr<osg::Group> group = new osg::Group();
	group->addChild(createQuad(false));
	group->addChild(createShape());
	osgUtil::Optimizer opt;
	opt.optimize(group.get());
	viewer->setSceneData(group.get());
	viewer->realize();
	viewer->run();
	return 0;
}

