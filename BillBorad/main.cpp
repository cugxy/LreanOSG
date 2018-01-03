#include "libInclude.h"
 
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/BillBoard>
#include <osg/Image>
#include <osg/Texture2D>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

osg::ref_ptr<osg::Node> createBillBoard(osg::ref_ptr<osg::Image> image)
{
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	osg::ref_ptr<osg::Vec3Array> vec3Array = new osg::Vec3Array();
	vec3Array->push_back(osg::Vec3(-0.5f, 0.0f, -0.5f));
	vec3Array->push_back(osg::Vec3(0.5f, 0.0f, -0.5f));
	vec3Array->push_back(osg::Vec3(0.5f, 0.0f, 0.5f));
	vec3Array->push_back(osg::Vec3(-0.5f, 0.0f, 0.5f));
	geometry->setVertexArray(vec3Array.get());

	osg::ref_ptr<osg::Vec3Array> normal = new osg::Vec3Array();
	normal->push_back(osg::Vec3(1.0f, 0.0f, 0.0f) ^ osg::Vec3(0.0f, 0.0f, 1.0f));

	geometry->setNormalArray(normal);
	geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);

	osg::ref_ptr<osg::Vec2Array> vec2Array = new osg::Vec2Array();
	vec2Array->push_back(osg::Vec2(0.0f, 0.0f));
	vec2Array->push_back(osg::Vec2(1.0f, 0.0f));
	vec2Array->push_back(osg::Vec2(1.0f, 1.0f));
	vec2Array->push_back(osg::Vec2(0.0f, 1.0f));
	geometry->setTexCoordArray(0, vec2Array);

	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
	if (image.get())
	{
		osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();
		osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
		texture->setImage(image.get());
		stateset->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
		stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
		stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		geometry->setStateSet(stateset.get());
	}
	osg::ref_ptr<osg::Billboard> billBoard1 = new osg::Billboard();
	billBoard1->setMode(osg::Billboard::POINT_ROT_EYE);
	billBoard1->addDrawable(geometry.get(), osg::Vec3(5.0f, 0.0f, 0.0f));

	osg::ref_ptr<osg::Billboard> billBoard2 = new osg::Billboard();
	billBoard2->setMode(osg::Billboard::AXIAL_ROT);
	billBoard2->setAxis(osg::Vec3(0.0f, 0.0f, 1.0f));
	billBoard2->addDrawable(geometry.get(), osg::Vec3(10.0f, 0.0f, 0.0f));

	osg::ref_ptr<osg::Group> group = new osg::Group();
	group->addChild(billBoard1.get());
	group->addChild(billBoard2.get());
	return group;
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile(kstrDataPath + "Images\\tree0.rgba");
	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
	pat->setScale(osg::Vec3(5.0f, 5.0f, 5.0f));
	pat->addChild(createBillBoard(image.get()));
	root->addChild(pat);
	root->addChild(osgDB::readNodeFile(kstrDataPath + "glider.osg"));

	osgUtil::Optimizer opt;
	opt.optimize(root.get());

	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();
	return 0;
}

