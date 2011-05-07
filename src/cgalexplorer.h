/*
 *   RapCAD - Rapid prototyping CAD IDE (www.rapcad.org)
 *   Copyright (C) 2010-2011 Giles Bathgate
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

#ifndef CGALEXPLORER_H
#define CGALEXPLORER_H

#include <QList>
#include "point.h"
#include "cgal.h"

class CGALExplorer
{
private:
	typedef CGAL::NefPolyhedron3::Vertex_const_handle VertexHandle;
	typedef CGAL::NefPolyhedron3::Halfedge_const_handle HalfEdgeHandle;
	typedef CGAL::NefPolyhedron3::Halffacet_const_handle HalfFacetHandle;
	typedef CGAL::NefPolyhedron3::SHalfedge_const_handle SHalfEdgeHandle;
	typedef CGAL::NefPolyhedron3::SHalfloop_const_handle SHalfLoopHandle;
	typedef CGAL::NefPolyhedron3::SFace_const_handle SFaceHandle;
public:
	typedef QList<CGAL::Point3> Polygon;

	CGALExplorer(const CGAL::NefPolyhedron3&);
	Polygon getPoints();
	CGAL::Bbox_3 getBounds();
	void visit(VertexHandle);
	void visit(HalfEdgeHandle) {}
	void visit(HalfFacetHandle) {}
	void visit(SHalfEdgeHandle) {}
	void visit(SHalfLoopHandle) {}
	void visit(SFaceHandle) {}
private:
	void evaluate();
	const CGAL::NefPolyhedron3& poly;
	Polygon points;
};

#endif // CGALEXPLORER_H
