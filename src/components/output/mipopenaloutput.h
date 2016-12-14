/*
    
  This file is a part of EMIPLIB, the EDM Media over IP Library.
  
  Copyright (C) 2006-2010  Hasselt University - Expertise Centre for
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
 * \file mipopenaloutput.h
 */

#ifndef MIPOPENALOUTPUT_H

#define MIPOPENALOUTPUT_H

#include "mipconfig.h"

#ifdef MIPCONFIG_SUPPORT_OPENAL

#include "mipcomponent.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <map>

/** An OpenAL audio output component.
 *  This component uses the OpenAL audio system to produce 3D audio output.
 *  It accepts raw audio messages using signed 16 bit native endian encoding.
 *  No messages are generated by the component.
 *  TODO's:
 *  - Drop packets when too much delay is being build up.
 *  - Support 8-bit unsigned data.
 *  - Test with two instances of MIPOpenALOutput.
 *  - Does OpenAL even support multiple contexts on the same output device?
 *  - Not Thread safe atm: a mutex on the current context would be needed.
 *  - Support for source position properties relative to own position?
 *  - Allow specification of distance attenuation properties.
 */
class MIPOpenALOutput : public MIPComponent
{
public:
	MIPOpenALOutput();
	virtual ~MIPOpenALOutput();

	/** Initializes the component.
	 *  Initializes the component.
	 *  \param sampRate The sampling rate.
	 *  \param channels The number of channels.
	 *  \param precision The precision of the samples, specified in bits. Currently, only
	 *                   16 bit audio messages are supported.
	*/
	bool open(int sampRate, int channels, int precision = 16);

	/** Closes a previously opened OpenAL audio component. */
	bool close();

	/** Set the position of a particular source.
	 *  Using this function, you can set the position of a particular source.
	 *  Uses a right handed Cartesian coordinate system.
	 */
	bool setSourcePosition(uint64_t sourceID, real_t pos[3]);

	/** Set your own position and orientation.
	 *  Using this function, you can store information about your own position and orientation.
	 *  The \c frontDirection and \c upDirection vectors need not be orthogonal and need not
	 *  be normalized.
	 */
	bool setOwnPosition(real_t pos[3], real_t frontDirection[3], real_t upDirection[3]);

	bool push(const MIPComponentChain &chain, int64_t iteration, MIPMessage *pMsg);
	bool pull(const MIPComponentChain &chain, int64_t iteration, MIPMessage **pMsg);

private:
	bool getSource(uint64_t sourceID, ALuint *pSource);
	bool enqueueData(ALuint source, void *pData, size_t size);
	static ALenum calcFormat(int channels, int precision);

private:
	bool m_init;

	int m_sampRate;
	int m_channels;

	ALenum m_format;
	ALCdevice  *m_pDevice;
	ALCcontext *m_pContext;
	
	std::map<uint64_t, ALuint> m_sources;
};

#endif // MIPCONFIG_SUPPORT_OPENAL

#endif // MIPOPENALOUTPUT_H
