#pragma once
#include "globalheader.h"

class GameResource
{
public:
	GameResource();
	~GameResource();

	const std::wstring GetKey() { return _key; }
	const std::wstring GetPath() { return _path; }

	void SetKey(const std::wstring& key) { _key = key; }
	void SetPath(const std::wstring& path) { _path = path; }

private:
	std::wstring _key;
	std::wstring _path;
};