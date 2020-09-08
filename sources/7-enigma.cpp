#include "common.h"

namespace
{
	constexpr const char *configRotors[3] = {
		"VFTYQMDRIOLGHUKZNABWXSJECP",
		"XGMPSALUFVKHJZTWRCINOBYDQE",
		"UCLHXATGZRNFOJBIEVSYWPDMKQ",
	};
	constexpr const char *configReflector = "GKWRVLSHAJUQPDNIMYFTOEBXZC";
	constexpr const char *configKey = "UKT";

	void rotate(std::string &r)
	{
		CAGE_ASSERT(r.size() == 26);
		r.insert(r.begin(), r[25]);
		r.erase(r.begin() + 26);
	}

	void rotateN(std::string &r, uint32 n)
	{
		for (uint32 i = 0; i < n; i++)
			rotate(r);
	}

	char rotorFwd(char c, const std::string &r)
	{
		return r[c - 'A'];
	}

	char rotorBack(char c, const std::string &r)
	{
		return numeric_cast<char>('A' + r.find(c));
	}

	char reflector(char c)
	{
		auto p = std::string_view(configReflector).find(c);
		if (p < 13)
			p += 13;
		else
			p -= 13;
		return std::string_view(configReflector)[p];
	}

	char str(char c, std::string &r1, std::string &r2, std::string &r3, uint32 &index)
	{
		if (c >= 'A' && c <= 'Z')
		{
			c = rotorFwd(c, r1);
			c = rotorFwd(c, r2);
			c = rotorFwd(c, r3);
			c = reflector(c);
			c = rotorBack(c, r3);
			c = rotorBack(c, r2);
			c = rotorBack(c, r1);
			index++;
			rotate(r1);
			if ((index % 4) == 0)
				rotate(r2);
			if ((index % 11) == 0)
				rotate(r3);
		}
		return c;
	}

	std::string enigmaCode(const std::string &i)
	{
		std::string r1 = configRotors[0];
		std::string r2 = configRotors[1];
		std::string r3 = configRotors[2];
		rotateN(r1, configKey[0] - 'A');
		rotateN(r2, configKey[1] - 'A');
		rotateN(r3, configKey[2] - 'A');

		uint32 index = 0;
		std::string s;
		s.reserve(i.size() + 10);
		for (const char c : i)
			s += str(c, r1, r2, r3, index);

		return s;
	}
}

void cipher7()
{
	constexpr uint32 cypherIndex = 7;

	std::string i = readInput(cypherIndex);
	i = replaceLfToSpaces(i);
	i = replaceCzech(i);
	i = toUpper(i);

	std::string s = enigmaCode(i);
	{
		std::string ss = enigmaCode(s);
		CAGE_ASSERT(ss == i);
	}

	const std::string o = generateHeader(cypherIndex) + s + generateFooter(cypherIndex);
	writeOutput(cypherIndex, o);
}

