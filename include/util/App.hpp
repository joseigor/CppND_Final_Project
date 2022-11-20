

#pragma once

#include "dbus/Server.hpp"
#include "vcs_version.hpp"
#include <sdbus-c++/sdbus-c++.h>
#include <string>

namespace app
{

class App {
public:
	explicit App(const std::string &name);

	std::string Name() const;

	std::string Usage() const;

public:
	inline static const std::string version{VCS_TAG};
	inline static const int version_major{VCS_TAG_MAJOR};
	inline static const int version_minor{VCS_TAG_MINOR};
	inline static const int version_patch{VCS_TAG_PATCH};

private:
	const std::string name_;
};

} // namespace app
