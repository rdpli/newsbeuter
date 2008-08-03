#include <listformatter.h>
#include <utils.h>
#include <stflpp.h>

namespace newsbeuter {

listformatter::listformatter() : refresh_cache(true) { }

listformatter::~listformatter() { }

void listformatter::add_line(const std::string& text, unsigned int id) {
	lines.push_back(line_id_pair(text, id));
	refresh_cache = true;
}

void listformatter::add_lines(const std::vector<std::string>& thelines) {
	for (std::vector<std::string>::const_iterator it=thelines.begin();it!=thelines.end();++it) {
		add_line(*it);
	}
}

std::string listformatter::format_list(regexmanager * rxman, const std::string& location) {
	format_cache = "{list";
	for (std::vector<line_id_pair>::iterator it=lines.begin();it!=lines.end();++it) {
		std::string str = it->first;
		if (rxman)
			rxman->quote_and_highlight(str, location);
		if (it->second == UINT_MAX) {
			format_cache.append(utils::strprintf("{listitem text:%s}", stfl::quote(str).c_str()));
		} else {
			format_cache.append(utils::strprintf("{listitem[%u] text:%s}", it->second, stfl::quote(str).c_str()));
		}
	}
	format_cache.append(1, '}');
	refresh_cache = false;
	return format_cache;
}

}
