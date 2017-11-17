#include <osg/Vec3>
#include <vector>

std::vector<osg::Vec3f> Caculate(osg::Vec3f v1, osg::Vec3f v2, float fWidth)
{
	std::vector<osg::Vec3f> result;
	if (fWidth <= 0.0)
		return result;
	if (v1.z() != 0 || v2.z() != 0)
		return result;
	if (v1 == v2)
		return result;

	osg::Vec3f tmpV1V2 = v2 - v1;
	osg::Vec3f kV1V2 = tmpV1V2 / tmpV1V2.length(); //单位向量
	float fx = -kV1V2.y();
	float fy = kV1V2.x();
	osg::Vec3f tmpV(fx, fy, 0.0); //垂直单位向量
	osg::Vec3f kV = tmpV * (fWidth / 2); 

	osg::Vec3f rV1 = v1 + kV;
	osg::Vec3f rV2 = v2 + kV;
	osg::Vec3f rV3 = v2 - kV;
	osg::Vec3f rV4 = v1 - kV;
	result.push_back(rV1);
	result.push_back(rV2);
	result.push_back(rV3);
	result.push_back(rV4);
	return result;
}

int main()
{
	osg::Vec3f vt1(0.0, 0.0, 0.0);
	osg::Vec3f vt2(1.732, 1.0, 0.0);
	float ft1 = 4;

	auto result = Caculate(vt1, vt2, ft1);
	return 0;
}