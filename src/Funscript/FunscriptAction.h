#pragma once

#include "OFS_Reflection.h"
//#include "OFS_Serialization.h"
#include <cstdint>
#include <limits>

struct FunscriptAction
{
	int32_t at;
	int32_t pos;

	FunscriptAction() noexcept
		: at(std::numeric_limits<int32_t>::min()), pos(std::numeric_limits<int32_t>::min()) {}

	FunscriptAction(int32_t at, int32_t pos) noexcept
	{
		this->at = at;
		this->pos = pos;
	}

	inline bool operator==(FunscriptAction b) const noexcept {
		return this->at == b.at && this->pos == b.pos; 
	}

	inline bool operator!=(FunscriptAction b) const noexcept {
		return !(*this == b);
	}

	inline bool operator<(FunscriptAction b) const noexcept {
		return this->at < b.at;
	}

	template <class Archive>
	inline void reflect(Archive& ar) {
		OFS_REFLECT(at, ar);
		OFS_REFLECT(pos, ar);
	}
};

struct FunscriptRawAction
{
	int32_t at;
	int32_t frame_no;
	int32_t pos;

	FunscriptRawAction()
		: at(std::numeric_limits<int32_t>::min()),
		frame_no(std::numeric_limits<int32_t>::min()),
		pos(std::numeric_limits<int32_t>::min()) 
	{ }

	FunscriptRawAction(int32_t at, int32_t pos, int32_t frame_no)
		: at(at), pos(pos), frame_no(frame_no) 
	{ }

	template<class Archive>
	inline void reflect(Archive& ar) {
		OFS_REFLECT(at, ar);
		OFS_REFLECT(frame_no, ar);
		OFS_REFLECT(pos, ar);
	}
};

