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

#include <math.h>
#include "rotatemodule.h"
#include "node/transformationnode.h"
#include "numbervalue.h"
#include "vectorvalue.h"
#include "tau.h"

RotateModule::RotateModule() : Module("rotate")
{
	addParameter("angle");
	addParameter("vector");
}

decimal RotateModule::round(decimal a)
{
	return a<0?ceil(a-0.5):floor(a+0.5);
}

bool RotateModule::rightAngle(decimal a)
{
	return fmod(a,90)==0.0;
}

decimal RotateModule::hardCos(decimal a)
{
	decimal ca=cos(a*M_TAU/360.0);
	return rightAngle(a)?round(ca):ca;
}

decimal RotateModule::hardSin(decimal a)
{
	decimal sa=sin(a*M_TAU/360.0);
	return rightAngle(a)?round(sa):sa;
}

Node* RotateModule::evaluate(Context* ctx)
{
	TransformationNode* n=new TransformationNode();

	bool origin;
	Point vec(0.0,0.0,0.1);
	decimal a=0.0;
	NumberValue* angValue=dynamic_cast<NumberValue*>(getParameterArgument(ctx,0));
	if(angValue) {
		a=angValue->getNumber();
		VectorValue* vecValue=dynamic_cast<VectorValue*>(getParameterArgument(ctx,1));
		if(vecValue)
			vec=vecValue->getPoint();
		origin=false;
	} else {
		VectorValue* vecValue=dynamic_cast<VectorValue*>(getParameterArgument(ctx,0));
		if(vecValue)
			vec=vecValue->getPoint();
		origin=true;
	}

	decimal x=0.0,y=0.0,z=0.0;
	vec.getXYZ(x,y,z);
	if(x==0.0&&y==0.0&&z==0.0)
		origin=true;

	if(origin) {

		decimal cx = hardCos(x);
		decimal cy = hardCos(y);
		decimal cz = hardCos(z);
		decimal sx = hardSin(x);
		decimal sy = hardSin(y);
		decimal sz = hardSin(z);

		/*
		Given the three affine transformation matricies for counter-clockwise
		rotations
		Rz = {{cos(z),-sin(z),0,0},{sin(z),cos(z),0,0},{0,0,1,0},{0,0,0,1}}
		Ry = {{cos(y),0,sin(y),0},{0,1,0,0},{-sin(y),0,cos(y),0},{0,0,0,1}}
		Rx = {{1,0,0,0},{0,cos(x),-sin(x),0},{0,sin(x),cos(x),0},{0,0,0,1}}

		We can multiply the matrices to give RzRyRx

		I cheated and used wolfram alpha to do this:
		http://tinyurl.com/q4utr88
		*/

		decimal RzRyRx[16] = {
			cy*cz,cz*sx*sy-cx*sz,cx*cz*sy+sx*sz,0,
			cy*sz,cx*cz+sx*sy*sz,-cz*sx+cx*sy*sz,0,
			-sy,cy*sx,cx*cy,0,
			0,0,0,1
		};

		for(int i=0; i<16; i++)
			n->matrix[i]=RzRyRx[i];

	} else {

		decimal c=hardCos(a);
		decimal s=hardSin(a);

		decimal mag = sqrt(x*x + y*y + z*z);
		decimal u = x/mag;
		decimal v = y/mag;
		decimal w = z/mag;

		decimal TxyTzRaTzTxy[16] = {
			u*u*(1-c)+c,u*v*(1-c)-w*s,u*w*(1-c)+v*s,0,
			u*v*(1-c)+w*s,v*v*(1-c)+c,v*w*(1-c)-u*s,0,
			u*w*(1-c)-v*s,v*w*(1-c)+u*s,w*w*(1-c)+c,0,
			0,0,0,1
		};

		for(int i=0; i<16; i++)
			n->matrix[i]=TxyTzRaTzTxy[i];
	}
	n->setChildren(ctx->getInputNodes());
	return n;
}
