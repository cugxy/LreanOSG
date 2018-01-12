#include "libInclude.h"
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

using namespace osg;
using namespace osgDB;


int main()
{
	ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	ref_ptr<Group> root = new Group();
	ref_ptr<Node> node = readNodeFile(kstrDataPath + "cow.osg");

	ref_ptr<PositionAttitudeTransform> pat1 = new PositionAttitudeTransform();
	pat1->setPosition(Vec3(-10.0f, 0.0f, 0.0f));
	pat1->setScale(Vec3(0.5f, 0.5f, 0.5f));
	pat1->addChild(node.get());

	ref_ptr<PositionAttitudeTransform> pat2 = new PositionAttitudeTransform();
	pat2->setPosition(Vec3(10.0f, 0.0f, 0.0f));
	pat2->addChild(node.get());

	ref_ptr<MatrixTransform> mt1 = new MatrixTransform();
	Matrix m;
	m.makeTranslate(Vec3(10.0f, 0.0f, 0.0f));
	m.makeRotate(45.0f, 1.0f, 0.0f, 0.0f);
	mt1->setMatrix(m);
	mt1->addChild(node.get());

	ref_ptr<MatrixTransform> mt2 = new MatrixTransform();
	Matrix t;
	t.makeTranslate(Vec3(-10.0f, 0.0f, 0.0f));
	mt2->setMatrix(t);
	mt2->addChild(node.get());


	root->addChild(pat1.get());
	root->addChild(pat2.get());
	root->addChild(mt1.get());
	root->addChild(mt2.get());

	osgUtil::Optimizer opt;
	opt.optimize(root.get());

	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();
	return 0;
}