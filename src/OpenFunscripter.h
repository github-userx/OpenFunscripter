#pragma once

#include "SDL.h"
#include "glad/glad.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "ScriptingMode.h"
#include "KeybindingSystem.h"
#include "OpenFunscripterSettings.h"
#include "ScriptPositionsWindow.h"
#include "OpenFunscripterVideoplayer.h"
#include "UndoSystem.h"
#include "event/EventSystem.h"
#include "GradientBar.h"
#include "ScriptSimulator.h"
#include "Funscript.h"
#include "ControllerInput.h"
#include "GradientBar.h"

#include <memory>
#include <array>
#include <chrono>

class OpenFunscripter {
private:
	SDL_Window* window;
	SDL_GLContext gl_context;
	bool exit_app = false;
	
	bool ShowMetadataEditor = false;
	bool ShowStatistics = true;
	bool ShowHistory = true;
	bool Fullscreen = false;
	bool DebugMetrics = false;
	bool DebugDemo = false;
	bool ShowAbout = false;
	
	std::vector<FunscriptAction> CopiedSelection;

	std::chrono::system_clock::time_point last_save_time;
	std::chrono::system_clock::time_point last_backup;

	ImGradient TimelineGradient;
	bool updateTimelineGradient = false;
	char tmp_buf[2][32];

	void register_bindings();

	void update() noexcept;
	void new_frame() noexcept;
	void render() noexcept;
	void rollingBackup() noexcept;

	bool imgui_setup() noexcept;
	void process_events() noexcept;

	void FunscriptChanged(SDL_Event& ev) noexcept;
	void FunscriptActionClicked(SDL_Event& ev) noexcept;

	void FileDialogOpenEvent(SDL_Event& ev) noexcept;
	void FileDialogSaveEvent(SDL_Event& ev) noexcept;
	void DragNDrop(SDL_Event& ev) noexcept;

	void MpvVideoLoaded(SDL_Event& ev) noexcept;

	void cutSelection() noexcept;
	void copySelection() noexcept;
	void pasteSelection() noexcept;
	void equalizeSelection() noexcept;
	void invertSelection() noexcept;
	void isolateAction() noexcept;

	void saveScript(const char* path = nullptr, bool override_location = true);
	void saveHeatmap(const char* path, int width, int height);

	void removeAction(FunscriptAction action) noexcept;
	void removeAction() noexcept;
	void addEditAction(int pos) noexcept;


	void showOpenFileDialog();
	void showSaveFileDialog();
	bool openFile(const std::string& file);
	void updateTitle();
	
	void SetFullscreen(bool fullscreen);

	void UpdateTimelineGradient(ImGradient& grad);

	// UI
	void CreateDockspace() noexcept;
	void ShowAboutWindow(bool* open) noexcept;
	void ShowStatisticsWindow(bool* open) noexcept;
	bool DrawTimelineWidget(const char* label, float* position) noexcept;
	void ShowMainMenuBar() noexcept;
	bool ShowMetadataEditorWindow(bool* open) noexcept;
public:
	static OpenFunscripter* ptr;
	static ImFont* DefaultFont2; // x2 size of default

	~OpenFunscripter();

	KeybindingSystem keybinds;
	ScriptPositionsWindow scriptPositions;
	VideoplayerWindow player;
	ScriptSimulator simulator;
	UndoSystem undoRedoSystem;

	bool RollingBackup = true;

	std::unique_ptr<ScriptingMode> scripting;
	std::unique_ptr<EventSystem> events;
	std::unique_ptr<ControllerInput> rawInput;
	std::unique_ptr<OpenFunscripterSettings> settings;
	std::unique_ptr<Funscript> LoadedFunscript;




	bool setup();
	int run() noexcept;
	void shutdown() noexcept;

	static inline Funscript& script() noexcept { return *OpenFunscripter::ptr->LoadedFunscript; }

	static void SetCursorType(SDL_SystemCursor id) noexcept;
};
