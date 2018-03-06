#include "libInclude.h"
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/AutoTransform>
#include <osg/Geometry>
#include <osg/ClipNode>
#include <osg/PolygonMode>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgText\Text>
#include <osgUtil/Optimizer>

#include <iostream>

osg::ref_ptr<osg::Node> createClipNode(osg::ref_ptr<osg::Node> subgraph)
{
	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osg::StateSet> stateSet = new osg::StateSet();

	osg::ref_ptr<osg::PolygonMode> polygonMode = new osg::PolygonMode();
	polygonMode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);

	stateSet->setAttributeAndModes(polygonMode, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);

	osg::ref_ptr<osg::Group> wirefram_subgraph = new osg::Group();
	wirefram_subgraph->setStateSet(stateSet);
	wirefram_subgraph->addChild(subgraph.get());
	//原对象 以线框方式显示
	root->addChild(wirefram_subgraph.get());

	//设置自动变换 其子节点为 ClipNode
	osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform();
	osg::ref_ptr<osg::NodeCallback> node_cb = new osg::AnimationPathCallback(subgraph->getBound().center(), osg::Vec3(0.0f, 0.0f, 1.0f), osg::inDegrees(45.0f));
	transform->setUpdateCallback(node_cb.get());

	osg::ref_ptr<osg::ClipNode> clip_node = new osg::ClipNode();
	osg::BoundingSphere bs = subgraph->getBound();
	bs.radius() *= 0.4f;

	osg::BoundingBox bb;
	bb.expandBy(bs);

	clip_node->createClipBox(bb);
	clip_node->setCullingActive(false);
	transform->addChild(clip_node.get());
	root->addChild(transform.get());


	osg::ref_ptr<osg::Group> node = new osg::Group();
	//将clipNode 的状态赋给node
	node->setStateSet(clip_node->getStateSet());
	node->addChild(subgraph.get());
	root->addChild(node.get());

	return root.get();
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	osg::ref_ptr<osg::Node> group = new osg::Node();
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(kstrDataPath + "cessna.osg");
	group = createClipNode(node);
	osgUtil::Optimizer opt;
	opt.optimize(group.get());
	viewer->setSceneData(group.get());
	viewer->realize();
	viewer->run();
	return 0;
}

