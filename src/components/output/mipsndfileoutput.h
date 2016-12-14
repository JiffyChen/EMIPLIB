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
 * \file mipsndfileoutput.h
 */

#ifndef MIPSNDFILEOUTPUT_H

#define MIPSNDFILEOUTPUT_H

#include "mipconfig.h"

#ifdef MIPCONFIG_SUPPORT_SNDFILE

#include "mipcomponent.h"
#include <sndfile.h>

/** A sound file output component.
 *  This component writes incoming sound data to a file. It uses \c libsndfile to
 *  accomplish this. Incoming messages have to be floating point raw audio messages.
 *  No messages are generated by this component.
 */
class MIPSndFileOutput : public MIPComponent
{
public:
	MIPSndFileOutput();
	~MIPSndFileOutput();

	/** Opens a sound file.
	 *  This function opens a sound file. If the file does not exist, the following
	 *  parameters are used in the creation of the file. If the file does exist and
	 *  the \c append parameter is \c true, the corresponding
	 *  parameters are read from the existing file.
	 *  \param fname The name of the file.
	 *  \param sampRate The sampling rate.
	 *  \param channels The number of channels.
	 *  \param bytesPerSample The number of bytes per sample. Can be either 1, 2 or 4.
	 *  \param append Flag to indicate if new data should be added to the end of an
	 *                existing file or if the file should be overwritten if it exists.
	 */
	bool open(const std::string &fname, int sampRate, int channels, int bytesPerSample, bool append);

	/** Closes the sound file.
	 *  Using this function, a previously opened sound file can be closed again.
	 */
	bool close();

	/** Returns the sampling rate of the file. */
	int getSamplingRate() const								{ if (m_pSndFile) return m_sampRate; return 0; }
	
	/** Returns the number of channels in the file. */
	int getNumberOfChannels() const								{ if (m_pSndFile) return m_channels; return 0; }
	
	bool push(const MIPComponentChain &chain, int64_t iteration, MIPMessage *pMsg);
	bool pull(const MIPComponentChain &chain, int64_t iteration, MIPMessage **pMsg);
private:
	SNDFILE *m_pSndFile;
	int m_sampRate;
	int m_channels;
};

#endif // MIPCONFIG_SUPPORT_SNDFILE

#endif // MIPSNDFILEOUTPUT_H

