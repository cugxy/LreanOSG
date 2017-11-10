#include "libInclude.h"

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	viewer->addEventHandler(new osgViewer::StatsHandler);
	viewer->setSceneData(osgDB::readNodeFile(kstrDataPath + "glider.osg"));
	return viewer->run();
}