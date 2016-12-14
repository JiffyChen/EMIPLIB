/*
    
  This file is a part of EMIPLIB, the EDM Media over IP Library.
  
  Copyright (C) 2006-2009  Hasselt University - Expertise Centre for
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
 * \file miplpcencoder.h
 */

#ifndef MIPLPCENCODER_H

#define MIPLPCENCODER_H

#include "mipconfig.h"

#ifdef MIPCONFIG_SUPPORT_LPC

#include "mipcomponent.h"
#include "miptime.h"
#include <list>

class MIPEncodedAudioMessage;
class LPCEncoder;

/** Compress audio using the LPC codec.
 *  Using this component, signed raw 16 bit (native encoded) audio messages can be 
 *  compressed using the LPC codec. Messages generated by this component 
 *  are encoded audio messages with subtype MIPENCODEDAUDIOMESSAGE_TYPE_LPC.
 */
class MIPLPCEncoder : public MIPComponent
{
public:
	MIPLPCEncoder();
	~MIPLPCEncoder();

	/** Initialize the LPC encoding component. */
	bool init();

	/** Clean up the LPC encoder. */
	bool destroy();

	bool push(const MIPComponentChain &chain, int64_t iteration, MIPMessage *pMsg);
	bool pull(const MIPComponentChain &chain, int64_t iteration, MIPMessage **pMsg);
private:
	void clearMessages();
	
	bool m_init;
	LPCEncoder *m_pEncoder;
	int *m_pFrameBuffer;
	int64_t m_prevIteration;

	std::list<MIPEncodedAudioMessage *> m_messages;
	std::list<MIPEncodedAudioMessage *>::const_iterator m_msgIt;
};	

#endif // MIPCONFIG_SUPPORT_LPC

#endif // MIPLPCENCODER_H

