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