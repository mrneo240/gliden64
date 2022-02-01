#include <algorithm>
#include <string>
#include "../PluginAPI.h"
#include "../RSP.h"

int PluginAPI::InitiateGFX(const GFX_INFO & _gfxInfo)
{
	_initiateGFX(_gfxInfo);

	return TRUE;
}

void PluginAPI::FindPluginPath(wchar_t * _strPath)
{
#if 0
	if (_strPath == NULL)
		return;
	::GetModuleFileNameW((HINSTANCE)&__ImageBase, _strPath, PLUGIN_PATH_SIZE);
	std::wstring pluginPath(_strPath);
	std::replace(pluginPath.begin(), pluginPath.end(), L'\\', L'/');
	std::wstring::size_type pos = pluginPath.find_last_of(L"/");
	wcscpy(_strPath, pluginPath.substr(0, pos).c_str());
#endif
	wcscpy(_strPath, L"./");
	return;
}

void PluginAPI::GetUserDataPath(wchar_t * _strPath)
{
	FindPluginPath(_strPath);
}

void PluginAPI::GetUserCachePath(wchar_t * _strPath)
{
	FindPluginPath(_strPath);
}
