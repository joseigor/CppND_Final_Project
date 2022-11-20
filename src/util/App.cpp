

#include "util/App.hpp"

namespace app
{
App::App(const std::string &name)
    : name_{name}
{
}

std::string App::Name() const
{
	return name_;
}

std::string App::Usage() const
{
	return "Usage: " + name_ + ":" + App::version + " [OPTION]\n" +
	       "\t-h, --help\t\tdisplay this help menu and exit application\n" +
	       "\t-v, --version\t\tdisplay application version info\n" +
	       "\t-d, --debug\t\tdisplay debug messages during runtime\n";
}
} // namespace app
