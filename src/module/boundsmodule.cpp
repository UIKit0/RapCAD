/*
 *   RapCAD - Rapid prototyping CAD IDE (www.rapcad.org)
 *   Copyright (C) 2010-2014 Giles Bathgate
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "boundsmodule.h"
#include "numbervalue.h"
#include "node/boundsnode.h"

BoundsModule::BoundsModule() : Module("bound")
{
	auxilary=true;
	addParameter("precision");
}

Node* BoundsModule::evaluate(Context* ctx)
{
	NumberValue* precVal=dynamic_cast<NumberValue*>(getParameterArgument(ctx,0));

	BoundsNode* n=new BoundsNode();
	if(precVal)
		n->setPrecision(precVal->getNumber());

	n->setChildren(ctx->getInputNodes());
	return n;
}
