#include "libInclude.h"
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Image>
#include <osg/TexGen>
#include <osg/Texture1D>
#include <osg/TexEnv>
#include <osg/StateSet>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgText\Text>
#include <osgUtil/Optimizer>

#include <iostream>

osg::ref_ptr<osg::Node> createNode()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
	//顶点数组
	osg::ref_ptr<osg::Vec3Array> vc = new osg::Vec3Array();
	vc->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	vc->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	vc->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	geom->setVertexArray(vc.get());

	//纹理坐标数组
	osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();
	vt->push_back(osg::Vec2(0.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 1.0f));
	vt->push_back(osg::Vec2(0.0f, 1.0f));
	geom->setTexCoordArray(0, vt.get());

	//设置法线
	osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	nc->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	geom->setNormalArray(nc.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	//设置图元
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	geode->addDrawable(geom.get());

	return geode.get();
}

osg::ref_ptr<osg::StateSet> createTexture2DState(osg::ref_ptr<osg::Image> img)
{
	osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
	texture->setDataVariance(osg::Object::DYNAMIC);
	texture->setImage(img.get());
	stateset->setTextureAttributeAndModes(0, texture.get(), osg::StateAttribute::ON);
	return stateset.get();
}


int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	osg::ref_ptr<osg::Group> root = new osg::Group();
	std::string imgname = kstrDataPath + "Images/tree0.rgba";
	osg::ref_ptr<osg::Image> img = osgDB::readImageFile(imgname);
	osg::ref_ptr<osg::Node> node = createNode();
	osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();
	stateset = createTexture2DState(img.get());
	node->setStateSet(stateset.get());
	root->addChild(node);
	osgUtil::Optimizer opt;
	opt.optimize(root.get());
	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();
	return 0;
}