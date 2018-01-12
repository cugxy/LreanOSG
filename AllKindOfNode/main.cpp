#include "libInclude.h"
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/AutoTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgText\Text>
#include <osgUtil/Optimizer>

#include <iostream>

using namespace osg;
using namespace osgDB;

ref_ptr<Node> createBillBoard(ref_ptr<Image> image)
{
	ref_ptr<Geometry> geometry = new Geometry();
	ref_ptr<Vec3Array> vec3Array = new Vec3Array();
	vec3Array->push_back(osg::Vec3(-0.5f, 0.0f, -0.5f));
	vec3Array->push_back(osg::Vec3(0.5f, 0.0f, -0.5f));
	vec3Array->push_back(osg::Vec3(0.5f, 0.0f, 0.5f));
	vec3Array->push_back(osg::Vec3(-0.5f, 0.0f, 0.5f));
	geometry->setVertexArray(vec3Array.get());

	ref_ptr<Vec3Array> normal = new Vec3Array();
	normal->push_back(Vec3(1.0f, 0.0f, 0.0f) ^ Vec3(0.0f, 0.0f, 1.0f));

	geometry->setNormalArray(normal);
	geometry->setNormalBinding(Geometry::BIND_OVERALL);

	ref_ptr<Vec2Array> vec2Array = new Vec2Array();
	vec2Array->push_back(Vec2(0.0f, 0.0f));
	vec2Array->push_back(Vec2(1.0f, 0.0f));
	vec2Array->push_back(Vec2(1.0f, 1.0f));
	vec2Array->push_back(Vec2(0.0f, 1.0f));
	geometry->setTexCoordArray(0, vec2Array);

	geometry->addPrimitiveSet(new DrawArrays(PrimitiveSet::QUADS, 0, 4));
	if (image.get())
	{
		ref_ptr<StateSet> stateset = new StateSet();
		ref_ptr<Texture2D> texture = new Texture2D();
		texture->setImage(image.get());
		stateset->setTextureAttributeAndModes(0, texture, StateAttribute::ON);
		stateset->setMode(GL_BLEND, StateAttribute::ON);
		stateset->setMode(GL_LIGHTING, StateAttribute::OFF);
		geometry->setStateSet(stateset.get());
	}
	ref_ptr<Billboard> billBoard1 = new Billboard();
	billBoard1->setMode(Billboard::POINT_ROT_EYE);
	billBoard1->addDrawable(geometry.get(), Vec3(5.0f, 0.0f, 0.0f));

	ref_ptr<Billboard> billBoard2 = new Billboard();
	billBoard2->setMode(Billboard::AXIAL_ROT);
	billBoard2->setAxis(Vec3(0.0f, 0.0f, 1.0f));
	billBoard2->addDrawable(geometry.get(), Vec3(10.0f, 0.0f, 0.0f));

	ref_ptr<osg::Group> group = new Group();
	group->addChild(billBoard1.get());
	group->addChild(billBoard2.get());
	return group;
}

ref_ptr<Node> createAutoTransfrom(
	Vec3 &position,
	float size,
	const std::string &label,
	AutoTransform::AutoRotateMode autoModel,
	osgText::Text::AxisAlignment axisAlignment
)
{
	ref_ptr<Geode> geode = new Geode();
	std::string font = kstrDataPath + "font\\cour.ttf";
	ref_ptr<osgText::Text> text = new osgText::Text();
	geode->addDrawable(text.get());
	text->setFont(font);
	text->setFontResolution(128, 128);
	text->setCharacterSize(size);
	text->setAlignment(osgText::Text::CENTER_CENTER);
	text->setAxisAlignment(axisAlignment);
	text->setText(label);
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, StateAttribute::OFF);

	ref_ptr<AutoTransform> autoTrans = new AutoTransform();
	autoTrans->addChild(geode.get());
	autoTrans->setAutoRotateMode(autoModel);
	autoTrans->setAutoScaleToScreen(false);
	autoTrans->setMaximumScale(5.0f);
	autoTrans->setMinimumScale(0.0f);
	autoTrans->setPosition(position);
	return autoTrans.get();
}

int main()
{
	ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	ref_ptr<Group> root = new Group();
	ref_ptr<Node> cowNode = readNodeFile(kstrDataPath + "cow.osg");
	ref_ptr<Node> gliderNode = readNodeFile(kstrDataPath + "glider.osg");

	//BillBoard
	ref_ptr<Image> image = osgDB::readImageFile(kstrDataPath + "Images\\tree0.rgba");
	ref_ptr<PositionAttitudeTransform> pat = new PositionAttitudeTransform();
	pat->setScale(Vec3(5.0f, 5.0f, 5.0f));
	pat->addChild(createBillBoard(image.get()));

	//PositionAttitudeTransform
	ref_ptr<PositionAttitudeTransform> pat1 = new PositionAttitudeTransform();
	pat1->setPosition(Vec3(-10.0f, 0.0f, 0.0f));
	pat1->setScale(Vec3(0.5f, 0.5f, 0.5f));
	pat1->addChild(cowNode.get());
	ref_ptr<PositionAttitudeTransform> pat2 = new PositionAttitudeTransform();
	pat2->setPosition(Vec3(10.0f, 0.0f, 0.0f));
	pat2->addChild(cowNode.get());

	//MatrixTransform
	ref_ptr<MatrixTransform> mt1 = new MatrixTransform();
	Matrix m;
	m.makeTranslate(Vec3(10.0f, 0.0f, 0.0f));
	m.makeRotate(45.0f, 1.0f, 0.0f, 0.0f);
	mt1->setMatrix(m);
	mt1->addChild(cowNode.get());
	ref_ptr<MatrixTransform> mt2 = new MatrixTransform();
	Matrix t;
	t.makeTranslate(Vec3(-10.0f, 0.0f, 0.0f));
	mt2->setMatrix(t);
	mt2->addChild(cowNode.get());

	//AutoTransform
	std::string str("MDZZ");
	Vec3 position(0.0f, 0.0f, 0.0f);
	ref_ptr<Node> node1 = createAutoTransfrom(position, 60.0f, str, AutoTransform::AutoRotateMode::NO_ROTATION, osgText::Text::XY_PLANE);
	ref_ptr<Node> node2 = createAutoTransfrom(position, 60.0f, str, AutoTransform::AutoRotateMode::ROTATE_TO_AXIS, osgText::Text::XY_PLANE);
	ref_ptr<Node> node3 = createAutoTransfrom(position, 60.0f, str, AutoTransform::AutoRotateMode::ROTATE_TO_CAMERA, osgText::Text::XY_PLANE);
	ref_ptr<Node> node4 = createAutoTransfrom(position, 60.0f, str, AutoTransform::AutoRotateMode::ROTATE_TO_SCREEN, osgText::Text::XY_PLANE);

	//Switch
	ref_ptr<Switch> switch1 = new Switch();
	switch1->addChild(pat1.get(), true);
	switch1->addChild(node1.get(), true);

	//LOD Level of detail
	ref_ptr<LOD> lodNode = new LOD();
	lodNode->addChild(cowNode.get(), 0.0f, 30.0f);
	lodNode->addChild(gliderNode.get(), 20.0f, 50.0f);
	osgDB::writeNodeFile(*(lodNode.get()), "lod.osg");


	//root->addChild(pat.get());
	//root->addChild(pat1.get());
	//root->addChild(pat2.get());
	//root->addChild(mt1.get());
	//root->addChild(mt2.get());
	//root->addChild(node1.get());
	//root->addChild(node2.get());
	//root->addChild(node3.get());
	//root->addChild(node4.get());
	//root->addChild(switch1);
	root->addChild(lodNode);

	osgUtil::Optimizer opt;
	opt.optimize(root.get());

	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();
	return 0;
}