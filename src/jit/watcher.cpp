/// @file
/// @brief Change notification for `--watch`: see jit/watcher.hpp.
///
/// Empty for now. What follows is how each system's version should look,
/// written as the members and calls jit/watcher.hpp lists; each goes inside
/// its own `#if`, the way src/memory/arena.cpp keeps VirtualAlloc and mmap
/// apart, and all of it inside `#if !defined(__EMSCRIPTEN__)`.
#include "jit/watcher.hpp"

namespace jit {
    // -------------------------------------------------------------------
    // Windows: ReadDirectoryChangesW, one directory handle per folder.
    //
    // Opened for listing with FILE_FLAG_OVERLAPPED, so every folder is
    // waited on at once with WaitForMultipleObjects, and with
    // FILE_FLAG_BACKUP_SEMANTICS, without which a folder will not open.
    //
    //     struct Folder {
    //         std::filesystem::path path{};
    //         HANDLE handle{INVALID_HANDLE_VALUE};
    //         OVERLAPPED overlapped{};
    //         alignas(DWORD) std::array<std::byte, 16 * 1024> buffer{};
    //     };
    //     std::vector<std::unique_ptr<Folder>> folders{};  // stable: the system writes into each buffer
    //
    //     void Watcher::post(const std::filesystem::path &folder) {
    //         if (std::ranges::any_of(folders, [&](const auto &each) { return each->path == folder; })) return;
    //         auto watched = std::make_unique<Folder>(Folder{.path = folder});
    //         watched->handle = CreateFileW(folder.c_str(), FILE_LIST_DIRECTORY,
    //                                       FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
    //                                       OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, nullptr);
    //         if (watched->handle == INVALID_HANDLE_VALUE) return;      // main.cpp falls back to polling
    //         watched->overlapped.hEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    //         // Ask for the first batch; each batch read in get() asks for the next.
    //         ReadDirectoryChangesW(watched->handle, watched->buffer.data(), static_cast<DWORD>(watched->buffer.size()),
    //                               FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_FILE_NAME |
    //                                      FILE_NOTIFY_CHANGE_SIZE, nullptr, &watched->overlapped, nullptr);
    //         folders.push_back(std::move(watched));
    //     }
    //
    // get() waits on every folder's event, walks the FILE_NOTIFY_INFORMATION
    // records the system wrote (NextEntryOffset to the next, FileName in
    // UTF-16 and FileNameLength in bytes, not characters), adds each
    // folder / name to what changed, asks for the next batch, and waits
    // again for up to 15 ms of quiet before it returns. The destructor
    // calls CancelIoEx and CloseHandle for each, and CloseHandle on each
    // event.
    //
    // -------------------------------------------------------------------
    // Linux: inotify, one descriptor for every folder.
    //
    //     int descriptor{-1};                               // inotify_init1(IN_NONBLOCK | IN_CLOEXEC)
    //     std::unordered_map<int, std::filesystem::path> folders{};  // watch number -> folder
    //
    //     const int watch = inotify_add_watch(descriptor, folder.c_str(),
    //                                         IN_CLOSE_WRITE | IN_MOVED_TO | IN_CREATE | IN_DELETE);
    //
    // IN_CLOSE_WRITE is a save finished, IN_MOVED_TO a save by rename. get()
    // poll()s the descriptor with the timeout, read()s whole inotify_event
    // records (each sizeof(inotify_event) + len bytes, its name inside), and
    // joins the folder of `wd` with `name`.
    //
    // -------------------------------------------------------------------
    // macOS: FSEvents, one stream over every folder.
    //
    // FSEventStreamCreate with kFSEventStreamCreateFlagFileEvents (so the
    // paths are files, not folders), kFSEventStreamCreateFlagNoDefer and a
    // latency of 0, on a dispatch queue of its own
    // (FSEventStreamSetDispatchQueue); the callback adds the paths under a
    // std::mutex and get() waits on a std::condition_variable. A stream's
    // folders are fixed when it is made, so post() stops it and makes a new
    // one. It needs the CoreServices framework, linked in the top-level
    // CMakeLists.txt beside the engine's other libraries:
    //
    //     if (APPLE)
    //         target_link_libraries(core PUBLIC "-framework CoreServices")
    //     endif ()
    //
    // kqueue would need no framework, but it watches open files, and a save
    // by rename leaves it watching the old one.
    //
    // -------------------------------------------------------------------
    // Testing it (tests/jit/test_watcher.cpp): post a folder under
    // std::filesystem::temp_directory_path(), write a file there from a
    // std::jthread, and assert get() returns it within a second; then write
    // a temporary file and std::filesystem::rename() it over the first, as
    // an editor saves, and assert that is reported once.
}
