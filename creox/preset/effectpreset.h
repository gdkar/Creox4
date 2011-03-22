/***************************************************************************
						effectpreset.h  -  description
							 -------------------
		begin                : Sun Jun 17 2001
		copyright            : (C) 2001 by Jozef Kosoru
		email                : jozef.kosoru@pobox.sk
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License version 2        *
 *   as published by the Free Software Foundation.                         *
 *                                                                         *
 ***************************************************************************/

#ifndef EFFECTPRESET_H
#define EFFECTPRESET_H

#include <new>
#include <vector>
#include "crexception.h"

class EffectKeeper;
class SoundProcessor;
class QDataStream;

/**
	*@author Jozef Kosoru
	*/
namespace Cr {
class CrException_presetDataError : public CrException_runtimeError {
public:
	CrException_presetDataError(const QString& what_arg): CrException_runtimeError(what_arg) { }
};
}

/**
	*@author Jozef Kosoru
	*/
struct EffectPresetSaveRequest {
	QString m_presetName;
	bool m_saveChain;
	std::vector<int> m_processorIdList;
};

/**
	*@author Jozef Kosoru
	*/
class EffectPreset {
public:
	EffectPreset(const EffectPresetSaveRequest& saveRequest, const EffectKeeper* effectKeeper);
	EffectPreset(QDataStream& dataStream) throw(Cr::CrException_presetDataError,std::bad_alloc);
	~EffectPreset();
	void loadEffect(EffectKeeper* effectKeeper);
	void saveEffect(QDataStream& dataStream) const;
private:
	EffectPreset(const EffectPreset&);
	EffectPreset& operator=(const EffectPreset&);
protected:
	class EffectPresetUnit;
	QString m_presetName;
	bool m_saveChain;
	std::vector<EffectPresetUnit*> m_presetUnitList;
};

/**
	*@author Jozef Kosoru
	*/
class EffectPreset::EffectPresetUnit {
public:
	EffectPresetUnit(const SoundProcessor* processor);
	EffectPresetUnit(QDataStream& dataStream) throw(Cr::CrException_presetDataError,std::bad_alloc);
	~EffectPresetUnit();
	void loadEffectUnit(SoundProcessor* processor);
	void saveEffectUnit(QDataStream& dataStream) const;
	int processorId() const { return m_processorId; }
	float processorVersion() const { return m_processorVersion; }
private:
	EffectPresetUnit(const EffectPresetUnit&);
	EffectPresetUnit& operator=(const EffectPresetUnit&);

	int m_processorId;
	float m_processorVersion;
	char* m_data;
	int m_size;
};

#endif
