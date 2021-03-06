#ifndef ROTATEEXTRUDEMODULE_H
#define ROTATEEXTRUDEMODULE_H

#include "primitivemodule.h"
#include "context.h"

class RotateExtrudeModule : public PrimitiveModule
{
public:
	RotateExtrudeModule();
	Node* evaluate(Context*);
};

#endif // ROTATEEXTRUDEMODULE_H
