#pragma once
#include "libInclude.h"
#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/AutoTransform>
#include <osg/stateset>
#include <osg/stateattribute>

#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgText\Text>
#include <osgUtil/Optimizer>

#include <iostream>

class MyCopyOp :
	public osg::CopyOp
{
public:
	inline MyCopyOp(CopyFlags flage = SHALLOW_COPY)
		: CopyOp(flage)
		, m_nBlank(2)
		, m_nNumber(5)
	{
	}
	virtual ~MyCopyOp() { };

	inline void moveIn() const
	{
		m_nBlank += m_nNumber;
	}
	inline void moveOut() const
	{
		m_nBlank -= m_nNumber;
	}
	inline void writeIndent() const
	{
		for (int i = 0; i < m_nBlank; ++i)
		{
			std::cout << ' ';
		}
	}

	virtual osg::Referenced * operator() (const osg::Referenced *ref)const override;
	virtual osg::Object * operator() (const osg::Object *obj)const override;
	virtual osg::Node * operator() (const osg::Node *node)const override;
	virtual osg::Drawable * operator() (const osg::Drawable *drawable)const override;
	virtual osg::StateSet * operator() (const osg::StateSet *stateset)const override;
	virtual osg::StateAttribute * operator() (const osg::StateAttribute *stateattribute)const override;
	virtual osg::Texture * operator() (const osg::Texture *texture)const override;
	virtual osg::Image * operator() (const osg::Image *img)const override;
private:
	mutable int m_nNumber;
	mutable int m_nBlank;
};

