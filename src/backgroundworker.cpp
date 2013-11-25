/*
 *   RapCAD - Rapid prototyping CAD IDE (www.rapcad.org)
 *   Copyright (C) 2010-2013 Giles Bathgate
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

#include "backgroundworker.h"

BackgroundWorker::BackgroundWorker(QTextStream& s,QObject* parent) :
	Worker(s,parent)
{
	thread=new QThread();
	connect(thread,SIGNAL(started()),this,SLOT(evaluateInternal()));
	this->moveToThread(thread);
}

BackgroundWorker::~BackgroundWorker()
{
	delete thread;
}

void BackgroundWorker::evaluate()
{
	thread->start();
}

void BackgroundWorker::finish()
{
	thread->quit();
}
