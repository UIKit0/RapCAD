/*
 *   RapCAD - Rapid prototyping CAD IDE (www.rapcad.org)
 *   Copyright (C) 2010-2021 Giles Bathgate
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

#include <QStringList>
#include "versionfunction.h"
#include "context.h"
#include "vectorvalue.h"
#include "numbervalue.h"
#include "textvalue.h"
#include "stringify.h"

VersionFunction::VersionFunction() : Function("version")
{
	addDescription(tr("Returns the version of RapCAD."));
}

Value* VersionFunction::evaluate(const Context&) const
{
	QList<Value*> version;
	QString v=STRINGIFY(RAPCAD_VERSION);
	QStringList parts=v.split(".");
	int major=parts.at(0).toInt();
	int minor=parts.at(1).toInt();
	const QString& build=parts.at(2);
	version.append(Value::factory.createNumber(major));
	version.append(Value::factory.createNumber(minor));
	if(build=="git") {
		version.append(Value::factory.createText(build));
		const QString& revision=parts.at(3);
		version.append(Value::factory.createText(revision));
	} else {
		version.append(new NumberValue(build.toInt()));
	}

	return Value::factory.createVector(version);
}
