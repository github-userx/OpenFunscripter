#pragma once

#include "Funscript.h"

#include <vector>
#include <memory>
#include <string>


// in a previous iteration
// this looked a lot more sophisticated
// while this is not memory efficient this turns out to be incredibly robust and flexible
class ScriptState {
private:
	struct ScriptStateHeader {
		int32_t message_len;
		int32_t actions_len;
		int32_t selection_len;
	};

	Funscript::FunscriptData data;
public:
	inline ScriptStateHeader Header() {
		ScriptStateHeader header;
		header.actions_len = data.Actions.size();
		header.message_len = Message.size();
		header.selection_len = data.selection.size();
		return header;
	}
	inline bool IsOnDisk() const { return DiskPointer != -1; }
	void WriteToDisk(int32_t diskPointer);
	Funscript::FunscriptData& Data();

	int32_t DiskPointer = -1;
	std::string Message;

	ScriptState(const std::string& msg, const Funscript::FunscriptData& data)
		: Message(msg), data(data), DiskPointer(-1) {}
};

class UndoSystem
{
	void SnapshotRedo(const std::string& msg) noexcept;
	// using vector as a stack...
	// because std::stack can't be iterated
	std::vector<ScriptState> UndoStack;
	std::vector<ScriptState> RedoStack;
public:
	int32_t SystemDiskPointer = 0;
	const int32_t MaxScriptStateInMemory = 500;

	void ShowUndoRedoHistory(bool* open);

	void Snapshot(const std::string& msg, bool clearRedo = true) noexcept;
	void Undo() noexcept;
	void Redo() noexcept;
	void ClearHistory() noexcept;
	void ClearRedo() noexcept;

	inline bool UndoEmpty() const { return UndoStack.empty(); }
	inline bool RedoEmpty() const { return RedoStack.empty(); }
};

