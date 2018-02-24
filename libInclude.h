#pragma once

#include <Windows.h>

#ifdef  _DEBUG
#pragma comment(lib, "osgViewerd.lib")
#pragma comment(lib, "osgDBd.lib")
#pragma comment(lib, "OpenThreadsd.lib")
#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgGAd.lib")
#pragma comment(lib, "osgUtild.lib")
#pragma comment(lib, "osgTextd.lib")
#else
#pragma comment(lib, "osgViewer.lib")
#pragma comment(lib, "osgDB.lib")
#pragma comment(lib, "OpenThreads.lib")
#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgGA.lib")
#pragma comment(lib, "osgUtil.lib")
#pragma comment(lib, "osgText.lib")
#endif //  _DEBUG
#include <string>
const std::string kstrDataPath = "E:\\3rdParty\\OSG3.0.0\\data\\";