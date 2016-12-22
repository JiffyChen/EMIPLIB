/*
    
  This file is a part of EMIPLIB, the EDM Media over IP Library.
  
  Copyright (C) 2006-2011  Hasselt University - Expertise Centre for
                      Digital Media (EDM) (http://www.edm.uhasselt.be)

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  
  USA

*/

/**
 * \file mipqt5outputwidget.h
 */

#ifndef MIPQT5OUTPUTWIDGET_H

#define MIPQT5OUTPUTWIDGET_H

#include "mipconfig.h"

#ifdef MIPCONFIG_SUPPORT_QT5

#include "mipcomponent.h"
#include "miptime.h"
#include <QtGui/QOpenGLWindow>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLTexture>
#include <QtWidgets/QMainWindow>
#include <QtCore/QMutex>
#include <jthread/jmutex.h>
#include <map>
#include <set>
#include <vector>

class MIPQt5OutputComponent;
class MIPVideoMessage;
class QOpenGLShaderProgram;
class QOpenGLBuffer;
class QMdiArea;

class MIPQt5OutputWindow : public QOpenGLWindow, public QOpenGLFunctions
{
	Q_OBJECT
private:
	MIPQt5OutputWindow(MIPQt5OutputComponent *pComp, uint64_t sourceID);
public:
	~MIPQt5OutputWindow();
	uint64_t getSourceID() const														{ return m_sourceID; }
private slots:
	void slotInternalNewFrame(MIPVideoMessage *pMsg);
signals:
	void signalResizeWidth(int w);
	void signalResizeHeight(int h);
	void signalResize(int w, int h);

	void signalInternalNewFrame(MIPVideoMessage *pMsg);
private:
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);
	void clearComponent();
	void injectFrame(MIPVideoMessage *pMsg);
	GLuint createTexture();
	void checkDisplayRoutines();

	bool m_init;
	MIPQt5OutputComponent *m_pComponent;
	QMutex m_mutex;
	uint64_t m_sourceID;

	MIPVideoMessage *m_pFrameToProcess;
	int m_prevWidth, m_prevHeight;

	QOpenGLShaderProgram *m_pYUV420Program;
	QOpenGLShaderProgram *m_pRGBProgram;
	QOpenGLShaderProgram *m_pYUYVProgram;
	QOpenGLShaderProgram *m_pLastUsedProgram;
	GLint m_tex0, m_tex1;
	GLint m_widthLoc;

	friend class MIPQt5OutputComponent;
};

class MIPQt5OutputObject : public QObject
{
	Q_OBJECT
private:
	MIPQt5OutputObject();
	~MIPQt5OutputObject();
signals:
	void signalNewSource(quint64 sourceID);
	void signalRemovedSource(quint64 sourceID);
private:
	void callNewSource(quint64 sourceID);
	void callRemovedSource(quint64 sourceID);

	friend class MIPQt5OutputComponent;
};

class MIPQt5OutputMDIWidget : public QMainWindow
{
	Q_OBJECT
public:
	MIPQt5OutputMDIWidget(MIPQt5OutputComponent *pComp);
	~MIPQt5OutputMDIWidget();
private slots:
	void slotResize(int w, int h);
	void slotNewSource(quint64 sourceID);
	void slotRemovedSource(quint64 sourceID);
private:
	MIPQt5OutputComponent *m_pComponent;
	QMdiArea *m_pMdiArea;
};

class MIPQt5OutputComponent : public MIPComponent
{
public:
	MIPQt5OutputComponent();
	~MIPQt5OutputComponent();

	bool init();
	bool destroy();

	// Don't delete this yourself!
	MIPQt5OutputObject *getSignallingObject();

	MIPQt5OutputWindow *createWindow(uint64_t sourceID);

	bool push(const MIPComponentChain &chain, int64_t iteration, MIPMessage *pMsg);
	bool pull(const MIPComponentChain &chain, int64_t iteration, MIPMessage **pMsg);
private:
	void registerWindow(MIPQt5OutputWindow *pWin);
	void unregisterWindow(MIPQt5OutputWindow *pWin);

	std::map<uint64_t, MIPTime> m_sourceTimes;
	std::set<MIPQt5OutputWindow *> m_windows;
	MIPQt5OutputObject *m_pSignalObject;
	jthread::JMutex m_mutex;

	friend class MIPQt5OutputWindow;
};

#endif // MIPCONFIG_SUPPORT_QT5

#endif // MIPQT5OUTPUTWIDGET_H
