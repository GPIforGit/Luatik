#include <windows.h>
#include "process.hpp"

namespace TinyProcessLib {

Process::Process(const string_type &command, const string_type &path,
                 const environment_type *environment,
                 bool open_stdin, const Config &config) noexcept
    : closed(true), open_stdin(open_stdin), config(config) {
  open(command, path, environment);
  async_read();
}

Process::~Process() noexcept {
  close_fds();
}

Process::id_type Process::get_id() const noexcept {
  return data.id;
}

bool Process::write(const std::string &str) {
  return write(str.c_str(), str.size());
}

std::string Process::read_stdout() {
    std::lock_guard<std::mutex> lock(stdout_mutex);
    auto ret = stdout_output;
    stdout_output = "";
    return ret;
}
std::string Process::read_stderr() {
    std::lock_guard<std::mutex> lock(stderr_mutex);
    auto ret = stderr_output;
    stderr_output = "";
    return ret;
}


} // namespace TinyProcessLib
