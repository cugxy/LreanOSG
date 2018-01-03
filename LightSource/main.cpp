#include "libInclude.h"

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgViewer/ViewerEventHandlers>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/ShapeDrawable>

osg::ref_ptr<osg::Node> CreateSphere(osg::Vec3 position)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(position, 0.2)));
	return 0;
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Node> nd = osgDB::readNodeFile(kstrDataPath + "glider.osg");

	osg::ref_ptr<osg::Light> topLight = new osg::Light;
	topLight->setLightNum(0);
	topLight->setPosition(osg::Vec4(0.0, 0.0, 1.5, 1.0));
	topLight->setAmbient(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	topLight->setDiffuse(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	topLight->setConstantAttenuation(0.1f);
	topLight->setLinearAttenuation(0.1f);
	topLight->setQuadraticAttenuation(0.1f);

	osg::ref_ptr<osg::LightSource > ls = new osg::LightSource;
	ls->setLight(topLight);
	ls->setLocalStateSetModes(osg::StateAttribute::ON);

	osg::ref_ptr<osg::Group > gp = new osg::Group;
	gp->addChild(nd);
	gp->addChild(ls);
	gp->addChild(CreateSphere(osg::Vec3(0.0, 0.0, 1.5)));

	viewer->setSceneData(gp);
	viewer->run();
	return 0;

}