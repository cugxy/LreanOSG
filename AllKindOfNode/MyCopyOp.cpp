#include "MyCopyOp.h"

osg::Referenced * MyCopyOp::operator()(const osg::Referenced * ref) const
{
	writeIndent();
	std::cout << "Copy Reference " << ref << std::endl;
	moveIn();
	osg::Referenced *ret_ref = CopyOp::operator()(ref);
	moveOut();
	return ret_ref;
}

osg::Object * MyCopyOp::operator()(const osg::Object * obj) const
{
	writeIndent();
	std::cout << "Copy Object " << obj << ' ';
	if (obj)
		std::cout << obj->className() << std::endl;
	moveIn();
	osg::Object *ret_obj= CopyOp::operator()(obj);
	moveOut();
	return ret_obj;
}

osg::Node * MyCopyOp::operator()(const osg::Node * node) const
{
	writeIndent();
	std::cout << "Copy Node " << node << ' ';
	if (node)
		std::cout << node->className() << std::endl;
	moveIn();
	osg::Node *ret_node = CopyOp::operator()(node);
	moveOut();
	return ret_node;
}

osg::Drawable * MyCopyOp::operator()(const osg::Drawable * drawable) const
{
	writeIndent();
	std::cout << "Copy Drawable " << drawable << ' ';
	if (drawable)
		std::cout << drawable->className() << std::endl;
	moveIn();
	osg::Drawable *ret_node = CopyOp::operator()(drawable);
	moveOut();
	return ret_node;
}

osg::StateSet * MyCopyOp::operator()(const osg::StateSet * stateset) const
{
	writeIndent();
	std::cout << "Copy StateSet " << stateset << ' ';
	if (stateset)
		std::cout << stateset->className() << std::endl;
	moveIn();
	osg::StateSet *ret_node = CopyOp::operator()(stateset);
	moveOut();
	return ret_node;
}

osg::StateAttribute * MyCopyOp::operator()(const osg::StateAttribute * stateattribute) const
{
	writeIndent();
	std::cout << "Copy StateAttribute " << stateattribute << ' ';
	if (stateattribute)
		std::cout << stateattribute->className() << std::endl;
	moveIn();
	osg::StateAttribute *ret_node = CopyOp::operator()(stateattribute);
	moveOut();
	return ret_node;
}

osg::Texture * MyCopyOp::operator()(const osg::Texture * texture) const
{
	writeIndent();
	std::cout << "Copy Texture " << texture << ' ';
	if (texture)
		std::cout << texture->className() << std::endl;
	moveIn();
	osg::Texture *ret_node = CopyOp::operator()(texture);
	moveOut();
	return ret_node;
}

osg::Image * MyCopyOp::operator()(const osg::Image * img) const
{
	writeIndent();
	std::cout << "Copy Image " << img << ' ';
	if (img)
		std::cout << img->className() << std::endl;
	moveIn();
	osg::Image *ret_node = CopyOp::operator()(img);
	moveOut();
	return ret_node;
}
